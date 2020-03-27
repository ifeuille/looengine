#ifndef LOO_RHI_PHYSICALDEVICE_H
#define LOO_RHI_PHYSICALDEVICE_H
#include "rhi/dllexporter.h"
#include "global/global.h"
#include "rhi/elementformat.h"
#include "rhi/createinfo.h"
#include "global/extstd/noncopyable.h"

namespace loo
{
	namespace rhi
	{
		class GraphicDevice;
		class RHI_EXPORT RHIPhysicalDevice
		{
		public:
			RHIPhysicalDevice () {}
			virtual ~RHIPhysicalDevice () {}

			virtual LOOPhysicalDeviceProperties GetPhysicalDeviceProperties () 
			{
				return deviceProperties;
			}
			virtual LOOPhysicalDeviceSparseProperties GetPhysicalDeviceSparseProperties ()
			{
				return deviceSparseProperties;
			}
			virtual LOOQueueFamilyProperties GetPhysicalDeviceQueueFamilyProperties ()
			{
				return queueFamilyProperties;
			}

			virtual GraphicDevice* CreateDeivce (LOODeviceCreateInfo ci)
			{
				return nullptr;
			}
		private:
			LOOPhysicalDeviceProperties deviceProperties;
			LOOPhysicalDeviceSparseProperties deviceSparseProperties;
			LOOQueueFamilyProperties queueFamilyProperties;
		};
	}
}
#endif