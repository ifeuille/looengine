#pragma once
#include "global/math/vec.h"
#include "global/extstd/fixedarray.h"
#include "global/extstd/ntstringview.h"
#include "vulkanloader/vulkanloader.h"
#include "vulkanloader/vulkancheckerror.h"


namespace loo
{
	namespace vkfg
	{
		//
		// Vulkan Surface Helper
		//
		class VulkanSurfaceUtil final
		{
		public:
			VulkanSurfaceUtil () = delete;
			~VulkanSurfaceUtil () = delete;

			ND_ static Array<const char*>	GetRequiredExtensions ();

			// Windows
#	if defined(LOO_PLATFORM_WINDOWS)
			ND_ static VkSurfaceKHR			CreateWin32Surface (VkInstance instance, void* hinstance, void* hwnd);
#	endif

			// Android
#	if defined(LOO_PLATFORM_ANDROID)
			ND_ static VkSurfaceKHR			CreateAndroidSurface (VkInstance instance, void* window);
#	endif

		};


	}
}