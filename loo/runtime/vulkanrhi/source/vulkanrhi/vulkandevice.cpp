#include "vulkanrhi/vulkanrhiprivate.h"
#include "vulkanrhi/vulkandevice.h"
#include "global/utils/path.h"
#include "vulkanrhi/vulkancontext.h"
#include "vulkanrhi/vulkanqueue.h"
#include "global/utils/panic.h"
#include "rhi/renderutils.h"

#ifdef LOO_PLATFORM_LINUX
#include <SDL.h>
#endif

loo::rhi::VulkanDevice::VulkanDevice (VkPhysicalDevice InGpu)
	:Gpu(InGpu)
	,Device(VK_NULL_HANDLE)
	//, ResourceHeapManager (this)
	//, DeferredDeletionQueue (this)
	//, DefaultSampler (nullptr)
	//, DefaultImage (nullptr)
	, DefaultImageView (VK_NULL_HANDLE)
	, GfxQueue (nullptr)
	, ComputeQueue (nullptr)
	, TransferQueue (nullptr)
	, PresentQueue (nullptr)
	//, ImmediateContext (nullptr)
	//, ComputeContext (nullptr)
#if VULKAN_ENABLE_DRAW_MARKERS
	, CmdDbgMarkerBegin (nullptr)
	, CmdDbgMarkerEnd (nullptr)
	, DebugMarkerSetObjectName (nullptr)
#endif
	//, PipelineStateCache (nullptr)
{
	memset (&GpuProps, 0, sizeof (GpuProps));
#if VULKAN_ENABLE_DESKTOP_HMD_SUPPORT
	memset (&GpuIdProps,0,sizeof(GpuIdProps));
#endif
	memset (&Features, 0, sizeof (Features));
	memset (&FormatProperties, 0, sizeof (FormatProperties));
	memset (&PixelFormatComponentMapping, 0, sizeof (PixelFormatComponentMapping));
}

loo::rhi::VulkanDevice::~VulkanDevice ()
{
	if (Device != VK_NULL_HANDLE)
	{
		Destroy ();
		Device = VK_NULL_HANDLE;
	}
}

void loo::rhi::VulkanDevice::CreateDevice ()
{
	ASSERT_MSG (Device == VK_NULL_HANDLE, "");
	//extension and layer info
	VkDeviceCreateInfo DeviceInfo;
	ZeroVulkanStruct (DeviceInfo, VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO);
	bool bDebugMarkersFound = false;
	std::vector<const ANSICHAR*> DeviceExtensions;
	std::vector<const ANSICHAR*> ValidationLayers;
	GetDeviceExtensions (DeviceExtensions, ValidationLayers, bDebugMarkersFound);

	ParseOptionalDeviceExtensions (DeviceExtensions);

	DeviceInfo.enabledExtensionCount = (uint32_t)DeviceExtensions.size ();
	DeviceInfo.ppEnabledExtensionNames = DeviceExtensions.data ();

	DeviceInfo.enabledLayerCount = (uint32_t)ValidationLayers.size ();
	DeviceInfo.ppEnabledLayerNames = (DeviceInfo.enabledLayerCount > 0) ? ValidationLayers.data () : nullptr;

	//queue info
	std::vector<VkDeviceQueueCreateInfo> QueueFamilyInfos;
	int32 GfxQueueFamilyIndex = -1;
	int32 ComputeQueueFamilyIndex = -1;
	int32 TransferQueueFamilyIndex = -1;
	utils::slog.i << "VULKAN INFO:"
		<< "Found %d Queue Families" << QueueFamilyProps.size () << utils::io::endl;
	uint32 NumPriorities = 0;
	for (size_t FamilyIndex = 0; FamilyIndex < QueueFamilyProps.size (); ++FamilyIndex)
	{
		const VkQueueFamilyProperties& CurrProps = QueueFamilyProps[FamilyIndex];

		bool bIsValidQueue = false;
		if ((CurrProps.queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT)
		{
			if (GfxQueueFamilyIndex == -1)
			{
				GfxQueueFamilyIndex = (int32_t)FamilyIndex;
				bIsValidQueue = true;
			}
			else
			{
				//#todo-rco: Support for multi-queue/choose the best queue!
			}
		}

		if ((CurrProps.queueFlags & VK_QUEUE_COMPUTE_BIT) == VK_QUEUE_COMPUTE_BIT)
		{
			if (ComputeQueueFamilyIndex == -1
				//&&(GRHIAllowAsyncComputeCvar.GetValueOnAnyThread () != 0 || GAllowPresentOnComputeQueue.GetValueOnAnyThread () != 0) 
				&& GfxQueueFamilyIndex != FamilyIndex)
			{
				ComputeQueueFamilyIndex = (int32_t)FamilyIndex;
				bIsValidQueue = true;
			}
		}

		if ((CurrProps.queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT)
		{
			// Prefer a non-gfx transfer queue
			if (TransferQueueFamilyIndex == -1 && (CurrProps.queueFlags & VK_QUEUE_GRAPHICS_BIT) != VK_QUEUE_GRAPHICS_BIT && (CurrProps.queueFlags & VK_QUEUE_COMPUTE_BIT) != VK_QUEUE_COMPUTE_BIT)
			{
				TransferQueueFamilyIndex = (int32_t)FamilyIndex;
				bIsValidQueue = true;
			}
		}

		auto GetQueueInfoString = [](const VkQueueFamilyProperties& Props)
		{
			std::wstring Info;
			if ((Props.queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT)
			{
				Info += TEXT (" Gfx");
			}
			if ((Props.queueFlags & VK_QUEUE_COMPUTE_BIT) == VK_QUEUE_COMPUTE_BIT)
			{
				Info += TEXT (" Compute");
			}
			if ((Props.queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT)
			{
				Info += TEXT (" Xfer");
			}
			if ((Props.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) == VK_QUEUE_SPARSE_BINDING_BIT)
			{
				Info += TEXT (" Sparse");
			}

			return Info;
		};

		if (!bIsValidQueue)
		{
			utils::slog.i << "VULKAN INFO:" << "Skipping unnecessary Queue Family " << FamilyIndex << ": " << CurrProps.queueCount << " queues"
				<< *GetQueueInfoString (CurrProps).c_str () << utils::io::endl;
			continue;
		}

		int32 QueueIndex = (int32_t)QueueFamilyInfos.size ();
		QueueFamilyInfos.push_back (VkDeviceQueueCreateInfo());
		VkDeviceQueueCreateInfo& CurrQueue = QueueFamilyInfos[QueueIndex];
		CurrQueue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		CurrQueue.queueFamilyIndex = (uint32_t)FamilyIndex;
		CurrQueue.queueCount = CurrProps.queueCount;
		NumPriorities += CurrProps.queueCount;
		utils::slog.i << "VULKAN INFO:" << "Initializing Queue Family " << FamilyIndex << ": " << CurrProps.queueCount << " queues " 
			<<*GetQueueInfoString (CurrProps).c_str () << utils::io::endl;
	}

	std::vector<float> QueuePriorities;
	QueuePriorities.resize (NumPriorities);
	float* CurrentPriority = QueuePriorities.data ();
	for (size_t Index = 0; Index < QueueFamilyInfos.size (); ++Index)
	{
		VkDeviceQueueCreateInfo& CurrQueue = QueueFamilyInfos[Index];
		CurrQueue.pQueuePriorities = CurrentPriority;

		const VkQueueFamilyProperties& CurrProps = QueueFamilyProps[CurrQueue.queueFamilyIndex];
		for (int32 QueueIndex = 0; QueueIndex < (int32)CurrProps.queueCount; ++QueueIndex)
		{
			*CurrentPriority++ = 1.0f;
		}
	}
	DeviceInfo.queueCreateInfoCount = (uint32_t)QueueFamilyInfos.size ();
	DeviceInfo.pQueueCreateInfos = QueueFamilyInfos.data ();

	DeviceInfo.pEnabledFeatures = &Features;

	VkResult result = vkCreateDevice (Gpu, &DeviceInfo, VKALLOC, &Device);
	ASSERT_POSTCONDITION (result == VK_SUCCESS, "Unable to create Vulkan device callback.");
	// Create Graphics Queue, here we submit command buffers for execution
	GfxQueue = new VulkanQueue (this, GfxQueueFamilyIndex, 0);
	if (ComputeQueueFamilyIndex == -1)
	{
		// If we didn't find a dedicated Queue, use the default one
		ComputeQueueFamilyIndex = GfxQueueFamilyIndex;
	}
	ComputeQueue = new VulkanQueue (this, ComputeQueueFamilyIndex, 0);
	if (TransferQueueFamilyIndex == -1)
	{
		// If we didn't find a dedicated Queue, use the default one
		TransferQueueFamilyIndex = ComputeQueueFamilyIndex;
	}
	TransferQueue = new VulkanQueue (this, TransferQueueFamilyIndex, 0);


}


void loo::rhi::VulkanDevice::PrepareForDestroy ()
{
	WaitUntilIdle ();
}

bool loo::rhi::VulkanDevice::QueryGPU (int32 DeviceIndex)
{
	bool bDiscrete = false;

	vkGetPhysicalDeviceProperties (Gpu, &GpuProps);

	auto GetDeviceTypeString = [&]()
	{
		std::wstring Info;
		switch (GpuProps.deviceType)
		{
		case  VK_PHYSICAL_DEVICE_TYPE_OTHER:
			Info = TEXT ("Other");
			break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			Info = TEXT ("Integrated GPU");
			break;
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			Info = TEXT ("Discrete GPU");
			bDiscrete = true;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			Info = TEXT ("Virtual GPU");
			break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			Info = TEXT ("CPU");
			break;
		default:
			Info = TEXT ("Unknown");
			break;
		}
		return Info;
	};

	utils::slog.i << "VULKAN INFO:" << "Initializing Device " << DeviceIndex << utils::io::endl;
	utils::slog.i << "VULKAN INFO:" << "Initializing Device " << DeviceIndex << utils::io::endl;
	utils::slog.i << "VULKAN INFO:" << "Initializing Device " << DeviceIndex << utils::io::endl;
	utils::slog.i << "VULKAN INFO:" << "Initializing Device " << DeviceIndex << utils::io::endl;
	utils::slog.i << "VULKAN INFO:" << "Initializing Device " << DeviceIndex << utils::io::endl;
	utils::slog.i << "VULKAN INFO:" << "API  " << GpuProps.apiVersion << " Driver " << GpuProps.driverVersion << " VendorId " << GpuProps.vendorID << utils::io::endl;
	utils::slog.i << "VULKAN INFO:" << "Name " << GpuProps.deviceName << " Device " << GpuProps.deviceID << " Type " << GetDeviceTypeString ().c_str () << utils::io::endl;
	utils::slog.i << "VULKAN INFO:" << "Max Descriptor Sets Bound "<< GpuProps.limits.maxBoundDescriptorSets<<" Timestamps "<< GpuProps.limits.timestampComputeAndGraphics << utils::io::endl;

	uint32 QueueCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties (Gpu, &QueueCount, nullptr);
	assert (QueueCount >= 1);

	QueueFamilyProps.resize (QueueCount);
	vkGetPhysicalDeviceQueueFamilyProperties (Gpu, &QueueCount, QueueFamilyProps.data ());

	return bDiscrete;
}

void loo::rhi::VulkanDevice::InitGPU (int32 DeviceIndex)
{
	LOO_UNUSED (DeviceIndex);
	vkGetPhysicalDeviceFeatures (Gpu, &Features);
	utils::slog.i << "VULKAN INFO:"
		<< "Geometry  " << Features.geometryShader<<"Tessellation "  << Features.tessellationShader << utils::io::endl;
	CreateDevice ();
	SetupFormats ();
	/*MemoryManager.Init (this);
	ResourceHeapManager.Init ();

	FenceManager.Init (this);

	StagingManager.Init (this);

	PipelineStateCache = new FVulkanPipelineStateCache (this);*/

	//std::vector<std::string> CacheFilenames;
	//FString StagedCacheDirectory = FPaths::ProjectDir () / TEXT ("Build") / TEXT ("ShaderCaches") / FPlatformProperties::IniPlatformName ();

	// look for any staged caches
	//TArray<FString> StagedCaches;
	//IFileManager::Get ().FindFiles (StagedCaches, *StagedCacheDirectory, TEXT ("cache"));
	// FindFiles returns the filenames without directory, so prepend the stage directory
	/*for (const FString& Filename : StagedCaches)
	{
		CacheFilenames.Add (StagedCacheDirectory / Filename);
	}*/

	// always look in the saved directory (for the cache from previous run that wasn't moved over to stage directory)
	//CacheFilenames.Add (VulkanRHI::GetPipelineCacheFilename ());

	//ImmediateContext = new FVulkanCommandListContext ((FVulkanDynamicRHI*)GDynamicRHI, this, GfxQueue, true);

	if (GfxQueue->GetFamilyIndex () != ComputeQueue->GetFamilyIndex ())
	{
		//ComputeContext = new FVulkanCommandListContext ((FVulkanDynamicRHI*)GDynamicRHI, this, ComputeQueue, true);
	}
	else
	{
		//ComputeContext = ImmediateContext;
	}

	/*extern TAutoConsoleVariable<int32> GRHIThreadCvar;
	if (GRHIThreadCvar->GetInt () > 1)
	{
		int32 Num = FTaskGraphInterface::Get ().GetNumWorkerThreads ();
		for (int32 Index = 0; Index < Num; Index++)
		{
			FVulkanCommandListContext* CmdContext = new FVulkanCommandListContext ((FVulkanDynamicRHI*)GDynamicRHI, this, GfxQueue, false);
			CommandContexts.Add (CmdContext);
		}
	}
*/
	//PipelineStateCache->InitAndLoad (CacheFilenames);

	// Setup default resource
	{
		/*FSamplerStateInitializerRHI Default (SF_Point);
		DefaultSampler = new FVulkanSamplerState (Default, *this);

		FRHIResourceCreateInfo CreateInfo;
		DefaultImage = new FVulkanSurface (*this, VK_IMAGE_VIEW_TYPE_2D, PF_B8G8R8A8, 1, 1, 1, false, 0, 1, 1, TexCreate_RenderTargetable | TexCreate_ShaderResource, CreateInfo);
		DefaultImageView = FVulkanTextureView::StaticCreate (*this, DefaultImage->Image, VK_IMAGE_VIEW_TYPE_2D, DefaultImage->GetFullAspectMask (), PF_B8G8R8A8, VK_FORMAT_B8G8R8A8_UNORM, 0, 1, 0, 1);*/
	}
}

void loo::rhi::VulkanDevice::Destroy ()
{
	vkDestroyImageView (GetInstanceHandle (), DefaultImageView, nullptr);
	DefaultImageView = VK_NULL_HANDLE;

	//delete DefaultSampler;
	//DefaultSampler = nullptr;

	//delete DefaultImage;
	//DefaultImage = nullptr;

	//if (ComputeContext != ImmediateContext)
	//{
	//	delete ComputeContext;
	//}
	//ComputeContext = nullptr;

	//delete ImmediateContext;
	//ImmediateContext = nullptr;

	//for (FVulkanQueryPool* QueryPool : OcclusionQueryPools)
	//{
	//	QueryPool->Destroy ();
	//	delete QueryPool;
	//}
	//OcclusionQueryPools.SetNum (0, false);

	/*for (FVulkanQueryPool* QueryPool : TimestampQueryPools)
	{
		QueryPool->Destroy ();
		delete QueryPool;
	}
	TimestampQueryPools.SetNum (0, false);*/

	/*delete PipelineStateCache;
	PipelineStateCache = nullptr;
	StagingManager.Deinit ();*/

	//ResourceHeapManager.Deinit ();

	delete TransferQueue;
	delete ComputeQueue;
	delete GfxQueue;

	/*FRHIResource::FlushPendingDeletes ();
	DeferredDeletionQueue.Clear ();*/

	//FenceManager.Deinit ();
	//MemoryManager.Deinit ();

	vkDestroyDevice (Device, nullptr);
	Device = VK_NULL_HANDLE;
}

void loo::rhi::VulkanDevice::WaitUntilIdle ()
{
	VERIFYVULKANRESULT (vkDeviceWaitIdle (Device));

	//#todo-rco: Loop through all contexts!
	//GetImmediateContext ().GetCommandBufferManager ()->RefreshFenceStatus ();

}

bool loo::rhi::VulkanDevice::IsFormatSupported (VkFormat Format) const
{
	auto ArePropertiesSupported = [](const VkFormatProperties& Prop) -> bool
	{
		return (Prop.bufferFeatures != 0) || (Prop.linearTilingFeatures != 0) || (Prop.optimalTilingFeatures != 0);
	};

	if (Format >= 0 && Format < VK_FORMAT_RANGE_SIZE)
	{
		const VkFormatProperties& Prop = FormatProperties[Format];
		return ArePropertiesSupported (Prop);
	}

	// Check for extension formats
	auto it = ExtensionFormatProperties.find (Format);
	if (it != ExtensionFormatProperties.end ())
	{
		return ArePropertiesSupported (it->second);
	}

	// Add it for faster caching next time
	VkFormatProperties NewProperties = { 0 };
	vkGetPhysicalDeviceFormatProperties (Gpu, Format, &NewProperties);
	ExtensionFormatProperties[Format] = NewProperties;

	return ArePropertiesSupported (NewProperties);
}

const VkComponentMapping & loo::rhi::VulkanDevice::GetFormatComponentMapping (EPixelFormat UEFormat) const
{
	if (UEFormat == PF_X24_G8)
	{
		return GetFormatComponentMapping (PF_DepthStencil);
	}
	ASSERT_MSG (GPixelFormats[UEFormat].Supported,"");
	return PixelFormatComponentMapping[UEFormat];
}

void loo::rhi::VulkanDevice::MapFormatSupport (EPixelFormat UEFormat, VkFormat VulkanFormat)
{
	PixelFormatInfo& FormatInfo = GPixelFormats[UEFormat];
	FormatInfo.PlatformFormat = VulkanFormat;
	FormatInfo.Supported = IsFormatSupported (VulkanFormat);

	if (!FormatInfo.Supported)
	{
		utils::slog.w << "VULKAN WARN:" << "EPixelFormat(" << (int32)UEFormat << ") is not supported with Vk format " << (int32)VulkanFormat << utils::io::endl;
	}
}

void loo::rhi::VulkanDevice::MapFormatSupport (EPixelFormat UEFormat, VkFormat VulkanFormat, int32 BlockBytes)
{
	MapFormatSupport (UEFormat, VulkanFormat);
	PixelFormatInfo& FormatInfo = GPixelFormats[UEFormat];
	FormatInfo.BlockBytes = BlockBytes;
}

void loo::rhi::VulkanDevice::SetComponentMapping (EPixelFormat UEFormat, VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a)
{
	// Please ensure that we support the mapping, otherwise there is no point setting it.
	assert (GPixelFormats[UEFormat].Supported);
	VkComponentMapping& ComponentMapping = PixelFormatComponentMapping[UEFormat];
	ComponentMapping.r = r;
	ComponentMapping.g = g;
	ComponentMapping.b = b;
	ComponentMapping.a = a;
}

void loo::rhi::VulkanDevice::SetupFormats ()
{
	for (uint32 Index = 0; Index < VK_FORMAT_RANGE_SIZE; ++Index)
	{
		const VkFormat Format = (VkFormat)Index;
		memset (&FormatProperties[Index],0,sizeof(FormatProperties[Index]));
		vkGetPhysicalDeviceFormatProperties (Gpu, Format, &FormatProperties[Index]);
	}

	static_assert(sizeof (VkFormat) <= sizeof (GPixelFormats[0].PlatformFormat), "PlatformFormat must be increased!");

	// Initialize the platform pixel format map.
	for (int32 Index = 0; Index < PF_MAX; ++Index)
	{
		GPixelFormats[Index].PlatformFormat = VK_FORMAT_UNDEFINED;
		GPixelFormats[Index].Supported = false;

		// Set default component mapping
		VkComponentMapping& ComponentMapping = PixelFormatComponentMapping[Index];
		ComponentMapping.r = VK_COMPONENT_SWIZZLE_R;
		ComponentMapping.g = VK_COMPONENT_SWIZZLE_G;
		ComponentMapping.b = VK_COMPONENT_SWIZZLE_B;
		ComponentMapping.a = VK_COMPONENT_SWIZZLE_A;
	}

	// Default formats
	MapFormatSupport (PF_B8G8R8A8, VK_FORMAT_B8G8R8A8_UNORM);
	SetComponentMapping (PF_B8G8R8A8, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_G8, VK_FORMAT_R8_UNORM);
	SetComponentMapping (PF_G8, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_G16, VK_FORMAT_R16_UNORM);
	SetComponentMapping (PF_G16, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_FloatRGB, VK_FORMAT_B10G11R11_UFLOAT_PACK32);
	SetComponentMapping (PF_FloatRGB, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_FloatRGBA, VK_FORMAT_R16G16B16A16_SFLOAT, 8);
	SetComponentMapping (PF_FloatRGBA, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_DepthStencil, VK_FORMAT_D32_SFLOAT_S8_UINT);
	if (!GPixelFormats[PF_DepthStencil].Supported)
	{
		MapFormatSupport (PF_DepthStencil, VK_FORMAT_D24_UNORM_S8_UINT);
		if (!GPixelFormats[PF_DepthStencil].Supported)
		{
			MapFormatSupport (PF_DepthStencil, VK_FORMAT_D16_UNORM_S8_UINT);
			if (!GPixelFormats[PF_DepthStencil].Supported)
			{
				utils::slog.e << "VULKAN ERROR:" << "No stencil texture format supported!" << utils::io::endl;
			}
		}
	}
	SetComponentMapping (PF_DepthStencil, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY);

	MapFormatSupport (PF_ShadowDepth, VK_FORMAT_D16_UNORM);
	SetComponentMapping (PF_ShadowDepth, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY);

	// Requirement for GPU particles
	MapFormatSupport (PF_G32R32F, VK_FORMAT_R32G32_SFLOAT, 8);
	SetComponentMapping (PF_G32R32F, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_A32B32G32R32F, VK_FORMAT_R32G32B32A32_SFLOAT, 16);
	SetComponentMapping (PF_A32B32G32R32F, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_G16R16, VK_FORMAT_R16G16_UNORM);
	SetComponentMapping (PF_G16R16, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_G16R16F, VK_FORMAT_R16G16_SFLOAT);
	SetComponentMapping (PF_G16R16F, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_G16R16F_FILTER, VK_FORMAT_R16G16_SFLOAT);
	SetComponentMapping (PF_G16R16F_FILTER, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R16_UINT, VK_FORMAT_R16_UINT);
	SetComponentMapping (PF_R16_UINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R16_SINT, VK_FORMAT_R16_SINT);
	SetComponentMapping (PF_R16_SINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R32_UINT, VK_FORMAT_R32_UINT);
	SetComponentMapping (PF_R32_UINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R32_SINT, VK_FORMAT_R32_SINT);
	SetComponentMapping (PF_R32_SINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R8_UINT, VK_FORMAT_R8_UINT);
	SetComponentMapping (PF_R8_UINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_D24, VK_FORMAT_X8_D24_UNORM_PACK32);
	if (!GPixelFormats[PF_D24].Supported)
	{
		MapFormatSupport (PF_D24, VK_FORMAT_D24_UNORM_S8_UINT);
		if (!GPixelFormats[PF_D24].Supported)
		{
			MapFormatSupport (PF_D24, VK_FORMAT_D16_UNORM_S8_UINT);
			if (!GPixelFormats[PF_D24].Supported)
			{
				MapFormatSupport (PF_D24, VK_FORMAT_D32_SFLOAT);
				if (!GPixelFormats[PF_D24].Supported)
				{
					MapFormatSupport (PF_D24, VK_FORMAT_D32_SFLOAT_S8_UINT);
					if (!GPixelFormats[PF_D24].Supported)
					{
						MapFormatSupport (PF_D24, VK_FORMAT_D16_UNORM);
					}
				}
			}
		}
	}

	SetComponentMapping (PF_D24, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R16F, VK_FORMAT_R16_SFLOAT);
	SetComponentMapping (PF_R16F, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R16F_FILTER, VK_FORMAT_R16_SFLOAT);
	SetComponentMapping (PF_R16F_FILTER, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_FloatR11G11B10, VK_FORMAT_B10G11R11_UFLOAT_PACK32, 4);
	SetComponentMapping (PF_FloatR11G11B10, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_A2B10G10R10, VK_FORMAT_A2B10G10R10_UNORM_PACK32, 4);
	SetComponentMapping (PF_A2B10G10R10, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_A16B16G16R16, VK_FORMAT_R16G16B16A16_UNORM, 8);
	SetComponentMapping (PF_A16B16G16R16, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_A8, VK_FORMAT_R8_UNORM);
	SetComponentMapping (PF_A8, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_R);

	MapFormatSupport (PF_R5G6B5_UNORM, VK_FORMAT_R5G6B5_UNORM_PACK16);
	SetComponentMapping (PF_R5G6B5_UNORM, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_R8G8B8A8, VK_FORMAT_R8G8B8A8_UNORM);
	SetComponentMapping (PF_R8G8B8A8, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_R8G8B8A8_UINT, VK_FORMAT_R8G8B8A8_UINT);
	SetComponentMapping (PF_R8G8B8A8_UINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_R8G8B8A8_SNORM, VK_FORMAT_R8G8B8A8_SNORM);
	SetComponentMapping (PF_R8G8B8A8_SNORM, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_R16G16_UINT, VK_FORMAT_R16G16_UINT);
	SetComponentMapping (PF_R16G16_UINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R16G16B16A16_UINT, VK_FORMAT_R16G16B16A16_UINT);
	SetComponentMapping (PF_R16G16B16A16_UINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_R16G16B16A16_SINT, VK_FORMAT_R16G16B16A16_SINT);
	SetComponentMapping (PF_R16G16B16A16_SINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_R32G32B32A32_UINT, VK_FORMAT_R32G32B32A32_UINT);
	SetComponentMapping (PF_R32G32B32A32_UINT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_R8G8, VK_FORMAT_R8G8_UNORM);
	SetComponentMapping (PF_R8G8, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_V8U8, VK_FORMAT_R8G8_UNORM);
	SetComponentMapping (PF_V8U8, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

	MapFormatSupport (PF_R32_FLOAT, VK_FORMAT_R32_SFLOAT);
	SetComponentMapping (PF_R32_FLOAT, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO);

#ifdef LOO_PLATFORM_WINDOWS
	MapFormatSupport (PF_DXT1, VK_FORMAT_BC1_RGB_UNORM_BLOCK);	// Also what OpenGL expects (RGBA instead RGB, but not SRGB)
	SetComponentMapping (PF_DXT1, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_ONE);

	MapFormatSupport (PF_DXT3, VK_FORMAT_BC2_UNORM_BLOCK);
	SetComponentMapping (PF_DXT3, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_DXT5, VK_FORMAT_BC3_UNORM_BLOCK);
	SetComponentMapping (PF_DXT5, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_BC4, VK_FORMAT_BC4_UNORM_BLOCK);
	SetComponentMapping (PF_BC4, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_BC5, VK_FORMAT_BC5_UNORM_BLOCK);
	SetComponentMapping (PF_BC5, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_BC6H, VK_FORMAT_BC6H_UFLOAT_BLOCK);
	SetComponentMapping (PF_BC6H, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);

	MapFormatSupport (PF_BC7, VK_FORMAT_BC7_UNORM_BLOCK);
	SetComponentMapping (PF_BC7, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);
#elif defined(LOO_PLATFORM_ANDROID)
	MapFormatSupport (PF_ASTC_4x4, VK_FORMAT_ASTC_4x4_UNORM_BLOCK);
	if (GPixelFormats[PF_ASTC_4x4].Supported)
	{
		SetComponentMapping (PF_ASTC_4x4, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);
	}

	MapFormatSupport (PF_ASTC_6x6, VK_FORMAT_ASTC_6x6_UNORM_BLOCK);
	if (GPixelFormats[PF_ASTC_6x6].Supported)
	{
		SetComponentMapping (PF_ASTC_6x6, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);
	}

	MapFormatSupport (PF_ASTC_8x8, VK_FORMAT_ASTC_8x8_UNORM_BLOCK);
	if (GPixelFormats[PF_ASTC_8x8].Supported)
	{
		SetComponentMapping (PF_ASTC_8x8, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);
	}

	MapFormatSupport (PF_ASTC_10x10, VK_FORMAT_ASTC_10x10_UNORM_BLOCK);
	if (GPixelFormats[PF_ASTC_10x10].Supported)
	{
		SetComponentMapping (PF_ASTC_10x10, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);
	}

	MapFormatSupport (PF_ASTC_12x12, VK_FORMAT_ASTC_12x12_UNORM_BLOCK);
	if (GPixelFormats[PF_ASTC_12x12].Supported)
	{
		SetComponentMapping (PF_ASTC_12x12, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);
	}

	// ETC1 is a subset of ETC2 R8G8B8.
	MapFormatSupport (PF_ETC1, VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK);
	if (GPixelFormats[PF_ETC1].Supported)
	{
		SetComponentMapping (PF_ETC1, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_ONE);
	}

	MapFormatSupport (PF_ETC2_RGB, VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK);
	if (GPixelFormats[PF_ETC2_RGB].Supported)
	{
		SetComponentMapping (PF_ETC2_RGB, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_ONE);
	}

	MapFormatSupport (PF_ETC2_RGBA, VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK);
	if (GPixelFormats[PF_ETC2_RGB].Supported)
	{
		SetComponentMapping (PF_ETC2_RGBA, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A);
	}
#endif
}

