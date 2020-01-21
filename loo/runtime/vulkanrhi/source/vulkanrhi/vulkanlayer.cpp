#include "global/global.h"
#include "vulkanrhi/vulkanrhiprivate.h"
#include "vulkanrhi/vulkandevice.h"
#include "global/template/external.h"
#include "ifvk/IfVK.h"

#ifdef LOO_PLATFORM_LINUX
#include <SDL.h>
#endif


#if VULKAN_HAS_DEBUGGING_ENABLED

#if VULKAN_ENABLE_DRAW_MARKERS
#define RENDERDOC_LAYER_NAME	"VK_LAYER_RENDERDOC_Capture"
#endif

// List of validation layers which we want to activate for the instance
static const loo::ANSICHAR* GRequiredLayersInstance[] =
{
	nullptr,
};

// Disable to be able to selectively choose which validation layers you want
#define VULKAN_ENABLE_STANDARD_VALIDATION	0

// List of validation layers which we want to activate for the instance
static const loo::ANSICHAR* GValidationLayersInstance[] =
{
#if VULKAN_ENABLE_STANDARD_VALIDATION
	"VK_LAYER_LUNARG_standard_validation",
#else
	"VK_LAYER_GOOGLE_threading",
	"VK_LAYER_LUNARG_parameter_validation",
	"VK_LAYER_LUNARG_object_tracker",
#if defined(VK_HEADER_VERSION) && (VK_HEADER_VERSION < 42)
	"VK_LAYER_LUNARG_image",
#endif
	"VK_LAYER_LUNARG_core_validation",
#if defined(VK_HEADER_VERSION) && (VK_HEADER_VERSION < 51)
	"VK_LAYER_LUNARG_swapchain",
#endif
	"VK_LAYER_GOOGLE_unique_objects",
#endif

	//"VK_LAYER_LUNARG_screenshot",
	//"VK_LAYER_NV_optimus",
	//"VK_LAYER_LUNARG_vktrace",		// Useful for future
	nullptr
};

// List of validation layers which we want to activate for the device
static const loo::ANSICHAR* GRequiredLayersDevice[] =
{
	nullptr,
};

// List of validation layers which we want to activate for the device
static const loo::ANSICHAR* GValidationLayersDevice[] =
{
	// Only have device validation layers on SDKs below 13
#if defined(VK_HEADER_VERSION) && (VK_HEADER_VERSION < 13)
#if VULKAN_ENABLE_STANDARD_VALIDATION
	"VK_LAYER_LUNARG_standard_validation",
#else
	"VK_LAYER_GOOGLE_threading",
	"VK_LAYER_LUNARG_parameter_validation",
	"VK_LAYER_LUNARG_object_tracker",
	"VK_LAYER_LUNARG_image",
	"VK_LAYER_LUNARG_core_validation",
	"VK_LAYER_LUNARG_swapchain",
	"VK_LAYER_GOOGLE_unique_objects",
	"VK_LAYER_LUNARG_core_validation",
#endif	// Standard Validation
#endif	// Header < 13
	//"VK_LAYER_LUNARG_screenshot",
	//"VK_LAYER_NV_optimus",
	//"VK_LAYER_NV_nsight",
	//"VK_LAYER_LUNARG_vktrace",		// Useful for future
	nullptr
};
#endif // VULKAN_HAS_DEBUGGING_ENABLED

// Instance Extensions to enable
static const loo::ANSICHAR* GInstanceExtensions[] =
{
#if !defined(LOO_PLATFORM_LINUX)
	VK_KHR_SURFACE_EXTENSION_NAME,
#endif
#if defined(LOO_PLATFORM_ANDROID)
	VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#elif defined(LOO_PLATFORM_LINUX)
	//	VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
	#elif defined(LOO_PLATFORM_WINDOWS)
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
	#endif
	#if VULKAN_HAS_DEBUGGING_ENABLED
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
	#endif
	#if VULKAN_ENABLE_DESKTOP_HMD_SUPPORT
		VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,
		VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
	#endif
		nullptr
};

// Device Extensions to enable
static const loo::ANSICHAR* GDeviceExtensions[] =
{
	//	VK_KHR_SURFACE_EXTENSION_NAME,			// Not supported, even if it's reported as a valid extension... (SDK/driver bug?)
#if PLATFORM_ANDROID
	VK_KHR_SURFACE_EXTENSION_NAME,
	VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#else
	//	VK_KHR_WIN32_SURFACE_EXTENSION_NAME,	// Not supported, even if it's reported as a valid extension... (SDK/driver bug?)
#endif
	VK_KHR_SWAPCHAIN_EXTENSION_NAME,

	//"VK_KHX_device_group",
#if SUPPORTS_MAINTENANCE_LAYER
	VK_KHR_MAINTENANCE1_EXTENSION_NAME,
#endif
	VK_KHR_SAMPLER_MIRROR_CLAMP_TO_EDGE_EXTENSION_NAME,
	nullptr
};

struct FLayerExtension
{
	FLayerExtension ()
	{
		memset (&LayerProps, 0, sizeof (LayerProps));
	}

	VkLayerProperties LayerProps;
	std::vector<VkExtensionProperties> ExtensionProps;
};


static inline void GetDeviceLayerExtensions (VkPhysicalDevice Device, const loo::ANSICHAR* LayerName, FLayerExtension& OutLayer)
{
	VkResult Result;
	do
	{
		loo::uint32 Count = 0;
		Result = vkEnumerateDeviceExtensionProperties (Device, LayerName, &Count, nullptr);
		assert (Result >= VK_SUCCESS);

		if (Count > 0)
		{
			OutLayer.ExtensionProps.resize (Count);
			Result = vkEnumerateDeviceExtensionProperties (Device, LayerName, &Count, OutLayer.ExtensionProps.data ());
			assert (Result >= VK_SUCCESS);
		}
	} while (Result == VK_INCOMPLETE);
}



void loo::rhi::VulkanDevice::GetDeviceExtensions (std::vector<const loo::ANSICHAR*>& OutDeviceExtensions, std::vector<const loo::ANSICHAR*>& OutDeviceLayers, bool& bOutDebugMarkers)
{
	bOutDebugMarkers = false;

	// Setup device layer properties
	std::vector<VkLayerProperties> LayerProperties;
	{
		uint32 Count = 0;
		VERIFYVULKANRESULT (vkEnumerateDeviceLayerProperties (Gpu, &Count, nullptr));
		LayerProperties.resize (Count);
		VERIFYVULKANRESULT (vkEnumerateDeviceLayerProperties (Gpu, &Count, (VkLayerProperties*)LayerProperties.data ()));
		assert (Count == LayerProperties.size ());
	}

	for (size_t Index = 0; Index < LayerProperties.size (); ++Index)
	{
		utils::slog.i << "VULKAN INFO:" << "- Found Device Layer " << LayerProperties[Index].layerName << utils::io::endl;
	}

#if VULKAN_HAS_DEBUGGING_ENABLED
	bool bRenderDocFound = false;
#if VULKAN_ENABLE_DRAW_MARKERS
	bool bDebugExtMarkerFound = false;
	for (size_t Index = 0; Index < LayerProperties.size (); ++Index)
	{
		if (0 == strcmp (LayerProperties[Index].layerName, RENDERDOC_LAYER_NAME))
		{
			bRenderDocFound = true;
			break;
		}
		else if (0 == strcmp (LayerProperties[Index].layerName, VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
		{
			bDebugExtMarkerFound = true;
			break;
		}
	}
#endif

	// Verify that all required device layers are available
	// ARRAY_COUNT is unnecessary, but MSVC analyzer doesn't seem to be happy with just a null check
	for (uint32 LayerIndex = 0; LayerIndex < ARRAY_COUNT (GRequiredLayersDevice) && GRequiredLayersDevice[LayerIndex] != nullptr; ++LayerIndex)
	{
		const ANSICHAR* CurrValidationLayer = GRequiredLayersDevice[LayerIndex];
		if (CurrValidationLayer)
		{
			bool bValidationFound = false;
			for (size_t Index = 0; Index < LayerProperties.size (); ++Index)
			{
				if (0 == strcmp (LayerProperties[Index].layerName, CurrValidationLayer))
				{
					bValidationFound = true;
					OutDeviceLayers.push_back (CurrValidationLayer);
					break;
				}
			}

			if (!bValidationFound)
			{
				utils::slog.w << "VULKAN WARN:" << "Unable to find Vulkan required device layer " << CurrValidationLayer << utils::io::endl;
			}
		}
	}

	// Verify that all requested debugging device-layers are available. Skip validation layers under RenderDoc
	if (!bRenderDocFound)
	{
		for (uint32 LayerIndex = 0; GValidationLayersDevice[LayerIndex] != nullptr; ++LayerIndex)
		{
			bool bValidationFound = false;
			const ANSICHAR* CurrValidationLayer = GValidationLayersDevice[LayerIndex];
			for (size_t Index = 0; Index < LayerProperties.size (); ++Index)
			{
				if (0 == strcmp (LayerProperties[Index].layerName, CurrValidationLayer))
				{
					bValidationFound = true;
					OutDeviceLayers.push_back (CurrValidationLayer);
					break;
				}
			}

			if (!bValidationFound)
			{
				utils::slog.w << "VULKAN WARN:" << "Unable to find Vulkan device validation layer " << CurrValidationLayer << utils::io::endl;
			}
		}
	}
#endif	// VULKAN_HAS_DEBUGGING_ENABLED

	FLayerExtension Extensions;
	memset (&Extensions.LayerProps,0,sizeof(Extensions.LayerProps));
	GetDeviceLayerExtensions (Gpu, nullptr, Extensions);

	for (size_t Index = 0; Index < Extensions.ExtensionProps.size (); ++Index)
	{
		utils::slog.i << "VULKAN INFO:" << "- Found Device Extension " << Extensions.ExtensionProps[Index].extensionName << utils::io::endl;
	}

	
	// ARRAY_COUNT is unnecessary, but MSVC analyzer doesn't seem to be happy with just a null check
	for (uint32 Index = 0; Index < ARRAY_COUNT (GDeviceExtensions) && GDeviceExtensions[Index] != nullptr; ++Index)
	{
		for (size_t i = 0; i < Extensions.ExtensionProps.size (); i++)
		{
			if (0 == strcmp (GDeviceExtensions[Index], Extensions.ExtensionProps[i].extensionName))
			{
				OutDeviceExtensions.push_back (GDeviceExtensions[Index]);
				break;
			}
		}
	}

#if VULKAN_HAS_DEBUGGING_ENABLED
#if VULKAN_ENABLE_DRAW_MARKERS
	{
		for (size_t i = 0; i < Extensions.ExtensionProps.size (); i++)
		{
			if (0 == strcmp (Extensions.ExtensionProps[i].extensionName, VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
			{
				OutDeviceExtensions.push_back (VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
				bOutDebugMarkers = true;
				break;
			}
		}
	}
#endif
#endif
	if (OutDeviceExtensions.size () > 0)
	{
		utils::slog.i << "VULKAN INFO:" << "Using device extensions" << utils::io::endl;
		for (const ANSICHAR* Extension : OutDeviceExtensions)
		{
			utils::slog.i << "*" << Extension << utils::io::endl;
		}
	}

	if (OutDeviceLayers.size () > 0)
	{
		utils::slog.i << "VULKAN INFO:" << "Using device layers" << utils::io::endl;
		for (const ANSICHAR* Layer : OutDeviceLayers)
		{
			utils::slog.i << "* " << Layer <<  utils::io::endl;
		}
	}
}


void loo::rhi::VulkanDevice::ParseOptionalDeviceExtensions (const std::vector<const loo::ANSICHAR *>& DeviceExtensions)
{
	//FMemory::Memzero (OptionalDeviceExtensions);

	auto HasExtension = [&DeviceExtensions](const ANSICHAR* InName) -> bool
	{
		for (auto it = DeviceExtensions.begin (); it != DeviceExtensions.end (); ++it)
		{
			if (0 == strcmp (*it, InName))
			{
				return true;
			}
		}
		return false;
	};
#if SUPPORTS_MAINTENANCE_LAYER
	OptionalDeviceExtensions.HasKHRMaintenance1 = HasExtension (VK_KHR_MAINTENANCE1_EXTENSION_NAME);
#endif
	//OptionalDeviceExtensions.HasMirrorClampToEdge = HasExtension (VK_KHR_SAMPLER_MIRROR_CLAMP_TO_EDGE_EXTENSION_NAME);


#if !defined(LOO_PLATFORM_ANDROID)
	// Verify the assumption on FVulkanSamplerState::FVulkanSamplerState()!
	//assert (OptionalDeviceExtensions.HasMirrorClampToEdge != 0);
#endif
}
