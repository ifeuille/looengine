#include "vulkanrhi/vulkanrhiprivate.h"
#include "vulkanrhi/vulkangraphicdevice.h"
#include "modulemanager/moduleinterface.h"
#include "global/utlis.h"
#include "vulkanrhi/instance/instance.h"
#include "vulkanrhi/instance/device.h"
#include "ifvk/IfVK.h"
#include "global/utils/panic.h"
#include "vulkanrhi/vulkandevice.h"

using namespace utils;

#if !defined(NDEBUG) && !defined(__APPLE__)
#define ENABLE_VALIDATION 1
#define ENABLE_RENDERDOC 1
#else
#define ENABLE_VALIDATION 0
#define ENABLE_RENDERDOC 0
#endif

#if ENABLE_VALIDATION
namespace {

	VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallback (VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location,
		int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
	{
		LOO_UNUSED (pUserData);
		LOO_UNUSED (messageCode);
		LOO_UNUSED (location);
		LOO_UNUSED (object);
		LOO_UNUSED (objectType);

		if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
		{
			utils::slog.e << "VULKAN ERROR: (" << pLayerPrefix << ") " << pMessage << utils::io::endl;
		}
		else
		{
			utils::slog.w << "VULKAN WARNING: (" << pLayerPrefix << ") "
				<< pMessage << utils::io::endl;
		}
		// Return TRUE here if an abort is desired.
		return VK_FALSE;
	}

}
#endif

loo::rhi::VulkanGraphicDevice::VulkanGraphicDevice ()
{
	vulkanContext = new VulkanContext ();
}

loo::rhi::VulkanGraphicDevice::~VulkanGraphicDevice ()
{

}

void loo::rhi::VulkanGraphicDevice::Init ()
{
	// Load Vulkan entry points.
	ASSERT_POSTCONDITION (ifvk::initialize (), "IfVK is unable to load entry points.");
	VkInstanceCreateInfo instanceCreateInfo = {};
	ZeroVulkanStruct (instanceCreateInfo, VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO);
#if ENABLE_VALIDATION
	static utils::StaticString DESIRED_LAYERS[] =
	{
#if defined(LOO_PLATFORM_ANDROID)
		// TODO: use VK_LAYER_KHRONOS_validation instead of these layers after it becomes available
		"VK_LAYER_GOOGLE_threading",
		"VK_LAYER_LUNARG_parameter_validation",
		"VK_LAYER_LUNARG_object_tracker",
		"VK_LAYER_LUNARG_core_validation",
		"VK_LAYER_GOOGLE_unique_objects"
#else
		"VK_LAYER_LUNARG_standard_validation",
#endif
#if defined(ENABLE_RENDERDOC)
		"VK_LAYER_RENDERDOC_Capture",
#endif
	};

	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties (&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers (layerCount);
	vkEnumerateInstanceLayerProperties (&layerCount, availableLayers.data ());
	std::vector<const char*> enabledLayers;
	for (const auto& desired : DESIRED_LAYERS)
	{
		for (const VkLayerProperties& layer : availableLayers)
		{
			const utils::CString availableLayer (layer.layerName);
			if (availableLayer == desired)
			{
				enabledLayers.push_back (desired.c_str ());
			}
		}
	}

	if (!enabledLayers.empty ())
	{
		instanceCreateInfo.enabledLayerCount = (uint32_t)enabledLayers.size ();
		instanceCreateInfo.ppEnabledLayerNames = enabledLayers.data ();
	}
	else
	{
#if defined(LOO_PLATFORM_ANDROID)
		utils::slog.d << "Validation layers are not available; did you set jniLibs in your "
			<< "gradle file?" << utils::io::endl;
#else
		utils::slog.d << "Validation layer not available; did you install the Vulkan SDK?\n"
			<< "Please ensure that VK_LAYER_PATH is set correctly." << utils::io::endl;
#endif
	}
#endif
	VkApplicationInfo appInfo = {};
	ZeroVulkanStruct (appInfo, VK_STRUCTURE_TYPE_APPLICATION_INFO);
	appInfo.applicationVersion = LOO_VERSION;
	appInfo.engineVersion = LOO_VERSION;
	appInfo.pEngineName = LOO_ENGINE_NAME;
	appInfo.pApplicationName = LOO_ENGINE_NAME;
	appInfo.apiVersion = VK_API_VERSION_1_0;
	instanceCreateInfo.pApplicationInfo = &appInfo;

	static const char* requestedExtensions[] =
	{
	"VK_KHR_surface",
#if defined(LOO_PLATFORM_WINDOWS)
	"VK_KHR_win32_surface",
#elif defined(LOO_PLATFORM_LINUX)
	"VK_KHR_xlib_surface",
#elif defined(LOO_PLATFORM_ANDROID)
	VK_KHR_android_surface,
#elif defined(LOO_PLATFORM_IOS)
	"VK_MVK_ios_surface",
#elif defined(LOO_PLATFORM_DARWIN)
	"VK_MVK_macos_surface",
#endif
#if !defined(NDEBUG) && !defined(LOO_PLATFORM_IOS) && !defined(LOO_PLATFORM_DARWIN)
	"VK_EXT_debug_report",
#endif
	};

	instanceCreateInfo.enabledExtensionCount = sizeof (requestedExtensions) / sizeof (requestedExtensions[0]);
	instanceCreateInfo.ppEnabledExtensionNames = requestedExtensions;
	VkResult result = vkCreateInstance (&instanceCreateInfo, VKALLOC, &vulkanContext->Instance);
	ASSERT_POSTCONDITION (result == VK_SUCCESS, "Unable to create Vulkan instance.");
	ifvk::bindInstance (vulkanContext->Instance);
#if ENABLE_VALIDATION
	if (vkCreateDebugReportCallbackEXT) {
		static VkDebugReportCallbackCreateInfoEXT cbinfo = {
			VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
			nullptr,
			VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT,
			debugReportCallback,
			nullptr
		};
		result = vkCreateDebugReportCallbackEXT (vulkanContext->Instance, &cbinfo, VKALLOC, &vulkanContext->mDebugCallback);
		ASSERT_POSTCONDITION (result == VK_SUCCESS, "Unable to create Vulkan debug callback.");
	}
#endif
	uint32_t GpuCount = 0;
	vkEnumeratePhysicalDevices (vulkanContext->Instance, &GpuCount, nullptr);
	ASSERT_MSG (GpuCount >= 1, "vkEnumeratePhysicalDevices = 0");
	std::vector< VkPhysicalDevice> physicalDevices;
	physicalDevices.resize (GpuCount);
	vkEnumeratePhysicalDevices (vulkanContext->Instance, &GpuCount, physicalDevices.data());
	VulkanDevice* DiscreteDevice = nullptr;
	uint32 DiscreteDeviceIndex = 0;
	utils::slog.i << "VULKAN INFO:"<<"Found "<< GpuCount<<" devices" << utils::io::endl;

	for (uint32 i = 0; i < GpuCount; ++i)
	{
		VulkanDevice* newDevice = new VulkanDevice (physicalDevices[i]);
		devices.push_back (newDevice);
		bool bIsDiscrete = newDevice->QueryGPU (i);

		if (!DiscreteDevice && bIsDiscrete)
		{
			DiscreteDevice = newDevice;
			DiscreteDeviceIndex = i;
		}
		uint32 DeviceIndex;

		if (DiscreteDevice)
		{
			vulkanDevice = DiscreteDevice;
			DeviceIndex = DiscreteDeviceIndex;
		}
		else
		{
			vulkanDevice = devices[0];
			DeviceIndex = 0;
		}

		ASSERT_MSG (vulkanDevice,"Can't find gpu supported vulkan");
		vulkanDevice->InitGPU (DeviceIndex);
	}

	//features check..




}

void loo::rhi::VulkanGraphicDevice::Suspend ()
{
}

void loo::rhi::VulkanGraphicDevice::Resume ()
{
}

void loo::rhi::VulkanGraphicDevice::Shutdown ()
{
}

void loo::rhi::VulkanGraphicDevice::InitInstance ()
{
}


bool loo::rhi::VulkanVideoDeviceModule::IsSupported ()
{
	return true;
}

void loo::rhi::VulkanVideoDeviceModule::CreateVideoDevice (std::unique_ptr<GraphicDevice>& ptr)
{
	ptr = loo::global::MakeUniquePtr<loo::rhi::VulkanGraphicDevice> ();
}

REGISTER_MODULE (loo::rhi::VulkanVideoDeviceModule, VULKANRHI_EXPORT);