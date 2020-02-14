
#pragma once


#include "vkfg/fg/framegraphdrawtask.h"
#include "vkfg/vulkan/vcommon.h"

namespace loo
{
	namespace vkfg
	{

		template <typename VTask>
		class VFgDrawTask;



		//
		// Draw Task interface
		//
		class IDrawTask
		{
			// types
		public:
			using Name_t = _vkfg_hidden_::TaskName_t;
			using ProcessFunc_t = void (*) (void *visitor, void *taskData);


			// variables
		private:
			ProcessFunc_t	_pass1 = null;
			ProcessFunc_t	_pass2 = null;
			Name_t			_taskName;
			loo::math::RGBA8u			_debugColor;


			// interface
		protected:
			template <typename TaskType>
			IDrawTask (const TaskType &task, ProcessFunc_t pass1, ProcessFunc_t pass2) :
				_pass1{ pass1 }, _pass2{ pass2 }, _taskName{ task.taskName }, _debugColor{ task.debugColor } {}

		public:
			ND_ StringView	GetName ()			const { return _taskName; }
			ND_ loo::math::RGBA8u		GetDebugColor ()	const { return _debugColor; }

			void Process1 (void *visitor) { ASSERT (_pass1);  _pass1 (visitor, this); }
			void Process2 (void *visitor) { ASSERT (_pass2);  _pass2 (visitor, this); }
		};



		//
		// Base Draw Vertices Task
		//
		class VBaseDrawVerticesTask : public IDrawTask
		{
			// types
		public:
			using VertexBuffers_t = StaticArray< VLocalBuffer const*, LOO_MaxVertexBuffers >;
			using VertexOffsets_t = StaticArray< VkDeviceSize, LOO_MaxVertexBuffers >;
			using VertexStrides_t = StaticArray< Bytes<uint>, LOO_MaxVertexBuffers >;


			// variables
		private:
			VPipelineResourceSet					_resources;

			VertexBuffers_t							_vertexBuffers;
			VertexOffsets_t							_vbOffsets;
			VertexStrides_t							_vbStrides;
			const uint								_vbCount;

			ArrayView< loo::math::RectI >						_scissors;
			ShaderDbgIndex							_debugModeIndex = Default;

		public:
			VGraphicsPipeline const* const			pipeline;
			const _vkfg_hidden_::PushConstants_t		pushConstants;

			const VertexInputState					vertexInput;

			const _vkfg_hidden_::ColorBuffers_t		colorBuffers;
			const _vkfg_hidden_::DynamicStates		dynamicStates;

			const EPrimitive						topology;
			const bool								primitiveRestart;

			mutable VkDescriptorSets_t				descriptorSets;


			// methods
		protected:
			template <typename TaskType>
			VBaseDrawVerticesTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const TaskType &task, ProcessFunc_t pass1, ProcessFunc_t pass2);

		public:
			ND_ VPipelineResourceSet const&		GetResources ()			const { return _resources; }
			ND_ ArrayView< loo::math::RectI >				GetScissors ()			const { return _scissors; }
			ND_ ShaderDbgIndex					GetDebugModeIndex ()	const { return _debugModeIndex; }

			ND_ ArrayView< VLocalBuffer const*>	GetVertexBuffers ()		const { return ArrayView< VLocalBuffer const*>( _vertexBuffers.data (), _vbCount ); }
			ND_ ArrayView< VkDeviceSize >		GetVBOffsets ()			const { return ArrayView< VkDeviceSize>( _vbOffsets.data (), _vbCount ); }
			ND_ ArrayView< Bytes<uint> >		GetVBStrides ()			const { return ArrayView< Bytes<uint>>( _vbStrides.data (), _vbCount ); }
		};



		//
		// Draw Vertices
		//
		template <>
		class VFgDrawTask< DrawVertices > final : public VBaseDrawVerticesTask
		{
		public:
			// variables
			const DrawVertices::DrawCommands_t		commands;

			// methods
			VFgDrawTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const DrawVertices &task, ProcessFunc_t pass1, ProcessFunc_t pass2);
		};



		//
		// Draw Indexed Vertices
		//
		template <>
		class VFgDrawTask< DrawIndexed > final : public VBaseDrawVerticesTask
		{
		public:
			// variables
			const DrawIndexed::DrawCommands_t	commands;

			VLocalBuffer const* const			indexBuffer;
			const BytesU						indexBufferOffset;
			const EIndex						indexType;

			// methods
			VFgDrawTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const DrawIndexed &task, ProcessFunc_t pass1, ProcessFunc_t pass2);
		};



		//
		// Draw Vertices Indirect
		//
		template <>
		class VFgDrawTask< DrawVerticesIndirect > final : public VBaseDrawVerticesTask
		{
		public:
			// variables
			const DrawVerticesIndirect::DrawCommands_t		commands;
			VLocalBuffer const* const						indirectBuffer;

			// methods
			VFgDrawTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const DrawVerticesIndirect &task, ProcessFunc_t pass1, ProcessFunc_t pass2);
		};



		//
		// Draw Indexed Vertices Indirect
		//
		template <>
		class VFgDrawTask< DrawIndexedIndirect > final : public VBaseDrawVerticesTask
		{
		public:
			// variables
			const DrawIndexedIndirect::DrawCommands_t	commands;
			VLocalBuffer const* const					indirectBuffer;

			VLocalBuffer const* const					indexBuffer;
			const BytesU								indexBufferOffset;
			const EIndex								indexType;

			// methods
			VFgDrawTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const DrawIndexedIndirect &task, ProcessFunc_t pass1, ProcessFunc_t pass2);
		};



		//
		// Base Draw Meshes
		//
		class VBaseDrawMeshes : public IDrawTask
		{
			// variables
		private:
			VPipelineResourceSet					_resources;
			ArrayView< loo::math::RectI >						_scissors;
			ShaderDbgIndex							_debugModeIndex = Default;
		public:
			VMeshPipeline const* const				pipeline;
			const _vkfg_hidden_::PushConstants_t		pushConstants;

			const _vkfg_hidden_::ColorBuffers_t		colorBuffers;
			const _vkfg_hidden_::DynamicStates		dynamicStates;

			mutable VkDescriptorSets_t				descriptorSets;


			// methods
		protected:
			template <typename TaskType>
			VBaseDrawMeshes (VLogicalRenderPass &rp, VCommandBuffer &cb, const TaskType &task, ProcessFunc_t pass1, ProcessFunc_t pass2);

		public:
			ND_ VPipelineResourceSet const&		GetResources ()			const { return _resources; }
			ND_ ArrayView< loo::math::RectI >				GetScissors ()			const { return _scissors; }
			ND_ ShaderDbgIndex					GetDebugModeIndex ()	const { return _debugModeIndex; }
		};



		//
		// Draw Meshes
		//
		template <>
		class VFgDrawTask< DrawMeshes > final : public VBaseDrawMeshes
		{
		public:
			// variables
			const DrawMeshes::DrawCommands_t	commands;

			// methods
			VFgDrawTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const DrawMeshes &task, ProcessFunc_t pass1, ProcessFunc_t pass2);
		};



		//
		// Draw Meshes Indirect
		//
		template <>
		class VFgDrawTask< DrawMeshesIndirect > final : public VBaseDrawMeshes
		{
		public:
			// variables
			const DrawMeshesIndirect::DrawCommands_t	commands;
			VLocalBuffer const* const					indirectBuffer;

			// methods
			VFgDrawTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const DrawMeshesIndirect &task, ProcessFunc_t pass1, ProcessFunc_t pass2);
		};



		//
		// Custom Draw
		//
		template <>
		class VFgDrawTask< CustomDraw > final : public IDrawTask
		{
			// types
			using Callback_t = CustomDraw::Callback_t;
			using Images_t = ArrayView< Pair< VLocalImage const*, EResourceState >>;
			using Buffers_t = ArrayView< Pair< VLocalBuffer const*, EResourceState >>;

			// variables
		private:
			Images_t			_images;
			Buffers_t			_buffers;
		public:
			const Callback_t	callback;

			// methods
			VFgDrawTask (VLogicalRenderPass &rp, VCommandBuffer &cb, const CustomDraw &task, ProcessFunc_t pass1, ProcessFunc_t pass2);

			ND_ Images_t	GetImages ()	const { return _images; }
			ND_ Buffers_t	GetBuffers ()	const { return _buffers; }
		};


	}
}