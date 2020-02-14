
#pragma once
#include "vkfg/fg/imagedesc.h"
#include "vkfg/vulkan/renderpass/vrenderpass.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Framebuffer
		//

		class VFramebuffer final
		{
			// types
		private:
			using Attachments_t = FixedArray< Pair<RawImageID, ImageViewDesc>, LOO_MaxColorBuffers + 1 >;


			// variables
		private:
			HashVal					_hash;
			VkFramebuffer			_framebuffer;
			RawRenderPassID			_renderPassId;

			loo::math::uint2					_dimension;
			ImageLayer				_layers;
			Attachments_t			_attachments;

			DebugName_t				_debugName;

			RWDataRaceCheck			_drCheck;


			// methods
		public:
			VFramebuffer ();
			VFramebuffer (VFramebuffer &&) = default;
			VFramebuffer (ArrayView<Pair<RawImageID, ImageViewDesc>> attachments, RawRenderPassID rp, loo::math::uint2 dim, uint layers);
			~VFramebuffer ();

			bool Create (VResourceManager &, StringView dbgName);
			void Destroy (VResourceManager &);

			ND_ bool IsAllResourcesAlive (const VResourceManager &) const;

			ND_ bool operator == (const VFramebuffer &rhs) const;

			ND_ VkFramebuffer		Handle ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _framebuffer; }
			ND_ RawRenderPassID		GetRenderPassID ()	const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _renderPassId; }
			ND_ loo::math::uint2 const&		Dimension ()		const { SHAREDLOCK (RWDataRaceCheck,_drCheck);  return _dimension; }
			ND_ uint				Layers ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _layers.Get (); }
			ND_ HashVal				GetHash ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _hash; }
		};


	}	

}
namespace std
{
	template <>
	struct hash< loo::vkfg::VFramebuffer > {
		ND_ size_t  operator () (const loo::vkfg::VFramebuffer &value) const {
			return size_t (value.GetHash ());
		}
	};

}	// std
