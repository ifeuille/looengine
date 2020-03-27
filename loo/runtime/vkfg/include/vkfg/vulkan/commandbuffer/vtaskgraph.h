
#pragma once


#include "vkfg/fg/framegraph.h"
#include "vkfg/fg/enumutils.h"
#include "vkfg/vulkan/vcommon.h"
namespace loo
{

	namespace vkfg
	{

		template <typename TaskType>
		class VFgTask;



		//
		// Task interface
		//

		class VFrameGraphTask : public IFrameGraphTask
		{
			// types
		protected:
			using Dependencies_t = FixedArray< VTask, LOO_MaxTaskDependencies >;
			using Name_t = SubmitRenderPass::TaskName_t;
			using ProcessFunc_t = void (*) (void *visitor, const void *taskData);


			// variables
		protected:
			ProcessFunc_t		_processFunc = null;
			Dependencies_t		_inputs;
			Dependencies_t		_outputs;
			Name_t				_taskName;
			loo::math::RGBA8u				_debugColor;
			uint				_visitorID = 0;
			ExeOrderIndex		_exeOrderIdx = ExeOrderIndex::Initial;


			// methods
		protected:
			VFrameGraphTask ()
			{}

			template <typename T>
			explicit VFrameGraphTask (const _vkfg_hidden_::BaseTask<T> &task, ProcessFunc_t process) :
				_processFunc{ process },
				_taskName{ task.taskName },
				_debugColor{ task.debugColor }
			{
				_inputs.resize (task.depends.size ());

				for (size_t i = 0; i < task.depends.size (); ++i) {
					_inputs[i] = Cast<VFrameGraphTask> (task.depends[i]);
				}

				// validate dependencies
				DEBUG_ONLY (
					for (auto& dep : task.depends) {
						ASSERT (dep != null);
					}
				)
			}


		public:
			ND_ StringView			Name ()				const { return _taskName; }
			ND_ loo::math::RGBA8u				DebugColor ()		const { return _debugColor; }
			ND_ uint				VisitorID ()		const { return _visitorID; }
			ND_ ExeOrderIndex		ExecutionOrder ()	const { return _exeOrderIdx; }

			ND_ ArrayView< VTask >	Inputs ()			const { return _inputs; }
			ND_ ArrayView< VTask >	Outputs ()			const { return _outputs; }

			void Attach (VTask output) { _outputs.push_back (output); }
			void SetVisitorID (uint id) { _visitorID = id; }
			void SetExecutionOrder (ExeOrderIndex idx) { _exeOrderIdx = idx; }

			void Process (void *visitor)			const { ASSERT (_processFunc);  _processFunc (visitor, this); }
		};



		//
		// Submit Render Pass
		//
		template <>
		class VFgTask< SubmitRenderPass > final : public VFrameGraphTask
		{
			// types
		private:
			using Self = VFgTask<SubmitRenderPass>;

			// variables
		private:
			VLogicalRenderPass *	_logicalPass = null;
			Self *					_prevSubpass = null;
			Self *					_nextSubpass = null;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const SubmitRenderPass &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ VLogicalRenderPass *	GetLogicalPass ()	const { return _logicalPass; }

			ND_ Self const *			GetPrevSubpass ()	const { return _prevSubpass; }
			ND_ Self const *			GetNextSubpass ()	const { return _nextSubpass; }

			ND_ bool					IsSubpass ()		const { return _prevSubpass != null; }
			ND_ bool					IsLastPass ()		const { return _nextSubpass == null; }
		};



		//
		// Dispatch Compute
		//
		template <>
		class VFgTask< DispatchCompute > final : public VFrameGraphTask
		{
			// variables
		private:
			VPipelineResourceSet					_resources;
			ShaderDbgIndex							_debugModeIndex = Default;
		public:
			VComputePipeline const* const			pipeline;
			const _vkfg_hidden_::PushConstants_t		pushConstants;

			const DispatchCompute::ComputeCmds_t	commands;
			const Optional< loo::math::uint3 >					localGroupSize;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const DispatchCompute &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ VPipelineResourceSet const&		GetResources ()			const { return _resources; }
			ND_ ShaderDbgIndex					GetDebugModeIndex ()	const { return _debugModeIndex; }
		};



		//
		// Dispatch Indirect Compute
		//
		template <>
		class VFgTask< DispatchComputeIndirect > final : public VFrameGraphTask
		{
			// variables
		private:
			VPipelineResourceSet					_resources;
			ShaderDbgIndex							_debugModeIndex = Default;
		public:
			VComputePipeline const* const			pipeline;
			const _vkfg_hidden_::PushConstants_t		pushConstants;

			const DispatchComputeIndirect::ComputeCmds_t	commands;

			VLocalBuffer const* const				indirectBuffer;
			const Optional< loo::math::uint3 >					localGroupSize;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const DispatchComputeIndirect &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ VPipelineResourceSet const&		GetResources ()			const { return _resources; }
			ND_ ShaderDbgIndex					GetDebugModeIndex ()	const { return _debugModeIndex; }
		};



		//
		// Copy Buffer
		//
		template <>
		class VFgTask< CopyBuffer > final : public VFrameGraphTask
		{
			// types
		private:
			using Region = CopyBuffer::Region;
			using Regions_t = CopyBuffer::Regions_t;


			// variables
		public:
			VLocalBuffer const* const	srcBuffer;
			VLocalBuffer const* const	dstBuffer;
			const Regions_t				regions;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const CopyBuffer &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Copy Image
		//
		template <>
		class VFgTask< CopyImage > final : public VFrameGraphTask
		{
			// types
		private:
			using Region = CopyImage::Region;
			using Regions_t = CopyImage::Regions_t;


			// variables
		public:
			VLocalImage const* const	srcImage;
			const VkImageLayout			srcLayout;
			VLocalImage const* const	dstImage;
			const VkImageLayout			dstLayout;
			const Regions_t				regions;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const CopyImage &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Copy Buffer to Image
		//
		template <>
		class VFgTask< CopyBufferToImage > final : public VFrameGraphTask
		{
			// types
		private:
			using Region = CopyBufferToImage::Region;
			using Regions_t = CopyBufferToImage::Regions_t;


			// variables
		public:
			VLocalBuffer const* const	srcBuffer;
			VLocalImage const* const	dstImage;
			const VkImageLayout			dstLayout;
			const Regions_t				regions;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const CopyBufferToImage &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Copy Image to Buffer
		//
		template <>
		class VFgTask< CopyImageToBuffer > final : public VFrameGraphTask
		{
			// types
		private:
			using Region = CopyImageToBuffer::Region;
			using Regions_t = CopyImageToBuffer::Regions_t;


			// variables
		public:
			VLocalImage const* const	srcImage;
			const VkImageLayout			srcLayout;
			VLocalBuffer const* const	dstBuffer;
			const Regions_t				regions;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const CopyImageToBuffer &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Blit Image
		//
		template <>
		class VFgTask< BlitImage > final : public VFrameGraphTask
		{
			// types
		private:
			using Region = BlitImage::Region;
			using Regions_t = BlitImage::Regions_t;


			// variables
		public:
			VLocalImage const* const	srcImage;
			const VkImageLayout			srcLayout;
			VLocalImage const* const	dstImage;
			const VkImageLayout			dstLayout;
			const VkFilter				filter;
			const Regions_t				regions;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const BlitImage &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Generate Mipmaps
		//
		template <>
		class VFgTask< GenerateMipmaps > final : public VFrameGraphTask
		{
			// variables
		public:
			VLocalImage const* const	image;
			const uint					baseLevel;
			const uint					levelCount;

			// methods
		public:
			VFgTask (VCommandBuffer &cb, const GenerateMipmaps &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Resolve Image
		//
		template <>
		class VFgTask< ResolveImage > final : public VFrameGraphTask
		{
			// types
		private:
			using Region = ResolveImage::Region;
			using Regions_t = ResolveImage::Regions_t;


			// variables
		public:
			VLocalImage const* const	srcImage;
			const VkImageLayout			srcLayout;

			VLocalImage const* const	dstImage;
			const VkImageLayout			dstLayout;

			const Regions_t				regions;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const ResolveImage &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Fill Buffer
		//
		template <>
		class VFgTask< FillBuffer > final : public VFrameGraphTask
		{
			// variables
		public:
			VLocalBuffer const* const	dstBuffer;
			const VkDeviceSize			dstOffset;
			const VkDeviceSize			size;
			const uint					pattern;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const FillBuffer &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Clear Color Image
		//
		template <>
		class VFgTask< ClearColorImage > final : public VFrameGraphTask
		{
			// types
		private:
			using Range = ClearColorImage::Range;
			using Ranges_t = ClearColorImage::Ranges_t;


			// variables
		public:
			VLocalImage const* const	dstImage;
			const VkImageLayout			dstLayout;
			const Ranges_t				ranges;
		private:
			VkClearColorValue			_clearValue;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const ClearColorImage &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ VkClearColorValue const&	ClearValue ()	const { return _clearValue; }
		};



		//
		// Clear Depth Stencil Image
		//
		template <>
		class VFgTask< ClearDepthStencilImage > final : public VFrameGraphTask
		{
			// types
		private:
			using Range = ClearDepthStencilImage::Range;
			using Ranges_t = ClearDepthStencilImage::Ranges_t;


			// variables
		public:
			VLocalImage const* const		dstImage;
			const VkImageLayout				dstLayout;
			const VkClearDepthStencilValue	clearValue;
			const Ranges_t					ranges;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const ClearDepthStencilImage &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Update Buffer
		//
		template <>
		class VFgTask< UpdateBuffer > final : public VFrameGraphTask
		{
			// types
		private:
			struct Region
			{
				void *			dataPtr;
				VkDeviceSize	dataSize;
				VkDeviceSize	bufferOffset;
			};


			// variables
		public:
			VLocalBuffer const* const	dstBuffer;
		private:
			ArrayView<Region>			_regions;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const UpdateBuffer &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ ArrayView<Region>	Regions ()	const { return _regions; }
		};



		//
		// Present
		//
		template <>
		class VFgTask< Present > final : public VFrameGraphTask
		{
			// variables
		public:
			VSwapchain const* const		swapchain;
			VLocalImage const* const	srcImage;
			const ImageLayer			layer;
			const MipmapLevel			mipmap;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const Present &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;
		};



		//
		// Update Ray Tracing Shader Table
		//
		template <>
		class VFgTask< UpdateRayTracingShaderTable > final : public VFrameGraphTask
		{
			friend class VCommandBuffer;

			// types
		private:
			using RayGetShader = UpdateRayTracingShaderTable::RayGenShader;
			using ShaderGroup = UpdateRayTracingShaderTable::ShaderGroup;

			// variables
		public:
			RawRTPipelineID						pipeline;
			VLocalRTScene const* const			rtScene;
			VRayTracingShaderTable * const		shaderTable;
			RayGetShader						rayGenShader;
			const uint							maxRecursionDepth;
		private:
			ShaderGroup *						_shaderGroups;
			const uint							_shaderGroupCount;

			// methods
		public:
			VFgTask (VCommandBuffer &cb, const UpdateRayTracingShaderTable &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ ArrayView< ShaderGroup >	GetShaderGroups ()	const { return { _shaderGroups, _shaderGroupCount }; }
		};



		//
		// Build Ray Tracing Geometry
		//
		template <>
		class VFgTask< BuildRayTracingGeometry > final : public VFrameGraphTask
		{
			friend class VCommandBuffer;

			// types
		private:
			using UsableBuffers_t = std::unordered_set< VLocalBuffer const*, std::hash<VLocalBuffer const*>, std::equal_to<VLocalBuffer const*>,
				StdLinearAllocator<VLocalBuffer const*> >;


			// variables
		private:
			VLocalRTGeometry const*		_rtGeometry = null;
			VLocalBuffer const*			_scratchBuffer = null;
			VkDeviceSize				_scratchBufferOffset = 0;
			VkGeometryNV *				_geometry = null;
			size_t						_geometryCount = 0;
			UsableBuffers_t				_usableBuffers;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const BuildRayTracingGeometry &task, ProcessFunc_t process);

			ND_ bool  IsValid () const { return true; }

			ND_ VLocalRTGeometry const*		RTGeometry ()			const { return _rtGeometry; }
			ND_ VLocalBuffer const*			ScratchBuffer ()		const { return _scratchBuffer; }
			ND_ VkDeviceSize				ScratchBufferOffset ()	const { return _scratchBufferOffset; }
			ND_ ArrayView<VkGeometryNV>		GetGeometry ()			const { return ArrayView<VkGeometryNV>{ _geometry, _geometryCount }; }
			ND_ UsableBuffers_t const&		GetBuffers ()			const { return _usableBuffers; }
		};



		//
		// Build Ray Tracing Scene
		//
		template <>
		class VFgTask< BuildRayTracingScene > final : public VFrameGraphTask
		{
			friend class VCommandBuffer;

			// types
		public:
			using Instance = Tuple< InstanceID, RTGeometryID, uint >;


			// variables
		private:
			VLocalRTScene const*		_rtScene = null;
			VLocalBuffer const*			_scratchBuffer = null;
			VkDeviceSize				_scratchBufferOffset = 0;
			VLocalBuffer const*			_instanceBuffer = null;
			VkDeviceSize				_instanceBufferOffset = 0;
			VLocalRTGeometry const**	_rtGeometries = null;
			Instance *					_instances = null;		// strong references
			uint						_instanceCount = 0;
			uint						_hitShadersPerInstance = 0;
			uint						_maxHitShaderCount = 0;


			// methods
		public:
			VFgTask (VCommandBuffer &, const BuildRayTracingScene &task, ProcessFunc_t process) : VFrameGraphTask{ task, process } {}

			ND_ bool  IsValid () const { return true; }

			ND_ VLocalRTScene const*				RTScene ()				const { return _rtScene; }
			ND_ VLocalBuffer const*					ScratchBuffer ()		const { return _scratchBuffer; }
			ND_ VkDeviceSize						ScratchBufferOffset ()	const { return _scratchBufferOffset; }
			ND_ VLocalBuffer const*					InstanceBuffer ()		const { return _instanceBuffer; }
			ND_ VkDeviceSize						InstanceBufferOffset ()	const { return _instanceBufferOffset; }
			ND_ uint								InstanceCount ()		const { return _instanceCount; }
			ND_ ArrayView<VLocalRTGeometry const*>	Geometries ()			const { return ArrayView<VLocalRTGeometry const*>{ _rtGeometries, _instanceCount }; }
			ND_ Instance *							Instances ()			const { return _instances; }
			ND_ uint								HitShadersPerInstance ()	const { return _hitShadersPerInstance; }
			ND_ uint								MaxHitShaderCount ()	const { return _maxHitShaderCount; }
		};



		//
		// Trace Rays
		//
		template <>
		class VFgTask< TraceRays > final : public VFrameGraphTask
		{
			// variables
		private:
			VPipelineResourceSet				_resources;
			ShaderDbgIndex						_debugModeIndex = Default;
		public:
			VRayTracingShaderTable const* const	shaderTable;
			const _vkfg_hidden_::PushConstants_t	pushConstants;

			const loo::math::uint3							groupCount;


			// methods
		public:
			VFgTask (VCommandBuffer &cb, const TraceRays &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ VPipelineResourceSet const&		GetResources ()			const { return _resources; }
			ND_ ShaderDbgIndex					GetDebugModeIndex ()	const { return _debugModeIndex; }
		};



		//
		// Custom Task
		//
		template <>
		class VFgTask< CustomTask > final : public VFrameGraphTask
		{
			// types
			using Callback_t = CustomTask::Callback_t;
			using Images_t = ArrayView< Pair< VLocalImage const*, EResourceState >>;
			using Buffers_t = ArrayView< Pair< VLocalBuffer const*, EResourceState >>;

			// variables
		private:
			Images_t			_images;
			Buffers_t			_buffers;
		public:
			const Callback_t	callback;

			// methods
			VFgTask (VCommandBuffer &cb, const CustomTask &task, ProcessFunc_t process);

			ND_ bool  IsValid () const;

			ND_ Images_t	GetImages ()	const { return _images; }
			ND_ Buffers_t	GetBuffers ()	const { return _buffers; }
		};



		//
		// Task Graph
		//
		template <typename VisitorT>
		class VTaskGraph
		{
			// types
		private:
			using Self = VTaskGraph< VisitorT >;
			using Allocator_t = LinearAllocator<>;
			using SearchableNodes_t = std::unordered_set< VTask, std::hash<VTask>, std::equal_to<VTask>, StdLinearAllocator<VTask> >;
			using Entries_t = std::vector< VTask, StdLinearAllocator<VTask> >;


			// variables
		private:
			InPlace<SearchableNodes_t>	_nodes;
			InPlace<Entries_t>			_entries;


			// methods
		public:
			VTaskGraph () {}
			~VTaskGraph () {}

			template <typename T>
			ND_ VFgTask<T>*  Add (VCommandBuffer &cb, const T &task);

			void OnStart (LinearAllocator<> &);
			void OnDiscardMemory ();

			ND_ ArrayView<VTask>	Entries ()		const { return *_entries; }
			ND_ size_t				Count ()		const { return _nodes->size (); }
			ND_ bool				Empty ()		const { return _nodes->empty (); }


		private:
			template <typename T>
			static void _Visitor (void *p, const void *task)
			{
				static_cast<VisitorT *>(p)->Visit (*static_cast<VFgTask<T> const *>(task));
			}
		};


		/*
		//
		// Render Pass Graph
		//
		class VRenderPassGraph
		{
		// methods
		public:
			void Add (const VFgTask<SubmitRenderPass> *)
			{
			}

			void Clear ()
			{
			}
		};*/



		/*
		=================================================
			OnStart
		=================================================
		*/
		template <typename VisitorT>
		inline void  VTaskGraph<VisitorT>::OnStart (LinearAllocator<> &alloc)
		{
			_nodes.Create (alloc);
			_entries.Create (alloc);
			_entries->reserve (64);
		}

		/*
		=================================================
			OnDiscardMemory
		=================================================
		*/
		template <typename VisitorT>
		inline void  VTaskGraph<VisitorT>::OnDiscardMemory ()
		{
			_nodes.Destroy ();
			_entries.Destroy ();
		}


	}
}