#include "vkfg/vulkan/framework/vulkansurface.h"
#include "global/extstd/cast.h"
#if defined(LOO_PLATFORM_WINDOWS) && !defined(VK_USE_PLATFORM_WIN32_KHR)
#include "global/utils/win32/windowsheader.h"
#define VK_USE_PLATFORM_WIN32_KHR	1
#include <vulkan/vulkan_win32.h>
#elif defined(LOO_PLATFORM_ANDROID)
#define VK_USE_PLATFORM_ANDROID_KHR	1
#include <vulkan/vulkan_android.h>
//#include <android_native_app_glue.h>
#endif

namespace loo
{
	namespace vkfg
	{		
		/*
		=================================================
			GetRequiredExtensions
		=================================================
		*/
		Array<const char*>  VulkanSurfaceUtil::GetRequiredExtensions ()
		{
			Array<const char*>	ext;

#		if defined(VK_USE_PLATFORM_ANDROID_KHR) and VK_USE_PLATFORM_ANDROID_KHR
			ext.push_back (VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_IOS_MVK) and VK_USE_PLATFORM_IOS_MVK
			ext.push_back (VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_MACOS_MVK) and VK_USE_PLATFORM_MACOS_MVK
			ext.push_back (VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_WIN32_KHR) and VK_USE_PLATFORM_WIN32_KHR
			ext.push_back (VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_MIR_KHR) and VK_USE_PLATFORM_MIR_KHR
			ext.push_back (VK_KHR_MIR_SURFACE_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_XCB_KHR) and VK_USE_PLATFORM_XCB_KHR
			ext.push_back (VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_XLIB_KHR) and VK_USE_PLATFORM_XLIB_KHR
			ext.push_back (VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) and VK_USE_PLATFORM_XLIB_XRANDR_EXT
			ext.push_back (VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME);
#		endif

#		if defined(VK_USE_PLATFORM_WAYLAND_KHR) and VK_USE_PLATFORM_WAYLAND_KHR
			ext.push_back (VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#		endif

			return ext;
		}

# if defined(VK_USE_PLATFORM_WIN32_KHR) and VK_USE_PLATFORM_WIN32_KHR	
		/*
		=================================================
			CreateWin32Surface
		=================================================
		*/
		VkSurfaceKHR  VulkanSurfaceUtil::CreateWin32Surface (VkInstance instance, void* hinstance, void* hwnd)
		{
			CHECK_ERR (instance and hinstance and hwnd);

			VkSurfaceKHR					surface;
			VkWin32SurfaceCreateInfoKHR		surface_info = {};

			surface_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			surface_info.hinstance = HINSTANCE (hinstance);
			surface_info.hwnd = HWND (hwnd);

			PFN_vkCreateWin32SurfaceKHR  fpCreateWin32SurfaceKHR = BitCast<PFN_vkCreateWin32SurfaceKHR> (vkGetInstanceProcAddr (instance, "vkCreateWin32SurfaceKHR"));
			CHECK_ERR (fpCreateWin32SurfaceKHR);

			VK_CHECK (fpCreateWin32SurfaceKHR (instance, &surface_info, null, OUT &surface));
			return surface;
		}
# endif
# if defined(LOO_PLATFORM_ANDROID)
		//defined(VK_USE_PLATFORM_ANDROID_KHR) and VK_USE_PLATFORM_ANDROID_KHR
		/*
		=================================================
			CreateAndroidSurface
		=================================================
		*/
		VkSurfaceKHR  VulkanSurfaceUtil::CreateAndroidSurface (VkInstance instance, void* window)
		{
			CHECK_ERR (instance and window);

			VkSurfaceKHR					surface;
			VkAndroidSurfaceCreateInfoKHR	surface_info = {};

			surface_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
			surface_info.flags = 0;
			surface_info.window = (ANativeWindow*) (window);

			PFN_vkCreateAndroidSurfaceKHR  fpCreateAndroidSurfaceKHR = BitCast<PFN_vkCreateAndroidSurfaceKHR> (vkGetInstanceProcAddr (instance, "vkCreateAndroidSurfaceKHR"));
			CHECK_ERR (fpCreateAndroidSurfaceKHR);

			VK_CHECK (fpCreateAndroidSurfaceKHR (instance, &surface_info, null, OUT &surface));
			return surface;
		}
# endif


	}
}
