
#include "vkfg/vulkan/swapchain/vswapchain.h"
#include "vkfg/vulkan/instance/vdevice.h"
#include "vkfg/vulkan/commandbuffer/vcommandbuffer.h"

namespace loo
{

	namespace vkfg
	{

		/*
		=================================================
			constructor
		=================================================
		*/
		VSwapchain::VSwapchain ()
		{
		}

		/*
		=================================================
			destructor
		=================================================
		*/
		VSwapchain::~VSwapchain ()
		{
			ASSERT (not _vkSwapchain);
			ASSERT (not _imageAvailable);
			ASSERT (not _renderFinished);
		}

		/*
		=================================================
			_IsImageAcquired
		=================================================
		*/
		inline bool  VSwapchain::_IsImageAcquired () const
		{
			return _currImageIndex < _imageIDs.size ();
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VSwapchain::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (not _IsImageAcquired ()/*, void ()*/);

			auto&	dev = resMngr.GetDevice ();

			if (_vkSwapchain)
				dev.vkDestroySwapchainKHR (dev.GetVkDevice (), _vkSwapchain, null);

			if (_imageAvailable)
				dev.vkDestroySemaphore (dev.GetVkDevice (), _imageAvailable, null);

			if (_renderFinished)
				dev.vkDestroySemaphore (dev.GetVkDevice (), _renderFinished, null);

			_DestroyImages (resMngr);

			_imageAvailable = VK_NULL_HANDLE;
			_renderFinished = VK_NULL_HANDLE;
			_presentQueue = null;

			_surfaceSize = Default;
			_vkSwapchain = VK_NULL_HANDLE;
			_vkSurface = VK_NULL_HANDLE;
			_currImageIndex = UMax;

			_colorFormat = VK_FORMAT_UNDEFINED;
			_colorSpace = VK_COLOR_SPACE_MAX_ENUM_KHR;
			_minImageCount = 2;
			_preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			_presentMode = VK_PRESENT_MODE_FIFO_KHR;
			_compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			_colorImageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		}

		/*
		=================================================
			Acquire
		=================================================
		*/
		bool VSwapchain::Acquire (VCommandBuffer &fgThread, ESwapchainImage type, OUT RawImageID &outImageId) const
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (_vkSwapchain);
			CHECK_ERR (type == ESwapchainImage::Primary);

			if (_IsImageAcquired ())
			{
				outImageId = _imageIDs[_currImageIndex].Get ();
				return true;
			}

			VkAcquireNextImageInfoKHR	info = {};
			info.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
			info.swapchain = _vkSwapchain;
			info.timeout = UMax;
			info.semaphore = _imageAvailable;
			info.deviceMask = 1;

			auto&	dev = fgThread.GetDevice ();
			VK_CHECK (dev.vkAcquireNextImage2KHR (dev.GetVkDevice (), &info, OUT &_currImageIndex));

			outImageId = _imageIDs[_currImageIndex].Get ();

			fgThread.WaitSemaphore (_imageAvailable, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
			fgThread.SignalSemaphore (_renderFinished);

			return true;
		}

		/*
		=================================================
			Present
		=================================================
		*/
		bool VSwapchain::Present (const VDevice &dev) const
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (not _IsImageAcquired ())
				return false;	// TODO ?

			VkPresentInfoKHR	present_info = {};
			present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			present_info.swapchainCount = 1;
			present_info.pSwapchains = &_vkSwapchain;
			present_info.pImageIndices = &_currImageIndex;
			present_info.waitSemaphoreCount = 1;
			present_info.pWaitSemaphores = &_renderFinished;

			VkResult	err = dev.vkQueuePresentKHR (_presentQueue->handle, &present_info);

			_currImageIndex = UMax;

			switch (err) {
			case VK_SUCCESS:
				break;

			case VK_SUBOPTIMAL_KHR:
			case VK_ERROR_SURFACE_LOST_KHR:
			case VK_ERROR_OUT_OF_DATE_KHR:
				// TODO: recreate swapchain
			default:
				RETURN_ERR ("Present failed");
			}
			return true;
		}

		/*
		=================================================
			_CreateSwapchain
		=================================================
		*/
		bool VSwapchain::_CreateSwapchain (VFrameGraph &fg, StringView dbgName)
		{
			VkSwapchainKHR				old_swapchain = _vkSwapchain;
			VkSwapchainCreateInfoKHR	swapchain_info = {};
			VDevice const &				dev = fg.GetDevice ();

			swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			swapchain_info.surface = _vkSurface;
			swapchain_info.imageFormat = _colorFormat;
			swapchain_info.imageColorSpace = _colorSpace;
			swapchain_info.imageExtent = { _surfaceSize.x, _surfaceSize.y };
			swapchain_info.imageArrayLayers = 1;
			swapchain_info.minImageCount = _minImageCount;
			swapchain_info.oldSwapchain = old_swapchain;
			swapchain_info.clipped = VK_TRUE;
			swapchain_info.preTransform = _preTransform;
			swapchain_info.presentMode = _presentMode;
			swapchain_info.compositeAlpha = _compositeAlpha;
			swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			swapchain_info.imageUsage = _colorImageUsage;

			VK_CHECK (dev.vkCreateSwapchainKHR (dev.GetVkDevice (), &swapchain_info, null, OUT &_vkSwapchain));

			_DestroyImages (fg.GetResourceManager ());

			if (old_swapchain != VK_NULL_HANDLE)
				dev.vkDestroySwapchainKHR (dev.GetVkDevice (), old_swapchain, null);

			if (dbgName.size ())
				dev.SetObjectName (BitCast<uint64_t> (_vkSwapchain), dbgName, VK_OBJECT_TYPE_SWAPCHAIN_KHR);

			// get supported queue families
			{
				auto	qmask = dev.GetQueueFamilyMask ();
				_queueFamilyMask = Default;

				for (uint qindex = 0; (1u << qindex) <= uint (qmask); ++qindex)
				{
					VkBool32	supports_present = 0;
					VK_CALL (vkGetPhysicalDeviceSurfaceSupportKHR (dev.GetVkPhysicalDevice (), qindex, _vkSurface, OUT &supports_present));

					_queueFamilyMask |= EQueueFamilyMask (supports_present ? (1u << qindex) : 0);
				}
				_queueFamilyMask &= qmask;
			}

			CHECK_ERR (_CreateImages (fg.GetResourceManager ()));
			CHECK_ERR (_CreateSemaphores (dev));
			CHECK_ERR (_ChoosePresentQueue (fg));
			return true;
		}

		/*
		=================================================
			_CreateImages
		=================================================
		*/
		bool VSwapchain::_CreateImages (VResourceManager &resMngr)
		{
			ASSERT (_imageIDs.empty ());

			FixedArray< VkImage, MaxImages >	images;
			VDevice const&						dev = resMngr.GetDevice ();
			{
				uint	count = 0;
				VK_CHECK (dev.vkGetSwapchainImagesKHR (dev.GetVkDevice (), _vkSwapchain, OUT &count, null));
				CHECK_ERR (count > 0);

				images.resize (count);
				VK_CHECK (dev.vkGetSwapchainImagesKHR (dev.GetVkDevice (), _vkSwapchain, INOUT &count, OUT images.data ()));
			}

			_imageIDs.resize (images.size ());

			VulkanImageDesc		desc = {};
			desc.imageType = BitCast<ImageTypeVk_t> (VK_IMAGE_TYPE_2D);
			desc.usage = BitCast<ImageUsageVk_t> (_colorImageUsage);
			desc.format = BitCast<FormatVk_t> (_colorFormat);
			desc.currentLayout = BitCast<ImageLayoutVk_t> (VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
			desc.defaultLayout = desc.currentLayout;
			desc.samples = BitCast<SampleCountFlagBitsVk_t> (VK_SAMPLE_COUNT_1_BIT);
			desc.dimension = loo::math::uint3{ _surfaceSize.x, _surfaceSize.y, 1 };
			desc.arrayLayers = 1;
			desc.maxLevels = 1;
			desc.queueFamily = VK_QUEUE_FAMILY_IGNORED;

			char	image_name[] = "SwapchainImage-0";

			for (size_t i = 0; i < images.size (); ++i)
			{
				desc.image = BitCast<ImageVk_t> (images[i]);
				image_name[sizeof (image_name) - 2] = char ('0' + i);

				_imageIDs[i] = ImageID{ resMngr.CreateImage (desc, {}, image_name) };
			}
			return true;
		}

		/*
		=================================================
			_DestroyImages
		=================================================
		*/
		void VSwapchain::_DestroyImages (VResourceManager &resMngr)
		{
			for (auto& id : _imageIDs)
			{
				resMngr.ReleaseResource (id.Release ());
			}
			_imageIDs.clear ();
		}

		/*
		=================================================
			_CreateSemaphores
		=================================================
		*/
		bool VSwapchain::_CreateSemaphores (const VDevice &dev)
		{
			if (_imageAvailable and _renderFinished)
				return true;

			VkSemaphoreCreateInfo	info = {};
			info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

			VK_CHECK (dev.vkCreateSemaphore (dev.GetVkDevice (), &info, null, OUT &_imageAvailable));
			VK_CHECK (dev.vkCreateSemaphore (dev.GetVkDevice (), &info, null, OUT &_renderFinished));

			dev.SetObjectName (BitCast<uint64_t> (_imageAvailable), "ImageAvailable", VK_OBJECT_TYPE_SEMAPHORE);
			dev.SetObjectName (BitCast<uint64_t> (_renderFinished), "RenderAvailable", VK_OBJECT_TYPE_SEMAPHORE);

			return true;
		}

		/*
		=================================================
			_ChoosePresentQueue
		=================================================
		*/
		bool VSwapchain::_ChoosePresentQueue (const VFrameGraph &fg)
		{
			if (_presentQueue)
				return true;

			for (uint i = 0; i < uint (EQueueType::_Count); ++i)
			{
				auto	q = fg.FindQueue (EQueueType (i));
				if (q)
				{
					VkBool32	supports_present = 0;
					VK_CALL (vkGetPhysicalDeviceSurfaceSupportKHR (fg.GetDevice ().GetVkPhysicalDevice (), uint (q->familyIndex), _vkSurface, OUT &supports_present));

					if (supports_present) {
						_presentQueue = q;
						return true;
					}
				}
			}

			RETURN_ERR ("can't find queue that supports present");
		}

		/*
		=================================================
			GetDefaultPresentModes
		=================================================
		*/
		static void GetDefaultPresentModes (ArrayView<VkPresentModeKHR> presentModes, OUT Appendable<VkPresentModeKHR> result)
		{
			bool	fifo_mode_supported = false;
			bool	mailbox_mode_supported = false;
			bool	immediate_mode_supported = false;

			for (size_t i = 0; i < presentModes.size (); ++i)
			{
				fifo_mode_supported |= (presentModes[i] == VK_PRESENT_MODE_FIFO_KHR);
				mailbox_mode_supported |= (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR);
				immediate_mode_supported |= (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR);
			}

			if (mailbox_mode_supported)
				result.push_back (VK_PRESENT_MODE_MAILBOX_KHR);
			else
				if (fifo_mode_supported)
					result.push_back (VK_PRESENT_MODE_FIFO_KHR);
				else
					if (immediate_mode_supported)
						result.push_back (VK_PRESENT_MODE_IMMEDIATE_KHR);
					else
						result.push_back (presentModes.front ());
		}

		/*
		=================================================
			IsPresentModeSupported
		=================================================
		*/
		ND_ static bool IsPresentModeSupported (ArrayView<VkPresentModeKHR> presentModes, VkPresentModeKHR required)
		{
			for (size_t i = 0; i < presentModes.size (); ++i)
			{
				if (presentModes[i] == required)
					return true;
			}
			return false;
		}

		/*
		=================================================
			GetCompositeAlpha
		=================================================
		*/
		static bool GetCompositeAlpha (INOUT VkCompositeAlphaFlagBitsKHR &compositeAlpha, const VkSurfaceCapabilitiesKHR &surfaceCaps)
		{
			if (compositeAlpha == 0)
				compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

			if (EnumEq (surfaceCaps.supportedCompositeAlpha, compositeAlpha))
				return true;	// keep current

			compositeAlpha = VK_COMPOSITE_ALPHA_FLAG_BITS_MAX_ENUM_KHR;

			for (VkCompositeAlphaFlagBitsKHR flag = VkCompositeAlphaFlagBitsKHR (0);
				flag < VK_COMPOSITE_ALPHA_FLAG_BITS_MAX_ENUM_KHR;
				flag = VkCompositeAlphaFlagBitsKHR (flag << 1))
			{
				if (EnumEq (surfaceCaps.supportedCompositeAlpha, flag))
				{
					compositeAlpha = flag;
					return true;
				}
			}
			RETURN_ERR ("no suitable composite alpha flags found!");
		}

		/*
		=================================================
			GetSwapChainExtent
		=================================================
		*/
		static void GetSwapChainExtent (INOUT loo::math::uint2 &extent, const VkSurfaceCapabilitiesKHR &surfaceCaps)
		{
			if (surfaceCaps.currentExtent.width == UMax and
				surfaceCaps.currentExtent.height == UMax)
			{
				// keep window size
			}
			else
			{
				extent.x = surfaceCaps.currentExtent.width;
				extent.y = surfaceCaps.currentExtent.height;
			}
		}

		/*
		=================================================
			GetSurfaceImageCount
		=================================================
		*/
		static void GetSurfaceImageCount (INOUT uint &minImageCount, const VkSurfaceCapabilitiesKHR &surfaceCaps)
		{
			if (minImageCount < surfaceCaps.minImageCount)
			{
				minImageCount = surfaceCaps.minImageCount;
			}

			if (surfaceCaps.maxImageCount > 0 and minImageCount > surfaceCaps.maxImageCount)
			{
				minImageCount = surfaceCaps.maxImageCount;
			}
		}

		/*
		=================================================
			GetSurfaceTransform
		=================================================
		*/
		static void GetSurfaceTransform (INOUT VkSurfaceTransformFlagBitsKHR &transform, const VkSurfaceCapabilitiesKHR &surfaceCaps)
		{
			if (transform == 0)
				transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

			if (EnumEq (surfaceCaps.supportedTransforms, transform))
				return;	// keep current

			if (EnumEq (surfaceCaps.supportedTransforms, VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR))
			{
				transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			}
			else
			{
				transform = surfaceCaps.currentTransform;
			}
		}

		/*
		=================================================
			GetDefaultColorFormats
		=================================================
		*/
		static void GetDefaultColorFormats (ArrayView<VkSurfaceFormat2KHR> formats, OUT Appendable<Pair<VkFormat, VkColorSpaceKHR>> result)
		{
			const VkFormat	default_fmt = VK_FORMAT_B8G8R8A8_UNORM;

			// add first 3 formats
			for (size_t i = 0; i < loo::math::Min (formats.size (), 3u); ++i)
			{
				auto&	item = formats[i].surfaceFormat;

				result.emplace_back ((item.format == VK_FORMAT_UNDEFINED ? default_fmt : item.format), item.colorSpace);
			}
		}

		/*
		=================================================
			IsColorFormatSupported
		=================================================
		*/
		ND_ static bool IsColorFormatSupported (ArrayView<VkSurfaceFormat2KHR> formats, const VkFormat requiredFormat, const VkColorSpaceKHR requiredColorSpace)
		{
			for (size_t i = 0; i < formats.size (); ++i)
			{
				auto&	item = formats[i].surfaceFormat;

				// supports any format
				if (item.format == VK_FORMAT_UNDEFINED and
					item.colorSpace == requiredColorSpace)
					return true;

				if (item.format == requiredFormat and
					item.colorSpace == requiredColorSpace)
					return true;
			}
			return false;
		}

		/*
		=================================================
			GetImageUsage
		=================================================
		*/
		static bool GetImageUsage (OUT VkImageUsageFlags &imageUsage, const VDevice &dev, const VkPresentModeKHR presentMode,
			const VkFormat colorFormat, const VkSurfaceCapabilities2KHR &surfaceCaps)
		{
			if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR or
				presentMode == VK_PRESENT_MODE_MAILBOX_KHR or
				presentMode == VK_PRESENT_MODE_FIFO_KHR or
				presentMode == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
			{
				imageUsage = surfaceCaps.surfaceCapabilities.supportedUsageFlags;
			}
			else
				if (presentMode == VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR or
					presentMode == VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR)
				{
					for (VkBaseInStructure const *iter = reinterpret_cast<VkBaseInStructure const *>(&surfaceCaps);
						iter != null;
						iter = iter->pNext)
					{
						if (iter->sType == VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR)
						{
							imageUsage = reinterpret_cast<VkSharedPresentSurfaceCapabilitiesKHR const*>(iter)->sharedPresentSupportedUsageFlags;
							break;
						}
					}
				}
				else
				{
					//RETURN_ERR( "unsupported presentMode, can't choose imageUsage!" );
					return false;
				}

			ASSERT (EnumEq (imageUsage, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT));
			imageUsage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;


			// validation:
			VkFormatProperties	format_props;
			vkGetPhysicalDeviceFormatProperties (dev.GetVkPhysicalDevice (), colorFormat, OUT &format_props);

			CHECK_ERR (EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT));
			ASSERT (EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT));

			if (EnumEq (imageUsage, VK_IMAGE_USAGE_TRANSFER_SRC_BIT) and
				(not EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_TRANSFER_SRC_BIT) or
					not EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_BLIT_DST_BIT)))
			{
				imageUsage &= ~VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			}

			if (EnumEq (imageUsage, VK_IMAGE_USAGE_TRANSFER_DST_BIT) and
				not EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_TRANSFER_DST_BIT))
			{
				imageUsage &= ~VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			}

			if (EnumEq (imageUsage, VK_IMAGE_USAGE_STORAGE_BIT) and
				not EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT))
			{
				imageUsage &= ~VK_IMAGE_USAGE_STORAGE_BIT;
			}

			if (EnumEq (imageUsage, VK_IMAGE_USAGE_SAMPLED_BIT) and
				not EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT))
			{
				imageUsage &= ~VK_IMAGE_USAGE_SAMPLED_BIT;
			}

			if (EnumEq (imageUsage, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) and
				not EnumEq (format_props.optimalTilingFeatures, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT))
			{
				imageUsage &= ~VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			}

			return true;
		}

		/*
		=================================================
			IsSupported
		=================================================
		*/
		static bool IsSupported (const VDevice &dev, const VkSurfaceCapabilities2KHR &surfaceCaps, const loo::math::uint2 &surfaceSize, const VkPresentModeKHR presentMode,
			const VkFormat colorFormat, INOUT VkImageUsageFlags &colorImageUsage)
		{
			VkImageUsageFlags	image_usage = 0;
			if (not GetImageUsage (OUT image_usage, dev, presentMode, colorFormat, surfaceCaps))
				return false;

			if (not EnumAny (image_usage, colorImageUsage))
				return false;

			VkImageFormatProperties	image_props = {};
			VK_CALL (vkGetPhysicalDeviceImageFormatProperties (dev.GetVkPhysicalDevice (), colorFormat, VK_IMAGE_TYPE_2D,
				VK_IMAGE_TILING_OPTIMAL, image_usage, 0, OUT &image_props));

			if (not EnumEq (image_props.sampleCounts, VK_SAMPLE_COUNT_1_BIT))
				return false;

			if (surfaceSize.x > image_props.maxExtent.width or
				surfaceSize.y > image_props.maxExtent.height or
				image_props.maxExtent.depth == 0)
				return false;

			if (image_props.maxArrayLayers < 1)
				return false;

			colorImageUsage = image_usage;
			return true;
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VSwapchain::Create (VFrameGraph &fg, const VulkanSwapchainCreateInfo &info, StringView dbgName)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (_vkSwapchain)
			{
				CHECK_ERR (_vkSurface == BitCast<VkSurfaceKHR> (info.surface));
			}

			VDevice const&	dev = fg.GetDevice ();

			_vkSurface = BitCast<VkSurfaceKHR> (info.surface);

			VkPhysicalDeviceSurfaceInfo2KHR	surf_info = {};
			surf_info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
			surf_info.surface = _vkSurface;

			// get surface capabilities
			VkSurfaceCapabilities2KHR		surf_caps = {};
			{
				surf_caps.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
				VK_CHECK (vkGetPhysicalDeviceSurfaceCapabilities2KHR (dev.GetVkPhysicalDevice (), &surf_info, OUT &surf_caps));
			}

			// get surface formats
			Array< VkSurfaceFormat2KHR >	surf_formats;
			{
				uint	count = 0;
				VK_CHECK (vkGetPhysicalDeviceSurfaceFormats2KHR (dev.GetVkPhysicalDevice (), &surf_info, OUT &count, null));
				CHECK_ERR (count > 0);

				surf_formats.resize (count);
				for (auto& fmt : surf_formats) { fmt.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR; }

				VK_CHECK (vkGetPhysicalDeviceSurfaceFormats2KHR (dev.GetVkPhysicalDevice (), &surf_info, INOUT &count, OUT surf_formats.data ()));
			}

			// get present modes
			Array< VkPresentModeKHR >		present_modes;
			{
				uint	count = 0;
				VK_CHECK (vkGetPhysicalDeviceSurfacePresentModesKHR (dev.GetVkPhysicalDevice (), _vkSurface, OUT &count, null));
				CHECK_ERR (count > 0);

				present_modes.resize (count);
				VK_CHECK (vkGetPhysicalDeviceSurfacePresentModesKHR (dev.GetVkPhysicalDevice (), _vkSurface, INOUT &count, OUT present_modes.data ()));
			}

			_compositeAlpha = BitCast<VkCompositeAlphaFlagBitsKHR> (info.compositeAlpha);
			CHECK_ERR (GetCompositeAlpha (INOUT _compositeAlpha, surf_caps.surfaceCapabilities));

			_surfaceSize = info.surfaceSize;
			GetSwapChainExtent (INOUT _surfaceSize, surf_caps.surfaceCapabilities);

			_minImageCount = info.minImageCount;
			GetSurfaceImageCount (INOUT _minImageCount, surf_caps.surfaceCapabilities);

			_preTransform = BitCast<VkSurfaceTransformFlagBitsKHR> (info.preTransform);
			GetSurfaceTransform (INOUT _preTransform, surf_caps.surfaceCapabilities);


			// try to use current settings
			if (_vkSwapchain)
			{
				const bool	present_mode_supported = IsPresentModeSupported (present_modes, _presentMode) and (info.presentModes.empty () or
					IsPresentModeSupported (ArrayView<VkPresentModeKHR>{ BitCast<VkPresentModeKHR const *> (info.presentModes.data ()), info.presentModes.size () }, _presentMode));

				bool		color_format_supported = IsColorFormatSupported (surf_formats, _colorFormat, _colorSpace);

				if (not info.formats.empty ())
				{
					bool	found = false;
					for (auto& pair : info.formats) {
						if (VkFormat (pair.first) == _colorFormat and VkColorSpaceKHR (pair.second) == _colorSpace) {
							found = true;
							break;
						}
					}
					color_format_supported &= found;
				}

				if (present_mode_supported and color_format_supported)
					return _CreateSwapchain (fg, dbgName);
			}


			// find suitable color format
			FixedArray< VkPresentModeKHR, 8 >	default_present_modes;
			GetDefaultPresentModes (present_modes, OUT default_present_modes);

			FixedArray< Pair<VkFormat, VkColorSpaceKHR>, 8 >	default_color_formats;
			GetDefaultColorFormats (surf_formats, OUT default_color_formats);

			const auto	required_usage = BitCast<VkImageUsageFlags> (info.requiredUsage);
			const auto	optional_usage = BitCast<VkImageUsageFlags> (info.optionalUsage) | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			const auto	required_present_modes = info.presentModes.empty () ?
				ArrayView<VkPresentModeKHR>{ default_present_modes } :
				ArrayView<VkPresentModeKHR>{ BitCast<VkPresentModeKHR const *> (info.presentModes.data ()), info.presentModes.size () };

			const auto	required_color_formats = info.formats.empty () ?
				ArrayView<Pair<VkFormat, VkColorSpaceKHR>>{ default_color_formats } :
				ArrayView<Pair<VkFormat, VkColorSpaceKHR>>{ BitCast<Pair<VkFormat, VkColorSpaceKHR> const *> (info.formats.data ()), info.formats.size () };

			for (auto mode : required_present_modes)
			{
				if (not IsPresentModeSupported (present_modes, mode))
					continue;

				for (auto fmt : required_color_formats)
				{
					_colorFormat = fmt.first;
					_colorSpace = fmt.second;

					if (not IsColorFormatSupported (surf_formats, _colorFormat, _colorSpace))
						continue;

					_colorImageUsage = required_usage | optional_usage;
					_presentMode = mode;

					if (IsSupported (dev, surf_caps, _surfaceSize, _presentMode, _colorFormat, INOUT _colorImageUsage) and
						(not required_usage or EnumEq (_colorImageUsage, required_usage)))
					{
						return _CreateSwapchain (fg, dbgName);
					}
				}
			}

			RETURN_ERR ("can't find suitable format");
		}

	}	
}