#ifndef LE_RHI_ELEMENTFORMAT_H
#define LE_RHI_ELEMENTFORMAT_H

/*
关于render pipeline,command buffer等的设计
说明
这里将采用vulkan作为蓝本，将渲染管线的细节曝光出来
这里模仿vucore.h的结构体实现了大量struct和enum,他们是上层能直接使用的部分，
下层，对于各个渲染器，他们必须使用converter从上层传入的结构体获取到自己所需的数据
command buffer主要按照vulkan和cocos的实现效果。
使用上，尽量贴近unity，目的是将渲染管线的可能性充分开放。
更甚，也许可以按照vulkan的使用方法来使用封装过的渲染器。
也就是说，也许可以实现多级渲染接口方案，最低级是渲染器的封装，更上层是自定义渲染管线。

关于converter的效率
尽量使用converter(src,dst&)这种，不让优化交给编译器，防止可能的问题
另外，对于结构体可以使用初始化列表的方法进行converter
对于enum就要考虑值得映射关系了

对于非struct的部分就是指针，实现隐藏在底层，上层只是一个指针
*/

//#pragma once
#include <cstdint>
//#include <iostream>

#define LE_LOD_CLAMP_NONE                 1000.0f
#define LE_REMAINING_MIP_LEVELS           (~0U)
#define LE_REMAINING_ARRAY_LAYERS         (~0U)
#define LE_WHOLE_SIZE                     (~0ULL)
#define LE_ATTACHMENT_UNUSED              (~0U)
#define LE_TRUE                           1
#define LE_FALSE                          0
#define LE_QUEUE_FAMILY_IGNORED           (~0U)
#define LE_SUBPASS_EXTERNAL               (~0U)
#define LE_MAX_PHYSICAL_DEVICE_NAME_SIZE  256
#define LE_UUID_SIZE                      16
#define LE_MAX_MEMORY_TYPES               32
#define LE_MAX_MEMORY_HEAPS               16
#define LE_MAX_EXTENSION_NAME_SIZE        256
#define LE_MAX_DESCRIPTION_SIZE           256



namespace le
{
	namespace rhi
	{
		typedef uint32_t LEFlags;
		typedef uint32_t LEBool32;
		typedef uint64_t LEDeviceSize;
		typedef uint32_t LESampleMask;
		//enum 定义
	  //#if(1)
		/**
		*#图片类型
		**/
		enum class LEImageType
		{
			e1D = 0,
			e2D = 1,
			e3D = 2
		};


		/**
		*图片采样
		**/
		enum class LEImageTiling {
			eOptimal = 0,
			eLinear = 1,
			//eDrmFormatModifierEXT = 2
		} ;


		//image
		enum class LESharingMode {
			LE_SHARING_MODE_EXCLUSIVE = 0,
			LE_SHARING_MODE_CONCURRENT = 1,
		} ;

		//
		enum class LEImageLayout {
			eUndefined = 0,
			eGeneral = 1,
			eColorAttachmentOptimal = 2,
			eDepthStencilAttachmentOptimal = 3,
			eDepthStencilReadOnlyOptimal = 4,
			eShaderReadOnlyOptimal = 5,
			eTransferSrcOptimal = 6,
			eTransferDstOptimal = 7,
			ePreinitialized = 8,
			eDepthReadOnlyStencilAttachmentOptimal = 1000117000,
			eDepthAttachmentStencilReadOnlyOptimal = 1000117001,
			ePresentSrcKHR = 1000001002,
			eSharedPresentKHR = 1000111000,
			eDepthReadOnlyStencilAttachmentOptimalKHR = eDepthReadOnlyStencilAttachmentOptimal,
			eDepthAttachmentStencilReadOnlyOptimalKHR = eDepthAttachmentStencilReadOnlyOptimal,
		} ;

		//颜色调制
		enum class LEImageViewType {
			e1D = 0,
			e2D = 1,
			e3D = 2,
			eCube = 3,
			e1DArray = 4,
			e2DArray = 5,
			eCubeArray = 6,
		} ;

		enum class LEComponentSwizzle {
			eIdentity = 0,
			eZero = 1,
			eOne = 2,
			eR = 3,
			eG = 4,
			eB = 5,
			eA = 6,
		};

		enum class LEVertexInputRate {
			eVertex = 0,
			eInstance = 1,
		} ;

		//图元类型
		enum class LEPrimitiveTopology {
			ePointList = 0,
			eLineList = 1,
			eLineStrip = 2,
			eTriangleList = 3,
			eTriangleStrip = 4,
			eTriangleFan = 5,
			eLineListWithAdjacency = 6,
			eLineStripWithAdjacency = 7,
			eTriangleListWithAdjacency = 8,
			eTriangleStripWithAdjacency = 9,
			ePatchList = 10,
		} ;

		enum class LEPolygonMode {
			eFill = 0,
			eLine = 1,
			ePoint = 2,
			eFillRectangleNV = 1000153000,
		} ;

		//front face
		enum class LEFrontFace {
			eCounterClockwise = 0,
			eClockwise = 1,
		} ;

		//比较
		enum class LECompareOp {
			eNever = 0,
			eLess = 1,
			eEqual = 2,
			eLessOrEqual = 3,
			eGreater = 4,
			eNotEqual = 5,
			eGreaterOrEqual = 6,
			eAlways = 7,
		} ;

		//stencil 操作
		enum class LEStencilOp {
			eKeep = 0,
			eZero = 1,
			eReplace = 2,
			eIncrementAndClamp = 3,
			eDecrementAndClamp = 4,
			eInvert = 5,
			eIncrementAndWrap = 6,
			eDecrementAndWrap = 7,
		} ;

		//逻辑操作，片元着色器之后的步骤可能用到
		enum class LELogicOp {
			eClear = 0,
			eAnd = 1,
			eAndReverse = 2,
			eCopy = 3,
			eAndInverted = 4,
			eNoOp = 5,
			eXor = 6,
			eOr = 7,
			eNor = 8,
			eEquivalent = 9,
			eInvert = 10,
			eOrReverse = 11,
			eCopyInverted = 12,
			eOrInverted = 13,
			eNand = 14,
			eSet = 15,
		} ;

		//混合因子
		enum class LEBlendFactor {
			eZero = 0,
			eOne = 1,
			eSrcColor = 2,
			eOneMinusSrcColor = 3,
			eDstColor = 4,
			eOneMinusDstColor = 5,
			eSrcAlpha = 6,
			eOneMinusSrcAlpha = 7,
			eDstAlpha = 8,
			eOneMinusDstAlpha = 9,
			eConstantColor = 10,
			eOneMinusConstantColor = 11,
			eConstantAlpha = 12,
			eOneMinusConstantAlpha = 13,
			eSrcAlphaSaturate = 14,
			eSrc1Color = 15,
			eOneMinusSrc1Color = 16,
			eSrc1Alpha = 17,
			eOneMinusSrc1Alpha = 18,
		} ;

		//混合操作
		enum class LEBlendOp {
			eAdd = 0,
			eSubtract = 1,
			eReverseSubtract = 2,
			eMin = 3,
			eMax = 4,
			eZeroEXT = 1000148000,
			eSrcEXT = 1000148001,
			eDstEXT = 1000148002,
			eSrcOverEXT = 1000148003,
			eDstOverEXT = 1000148004,
			eSrcInEXT = 1000148005,
			eDstInEXT = 1000148006,
			eSrcOutEXT = 1000148007,
			eDstOutEXT = 1000148008,
			eSrcAtopEXT = 1000148009,
			eDstAtopEXT = 1000148010,
			eXorEXT = 1000148011,
			eMultiplyEXT = 1000148012,
			eScreenEXT = 1000148013,
			eOverlayEXT = 1000148014,
			eDarkenEXT = 1000148015,
			eLightenEXT = 1000148016,
			eColordodgeEXT = 1000148017,
			eColorburnEXT = 1000148018,
			eHardlightEXT = 1000148019,
			eSoftlightEXT = 1000148020,
			eDifferenceEXT = 1000148021,
			eExclusionEXT = 1000148022,
			eInvertEXT = 1000148023,
			eInvertRgbEXT = 1000148024,
			eLineardodgeEXT = 1000148025,
			eLinearburnEXT = 1000148026,
			eVividlightEXT = 1000148027,
			eLinearlightEXT = 1000148028,
			ePinlightEXT = 1000148029,
			eHardmixEXT = 1000148030,
			eHslHueEXT = 1000148031,
			eHslSaturationEXT = 1000148032,
			eHslColorEXT = 1000148033,
			eHslLuminosityEXT = 1000148034,
			ePlusEXT = 1000148035,
			ePlusClampedEXT = 1000148036,
			ePlusClampedAlphaEXT = 1000148037,
			ePlusDarkerEXT = 1000148038,
			eMinusEXT = 1000148039,
			eMinusClampedEXT = 1000148040,
			eContrastEXT = 1000148041,
			eInvertOvgEXT = 1000148042,
			eRedEXT = 1000148043,
			eGreenEXT = 1000148044,
			eBlueEXT = 1000148045,
		} ;

		//dynamic 选项
		enum class LEDynamicState {
			LE_DYNAMIC_STATE_VIEWPORT = 0,
			LE_DYNAMIC_STATE_SCISSOR = 1,
			LE_DYNAMIC_STATE_LINE_WIDTH = 2,
			LE_DYNAMIC_STATE_DEPTH_BIAS = 3,
			LE_DYNAMIC_STATE_BLEND_CONSTANTS = 4,
			LE_DYNAMIC_STATE_DEPTH_BOUNDS = 5,
			LE_DYNAMIC_STATE_STENCIL_COMPARE_MASK = 6,
			LE_DYNAMIC_STATE_STENCIL_WRITE_MASK = 7,
			LE_DYNAMIC_STATE_STENCIL_REFERENCE = 8,
			LE_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV = 1000087000,
			LE_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT = 1000099000,
			LE_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT = 1000143000,
			LE_DYNAMIC_STATE_BEGIN_RANGE = LE_DYNAMIC_STATE_VIEWPORT,
			LE_DYNAMIC_STATE_END_RANGE = LE_DYNAMIC_STATE_STENCIL_REFERENCE,
			LE_DYNAMIC_STATE_RANGE_SIZE = (LE_DYNAMIC_STATE_STENCIL_REFERENCE - LE_DYNAMIC_STATE_VIEWPORT + 1),
			LE_DYNAMIC_STATE_MAX_ENUM = 0x7FFFFFFF
		} ;

		enum class LEFilter {
			eNearest = 0,
			eLinear = 1,
			eCubicIMG = 1000015000,
		} ;

		//mipmap插值方式
		enum class LESamplerMipmapMode {
			eNearest = 0,
			eLinear = 1,
		} ;

		//采样方式
		enum class LESamplerAddressMode {
			eRepeat = 0,
			eMirroredRepeat = 1,
			eClampToEdge = 2,
			eClampToBorder = 3,
			eMirrorClampToEdge = 4,
		} ;


		enum class LEBorderColor {
			eFloatTransparentBlack = 0,
			eIntTransparentBlack = 1,
			eFloatOpaqueBlack = 2,
			eIntOpaqueBlack = 3,
			eFloatOpaqueWhite = 4,
			eIntOpaqueWhite = 5,
		} ;


		enum class LEAttachmentLoadOp {
			eLoad = 0,
			eClear = 1,
			eDontCare = 2,
		} ;


		enum class LEAttachmentStoreOp {
			eStore = 0,
			eDontCare = 1,
		} ;


		enum class LEPipelineBindPoint {
			eGraphics = 0,
			eCompute = 1,
			eRaytracingNVX = 2,
		} ;

		enum class LECommandBufferLevel {
			ePrimary = 0,
			eSecondary = 1,
		} ;


		enum class LEIndexType {
			eUint16 = 0,
			eUint32 = 1,
		} ;

		enum class LESubpassContents {
			eInline = 0,
			eSecondaryCommandBuffers = 1,
		} ;


		//#endif


		enum class LESampleCountFlagBits {
			e1 = 0x00000001,
			e2 = 0x00000002,
			e3 = 0x00000004,
			e4 = 0x00000008,
			e5 = 0x00000010,
			e6 = 0x00000020,
			e7 = 0x00000040,
			e8 = 0x7FFFFFFF
		} ;
		typedef LEFlags LESampleCountFlags;



		//LEQueueFlagBits


		

		enum class LEImageAspectFlagBits {
			eColor = 0x00000001,
			eDepth = 0x00000002,
			eStencil = 0x00000004,
			eMetadata = 0x00000008,
			ePlane0 = 0x00000010,
			ePlane1 = 0x00000020,
			ePlane2 = 0x00000040,
			ePlane0KHR = ePlane0,
			ePlane1KHR = ePlane1,
			ePlane2KHR = ePlane2,
			/*eMemoryPlane0EXT = VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT,
			eMemoryPlane1EXT = VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT,
			eMemoryPlane2EXT = VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT,
			eMemoryPlane3EXT = VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT*/
		} ;
		typedef LEFlags LEImageAspectFlags;


		enum class LECullModeFlagBits {
			eNone = 0,
			eFront = 0x00000001,
			eBack = 0x00000002,
			eFrontAndBack = 0x00000003,
		} ;
		typedef LEFlags LECullModeFlags;
		typedef LEFlags LEPipelineMultisampleStateCreateFlags;
		typedef LEFlags LEPipelineDepthStencilStateCreateFlags;
		typedef LEFlags LEPipelineColorBlendStateCreateFlags;

		enum class LEColorComponentFlagBits {
			eR = 0x00000001,
			eG = 0x00000002,
			eB = 0x00000004,
			eA = 0x00000008,
		} ;
		typedef LEFlags LEColorComponentFlags;
		typedef LEFlags LEPipelineDynamicStateCreateFlags;
		typedef LEFlags LEPipelineLayoutCreateFlags;
		typedef LEFlags LEShaderStageFlags;
		typedef LEFlags LESamplerCreateFlags;



		enum class LECommandBufferUsageFlagBits {
			eOneTimeSubmit = 0x00000001,
			eRenderPassContinue = 0x00000002,
			eSimultaneousUse = 0x00000004,
		} ;
		typedef LEFlags LECommandBufferUsageFlags;

		enum class LEQueryControlFlagBits {
			ePrecise = 0x00000001,
		} ;
		typedef LEFlags LEQueryControlFlags;

		enum class LECommandBufferResetFlagBits {
			eReleaseResources = 0x00000001,
		} ;
		typedef LEFlags LECommandBufferResetFlags;

		enum class LEStencilFaceFlagBits {
			eFront = 0x00000001,
			eBack = 0x00000002,
			eVkStencilFrontAndBack = 0x00000003,
		} ;
		typedef LEFlags LEStencilFaceFlags;





		//#endif


		  //struct定义
		//#if(1)
		  //typedef struct LEApplicationInfo {
		  //  ////LEStructureType    sType;
		  //  const void*        pNext;
		  //  const char*        pApplicationName;
		  //  uint32_t           applicationVersion;
		  //  const char*        pEngineName;
		  //  uint32_t           engineVersion;
		  //  uint32_t           apiVersion;
		  //} LEApplicationInfo;

		  //typedef struct LEInstanceCreateInfo {
		  // // //LEStructureType             sType;
		  //  const void*                 pNext;
		  //  //LEInstanceCreateFlags       flags;
		  //  const LEApplicationInfo*    pApplicationInfo;
		  //  uint32_t                    enabledLayerCount;
		  //  const char* const*          ppEnabledLayerNames;
		  //  uint32_t                    enabledExtensionCount;
		  //  const char* const*          ppEnabledExtensionNames;
		  //} LEInstanceCreateInfo;

		typedef struct LEPhysicalDeviceFeatures {
			LEBool32    robustBufferAccess;
			LEBool32    fullDrawIndexUint32;
			LEBool32    imageCubeArray;
			LEBool32    independentBlend;
			LEBool32    geometryShader;
			LEBool32    tessellationShader;
			LEBool32    sampleRateShading;
			LEBool32    dualSrcBlend;
			LEBool32    logicOp;
			LEBool32    multiDrawIndirect;
			LEBool32    drawIndirectFirstInstance;
			LEBool32    depthClamp;
			LEBool32    depthBiasClamp;
			LEBool32    fillModeNonSolid;
			LEBool32    depthBounds;
			LEBool32    wideLines;
			LEBool32    largePoints;
			LEBool32    alphaToOne;
			LEBool32    multiViewport;
			LEBool32    samplerAnisotropy;
			LEBool32    textureCompressionETC2;
			LEBool32    textureCompressionASTC_LDR;
			LEBool32    textureCompressionBC;
			LEBool32    occlusionQueryPrecise;
			LEBool32    pipelineStatisticsQuery;
			LEBool32    vertexPipelineStoresAndAtomics;
			LEBool32    fragmentStoresAndAtomics;
			LEBool32    shaderTessellationAndGeometryPointSize;
			LEBool32    shaderImageGatherExtended;
			LEBool32    shaderStorageImageExtendedFormats;
			LEBool32    shaderStorageImageMultisample;
			LEBool32    shaderStorageImageReadWithoutFormat;
			LEBool32    shaderStorageImageWriteWithoutFormat;
			LEBool32    shaderUniformBufferArrayDynamicIndexing;
			LEBool32    shaderSampledImageArrayDynamicIndexing;
			LEBool32    shaderStorageBufferArrayDynamicIndexing;
			LEBool32    shaderStorageImageArrayDynamicIndexing;
			LEBool32    shaderClipDistance;
			LEBool32    shaderCullDistance;
			LEBool32    shaderFloat64;
			LEBool32    shaderInt64;
			LEBool32    shaderInt16;
			LEBool32    shaderResourceResidency;
			LEBool32    shaderResourceMinLod;
			LEBool32    sparseBinding;
			LEBool32    sparseResidencyBuffer;
			LEBool32    sparseResidencyImage2D;
			LEBool32    sparseResidencyImage3D;
			LEBool32    sparseResidency2Samples;
			LEBool32    sparseResidency4Samples;
			LEBool32    sparseResidency8Samples;
			LEBool32    sparseResidency16Samples;
			LEBool32    sparseResidencyAliased;
			LEBool32    variableMultisampleRate;
			LEBool32    inheritedQueries;
		} LEPhysicalDeviceFeatures;


		//typedef struct LEFormatProperties {
		//  LEFormatFeatureFlags    linearTilingFeatures;
		//  LEFormatFeatureFlags    optimalTilingFeatures;
		//  LEFormatFeatureFlags    bufferFeatures;
		//} LEFormatProperties;

		typedef struct LEExtent3D {
			uint32_t    width;
			uint32_t    height;
			uint32_t    depth;
		} LEExtent3D;


		typedef struct LEPhysicalDeviceLimits {
			uint32_t              maxImageDimension1D;
			uint32_t              maxImageDimension2D;
			uint32_t              maxImageDimension3D;
			uint32_t              maxImageDimensionCube;
			uint32_t              maxImageArrayLayers;
			uint32_t              maxTexelBufferElements;
			uint32_t              maxUniformBufferRange;
			uint32_t              maxStorageBufferRange;
			uint32_t              maxPushConstantsSize;
			uint32_t              maxMemoryAllocationCount;
			uint32_t              maxSamplerAllocationCount;
			LEDeviceSize          bufferImageGranularity;
			LEDeviceSize          sparseAddressSpaceSize;
			uint32_t              maxBoundDescriptorSets;
			uint32_t              maxPerStageDescriptorSamplers;
			uint32_t              maxPerStageDescriptorUniformBuffers;
			uint32_t              maxPerStageDescriptorStorageBuffers;
			uint32_t              maxPerStageDescriptorSampledImages;
			uint32_t              maxPerStageDescriptorStorageImages;
			uint32_t              maxPerStageDescriptorInputAttachments;
			uint32_t              maxPerStageResources;
			uint32_t              maxDescriptorSetSamplers;
			uint32_t              maxDescriptorSetUniformBuffers;
			uint32_t              maxDescriptorSetUniformBuffersDynamic;
			uint32_t              maxDescriptorSetStorageBuffers;
			uint32_t              maxDescriptorSetStorageBuffersDynamic;
			uint32_t              maxDescriptorSetSampledImages;
			uint32_t              maxDescriptorSetStorageImages;
			uint32_t              maxDescriptorSetInputAttachments;
			uint32_t              maxVertexInputAttributes;
			uint32_t              maxVertexInputBindings;
			uint32_t              maxVertexInputAttributeOffset;
			uint32_t              maxVertexInputBindingStride;
			uint32_t              maxVertexOutputComponents;
			uint32_t              maxTessellationGenerationLevel;
			uint32_t              maxTessellationPatchSize;
			uint32_t              maxTessellationControlPerVertexInputComponents;
			uint32_t              maxTessellationControlPerVertexOutputComponents;
			uint32_t              maxTessellationControlPerPatchOutputComponents;
			uint32_t              maxTessellationControlTotalOutputComponents;
			uint32_t              maxTessellationEvaluationInputComponents;
			uint32_t              maxTessellationEvaluationOutputComponents;
			uint32_t              maxGeometryShaderInvocations;
			uint32_t              maxGeometryInputComponents;
			uint32_t              maxGeometryOutputComponents;
			uint32_t              maxGeometryOutputVertices;
			uint32_t              maxGeometryTotalOutputComponents;
			uint32_t              maxFragmentInputComponents;
			uint32_t              maxFragmentOutputAttachments;
			uint32_t              maxFragmentDualSrcAttachments;
			uint32_t              maxFragmentCombinedOutputResources;
			uint32_t              maxComputeSharedMemorySize;
			uint32_t              maxComputeWorkGroupCount[3];
			uint32_t              maxComputeWorkGroupInvocations;
			uint32_t              maxComputeWorkGroupSize[3];
			uint32_t              subPixelPrecisionBits;
			uint32_t              subTexelPrecisionBits;
			uint32_t              mipmapPrecisionBits;
			uint32_t              maxDrawIndexedIndexValue;
			uint32_t              maxDrawIndirectCount;
			float                 maxSamplerLodBias;
			float                 maxSamplerAnisotropy;
			uint32_t              maxViewports;
			uint32_t              maxViewportDimensions[2];
			float                 viewportBoundsRange[2];
			uint32_t              viewportSubPixelBits;
			size_t                minMemoryMapAlignment;
			LEDeviceSize          minTexelBufferOffsetAlignment;
			LEDeviceSize          minUniformBufferOffsetAlignment;
			LEDeviceSize          minStorageBufferOffsetAlignment;
			int32_t               minTexelOffset;
			uint32_t              maxTexelOffset;
			int32_t               minTexelGatherOffset;
			uint32_t              maxTexelGatherOffset;
			float                 minInterpolationOffset;
			float                 maxInterpolationOffset;
			uint32_t              subPixelInterpolationOffsetBits;
			uint32_t              maxFramebufferWidth;
			uint32_t              maxFramebufferHeight;
			uint32_t              maxFramebufferLayers;
			LESampleCountFlags    framebufferColorSampleCounts;
			LESampleCountFlags    framebufferDepthSampleCounts;
			LESampleCountFlags    framebufferStencilSampleCounts;
			LESampleCountFlags    framebufferNoAttachmentsSampleCounts;
			uint32_t              maxColorAttachments;
			LESampleCountFlags    sampledImageColorSampleCounts;
			LESampleCountFlags    sampledImageIntegerSampleCounts;
			LESampleCountFlags    sampledImageDepthSampleCounts;
			LESampleCountFlags    sampledImageStencilSampleCounts;
			LESampleCountFlags    storageImageSampleCounts;
			uint32_t              maxSampleMaskWords;
			LEBool32              timestampComputeAndGraphics;
			float                 timestampPeriod;
			uint32_t              maxClipDistances;
			uint32_t              maxCullDistances;
			uint32_t              maxCombinedClipAndCullDistances;
			uint32_t              discreteQueuePriorities;
			float                 pointSizeRange[2];
			float                 lineWidthRange[2];
			float                 pointSizeGranularity;
			float                 lineWidthGranularity;
			LEBool32              strictLines;
			LEBool32              standardSampleLocations;
			LEDeviceSize          optimalBufferCopyOffsetAlignment;
			LEDeviceSize          optimalBufferCopyRowPitchAlignment;
			LEDeviceSize          nonCoherentAtomSize;
		} LEPhysicalDeviceLimits;

		typedef struct LEPhysicalDeviceSparseProperties {
			LEBool32    residencyStandard2DBlockShape;
			LEBool32    residencyStandard2DMultisampleBlockShape;
			LEBool32    residencyStandard3DBlockShape;
			LEBool32    residencyAlignedMipSize;
			LEBool32    residencyNonResidentStrict;
		} LEPhysicalDeviceSparseProperties;


		typedef struct LEQueueFamilyProperties {
			///LEQueueFlags    queueFlags;
			uint32_t        queueCount;
			uint32_t        timestampValidBits;
			LEExtent3D      minImageTransferGranularity;
		} LEQueueFamilyProperties;


		typedef LEFlags LEDeviceQueueCreateFlags;

		//typedef void (LEAPI_PTR *PFN_vkVoidFunction)(void);
		typedef struct LEDeviceQueueCreateInfo {
			//LEStructureType             sType;
			const void*                 pNext;
			LEDeviceQueueCreateFlags    flags;
			uint32_t                    queueFamilyIndex;
			uint32_t                    queueCount;
			const float*                pQueuePriorities;
		} LEDeviceQueueCreateInfo;
			

		typedef union LEClearColorValue {
			float       float32[4];
			int32_t     int32[4];
			uint32_t    uint32[4];
		} LEClearColorValue;

		typedef struct LEClearDepthStencilValue {
			float       depth;
			uint32_t    stencil;
		} LEClearDepthStencilValue;

		typedef union LEClearValue {
			LEClearColorValue           color;
			LEClearDepthStencilValue    depthStencil;
		} LEClearValue;

		typedef struct LEClearAttachment {
			LEImageAspectFlags    aspectMask;
			uint32_t              colorAttachment;
			LEClearValue          clearValue;
		} LEClearAttachment;

			   
		typedef struct LEDispatchIndirectCommand {
			uint32_t    x;
			uint32_t    y;
			uint32_t    z;
		} LEDispatchIndirectCommand;

		typedef struct LEDrawIndexedIndirectCommand {
			uint32_t    indexCount;
			uint32_t    instanceCount;
			uint32_t    firstIndex;
			int32_t     vertexOffset;
			uint32_t    firstInstance;
		} LEDrawIndexedIndirectCommand;

		typedef struct LEDrawIndirectCommand {
			uint32_t    vertexCount;
			uint32_t    instanceCount;
			uint32_t    firstVertex;
			uint32_t    firstInstance;
		} LEDrawIndirectCommand;




		//#endif

		//必须struct
		//#if(1)
		//
		//
		//#endif


		/**
		 * The RHI's feature level indicates what level of support can be relied upon.
		 * Note: these are named after graphics API's like ES2 but a feature level can be used with a different API (eg ERHIFeatureLevel::ES2 on D3D11)
		 * As long as the graphics API supports all the features of the feature level (eg no ERHIFeatureLevel::SM5 on OpenGL ES2)
		 */
		namespace ERHIFeatureLevel
		{
			enum Type
			{
				/** Feature level defined by the core capabilities of OpenGL ES2. */
				ES2,
				/** Feature level defined by the core capabilities of OpenGL ES3.1 & Metal/Vulkan. */
				ES3_1,
				/** Feature level defined by the capabilities of DX10 Shader Model 4. */
				SM4,
				/** Feature level defined by the capabilities of DX11 Shader Model 5. */
				SM5,
				Num
			};
		};

		/** @warning: update *LegacyShaderPlatform* when the below changes */
		enum EShaderPlatform
		{
			SP_PCD3D_SM5 = 0,
			SP_OPENGL_SM4 = 1,
			SP_PS4 = 2,
			/** Used when running in Feature Level ES2 in OpenGL. */
			SP_OPENGL_PCES2 = 3,
			SP_XBOXONE_D3D12 = 4,
			SP_PCD3D_SM4 = 5,
			SP_OPENGL_SM5 = 6,
			/** Used when running in Feature Level ES2 in D3D11. */
			SP_PCD3D_ES2 = 7,
			SP_OPENGL_ES2_ANDROID = 8,
			SP_OPENGL_ES2_WEBGL = 9,
			SP_OPENGL_ES2_IOS = 10,
			SP_METAL = 11,
			SP_METAL_MRT = 12,
			SP_OPENGL_ES31_EXT = 13,
			/** Used when running in Feature Level ES3_1 in D3D11. */
			SP_PCD3D_ES3_1 = 14,
			/** Used when running in Feature Level ES3_1 in OpenGL. */
			SP_OPENGL_PCES3_1 = 15,
			SP_METAL_SM5 = 16,
			SP_VULKAN_PCES3_1 = 17,
			SP_METAL_SM5_NOTESS = 18,
			SP_VULKAN_SM4 = 19,
			SP_VULKAN_SM5 = 20,
			SP_VULKAN_ES3_1_ANDROID = 21,
			SP_METAL_MACES3_1 = 22,
			SP_METAL_MACES2 = 23,
			SP_OPENGL_ES3_1_ANDROID = 24,
			SP_SWITCH = 25,
			SP_SWITCH_FORWARD = 26,
			SP_METAL_MRT_MAC = 27,

			SP_NumPlatforms = 28,
			SP_NumBits = 5,
		};
		static_assert(SP_NumPlatforms <= (1 << SP_NumBits), "SP_NumPlatforms will not fit on SP_NumBits");


	}
}

namespace le
{
	namespace rhi
	{


#if defined(PF_MAX)
#undef PF_MAX
#endif
#if 0
		enum class EPixelFormat
		{
			PF_FORMAT_UNDEFINED = 0,
			PF_FORMAT_R4G4_UNORM_PACK8 = 1,
			PF_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
			PF_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
			PF_FORMAT_R5G6B5_UNORM_PACK16 = 4,
			PF_FORMAT_B5G6R5_UNORM_PACK16 = 5,
			PF_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
			PF_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
			PF_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
			PF_FORMAT_R8_UNORM = 9,
			PF_FORMAT_R8_SNORM = 10,
			PF_FORMAT_R8_USCALED = 11,
			PF_FORMAT_R8_SSCALED = 12,
			PF_FORMAT_R8_UINT = 13,
			PF_FORMAT_R8_SINT = 14,
			PF_FORMAT_R8_SRGB = 15,
			PF_FORMAT_R8G8_UNORM = 16,
			PF_FORMAT_R8G8_SNORM = 17,
			PF_FORMAT_R8G8_USCALED = 18,
			PF_FORMAT_R8G8_SSCALED = 19,
			PF_FORMAT_R8G8_UINT = 20,
			PF_FORMAT_R8G8_SINT = 21,
			PF_FORMAT_R8G8_SRGB = 22,
			PF_FORMAT_R8G8B8_UNORM = 23,
			PF_FORMAT_R8G8B8_SNORM = 24,
			PF_FORMAT_R8G8B8_USCALED = 25,
			PF_FORMAT_R8G8B8_SSCALED = 26,
			PF_FORMAT_R8G8B8_UINT = 27,
			PF_FORMAT_R8G8B8_SINT = 28,
			PF_FORMAT_R8G8B8_SRGB = 29,
			PF_FORMAT_B8G8R8_UNORM = 30,
			PF_FORMAT_B8G8R8_SNORM = 31,
			PF_FORMAT_B8G8R8_USCALED = 32,
			PF_FORMAT_B8G8R8_SSCALED = 33,
			PF_FORMAT_B8G8R8_UINT = 34,
			PF_FORMAT_B8G8R8_SINT = 35,
			PF_FORMAT_B8G8R8_SRGB = 36,
			PF_FORMAT_R8G8B8A8_UNORM = 37,
			PF_FORMAT_R8G8B8A8_SNORM = 38,
			PF_FORMAT_R8G8B8A8_USCALED = 39,
			PF_FORMAT_R8G8B8A8_SSCALED = 40,
			PF_FORMAT_R8G8B8A8_UINT = 41,
			PF_FORMAT_R8G8B8A8_SINT = 42,
			PF_FORMAT_R8G8B8A8_SRGB = 43,
			PF_FORMAT_B8G8R8A8_UNORM = 44,
			PF_FORMAT_B8G8R8A8_SNORM = 45,
			PF_FORMAT_B8G8R8A8_USCALED = 46,
			PF_FORMAT_B8G8R8A8_SSCALED = 47,
			PF_FORMAT_B8G8R8A8_UINT = 48,
			PF_FORMAT_B8G8R8A8_SINT = 49,
			PF_FORMAT_B8G8R8A8_SRGB = 50,
			PF_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
			PF_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
			PF_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
			PF_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
			PF_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
			PF_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
			PF_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
			PF_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
			PF_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
			PF_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
			PF_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
			PF_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
			PF_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
			PF_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
			PF_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
			PF_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
			PF_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
			PF_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
			PF_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
			PF_FORMAT_R16_UNORM = 70,
			PF_FORMAT_R16_SNORM = 71,
			PF_FORMAT_R16_USCALED = 72,
			PF_FORMAT_R16_SSCALED = 73,
			PF_FORMAT_R16_UINT = 74,
			PF_FORMAT_R16_SINT = 75,
			PF_FORMAT_R16_SFLOAT = 76,
			PF_FORMAT_R16G16_UNORM = 77,
			PF_FORMAT_R16G16_SNORM = 78,
			PF_FORMAT_R16G16_USCALED = 79,
			PF_FORMAT_R16G16_SSCALED = 80,
			PF_FORMAT_R16G16_UINT = 81,
			PF_FORMAT_R16G16_SINT = 82,
			PF_FORMAT_R16G16_SFLOAT = 83,
			PF_FORMAT_R16G16B16_UNORM = 84,
			PF_FORMAT_R16G16B16_SNORM = 85,
			PF_FORMAT_R16G16B16_USCALED = 86,
			PF_FORMAT_R16G16B16_SSCALED = 87,
			PF_FORMAT_R16G16B16_UINT = 88,
			PF_FORMAT_R16G16B16_SINT = 89,
			PF_FORMAT_R16G16B16_SFLOAT = 90,
			PF_FORMAT_R16G16B16A16_UNORM = 91,
			PF_FORMAT_R16G16B16A16_SNORM = 92,
			PF_FORMAT_R16G16B16A16_USCALED = 93,
			PF_FORMAT_R16G16B16A16_SSCALED = 94,
			PF_FORMAT_R16G16B16A16_UINT = 95,
			PF_FORMAT_R16G16B16A16_SINT = 96,
			PF_FORMAT_R16G16B16A16_SFLOAT = 97,
			PF_FORMAT_R32_UINT = 98,
			PF_FORMAT_R32_SINT = 99,
			PF_FORMAT_R32_SFLOAT = 100,
			PF_FORMAT_R32G32_UINT = 101,
			PF_FORMAT_R32G32_SINT = 102,
			PF_FORMAT_R32G32_SFLOAT = 103,
			PF_FORMAT_R32G32B32_UINT = 104,
			PF_FORMAT_R32G32B32_SINT = 105,
			PF_FORMAT_R32G32B32_SFLOAT = 106,
			PF_FORMAT_R32G32B32A32_UINT = 107,
			PF_FORMAT_R32G32B32A32_SINT = 108,
			PF_FORMAT_R32G32B32A32_SFLOAT = 109,
			PF_FORMAT_R64_UINT = 110,
			PF_FORMAT_R64_SINT = 111,
			PF_FORMAT_R64_SFLOAT = 112,
			PF_FORMAT_R64G64_UINT = 113,
			PF_FORMAT_R64G64_SINT = 114,
			PF_FORMAT_R64G64_SFLOAT = 115,
			PF_FORMAT_R64G64B64_UINT = 116,
			PF_FORMAT_R64G64B64_SINT = 117,
			PF_FORMAT_R64G64B64_SFLOAT = 118,
			PF_FORMAT_R64G64B64A64_UINT = 119,
			PF_FORMAT_R64G64B64A64_SINT = 120,
			PF_FORMAT_R64G64B64A64_SFLOAT = 121,
			PF_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
			PF_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
			PF_FORMAT_D16_UNORM = 124,
			PF_FORMAT_X8_D24_UNORM_PACK32 = 125,
			PF_FORMAT_D32_SFLOAT = 126,
			PF_FORMAT_S8_UINT = 127,
			PF_FORMAT_D16_UNORM_S8_UINT = 128,
			PF_FORMAT_D24_UNORM_S8_UINT = 129,
			PF_FORMAT_D32_SFLOAT_S8_UINT = 130,
			PF_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
			PF_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
			PF_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
			PF_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
			PF_FORMAT_BC2_UNORM_BLOCK = 135,
			PF_FORMAT_BC2_SRGB_BLOCK = 136,
			PF_FORMAT_BC3_UNORM_BLOCK = 137,
			PF_FORMAT_BC3_SRGB_BLOCK = 138,
			PF_FORMAT_BC4_UNORM_BLOCK = 139,
			PF_FORMAT_BC4_SNORM_BLOCK = 140,
			PF_FORMAT_BC5_UNORM_BLOCK = 141,
			PF_FORMAT_BC5_SNORM_BLOCK = 142,
			PF_FORMAT_BC6H_UFLOAT_BLOCK = 143,
			PF_FORMAT_BC6H_SFLOAT_BLOCK = 144,
			PF_FORMAT_BC7_UNORM_BLOCK = 145,
			PF_FORMAT_BC7_SRGB_BLOCK = 146,
			PF_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
			PF_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
			PF_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
			PF_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
			PF_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
			PF_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
			PF_FORMAT_EAC_R11_UNORM_BLOCK = 153,
			PF_FORMAT_EAC_R11_SNORM_BLOCK = 154,
			PF_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
			PF_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
			PF_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
			PF_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
			PF_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
			PF_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
			PF_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
			PF_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
			PF_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
			PF_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
			PF_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
			PF_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
			PF_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
			PF_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
			PF_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
			PF_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
			PF_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
			PF_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
			PF_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
			PF_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
			PF_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
			PF_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
			PF_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
			PF_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
			PF_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
			PF_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
			PF_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
			PF_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
			PF_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
			PF_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
			PF_FORMAT_G8B8G8R8_422_UNORM = 1000156000,
			PF_FORMAT_B8G8R8G8_422_UNORM = 1000156001,
			PF_FORMAT_G8_B8_R8_3PLANE_420_UNORM = 1000156002,
			PF_FORMAT_G8_B8R8_2PLANE_420_UNORM = 1000156003,
			PF_FORMAT_G8_B8_R8_3PLANE_422_UNORM = 1000156004,
			PF_FORMAT_G8_B8R8_2PLANE_422_UNORM = 1000156005,
			PF_FORMAT_G8_B8_R8_3PLANE_444_UNORM = 1000156006,
			PF_FORMAT_R10X6_UNORM_PACK16 = 1000156007,
			PF_FORMAT_R10X6G10X6_UNORM_2PACK16 = 1000156008,
			PF_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 1000156009,
			PF_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 1000156010,
			PF_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 1000156011,
			PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012,
			PF_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 1000156013,
			PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014,
			PF_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 1000156015,
			PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016,
			PF_FORMAT_R12X4_UNORM_PACK16 = 1000156017,
			PF_FORMAT_R12X4G12X4_UNORM_2PACK16 = 1000156018,
			PF_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 1000156019,
			PF_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 1000156020,
			PF_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 1000156021,
			PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022,
			PF_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 1000156023,
			PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024,
			PF_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 1000156025,
			PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026,
			PF_FORMAT_G16B16G16R16_422_UNORM = 1000156027,
			PF_FORMAT_B16G16R16G16_422_UNORM = 1000156028,
			PF_FORMAT_G16_B16_R16_3PLANE_420_UNORM = 1000156029,
			PF_FORMAT_G16_B16R16_2PLANE_420_UNORM = 1000156030,
			PF_FORMAT_G16_B16_R16_3PLANE_422_UNORM = 1000156031,
			PF_FORMAT_G16_B16R16_2PLANE_422_UNORM = 1000156032,
			PF_FORMAT_G16_B16_R16_3PLANE_444_UNORM = 1000156033,
			PF_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG = 1000054000,
			PF_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG = 1000054001,
			PF_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG = 1000054002,
			PF_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG = 1000054003,
			PF_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG = 1000054004,
			PF_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG = 1000054005,
			PF_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG = 1000054006,
			PF_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG = 1000054007,
			PF_FORMAT_G8B8G8R8_422_UNORM_KHR = PF_FORMAT_G8B8G8R8_422_UNORM,
			PF_FORMAT_B8G8R8G8_422_UNORM_KHR = PF_FORMAT_B8G8R8G8_422_UNORM,
			PF_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR = PF_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
			PF_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR = PF_FORMAT_G8_B8R8_2PLANE_420_UNORM,
			PF_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR = PF_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
			PF_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR = PF_FORMAT_G8_B8R8_2PLANE_422_UNORM,
			PF_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR = PF_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
			PF_FORMAT_R10X6_UNORM_PACK16_KHR = PF_FORMAT_R10X6_UNORM_PACK16,
			PF_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR = PF_FORMAT_R10X6G10X6_UNORM_2PACK16,
			PF_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = PF_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
			PF_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = PF_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
			PF_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = PF_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
			PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
			PF_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = PF_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
			PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
			PF_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = PF_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
			PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = PF_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
			PF_FORMAT_R12X4_UNORM_PACK16_KHR = PF_FORMAT_R12X4_UNORM_PACK16,
			PF_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR = PF_FORMAT_R12X4G12X4_UNORM_2PACK16,
			PF_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = PF_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
			PF_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = PF_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
			PF_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = PF_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
			PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
			PF_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = PF_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
			PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
			PF_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = PF_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
			PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = PF_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
			PF_FORMAT_G16B16G16R16_422_UNORM_KHR = PF_FORMAT_G16B16G16R16_422_UNORM,
			PF_FORMAT_B16G16R16G16_422_UNORM_KHR = PF_FORMAT_B16G16R16G16_422_UNORM,
			PF_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR = PF_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
			PF_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR = PF_FORMAT_G16_B16R16_2PLANE_420_UNORM,
			PF_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR = PF_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
			PF_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR = PF_FORMAT_G16_B16R16_2PLANE_422_UNORM,
			PF_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR = PF_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
			PF_FORMAT_BEGIN_RANGE = PF_FORMAT_UNDEFINED,
			PF_FORMAT_END_RANGE = PF_FORMAT_ASTC_12x12_SRGB_BLOCK,
			PF_FORMAT_RANGE_SIZE = (PF_FORMAT_ASTC_12x12_SRGB_BLOCK - PF_FORMAT_UNDEFINED + 1),
			PF_FORMAT_MAX_ENUM = 0x7FFFFFFF
		};
#else
		enum EPixelFormat
		{
			PF_Unknown = 0,
			PF_A32B32G32R32F = 1,
			PF_B8G8R8A8 = 2,
			PF_G8 = 3,
			PF_G16 = 4,
			PF_DXT1 = 5,
			PF_DXT3 = 6,
			PF_DXT5 = 7,
			PF_UYVY = 8,
			PF_FloatRGB = 9,
			PF_FloatRGBA = 10,
			PF_DepthStencil = 11,
			PF_ShadowDepth = 12,
			PF_R32_FLOAT = 13,
			PF_G16R16 = 14,
			PF_G16R16F = 15,
			PF_G16R16F_FILTER = 16,
			PF_G32R32F = 17,
			PF_A2B10G10R10 = 18,
			PF_A16B16G16R16 = 19,
			PF_D24 = 20,
			PF_R16F = 21,
			PF_R16F_FILTER = 22,
			PF_BC5 = 23,
			PF_V8U8 = 24,
			PF_A1 = 25,
			PF_FloatR11G11B10 = 26,
			PF_A8 = 27,
			PF_R32_UINT = 28,
			PF_R32_SINT = 29,
			PF_PVRTC2 = 30,
			PF_PVRTC4 = 31,
			PF_R16_UINT = 32,
			PF_R16_SINT = 33,
			PF_R16G16B16A16_UINT = 34,
			PF_R16G16B16A16_SINT = 35,
			PF_R5G6B5_UNORM = 36,
			PF_R8G8B8A8 = 37,
			PF_A8R8G8B8 = 38,	// Only used for legacy loading; do NOT use!
			PF_BC4 = 39,
			PF_R8G8 = 40,
			PF_ATC_RGB = 41,
			PF_ATC_RGBA_E = 42,
			PF_ATC_RGBA_I = 43,
			PF_X24_G8 = 44,	// Used for creating SRVs to alias a DepthStencil buffer to read Stencil. Don't use for creating textures.
			PF_ETC1 = 45,
			PF_ETC2_RGB = 46,
			PF_ETC2_RGBA = 47,
			PF_R32G32B32A32_UINT = 48,
			PF_R16G16_UINT = 49,
			PF_ASTC_4x4 = 50,	// 8.00 bpp
			PF_ASTC_6x6 = 51,	// 3.56 bpp
			PF_ASTC_8x8 = 52,	// 2.00 bpp
			PF_ASTC_10x10 = 53,	// 1.28 bpp
			PF_ASTC_12x12 = 54,	// 0.89 bpp
			PF_BC6H = 55,
			PF_BC7 = 56,
			PF_R8_UINT = 57,
			PF_L8 = 58,
			PF_XGXR8 = 59,
			PF_R8G8B8A8_UINT = 60,
			PF_R8G8B8A8_SNORM = 61,
			PF_R16G16B16A16_UNORM = 62,
			PF_R16G16B16A16_SNORM = 63,
			PF_MAX = 64,
		};
#define FOREACH_ENUM_EPIXELFORMAT(op) \
	op(PF_Unknown) \
	op(PF_A32B32G32R32F) \
	op(PF_B8G8R8A8) \
	op(PF_G8) \
	op(PF_G16) \
	op(PF_DXT1) \
	op(PF_DXT3) \
	op(PF_DXT5) \
	op(PF_UYVY) \
	op(PF_FloatRGB) \
	op(PF_FloatRGBA) \
	op(PF_DepthStencil) \
	op(PF_ShadowDepth) \
	op(PF_R32_FLOAT) \
	op(PF_G16R16) \
	op(PF_G16R16F) \
	op(PF_G16R16F_FILTER) \
	op(PF_G32R32F) \
	op(PF_A2B10G10R10) \
	op(PF_A16B16G16R16) \
	op(PF_D24) \
	op(PF_R16F) \
	op(PF_R16F_FILTER) \
	op(PF_BC5) \
	op(PF_V8U8) \
	op(PF_A1) \
	op(PF_FloatR11G11B10) \
	op(PF_A8) \
	op(PF_R32_UINT) \
	op(PF_R32_SINT) \
	op(PF_PVRTC2) \
	op(PF_PVRTC4) \
	op(PF_R16_UINT) \
	op(PF_R16_SINT) \
	op(PF_R16G16B16A16_UINT) \
	op(PF_R16G16B16A16_SINT) \
	op(PF_R5G6B5_UNORM) \
	op(PF_R8G8B8A8) \
	op(PF_A8R8G8B8) \
	op(PF_BC4) \
	op(PF_R8G8) \
	op(PF_ATC_RGB) \
	op(PF_ATC_RGBA_E) \
	op(PF_ATC_RGBA_I) \
	op(PF_X24_G8) \
	op(PF_ETC1) \
	op(PF_ETC2_RGB) \
	op(PF_ETC2_RGBA) \
	op(PF_R32G32B32A32_UINT) \
	op(PF_R16G16_UINT) \
	op(PF_ASTC_4x4) \
	op(PF_ASTC_6x6) \
	op(PF_ASTC_8x8) \
	op(PF_ASTC_10x10) \
	op(PF_ASTC_12x12) \
	op(PF_BC6H) \
	op(PF_BC7) \
	op(PF_R8_UINT) \
	op(PF_R16G16B16A16_UNORM) \
	op(PF_R16G16B16A16_SNORM) \
	op(PF_L8)
	}
#endif
}

#endif //LE_RHI_ELEMENTFORMAT_H