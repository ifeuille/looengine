#pragma once
/*
	Default states - all render states except 'InputAssemblyState' will be copied from render pass,
	the 'InputAssemblyState' will be invalidated, all pipelines will be invalidated.
*/

#include "vkfg/fg/pipelineresources.h"
#include "vkfg/fg/vertexinputstate.h"
#include "vkfg/fg/vulkantype.h"

namespace loo
{
	namespace vkfg
	{
		class IDrawContext
		{
			//types
		public:
			using Context_t = nonstd::variant< NullUnion, VulkanDrawContext >;

			// interface
		public:
			// returns API-specific data.
		// this data can be used to set states and write draw commands directly to the vulkan command buffer.
		ND_ virtual Context_t  GetData () = 0;

		// reset current states to default states (see above).
		// use this if you set states by raw vulkan function call and want to continue using context api.
		virtual void Reset () = 0;

		// pipelines
		virtual void BindPipeline (RawGPipelineID id, EPipelineDynamicState dynamicState = EPipelineDynamicState::Default) = 0;
		virtual void BindPipeline (RawMPipelineID id, EPipelineDynamicState dynamicState = EPipelineDynamicState::Default) = 0;

		// resources (descriptor sets)
		virtual void BindResources (const DescriptorSetID &id, const PipelineResources &res) = 0;
		virtual void PushConstants (const PushConstantID &id, const void *data, BytesU dataSize) = 0;
		virtual void BindShadingRateImage (RawImageID value, ImageLayer layer = Default, MipmapLevel level = Default) = 0;

		// vertex attributes and index buffer
		virtual void BindVertexAttribs (const VertexInputState &) = 0;
		virtual void BindVertexBuffer (const VertexBufferID &id, RawBufferID vbuf, BytesU offset) = 0;
		virtual void BindIndexBuffer (RawBufferID ibuf, BytesU offset, EIndex type) = 0;

		// render states
		virtual void SetColorBuffer (RenderTargetID id, const RenderState::ColorBuffer &value) = 0;
		virtual void SetLogicOp (ELogicOp value) = 0;
		virtual void SetBlendColor (const loo::math::RGBA32f &value) = 0;
		virtual void SetStencilBuffer (const RenderState::StencilBufferState &value) = 0;
		virtual void SetDepthBuffer (const RenderState::DepthBufferState &value) = 0;
		virtual void SetInputAssembly (const RenderState::InputAssemblyState &value) = 0;
		virtual void SetRasterization (const RenderState::RasterizationState &value) = 0;
		virtual void SetMultisample (const RenderState::MultisampleState &value) = 0;

		// dynamic states
		virtual void SetStencilCompareMask (uint value) = 0;
		virtual void SetStencilWriteMask (uint value) = 0;
		virtual void SetStencilReference (uint value) = 0;
		virtual void SetShadingRatePalette (uint viewportIndex, ArrayView<EShadingRatePalette> value) = 0;

		// draw commands
		virtual void DrawVertices (uint vertexCount,
								   uint instanceCount	= 1,
								   uint firstVertex		= 0,
								   uint firstInstance	= 0) = 0;

		virtual void DrawIndexed (uint indexCount,
								  uint instanceCount	= 1,
								  uint firstIndex		= 0,
								  int  vertexOffset		= 0,
								  uint firstInstance	= 0) = 0;

		virtual void DrawVerticesIndirect (RawBufferID	indirectBuffer,
										   BytesU		indirectBufferOffset,
										   uint			drawCount,
										   BytesU		stride = 0_b) = 0;

		virtual void DrawIndexedIndirect (RawBufferID	indirectBuffer,
										  BytesU		indirectBufferOffset,
										  uint			drawCount,
										  BytesU		stride = 0_b) = 0;

		virtual void DrawMeshes (uint	taskCount,
								 uint	firstTask	= 0) = 0;

		virtual void DrawMeshesIndirect (RawBufferID	indirectBuffer,
										 BytesU			indirectBufferOffset,
										 uint			drawCount,
										 BytesU			stride = 0_b) = 0;
			
		};
	}
}