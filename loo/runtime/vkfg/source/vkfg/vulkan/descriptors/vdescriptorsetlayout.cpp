
#include "vkfg/fg/pipelineresources.h"
#include "vkfg/fg/pipelineresourceshelper.h"
#include "vkfg/vulkan/descriptors/vdescriptorsetlayout.h"
#include "vkfg/vulkan/utils/venumcast.h"
#include "vkfg/vulkan/instance/vresourcemanager.h"
#include "vkfg/vulkan/instance/vdevice.h"


namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			destructor
		=================================================
		*/
		VDescriptorSetLayout::~VDescriptorSetLayout ()
		{
			CHECK (not _layout);
		}

		/*
		=================================================
			constructor
		=================================================
		*/
		VDescriptorSetLayout::VDescriptorSetLayout (const UniformMapPtr &uniforms, OUT DescriptorBinding_t &binding) :
			_uniforms{ uniforms }
		{
			EXLOCK (RWDataRaceCheck,_drCheck);
			ASSERT (uniforms);

			// bind uniforms
			binding.clear ();
			binding.reserve (_uniforms->size ());

			for (auto& un : *_uniforms)
			{
				ASSERT (un.first.IsDefined ());

				_hash << HashOf (un.first);

				_AddUniform (un.second, INOUT binding);
			}
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VDescriptorSetLayout::Create (const VDevice &dev, const DescriptorBinding_t &binding)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (not _layout);

			VkDescriptorSetLayoutCreateInfo	descriptor_info = {};
			descriptor_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			descriptor_info.pBindings = binding.data ();
			descriptor_info.bindingCount = uint (binding.size ());

			VK_CHECK (dev.vkCreateDescriptorSetLayout (dev.GetVkDevice (), &descriptor_info, null, OUT &_layout));

			_resourcesTemplate = PipelineResourcesHelper::CreateDynamicData (_uniforms, _maxIndex + 1, _elementCount, _dynamicOffsetCount);
			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VDescriptorSetLayout::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (_descSetCache.size ()) {
				resMngr.GetDescriptorManager ().DeallocDescriptorSets (_descSetCache);
			}

			if (_layout) {
				auto&	dev = resMngr.GetDevice ();
				dev.vkDestroyDescriptorSetLayout (dev.GetVkDevice (), _layout, null);
			}

			_descSetCache.clear ();
			_resourcesTemplate.reset ();
			_poolSize.clear ();

			_uniforms = null;
			_layout = VK_NULL_HANDLE;
			_hash = Default;
			_maxIndex = 0;
			_elementCount = 0;
			_dynamicOffsetCount = 0;
		}

		/*
		=================================================
			AllocDescriptorSet
		=================================================
		*/
		bool  VDescriptorSetLayout::AllocDescriptorSet (VResourceManager &resMngr, OUT DescriptorSet &ds) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);

			ds = { VK_NULL_HANDLE, UMax };

			// get from cache
			{
				EXLOCK (SpinLock,_descSetCacheGuard);

				if (_descSetCache.size ())
				{
					ds = _descSetCache.back ();
					_descSetCache.pop_back ();
					return true;
				}
			}

			return resMngr.GetDescriptorManager ().AllocDescriptorSet (_layout, OUT ds);
		}

		/*
		=================================================
			ReleaseDescriptorSet
		=================================================
		*/
		void  VDescriptorSetLayout::ReleaseDescriptorSet (VResourceManager &resMngr, const DescriptorSet &ds) const
		{
			SHAREDLOCK (RWDataRaceCheck,_drCheck);
			EXLOCK (SpinLock, _descSetCacheGuard);

			if (_descSetCache.size () == _descSetCache.capacity ())
			{
				resMngr.GetDescriptorManager ().DeallocDescriptorSets (_descSetCache);
				_descSetCache.clear ();
			}

			_descSetCache.push_back (ds);
		}

		/*
		=================================================
			_AddUniform
		=================================================
		*/
		struct _AddUniform_VisitFuncLocal
		{
			VDescriptorSetLayout& _this;
			const PipelineDescription::Uniform &un;
			VDescriptorSetLayout::DescriptorBinding_t &binding;

			_AddUniform_VisitFuncLocal (VDescriptorSetLayout& t,
			const PipelineDescription::Uniform & u,
			VDescriptorSetLayout::DescriptorBinding_t &b)
				:_this(t),un(u),binding(b)
			{}

			void operator()(const PipelineDescription::Texture &tex)const {
				_this._AddTexture (tex, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			}
			void operator()(const PipelineDescription::Sampler &samp)const {
				_this._AddSampler (samp, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			}
			void operator()(const PipelineDescription::SubpassInput &spi)const {
				_this._AddSubpassInput (spi, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			}
			void operator()(const PipelineDescription::Image &img)const {
				_this._AddImage (img, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			}
			void operator()(const PipelineDescription::UniformBuffer &ub)const {
				_this._AddUniformBuffer (ub, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			}
			void operator()(const PipelineDescription::StorageBuffer &sb)const {
				_this._AddStorageBuffer (sb, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			}
			void operator()(const PipelineDescription::RayTracingScene &rts)const {
				_this._AddRayTracingScene (rts, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			}
			void operator()(const NullUnion &)const {
				ASSERT (false);
			}
		};
		void VDescriptorSetLayout::_AddUniform (const PipelineDescription::Uniform &un, INOUT DescriptorBinding_t &binding)
		{
			ASSERT (un.index.VKBinding () != UMax);
			_AddUniform_VisitFuncLocal visitfunc (*this, un, binding);
			Visit (un.data,
#if 1
				visitfunc
#else
				[&](const PipelineDescription::Texture &tex) {
				_AddTexture (tex, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			},
				[&](const PipelineDescription::Sampler &samp) {
				_AddSampler (samp, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			},
				[&](const PipelineDescription::SubpassInput &spi) {
				_AddSubpassInput (spi, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			},
				[&](const PipelineDescription::Image &img) {
				_AddImage (img, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			},
				[&](const PipelineDescription::UniformBuffer &ub) {
				_AddUniformBuffer (ub, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			},
				[&](const PipelineDescription::StorageBuffer &sb) {
				_AddStorageBuffer (sb, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			},
				[&](const PipelineDescription::RayTracingScene &rts) {
				_AddRayTracingScene (rts, un.index.VKBinding (), un.arraySize, un.stageFlags, INOUT binding);
			},
				[](const NullUnion &) {
				ASSERT (false);
			}
#endif
			);
		}

		/*
		=================================================
			_IncDescriptorCount
		=================================================
		*/
		void VDescriptorSetLayout::_IncDescriptorCount (VkDescriptorType type)
		{
			for (auto& size : _poolSize)
			{
				if (size.type == type)
				{
					++size.descriptorCount;
					return;
				}
			}

			_poolSize.emplace_back (type, 1u);
		}

		/*
		=================================================
			_AddImage
		=================================================
		*/
		void VDescriptorSetLayout::_AddImage (const PipelineDescription::Image &img, uint bindingIndex,
			uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding)
		{
			// calculate hash
			_hash << HashOf (img.imageType)
				<< HashOf (img.format)
				<< HashOf (bindingIndex)
				<< HashOf (stageFlags)
				<< HashOf (img.state)
				<< HashOf (arraySize);

			arraySize = (arraySize ? arraySize : LOO_MaxElementsInUnsizedDesc);
			_elementCount += arraySize;

			// add binding
			VkDescriptorSetLayoutBinding	bind = {};
			bind.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			bind.stageFlags = VEnumCast (stageFlags);
			bind.binding = bindingIndex;
			bind.descriptorCount = arraySize;

			_maxIndex = loo::math::Max (_maxIndex, bind.binding);
			_IncDescriptorCount (bind.descriptorType);

			binding.push_back (std::move (bind));
		}

		/*
		=================================================
			_AddTexture
		=================================================
		*/
		void VDescriptorSetLayout::_AddTexture (const PipelineDescription::Texture &tex, uint bindingIndex,
			uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding)
		{
			// calculate hash
			_hash << HashOf (tex.textureType)
				<< HashOf (bindingIndex)
				<< HashOf (stageFlags)
				<< HashOf (tex.state)
				<< HashOf (arraySize);

			arraySize = (arraySize ? arraySize : LOO_MaxElementsInUnsizedDesc);
			_elementCount += arraySize;

			// add binding
			VkDescriptorSetLayoutBinding	bind = {};
			bind.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			bind.stageFlags = VEnumCast (stageFlags);
			bind.binding = bindingIndex;
			bind.descriptorCount = arraySize;

			_maxIndex = loo::math::Max (_maxIndex, bind.binding);
			_IncDescriptorCount (bind.descriptorType);

			binding.push_back (std::move (bind));
		}

		/*
		=================================================
			_AddSampler
		=================================================
		*/
		void VDescriptorSetLayout::_AddSampler (const PipelineDescription::Sampler &, uint bindingIndex,
			uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding)
		{
			// calculate hash
			_hash << HashOf (bindingIndex)
				<< HashOf (stageFlags)
				<< HashOf (arraySize);

			arraySize = (arraySize ? arraySize : LOO_MaxElementsInUnsizedDesc);
			_elementCount += arraySize;

			// add binding
			VkDescriptorSetLayoutBinding	bind = {};
			bind.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
			bind.stageFlags = VEnumCast (stageFlags);
			bind.binding = bindingIndex;
			bind.descriptorCount = arraySize;

			_maxIndex = loo::math::Max (_maxIndex, bind.binding);
			_IncDescriptorCount (bind.descriptorType);

			binding.push_back (std::move (bind));
		}

		/*
		=================================================
			_AddSubpassInput
		=================================================
		*/
		void VDescriptorSetLayout::_AddSubpassInput (const PipelineDescription::SubpassInput &spi, uint bindingIndex,
			uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding)
		{
			// calculate hash
			_hash << HashOf (spi.attachmentIndex)
				<< HashOf (spi.isMultisample)
				<< HashOf (bindingIndex)
				<< HashOf (stageFlags)
				<< HashOf (spi.state)
				<< HashOf (arraySize);

			arraySize = (arraySize ? arraySize : LOO_MaxElementsInUnsizedDesc);
			_elementCount += arraySize;

			// add binding
			VkDescriptorSetLayoutBinding	bind = {};
			bind.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			bind.stageFlags = VEnumCast (stageFlags);
			bind.binding = bindingIndex;
			bind.descriptorCount = arraySize;

			_maxIndex = loo::math::Max (_maxIndex, bind.binding);
			_IncDescriptorCount (bind.descriptorType);

			binding.push_back (std::move (bind));
		}

		/*
		=================================================
			_AddUniformBuffer
		=================================================
		*/
		void VDescriptorSetLayout::_AddUniformBuffer (const PipelineDescription::UniformBuffer &ub, uint bindingIndex,
			uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding)
		{
			// calculate hash
			_hash << HashOf (ub.size)
				<< HashOf (bindingIndex)
				<< HashOf (stageFlags)
				<< HashOf (ub.state)
				<< HashOf (arraySize);

			const bool	is_dynamic = EnumEq (ub.state, EResourceState::_BufferDynamicOffset);

			arraySize = (arraySize ? arraySize : LOO_MaxElementsInUnsizedDesc);
			_elementCount += arraySize;
			_dynamicOffsetCount += (is_dynamic ? arraySize : 0);

			// add binding
			VkDescriptorSetLayoutBinding	bind = {};
			bind.descriptorType = is_dynamic ? VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC : VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			bind.stageFlags = VEnumCast (stageFlags);
			bind.binding = bindingIndex;
			bind.descriptorCount = arraySize;

			_maxIndex = loo::math::Max (_maxIndex, bind.binding);
			_IncDescriptorCount (bind.descriptorType);

			binding.push_back (std::move (bind));
		}

		/*
		=================================================
			_AddStorageBuffer
		=================================================
		*/
		void VDescriptorSetLayout::_AddStorageBuffer (const PipelineDescription::StorageBuffer &sb, uint bindingIndex,
			uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding)
		{
			// calculate hash
			_hash << HashOf (sb.staticSize)
				<< HashOf (sb.arrayStride)
				<< HashOf (bindingIndex)
				<< HashOf (stageFlags)
				<< HashOf (sb.state)
				<< HashOf (arraySize);

			const bool	is_dynamic = EnumEq (sb.state, EResourceState::_BufferDynamicOffset);

			arraySize = (arraySize ? arraySize : LOO_MaxElementsInUnsizedDesc);
			_elementCount += arraySize;
			_dynamicOffsetCount += (is_dynamic ? arraySize : 0);

			// add binding
			VkDescriptorSetLayoutBinding	bind = {};
			bind.descriptorType = is_dynamic ? VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC : VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			bind.stageFlags = VEnumCast (stageFlags);
			bind.binding = bindingIndex;
			bind.descriptorCount = arraySize;

			_maxIndex = loo::math::Max (_maxIndex, bind.binding);
			_IncDescriptorCount (bind.descriptorType);

			binding.push_back (std::move (bind));
		}

		/*
		=================================================
			_AddRayTracingScene
		=================================================
		*/
		void VDescriptorSetLayout::_AddRayTracingScene (const PipelineDescription::RayTracingScene &rts, uint bindingIndex,
			uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding)
		{
			// calculate hash
			_hash << HashOf (rts.state)
				<< HashOf (arraySize);

			arraySize = (arraySize ? arraySize : LOO_MaxElementsInUnsizedDesc);
			_elementCount += arraySize;

			// add binding
			VkDescriptorSetLayoutBinding	bind = {};
			bind.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
			bind.stageFlags = VEnumCast (stageFlags);
			bind.binding = bindingIndex;
			bind.descriptorCount = arraySize;

			_maxIndex = loo::math::Max (_maxIndex, bind.binding);
			_IncDescriptorCount (bind.descriptorType);

			binding.push_back (std::move (bind));
		}

		/*
		=================================================
			operator ==
		=================================================
		*/
		bool VDescriptorSetLayout::operator == (const VDescriptorSetLayout &rhs) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			SHAREDLOCK (RWDataRaceCheck, rhs._drCheck);

			if (_hash != rhs._hash or
				not (_uniforms and rhs._uniforms) or
				_uniforms->size () != rhs._uniforms->size ())
			{
				return false;
			}

			for (auto& un : *_uniforms)
			{
				auto	iter = rhs._uniforms->find (un.first);

				if (iter == rhs._uniforms->end () or
					not (un.second == iter->second))
					return false;
			}
			return true;
		}


	}	
}