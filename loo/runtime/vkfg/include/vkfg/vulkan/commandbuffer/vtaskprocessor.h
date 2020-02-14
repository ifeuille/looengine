
#pragma once

#include "vkfg/vulkan/commandbuffer/vtaskgraph.h"
#include "vkfg/vulkan/buffer/vlocalbuffer.h"
#include "vkfg/vulkan/raytracing/vlocalrtgeometry.h"
#include "vkfg/vulkan/raytracing/vlocalrtscene.h"
#include "vkfg/vulkan/commandbuffer/vbarriermanager.h"
#include "vkfg/vulkan/image/vlocalimage.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Task Processor
		//

		class VTaskProcessor final : public VulkanDeviceFn
		{
			// types
		private:
			class DrawTaskBarriers;
			class DrawTaskCommands;
			class PipelineResourceBarriers;
			class DrawContext;

			using BufferRange = VLocalBuffer::BufferRange;
			using ImageRange = VLocalImage::ImageRange;
			using BufferState = VLocalBuffer::BufferState;
			using ImageState = VLocalImage::ImageState;
			using RTGeometryState = VLocalRTGeometry::GeometryState;
			using RTSceneState = VLocalRTScene::SceneState;

			using CommitBarrierFn_t = void (*) (const void *, VBarrierManager &, Ptr<VLocalDebugger>);
			using PendingResourceBarriers_t = std::unordered_map< void const*, CommitBarrierFn_t, std::hash<void const*>, std::equal_to<void const*>,
				StdLinearAllocator<Pair<void const* const, CommitBarrierFn_t>> >;	// TODO: use temp allocator

			using BufferCopyRegions_t = FixedArray< VkBufferCopy, LOO_MaxCopyRegions >;
			using ImageCopyRegions_t = FixedArray< VkImageCopy, LOO_MaxCopyRegions >;
			using BufferImageCopyRegions_t = FixedArray< VkBufferImageCopy, LOO_MaxCopyRegions >;
			using BlitRegions_t = FixedArray< VkImageBlit, LOO_MaxBlitRegions >;
			using ResolveRegions_t = FixedArray< VkImageResolve, LOO_MaxResolveRegions >;
			using ImageClearRanges_t = FixedArray< VkImageSubresourceRange, LOO_MaxClearRanges >;

			using Statistic_t = IFrameGraph::RenderingStatistics;
			using StencilValue_t = decltype(_vkfg_hidden_::DynamicStates::stencilReference);

			struct PipelineState
			{
				VkPipeline		pipeline = VK_NULL_HANDLE;
			};


			// variables
		private:
			VCommandBuffer &			_fgThread;
			const VkCommandBuffer		_cmdBuffer;

			VTask						_currTask;
			bool						_enableDebugUtils : 1;
			bool						_isDefaultScissor : 1;
			bool						_perPassStatesUpdated : 1;

			PendingResourceBarriers_t	_pendingResourceBarriers;

			PipelineState				_graphicsPipeline;
			PipelineState				_computePipeline;
			PipelineState				_rayTracingPipeline;

			// index bufer state
			VkBuffer					_indexBuffer = VK_NULL_HANDLE;
			VkDeviceSize				_indexBufferOffset = UMax;
			VkIndexType					_indexType = VK_INDEX_TYPE_MAX_ENUM;

			VkImageView					_shadingRateImage = VK_NULL_HANDLE;

			static constexpr float		_dbgColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };


			// methods
		public:
			explicit VTaskProcessor (VCommandBuffer &, VkCommandBuffer);
			~VTaskProcessor ();

			void Visit (const VFgTask<SubmitRenderPass> &);
			void Visit (const VFgTask<DispatchCompute> &);
			void Visit (const VFgTask<DispatchComputeIndirect> &);
			void Visit (const VFgTask<CopyBuffer> &);
			void Visit (const VFgTask<CopyImage> &);
			void Visit (const VFgTask<CopyBufferToImage> &);
			void Visit (const VFgTask<CopyImageToBuffer> &);
			void Visit (const VFgTask<BlitImage> &);
			void Visit (const VFgTask<ResolveImage> &);
			void Visit (const VFgTask<GenerateMipmaps> &);
			void Visit (const VFgTask<FillBuffer> &);
			void Visit (const VFgTask<ClearColorImage> &);
			void Visit (const VFgTask<ClearDepthStencilImage> &);
			void Visit (const VFgTask<UpdateBuffer> &);
			void Visit (const VFgTask<Present> &);
			void Visit (const VFgTask<UpdateRayTracingShaderTable> &);
			void Visit (const VFgTask<BuildRayTracingGeometry> &);
			void Visit (const VFgTask<BuildRayTracingScene> &);
			void Visit (const VFgTask<TraceRays> &);
			void Visit (const VFgTask<CustomTask> &);

			static void Visit1_DrawVertices (void *, void *);
			static void Visit2_DrawVertices (void *, void *);
			static void Visit1_DrawIndexed (void *, void *);
			static void Visit2_DrawIndexed (void *, void *);
			static void Visit1_DrawMeshes (void *, void *);
			static void Visit2_DrawMeshes (void *, void *);
			static void Visit1_DrawVerticesIndirect (void *, void *);
			static void Visit2_DrawVerticesIndirect (void *, void *);
			static void Visit1_DrawIndexedIndirect (void *, void *);
			static void Visit2_DrawIndexedIndirect (void *, void *);
			static void Visit1_DrawMeshesIndirect (void *, void *);
			static void Visit2_DrawMeshesIndirect (void *, void *);
			static void Visit1_CustomDraw (void *, void *);
			static void Visit2_CustomDraw (void *, void *);

			void Run (VTask);


		private:
			void _CmdDebugMarker (StringView text) const;
			void _CmdPushDebugGroup (StringView text) const;
			void _CmdPopDebugGroup () const;

			template <typename ID>	ND_ auto const*  _ToLocal (ID id) const;
			template <typename ID>	ND_ auto const*  _GetResource (ID id) const;

			void _CommitBarriers ();

			void _AddRenderTargetBarriers (const VLogicalRenderPass &logicalRP, const DrawTaskBarriers &info);
			void _SetShadingRateImage (const VLogicalRenderPass &logicalRP, OUT VkImageView &view);
			void _BeginRenderPass (const VFgTask<SubmitRenderPass> &task);
			void _BeginSubpass (const VFgTask<SubmitRenderPass> &task);
			bool _CreateRenderPass (ArrayView<VLogicalRenderPass*> logicalPasses);

			void _ExtractDescriptorSets (const VPipelineLayout &, const VPipelineResourceSet &, OUT VkDescriptorSets_t &);
			void _BindPipelineResources (const VPipelineLayout &layout, const VPipelineResourceSet &resourceSet, VkPipelineBindPoint bindPoint, ShaderDbgIndex debugModeIndex);
			void _BindPipeline (const VLogicalRenderPass &logicalRP, const VBaseDrawVerticesTask &task, OUT VPipelineLayout const* &pplnLayout);
			void _BindPipeline (const VLogicalRenderPass &logicalRP, const VBaseDrawMeshes &task, OUT VPipelineLayout const* &pplnLayout);
			void _BindPipeline2 (const VLogicalRenderPass &logicalRP, VkPipeline pipelineId);
			void _BindPipeline (const VComputePipeline* pipeline, const Optional<loo::math::uint3> &localSize, ShaderDbgIndex debugModeIndex,
				VkPipelineCreateFlags flags, OUT VPipelineLayout const* &pplnLayout);
			void _PushConstants (const VPipelineLayout &layout, const _vkfg_hidden_::PushConstants_t &pc) const;
			void _SetScissor (const VLogicalRenderPass &, ArrayView<loo::math::RectI>);
			void _SetDynamicStates (const _vkfg_hidden_::DynamicStates &) const;
			void _BindShadingRateImage (VkImageView view);
			void _ResetDrawContext ();

			void _AddImage (const VLocalImage *img, EResourceState state, VkImageLayout layout, const ImageViewDesc &desc);
			void _AddImage (const VLocalImage *img, EResourceState state, VkImageLayout layout, const VkImageSubresourceLayers &subresLayers);
			void _AddImage (const VLocalImage *img, EResourceState state, VkImageLayout layout, const VkImageSubresourceRange &subres);
			void _AddImageState (const VLocalImage *img, const ImageState &state);

			void _AddBuffer (const VLocalBuffer *buf, EResourceState state, VkDeviceSize offset, VkDeviceSize size);
			void _AddBuffer (const VLocalBuffer *buf, EResourceState state, const VkBufferImageCopy &reg, const VLocalImage *img);
			void _AddBufferState (const VLocalBuffer *buf, const BufferState &state);

			void _AddRTGeometry (const VLocalRTGeometry *geom, EResourceState state);
			void _AddRTScene (const VLocalRTScene *scene, EResourceState state);

			void _BindIndexBuffer (VkBuffer indexBuffer, VkDeviceSize indexOffset, VkIndexType indexType);

			ND_ Statistic_t&  Stat () const;
		};


	}	
}