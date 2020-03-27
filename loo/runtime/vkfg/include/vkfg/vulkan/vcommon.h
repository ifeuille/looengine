#pragma once

#include "vkfg/fg/mipmaplevel.h"
#include "vkfg/fg/multisamples.h"
#include "vkfg/fg/imagelayer.h"
#include "vkfg/fg/ids.h"
#include "vkfg/fg/vulkantype.h"
#include "vkfg/fg/enums.h"
#include "vkfg/fg/localresourceid.h"

#include "vulkanloader/VulkanLoader.h"
#include "vulkanloader/VulkanCheckError.h"

#include "global/extstd/dataracecheck.h"
#include "global/extstd/spinlock.h"
#include "global/container/appendable.h"
#include "global/container/inplace.h"
#include "global/extstd/linearallocator.h"
#include "vkfg/vulkan/utils/venums.h"

#if 0
#include <foonathan/memory/memory_pool.hpp>
#include <foonathan/memory/temporary_allocator.hpp>
#include <foonathan/memory/std_allocator.hpp>
#endif

namespace loo
{
	namespace vkfg
	{
		//template <typename T>
		//using TempArray					= std::vector< T, foonathan::memory::std_allocator< T, > >;

		using DebugName_t = StaticString<64>;

		using VkDescriptorSets_t = FixedArray< VkDescriptorSet, LOO_MaxDescriptorSets >;

		using VDeviceQueueInfoPtr = Ptr< const struct VDeviceQueueInfo >;

		using VTask = Ptr< class VFrameGraphTask >;

		enum class ShaderDbgIndex : uint { Unknown = ~0u };

		enum class BLASHandle_t : uint64_t {};

		struct VkGeometryInstance
		{
			// 4x3 row-major matrix
			loo::math::float4			transformRow0;
			loo::math::float4			transformRow1;
			loo::math::float4			transformRow2;

			uint			customIndex : 24;
			uint			mask : 8;
			uint			instanceOffset : 24;
			uint			flags : 8;
			BLASHandle_t	blasHandle;
		};


		class VDevice;
		class VDebugger;
		class VMemoryObj;
		class VBarrierManager;
		class VRenderPass;
		class VLogicalRenderPass;
		class VPipelineCache;
		class VDescriptorManager;
		class VLocalBuffer;
		class VLocalImage;
		class VLocalRTGeometry;
		class VLocalRTScene;
		class VRenderPassCache;
		class VBaseDrawVerticesTask;
		class VBaseDrawMeshes;
		class VComputePipeline;
		class VGraphicsPipeline;
		class VMeshPipeline;
		class VRayTracingScene;
		class VRayTracingPipeline;
		class VRayTracingShaderTable;
		class VPipelineLayout;
		class VShaderDebugger;
		class VPipelineResources;
		class VCommandBuffer;
		class VSwapchain;
		class VSubmitted;
		class VLocalDebugger;
		class VResourceManager;
		class VMemoryManager;
		class VFrameGraph;
		class VDebugger;


		struct VPipelineResourceSet
		{
			struct Item {
				DescriptorSetID				descSetId;
				VPipelineResources const*	pplnRes = null;
				uint						offsetIndex;		// in 'dynamicOffsets'
				uint						offsetCount = 0;
			};

			FixedArray< Item, LOO_MaxDescriptorSets >					resources;
			mutable FixedArray< uint, LOO_MaxBufferDynamicOffsets >		dynamicOffsets;
		};

	}
}