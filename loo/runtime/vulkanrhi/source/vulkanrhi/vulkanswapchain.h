#ifndef LOO_VULKANRHI_VULKANSWAPCHAIN_H
#define LOO_VULKANRHI_VULKANSWAPCHAIN_H
#include "global/global.h"

namespace loo
{
	namespace rhi
	{
		class Fence;
		class VulkanQueue;

		class VulkanSwapChain
		{
		public:
			VulkanSwapChain (VkInstance InInstance, VulkanDevice& InDevice, void* WindowHandle, EPixelFormat& Informat, uint32 Width, uint32 Height,
				uint32* InOutDesiredNumBackBuffers, std::vector<VkImage>& OutImage);
			void Desroy ();
			// Has to be negative as we use this also on other callbacks as the acquired image index
			enum class EStatus
			{
				Healthy = 0,
				OutOfDate = -1,
				SurfaceLost = -2,
			};
			EStatus Present (VulkanQueue* GfxQueue, VulkanQueue* PresentQueue, VulkanSemaphore* BackBufferRenderingDoneSemaphore);

		private:
			VkSwapchainKHR SwapChain;
			VulkanDevice& Device;

			VkSurfaceKHR Surface;

			int32 CurrentImageIndex;
			int32 SemaphoreIndex;
			uint32 NumPresentCalls;
			uint32 NumAcquireCalls;
			VkInstance Instance;
			std::vector<VulkanSemaphore*> ImageAcquiredSemaphore;
#if VULKAN_USE_IMAGE_ACQUIRE_FENCES
			std::vector<Fence*> ImageAcquiredFences;
#endif

			int32 AcquireImageIndex (VulkanSemaphore** OutSemaphore);

			friend class FVulkanViewport;
			friend class FVulkanQueue;
		};
	}
}

#endif