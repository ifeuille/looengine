#ifndef LOO_RHI_INSTANCE_H
#define LOO_RHI_INSTANCE_H
#include "rhi/dllexporter.h"
#include "global/global.h"
#include "rhi/elementformat.h"
#include "rhi/createinfo.h"
#include "global/extstd/noncopyable.h"
#include "rhi/physicaldevice.h"

namespace loo
{
	namespace rhi
	{
		class RHI_EXPORT RHIInstance:loo::noncopyable
		{
		public:
			RHIInstance (LOOInstanceCreateInfo ci, RHIInstance* InInstance) {}
			virtual ~RHIInstance () {}

			virtual void EnumeratePhysicalDevices (int& num, RHIPhysicalDevice* physicalDevices) { num = 0; }

		private:

		};
	}
}
#endif