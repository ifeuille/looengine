#ifndef LOO_FGVK_FG_ENUMS_H
#define LOO_FGVK_FG_ENUMS_H
#pragma once

#include "global/types.h"
#include "looreflect/looreflect.h"

namespace loo
{
	// 
	namespace vkfg
	{
		enum class LOOENUM ()ESwapchainImage :uint32
		{
			Primary LOOPROPERTY (Serialized),
			// for VR:
			LeftEye LOOPROPERTY (Serialized),
			RightEye LOOPROPERTY (Serialized),
		};
		enum class LOOENUM () EDebugFlags : uint
		{
			LogTasks LOOPROPERTY (Serialized) = 1 << 0,	// 
			LogBarriers LOOPROPERTY (Serialized) = 1 << 1,	//
			LogResourceUsage LOOPROPERTY (Serialized) = 1 << 2,	// 

			VisTasks LOOPROPERTY (Serialized) = 1 << 10,
			VisDrawTasks LOOPROPERTY (Serialized) = 1 << 11,
			VisResources LOOPROPERTY (Serialized) = 1 << 12,
			VisBarriers LOOPROPERTY (Serialized) = 1 << 13,
			VisBarrierLabels LOOPROPERTY (Serialized) = 1 << 14,
			VisTaskDependencies LOOPROPERTY (Serialized) = 1 << 15,

			/*LogUnreleasedResources			= 1 << 3,	//

			CheckNonOptimalLayouts			= 1 << 16,	// if used 'General' layout instead optimal layout.
			CheckWritingToImmutable			= 1 << 17,	// immutable resource supports only read access, immutable images must be in 'General' layout.

			CheckDiscardingResult			= 1 << 18,	// performance/logic warning, triggered if you write to image/buffer in one task,
														// then write to same region in next task that discarding previous result,
														// used for pattern: ReadWrite/WriteOnly -> WriteDiscard.
			CheckPossibleDiscardingResult	= 1 << 19,	// same as 'CheckDiscardingResult', used for pattern: ReadWrite -> WriteOnly.

			SuppressWarnings				= 1 << 30,	// debugger may generate warning messages in log, use this flag to disable warnings*/
			Unknown LOOPROPERTY (Serialized) = 0,

			Default LOOPROPERTY (Serialized) = LogTasks | LogBarriers | LogResourceUsage |
			VisTasks | VisDrawTasks | VisResources | VisBarriers,
		};
		LOO_BIT_OPERATORS (EDebugFlags);
		//using Flags< EDebugFlags> 
	}

	// resource enums
	namespace vkfg
	{

		enum class LOOENUM () EQueueType : uint
		{
			Graphics LOOPROPERTY (Serialized),			// also supports compute and transfer commands
			AsyncCompute LOOPROPERTY (Serialized),		// separate compute queue
			AsyncTransfer LOOPROPERTY (Serialized),		// separate transfer queue
			//Present LOOPROPERTY (Serialized),			// queue must support present, may be a separate queue
			_Count,
			Unknown = ~0u,
		};


		enum class LOOENUM () EQueueUsage : uint
		{
			Unknown  LOOPROPERTY (Serialized) = 0,
			Graphics  LOOPROPERTY (Serialized) = 1 << uint (EQueueType::Graphics),
			AsyncCompute  LOOPROPERTY (Serialized) = 1 << uint (EQueueType::AsyncCompute),
			AsyncTransfer  LOOPROPERTY (Serialized) = 1 << uint (EQueueType::AsyncTransfer),
			_end,
			_begin = Unknown,
			All = ((_end - 1) << 1) - 1,
		};
		LOO_BIT_OPERATORS (EQueueUsage);


		LOO_FORCEINLINE constexpr EQueueUsage&  operator |= (EQueueUsage &lhs, EQueueType rhs)
		{
			ASSERT (uint (rhs) < 32);
			return lhs = BitCast<EQueueUsage> (uint (lhs) | (1u << (uint (rhs) & 31)));
		}

		LOO_FORCEINLINE constexpr EQueueUsage   operator |  (EQueueUsage lhs, EQueueType rhs)
		{
			ASSERT (uint (rhs) < 32);
			return BitCast<EQueueUsage> (uint (lhs) | (1u << (uint (rhs) & 31)));
		}


		enum class LOOENUM () EMemoryType : uint
		{
			Default  LOOPROPERTY (Serialized) = 0,			// local in GPU
			HostRead  LOOPROPERTY (Serialized) = 1 << 0,
			HostWrite  LOOPROPERTY (Serialized) = 1 << 1,
			Dedicated  LOOPROPERTY (Serialized) = 1 << 2,		// force to use dedicated allocation
			AllowAliasing  LOOPROPERTY (Serialized) = 1 << 3,		// 
			Sparse  LOOPROPERTY (Serialized) = 1 << 4,
			_end,
			_begin = Default
		};
		LOO_BIT_OPERATORS (EMemoryType);


		enum class LOOENUM () EBufferUsage : uint
		{
			TransferSrc  LOOPROPERTY (Serialized) = 1 << 0,
			TransferDst  LOOPROPERTY (Serialized) = 1 << 1,
			UniformTexel  LOOPROPERTY (Serialized) = 1 << 2,
			StorageTexel  LOOPROPERTY (Serialized) = 1 << 3,
			Uniform  LOOPROPERTY (Serialized) = 1 << 4,
			Storage  LOOPROPERTY (Serialized) = 1 << 5,
			Index  LOOPROPERTY (Serialized) = 1 << 6,
			Vertex  LOOPROPERTY (Serialized) = 1 << 7,
			Indirect  LOOPROPERTY (Serialized) = 1 << 8,
			RayTracing  LOOPROPERTY (Serialized) = 1 << 9,
			_end,
			_begin = TransferSrc,

			All = ((_end - 1) << 1) - 1,
			Transfer = TransferDst | TransferSrc,
			Unknown = 0,
		};
		LOO_BIT_OPERATORS (EBufferUsage);


		enum class LOOENUM () EImage : uint
		{
			Tex1D  LOOPROPERTY (Serialized) = 0,
			Tex1DArray LOOPROPERTY (Serialized),
			Tex2D LOOPROPERTY (Serialized),
			Tex2DArray LOOPROPERTY (Serialized),
			Tex2DMS LOOPROPERTY (Serialized),
			Tex2DMSArray LOOPROPERTY (Serialized),
			TexCube LOOPROPERTY (Serialized),
			TexCubeArray LOOPROPERTY (Serialized),
			Tex3D LOOPROPERTY (Serialized),
			Buffer LOOPROPERTY (Serialized),
			Unknown  LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EImageUsage : uint
		{
			TransferSrc  LOOPROPERTY (Serialized) = 1 << 0,		// for all copy operations
			TransferDst  LOOPROPERTY (Serialized) = 1 << 1,		// for all copy operations
			Sampled  LOOPROPERTY (Serialized) = 1 << 2,		// access in shader as texture
			Storage LOOPROPERTY (Serialized) = 1 << 3,		// access in shader as image
			ColorAttachment  LOOPROPERTY (Serialized) = 1 << 4,		// color or resolve attachment
			DepthStencilAttachment LOOPROPERTY (Serialized) = 1 << 5,		// depth/stencil attachment
			TransientAttachment LOOPROPERTY (Serialized) = 1 << 6,		// color, resolve, depth/stencil, input attachment
			InputAttachment LOOPROPERTY (Serialized) = 1 << 7,		// input attachment in shader
			ShadingRate LOOPROPERTY (Serialized) = 1 << 8,
			_end,
			_begin = TransferSrc,

			All = ((_end - 1) << 1) - 1,
			Transfer LOOPROPERTY (Serialized) = TransferSrc | TransferDst,
			Unknown = 0,
		};
		LOO_BIT_OPERATORS (EImageUsage);


		enum class LOOENUM () EImageAspect : uint
		{
			Color LOOPROPERTY (Serialized) = 1 << 0,
			Depth LOOPROPERTY (Serialized) = 1 << 1,
			Stencil LOOPROPERTY (Serialized) = 1 << 2,
			Metadata LOOPROPERTY (Serialized) = 1 << 3,
			_end,
			_begin = Color,

			DepthStencil LOOPROPERTY (Serialized) = Depth | Stencil,
			Auto LOOPROPERTY (Serialized) = ~0u,
			Unknown LOOPROPERTY (Serialized) = 0,
		};
		LOO_BIT_OPERATORS (EImageAspect);


		enum class LOOENUM () EAttachmentLoadOp : uint
		{
			Invalidate LOOPROPERTY (Serialized),
			Load LOOPROPERTY (Serialized),
			Clear LOOPROPERTY (Serialized),
			Unknown  LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EAttachmentStoreOp : uint
		{
			Invalidate LOOPROPERTY (Serialized),
			Store LOOPROPERTY (Serialized),
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EShadingRatePalette : uint8_t
		{
			NoInvocations LOOPROPERTY (Serialized) = 0,
			Block_1x1_16 LOOPROPERTY (Serialized) = 1,	// 16 invocations per 1x1 pixel block
			Block_1x1_8 LOOPROPERTY (Serialized) = 2,	//  8 invocations per 1x1 pixel block
			Block_1x1_4 LOOPROPERTY (Serialized) = 3,	//  4 invocations per 1x1 pixel block
			Block_1x1_2 LOOPROPERTY (Serialized) = 4,	//  2 invocations per 1x1 pixel block
			Block_1x1_1 LOOPROPERTY (Serialized) = 5,	//  1 invocation  per 1x1 pixel block
			Block_2x1_1 LOOPROPERTY (Serialized) = 6,	//  1 invocation  per 2x1 pixel block
			Block_1x2_1 LOOPROPERTY (Serialized) = 7,	//  1 invocation  per 1x2 pixel block
			Block_2x2_1 LOOPROPERTY (Serialized) = 8,	//  1 invocation  per 2x2 pixel block
			Block_4x2_1 LOOPROPERTY (Serialized) = 9,	//  1 invocation  per 4x2 pixel block
			Block_2x4_1 LOOPROPERTY (Serialized) = 10,	//  1 invocation  per 2x4 pixel block
			Block_4x4_1 LOOPROPERTY (Serialized) = 11,	//  1 invocation  per 4x4 pixel block
			_Count,
		};


		enum class LOOENUM () EPixelFormat : uint
		{
			// signed normalized
			RGBA16_SNorm LOOPROPERTY (Serialized),
			RGBA8_SNorm LOOPROPERTY (Serialized),
			RGB16_SNorm LOOPROPERTY (Serialized),
			RGB8_SNorm LOOPROPERTY (Serialized),
			RG16_SNorm LOOPROPERTY (Serialized),
			RG8_SNorm LOOPROPERTY (Serialized),
			R16_SNorm LOOPROPERTY (Serialized),
			R8_SNorm LOOPROPERTY (Serialized),

			// unsigned normalized
			RGBA16_UNorm LOOPROPERTY (Serialized),
			RGBA8_UNorm LOOPROPERTY (Serialized),
			RGB16_UNorm LOOPROPERTY (Serialized),
			RGB8_UNorm LOOPROPERTY (Serialized),
			RG16_UNorm LOOPROPERTY (Serialized),
			RG8_UNorm LOOPROPERTY (Serialized),
			R16_UNorm LOOPROPERTY (Serialized),
			R8_UNorm LOOPROPERTY (Serialized),
			RGB10_A2_UNorm LOOPROPERTY (Serialized),
			RGBA4_UNorm LOOPROPERTY (Serialized),
			RGB5_A1_UNorm LOOPROPERTY (Serialized),
			RGB_5_6_5_UNorm LOOPROPERTY (Serialized),

			// BGRA
			BGR8_UNorm LOOPROPERTY (Serialized),
			BGRA8_UNorm LOOPROPERTY (Serialized),

			// sRGB
			sRGB8 LOOPROPERTY (Serialized),
			sRGB8_A8 LOOPROPERTY (Serialized),
			sBGR8 LOOPROPERTY (Serialized),
			sBGR8_A8 LOOPROPERTY (Serialized),

			// signed integer
			R8I LOOPROPERTY (Serialized),
			RG8I LOOPROPERTY (Serialized),
			RGB8I LOOPROPERTY (Serialized),
			RGBA8I LOOPROPERTY (Serialized),
			R16I LOOPROPERTY (Serialized),
			RG16I LOOPROPERTY (Serialized),
			RGB16I LOOPROPERTY (Serialized),
			RGBA16I LOOPROPERTY (Serialized),
			R32I LOOPROPERTY (Serialized),
			RG32I LOOPROPERTY (Serialized),
			RGB32I LOOPROPERTY (Serialized),
			RGBA32I LOOPROPERTY (Serialized),

			// unsigned integer
			R8U LOOPROPERTY (Serialized),
			RG8U LOOPROPERTY (Serialized),
			RGB8U LOOPROPERTY (Serialized),
			RGBA8U LOOPROPERTY (Serialized),
			R16U LOOPROPERTY (Serialized),
			RG16U LOOPROPERTY (Serialized),
			RGB16U LOOPROPERTY (Serialized),
			RGBA16U LOOPROPERTY (Serialized),
			R32U LOOPROPERTY (Serialized),
			RG32U LOOPROPERTY (Serialized),
			RGB32U LOOPROPERTY (Serialized),
			RGBA32U LOOPROPERTY (Serialized),
			RGB10_A2U LOOPROPERTY (Serialized),

			// float
			R16F LOOPROPERTY (Serialized),
			RG16F LOOPROPERTY (Serialized),
			RGB16F LOOPROPERTY (Serialized),
			RGBA16F LOOPROPERTY (Serialized),
			R32F LOOPROPERTY (Serialized),
			RG32F LOOPROPERTY (Serialized),
			RGB32F LOOPROPERTY (Serialized),
			RGBA32F LOOPROPERTY (Serialized),
			RGB_11_11_10F LOOPROPERTY (Serialized),

			// depth stencil
			Depth16 LOOPROPERTY (Serialized),
			Depth24 LOOPROPERTY (Serialized),
			Depth32F LOOPROPERTY (Serialized),
			Depth16_Stencil8 LOOPROPERTY (Serialized),
			Depth24_Stencil8 LOOPROPERTY (Serialized),
			Depth32F_Stencil8 LOOPROPERTY (Serialized),

			// compressed
			BC1_RGB8_UNorm LOOPROPERTY (Serialized),
			BC1_sRGB8_UNorm LOOPROPERTY (Serialized),
			BC1_RGB8_A1_UNorm LOOPROPERTY (Serialized),
			BC1_sRGB8_A1_UNorm LOOPROPERTY (Serialized),
			BC2_RGBA8_UNorm LOOPROPERTY (Serialized),
			BC3_RGBA8_UNorm LOOPROPERTY (Serialized),
			BC3_sRGB LOOPROPERTY (Serialized),
			BC4_RED8_SNorm LOOPROPERTY (Serialized),
			BC4_RED8_UNorm LOOPROPERTY (Serialized),
			BC5_RG8_SNorm LOOPROPERTY (Serialized),
			BC5_RG8_UNorm LOOPROPERTY (Serialized),
			BC7_RGBA8_UNorm LOOPROPERTY (Serialized),
			BC7_SRGB8_A8 LOOPROPERTY (Serialized),
			BC6H_RGB16F LOOPROPERTY (Serialized),
			BC6H_RGB16UF LOOPROPERTY (Serialized),
			ETC2_RGB8_UNorm LOOPROPERTY (Serialized),
			ECT2_SRGB8 LOOPROPERTY (Serialized),
			ETC2_RGB8_A1_UNorm LOOPROPERTY (Serialized),
			ETC2_SRGB8_A1 LOOPROPERTY (Serialized),
			ETC2_RGBA8_UNorm LOOPROPERTY (Serialized),
			ETC2_SRGB8_A8 LOOPROPERTY (Serialized),
			EAC_R11_SNorm LOOPROPERTY (Serialized),
			EAC_R11_UNorm LOOPROPERTY (Serialized),
			EAC_RG11_SNorm LOOPROPERTY (Serialized),
			EAC_RG11_UNorm LOOPROPERTY (Serialized),
			ASTC_RGBA_4x4 LOOPROPERTY (Serialized),
			ASTC_RGBA_5x4 LOOPROPERTY (Serialized),
			ASTC_RGBA_5x5 LOOPROPERTY (Serialized),
			ASTC_RGBA_6x5 LOOPROPERTY (Serialized),
			ASTC_RGBA_6x6 LOOPROPERTY (Serialized),
			ASTC_RGBA_8x5 LOOPROPERTY (Serialized),
			ASTC_RGBA_8x6 LOOPROPERTY (Serialized),
			ASTC_RGBA_8x8 LOOPROPERTY (Serialized),
			ASTC_RGBA_10x5 LOOPROPERTY (Serialized),
			ASTC_RGBA_10x6 LOOPROPERTY (Serialized),
			ASTC_RGBA_10x8 LOOPROPERTY (Serialized),
			ASTC_RGBA_10x10 LOOPROPERTY (Serialized),
			ASTC_RGBA_12x10 LOOPROPERTY (Serialized),
			ASTC_RGBA_12x12 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_4x4 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_5x4 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_5x5 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_6x5 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_6x6 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_8x5 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_8x6 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_8x8 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_10x5 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_10x6 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_10x8 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_10x10 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_12x10 LOOPROPERTY (Serialized),
			ASTC_SRGB8_A8_12x12 LOOPROPERTY (Serialized),

			_Count LOOPROPERTY (Serialized),
			Unknown  LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EFragOutput : uint
		{
			Unknown LOOPROPERTY (Serialized) = 0,
			Int4 LOOPROPERTY (Serialized) = uint (EPixelFormat::RGBA32I),
			UInt4 LOOPROPERTY (Serialized) = uint (EPixelFormat::RGBA32U),
			Float4 LOOPROPERTY (Serialized) = uint (EPixelFormat::RGBA32F),
		};


	}

	// sampler enums
	namespace vkfg
	{

		enum class LOOENUM () EFilter : uint
		{
			Nearest LOOPROPERTY (Serialized),
			Linear LOOPROPERTY (Serialized),

			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EMipmapFilter : uint
		{
			Nearest LOOPROPERTY (Serialized),
			Linear LOOPROPERTY (Serialized),

			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EAddressMode : uint
		{
			Repeat LOOPROPERTY (Serialized),
			MirrorRepeat LOOPROPERTY (Serialized),
			ClampToEdge LOOPROPERTY (Serialized),
			ClampToBorder LOOPROPERTY (Serialized),
			MirrorClampToEdge LOOPROPERTY (Serialized),

			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EBorderColor : uint
		{
			FloatTransparentBlack LOOPROPERTY (Serialized),
			FloatOpaqueBlack LOOPROPERTY (Serialized),
			FloatOpaqueWhite LOOPROPERTY (Serialized),

			IntTransparentBlack LOOPROPERTY (Serialized),
			IntOpaqueBlack LOOPROPERTY (Serialized),
			IntOpaqueWhite LOOPROPERTY (Serialized),

			Unknown LOOPROPERTY (Serialized) = ~0u,
		};

	}

	// shader enums
	namespace vkfg
	{

		enum class LOOENUM () EShader : uint
		{
			Vertex LOOPROPERTY (Serialized),
			TessControl LOOPROPERTY (Serialized),
			TessEvaluation LOOPROPERTY (Serialized),
			Geometry LOOPROPERTY (Serialized),
			Fragment LOOPROPERTY (Serialized),
			Compute LOOPROPERTY (Serialized),

			MeshTask LOOPROPERTY (Serialized),
			Mesh LOOPROPERTY (Serialized),

			RayGen LOOPROPERTY (Serialized),
			RayAnyHit LOOPROPERTY (Serialized),
			RayClosestHit LOOPROPERTY (Serialized),
			RayMiss LOOPROPERTY (Serialized),
			RayIntersection LOOPROPERTY (Serialized),
			RayCallable LOOPROPERTY (Serialized),

			_Count LOOPROPERTY (Serialized),
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EShaderStages : uint
		{
			Vertex LOOPROPERTY (Serialized) = 1 << uint (EShader::Vertex),
			TessControl LOOPROPERTY (Serialized) = 1 << uint (EShader::TessControl),
			TessEvaluation LOOPROPERTY (Serialized) = 1 << uint (EShader::TessEvaluation),
			Geometry LOOPROPERTY (Serialized) = 1 << uint (EShader::Geometry),
			Fragment LOOPROPERTY (Serialized) = 1 << uint (EShader::Fragment),
			Compute LOOPROPERTY (Serialized) = 1 << uint (EShader::Compute),
			MeshTask LOOPROPERTY (Serialized) = 1 << uint (EShader::MeshTask),
			Mesh LOOPROPERTY (Serialized) = 1 << uint (EShader::Mesh),
			RayGen LOOPROPERTY (Serialized) = 1 << uint (EShader::RayGen),
			RayAnyHit LOOPROPERTY (Serialized) = 1 << uint (EShader::RayAnyHit),
			RayClosestHit LOOPROPERTY (Serialized) = 1 << uint (EShader::RayClosestHit),
			RayMiss  LOOPROPERTY (Serialized) = 1 << uint (EShader::RayMiss),
			RayIntersection LOOPROPERTY (Serialized) = 1 << uint (EShader::RayIntersection),
			RayCallable LOOPROPERTY (Serialized) = 1 << uint (EShader::RayCallable),
			_end,
			_begin = Vertex,

			All LOOPROPERTY (Serialized) = ((_end - 1) << 1) - 1,
			AllGraphics LOOPROPERTY (Serialized) = Vertex | TessControl | TessEvaluation | Geometry | MeshTask | Mesh | Fragment,
			AllRayTracing LOOPROPERTY (Serialized) = RayGen | RayAnyHit | RayClosestHit | RayMiss | RayIntersection | RayCallable,
			Unknown LOOPROPERTY (Serialized) = 0,
		};
		LOO_BIT_OPERATORS (EShaderStages);

		ND_ LOO_FORCEINLINE EShaderStages  operator |  (EShaderStages lhs, EShader rhs) { return lhs | EShaderStages (1 << uint (rhs)); }
		LOO_FORCEINLINE EShaderStages  operator |= (EShaderStages &lhs, EShader rhs) { return (lhs |= EShaderStages (1 << uint (rhs))); }


		enum class LOOENUM () EShaderAccess : uint
		{
			ReadOnly LOOPROPERTY (Serialized),
			WriteOnly LOOPROPERTY (Serialized),
			WriteDiscard LOOPROPERTY (Serialized),	// (optimization) same as WriteOnly, but previous data will be discarded
			ReadWrite LOOPROPERTY (Serialized),
		};


		enum class LOOENUM () EShaderLangFormat : uint
		{
			// api
			_ApiOffset LOOPROPERTY (Serialized) = 18,
			_ApiMask LOOPROPERTY (Serialized) = 0xF << _ApiOffset,
			OpenGL LOOPROPERTY (Serialized) = 1 << _ApiOffset,
			OpenGLES LOOPROPERTY (Serialized) = 2 << _ApiOffset,
			DirectX LOOPROPERTY (Serialized) = 3 << _ApiOffset,
			OpenCL LOOPROPERTY (Serialized) = 4 << _ApiOffset,
			Vulkan LOOPROPERTY (Serialized) = 5 << _ApiOffset,
			Metal LOOPROPERTY (Serialized) = 6 << _ApiOffset,
			CUDA LOOPROPERTY (Serialized) = 7 << _ApiOffset,
			Software LOOPROPERTY (Serialized) = 8 << _ApiOffset,	// c++ shader for software renderer

			// version
			_VersionOffset LOOPROPERTY (Serialized) = 8,
			_VersionMask LOOPROPERTY (Serialized) = 0x3FF << _VersionOffset,
			OpenGL_330 LOOPROPERTY (Serialized) = (330 << _VersionOffset) | OpenGL,
			OpenGL_420 LOOPROPERTY (Serialized) = (420 << _VersionOffset) | OpenGL,
			OpenGL_430 LOOPROPERTY (Serialized) = (430 << _VersionOffset) | OpenGL,
			OpenGL_440 LOOPROPERTY (Serialized) = (440 << _VersionOffset) | OpenGL,
			OpenGL_450 LOOPROPERTY (Serialized) = (450 << _VersionOffset) | OpenGL,
			OpenGL_460 LOOPROPERTY (Serialized) = (460 << _VersionOffset) | OpenGL,
			OpenGLES_200 LOOPROPERTY (Serialized) = (200 << _VersionOffset) | OpenGLES,
			OpenGLES_300 LOOPROPERTY (Serialized) = (300 << _VersionOffset) | OpenGLES,
			OpenGLES_310 LOOPROPERTY (Serialized) = (310 << _VersionOffset) | OpenGLES,
			OpenGLES_320 LOOPROPERTY (Serialized) = (320 << _VersionOffset) | OpenGLES,
			DirectX_10 LOOPROPERTY (Serialized) = (100 << _VersionOffset) | DirectX,
			DirectX_11 LOOPROPERTY (Serialized) = (110 << _VersionOffset) | DirectX,
			DirectX_12 LOOPROPERTY (Serialized) = (120 << _VersionOffset) | DirectX,
			OpenCL_120 LOOPROPERTY (Serialized) = (120 << _VersionOffset) | OpenCL,
			OpenCL_200 LOOPROPERTY (Serialized) = (200 << _VersionOffset) | OpenCL,
			OpenCL_210 LOOPROPERTY (Serialized) = (210 << _VersionOffset) | OpenCL,
			Vulkan_100 LOOPROPERTY (Serialized) = (100 << _VersionOffset) | Vulkan,
			Vulkan_110 LOOPROPERTY (Serialized) = (110 << _VersionOffset) | Vulkan,
			Software_100 LOOPROPERTY (Serialized) = (100 << _VersionOffset) | Software,

			// storage
			_StorageOffset LOOPROPERTY (Serialized) = 4,
			_StorageMask LOOPROPERTY (Serialized) = 0xF << _StorageOffset,
			Source LOOPROPERTY (Serialized) = 1 << _StorageOffset,
			Binary LOOPROPERTY (Serialized) = 2 << _StorageOffset,					// compiled program (HLSL bytecode, SPIRV)
			Executable LOOPROPERTY (Serialized) = 3 << _StorageOffset,					// compiled program (exe, dll, so, ...)

			// format
			_FormatOffset LOOPROPERTY (Serialized) = 0,
			_FormatMask LOOPROPERTY (Serialized) = 0xF << _FormatOffset,
			HighLevel LOOPROPERTY (Serialized) = (1 << _FormatOffset) | Source,		// GLSL, HLSL, CL
			SPIRV LOOPROPERTY (Serialized) = (2 << _FormatOffset) | Binary,
			GL_Binary LOOPROPERTY (Serialized) = (3 << _FormatOffset) | Binary,		// vendor specific
			DXBC  LOOPROPERTY (Serialized) = (4 << _FormatOffset) | Binary,		// HLSL bytecode
			DXIL LOOPROPERTY (Serialized) = (5 << _FormatOffset) | Binary,		// HLSL IL
			Assembler LOOPROPERTY (Serialized) = (6 << _FormatOffset) | Source,
			Invocable LOOPROPERTY (Serialized) = (7 << _FormatOffset) | Executable,	// function pointer
			ShaderModule LOOPROPERTY (Serialized) = (8 << _FormatOffset) | Executable,	// vkShaderModule, GLuint, ...

			// debug/profiling mode
			_ModeOffset LOOPROPERTY (Serialized) = 22,
			_ModeMask LOOPROPERTY (Serialized) = 0xF << _ModeOffset,
			EnableDebugTrace LOOPROPERTY (Serialized) = 1 << _ModeOffset,		// writes trace only for selected shader invocation (may be very slow)
			//EnableDebugAsserts LOOPROPERTY (Serialized)	= 2 << _ModeOffset,		// TODO: writes only shader unique invocation id in which assert was trigged
			//EnableDebugView LOOPROPERTY (Serialized)		= 3 << _ModeOffset,		// TODO: if assertion failed then writes specified value in separate image
			//EnableProfiling LOOPROPERTY (Serialized)		= 4 << _ModeOffset,		// TODO: use 'subgroupBallot' and 'timeAMD' to profile shaders
			//EnableInstrCounter LOOPROPERTY (Serialized)	= 5 << _ModeOffset,		// TODO: writes count of instruction in shader invocation

			// independent flags
			_FlagsOffset LOOPROPERTY (Serialized) = 26,
			_FlagsMask LOOPROPERTY (Serialized) = 0xF << _FlagsOffset,
			HasInputAttachment LOOPROPERTY (Serialized) = 1 << _FlagsOffset,	// if shader contains input attachment then may be generated 2 shaders:
														// 1. keep input attachments and add flag 'HasInputAttachment'.
														// 2. replaces attachments by sampler2D and texelFetch function.

			Unknown LOOPROPERTY (Serialized) = 0,

			// combined masks
			_StorageFormatMask LOOPROPERTY (Serialized) = _StorageMask | _FormatMask,
			_ApiStorageFormatMask LOOPROPERTY (Serialized) = _ApiMask | _StorageMask | _FormatMask,
			_ApiVersionMask LOOPROPERTY (Serialized) = _ApiMask | _VersionMask,
			_VersionModeFlagsMask LOOPROPERTY (Serialized) = _VersionMask | _ModeMask | _FlagsMask,

			// default
			GLSL_440  LOOPROPERTY (Serialized) = OpenGL_440 | HighLevel,
			GLSL_450 LOOPROPERTY (Serialized) = OpenGL_450 | HighLevel,
			GLSL_460 LOOPROPERTY (Serialized) = OpenGL_460 | HighLevel,
			VKSL_100 LOOPROPERTY (Serialized) = Vulkan_100 | HighLevel,
			VKSL_110 LOOPROPERTY (Serialized) = Vulkan_110 | HighLevel,
			SPIRV_100  LOOPROPERTY (Serialized) = Vulkan_100 | SPIRV,
			SPIRV_110 LOOPROPERTY (Serialized) = Vulkan_110 | SPIRV,
			VkShader_100 LOOPROPERTY (Serialized) = Vulkan_100 | ShaderModule,
			VkShader_110 LOOPROPERTY (Serialized) = Vulkan_110 | ShaderModule,
		};
		LOO_BIT_OPERATORS (EShaderLangFormat);


		enum class LOOENUM () EShaderDebugMode : uint
		{
			None LOOPROPERTY (Serialized) = 0,
			Trace LOOPROPERTY (Serialized),
			Asserts LOOPROPERTY (Serialized),
			View LOOPROPERTY (Serialized),
			InstructionCounter LOOPROPERTY (Serialized),
			Unknown LOOPROPERTY (Serialized) = None,
		};


	}

	// vertex enums
	namespace vkfg
	{
		enum class LOOENUM () EVertexType : uint
		{
			// vector size
			_VecOffset LOOPROPERTY (Serialized) = 0,
			_Vec1 LOOPROPERTY (Serialized) = 1 << _VecOffset,
			_Vec2 LOOPROPERTY (Serialized) = 2 << _VecOffset,
			_Vec3 LOOPROPERTY (Serialized) = 3 << _VecOffset,
			_Vec4 LOOPROPERTY (Serialized) = 4 << _VecOffset,
			_VecMask LOOPROPERTY (Serialized) = 0xF << _VecOffset,

			// type
			_TypeOffset LOOPROPERTY (Serialized) = 8,
			_Byte LOOPROPERTY (Serialized) = 1 << _TypeOffset,
			_UByte LOOPROPERTY (Serialized) = 2 << _TypeOffset,
			_Short LOOPROPERTY (Serialized) = 3 << _TypeOffset,
			_UShort LOOPROPERTY (Serialized) = 4 << _TypeOffset,
			_Int LOOPROPERTY (Serialized) = 5 << _TypeOffset,
			_UInt LOOPROPERTY (Serialized) = 6 << _TypeOffset,
			_Long LOOPROPERTY (Serialized) = 7 << _TypeOffset,
			_ULong LOOPROPERTY (Serialized) = 8 << _TypeOffset,
			_Half LOOPROPERTY (Serialized) = 9 << _TypeOffset,
			_Float LOOPROPERTY (Serialized) = 10 << _TypeOffset,
			_Double LOOPROPERTY (Serialized) = 11 << _TypeOffset,
			_TypeMask LOOPROPERTY (Serialized) = 0xF << _TypeOffset,

			// flags
			_FlagsOffset LOOPROPERTY (Serialized) = 16,
			NormalizedFlag LOOPROPERTY (Serialized) = 1 << _FlagsOffset,	// convert integer to normalized float value (-1..+1)
			ScaledFlag LOOPROPERTY (Serialized) = 2 << _FlagsOffset,	// convert integer to float value (min..max)


			// default types
			Byte LOOPROPERTY (Serialized) = _Byte | _Vec1,
			Byte2 LOOPROPERTY (Serialized) = _Byte | _Vec2,
			Byte3 LOOPROPERTY (Serialized) = _Byte | _Vec3,
			Byte4 LOOPROPERTY (Serialized) = _Byte | _Vec4,

			Byte_Norm LOOPROPERTY (Serialized) = Byte | NormalizedFlag,
			Byte2_Norm LOOPROPERTY (Serialized) = Byte2 | NormalizedFlag,
			Byte3_Norm LOOPROPERTY (Serialized) = Byte3 | NormalizedFlag,
			Byte4_Norm LOOPROPERTY (Serialized) = Byte4 | NormalizedFlag,

			Byte_Scaled LOOPROPERTY (Serialized) = Byte | ScaledFlag,
			Byte2_Scaled LOOPROPERTY (Serialized) = Byte2 | ScaledFlag,
			Byte3_Scaled LOOPROPERTY (Serialized) = Byte3 | ScaledFlag,
			Byte4_Scaled LOOPROPERTY (Serialized) = Byte4 | ScaledFlag,

			UByte LOOPROPERTY (Serialized) = _UByte | _Vec1,
			UByte2 LOOPROPERTY (Serialized) = _UByte | _Vec2,
			UByte3 LOOPROPERTY (Serialized) = _UByte | _Vec3,
			UByte4 LOOPROPERTY (Serialized) = _UByte | _Vec4,

			UByte_Norm LOOPROPERTY (Serialized) = UByte | NormalizedFlag,
			UByte2_Norm LOOPROPERTY (Serialized) = UByte2 | NormalizedFlag,
			UByte3_Norm LOOPROPERTY (Serialized) = UByte3 | NormalizedFlag,
			UByte4_Norm LOOPROPERTY (Serialized) = UByte4 | NormalizedFlag,

			UByte_Scaled LOOPROPERTY (Serialized) = UByte | ScaledFlag,
			UByte2_Scaled LOOPROPERTY (Serialized) = UByte2 | ScaledFlag,
			UByte3_Scaled LOOPROPERTY (Serialized) = UByte3 | ScaledFlag,
			UByte4_Scaled LOOPROPERTY (Serialized) = UByte4 | ScaledFlag,

			Short LOOPROPERTY (Serialized) = _Short | _Vec1,
			Short2 LOOPROPERTY (Serialized) = _Short | _Vec2,
			Short3 LOOPROPERTY (Serialized) = _Short | _Vec3,
			Short4 LOOPROPERTY (Serialized) = _Short | _Vec4,

			Short_Norm LOOPROPERTY (Serialized) = Short | NormalizedFlag,
			Short2_Norm LOOPROPERTY (Serialized) = Short2 | NormalizedFlag,
			Short3_Norm LOOPROPERTY (Serialized) = Short3 | NormalizedFlag,
			Short4_Norm LOOPROPERTY (Serialized) = Short4 | NormalizedFlag,

			Short_Scaled LOOPROPERTY (Serialized) = Short | ScaledFlag,
			Short2_Scaled LOOPROPERTY (Serialized) = Short2 | ScaledFlag,
			Short3_Scaled LOOPROPERTY (Serialized) = Short3 | ScaledFlag,
			Short4_Scaled LOOPROPERTY (Serialized) = Short4 | ScaledFlag,

			UShort LOOPROPERTY (Serialized) = _UShort | _Vec1,
			UShort2 LOOPROPERTY (Serialized) = _UShort | _Vec2,
			UShort3 LOOPROPERTY (Serialized) = _UShort | _Vec3,
			UShort4 LOOPROPERTY (Serialized) = _UShort | _Vec4,

			UShort_Norm LOOPROPERTY (Serialized) = UShort | NormalizedFlag,
			UShort2_Norm LOOPROPERTY (Serialized) = UShort2 | NormalizedFlag,
			UShort3_Norm LOOPROPERTY (Serialized) = UShort3 | NormalizedFlag,
			UShort4_Norm LOOPROPERTY (Serialized) = UShort4 | NormalizedFlag,

			UShort_Scaled LOOPROPERTY (Serialized) = UShort | ScaledFlag,
			UShort2_Scaled LOOPROPERTY (Serialized) = UShort2 | ScaledFlag,
			UShort3_Scaled LOOPROPERTY (Serialized) = UShort3 | ScaledFlag,
			UShort4_Scaled LOOPROPERTY (Serialized) = UShort4 | ScaledFlag,

			Int LOOPROPERTY (Serialized) = _Int | _Vec1,
			Int2 LOOPROPERTY (Serialized) = _Int | _Vec2,
			Int3 LOOPROPERTY (Serialized) = _Int | _Vec3,
			Int4 LOOPROPERTY (Serialized) = _Int | _Vec4,

			UInt LOOPROPERTY (Serialized) = _UInt | _Vec1,
			UInt2 LOOPROPERTY (Serialized) = _UInt | _Vec2,
			UInt3 LOOPROPERTY (Serialized) = _UInt | _Vec3,
			UInt4 LOOPROPERTY (Serialized) = _UInt | _Vec4,

			Long LOOPROPERTY (Serialized) = _Long | _Vec1,
			Long2 LOOPROPERTY (Serialized) = _Long | _Vec2,
			Long3 LOOPROPERTY (Serialized) = _Long | _Vec3,
			Long4 LOOPROPERTY (Serialized) = _Long | _Vec4,

			ULong LOOPROPERTY (Serialized) = _ULong | _Vec1,
			ULong2 LOOPROPERTY (Serialized) = _ULong | _Vec2,
			ULong3 LOOPROPERTY (Serialized) = _ULong | _Vec3,
			ULong4 LOOPROPERTY (Serialized) = _ULong | _Vec4,

			Half LOOPROPERTY (Serialized) = _Half | _Vec1,
			Half2 LOOPROPERTY (Serialized) = _Half | _Vec2,
			Half3 LOOPROPERTY (Serialized) = _Half | _Vec3,
			Half4 LOOPROPERTY (Serialized) = _Half | _Vec4,

			Float LOOPROPERTY (Serialized) = _Float | _Vec1,
			Float2 LOOPROPERTY (Serialized) = _Float | _Vec2,
			Float3 LOOPROPERTY (Serialized) = _Float | _Vec3,
			Float4 LOOPROPERTY (Serialized) = _Float | _Vec4,

			Double LOOPROPERTY (Serialized) = _Double | _Vec1,
			Double2 LOOPROPERTY (Serialized) = _Double | _Vec2,
			Double3 LOOPROPERTY (Serialized) = _Double | _Vec3,
			Double4 LOOPROPERTY (Serialized) = _Double | _Vec4,

			Unknown LOOPROPERTY (Serialized) = 0,
		};
		LOO_BIT_OPERATORS (EVertexType);


		enum class LOOENUM () EVertexInputRate : uint
		{
			Vertex LOOPROPERTY (Serialized),
			Instance LOOPROPERTY (Serialized),
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EIndex : uint
		{
			UShort LOOPROPERTY (Serialized),
			UInt LOOPROPERTY (Serialized),
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};

	}

	// render state enums
	namespace vkfg
	{

		enum class LOOENUM () EBlendFactor : uint
		{
			// result = srcColor * srcBlend [blendOp] dstColor * dstBlend;
			Zero LOOPROPERTY (Serialized),						// 0
			One LOOPROPERTY (Serialized),						// 1
			SrcColor LOOPROPERTY (Serialized),					// src
			OneMinusSrcColor LOOPROPERTY (Serialized),			// 1 - src
			DstColor LOOPROPERTY (Serialized),					// dst
			OneMinusDstColor LOOPROPERTY (Serialized),			// 1 - dst
			SrcAlpha LOOPROPERTY (Serialized),					// src.a
			OneMinusSrcAlpha LOOPROPERTY (Serialized),			// 1 - src.a
			DstAlpha LOOPROPERTY (Serialized),					// dst.a
			OneMinusDstAlpha LOOPROPERTY (Serialized),			// 1 - dst.a
			ConstColor LOOPROPERTY (Serialized),					// cc
			OneMinusConstColor LOOPROPERTY (Serialized),			// 1 - cc
			ConstAlpha LOOPROPERTY (Serialized),					// cc.a
			OneMinusConstAlpha LOOPROPERTY (Serialized),			// 1 - cc.a
			SrcAlphaSaturate LOOPROPERTY (Serialized),			// rgb * min( src.a, dst.a ), a * 1

			Src1Color LOOPROPERTY (Serialized),					// 
			OneMinusSrc1Color LOOPROPERTY (Serialized),			// 
			Src1Alpha LOOPROPERTY (Serialized),					// 
			OneMinusSrc1Alpha LOOPROPERTY (Serialized),			// 

			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EBlendOp : uint
		{
			// result = srcColor * srcBlend [blendOp] dstColor * dstBlend;
			Add LOOPROPERTY (Serialized),			// S+D
			Sub LOOPROPERTY (Serialized),			// S-D
			RevSub LOOPROPERTY (Serialized),			// D-S
			Min LOOPROPERTY (Serialized),			// min(S,D)
			Max LOOPROPERTY (Serialized),			// max(S,D)
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () ELogicOp : uint
		{
			None LOOPROPERTY (Serialized),				// disabled
			Clear LOOPROPERTY (Serialized),				// 0
			Set LOOPROPERTY (Serialized),				// 1
			Copy LOOPROPERTY (Serialized),				// S
			CopyInverted LOOPROPERTY (Serialized),		// ~S
			NoOp LOOPROPERTY (Serialized),				// D
			Invert LOOPROPERTY (Serialized),				// ~D
			And LOOPROPERTY (Serialized),				// S & D
			NotAnd LOOPROPERTY (Serialized),				// ~ ( S & D )
			Or LOOPROPERTY (Serialized),					// S | D
			NotOr LOOPROPERTY (Serialized),				// ~ ( S | D )
			Xor LOOPROPERTY (Serialized),				// S ^ D
			Equiv LOOPROPERTY (Serialized),				// ~ ( S ^ D )
			AndReverse LOOPROPERTY (Serialized),			// S & ~D
			AndInverted LOOPROPERTY (Serialized),		// ~S & D
			OrReverse LOOPROPERTY (Serialized),			// S | ~D
			OrInverted LOOPROPERTY (Serialized),			// ~S | D
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () ECompareOp : uint8_t
		{
			Never LOOPROPERTY (Serialized),			// false
			Less LOOPROPERTY (Serialized),			// <
			Equal LOOPROPERTY (Serialized),			// ==
			LEqual LOOPROPERTY (Serialized),			// <=
			Greater LOOPROPERTY (Serialized),		// >
			NotEqual LOOPROPERTY (Serialized),		// !=
			GEqual LOOPROPERTY (Serialized),			// >=
			Always LOOPROPERTY (Serialized),			// true
			Unknown LOOPROPERTY (Serialized) = uint8_t (~0),
		};


		enum class LOOENUM () EStencilOp : uint8_t
		{
			Keep LOOPROPERTY (Serialized),			// s
			Zero LOOPROPERTY (Serialized),			// 0
			Replace LOOPROPERTY (Serialized),		// ref
			Incr LOOPROPERTY (Serialized),			// min( ++s, 0 )
			IncrWrap LOOPROPERTY (Serialized),		// ++s & maxvalue
			Decr LOOPROPERTY (Serialized),			// max( --s, 0 )
			DecrWrap LOOPROPERTY (Serialized),		// --s & maxvalue
			Invert LOOPROPERTY (Serialized),			// ~s
			Unknown LOOPROPERTY (Serialized) = uint8_t (~0),
		};


		enum class LOOENUM () EPolygonMode : uint
		{
			Point LOOPROPERTY (Serialized),
			Line LOOPROPERTY (Serialized),
			Fill LOOPROPERTY (Serialized),
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () EPrimitive : uint
		{
			Point LOOPROPERTY (Serialized),

			LineList LOOPROPERTY (Serialized),
			LineStrip LOOPROPERTY (Serialized),
			LineListAdjacency LOOPROPERTY (Serialized),
			LineStripAdjacency LOOPROPERTY (Serialized),

			TriangleList LOOPROPERTY (Serialized),
			TriangleStrip LOOPROPERTY (Serialized),
			TriangleFan LOOPROPERTY (Serialized),
			TriangleListAdjacency LOOPROPERTY (Serialized),
			TriangleStripAdjacency LOOPROPERTY (Serialized),

			Patch LOOPROPERTY (Serialized),

			_Count,
			Unknown LOOPROPERTY (Serialized) = ~0u,
		};


		enum class LOOENUM () ECullMode : uint8_t
		{
			None LOOPROPERTY (Serialized) = 0,
			Front  LOOPROPERTY (Serialized) = 1 << 0,
			Back LOOPROPERTY (Serialized) = 1 << 1,
			FontAndBack LOOPROPERTY (Serialized) = Front | Back,
			Unknown LOOPROPERTY (Serialized) = None,
		};
		LOO_BIT_OPERATORS (ECullMode);


		enum class LOOENUM () EPipelineDynamicState : uint8_t
		{
			Unknown LOOPROPERTY (Serialized) = 0,
			Viewport LOOPROPERTY (Serialized) = 1 << 0,
			Scissor LOOPROPERTY (Serialized) = 1 << 1,
			StencilCompareMask LOOPROPERTY (Serialized) = 1 << 2,
			StencilWriteMask LOOPROPERTY (Serialized) = 1 << 3,
			StencilReference LOOPROPERTY (Serialized) = 1 << 4,
			ShadingRatePalette LOOPROPERTY (Serialized) = 1 << 5,
			_end,
			_begin = Unknown,

			All LOOPROPERTY (Serialized) = ((_end - 1) << 1) - 1,
			RasterizerMask LOOPROPERTY (Serialized) = All,
			Default LOOPROPERTY (Serialized) = Viewport | Scissor,
		};
		LOO_BIT_OPERATORS (EPipelineDynamicState);


	}	// loo
	
	// resource state
	namespace vkfg
	{

		//
		// Resource State
		//
		enum class LOOENUM () EResourceState : uint
		{
			Unknown LOOPROPERTY (Serialized) = 0,

			// memory access
			_Access_ShaderStorage LOOPROPERTY (Serialized),				// uniform buffer, storage buffer, image storage
			_Access_Uniform LOOPROPERTY (Serialized),					// uniform buffer only
			_Access_ShaderSample LOOPROPERTY (Serialized),				// texture only
			_Access_InputAttachment LOOPROPERTY (Serialized),			// same as ShaderRead
			_Access_Transfer LOOPROPERTY (Serialized),					// copy buffer/image
			_Access_ColorAttachment LOOPROPERTY (Serialized),			// color render target
			_Access_DepthStencilAttachment LOOPROPERTY (Serialized),		// depth/stencil write/test
			_Access_Host LOOPROPERTY (Serialized),						// resource mapping
			_Access_Present LOOPROPERTY (Serialized),					// image only
			_Access_IndirectBuffer LOOPROPERTY (Serialized),
			_Access_IndexBuffer LOOPROPERTY (Serialized),
			_Access_VertexBuffer LOOPROPERTY (Serialized),
			_Access_ConditionalRendering LOOPROPERTY (Serialized),
			_Access_CommandProcess LOOPROPERTY (Serialized),
			_Access_ShadingRateImage LOOPROPERTY (Serialized),
			_Access_BuildRayTracingAS LOOPROPERTY (Serialized),			// build/update acceleration structure for ray tracing
			_Access_RTASBuildingBuffer LOOPROPERTY (Serialized),			// vertex, index, ..., scratch buffer that used when build/update acceleration structure
			_AccessLast LOOPROPERTY (Serialized),
			_AccessMask LOOPROPERTY (Serialized) = (1 << 8) - 1,

			// shader stages
			_VertexShader LOOPROPERTY (Serialized) = 1 << 8,
			_TessControlShader LOOPROPERTY (Serialized) = 1 << 9,
			_TessEvaluationShader LOOPROPERTY (Serialized) = 1 << 10,
			_GeometryShader LOOPROPERTY (Serialized) = 1 << 11,
			_FragmentShader LOOPROPERTY (Serialized) = 1 << 12,
			_ComputeShader LOOPROPERTY (Serialized) = 1 << 13,
			_MeshTaskShader LOOPROPERTY (Serialized) = 1 << 14,
			_MeshShader LOOPROPERTY (Serialized) = 1 << 15,
			_RayTracingShader LOOPROPERTY (Serialized) = 1 << 16,		// AnyHitShader, ClosestHitShader, MissShader, and other
			_AllGraphics LOOPROPERTY (Serialized) = _VertexShader | _TessControlShader | _TessEvaluationShader |
			_GeometryShader LOOPROPERTY (Serialized) | _FragmentShader | _MeshTaskShader | _MeshShader,
			_ShaderMask LOOPROPERTY (Serialized) = _AllGraphics | _ComputeShader | _RayTracingShader,

			// flags
			// unused range: 17..24
			_BufferDynamicOffset LOOPROPERTY (Serialized) = 1 << 25,

			// for ColorAttachment, DepthStencilAttachment
			InvalidateBefore  LOOPROPERTY (Serialized) = 1 << 26,				// discard image content before executing command
			InvalidateAfter LOOPROPERTY (Serialized) = 1 << 27,				// discard image content after command execution

			// for DepthStencilAttachment
			EarlyFragmentTests LOOPROPERTY (Serialized) = 1 << 28,
			LateFragmentTests LOOPROPERTY (Serialized) = 1 << 29,

			// read/write access
			_Read LOOPROPERTY (Serialized) = 1u << 30,
			_Write LOOPROPERTY (Serialized) = 1u << 31,
			_ReadWrite LOOPROPERTY (Serialized) = _Read | _Write,


			// default states
			_StateMask LOOPROPERTY (Serialized) = _AccessMask | _ReadWrite,

			ShaderRead LOOPROPERTY (Serialized) = _Access_ShaderStorage | _Read,
			ShaderWrite LOOPROPERTY (Serialized) = _Access_ShaderStorage | _Write,
			ShaderReadWrite LOOPROPERTY (Serialized) = _Access_ShaderStorage | _ReadWrite,

			UniformRead LOOPROPERTY (Serialized) = _Access_Uniform | _Read,

			ShaderSample LOOPROPERTY (Serialized) = _Access_ShaderSample | _Read,
			InputAttachment LOOPROPERTY (Serialized) = _Access_InputAttachment | _Read,

			TransferSrc LOOPROPERTY (Serialized) = _Access_Transfer | _Read,
			TransferDst LOOPROPERTY (Serialized) = _Access_Transfer | _Write,

			ColorAttachmentRead LOOPROPERTY (Serialized) = _Access_ColorAttachment | _Read,
			ColorAttachmentWrite LOOPROPERTY (Serialized) = _Access_ColorAttachment | _Write,
			ColorAttachmentReadWrite LOOPROPERTY (Serialized) = _Access_ColorAttachment | _ReadWrite,

			DepthStencilAttachmentRead LOOPROPERTY (Serialized) = _Access_DepthStencilAttachment | _Read,
			DepthStencilAttachmentWrite LOOPROPERTY (Serialized) = _Access_DepthStencilAttachment | _Write,
			DepthStencilAttachmentReadWrite LOOPROPERTY (Serialized) = _Access_DepthStencilAttachment | _ReadWrite,

			HostRead LOOPROPERTY (Serialized) = _Access_Host | _Read,
			HostWrite LOOPROPERTY (Serialized) = _Access_Host | _Write,
			HostReadWrite LOOPROPERTY (Serialized) = _Access_Host | _ReadWrite,

			PresentImage LOOPROPERTY (Serialized) = _Access_Present | _Read,

			IndirectBuffer LOOPROPERTY (Serialized) = _Access_IndirectBuffer | _Read,
			IndexBuffer LOOPROPERTY (Serialized) = _Access_IndexBuffer | _Read,
			VertexBuffer LOOPROPERTY (Serialized) = _Access_VertexBuffer | _Read,

			BuildRayTracingStructRead LOOPROPERTY (Serialized) = _Access_BuildRayTracingAS | _Read,
			BuildRayTracingStructWrite  LOOPROPERTY (Serialized) = _Access_BuildRayTracingAS | _Write,
			BuildRayTracingStructReadWrite LOOPROPERTY (Serialized) = _Access_BuildRayTracingAS | _Read | _Write,

			RTASBuildingBufferRead LOOPROPERTY (Serialized) = _Access_RTASBuildingBuffer | _Read,
			RTASBuildingBufferReadWrite LOOPROPERTY (Serialized) = _Access_RTASBuildingBuffer | _Read | _Write,

			RayTracingShaderRead LOOPROPERTY (Serialized) = ShaderRead | _RayTracingShader,

			ShadingRateImageRead LOOPROPERTY (Serialized) = _Access_ShadingRateImage | _Read,
		};

		LOO_BIT_OPERATORS (EResourceState);

		STATIC_ASSERT (EResourceState::_AccessLast < EResourceState::_AccessMask, "");

	}	

	// raytracing enums
	namespace vkfg
	{

		enum class LOOENUM () ERayTracingGeometryFlags : uint
		{
			Opaque LOOPROPERTY (Serialized) = 1 << 0,	// indicates that this geometry does not invoke the any-hit shaders even if present in a hit group
			NoDuplicateAnyHitInvocation LOOPROPERTY (Serialized) = 1 << 1,
			_end,
			_begin = Opaque,

			Unknown LOOPROPERTY (Serialized) = 0,
		};
		LOO_BIT_OPERATORS (ERayTracingGeometryFlags);


		enum class LOOENUM () ERayTracingInstanceFlags : uint
		{
			TriangleCullDisable LOOPROPERTY (Serialized) = 1 << 0,
			TriangleFrontCCW LOOPROPERTY (Serialized) = 1 << 1,
			ForceOpaque LOOPROPERTY (Serialized) = 1 << 2,	// enable ERayTracingGeometryFlags::Opaque flag
			ForceNonOpaque LOOPROPERTY (Serialized) = 1 << 3,	// disable ERayTracingGeometryFlags::Opaque flag
			_end,
			_begin = TriangleCullDisable,
			Unknown LOOPROPERTY (Serialized) = 0,
		};
		LOO_BIT_OPERATORS (ERayTracingInstanceFlags);


		// TODO: rename
		enum class LOOENUM () ERayTracingFlags : uint
		{
			AllowUpdate LOOPROPERTY (Serialized) = 1 << 0,
			AllowCompaction LOOPROPERTY (Serialized) = 1 << 1,
			PreferFastTrace LOOPROPERTY (Serialized) = 1 << 2,
			PreferFastBuild LOOPROPERTY (Serialized) = 1 << 3,
			LowMemory LOOPROPERTY (Serialized) = 1 << 4,
			_end,
			_begin = AllowUpdate,
			Unknown LOOPROPERTY (Serialized) = 0,
		};
		LOO_BIT_OPERATORS (ERayTracingFlags);


	}	
}
#ifndef __LOOREFLECT__
#include "vkfg/fg/generate/enums.loo.h"
#endif
#endif