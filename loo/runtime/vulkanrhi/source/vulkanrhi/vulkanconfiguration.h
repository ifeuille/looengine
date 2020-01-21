// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	VulkanConfiguration.h: Vulkan resource RHI definitions.
=============================================================================*/

// Compiled with 1.0.57.0

#pragma once
#include "global/global.h"
#include "rhi/elementformat.h"

#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR 1
#elif defined(IOS)
#define VK_USE_PLATFORM_IOS_MVK 1
#elif defined(__linux__)
#define VK_USE_PLATFORM_XLIB_KHR 1
#elif defined(__APPLE__)
#define VK_USE_PLATFORM_MACOS_MVK 1
#elif defined(WIN32)
#define VK_USE_PLATFORM_WIN32_KHR 1
#endif

// API version we want to target.
#ifdef LOO_PLATFORM_WINDOWS
#define UE_VK_API_VERSION	VK_MAKE_VERSION(1, 0, 1)
#elif  defined(LOO_PLATFORM_MAC) // Needed for compiling Vulkan shaders for Android
#define UE_VK_API_VERSION	VK_MAKE_VERSION(1, 0, 1)
#elif defined(LOO_PLATFORM_ANDROID)
#define UE_VK_API_VERSION	VK_MAKE_VERSION(1, 0, 1)
#elif defined(LOO_PLATFORM_LINUX)
#define UE_VK_API_VERSION	VK_MAKE_VERSION(1, 0, 1)
#else
#error Unsupported platform!
#endif

#if defined(LOO_DEBUG) || defined(LOO_PLATFORM_WINDOWS) || (defined(LOO_PLATFORM_ANDROID) && defined(LOO_DEBUG))
#define VULKAN_HAS_DEBUGGING_ENABLED 1 //!!!
#else
#define VULKAN_HAS_DEBUGGING_ENABLED 0
#endif

// constants we probably will change a few times
#define VULKAN_UB_RING_BUFFER_SIZE								(8 * 1024 * 1024)

enum class EDescriptorSetStage
{
	// Adjusting these requires a full shader rebuild (ie modify the guid on VulkanCommon.usf)
	// Keep the values in sync with EShaderFrequency
	Vertex = 0,
	Hull = 1,
	Domain = 2,
	Pixel = 3,
	Geometry = 4,

	// Compute is its own pipeline, so it can all live as set 0
	Compute = 0,

	Invalid = -1,
};

inline EDescriptorSetStage GetDescriptorSetForStage (loo::rhi::EShaderFrequency Stage)
{
	switch (Stage)
	{
	case loo::rhi::SF_Vertex:		return EDescriptorSetStage::Vertex;
	case loo::rhi::SF_Hull:		return EDescriptorSetStage::Hull;
	case loo::rhi::SF_Domain:		return EDescriptorSetStage::Domain;
	case loo::rhi::SF_Pixel:		return EDescriptorSetStage::Pixel;
	case loo::rhi::SF_Geometry:	return EDescriptorSetStage::Geometry;
	case loo::rhi::SF_Compute:	return EDescriptorSetStage::Compute;
	default:
		assert(0 && TEXT ("Invalid shader Stage %d")&&Stage);
		break;
	}

	return EDescriptorSetStage::Invalid;
}

// Enables the VK_LAYER_LUNARG_api_dump layer and the report VK_DEBUG_REPORT_INFORMATION_BIT_EXT flag
#define VULKAN_ENABLE_API_DUMP									0
// Enables logging wrappers per Vulkan call
#define VULKAN_ENABLE_DUMP_LAYER								0
#if defined(LOO_PLATFORM_WINDOWS)&& !VULKAN_ENABLE_DUMP_LAYER
#define VULKAN_ENABLE_DRAW_MARKERS								1
#else
#define VULKAN_ENABLE_DRAW_MARKERS								0
#endif

// Keep the Vk*CreateInfo stored per object for debugging
#define VULKAN_KEEP_CREATE_INFO									0

#define VULKAN_SINGLE_ALLOCATION_PER_RESOURCE					0

#define VULKAN_CUSTOM_MEMORY_MANAGER_ENABLED					0

#define VULKAN_RETAIN_BUFFERS									0

#define VULKAN_USE_MSAA_RESOLVE_ATTACHMENTS						1

#define VULKAN_ENABLE_AGGRESSIVE_STATS							0

#define VULKAN_ENABLE_RHI_DEBUGGING								1

#define VULKAN_REUSE_FENCES										1

#define VULKAN_ENABLE_DESKTOP_HMD_SUPPORT						PLATFORM_WINDOWS

#if defined(LOO_PLATFORM_ANDROID)
#define VULKAN_SIGNAL_UNIMPLEMENTED()
#elif defined(LOO_PLATFORM_LINUX)
#define VULKAN_SIGNAL_UNIMPLEMENTED()				ASSERT_MSG(false, TEXT("Unimplemented vulkan functionality: %s"), __FUNC__)
#else
#define VULKAN_SIGNAL_UNIMPLEMENTED()				ASSERT_MSG(false, TEXT("Unimplemented vulkan functionality: %s"), TEXT(__FUNCTION__))
#endif

namespace EVulkanBindingType
{
	enum EType : loo::uint8
	{
		PackedUniformBuffer,		//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
		UniformBuffer,			//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER

		CombinedImageSampler,	//VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
		Sampler,					//VK_DESCRIPTOR_TYPE_SAMPLER
		Image,						//VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE

		UniformTexelBuffer,			//VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER	Buffer<>

		//A storage image (VK_DESCRIPTOR_TYPE_STORAGE_IMAGE) is a descriptor type that is used for load, store, and atomic operations on image memory from within shaders bound to pipelines.
		StorageImage,				//VK_DESCRIPTOR_TYPE_STORAGE_IMAGE		RWTexture

		//RWBuffer/RWTexture?
		//A storage texel buffer (VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER) represents a tightly packed array of homogeneous formatted data that is stored in a buffer and is made accessible to shaders. Storage texel buffers differ from uniform texel buffers in that they support stores and atomic operations in shaders, may support a different maximum length, and may have different performance characteristics.
		StorageTexelBuffer,

		// UAV/RWBuffer
		//A storage buffer(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER) is a region of structured storage that supports both read and write access for shaders.In addition to general read and write operations, some members of storage buffers can be used as the target of atomic operations.In general, atomic operations are only supported on members that have unsigned integer formats.
		StorageBuffer,


		Count,
	};

	static inline char GetBindingTypeChar (EType Type)
	{
		// Make sure these do NOT alias EPackedTypeName*
		switch (Type)
		{
		case UniformBuffer:			return 'b';
		case CombinedImageSampler:	return 'c';
		case Sampler:				return 'p';
		case Image:					return 'w';
		case UniformTexelBuffer:	return 'x';
		case StorageImage:			return 'y';
		case StorageTexelBuffer:	return 'z';
		case StorageBuffer:			return 'v';
		default:
			assert (0);
			break;
		}

		return 0;
	}
}

/** How many back buffers to cycle through */
enum
{
	NUM_RENDER_BUFFERS = 3,
};

