#include "vkfg/vulkan/pipeline/vpipelinelayout.h"
#include "vkfg/vulkan/instance/vresourcemanager.h"
#include "vkfg/vulkan/instance/vdevice.h"
#include "vkfg/vulkan/utils/venumcast.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			PushConstantEquals
		=================================================
		*/
		ND_ inline bool PushConstantEquals (const PipelineDescription::PushConstant &lhs, const PipelineDescription::PushConstant &rhs)
		{
			return	lhs.offset == rhs.offset;
		}

		/*
		=================================================
			PushConstantGreater
		=================================================
		*/
		ND_ inline bool PushConstantGreater (const PipelineDescription::PushConstant &lhs, const PipelineDescription::PushConstant &rhs)
		{
			return	lhs.offset > rhs.offset;
		}

		/*
		=================================================
			PushConstantHash
		=================================================
		*/
		ND_ inline HashVal PushConstantHash (const Pair<PushConstantID, PipelineDescription::PushConstant> &pc)
		{
			return HashOf (pc.first) + HashOf (pc.second.stageFlags) + HashOf (pc.second.offset) + HashOf (pc.second.size);
		}
		//-----------------------------------------------------------------------------



		/*
		=================================================
			destructor
		=================================================
		*/
		VPipelineLayout::~VPipelineLayout ()
		{
			CHECK (_layout == VK_NULL_HANDLE);
		}

		/*
		=================================================
			constructor
		=================================================
		*/
		VPipelineLayout::VPipelineLayout (const PipelineDescription::PipelineLayout &ppln, DSLayoutArray_t sets)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			ASSERT (ppln.descriptorSets.size () == sets.size ());
			ASSERT (_layout == VK_NULL_HANDLE);

			_AddDescriptorSets (ppln, sets, INOUT _hash, OUT _descriptorSets);
			_AddPushConstants (ppln, INOUT _hash, OUT _pushConstants);
		}

		/*
		=================================================
			_AddDescriptorSets
		=================================================
		*/
		void VPipelineLayout::_AddDescriptorSets (const PipelineDescription::PipelineLayout &ppln, DSLayoutArray_t sets,
			INOUT HashVal &hash, OUT DescriptorSets_t &setsInfo) const
		{
			setsInfo.clear ();

			for (size_t i = 0; i < ppln.descriptorSets.size (); ++i)
			{
				auto&	ds = ppln.descriptorSets[i];
				auto&	res = sets[i].second->Data ();

				ASSERT (ds.id.IsDefined ());
				ASSERT (ds.bindingIndex < MaxDescSets);
				ASSERT (res.Handle ());

				setsInfo.insert ({ ds.id, DescSetLayout{ sets[i].first, res.Handle (), ds.bindingIndex } });

				// calculate hash
				hash << HashOf (ds.id);
				hash << HashOf (ds.bindingIndex);
				hash << res.GetHash ();
			}
		}

		/*
		=================================================
			_AddPushConstants
		=================================================
		*/
		void VPipelineLayout::_AddPushConstants (const PipelineDescription::PipelineLayout &ppln, INOUT HashVal &hash,
			OUT PushConstants_t &pushConst) const
		{
			pushConst = ppln.pushConstants;

			for (auto& pc : ppln.pushConstants)
			{
				ASSERT (pc.first.IsDefined ());

				// calculate hash
				hash << PushConstantHash (pc);
			}
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VPipelineLayout::Create (const VDevice &dev, VkDescriptorSetLayout emptyLayout)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (_layout == VK_NULL_HANDLE);

			VkDescriptorSetLayouts_t	vk_layouts;
			VkPushConstantRanges_t		vk_ranges;

			for (auto& layout : vk_layouts) {
				layout = emptyLayout;
			}

			uint	min_set = uint (vk_layouts.size ());
			uint	max_set = 0;
			auto	ds_iter = _descriptorSets.begin ();

			for (size_t i = 0; ds_iter != _descriptorSets.end (); ++i, ++ds_iter)
			{
				auto&	ds = ds_iter->second;
				ASSERT (vk_layouts[ds.index] == emptyLayout);
				ASSERT (ds.layout);

				vk_layouts[ds.index] = ds.layout;
				min_set = loo::math::Min (min_set, ds.index);
				max_set = loo::math::Max (max_set, ds.index);
			}

			for (auto& pc : _pushConstants)
			{
				VkPushConstantRange	range = {};
				range.offset = uint (pc.second.offset);
				range.size = uint (pc.second.size);
				range.stageFlags = VEnumCast (pc.second.stageFlags);

				vk_ranges.push_back (range);
			}

			VkPipelineLayoutCreateInfo			layout_info = {};
			layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			layout_info.setLayoutCount = max_set + 1;
			layout_info.pSetLayouts = vk_layouts.data ();
			layout_info.pushConstantRangeCount = uint (vk_ranges.size ());
			layout_info.pPushConstantRanges = vk_ranges.data ();

			VK_CHECK (dev.vkCreatePipelineLayout (dev.GetVkDevice (), &layout_info, null, OUT &_layout));

			_firstDescSet = min_set;
			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VPipelineLayout::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (_layout) {
				auto&	dev = resMngr.GetDevice ();
				dev.vkDestroyPipelineLayout (dev.GetVkDevice (), _layout, null);
			}

			for (auto& ds : _descriptorSets) {
				resMngr.ReleaseResource (ds.second.layoutId);
			}

			_descriptorSets.clear ();
			_pushConstants.clear ();

			_layout = VK_NULL_HANDLE;
			_hash = Default;
			_firstDescSet = UMax;
		}

		/*
		=================================================
			IsAllResourcesAlive
		=================================================
		*/
		bool VPipelineLayout::IsAllResourcesAlive (const VResourceManager &resMngr) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);

			for (auto& ds : _descriptorSets)
			{
				if (not resMngr.IsResourceAlive (ds.second.layoutId))
					return false;
			}
			return true;
		}

		/*
		=================================================
			operator ==
		=================================================
		*/
		bool VPipelineLayout::operator == (const VPipelineLayout &rhs) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			SHAREDLOCK (RWDataRaceCheck, rhs._drCheck);

			if (_hash != rhs._hash)
				return false;

			if (_descriptorSets.size () != rhs._descriptorSets.size ())
				return false;

			const size_t	ds_count = _descriptorSets.size ();
			auto			lhs_ds = _descriptorSets.begin ();
			auto			rhs_ds = rhs._descriptorSets.begin ();

			for (size_t i = 0; i < _descriptorSets.size (); ++i, ++lhs_ds, ++rhs_ds)
			{
				if (lhs_ds->second.index != rhs_ds->second.index)
					return false;

				ASSERT (lhs_ds->second.layout);
				ASSERT (rhs_ds->second.layout);

				if (not (lhs_ds->second.layoutId == rhs_ds->second.layoutId))
					return false;
			}
			return true;
		}

		/*
		=================================================
			GetDescriptorSetLayout
		=================================================
		*/
		bool VPipelineLayout::GetDescriptorSetLayout (const DescriptorSetID &id, OUT RawDescriptorSetLayoutID &layout, OUT uint &binding) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);

			auto	iter = _descriptorSets.find (id);

			if (iter != _descriptorSets.end ())
			{
				layout = iter->second.layoutId;
				binding = iter->second.index;
				return true;
			}

			return false;
		}


	}	
}