// all commands
#pragma once

#include "vkfg/fg/pipelineresources.h"
#include "vkfg/fg/bufferview.h"
#include "vkfg/fg/imageview.h"
#include "vkfg/fg/enums.h"
#include "vkfg/fg/raytracinggeometrydesc.h"
#include "vkfg/fg/raytracingscenedesc.h"
#include "vkfg/fg/framegraphdrawtask.h"

namespace loo
{
	namespace vkfg
	{
		namespace _vkfg_hidden_
		{
			//
			// Base Task
			//
			template <typename BaseType>
			struct BaseTask
			{
				// types
				using Tasks_t = FixedArray< Task, LOO_MaxTaskDependencies >;
				using TaskName_t = StaticString<64>;

				// variables
				Tasks_t					depends;	// current task wiil be executed after dependencies
				TaskName_t				taskName;
				loo::math::RGBA8u		debugColor;

				// methods
				BaseTask () {}
				BaseTask (StringView name, loo::math::RGBA8u color) : taskName{ name }, debugColor{ color } {}

				BaseType& SetName (StringView name) { taskName = name;  return static_cast<BaseType &>(*this); }
				BaseType& SetDebugColor (loo::math::RGBA8u color) { debugColor = color;  return static_cast<BaseType &>(*this); }

				template <typename Arg0, typename ...Args>
				BaseType& DependsOn (Arg0 task0, Args ...tasks) { if (task0) depends.push_back (task0);  return DependsOn<Args...> (tasks...); }

				template <typename Arg0>
				BaseType& DependsOn (Arg0 task) { if (task) depends.push_back (task);  return static_cast<BaseType &>(*this); }
			};

			//
			// Compute Shader Debug Mode
			//
			struct ComputeShaderDebugMode
			{
				EShaderDebugMode	mode = Default;
				loo::math::uint3	globalID{ ~0u };
			};

			//
			// Ray Tracing Shader Debug Mode
			//
			struct RayTracingShaderDebugMode
			{
				EShaderDebugMode	mode = Default;
				loo::math::uint3	launchID{ ~0u };
			};

		}
	}
}

namespace loo
{
	namespace vkfg
	{
		

		//
		// Image Subresource Range
		//
		struct ImageSubresourceRange
		{
			// variables
			EImageAspect	aspectMask;
			MipmapLevel		mipLevel;
			ImageLayer		baseLayer;
			uint			layerCount;

			// methods
			ImageSubresourceRange () :
				aspectMask{ EImageAspect::Auto }, layerCount{ 1 } {}

			explicit
				ImageSubresourceRange (MipmapLevel	mipLevel,
					ImageLayer	baseLayer = Default,
					uint			layerCount = 1,
					EImageAspect	aspectMask = EImageAspect::Auto) :
				aspectMask (aspectMask), mipLevel (mipLevel), baseLayer (baseLayer), layerCount (layerCount) {}
		};



		//
		// Submit Render Pass
		//
		struct SubmitRenderPass final : _vkfg_hidden_::BaseTask<SubmitRenderPass>
		{
			// types
			using Images_t = CustomDraw::Images_t;
			using Buffers_t = CustomDraw::Buffers_t;

			// variables
			LogicalPassID		renderPassId;
			Images_t			images;		// can be used for pipeline barriers and layout transitions
			Buffers_t			buffers;

			// methods
			explicit SubmitRenderPass (LogicalPassID rp) :
				BaseTask<SubmitRenderPass>{ "RenderPass", ColorScheme::RenderPass }, renderPassId{ rp } {}

			SubmitRenderPass&  AddImage (RawImageID id, EResourceState state = EResourceState::ShaderSample)
			{
				ASSERT (id);
				images.emplace_back (id, state);
				return *this;
			}

			SubmitRenderPass&  AddBuffer (RawBufferID id, EResourceState state = EResourceState::UniformRead)
			{
				ASSERT (id);
				buffers.emplace_back (id, state);
				return *this;
			}
		};



		//
		// Dispatch Compute
		//
		struct DispatchCompute final : _vkfg_hidden_::BaseTask<DispatchCompute>
		{
			// types
			using PushConstants_t = _vkfg_hidden_::PushConstants_t;
			using DebugMode = _vkfg_hidden_::ComputeShaderDebugMode;

			struct ComputeCmd
			{
				loo::math::uint3	baseGroup;
				loo::math::uint3	groupCount;
			};
			using ComputeCmds_t = FixedArray< ComputeCmd, 16 >;


			// variables
			RawCPipelineID			pipeline;
			PipelineResourceSet		resources;
			ComputeCmds_t			commands;
			Optional< loo::math::uint3 >		localGroupSize;
			PushConstants_t			pushConstants;
			DebugMode				debugMode;


			// methods
			DispatchCompute () :
				BaseTask<DispatchCompute>{ "DispatchCompute", ColorScheme::Compute } {}

			DispatchCompute&  SetPipeline (RawCPipelineID ppln) { ASSERT (ppln);  pipeline = ppln;  return *this; }

			DispatchCompute&  Dispatch (const loo::math::uint2 &off, const loo::math::uint2 &count) { commands.emplace_back (loo::math::uint3{ off, 0 }, loo::math::uint3{ count, 1 });  return *this; }
			DispatchCompute&  Dispatch (const loo::math::uint3 &off, const loo::math::uint3 &count) { commands.emplace_back (off, count);  return *this; }
			DispatchCompute&  Dispatch (const loo::math::uint2 &count) { commands.emplace_back (loo::math::uint3{ 0 }, loo::math::uint3{ count, 1 });  return *this; }
			DispatchCompute&  Dispatch (const loo::math::uint3 &count) { commands.emplace_back (loo::math::uint3{ 0 }, count);  return *this; }

			DispatchCompute&  SetLocalSize (const loo::math::uint2 &value) { localGroupSize = loo::math::uint3{ value.x, value.y, 1 };  return *this; }
			DispatchCompute&  SetLocalSize (const loo::math::uint3 &value) { localGroupSize = value;  return *this; }
			DispatchCompute&  SetLocalSize (uint x, uint y = 1, uint z = 1) { localGroupSize = loo::math::uint3{ x, y, z };  return *this; }

			DispatchCompute&  EnableDebugTrace (const loo::math::uint3 &globalID);
			DispatchCompute&  EnableDebugTrace () { return EnableDebugTrace (loo::math::uint3{ ~0u }); }

			DispatchCompute&  AddResources (const DescriptorSetID &id, const PipelineResources *res);

			template <typename ValueType>
			DispatchCompute&  AddPushConstant (const PushConstantID &id, const ValueType &value);
			DispatchCompute&  AddPushConstant (const PushConstantID &id, const void *ptr, BytesU size);
		};



		//
		// Dispatch Compute Indirect
		//
		struct DispatchComputeIndirect final : _vkfg_hidden_::BaseTask<DispatchComputeIndirect>
		{
			// types
			using PushConstants_t = _vkfg_hidden_::PushConstants_t;
			using DebugMode = _vkfg_hidden_::ComputeShaderDebugMode;

			struct ComputeCmd
			{
				BytesU		indirectBufferOffset;
			};
			using ComputeCmds_t = FixedArray< ComputeCmd, 16 >;

			struct DispatchIndirectCommand
			{
				loo::math::uint3		groudCount;
			};


			// variables
			RawCPipelineID			pipeline;
			PipelineResourceSet		resources;
			ComputeCmds_t			commands;
			RawBufferID				indirectBuffer;
			Optional< loo::math::uint3 >		localGroupSize;
			PushConstants_t			pushConstants;
			DebugMode				debugMode;


			// methods
			DispatchComputeIndirect () :
				BaseTask<DispatchComputeIndirect>{ "DispatchComputeIndirect", ColorScheme::Compute } {}

			DispatchComputeIndirect&  SetLocalSize (const loo::math::uint3 &value) { localGroupSize = value;  return *this; }
			DispatchComputeIndirect&  SetLocalSize (uint x, uint y = 1, uint z = 1) { localGroupSize = loo::math::uint3{ x, y, z };  return *this; }

			DispatchComputeIndirect&  Dispatch (BytesU offset) { commands.push_back ({ offset });  return *this; }

			DispatchComputeIndirect&  EnableDebugTrace (const loo::math::uint3 &globalID);
			DispatchComputeIndirect&  EnableDebugTrace () { return EnableDebugTrace (loo::math::uint3{ ~0u }); }

			DispatchComputeIndirect&  SetPipeline (RawCPipelineID ppln) { ASSERT (ppln);  pipeline = ppln;  return *this; }
			DispatchComputeIndirect&  SetIndirectBuffer (RawBufferID buffer) { ASSERT (buffer);  indirectBuffer = buffer;  return *this; }

			DispatchComputeIndirect&  AddResources (const DescriptorSetID &id, const PipelineResources *res);

			template <typename ValueType>
			DispatchComputeIndirect&  AddPushConstant (const PushConstantID &id, const ValueType &value);
			DispatchComputeIndirect&  AddPushConstant (const PushConstantID &id, const void *ptr, BytesU size);
		};



		//
		// Copy Buffer
		//
		struct CopyBuffer final : _vkfg_hidden_::BaseTask<CopyBuffer>
		{
			// types
			struct Region
			{
				BytesU		srcOffset;
				BytesU		dstOffset;
				BytesU		size;
			};
			using Regions_t = FixedArray< Region, LOO_MaxCopyRegions >;


			// variables
			RawBufferID		srcBuffer;
			RawBufferID		dstBuffer;
			Regions_t		regions;


			// methods
			CopyBuffer () :
				BaseTask<CopyBuffer>{ "CopyBuffer", ColorScheme::DeviceLocalTransfer } {}

			CopyBuffer&  From (RawBufferID buf) { ASSERT (buf);  srcBuffer = buf;  return *this; }
			CopyBuffer&  To (RawBufferID buf) { ASSERT (buf);  dstBuffer = buf;  return *this; }

			CopyBuffer&  AddRegion (BytesU srcOffset, BytesU dstOffset, BytesU size)
			{
				regions.push_back (Region{ srcOffset, dstOffset, size });
				return *this;
			}
		};



		//
		// Copy Image
		//
		struct CopyImage final : _vkfg_hidden_::BaseTask<CopyImage>
		{
			// types
			struct Region
			{
				ImageSubresourceRange	srcSubresource;
				loo::math::int3					srcOffset;
				ImageSubresourceRange	dstSubresource;
				loo::math::int3					dstOffset;
				loo::math::uint3					size;
			};
			using Regions_t = FixedArray< Region, LOO_MaxCopyRegions >;


			// variables
			RawImageID		srcImage;
			RawImageID		dstImage;
			Regions_t		regions;


			// methods
			CopyImage () :
				BaseTask<CopyImage>{ "CopyImage", ColorScheme::DeviceLocalTransfer } {}

			CopyImage&  From (RawImageID img) { ASSERT (img);  srcImage = img;  return *this; }
			CopyImage&  To (RawImageID img) { ASSERT (img);  dstImage = img;  return *this; }

			CopyImage&  AddRegion (const ImageSubresourceRange &srcSubresource, const loo::math::int3 &srcOffset,
				const ImageSubresourceRange &dstSubresource, const loo::math::int3 &dstOffset,
				const loo::math::uint3 &size)
			{
				regions.push_back (Region{ srcSubresource, srcOffset, dstSubresource, dstOffset, size });
				return *this;
			}

			CopyImage&  AddRegion (const ImageSubresourceRange &srcSubresource, const loo::math::int2 &srcOffset,
				const ImageSubresourceRange &dstSubresource, const loo::math::int2 &dstOffset,
				const loo::math::uint2 &size)
			{
				regions.push_back (Region{ srcSubresource, loo::math::int3{ srcOffset.x, srcOffset.y, 0 },
										  dstSubresource, loo::math::int3{ dstOffset.x, dstOffset.y, 0 },
										  loo::math::uint3{ size.x, size.y, 0 } });
				return *this;
			}
		};



		//
		// Copy Buffer to Image
		//
		struct CopyBufferToImage final : _vkfg_hidden_::BaseTask<CopyBufferToImage>
		{
			// types
			struct Region
			{
				BytesU					bufferOffset;
				uint					bufferRowLength;	// pixels
				uint					bufferImageHeight;	// pixels
				ImageSubresourceRange	imageLayers;
				loo::math::int3					imageOffset;
				loo::math::uint3					imageSize;
			};
			using Regions_t = FixedArray< Region, LOO_MaxCopyRegions >;


			// variables
			RawBufferID		srcBuffer;
			RawImageID		dstImage;
			Regions_t		regions;


			// methods
			CopyBufferToImage () :
				BaseTask<CopyBufferToImage>{ "CopyBufferToImage", ColorScheme::DeviceLocalTransfer } {}

			CopyBufferToImage&  From (RawBufferID buf) { ASSERT (buf);  srcBuffer = buf;  return *this; }
			CopyBufferToImage&  To (RawImageID img) { ASSERT (img);  dstImage = img;  return *this; }

			CopyBufferToImage&  AddRegion (BytesU bufferOffset, uint bufferRowLength, uint bufferImageHeight,
				const ImageSubresourceRange &imageLayers, const loo::math::int3 &imageOffset, const loo::math::uint3 &imageSize)
			{
				regions.push_back (Region{ bufferOffset, bufferRowLength, bufferImageHeight,
										  imageLayers, imageOffset, imageSize });
				return *this;
			}

			CopyBufferToImage&  AddRegion (BytesU bufferOffset, uint bufferRowLength, uint bufferImageHeight,
				const ImageSubresourceRange &imageLayers, const loo::math::int2 &imageOffset, const loo::math::uint2 &imageSize)
			{
				regions.push_back (Region{ bufferOffset, bufferRowLength, bufferImageHeight,
										  imageLayers, loo::math::int3{imageOffset, 0}, loo::math::uint3{imageSize, 1} });
				return *this;
			}
		};



		//
		// Copy Image to Buffer
		//
		struct CopyImageToBuffer final : _vkfg_hidden_::BaseTask<CopyImageToBuffer>
		{
			// types
			using Region = CopyBufferToImage::Region;
			using Regions_t = CopyBufferToImage::Regions_t;


			// variables
			RawImageID		srcImage;
			RawBufferID		dstBuffer;
			Regions_t		regions;


			// methods
			CopyImageToBuffer () :
				BaseTask<CopyImageToBuffer>{ "CopyImageToBuffer", ColorScheme::DeviceLocalTransfer } {}

			CopyImageToBuffer&  From (RawImageID img) { ASSERT (img);  srcImage = img;  return *this; }
			CopyImageToBuffer&  To (RawBufferID buf) { ASSERT (buf);  dstBuffer = buf;  return *this; }

			CopyImageToBuffer&  AddRegion (const ImageSubresourceRange &imageLayers, const loo::math::int3 &imageOffset, const loo::math::uint3 &imageSize,
				BytesU bufferOffset, uint bufferRowLength, uint bufferImageHeight)
			{
				regions.push_back (Region{ bufferOffset, bufferRowLength, bufferImageHeight,
										  imageLayers, imageOffset, imageSize });
				return *this;
			}
		};



		//
		// Blit Image
		//
		struct BlitImage final : _vkfg_hidden_::BaseTask<BlitImage>
		{
			// types
			struct Region
			{
				ImageSubresourceRange	srcSubresource;
				loo::math::int3					srcOffset0;		// start offset
				loo::math::int3					srcOffset1;		// end offset
				ImageSubresourceRange	dstSubresource;
				loo::math::int3					dstOffset0;		// start offset
				loo::math::int3					dstOffset1;		// end offset
			};
			using Regions_t = FixedArray< Region, LOO_MaxBlitRegions >;


			// variables
			RawImageID		srcImage;
			RawImageID		dstImage;
			EFilter			filter = EFilter::Nearest;
			Regions_t		regions;


			// methods
			BlitImage () :
				BaseTask<BlitImage>{ "BlitImage", ColorScheme::DeviceLocalTransfer } {}

			BlitImage&  From (RawImageID img) { ASSERT (img);  srcImage = img;  return *this; }
			BlitImage&  To (RawImageID img) { ASSERT (img);  dstImage = img;  return *this; }

			BlitImage&  SetFilter (EFilter value) { filter = value;  return *this; }

			BlitImage&  AddRegion (const ImageSubresourceRange &srcSubresource, const loo::math::int2 &srcOffset0, const loo::math::int2 &srcOffset1,
				const ImageSubresourceRange &dstSubresource, const loo::math::int2 &dstOffset0, const loo::math::int2 &dstOffset1)
			{
				regions.push_back (Region{ srcSubresource, loo::math::int3{srcOffset0.x, srcOffset0.y, 0}, loo::math::int3{srcOffset1.x, srcOffset1.y, 1},
										  dstSubresource, loo::math::int3{dstOffset0.x, dstOffset0.y, 0}, loo::math::int3{dstOffset1.x, dstOffset1.y, 1} });
				return *this;
			}

			BlitImage&  AddRegion (const ImageSubresourceRange &srcSubresource, const loo::math::int3 &srcOffset0, const loo::math::int3 &srcOffset1,
				const ImageSubresourceRange &dstSubresource, const loo::math::int3 &dstOffset0, const loo::math::int3 &dstOffset1)
			{
				regions.push_back (Region{ srcSubresource, srcOffset0, srcOffset1,
										  dstSubresource, dstOffset0, dstOffset1 });
				return *this;
			}
		};



		//
		// Generate Mipmaps
		//
		struct GenerateMipmaps final : _vkfg_hidden_::BaseTask<GenerateMipmaps>
		{
			// variables
			RawImageID		image;
			MipmapLevel		baseLevel;
			uint			levelCount = UMax;

			// methods
			GenerateMipmaps () :
				BaseTask<GenerateMipmaps>{ "GenerateMipmaps", ColorScheme::DeviceLocalTransfer } {}

			GenerateMipmaps&  SetImage (RawImageID img) { ASSERT (img);  image = img;  return *this; }
			GenerateMipmaps&  SetRange (MipmapLevel base, uint count) { baseLevel = base;  levelCount = count;  return *this; }
		};



		//
		// Resolve Image
		//
		struct ResolveImage final : _vkfg_hidden_::BaseTask<ResolveImage>
		{
			// types
			struct Region
			{
				ImageSubresourceRange	srcSubresource;
				loo::math::int3					srcOffset;
				ImageSubresourceRange	dstSubresource;
				loo::math::int3					dstOffset;
				loo::math::uint3					extent;
			};
			using Regions_t = FixedArray< Region, LOO_MaxResolveRegions >;


			// variables
			RawImageID		srcImage;
			RawImageID		dstImage;
			Regions_t		regions;


			// methods
			ResolveImage () :
				BaseTask<ResolveImage>{ "ResolveImage", ColorScheme::DeviceLocalTransfer } {}

			ResolveImage&  From (RawImageID img) { ASSERT (img);  srcImage = img;  return *this; }
			ResolveImage&  To (RawImageID img) { ASSERT (img);  dstImage = img;  return *this; }

			ResolveImage&  AddRegion (const ImageSubresourceRange &srcSubresource, const loo::math::int2 &srcOffset,
				const ImageSubresourceRange &dstSubresource, const loo::math::int2 &dstOffset,
				const loo::math::uint2 &extent)
			{
				regions.push_back (Region{ srcSubresource, loo::math::int3{srcOffset, 0}, dstSubresource, loo::math::int3{dstOffset, 0}, loo::math::uint3{extent, 1} });
				return *this;
			}

			ResolveImage&  AddRegion (const ImageSubresourceRange &srcSubresource, const loo::math::int3 &srcOffset,
				const ImageSubresourceRange &dstSubresource, const loo::math::int3 &dstOffset,
				const loo::math::uint3 &extent)
			{
				regions.push_back (Region{ srcSubresource, srcOffset, dstSubresource, dstOffset, extent });
				return *this;
			}
		};



		//
		// Fill Buffer
		//
		struct FillBuffer final : _vkfg_hidden_::BaseTask<FillBuffer>
		{
			// variables
			RawBufferID		dstBuffer;
			BytesU			dstOffset;
			BytesU			size;
			uint			pattern = 0;


			// methods
			FillBuffer () :
				BaseTask<FillBuffer>{ "FillBuffer", ColorScheme::DeviceLocalTransfer } {}

			FillBuffer&  SetBuffer (RawBufferID buf)
			{
				return SetBuffer (buf, 0_b, ~0_b);
			}

			FillBuffer&  SetBuffer (RawBufferID buf, BytesU off, BytesU bufSize)
			{
				ASSERT (buf);
				dstBuffer = buf;
				dstOffset = off;
				size = bufSize;
				return *this;
			}

			FillBuffer&  SetPattern (uint value)
			{
				pattern = value;
				return *this;
			}
		};



		//
		// Clear Color Image
		//
		struct ClearColorImage final : _vkfg_hidden_::BaseTask<ClearColorImage>
		{
			// types
			struct Range
			{
				EImageAspect	aspectMask;
				MipmapLevel		baseMipLevel;
				uint			levelCount;
				ImageLayer		baseLayer;
				uint			layerCount;
			};
			using Ranges_t = FixedArray< Range, LOO_MaxClearRanges >;
			using ClearColor_t = nonstd::variant< NullUnion, loo::math::RGBA32f, loo::math::RGBA32u, loo::math::RGBA32i >;


			// variables
			RawImageID			dstImage;
			Ranges_t			ranges;
			ClearColor_t		clearValue;


			// methods
			ClearColorImage () :
				BaseTask<ClearColorImage>{ "ClearColorImage", ColorScheme::DeviceLocalTransfer } {}

			ClearColorImage&  SetImage (RawImageID img) { ASSERT (img);  dstImage = img;  return *this; }

			ClearColorImage&  Clear (const loo::math::RGBA32f &value) { clearValue = value;  return *this; }
			ClearColorImage&  Clear (const loo::math::RGBA32u &value) { clearValue = value;  return *this; }
			ClearColorImage&  Clear (const loo::math::RGBA32i &value) { clearValue = value;  return *this; }

			ClearColorImage&  AddRange (MipmapLevel baseMipLevel, uint levelCount,
				ImageLayer baseLayer, uint layerCount)
			{
				ranges.push_back (Range{ EImageAspect::Color, baseMipLevel, levelCount, baseLayer, layerCount });
				return *this;
			}
		};



		//
		// Clear Depth Stencil Image
		//
		struct ClearDepthStencilImage final : _vkfg_hidden_::BaseTask<ClearDepthStencilImage>
		{
			// types
			using Range = ClearColorImage::Range;
			using Ranges_t = FixedArray< Range, LOO_MaxClearRanges >;


			// variables
			RawImageID			dstImage;
			Ranges_t			ranges;
			loo::math::DepthStencil		clearValue;


			// methods
			ClearDepthStencilImage () :
				BaseTask<ClearDepthStencilImage>{ "ClearDepthStencilImage", ColorScheme::DeviceLocalTransfer } {}

			ClearDepthStencilImage&  SetImage (RawImageID img) { ASSERT (img);  dstImage = img;  return *this; }

			ClearDepthStencilImage&  Clear (float depth, uint stencil = 0) { clearValue = loo::math::DepthStencil{ depth, stencil };  return *this; }

			ClearDepthStencilImage&  AddRange (MipmapLevel baseMipLevel, uint levelCount,
				ImageLayer baseLayer, uint layerCount)
			{
				ranges.push_back (Range{ EImageAspect::DepthStencil, baseMipLevel, levelCount, baseLayer, layerCount });
				return *this;
			}
		};



		//
		// Update Buffer
		//
		struct UpdateBuffer final : _vkfg_hidden_::BaseTask<UpdateBuffer>
		{
			// types
			struct Region
			{
				BytesU				offset;
				ArrayView<uint8_t>	data;
			};
			using Regions_t = FixedArray< Region, LOO_MaxCopyRegions >;


			// variables
			RawBufferID		dstBuffer;		// if buffer has gpu local memory, then staging buffer will be used
			Regions_t		regions;


			// methods
			UpdateBuffer () :
				BaseTask<UpdateBuffer>{ "UpdateBuffer", ColorScheme::HostToDeviceTransfer } {}

			UpdateBuffer (RawBufferID buf, BytesU off, ArrayView<uint8_t> data) :
				UpdateBuffer () {
				SetBuffer (buf).AddData (data, off);
			}

			UpdateBuffer&  SetBuffer (RawBufferID buf)
			{
				ASSERT (buf);
				dstBuffer = buf;
				return *this;
			}

			template <typename T>
			UpdateBuffer&  AddData (const Array<T> &value, BytesU bufferOffset = 0_b)
			{
				regions.emplace_back (bufferOffset, ArrayView< uint8_t>{ Cast<uint8_t> (value.data ()), value.size () * sizeof (T) });
				return *this;
			}

			template <typename T>
			UpdateBuffer&  AddData (ArrayView<T> value, BytesU bufferOffset = 0_b)
			{
				regions.emplace_back (bufferOffset, ArrayView< uint8_t> ( Cast<uint8_t> (value.data ()), value.size () * sizeof (T) ));
				return *this;
			}

			template <typename T>
			UpdateBuffer&  AddData (const T* ptr, size_t count, BytesU bufferOffset = 0_b)
			{
				regions.emplace_back (bufferOffset, ArrayView{ Cast<uint8_t> (ptr), count * sizeof (T) });
				return *this;
			}

			template <typename T>
			UpdateBuffer&  AddData (const void* ptr, BytesU size, BytesU bufferOffset = 0_b)
			{
				regions.emplace_back (bufferOffset, ArrayView< uint8_t> ( Cast<uint8_t> (ptr), size_t (size) ));
				return *this;
			}
		};



		//
		// Read Buffer
		//
		struct ReadBuffer final : _vkfg_hidden_::BaseTask<ReadBuffer>
		{
			// types
			using Callback_t = std::function< void (BufferView) >;

			// variables
			RawBufferID		srcBuffer;
			BytesU			offset;
			BytesU			size;
			Callback_t		callback;

			// methods
			ReadBuffer () :
				BaseTask<ReadBuffer>{ "ReadBuffer", ColorScheme::DeviceToHostTransfer } {}

			ReadBuffer&  SetBuffer (RawBufferID buf, const BytesU off, const BytesU dataSize)
			{
				ASSERT (buf);
				srcBuffer = buf;
				offset = off;
				size = dataSize;
				return *this;
			}

			template <typename FN>
			ReadBuffer&  SetCallback (FN &&value)
			{
				callback = std::move (value);
				return *this;
			}
		};



		//
		// Update Image
		//
		struct UpdateImage final : _vkfg_hidden_::BaseTask<UpdateImage>
		{
			// variables
			RawImageID			dstImage;
			loo::math::int3				imageOffset;
			loo::math::uint3				imageSize;
			ImageLayer			arrayLayer;
			MipmapLevel			mipmapLevel;
			BytesU				dataRowPitch;
			BytesU				dataSlicePitch;
			EImageAspect		aspectMask = EImageAspect::Color;	// must only have a single bit set
			ArrayView<uint8_t>	data;


			// methods
			UpdateImage () :
				BaseTask<UpdateImage>{ "UpdateImage", ColorScheme::HostToDeviceTransfer } {}

			UpdateImage&  SetImage (RawImageID img, const loo::math::int2 &offset, MipmapLevel mipmap = Default)
			{
				ASSERT (img);
				dstImage = img;
				imageOffset = loo::math::int3 (offset.x, offset.y, 0);
				mipmapLevel = mipmap;
				return *this;
			}

			UpdateImage&  SetImage (RawImageID img, const loo::math::int3 &offset = Default, MipmapLevel mipmap = Default)
			{
				ASSERT (img);
				dstImage = img;
				imageOffset = offset;
				mipmapLevel = mipmap;
				return *this;
			}

			UpdateImage&  SetImage (RawImageID img, const loo::math::int2 &offset, ImageLayer layer, MipmapLevel mipmap)
			{
				ASSERT (img);
				dstImage = img;
				imageOffset = loo::math::int3 (offset.x, offset.y, 0);
				arrayLayer = layer;
				mipmapLevel = mipmap;
				return *this;
			}

			UpdateImage&  SetData (ArrayView<uint8_t> value, const loo::math::uint2 &dimension, BytesU rowPitch = 0_b)
			{
				data = value;
				imageSize = loo::math::uint3 (dimension.x, dimension.y, 0);
				dataRowPitch = rowPitch;
				return *this;
			}

			template <typename T>
			UpdateImage&  SetData (const T* ptr, size_t count, const loo::math::uint2 &dimension, BytesU rowPitch = 0_b)
			{
				return SetData (ArrayView<uint8_t>{ Cast<uint8_t> (ptr), count * sizeof (T) }, dimension, rowPitch);
			}

			UpdateImage&  SetData (ArrayView<uint8_t> value, const loo::math::uint3 &dimension, BytesU rowPitch = 0_b, BytesU slicePitch = 0_b)
			{
				data = value;
				imageSize = dimension;
				dataRowPitch = rowPitch;
				dataSlicePitch = slicePitch;
				return *this;
			}

			template <typename T>
			UpdateImage&  SetData (const T* ptr, size_t count, const loo::math::uint3 &dimension, BytesU rowPitch = 0_b, BytesU slicePitch = 0_b)
			{
				return SetData (ArrayView<uint8_t>{ Cast<uint8_t> (ptr), count * sizeof (T) }, dimension, rowPitch, slicePitch);
			}
		};



		//
		// Read Image
		//
		struct ReadImage final : _vkfg_hidden_::BaseTask<ReadImage>
		{
			// types
			using Callback_t = std::function< void (const ImageView &) >;


			// variables
			RawImageID		srcImage;
			loo::math::int3			imageOffset;
			loo::math::uint3			imageSize;
			ImageLayer		arrayLayer;
			MipmapLevel		mipmapLevel;
			EImageAspect	aspectMask = EImageAspect::Color;	// must only have a single bit set
			Callback_t		callback;


			// methods
			ReadImage () :
				BaseTask<ReadImage>{ "ReadImage", ColorScheme::DeviceToHostTransfer } {}

			ReadImage&  SetImage (RawImageID img, const loo::math::int2 &offset, const loo::math::uint2 &size, MipmapLevel mipmap = Default)
			{
				ASSERT (img);
				srcImage = img;
				imageOffset = loo::math::int3 (offset.x, offset.y, 0);
				imageSize = loo::math::uint3 (size.x, size.y, 0);
				mipmapLevel = mipmap;
				return *this;
			}

			ReadImage&  SetImage (RawImageID img, const loo::math::int3 &offset, const loo::math::uint3 &size, MipmapLevel mipmap = Default)
			{
				ASSERT (img);
				srcImage = img;
				imageOffset = offset;
				imageSize = size;
				mipmapLevel = mipmap;
				return *this;
			}

			ReadImage&  SetImage (RawImageID img, const loo::math::int2 &offset, const loo::math::uint2 &size, ImageLayer layer, MipmapLevel mipmap = Default)
			{
				ASSERT (img);
				srcImage = img;
				imageOffset = loo::math::int3 (offset.x, offset.y, 0);
				imageSize = loo::math::uint3 (size.x, size.y, 0);
				arrayLayer = layer;
				mipmapLevel = mipmap;
				return *this;
			}

			template <typename FN>
			ReadImage&  SetCallback (FN &&value)
			{
				callback = std::move (value);
				return *this;
			}
		};



		//
		// Present
		//
		struct Present final : _vkfg_hidden_::BaseTask<Present>
		{
			// variables
			RawSwapchainID	swapchain;
			RawImageID		srcImage;
			ImageLayer		layer;
			MipmapLevel		mipmap;


			// methods
			Present () :
				BaseTask<Present>{ "Present", ColorScheme::Present } {}

			explicit Present (RawSwapchainID swchain, RawImageID img) :
				Present () {
				SetSwapchain (swchain).SetImage (img);
			}

			Present&  SetSwapchain (RawSwapchainID id)
			{
				ASSERT (id);
				swapchain = id;
				return *this;
			}

			Present&  SetImage (RawImageID img, ImageLayer imgLayer = Default, MipmapLevel imgLevel = Default)
			{
				ASSERT (img);
				srcImage = img;
				layer = imgLayer;
				mipmap = imgLevel;
				return *this;
			}
		};



		//
		// Build Ray Tracing Geometry
		//
		struct BuildRayTracingGeometry final : _vkfg_hidden_::BaseTask<BuildRayTracingGeometry>
		{
			// types
			using EFlags = ERayTracingGeometryFlags;
			using Matrix3x4 = loo::math::Matrix< float, 3, 4, loo::math::EMatrixOrder::RowMajor >;

			struct Triangles
			{
				// variables
				GeometryID			geometryId;

				ArrayView<uint8_t>	vertexData;
				RawBufferID			vertexBuffer;
				BytesU				vertexOffset;
				Bytes<uint>			vertexStride;
				uint				vertexCount = 0;
				EVertexType			vertexFormat = Default;

				// optional:
				ArrayView<uint8_t>	indexData;
				RawBufferID			indexBuffer;
				BytesU				indexOffset;
				uint				indexCount = 0;
				EIndex				indexType = Default;

				// optional:
				Optional<Matrix3x4>	transformData;
				RawBufferID			transformBuffer;	// 3x4 row major affine transformation matrix for this geometry.
				BytesU				transformOffset;

				// methods
				Triangles () {}
				explicit Triangles (const GeometryID &id) : geometryId{ id } {}

				template <typename T, typename Idx>
				Triangles&  SetVertices (Idx count, BytesU stride = 0_b);
				template <typename Idx>
				Triangles&  SetVertices (Idx count, EVertexType format, BytesU stride = 0_b);
				Triangles&  SetVertexBuffer (RawBufferID id, BytesU offset = 0_b);
				Triangles&  SetVertexData (ArrayView<uint8_t> data);
				template <typename VertexT>
				Triangles&  SetVertexArray (ArrayView<VertexT> data);
				template <typename VertexT, typename AllocT>
				Triangles&  SetVertexArray (const std::vector<VertexT, AllocT> &data) { return SetVertexArray (ArrayView<VertexT>{ data }); }
				template <typename Idx>
				Triangles&  SetIndices (Idx count, EIndex type);
				template <typename IndexT>
				Triangles&  SetIndexArray (ArrayView<IndexT> data);
				template <typename IndexT, typename AllocT>
				Triangles&  SetIndexArray (const std::vector<IndexT, AllocT> &data) { return SetIndexArray (ArrayView<IndexT>{ data }); }
				Triangles&  SetIndexBuffer (RawBufferID id, BytesU offset = 0_b);
				Triangles&  SetIndexData (ArrayView<uint8_t> data);
				Triangles&  SetTransform (RawBufferID id, BytesU offset = 0_b);
				Triangles&  SetTransform (const Matrix3x4 &mat);
				Triangles&  SetID (const GeometryID &id) { geometryId = id;  return *this; }
			};


			struct AABBData
			{
				loo::math::float3		min;
				loo::math::float3		max;
			};

			struct AABB
			{
				// variables
				GeometryID			geometryId;
				ArrayView<uint8_t>	aabbData;
				RawBufferID			aabbBuffer;		// array of 'AABBData'
				BytesU				aabbOffset;
				Bytes<uint>			aabbStride;
				uint				aabbCount = 0;

				// methods
				AABB () {}
				explicit AABB (const GeometryID &id) : geometryId{ id } {}

				template <typename Idx>
				AABB&  SetCount (Idx count, BytesU stride = 0_b);
				AABB&  SetBuffer (RawBufferID id, BytesU offset = 0_b);
				AABB&  SetData (ArrayView<uint8_t> data);
				AABB&  SetID (const GeometryID &id) { geometryId = id;  return *this; }
			};


			// variables
			RawRTGeometryID			rtGeometry;
			Array< Triangles >		triangles;		// TODO: use ArrayView ?
			Array< AABB >			aabbs;


			// methods
			BuildRayTracingGeometry () :
				BaseTask<BuildRayTracingGeometry>{ "BuildRayTracingGeometry", ColorScheme::BuildRayTracingStruct } {}

			BuildRayTracingGeometry&  SetTarget (RawRTGeometryID id) { ASSERT (id);  rtGeometry = id;  return *this; }

			BuildRayTracingGeometry&  Add (const Triangles &value) { triangles.push_back (value);  return *this; }
			BuildRayTracingGeometry&  Add (const AABB &value) { aabbs.push_back (value);  return *this; }
		};



		//
		// Build Ray Tracing Scene
		//
		struct BuildRayTracingScene final : _vkfg_hidden_::BaseTask<BuildRayTracingScene>
		{
			// types
			using Matrix4x3 = loo::math::Matrix< float, 4, 3, loo::math::EMatrixOrder::RowMajor >;
			using EFlags = ERayTracingInstanceFlags;

			struct Instance
			{
				// variables
				InstanceID			instanceId;
				RawRTGeometryID		geometryId;
				Matrix4x3			transform = Matrix4x3::Identity ();
				uint				customId = 0;		// 'gl_InstanceCustomIndexNV' in the shader
				EFlags				flags = Default;
				uint8_t				mask = 0xFF;

				// methods
				Instance () {}
				explicit Instance (const InstanceID &id) { SetID (id); }

				Instance&  SetID (const InstanceID &value);
				Instance&  SetGeometry (RawRTGeometryID value);
				Instance&  SetInstanceIndex (uint value) { customId = value;  return *this; }
				Instance&  SetTransfrom (const Matrix4x3 &value) { transform = value;  return *this; }
				Instance&  AddFlags (EFlags value) { flags |= value;  return *this; }
				Instance&  SetMask (uint8_t value) { mask = value;  return *this; }
			};


			// variables
			RawRTSceneID		rtScene;
			Array< Instance >	instances;
			uint				hitShadersPerInstance = 1;		// same as 'sbtRecordStride' in ray gen shader


		// methods
			BuildRayTracingScene () :
				BaseTask<BuildRayTracingScene>{ "BuildRayTracingScene", ColorScheme::BuildRayTracingStruct } {}

			BuildRayTracingScene&  SetTarget (RawRTSceneID id) { ASSERT (id);  rtScene = id;  return *this; }
			BuildRayTracingScene&  SetHitShadersPerInstance (uint count) { ASSERT (count > 0);  hitShadersPerInstance = count;  return *this; }
			BuildRayTracingScene&  Add (const Instance &value) { instances.push_back (value);  return *this; }
		};



		//
		// Update Ray Tracing Shader Table
		//
		struct UpdateRayTracingShaderTable final : _vkfg_hidden_::BaseTask<UpdateRayTracingShaderTable>
		{
			// types
			struct RayGenShader
			{
				RTShaderID			shaderId;
			};

			enum class EGroupType
			{
				Unknown,
				MissShader,
				TriangleHitShader,
				ProceduralHitShader,
				CallableShader,
			};

			struct ShaderGroup
			{
				EGroupType			type = Default;
				InstanceID			instanceId;
				GeometryID			geometryId;
				uint				offset = 0;
				RTShaderID			mainShader;			// miss or closest hit shader
				RTShaderID			anyHitShader;		// optional
				RTShaderID			intersectionShader;	// only for procedural geometry

				ShaderGroup (const RTShaderID &missShader, uint missIndex) :
					type{ EGroupType::MissShader }, offset{ missIndex }, mainShader{ missShader } {}

				ShaderGroup (const InstanceID &inst, const GeometryID &geom, uint off, const RTShaderID &chit, const RTShaderID &anyHit) :
					type{ EGroupType::TriangleHitShader }, instanceId{ inst }, geometryId{ geom }, offset{ off }, mainShader{ chit }, anyHitShader{ anyHit } {}

				ShaderGroup (const InstanceID &inst, const GeometryID &geom, uint off, const RTShaderID &chit, const RTShaderID &anyHit, const RTShaderID &inter) :
					type{ EGroupType::ProceduralHitShader }, instanceId{ inst }, geometryId{ geom }, offset{ off }, mainShader{ chit }, anyHitShader{ anyHit }, intersectionShader{ inter } {}
			};

			using ShaderGroups_t = Array< ShaderGroup >;
			using Self = UpdateRayTracingShaderTable;


			// variables
			RawRTShaderTableID		shaderTable;
			RawRTPipelineID			pipeline;
			RawRTSceneID			rtScene;
			RayGenShader			rayGenShader;
			ShaderGroups_t			shaderGroups;
			uint					maxRecursionDepth = 0;


			// methods
			UpdateRayTracingShaderTable () :
				BaseTask<UpdateRayTracingShaderTable>{ "UpdateRayTracingShaderTable", ColorScheme::HostToDeviceTransfer } {}

			Self&  SetPipeline (RawRTPipelineID ppln);
			Self&  SetScene (RawRTSceneID scene);
			Self&  SetTarget (RawRTShaderTableID sbt);
			Self&  SetMaxRecursionDepth (uint value) { maxRecursionDepth = value;  return *this; }

			Self&  SetRayGenShader (const RTShaderID &shader);
			Self&  AddMissShader (const RTShaderID &shader, uint missIndex);
			//Self&  AddCallableShader ();

			Self&  AddHitShader (const InstanceID &inst, uint offset,
				const RTShaderID &closestHit, const RTShaderID &anyHit = Default);

			Self&  AddHitShader (const InstanceID &inst, const GeometryID &geom, uint offset,
				const RTShaderID &closestHit, const RTShaderID &anyHit = Default);

			Self&  AddProceduralHitShader (const InstanceID &inst, const GeometryID &geom, uint offset,
				const RTShaderID &closestHit, const RTShaderID &anyHit, const RTShaderID &intersection);
		};



		//
		// Trace Rays
		//
		struct TraceRays final : _vkfg_hidden_::BaseTask<TraceRays>
		{
			// types
			using PushConstants_t = _vkfg_hidden_::PushConstants_t;
			using DebugMode = _vkfg_hidden_::RayTracingShaderDebugMode;


			// variables
			PipelineResourceSet		resources;
			loo::math::uint3					groupCount;
			PushConstants_t			pushConstants;
			RawRTShaderTableID		shaderTable;
			DebugMode				debugMode;


			// methods
			TraceRays () :
				BaseTask<TraceRays>{ "TraceRays", ColorScheme::RayTracing } {}

			TraceRays&  SetGroupCount (const loo::math::uint3 &value) { groupCount = value;  return *this; }
			TraceRays&  SetGroupCount (uint x, uint y = 1, uint z = 1) { groupCount = { x, y, z };  return *this; }

			TraceRays&  AddResources (const DescriptorSetID &id, const PipelineResources *res);
			TraceRays&  SetShaderTable (RawRTShaderTableID id);

			template <typename ValueType>
			TraceRays&  AddPushConstant (const PushConstantID &id, const ValueType &value);
			TraceRays&  AddPushConstant (const PushConstantID &id, const void *ptr, BytesU size);

			TraceRays&  EnableDebugTrace (const loo::math::uint3 &launchID);
			TraceRays&  EnableDebugTrace ();
		};



		//
		// Custom Task
		//
		struct CustomTask final : _vkfg_hidden_::BaseTask<CustomTask>
		{
			// types
			using Context_t = nonstd::variant< NullUnion, VulkanContext >;
			using Callback_t = std::function< void (const Context_t &) >;
			using Images_t = FixedArray< Pair< RawImageID, EResourceState >, 8 >;
			using Buffers_t = FixedArray< Pair< RawBufferID, EResourceState >, 8 >;


			// variables
			Callback_t		callback;
			Images_t		images;		// can be used for pipeline barriers and layout transitions
			Buffers_t		buffers;


			// methods
			CustomTask () :
				BaseTask<CustomTask>{ "CustomTask", ColorScheme::Debug } {}

			template <typename FN>
			explicit CustomTask (FN &&fn) : CustomTask{}
			{
				callback = Callback_t{ fn };
			}

			CustomTask&  AddImage (RawImageID id, EResourceState state = EResourceState::ShaderSample)
			{
				ASSERT (id);
				images.emplace_back (id, state);
				return *this;
			}

			CustomTask&  AddBuffer (RawBufferID id, EResourceState state = EResourceState::UniformRead)
			{
				ASSERT (id);
				buffers.emplace_back (id, state);
				return *this;
			}
		};
		//-----------------------------------------------------------------------------

	}
}

namespace loo
{
	// DispatchCompute
	namespace vkfg
	{
		inline DispatchCompute&  DispatchCompute::EnableDebugTrace (const loo::math::uint3 &globalID)
		{
			debugMode.mode = EShaderDebugMode::Trace;
			debugMode.globalID = globalID;
			return *this;
		}

		inline DispatchCompute&  DispatchCompute::AddResources (const DescriptorSetID &id, const PipelineResources *res)
		{
			ASSERT (id.IsDefined () and res);
			resources.insert ({ id, res });
			return *this;
		}

		template <typename ValueType>
		DispatchCompute&  DispatchCompute::AddPushConstant (const PushConstantID &id, const ValueType &value)
		{
			STATIC_ASSERT (not IsPointer<ValueType>, "");
			return AddPushConstant (id, AddressOf (value), SizeOf<ValueType>);
		}

		inline DispatchCompute&  DispatchCompute::AddPushConstant (const PushConstantID &id, const void *ptr, BytesU size)
		{
			ASSERT (id.IsDefined ());
			auto&	pc = pushConstants.emplace_back ();
			pc.id = id;
			pc.size = Bytes<uint16_t>{ size };
			MemCopy (pc.data, BytesU::SizeOf (pc.data), ptr, size);
			return *this;
		}


	}

	// DispatchComputeIndirect
	namespace vkfg
	{
		inline DispatchComputeIndirect&  DispatchComputeIndirect::EnableDebugTrace (const loo::math::uint3 &globalID)
		{
			debugMode.mode = EShaderDebugMode::Trace;
			debugMode.globalID = globalID;
			return *this;
		}

		inline DispatchComputeIndirect&  DispatchComputeIndirect::AddResources (const DescriptorSetID &id, const PipelineResources *res)
		{
			ASSERT (id.IsDefined () and res);
			resources.insert ({ id, res });
			return *this;
		}

		template <typename ValueType>
		DispatchComputeIndirect&  DispatchComputeIndirect::AddPushConstant (const PushConstantID &id, const ValueType &value)
		{
			STATIC_ASSERT (not IsPointer<ValueType>, "");
			return AddPushConstant (id, AddressOf (value), SizeOf<ValueType>);
		}

		inline DispatchComputeIndirect&  DispatchComputeIndirect::AddPushConstant (const PushConstantID &id, const void *ptr, BytesU size)
		{
			ASSERT (id.IsDefined ());
			auto&	pc = pushConstants.emplace_back ();
			pc.id = id;
			pc.size = Bytes<uint16_t>{ size };
			MemCopy (pc.data, BytesU::SizeOf (pc.data), ptr, size);
			return *this;
		}

	}

	// BuildRayTracingGeometry::Triangles
	namespace vkfg
	{

		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetVertexBuffer (RawBufferID id, BytesU offset)
		{
			ASSERT (vertexData.empty ());
			vertexBuffer = id;
			vertexOffset = offset;
			return *this;
		}

		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetVertexData (ArrayView<uint8_t> data)
		{
			ASSERT (not vertexBuffer);
			vertexData = data;
			return *this;
		}

		template <typename VertexT>
		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetVertexArray (ArrayView<VertexT> vertices)
		{
			ASSERT (vertices.size ());
			vertexBuffer = Default;
			vertexData = ArrayView<uint8_t>{ Cast<uint8_t> (vertices.data ()), vertices.size () * sizeof (VertexT) };
			vertexCount = uint (vertices.size ());
			vertexFormat = VertexDesc<VertexT>::attrib;
			vertexStride = Bytes<uint>::SizeOf<VertexT> ();
			return *this;
		}

		template <typename T, typename Idx>
		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetVertices (Idx count, BytesU stride)
		{
			STATIC_ASSERT (IsInteger<Idx>,"");
			vertexCount = uint (count);
			vertexStride = Bytes<uint>{ uint (stride) };
			vertexFormat = VertexDesc<T>::attrib;
			return *this;
		}

		template <typename Idx>
		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetVertices (Idx count, EVertexType format, BytesU stride)
		{
			STATIC_ASSERT (IsInteger<Idx>, "");
			vertexCount = uint (count);
			vertexStride = Bytes<uint>{ uint (stride) };
			vertexFormat = format;
			return *this;
		}

		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetIndexBuffer (RawBufferID id, BytesU offset)
		{
			ASSERT (indexData.empty ());
			indexBuffer = id;
			indexOffset = offset;
			return *this;
		}

		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetIndexData (ArrayView<uint8_t> data)
		{
			ASSERT (not indexBuffer);
			indexData = data;
			return *this;
		}

		template <typename Idx>
		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetIndices (Idx count, EIndex type)
		{
			STATIC_ASSERT (IsInteger<Idx>, "");
			indexCount = uint (count);
			indexType = type;
			return *this;
		}

		template <typename IndexT>
		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetIndexArray (ArrayView<IndexT> indices)
		{
			ASSERT (indices.size ());
			indexBuffer = Default;
			indexData = ArrayView<uint8_t>{ Cast<uint8_t> (indices.data ()), indices.size () * sizeof (IndexT) };
			indexCount = uint (indices.size ());
			indexType = (IsSameTypes<IndexT, uint32_t> ? EIndex::UInt : (IsSameTypes<IndexT, uint16_t> ? EIndex::UShort : EIndex::Unknown));
			return *this;
		}

		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetTransform (RawBufferID id, BytesU offset)
		{
			ASSERT (not transformData.has_value ());
			transformBuffer = id;
			transformOffset = offset;
			return *this;
		}

		inline BuildRayTracingGeometry::Triangles&
			BuildRayTracingGeometry::Triangles::SetTransform (const Matrix3x4 &mat)
		{
			ASSERT (not transformBuffer);
			transformData = mat;
			return *this;
		}
	}

	// BuildRayTracingGeometry::AABB
	namespace vkfg
	{

		inline BuildRayTracingGeometry::AABB&
			BuildRayTracingGeometry::AABB::SetBuffer (RawBufferID id, BytesU offset)
		{
			ASSERT (aabbData.empty ());
			aabbBuffer = id;
			aabbOffset = offset;
			return *this;
		}

		inline BuildRayTracingGeometry::AABB&
			BuildRayTracingGeometry::AABB::SetData (ArrayView<uint8_t> data)
		{
			ASSERT (not aabbBuffer);
			aabbData = data;
			return *this;
		}

		template <typename Idx>
		inline BuildRayTracingGeometry::AABB&
			BuildRayTracingGeometry::AABB::SetCount (Idx count, BytesU stride)
		{
			STATIC_ASSERT (IsInteger<Idx>, "");
			aabbCount = uint (count);
			aabbStride = Bytes<uint>{ uint (stride) };
			return *this;
		}
	}

	// BuildRayTracingScene::Instance
	namespace vkfg
	{
		inline BuildRayTracingScene::Instance&
			BuildRayTracingScene::Instance::SetID (const InstanceID &id)
		{
			ASSERT (id.IsDefined ());
			instanceId = id;
			return *this;
		}

		inline BuildRayTracingScene::Instance&
			BuildRayTracingScene::Instance::SetGeometry (RawRTGeometryID id)
		{
			ASSERT (id.IsValid ());
			geometryId = id;
			return *this;
		}
	}

	// UpdateRayTracingShaderTable
	namespace vkfg
	{
		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::SetPipeline (RawRTPipelineID ppln)
		{
			ASSERT (ppln);
			pipeline = ppln;
			return *this;
		}

		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::SetScene (RawRTSceneID scene)
		{
			ASSERT (scene);
			rtScene = scene;
			return *this;
		}

		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::SetTarget (RawRTShaderTableID sbt)
		{
			ASSERT (sbt);
			shaderTable = sbt;
			return *this;
		}

		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::SetRayGenShader (const RTShaderID &shader)
		{
			ASSERT (shader.IsDefined ());
			rayGenShader = RayGenShader{ shader };
			return *this;
		}

		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::AddMissShader (const RTShaderID &shader, uint missIndex)
		{
			ASSERT (shader.IsDefined ());
			shaderGroups.push_back (ShaderGroup{ shader, missIndex });
			return *this;
		}

		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::AddHitShader (const InstanceID &inst, uint offset,
				const RTShaderID &closestHit, const RTShaderID &anyHit)
		{
			ASSERT (inst.IsDefined ());
			ASSERT (closestHit.IsDefined ());
			shaderGroups.push_back (ShaderGroup{ inst, Default, offset, closestHit, anyHit });
			return *this;
		}

		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::AddHitShader (const InstanceID &inst, const GeometryID &geom, uint offset,
				const RTShaderID &closestHit, const RTShaderID &anyHit)
		{
			ASSERT (inst.IsDefined ());
			ASSERT (geom.IsDefined ());
			ASSERT (closestHit.IsDefined ());
			shaderGroups.push_back (ShaderGroup{ inst, geom, offset, closestHit, anyHit });
			return *this;
		}

		inline UpdateRayTracingShaderTable&
			UpdateRayTracingShaderTable::AddProceduralHitShader (const InstanceID &inst, const GeometryID &geom, uint offset,
				const RTShaderID &closestHit, const RTShaderID &anyHit, const RTShaderID &intersection)
		{
			ASSERT (inst.IsDefined ());
			//ASSERT( geom.IsDefined() );
			ASSERT (closestHit.IsDefined ());
			shaderGroups.push_back (ShaderGroup{ inst, geom, offset, closestHit, anyHit, intersection });
			return *this;
		}
	}

	// TraceRays
	namespace vkfg
	{
		template <typename ValueType>
		TraceRays&  TraceRays::AddPushConstant (const PushConstantID &id, const ValueType &value)
		{
			STATIC_ASSERT (not IsPointer<ValueType>, "");
			return AddPushConstant (id, AddressOf (value), SizeOf<ValueType>);
		}

		inline TraceRays&  TraceRays::AddPushConstant (const PushConstantID &id, const void *ptr, BytesU size)
		{
			ASSERT (id.IsDefined ());
			auto&	pc = pushConstants.emplace_back ();
			pc.id = id;
			pc.size = Bytes<uint16_t>{ size };
			MemCopy (pc.data, BytesU::SizeOf (pc.data), ptr, size);
			return *this;
		}

		inline TraceRays&  TraceRays::AddResources (const DescriptorSetID &id, const PipelineResources *res)
		{
			ASSERT (id.IsDefined () and res);
			resources.insert ({ id, res });
			return *this;
		}

		inline TraceRays&  TraceRays::SetShaderTable (RawRTShaderTableID id)
		{
			ASSERT (id);
			shaderTable = id;
			return *this;
		}

		inline TraceRays&  TraceRays::EnableDebugTrace (const loo::math::uint3 &launchID)
		{
			debugMode.mode = EShaderDebugMode::Trace;
			debugMode.launchID = launchID;
			return *this;
		}

		inline TraceRays&  TraceRays::EnableDebugTrace ()
		{
			debugMode.mode = EShaderDebugMode::Trace;
			return *this;
		}
	}

}