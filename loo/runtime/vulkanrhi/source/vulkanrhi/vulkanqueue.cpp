#include "vulkanrhi/vulkanrhiprivate.h"
#include "vulkanrhi/vulkanqueue.h"
#include "vulkanrhi/VulkanDevice.h"


loo::rhi::VulkanQueue::VulkanQueue (VulkanDevice * InDevice, uint32 InFamilyIndex, uint32 InQueueIndex)
	: Queue (VK_NULL_HANDLE)
	, FamilyIndex (InFamilyIndex)
	, QueueIndex (InQueueIndex)
	, Device (InDevice)
	//, LastSubmittedCmdBuffer (nullptr)
	//, LastSubmittedCmdBufferFenceCounter (0)
	//, SubmitCounter (0)
{
	vkGetDeviceQueue (Device->GetInstanceHandle (), FamilyIndex, InQueueIndex, &Queue);
}

loo::rhi::VulkanQueue::~VulkanQueue ()
{
	ASSERT_MSG (Device,"");
}
