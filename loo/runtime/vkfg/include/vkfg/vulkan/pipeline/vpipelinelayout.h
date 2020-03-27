
#pragma once
#include "vkfg/fg/resourcebase.h"
#include "vkfg/vulkan/descriptors/vdescriptorsetlayout.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Pipeline Layout
		//

		class VPipelineLayout final
		{
			// types
		private:
			struct DescSetLayout
			{
				RawDescriptorSetLayoutID	layoutId;
				VkDescriptorSetLayout		layout = VK_NULL_HANDLE;	// TODO: remove?
				uint						index = 0;

				DescSetLayout () {}
				DescSetLayout (RawDescriptorSetLayoutID id, VkDescriptorSetLayout layout, uint index) : layoutId{ id }, layout{ layout }, index{ index } {}
			};

			// the last index will be used for shader debugger
			static constexpr uint	MaxDescSets = LOO_MaxDescriptorSets;

			using DescriptorSets_t = FixedMap< DescriptorSetID, DescSetLayout, MaxDescSets >;
			using PushConstants_t = PipelineDescription::PushConstants_t;
			using VkDescriptorSetLayouts_t = StaticArray< VkDescriptorSetLayout, MaxDescSets >;
			using VkPushConstantRanges_t = FixedArray< VkPushConstantRange, LOO_MaxPushConstants >;
			using DSLayoutArray_t = ArrayView<Pair<RawDescriptorSetLayoutID, ResourceBase<VDescriptorSetLayout> *>>;


			// variables
		private:
			HashVal					_hash;
			VkPipelineLayout		_layout = VK_NULL_HANDLE;
			DescriptorSets_t		_descriptorSets;
			PushConstants_t			_pushConstants;
			uint					_firstDescSet = UMax;

			DebugName_t				_debugName;

			mutable RWDataRaceCheck			_drCheck;


			// methods
		public:
			VPipelineLayout () {}
			VPipelineLayout (VPipelineLayout &&) = default;
			VPipelineLayout (const PipelineDescription::PipelineLayout &ppln, DSLayoutArray_t sets);
			~VPipelineLayout ();

			bool Create (const VDevice &dev, VkDescriptorSetLayout emptyLayout);
			void Destroy (VResourceManager &);

			bool  GetDescriptorSetLayout (const DescriptorSetID &id, OUT RawDescriptorSetLayoutID &layout, OUT uint &binding) const;

			ND_ bool  IsAllResourcesAlive (const VResourceManager &) const;

			ND_ bool  operator == (const VPipelineLayout &rhs) const;

			ND_ VkPipelineLayout		Handle ()					const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _layout; }
			ND_ HashVal					GetHash ()					const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _hash; }

			ND_ StringView				GetDebugName ()				const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _debugName; }

			ND_ uint					GetFirstDescriptorSet ()	const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _firstDescSet; }
			ND_ DescriptorSets_t const&	GetDescriptorSets ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _descriptorSets; }
			ND_ PushConstants_t const&	GetPushConstants ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _pushConstants; }


		private:
			void _AddDescriptorSets (const PipelineDescription::PipelineLayout &ppln, DSLayoutArray_t sets,
				INOUT HashVal &hash, OUT DescriptorSets_t &setsInfo) const;
			void _AddPushConstants (const PipelineDescription::PipelineLayout &ppln,
				INOUT HashVal &hash, OUT PushConstants_t &pushConst) const;
		};

	}
}

namespace std
{

	template <>
	struct hash< loo::vkfg::VPipelineLayout >
	{
		ND_ size_t  operator () (const loo::vkfg::VPipelineLayout &value) const {
			return size_t (value.GetHash ());
		}
	};

}	// std
