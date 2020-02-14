
#include "vkfg/vulkan/renderpass/vframebuffer.h"
#include "vkfg/vulkan/instance/vdevice.h"
#include "vkfg/vulkan/instance/vresourcemanager.h"


namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			constructor
		=================================================
		*/
		VFramebuffer::VFramebuffer () :
			_hash{ 0 },
			_framebuffer{ VK_NULL_HANDLE }
		{
		}

		/*
		=================================================
			destructor
		=================================================
		*/
		VFramebuffer::~VFramebuffer ()
		{
			CHECK (_framebuffer == VK_NULL_HANDLE);
		}

		/*
		=================================================
			IsAllResourcesAlive
		=================================================
		*/
		bool VFramebuffer::IsAllResourcesAlive (const VResourceManager &resMngr) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);

			for (auto& attach : _attachments)
			{
				if (not resMngr.IsResourceAlive (attach.first))
					return false;
			}
			return true;
		}

		/*
		=================================================
			operator ==
		=================================================
		*/
		bool VFramebuffer::operator == (const VFramebuffer &rhs) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			SHAREDLOCK (RWDataRaceCheck, rhs._drCheck);

			if (_hash != rhs._hash)
				return false;

			return	All (_dimension == rhs._dimension) and
				_layers == rhs._layers		and
				_attachments == rhs._attachments	and
				_renderPassId == rhs._renderPassId;
		}

		/*
		=================================================
			constructor
		=================================================
		*/
		VFramebuffer::VFramebuffer (ArrayView<Pair<RawImageID, ImageViewDesc>> attachments, RawRenderPassID rp, loo::math::uint2 dim, uint layers)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			ASSERT (not attachments.empty ());

			_attachments = attachments;
			_renderPassId = rp;
			_dimension = dim;
			_layers = ImageLayer (layers);

			// calc hash
			_hash = HashOf (_attachments);
			_hash << HashOf (_renderPassId);
			_hash << HashOf (_dimension);
			_hash << HashOf (_layers);
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VFramebuffer::Create (VResourceManager &resMngr, StringView dbgName)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (not _framebuffer);
			CHECK_ERR (_renderPassId);

			FixedArray< VkImageView, LOO_MaxColorBuffers + 1 >		image_views;
			VDevice const &										dev = resMngr.GetDevice ();

			for (auto& rt : _attachments)
			{
				auto*		image = resMngr.GetResource (rt.first);
				CHECK_ERR (image);

				VkImageView	view = image->GetView (dev, false, INOUT rt.second);
				CHECK_ERR (view);

				image_views.push_back (view);
			}

			// create framebuffer
			VkFramebufferCreateInfo		fb_info = {};

			fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			fb_info.renderPass = resMngr.GetResource (_renderPassId)->Handle ();
			fb_info.attachmentCount = uint (image_views.size ());
			fb_info.pAttachments = image_views.data ();
			fb_info.width = _dimension.x;
			fb_info.height = _dimension.y;
			fb_info.layers = _layers.Get ();

			VK_CHECK (dev.vkCreateFramebuffer (dev.GetVkDevice (), &fb_info, null, OUT &_framebuffer));

			_debugName = dbgName;
			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VFramebuffer::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (_framebuffer) {
				auto&	dev = resMngr.GetDevice ();
				dev.vkDestroyFramebuffer (dev.GetVkDevice (), _framebuffer, null);
			}

			if (_renderPassId) {
				resMngr.ReleaseResource (_renderPassId);
			}

			for (auto& att : _attachments) {
				resMngr.ReleaseResource (att.first);
			}

			_framebuffer = VK_NULL_HANDLE;
			_hash = Default;
			_renderPassId = Default;
			_dimension = Default;
			_layers = Default;

			_attachments.clear ();
			_debugName.clear ();
		}


	}	
}