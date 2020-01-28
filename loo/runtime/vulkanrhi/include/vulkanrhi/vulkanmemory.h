#ifndef LOO_RHI_VULKAN_VULKANMEMORY_H
#define LOO_RHI_VULKAN_VULKANMEMORY_H
#pragma once
#include "vulkanrhi/dllexporter.h"
#include "global/global.h"
#include "global/utils/threadsafecounter.h"
#include "rhi/rhi.h"

namespace loo
{
	namespace rhi
	{
		

		//
		class DeviceChild
		{
		public:
			DeviceChild ();
			virtual ~DeviceChild ();

		private:
			loo::global::ThreadSafeCounter<int> RefsCounter;
		};
	}
}

#endif