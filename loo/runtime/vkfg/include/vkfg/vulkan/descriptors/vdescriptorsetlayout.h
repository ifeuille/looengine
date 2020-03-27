
#pragma once
#include "vkfg/fg/pipeline.h"
#include "vkfg/fg/pipelineresources.h"
#include "vkfg/vulkan/vcommon.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Descriptor Set Layout
		//
		struct _AddUniform_VisitFuncLocal;
		class VDescriptorSetLayout final
		{
			friend _AddUniform_VisitFuncLocal;
			// types
		public:
			using DescriptorBinding_t = Array< VkDescriptorSetLayoutBinding >;
			using DescriptorSet = Pair< VkDescriptorSet, /*pool index*/uint8_t >;

		private:
			using UniformMapPtr = PipelineDescription::UniformMapPtr;
			using PoolSizeArray_t = FixedArray< VkDescriptorPoolSize, 10 >;
			using DynamicDataPtr = PipelineResources::DynamicDataPtr;
			using DescSetCache_t = FixedArray< DescriptorSet, 32 >;


			// variables
		private:
			HashVal					_hash;
			VkDescriptorSetLayout	_layout = VK_NULL_HANDLE;
			UniformMapPtr			_uniforms;
			PoolSizeArray_t			_poolSize;
			uint					_maxIndex = 0;
			uint					_elementCount = 0;
			uint					_dynamicOffsetCount = 0;
			DynamicDataPtr			_resourcesTemplate;

			mutable SpinLock		_descSetCacheGuard;
			mutable DescSetCache_t	_descSetCache;

			DebugName_t				_debugName;
			// TODO: desc set update template

			mutable RWDataRaceCheck			_drCheck;


			// methods
		public:
			VDescriptorSetLayout () {}
			VDescriptorSetLayout (VDescriptorSetLayout &&) = default;
			VDescriptorSetLayout (const UniformMapPtr &uniforms, OUT DescriptorBinding_t &binding);
			~VDescriptorSetLayout ();

			bool Create (const VDevice &dev, const DescriptorBinding_t &binding);
			void Destroy (VResourceManager &);

			bool AllocDescriptorSet (VResourceManager &, OUT DescriptorSet &) const;
			void ReleaseDescriptorSet (VResourceManager &, const DescriptorSet &) const;

			ND_ bool	operator == (const VDescriptorSetLayout &rhs) const;

			ND_ VkDescriptorSetLayout	Handle ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _layout; }
			ND_ HashVal					GetHash ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _hash; }
			ND_ UniformMapPtr const&	GetUniforms ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _uniforms; }
			ND_ DynamicDataPtr const&	GetResources ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _resourcesTemplate; }
			ND_ uint					GetMaxIndex ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _maxIndex; }
			ND_ StringView				GetDebugName ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _debugName; }


		private:
			void _AddUniform (const PipelineDescription::Uniform &un, INOUT DescriptorBinding_t &binding);
			void _AddImage (const PipelineDescription::Image &img, uint bindingIndex, uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding);
			void _AddTexture (const PipelineDescription::Texture &tex, uint bindingIndex, uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding);
			void _AddSampler (const PipelineDescription::Sampler &samp, uint bindingIndex, uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding);
			void _AddSubpassInput (const PipelineDescription::SubpassInput &spi, uint bindingIndex, uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding);
			void _AddUniformBuffer (const PipelineDescription::UniformBuffer &ub, uint bindingIndex, uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding);
			void _AddStorageBuffer (const PipelineDescription::StorageBuffer &sb, uint bindingIndex, uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding);
			void _AddRayTracingScene (const PipelineDescription::RayTracingScene &rts, uint bindingIndex, uint arraySize, EShaderStages stageFlags, INOUT DescriptorBinding_t &binding);
			void _IncDescriptorCount (VkDescriptorType type);
		};

	}	
}

namespace std
{

	template <>
	struct hash< loo::vkfg::VDescriptorSetLayout >
	{
		ND_ size_t  operator () (const loo::vkfg::VDescriptorSetLayout &value) const {
			return size_t (value.GetHash ());
		}
	};

}	// std
