#ifndef LOO_RHI_VULKAN_VULKANGRAPHICDEVICE_H
#define LOO_RHI_VULKAN_VULKANGRAPHICDEVICE_H
#include "vulkanrhi/dllexporter.h"
#include "global/global.h"
#include "rhi/graphicdevice.h"
#include "global/template/refcounting.h"
#include "rhi/rhi.h"

namespace loo
{
	namespace rhi
	{
		struct VulkanContext;
		class VulkanDevice;
		class VulkanSwapchain;
		class VulkanViewPort;
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

			static void RecreateSwapChain (void* NewNativeWindow);

		private:
			VulkanContext* vulkanContext;
			VulkanDevice* vulkanDevice;
			std::vector< VulkanDevice*> devices;

			std::vector<VulkanViewPort*> Viewports;
			loo::global::TRefCountPtr<VulkanViewPort> DrawingViewport;


			friend class VulkanViewPort;

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