#ifndef LOO_RHI_VULKAN_VULKANGRAPHICDEVICE_H
#define LOO_RHI_VULKAN_VULKANGRAPHICDEVICE_H
#include "vulkanrhi/dllexporter.h"
#include "global/global.h"
#include "rhi/graphicdevice.h"

namespace loo
{
	namespace rhi
	{
		struct VulkanContext;
		class VulkanDevice;
		class VULKANRHI_EXPORT VulkanGraphicDevice : public GraphicDevice
		{
		public:
			VulkanGraphicDevice ();
			virtual ~VulkanGraphicDevice ();
			virtual void Init () override;
			virtual void Suspend () override;
			virtual void Resume () override;
			virtual void Shutdown () override;
			virtual const char* GetName () { return "vulkan"; }

			void InitInstance ();

		private:
			VulkanContext* vulkanContext;
			VulkanDevice* vulkanDevice;
			std::vector< VulkanDevice*> devices;
		};
	}
}

namespace loo
{
	namespace rhi
	{

		class VULKANRHI_EXPORT VulkanVideoDeviceModule : public VideoDeviceModule
		{
		public:

			/** Checks whether the RHI is supported by the current system. */
			virtual bool IsSupported () override;

			/** Creates a new instance of the dynamic RHI implemented by the module. */
			virtual void CreateVideoDevice (std::unique_ptr <GraphicDevice>& ptr/*, ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num*/)override;
		};
	}
}


#endif