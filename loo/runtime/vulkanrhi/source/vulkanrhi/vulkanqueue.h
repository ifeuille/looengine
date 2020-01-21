#ifndef LOO_RHI_VULKANQUEUE_H
#define LOO_RHI_VULKANQUEUE_H
#include "global/global.h"

namespace loo
{
	namespace rhi
	{
		class VulkanDevice;

		class VulkanQueue
		{
		public:
			VulkanQueue (VulkanDevice* InDevice, uint32 InFamilyIndex, uint32 InQueueIndex);

			~VulkanQueue ();

			inline uint32 GetFamilyIndex () const
			{
				return FamilyIndex;
			}
			//void Submit(FVulkanCmdBuffer* CmdBuffer, FVulkanSemaphore* WaitSemaphore, VkPipelineStageFlags WaitStageFlags, FVulkanSemaphore* SignalSemaphore);
			inline VkQueue GetHandle () const
			{
				return Queue;
			}

			/*void GetLastSubmittedInfo (FVulkanCmdBuffer*& OutCmdBuffer, uint64& OutFenceCounter) const
			{
				FScopeLock ScopeLock (&CS);
				OutCmdBuffer = LastSubmittedCmdBuffer;
				OutFenceCounter = LastSubmittedCmdBufferFenceCounter;
			}

			inline uint64 GetSubmitCount () const
			{
				return SubmitCounter;
			}*/

		private:
			VkQueue Queue;
			uint32 FamilyIndex;
			uint32 QueueIndex;
			VulkanDevice* Device;
			/*mutable FCriticalSection CS;
			FVulkanCmdBuffer* LastSubmittedCmdBuffer;
			uint64 LastSubmittedCmdBufferFenceCounter;
			uint64 SubmitCounter;

			void UpdateLastSubmittedCommandBuffer (FVulkanCmdBuffer* CmdBuffer);*/

		};
	}
}

#endif