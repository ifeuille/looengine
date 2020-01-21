#ifndef LOO_RHI_GRAPHICDEVICE_H
#define LOO_RHI_GRAPHICDEVICE_H
#include "rhi/dllexporter.h"
#include "global/global.h"
#include "elementformat.h"
#include "modulemanager/moduleinterface.h"

namespace loo
{
	namespace rhi
	{
		class RHI_EXPORT GraphicDevice
		{
		public:
			virtual void Init () = 0;
			virtual void Suspend () = 0;
			virtual void Resume () = 0;
			virtual void Shutdown () = 0;
			virtual const char* GetName () { return "null"; }
		protected:

		public:
			const LOOPhysicalDeviceLimits GetPhysicalDeviceLimits ()const { return physicalDeviceLimits; }

		private:
			LOOPhysicalDeviceLimits physicalDeviceLimits;
		};

		/** A global pointer to the dynamically bound RHI implementation. */
		extern RHI_EXPORT GraphicDevice* GGraphicDevice;
	}
}

namespace loo
{
	namespace rhi
	{
		// interface for video device create
		class RHI_EXPORT VideoDeviceModule : public loo::IModuleInterface
		{
		public:

			/** Checks whether the RHI is supported by the current system. */
			virtual bool IsSupported () = 0;

			/** Creates a new instance of the dynamic RHI implemented by the module. */
			virtual void CreateVideoDevice (std::unique_ptr <GraphicDevice>& ptr/*, ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num*/) = 0;
		};
	}
}

#endif