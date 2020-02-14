
#pragma once
#include "vkfg/fg/pipeline.h"
#include "vkfg/vulkan/renderpass/vlogicalrenderpass.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Render Pass
		//

		class VRenderPass final
		{
			// types
		private:
			static constexpr uint	maxColorAttachments = LOO_MaxColorBuffers;
			static constexpr uint	maxAttachments = LOO_MaxColorBuffers + 1;
			static constexpr uint	maxSubpasses = LOO_MaxRenderPassSubpasses;
			static constexpr uint	maxDependencies = maxSubpasses * 2;

			using Attachments_t = FixedArray< VkAttachmentDescription, maxAttachments >;
			using AttachmentsRef_t = FixedArray< VkAttachmentReference, maxAttachments * maxSubpasses >;
			using AttachmentsRef2_t = FixedArray< VkAttachmentReference, maxSubpasses >;
			using Subpasses_t = FixedArray< VkSubpassDescription, maxSubpasses >;
			using Dependencies_t = FixedArray< VkSubpassDependency, maxDependencies >;
			using Preserves_t = FixedArray< uint, maxColorAttachments * maxSubpasses >;
			using SubpassesHash_t = FixedArray< HashVal, maxSubpasses >;


			// variables
		private:
			VkRenderPass			_renderPass = VK_NULL_HANDLE;

			HashVal					_hash;
			HashVal					_attachmentHash;
			SubpassesHash_t			_subpassesHash;

			VkRenderPassCreateInfo	_createInfo = {};
			Attachments_t			_attachments;
			AttachmentsRef_t		_attachmentRef;
			AttachmentsRef_t		_inputAttachRef;
			AttachmentsRef2_t		_resolveAttachRef;
			Subpasses_t				_subpasses;
			Dependencies_t			_dependencies;
			Preserves_t				_preserves;

			DebugName_t				_debugName;

			RWDataRaceCheck			_drCheck;


			// methods
		public:
			VRenderPass () {}
			VRenderPass (VRenderPass &&) = default;
			explicit VRenderPass (ArrayView<VLogicalRenderPass*> logicalPasses);
			~VRenderPass ();

			bool Create (const VDevice &dev, StringView dbgName);
			void Destroy (VResourceManager &);

			ND_ bool operator == (const VRenderPass &rhs) const;

			ND_ VkRenderPass					Handle ()			const { SHAREDLOCK (RWDataRaceCheck,_drCheck);  return _renderPass; }
			ND_ VkRenderPassCreateInfo const&	GetCreateInfo ()	const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _createInfo; }
			ND_ HashVal							GetHash ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _hash; }


		private:
			bool _Initialize (ArrayView<VLogicalRenderPass*> logicalPasses);

			static void  _CalcHash (const VkRenderPassCreateInfo &ci, OUT HashVal &hash, OUT HashVal &attachmentHash,
				OUT SubpassesHash_t &subpassesHash);
		};


	}	
}

namespace std
{
	template <>
	struct hash< loo::vkfg::VRenderPass > {
		ND_ size_t  operator () (const loo::vkfg::VRenderPass &value) const {
			return size_t (value.GetHash ());
		}
	};

}	// std
