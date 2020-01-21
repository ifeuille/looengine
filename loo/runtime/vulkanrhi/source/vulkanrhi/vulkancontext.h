#ifndef LOO_RHI_VULKAN_CONTEXT_H
#define LOO_RHI_VULKAN_CONTEXT_H

namespace loo
{
	namespace rhi
	{
		struct VulkanContext
		{
			//std::unique_ptr<VulkanInstance> instance;
			VkInstance Instance;
			VkPhysicalDevice physicalDevice;
			VkPhysicalDeviceProperties physicalDeviceProperties;
			VkPhysicalDeviceFeatures physicalDeviceFeatures;
			VkPhysicalDeviceMemoryProperties memoryProperties;
			VkDebugReportCallbackEXT mDebugCallback = VK_NULL_HANDLE;
		};
	}
}
#endif