#include "vulkanrhi/vulkanrhiprivate.h"
#include "vulkanrhi/vulkandevice.h"
#include "vulkanrhi/vulkanqueue.h"
#include "vulkanrhi/vulkansemaphore.h"
#include "vulkanrhi/vulkanswapchain.h"

loo::rhi::VulkanSwapChain::VulkanSwapChain (
	VkInstance InInstance, VulkanDevice & InDevice,
	void * WindowHandle, EPixelFormat & Informat, 
	uint32 Width, uint32 Height, uint32 * InOutDesiredNumBackBuffers, std::vector<VkImage>& OutImage)
{
}

void loo::rhi::VulkanSwapChain::Desroy ()
{
}

loo::rhi::VulkanSwapChain::EStatus loo::rhi::VulkanSwapChain::Present (VulkanQueue * GfxQueue, VulkanQueue * PresentQueue, VulkanSemaphore * BackBufferRenderingDoneSemaphore)
{
	return EStatus ();
}

loo::int32 loo::rhi::VulkanSwapChain::AcquireImageIndex (VulkanSemaphore ** OutSemaphore)
{
	return int32 ();
}
