#ifndef LOO_RHI_VULKANDEVICE_H
#define LOO_RHI_VULKANDEVICE_H
#include "vulkanrhi/dllexporter.h"
#include "global/global.h"

namespace loo
{
	namespace rhi
	{
		class VulkanQueue;
		class VulkanDevice
		{
		public:
			VulkanDevice (VkPhysicalDevice Gpu);
			~VulkanDevice ();
			bool QueryGPU (int32 DeviceIndex);
			void InitGPU (int32 DeviceIndex);
			void CreateDevice ();
			void PrepareForDestroy ();
			void Destroy ();
			void WaitUntilIdle ();

			inline VulkanQueue* GetGraphicsQueue ()
			{
				return GfxQueue;
			}

			inline VulkanQueue* GetComputeQueue ()
			{
				return ComputeQueue;
			}

			inline VulkanQueue* GetTransferQueue ()
			{
				return TransferQueue;
			}

			inline VulkanQueue* GetPresentQueue ()
			{
				return PresentQueue;
			}

			inline VkPhysicalDevice GetPhysicalHandle () const
			{
				return Gpu;
			}

			inline const VkPhysicalDeviceProperties& GetDeviceProperties () const
			{
				return GpuProps;
			}

			inline const VkPhysicalDeviceLimits& GetLimits () const
			{
				return GpuProps.limits;
			}


			inline const VkPhysicalDeviceFeatures& GetFeatures () const
			{
				return Features;
			}

			/*inline bool HasUnifiedMemory () const
			{
				return MemoryManager.HasUnifiedMemory ();
			}*/

			bool IsFormatSupported (VkFormat Format) const;

			const VkComponentMapping& GetFormatComponentMapping (EPixelFormat UEFormat) const;

			inline VkDevice GetInstanceHandle ()
			{
				ASSERT_MSG (Device != VK_NULL_HANDLE,"");
				return Device;
			}

			/*inline VkSampler GetDefaultSampler () const
			{
				return DefaultSampler->Sampler;
			}*/

			inline VkImageView GetDefaultImageView () const
			{
				return DefaultImageView;
			}

			inline const VkFormatProperties* GetFormatProperties () const
			{
				return FormatProperties;
			}

			inline VkPhysicalDeviceSparseProperties GetSparseProperties ()const {
				return GpuSparseProperties;
			}

		private:
			void MapFormatSupport (EPixelFormat UEFormat, VkFormat VulkanFormat);
			void MapFormatSupport (EPixelFormat UEFormat, VkFormat VulkanFormat, int32 BlockBytes);
			void SetComponentMapping (EPixelFormat UEFormat, VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a);

		private:
			VkPhysicalDevice Gpu;
			VkPhysicalDeviceProperties GpuProps;
			VkPhysicalDeviceSparseProperties GpuSparseProperties;

#if VULKAN_ENABLE_DESKTOP_HMD_SUPPORT
			VkPhysicalDeviceIDPropertiesKHR GpuIdProps;
#endif
			VkPhysicalDeviceFeatures Features;

			VkDevice Device;


			/*VulkanRHI::FDeviceMemoryManager MemoryManager;

			VulkanRHI::FResourceHeapManager ResourceHeapManager;

			VulkanRHI::FDeferredDeletionQueue DeferredDeletionQueue;

			VulkanRHI::FStagingManager StagingManager;

			VulkanRHI::FFenceManager FenceManager;

			FVulkanSamplerState* DefaultSampler;
			FVulkanSurface* DefaultImage;*/

			VkImageView DefaultImageView;

			std::vector< VkQueueFamilyProperties> QueueFamilyProps;
			VkFormatProperties FormatProperties[VK_FORMAT_RANGE_SIZE];
			// Info for formats that are not in the core Vulkan spec (i.e. extensions)
			mutable std::unordered_map<VkFormat, VkFormatProperties> ExtensionFormatProperties;
			/*std::vector<FVulkanBufferedQueryPool*> OcclusionQueryPools;
			std::vector<FVulkanBufferedQueryPool*> TimestampQueryPools;*/
			VulkanQueue* GfxQueue;
			VulkanQueue* ComputeQueue;
			VulkanQueue* TransferQueue;
			VulkanQueue* PresentQueue;

			VkComponentMapping PixelFormatComponentMapping[PF_MAX];

			/*FVulkanCommandListContext* ImmediateContext;
			FVulkanCommandListContext* ComputeContext;
			TArray<FVulkanCommandListContext*> CommandContexts;
*/
			void GetDeviceExtensions (std::vector<const ANSICHAR*>& OutDeviceExtensions, std::vector<const ANSICHAR*>& OutDeviceLayers, bool& bOutDebugMarkers);

			void ParseOptionalDeviceExtensions (const std::vector<const ANSICHAR*>& DeviceExtensions);
			//FOptionalVulkanDeviceExtensions OptionalDeviceExtensions;

			void SetupFormats ();

#if VULKAN_ENABLE_DRAW_MARKERS
			PFN_vkCmdDebugMarkerBeginEXT CmdDbgMarkerBegin;
			PFN_vkCmdDebugMarkerEndEXT CmdDbgMarkerEnd;
			PFN_vkDebugMarkerSetObjectNameEXT DebugMarkerSetObjectName;
			//friend class FVulkanCommandListContext;
#endif

			//class FVulkanPipelineStateCache* PipelineStateCache;
			friend class VulkanGraphicDevice;
		};
	}
}


#endif