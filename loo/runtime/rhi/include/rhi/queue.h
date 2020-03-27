#ifndef LOO_RHI_QUEUE_H
#define LOO_RHI_QUEUE_H
#pragma once
#include "rhi/dllexporter.h"
#include "global/global.h"

namespace loo
{
	namespace rhi
	{
		class GraphicDevice;
		class RHICommandPool;
		class RHI_EXPORT RHIQueue
		{
		public:
			RHIQueue (GraphicDevice* InDevice, uint32 InqueueFamilyIndex, uint32 InqueueIndex)
				:graphicDevice (InDevice)
				, queueFamilyIndex(InqueueFamilyIndex)
				, queueIndex(InqueueIndex)
			{
			}

			virtual ~RHIQueue () {}

			virtual void QueueWaitIdle () {}

			virtual RHICommandPool* CreateCommandPool () { return nullptr; }

		private:
			uint32 queueFamilyIndex;
			uint32 queueIndex;

			GraphicDevice* graphicDevice;
		};
	}
}

#endif