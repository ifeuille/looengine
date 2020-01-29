#ifndef LOO_VULKANRHI_VULKANVIEWPORT_H
#define LOO_VULKANRHI_VULKANVIEWPORT_H
#include "global/global.h"
#include "global/template/refcounting.h"
#include "rhi/resources.h"
#include "vulkanrhi/vulkanresource.h"

namespace loo
{
	namespace rhi
	{
		class VulkanSwapChain;
		class VulkanGraphicDevice;
		class VulkanQueue;
		class VulkanSemaphore;
		class VulkanViewport:public rhi::RHIViewport,rhi::DeviceChild
		{
		public:
			enum { NUM_BUFFERS = 3 };
			VulkanViewport(VulkanGraphicDevice* InGraphicDevice,
				VulkanDevice* InVkDevice, 
				void* InWindowHandle, 
				uint32 InSizeX, uint32 InSizeY,
				bool bInIsFullscreen, 
				EPixelFormat InPreferredPixelFormat);
			virtual ~VulkanViewport ();

			VulkanTexture2D* GetBackBuffer (RHICommandList& RHICmdList);

			void WaitForFrameEventCompletion ();

			//#todo-rco
			void IssueFrameEvent () {}



		private:
			VkImage BackBufferImages[NUM_BUFFERS];
			VulkanSemaphore* RenderingDoneSemaphores[NUM_BUFFERS];
			VulkanTextureView TextureViews[NUM_BUFFERS];

			// 'Dummy' back buffer
			loo::global::TRefCountPtr<VulkanBackBuffer> RenderingBackBuffer;
			loo::global::TRefCountPtr<VulkanBackBuffer> RHIBackBuffer;

			VulkanGraphicDevice* RHI;
			uint32 SizeX;
			uint32 SizeY;
			bool bIsFullscreen;
			EPixelFormat PixelFormat;
			int32 AcquiredImageIndex;
			VulkanSwapChain* SwapChain;
			void* WindowHandle;
			uint32 PresentCount;

			// Just a pointer, not owned by this class
			VulkanSemaphore* AcquiredSemaphore;

			CustomPresentRHIRef CustomPresent;

			void CreateSwapchain ();
			void AcquireBackBuffer (RHICommandListBase& CmdList, VulkanBackBuffer* NewBackBuffer);

			void RecreateSwapchain (void* NewNativeWindow, bool bForce = false);
			void Resize (uint32 InSizeX, uint32 InSizeY, bool bIsFullscreen);

			static int32 DoAcquireImageIndex (VulkanViewport* Viewport);
			bool DoCheckedSwapChainJob (std::function<int32 (VulkanViewport*)> SwapChainJob);


			friend class VulkanGraphicDevice;
			//friend class FVulkanCommandListContext;
			//friend struct FRHICommandAcquireBackBuffer;

		};
	}
}

#endif