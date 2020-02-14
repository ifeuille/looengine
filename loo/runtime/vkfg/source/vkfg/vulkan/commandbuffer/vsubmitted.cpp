

#include "vkfg/vulkan/commandbuffer/vsubmitted.h"
#include "vkfg/vulkan/instance/vdevice.h"
#include "vkfg/vulkan/instance/vresourcemanager.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			constructor
		=================================================
		*/
		VSubmitted::VSubmitted (uint indexInPool) :
			_indexInPool{ indexInPool },
			_fence{ VK_NULL_HANDLE },
			_queueType{ Default }
		{
		}

		/*
		=================================================
			destructor
		=================================================
		*/
		VSubmitted::~VSubmitted ()
		{
			ASSERT (not _fence);
			ASSERT (_semaphores.empty ());
			ASSERT (_batches.empty ());
		}

		/*
		=================================================
			_Initialize
		=================================================
		*/
		void VSubmitted::_Initialize (const VDevice &dev, EQueueType queue, ArrayView<VCmdBatchPtr> batches, ArrayView<VkSemaphore> semaphores)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (not _fence)
			{
				VkFenceCreateInfo	info = {};
				info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				info.flags = 0;
				VK_CALL (dev.vkCreateFence (dev.GetVkDevice (), &info, null, OUT &_fence));
			}
			else
				VK_CALL (dev.vkResetFences (dev.GetVkDevice (), 1, &_fence));

			_batches = batches;
			_semaphores = semaphores;
			_queueType = queue;
		}

		/*
		=================================================
			_Release
		=================================================
		*/
		void VSubmitted::_Release (const VDevice &dev, VDebugger &debugger, const IFrameGraph::ShaderDebugCallback_t &shaderDbgCallback, INOUT Statistic_t &outStatistic)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			for (auto& sem : _semaphores) {
				dev.vkDestroySemaphore (dev.GetVkDevice (), sem, null);
			}

			_semaphores.clear ();

			for (auto& batch : _batches) {
				batch->OnComplete (debugger, shaderDbgCallback, INOUT outStatistic);
			}

			_batches.clear ();
		}

		/*
		=================================================
			_Destroy
		=================================================
		*/
		void VSubmitted::_Destroy (const VDevice &dev)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			dev.vkDestroyFence (dev.GetVkDevice (), _fence, null);
			_fence = VK_NULL_HANDLE;
		}


	}	
}