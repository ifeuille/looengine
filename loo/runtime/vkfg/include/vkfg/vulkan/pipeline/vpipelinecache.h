
#pragma once


#include "vkfg/fg/framegraphtask.h"
#include "vkfg/vulkan/descriptors/vdescriptorsetlayout.h"
#include "vkfg/vulkan/pipeline/vpipelinelayout.h"
#include "vkfg/vulkan/pipeline/vgraphicspipeline.h"
#include "vkfg/vulkan/pipeline/vcomputepipeline.h"
#include "vkfg/vulkan/pipeline/vmeshpipeline.h"
#include "vkfg/vulkan/raytracing/vraytracingpipeline.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Pipeline Cache
		//

		class VPipelineCache final
		{
			// types
		private:
			using DynamicStates_t = FixedArray< VkDynamicState, 32 >;
			using Viewports_t = FixedArray< VkViewport, 16 >;
			using Scissors_t = FixedArray< VkRect2D, 16 >;
			using VertexInputAttributes_t = FixedArray< VkVertexInputAttributeDescription, LOO_MaxVertexAttribs >;
			using VertexInputBindings_t = FixedArray< VkVertexInputBindingDescription, LOO_MaxVertexBuffers >;
			using ColorAttachments_t = FixedArray< VkPipelineColorBlendAttachmentState, LOO_MaxColorBuffers >;
			using Specializations_t = Array< VkSpecializationInfo >;
			using SpecializationEntries_t = Array< VkSpecializationMapEntry >;
			using SpecializationData_t = Array< uint >;
			using ShaderStages_t = Array< VkPipelineShaderStageCreateInfo >;
			using RTShaderGroups_t = Array< VkRayTracingShaderGroupCreateInfoNV >;

			using EGroupType = UpdateRayTracingShaderTable::EGroupType;
			using RayGenShader = UpdateRayTracingShaderTable::RayGenShader;
			using RTShaderGroup = UpdateRayTracingShaderTable::ShaderGroup;

			struct RTShaderGroupHash {
				ND_ size_t  operator () (const RTShaderGroup *value) const {
					return size_t (HashOf (value->type) + HashOf (value->mainShader) + HashOf (value->anyHitShader) + HashOf (value->intersectionShader));
				}
			};
			struct RTShaderGroupEqual {
				ND_ bool  operator () (const RTShaderGroup *lhs, const RTShaderGroup *rhs) const {
					return	lhs->type == rhs->type and lhs->mainShader == rhs->mainShader and
						lhs->anyHitShader == rhs->anyHitShader and lhs->intersectionShader == rhs->intersectionShader;
				}
			};
			using RTShaderGroupMap_t = std::unordered_map< RTShaderGroup const*, uint, RTShaderGroupHash, RTShaderGroupEqual >;

			struct RTShaderSpec
			{
				SpecializationID	id;
				BytesU				offset;
			};
			using RTShaderSpecializations_t = FixedArray< RTShaderSpec, 32 >;

			using ShaderModule_t = VGraphicsPipeline::ShaderModule;

		public:
			struct BufferCopyRegion
			{
				VLocalBuffer const*		srcBuffer = null;
				VLocalBuffer const*		dstBuffer = null;
				VkBufferCopy			region{};
			};
			using BufferCopyRegions_t = FixedArray< BufferCopyRegion, 8 >;


			// variables
		private:
			VkPipelineCache				_pipelinesCache;

			// temporary arrays
			ShaderStages_t				_tempStages;			// TODO: use custom allocator?
			Specializations_t			_tempSpecialization;
			DynamicStates_t				_tempDynamicStates;
			Viewports_t					_tempViewports;
			Scissors_t					_tempScissors;
			VertexInputAttributes_t		_tempVertexAttribs;
			VertexInputBindings_t		_tempVertexBinding;
			ColorAttachments_t			_tempAttachments;
			SpecializationEntries_t		_tempSpecEntries;
			SpecializationData_t		_tempSpecData;
			RTShaderGroups_t			_tempShaderGroups;
			RTShaderGroupMap_t			_tempShaderGraphMap;
			RTShaderSpecializations_t	_rtShaderSpecs;


			// methods
		public:
			VPipelineCache ();
			~VPipelineCache ();

			bool Initialize (const VDevice &dev);
			void Deinitialize (const VDevice &dev);

			bool MergeCache (VPipelineCache &);

			bool CreatePipelineInstance (VCommandBuffer					&fgThread,
				const VLogicalRenderPass		&logicalRP,
				const VGraphicsPipeline		&gpipeline,
				const VertexInputState			&vertexInput,
				const RenderState				&renderState,
				const EPipelineDynamicState	 dynamicStates,
				const ShaderDbgIndex			 debugModeIndex,
				OUT VkPipeline					&outPipeline,
				OUT VPipelineLayout const*		&outLayout);

			bool CreatePipelineInstance (VCommandBuffer					&fgThread,
				const VLogicalRenderPass		&logicalRP,
				const VMeshPipeline			&mpipeline,
				const RenderState				&renderState,
				const EPipelineDynamicState	 dynamicStates,
				const ShaderDbgIndex			 debugModeIndex,
				OUT VkPipeline					&outPipeline,
				OUT VPipelineLayout const*		&outLayout);

			bool CreatePipelineInstance (VCommandBuffer					&fgThread,
				const VComputePipeline			&ppln,
				const Optional<loo::math::uint3>			&localGroupSize,
				VkPipelineCreateFlags			 pipelineFlags,
				const ShaderDbgIndex			 debugModeIndex,
				OUT VkPipeline					&outPipeline,
				OUT VPipelineLayout const*		&outLayout);

			bool InitShaderTable (VCommandBuffer				&fgThread,
				RawRTPipelineID				 pipelineId,
				VRayTracingScene const		&rtScene,
				const RayGenShader			&rayGenShader,
				ArrayView< RTShaderGroup >	 shaderGroups,
				const uint					 maxRecursionDepth,
				INOUT VRayTracingShaderTable	&shaderTable,
				OUT BufferCopyRegions_t		&copyRegions);


		private:
			bool _CreatePipelineCache (const VDevice &dev);

			template <typename Pipeline>
			bool _SetupShaderDebugging (VCommandBuffer &fgThread, const Pipeline &ppln, ShaderDbgIndex debugModeIndex,
				OUT EShaderDebugMode &debugMode, OUT EShaderStages &debuggableShaders, OUT RawPipelineLayoutID &layoutId);

			void _ClearTemp ();

			void _SetColorBlendState (OUT VkPipelineColorBlendStateCreateInfo &outState,
				OUT ColorAttachments_t &attachments,
				const RenderState::ColorBuffersState &inState,
				const VRenderPass &renderPass,
				uint subpassIndex) const;

			void _SetShaderStages (OUT ShaderStages_t &stages,
				INOUT Specializations_t &specialization,
				INOUT SpecializationEntries_t &specEntries,
				ArrayView<ShaderModule_t> shaders,
				EShaderDebugMode debugMode,
				EShaderStages debuggableShaders) const;

			void _SetDynamicState (OUT VkPipelineDynamicStateCreateInfo &outState,
				OUT DynamicStates_t &states,
				EPipelineDynamicState inState) const;

			void _SetMultisampleState (OUT VkPipelineMultisampleStateCreateInfo &outState,
				const RenderState::MultisampleState &inState) const;

			void _SetTessellationState (OUT VkPipelineTessellationStateCreateInfo &outState,
				uint patchSize) const;

			void _SetDepthStencilState (OUT VkPipelineDepthStencilStateCreateInfo &outState,
				const RenderState::DepthBufferState &depth,
				const RenderState::StencilBufferState &stencil) const;

			void _SetRasterizationState (OUT VkPipelineRasterizationStateCreateInfo &outState,
				const RenderState::RasterizationState &inState) const;

			void _SetupPipelineInputAssemblyState (OUT VkPipelineInputAssemblyStateCreateInfo &outState,
				const RenderState::InputAssemblyState &inState) const;

			void _SetVertexInputState (OUT VkPipelineVertexInputStateCreateInfo &outState,
				OUT VertexInputAttributes_t &vertexAttribs,
				OUT VertexInputBindings_t &vertexBinding,
				const VertexInputState &inState) const;

			void _SetViewportState (OUT VkPipelineViewportStateCreateInfo &outState,
				OUT Viewports_t &tmpViewports,
				OUT Scissors_t &tmpScissors,
				const loo::math::uint2 &viewportSize,
				uint viewportCount,
				EPipelineDynamicState dynamicStates) const;

			void _AddLocalGroupSizeSpecialization (INOUT SpecializationEntries_t &outEntries,
				INOUT SpecializationData_t &outEntryData,
				const loo::math::uint3 &localSizeSpec,
				const loo::math::uint3 &localGroupSize) const;

			bool _InitShaderStage (const VRayTracingPipeline *ppln, const RTShaderID &id, EShaderDebugMode mode,
				OUT VkPipelineShaderStageCreateInfo &stage);

			bool _GetShaderGroup (const VRayTracingPipeline *ppln, const RTShaderGroup &group, EShaderDebugMode mode,
				OUT VkRayTracingShaderGroupCreateInfoNV &group_ci);

			void _ValidateRenderState (const VDevice &dev, INOUT RenderState &renderState, INOUT EPipelineDynamicState &dynamicStates) const;
		};


	}
}