#ifndef LOO_RHI_RHI_H
#define LOO_RHI_RHI_H
#include "rhi/dllexporter.h"
#include "global/global.h"
#include "rhi/elementformat.h"
#include "rhi/graphicdevice.h"

namespace loo
{
	namespace rhi
	{
		//globals
		extern RHI_EXPORT bool GIsRHIInitialized;

		struct PhysicalDeviceProperties
		{
			uint32 vendorID;
			std::string deviceName;
			uint32 deviceID;
			std::string driverVersion;
			std::string driverInternalVersion;
			LooPhysicalDeviceType physicalDeviceTpye;
			uint8 pipelineCacheUUID[LOO_UUID_SIZE];

			LOOPhysicalDeviceFeatures physicalDeviceFeatures;
			LOOPhysicalDeviceLimits physicalDeviceLimits;

			PhysicalDeviceProperties ()
				: vendorID (0)
				, deviceName ("unknown")
				, driverVersion ("0.0.0")
				, driverInternalVersion ("0.0.0")
				, physicalDeviceFeatures ()
				, physicalDeviceLimits ()
				, deviceID (0)
				, physicalDeviceTpye (LooPhysicalDeviceType::OTHER)
			{
			}
		};

		extern RHI_EXPORT PhysicalDeviceProperties GPhysicalDeviceProperties;
	}
}

#endif