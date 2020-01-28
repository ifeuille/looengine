#include "vulkanrhi/vulkanrhiprivate.h"
#include "vulkanrhi/vulkandevice.h"
#include "vulkanrhi/vulkanqueue.h"
#include "vulkanrhi/vulkansemaphore.h"
#include "vulkanrhi/vulkanswapchain.h"

loo::rhi::VulkanSwapchain::VulkanSwapchain (
	VkInstance InInstance, VulkanDevice & InDevice,
	void * WindowHandle, EPixelFormat & Informat, 
	uint32 Width, uint32 Height, uint32 * InOutDesiredNumBackBuffers, std::vector<VkImage>& OutImage)
{
}

void loo::rhi::VulkanSwapchain::Desroy ()
{
}

loo::rhi::VulkanSwapchain::EStatus loo::rhi::VulkanSwapchain::Present (VulkanQueue * GfxQueue, VulkanQueue * PresentQueue, VulkanSemaphore * BackBufferRenderingDoneSemaphore)
{
	return EStatus ();
}

loo::int32 loo::rhi::VulkanSwapchain::AcquireImageIndex (VulkanSemaphore ** OutSemaphore)
{
	return int32 ();
}
