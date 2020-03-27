
#pragma once
#include "vkfg/fg/framegraph.h"
#include "vkfg/fg/resourcebase.h"
#include "vkfg/fg/hashcollisioncheck.h"
#include "global/extstd/linearallocator.h"
#include "global/container/chunkedindexedpool.h"
#include "global/container/cachedindexedpool.h"
#include "global/extstd/lfindexedpool.h"
#include "vkfg/vulkan/buffer/vbuffer.h"
#include "vkfg/vulkan/image/vimage.h"
#include "vkfg/vulkan/image/vsampler.h"
#include "vkfg/vulkan/memory/vmemoryobj.h"
#include "vkfg/vulkan/pipeline/vpipelinecache.h"
#include "vkfg/vulkan/renderpass/vrenderpass.h"
#include "vkfg/vulkan/renderpass/vframebuffer.h"
//#include "vkfg/vulkan/instance/vframegraph.h"
#include "vkfg/vulkan/descriptors/vpipelineresources.h"
#include "vkfg/vulkan/raytracing/vraytracinggeometry.h"
#include "vkfg/vulkan/raytracing/vraytracingscene.h"
#include "vkfg/vulkan/raytracing/vraytracingshadertable.h"
#include "vkfg/vulkan/swapchain/vswapchain.h"
#include "vkfg/vulkan/memory/vmemorymanager.h"
#include "vkfg/vulkan/descriptors/vdescriptormanager.h"
#include "vkfg/vulkan/commandbuffer/vcmdbatch.h"

//namespace loo
//{
	/*
	=================================================
		operator ==
	=================================================
	*/
	inline bool operator == (const VkAttachmentDescription &lhs, const VkAttachmentDescription &rhs)
	{
		return	lhs.flags == rhs.flags			and
			lhs.format == rhs.format			and
			lhs.samples == rhs.samples			and
			lhs.loadOp == rhs.loadOp			and
			lhs.storeOp == rhs.storeOp			and
			lhs.stencilLoadOp == rhs.stencilLoadOp	and
			lhs.stencilStoreOp == rhs.stencilStoreOp	and
			lhs.initialLayout == rhs.initialLayout	and
			lhs.finalLayout == rhs.finalLayout;
	}

	/*
	=================================================
		operator ==
	=================================================
	*/
	inline bool operator == (const VkAttachmentReference &lhs, const VkAttachmentReference &rhs)
	{
		return	lhs.attachment == rhs.attachment	and
			lhs.layout == rhs.layout;
	}

	/*
	=================================================
		operator ==
	=================================================
	*/
	inline bool operator == (const VkSubpassDescription &lhs, const VkSubpassDescription &rhs)
	{
		using AttachView = loo::ArrayView< VkAttachmentReference >;
		using PreserveView = loo::ArrayView< loo::uint >;

		auto	lhs_resolve_attachments = lhs.pResolveAttachments ? AttachView{ lhs.pResolveAttachments, lhs.colorAttachmentCount } : AttachView{};
		auto	rhs_resolve_attachments = rhs.pResolveAttachments ? AttachView{ rhs.pResolveAttachments, rhs.colorAttachmentCount } : AttachView{};

		return	lhs.flags == rhs.flags														and
			lhs.pipelineBindPoint == rhs.pipelineBindPoint											and
			AttachView{ lhs.pInputAttachments, lhs.inputAttachmentCount } == AttachView{ rhs.pInputAttachments, rhs.inputAttachmentCount }		and
			AttachView{ lhs.pColorAttachments, lhs.colorAttachmentCount } == AttachView{ rhs.pColorAttachments, rhs.colorAttachmentCount }		and
			lhs_resolve_attachments == rhs_resolve_attachments and
			not lhs.pDepthStencilAttachment == not rhs.pDepthStencilAttachment and
			(not lhs.pDepthStencilAttachment or *lhs.pDepthStencilAttachment == *rhs.pDepthStencilAttachment) and
			PreserveView {
			lhs.pPreserveAttachments, lhs.preserveAttachmentCount
		} == PreserveView{ rhs.pPreserveAttachments, rhs.preserveAttachmentCount };
	}

	/*
	=================================================
		operator ==
	=================================================
	*/
	inline bool operator == (const VkSubpassDependency &lhs, const VkSubpassDependency &rhs)
	{
		return	lhs.srcSubpass == rhs.srcSubpass		and
			lhs.dstSubpass == rhs.dstSubpass		and
			lhs.srcStageMask == rhs.srcStageMask		and
			lhs.dstStageMask == rhs.dstStageMask		and
			lhs.srcAccessMask == rhs.srcAccessMask	and
			lhs.dstAccessMask == rhs.dstAccessMask	and
			lhs.dependencyFlags == rhs.dependencyFlags;
	}
	//inline bool operator==(const ArrayView< VkSubpassDependency>& lhs, const ArrayView< VkSubpassDependency>& rhs)
	//{
	//	return lhs.data () == rhs.data ();
	//}

//}


namespace loo
{
	namespace vkfg
	{

		//
		// Resource Manager
		//

		class VResourceManager final
		{
			// types
		public:
			using Index_t = RawImageID::Index_t;
			using AssignOpGuard_t = std::mutex;
			using CacheGuard_t = std::shared_mutex;

			template <typename T, size_t ChunkSize, size_t MaxChunks>
			using PoolTmpl = ChunkedIndexedPool< T, Index_t, ChunkSize, MaxChunks, UntypedAlignedAllocator, AssignOpGuard_t, AtomicPtr >;

			template <typename T, size_t ChunkSize, size_t MaxChunks>
			using CachedPoolTmpl = CachedIndexedPool< T, Index_t, ChunkSize, MaxChunks, UntypedAlignedAllocator, AssignOpGuard_t, CacheGuard_t, AtomicPtr >;

			static constexpr uint	MaxImages = 1u << 10;
			static constexpr uint	MaxBuffers = 1u << 10;
			static constexpr uint	MaxMemoryObjs = 1u << 10;
			static constexpr uint	MaxCached = 1u << 9;
			static constexpr uint	MaxRTObjects = 1u << 9;

			using ImagePool_t = PoolTmpl<			ResourceBase<VImage>, MaxImages, 32 >;
			using BufferPool_t = PoolTmpl<			ResourceBase<VBuffer>, MaxBuffers, 32 >;
			using MemoryPool_t = PoolTmpl<			ResourceBase<VMemoryObj>, MaxMemoryObjs, 63 >;
			using SamplerPool_t = CachedPoolTmpl<	ResourceBase<VSampler>, MaxCached, 8 >;
			using GPipelinePool_t = PoolTmpl<			ResourceBase<VGraphicsPipeline>, MaxCached, 8 >;
			using CPipelinePool_t = PoolTmpl<			ResourceBase<VComputePipeline>, MaxCached, 8 >;
			using MPipelinePool_t = PoolTmpl<			ResourceBase<VMeshPipeline>, MaxCached, 8 >;
			using RTPipelinePool_t = PoolTmpl<			ResourceBase<VRayTracingPipeline>, MaxCached, 8 >;
			using PplnLayoutPool_t = CachedPoolTmpl<	ResourceBase<VPipelineLayout>, MaxCached, 8 >;
			using DSLayoutPool_t = CachedPoolTmpl<	ResourceBase<VDescriptorSetLayout>, MaxCached, 8 >;
			using RenderPassPool_t = CachedPoolTmpl<	ResourceBase<VRenderPass>, MaxCached, 8 >;
			using FramebufferPool_t = CachedPoolTmpl<	ResourceBase<VFramebuffer>, MaxCached, 8 >;
			using PplnResourcesPool_t = CachedPoolTmpl<	ResourceBase<VPipelineResources>, MaxCached, 8 >;
			using RTGeometryPool_t = PoolTmpl<			ResourceBase<VRayTracingGeometry>, MaxRTObjects, 16 >;
			using RTScenePool_t = PoolTmpl<			ResourceBase<VRayTracingScene>, MaxRTObjects, 16 >;
			using RTShaderTablePool_t = PoolTmpl<			ResourceBase<VRayTracingShaderTable>, MaxRTObjects, 16 >;
			using SwapchainPool_t = PoolTmpl<			ResourceBase<VSwapchain>, 64, 1 >;

			using PipelineCompilers_t = HashSet< PipelineCompiler >;
			using VkShaderPtr = PipelineDescription::VkShaderPtr;
			using ShaderModules_t = Array< VkShaderPtr >;
			using DSLayouts_t = FixedArray<Pair< RawDescriptorSetLayoutID, ResourceBase<VDescriptorSetLayout> *>, LOO_MaxDescriptorSets >;

			using DebugLayoutCache_t = HashMap< uint, RawDescriptorSetLayoutID >;

			using StagingBufferfPool_t = LfIndexedPool< BufferID, uint, 32, 16 >;


			// variables
		private:
			VDevice const&				_device;
			VMemoryManager				_memoryMngr;
			VDescriptorManager			_descMngr;

			BufferPool_t				_bufferPool;
			ImagePool_t					_imagePool;
			SamplerPool_t				_samplerCache;
			MemoryPool_t				_memoryObjPool;

			GPipelinePool_t				_graphicsPplnPool;
			CPipelinePool_t				_computePplnPool;
			MPipelinePool_t				_meshPplnPool;
			RTPipelinePool_t			_rayTracingPplnPool;

			PplnLayoutPool_t			_pplnLayoutCache;
			DSLayoutPool_t				_dsLayoutCache;
			PplnResourcesPool_t			_pplnResourcesCache;

			RenderPassPool_t			_renderPassCache;
			FramebufferPool_t			_framebufferCache;

			RTGeometryPool_t			_rtGeometryPool;
			RTScenePool_t				_rtScenePool;
			RTShaderTablePool_t			_rtShaderTablePool;

			SwapchainPool_t				_swapchainPool;

			std::mutex					_shaderCacheGuard;
			ShaderModules_t				_shaderCache;

			std::shared_mutex			_compilersGuard;
			PipelineCompilers_t			_compilers;

			std::atomic<uint>			_submissionCounter;

			DebugLayoutCache_t			_debugDSLayoutsCache;

			struct {
				StagingBufferfPool_t		write;
				StagingBufferfPool_t		read;
			}							_stagingBuf;

			// cached resources validation
			struct {
				std::atomic<uint>			createdFramebuffers{ 0 };
				std::atomic<uint>			lastCheckedFramebuffer{ 0 };

				std::atomic<uint>			createdPplnResources{ 0 };
				std::atomic<uint>			lastCheckedPipelineResource{ 0 };
			}							_validation;

			// dummy resource descriptions
			const BufferDesc			_dummyBufferDesc;
			const ImageDesc				_dummyImageDesc;

			RawDescriptorSetLayoutID	_emptyDSLayout;

			DEBUG_ONLY (
				HashCollisionCheck<std::shared_mutex>	_hashCollisionCheck;
			)


				// methods
		public:
			explicit VResourceManager (const VDevice &dev);
			~VResourceManager ();

			bool Initialize ();
			void Deinitialize ();

			void AddCompiler (const PipelineCompiler &comp);
			void OnSubmit ();

			ND_ RawMPipelineID		CreatePipeline (INOUT MeshPipelineDesc &desc, StringView dbgName);
			ND_ RawGPipelineID		CreatePipeline (INOUT GraphicsPipelineDesc &desc, StringView dbgName);
			ND_ RawCPipelineID		CreatePipeline (INOUT ComputePipelineDesc &desc, StringView dbgName);
			ND_ RawRTPipelineID		CreatePipeline (INOUT RayTracingPipelineDesc &desc);

			ND_ RawImageID			CreateImage (const ImageDesc &desc, const MemoryDesc &mem, EQueueFamilyMask queueFamilyMask, EResourceState defaultState, StringView dbgName);
			ND_ RawBufferID			CreateBuffer (const BufferDesc &desc, const MemoryDesc &mem, EQueueFamilyMask queueFamilyMask, StringView dbgName);
			ND_ RawSamplerID		CreateSampler (const SamplerDesc &desc, StringView dbgName);

			ND_ RawImageID			CreateImage (const VulkanImageDesc &desc, IFrameGraph::OnExternalImageReleased_t &&onRelease, StringView dbgName);
			ND_ RawBufferID			CreateBuffer (const VulkanBufferDesc &desc, IFrameGraph::OnExternalBufferReleased_t &&onRelease, StringView dbgName);

			ND_ RawRenderPassID		CreateRenderPass (ArrayView<VLogicalRenderPass*> logicalPasses, StringView dbgName);
			ND_ RawFramebufferID	CreateFramebuffer (ArrayView<Pair<RawImageID, ImageViewDesc>> attachments, RawRenderPassID rp, loo::math::uint2 dim, uint layers, StringView dbgName);

			ND_ VPipelineResources const*	CreateDescriptorSet (const PipelineResources &desc, VCmdBatch::ResourceMap_t &);
			bool						CacheDescriptorSet (INOUT PipelineResources &desc);

			ND_ RawRTGeometryID		CreateRayTracingGeometry (const RayTracingGeometryDesc &desc, const MemoryDesc &mem, StringView dbgName);
			ND_ RawRTSceneID		CreateRayTracingScene (const RayTracingSceneDesc &desc, const MemoryDesc &mem, StringView dbgName);

			ND_ RawRTShaderTableID	CreateRayTracingShaderTable (StringView dbgName);

			ND_ RawPipelineLayoutID	CreateDebugPipelineLayout (RawPipelineLayoutID baseLayout, EShaderDebugMode debugMode, EShaderStages debuggableShaders, const DescriptorSetID &dsID);

			ND_ RawDescriptorSetLayoutID GetDescriptorSetLayout (EShaderDebugMode debugMode, EShaderStages debuggableShaders);

			ND_ RawDescriptorSetLayoutID CreateDescriptorSetLayout (const PipelineDescription::UniformMapPtr &uniforms);

			ND_ RawSwapchainID		CreateSwapchain (const VulkanSwapchainCreateInfo &desc, RawSwapchainID oldSwapchain, VFrameGraph &, StringView dbgName);

			template <typename ID>
			void ReleaseResource (ID id, uint refCount = 1);
			void ReleaseResource (INOUT PipelineResources &desc);

			template <typename ID>
			bool AcquireResource (ID id);

			template <typename ID>
			ND_ bool				IsResourceAlive (ID id)		const;

			template <typename ID>
			ND_ auto const*			GetResource (ID id, bool incRef = false, bool quiet = false) const;

			template <typename ID>
			ND_ auto const&			GetDescription (ID id)		const;

			ND_ VDevice const&		GetDevice ()				const { return _device; }
			ND_ VMemoryManager&		GetMemoryManager () { return _memoryMngr; }
			ND_ VDescriptorManager&	GetDescriptorManager () { return _descMngr; }

			ND_ uint				GetSubmitIndex ()			const { return _submissionCounter.load (memory_order_relaxed); }

			ND_ static BytesU		GetDebugShaderStorageSize (EShaderStages stages);

			void CheckTask (const BuildRayTracingScene &);

			void RunValidation (uint maxIter);

			bool CreateStagingBuffer (const BufferDesc &desc, bool write, OUT RawBufferID &id, OUT StagingBufferIdx &index);
			void ReleaseStagingBuffer (StagingBufferIdx index);


		private:
			bool  _CreateMemory (OUT RawMemoryID &id, OUT ResourceBase<VMemoryObj>* &memPtr, const MemoryDesc &desc, StringView dbgName);

			bool  _CreatePipelineLayout (OUT RawPipelineLayoutID &id, OUT ResourceBase<VPipelineLayout> const* &layoutPtr,
				PipelineDescription::PipelineLayout &&desc);

			bool  _CreatePipelineLayout (OUT RawPipelineLayoutID &id, OUT ResourceBase<VPipelineLayout> const* &layoutPtr,
				const PipelineDescription::PipelineLayout &, const DSLayouts_t &);

			bool  _CreateDescriptorSetLayout (OUT RawDescriptorSetLayoutID &id, OUT ResourceBase<VDescriptorSetLayout>* &layoutPtr,
				const PipelineDescription::UniformMapPtr &uniforms);

			template <typename ID, typename FnInitialize, typename FnCreate>
			ND_ ID  _CreateCachedResource (StringView errorStr, FnInitialize&& fnInit, FnCreate&& fnCreate);

			template <typename DescT>
			bool  _CompileShaders (INOUT DescT &desc, const VDevice &dev);
			bool  _CompileShader (INOUT ComputePipelineDesc &desc, const VDevice &dev);
			bool  _CompileSPIRVShader (const VDevice &dev, const PipelineDescription::ShaderDataUnion_t &shaderData, OUT VkShaderPtr &module);

			template <typename DataT, size_t CS, size_t MC>
			void  _DestroyResourceCache (INOUT CachedPoolTmpl<DataT, CS, MC> &pool);

			template <typename DataT, size_t CS, size_t MC>
			void  _ReleaseResource (PoolTmpl<DataT, CS, MC> &pool, DataT& data, Index_t index, uint refCount);

			template <typename DataT, size_t CS, size_t MC>
			void  _ReleaseResource (CachedPoolTmpl<DataT, CS, MC> &pool, DataT& data, Index_t index, uint refCount);

			void  _DestroyStagingBuffers ();


			// resource pool
			ND_ auto&  _GetResourcePool (const RawBufferID &) { return _bufferPool; }
			ND_ auto&  _GetResourcePool (const RawImageID &) { return _imagePool; }
			ND_ auto&  _GetResourcePool (const RawSamplerID &) { return _samplerCache; }
			ND_ auto&  _GetResourcePool (const RawMemoryID &) { return _memoryObjPool; }
			ND_ auto&  _GetResourcePool (const RawGPipelineID &) { return _graphicsPplnPool; }
			ND_ auto&  _GetResourcePool (const RawCPipelineID &) { return _computePplnPool; }
			ND_ auto&  _GetResourcePool (const RawMPipelineID &) { return _meshPplnPool; }
			ND_ auto&  _GetResourcePool (const RawRTPipelineID &) { return _rayTracingPplnPool; }
			ND_ auto&  _GetResourcePool (const RawPipelineLayoutID &) { return _pplnLayoutCache; }
			ND_ auto&  _GetResourcePool (const RawDescriptorSetLayoutID &) { return _dsLayoutCache; }
			ND_ auto&  _GetResourcePool (const RawRenderPassID &) { return _renderPassCache; }
			ND_ auto&  _GetResourcePool (const RawFramebufferID &) { return _framebufferCache; }
			ND_ auto&  _GetResourcePool (const RawPipelineResourcesID &) { return _pplnResourcesCache; }
			ND_ auto&  _GetResourcePool (const RawRTGeometryID &) { return _rtGeometryPool; }
			ND_ auto&  _GetResourcePool (const RawRTSceneID &) { return _rtScenePool; }
			ND_ auto&  _GetResourcePool (const RawRTShaderTableID &) { return _rtShaderTablePool; }
			ND_ auto&  _GetResourcePool (const RawSwapchainID &) { return _swapchainPool; }

			template <typename ID>
			ND_ const auto&  _GetResourceCPool (const ID &id)		const { return const_cast<VResourceManager *>(this)->_GetResourcePool (id); }


			// 
			template <typename ID>	ND_ bool   _Assign (OUT ID &id);
			template <typename ID>		void   _Unassign (ID id);


			// empty descriptor set layout
			bool _CreateEmptyDescriptorSetLayout ();
			ND_ auto _GetEmptyDescriptorSetLayout () { return _emptyDSLayout; }
		};



		/*
		=================================================
			GetResource
		=================================================
		*/
		template <typename ID>
		inline auto const*  VResourceManager::GetResource (ID id, bool incRef, bool quiet) const
		{
			LOO_UNUSED (quiet);
			auto&	pool = _GetResourceCPool (id);

			using Result_t = typename std::remove_reference_t<decltype(pool)>::Value_t::Resource_t const*;

			if (id.Index () < pool.size ())
			{
				auto&	data = pool[id.Index ()];

				if (data.IsCreated () and data.GetInstanceID () == id.InstanceID ())
				{
					if (incRef) data.AddRef ();
					return &data.Data ();
				}

				ASSERT (quiet or data.IsCreated ());
				ASSERT (quiet or data.GetInstanceID () == id.InstanceID ());
			}

			ASSERT (quiet and "resource index is out of range");
			return static_cast<Result_t>(null);
		}

		/*
		=================================================
			GetDescription
		=================================================
		*/
		template <>
		inline auto const&  VResourceManager::GetDescription (RawBufferID id) const
		{
			auto*	res = GetResource (id);
			return res ? res->Description () : _dummyBufferDesc;
		}

		template <>
		inline auto const&  VResourceManager::GetDescription (RawImageID id) const
		{
			auto*	res = GetResource (id);
			return res ? res->Description () : _dummyImageDesc;
		}

		/*
		=================================================
			IsResourceAlive
		=================================================
		*/
		template <typename ID>
		inline bool  VResourceManager::IsResourceAlive (ID id) const
		{
			ASSERT (id);
			auto&	pool = _GetResourceCPool (id);

			return	id.Index () < pool.size () and
				pool[id.Index ()].GetInstanceID () == id.InstanceID ();
		}

		/*
		=================================================
			AcquireResource
		=================================================
		*/
		template <typename ID>
		inline bool  VResourceManager::AcquireResource (ID id)
		{
			ASSERT (id);

			auto&	pool = _GetResourcePool (id);

			if (id.Index () < pool.size ())
			{
				auto&	data = pool[id.Index ()];

				if (not data.IsCreated () or data.GetInstanceID () != id.InstanceID ())
					return false;

				data.AddRef ();
				return true;
			}

			return false;
		}

		/*
		=================================================
			ReleaseResource
		=================================================
		*/
		template <typename ID>
		inline void  VResourceManager::ReleaseResource (ID id, uint refCount)
		{
			ASSERT (id);

			auto&	pool = _GetResourcePool (id);

			if (id.Index () >= pool.size ())
				return;

			auto&	data = pool[id.Index ()];

			if (data.GetInstanceID () != id.InstanceID ())
				return;	// this instance is already destroyed

			_ReleaseResource (pool, data, id.Index (), refCount);
		}

		template <typename DataT, size_t CS, size_t MC>
		inline void  VResourceManager::_ReleaseResource (PoolTmpl<DataT, CS, MC> &pool, DataT& data, Index_t index, uint refCount)
		{
			if (data.ReleaseRef (refCount) and data.IsCreated ())
			{
				data.Destroy (*this);
				pool.Unassign (index);
			}
		}

		template <typename DataT, size_t CS, size_t MC>
		inline void  VResourceManager::_ReleaseResource (CachedPoolTmpl<DataT, CS, MC> &pool, DataT& data, Index_t index, uint refCount)
		{
			if (data.ReleaseRef (refCount) and data.IsCreated ())
			{
				pool.RemoveFromCache (index);
				data.Destroy (*this);
				pool.Unassign (index);
			}
		}

		/*
		=================================================
			_Assign
		----
			acquire free index from cache (cache is local in thread),
			if cache empty then acquire new indices from main pool (internaly synchronized),
			if pool is full then error (false) will be returned.
		=================================================
		*/
		template <typename ID>
		inline bool  VResourceManager::_Assign (OUT ID &id)
		{
			auto&	pool = _GetResourcePool (id);

			Index_t	index = UMax;
			CHECK_ERR (pool.Assign (OUT index));

			id = ID (index, pool[index].GetInstanceID ());
			return true;
		}

		/*
		=================================================
			_Unassign
		=================================================
		*/
		template <typename ID>
		inline void  VResourceManager::_Unassign (ID id)
		{
			ASSERT (id);
			auto&	pool = _GetResourcePool (id);

			pool.Unassign (id.Index ());
		}


	}	
}