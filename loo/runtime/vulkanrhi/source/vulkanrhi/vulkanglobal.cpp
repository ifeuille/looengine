#include "vulkanrhi/vulkanrhiprivate.h"
#include "vulkanrhi/vulkanglobal.h"
#include "global/utils/log.h"

void VerifyVulkanResult (VkResult Result, const loo::ANSICHAR* VkFunction, const loo::ANSICHAR* Filename, loo::uint32 Line)
{
	std::wstring ErrorString;
	switch (Result)
	{
#define VKERRORCASE(x)	case x: ErrorString = TEXT(#x)
		VKERRORCASE (VK_NOT_READY); break;
		VKERRORCASE (VK_TIMEOUT); break;
		VKERRORCASE (VK_EVENT_SET); break;
		VKERRORCASE (VK_EVENT_RESET); break;
		VKERRORCASE (VK_INCOMPLETE); break;
		VKERRORCASE (VK_ERROR_OUT_OF_HOST_MEMORY); break;
		VKERRORCASE (VK_ERROR_OUT_OF_DEVICE_MEMORY); break;
		VKERRORCASE (VK_ERROR_INITIALIZATION_FAILED); break;
		VKERRORCASE (VK_ERROR_DEVICE_LOST);/* GIsGPUCrashed = true;*/ break;
		VKERRORCASE (VK_ERROR_MEMORY_MAP_FAILED); break;
		VKERRORCASE (VK_ERROR_LAYER_NOT_PRESENT); break;
		VKERRORCASE (VK_ERROR_EXTENSION_NOT_PRESENT); break;
		VKERRORCASE (VK_ERROR_FEATURE_NOT_PRESENT); break;
		VKERRORCASE (VK_ERROR_INCOMPATIBLE_DRIVER); break;
		VKERRORCASE (VK_ERROR_TOO_MANY_OBJECTS); break;
		VKERRORCASE (VK_ERROR_FORMAT_NOT_SUPPORTED); break;
		VKERRORCASE (VK_ERROR_SURFACE_LOST_KHR); break;
		VKERRORCASE (VK_ERROR_NATIVE_WINDOW_IN_USE_KHR); break;
		VKERRORCASE (VK_SUBOPTIMAL_KHR); break;
		VKERRORCASE (VK_ERROR_OUT_OF_DATE_KHR); break;
		VKERRORCASE (VK_ERROR_INCOMPATIBLE_DISPLAY_KHR); break;
		VKERRORCASE (VK_ERROR_VALIDATION_FAILED_EXT); break;
#undef VKERRORCASE
	default:
		break;
	}
	utils::slog.e << "VULKAN ERROR:" << VkFunction << " failed, VkResult=%d\n at %s:%u \n with error %s"
		<< VkFunction << (loo::int32)Result << (Filename) << Line << ErrorString.c_str () << utils::io::endl;
}
