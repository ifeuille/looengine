#include "core/application/window.h"
#include "core/context.h"
#include "global/global.h"
#include "global/mutex.h"
#include "vkfg/vulkan/framework/vulkansurface.h"
#include "core/application/application.h"

namespace loo
{
	namespace core
	{
		Window::VulkanSurface::VulkanSurface (loo::core::Window* wnd)
			:_windows (wnd), _extensions (loo::vkfg::VulkanSurfaceUtil::GetRequiredExtensions ())
		{
		}

		VkSurfaceKHR Window::VulkanSurface::Create (VkInstance inst) const
		{
			VulkanLoader::Initialize ();//core.dll,这种结构下,每个dll需要单独load vulkan得符号
#ifdef LOO_PLATFORM_WINDOWS
			return loo::vkfg::VulkanSurfaceUtil::CreateWin32Surface (inst, GetModuleHandle (NULL), _windows->HWnd ());
#elif defined(LOO_PLATFORM_ANDROID)
			return loo::vkfg::VulkanSurfaceUtil::CreateAndroidSurface (inst, _windows->NativeWindow ());
#else
#error "Un Supported!"
#endif
		}

		void Window::UpdateDpiScale (float scale)
		{
			dpi_scale = scale;

			float const max_dpi_scale = app->Config ().graphic_settings.max_dpi_scale;
			if (max_dpi_scale > 0)
			{
				effective_dpi_scale = loo::math::Min (max_dpi_scale, dpi_scale);
			}
			else
			{
				effective_dpi_scale = dpi_scale;
			}
		}


		std::unique_ptr<loo::vkfg::IVulkanSurface> Window::GetVulkanSurface () 
		{
			return UniquePtr<loo::vkfg::IVulkanSurface> (new loo::core::Window::VulkanSurface (this));
		}
	}
}