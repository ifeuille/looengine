#include "vkfg/vulkan/memory/vmemorymanager.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			constructor
		=================================================
		*/
		VMemoryManager::VMemoryManager (const VDevice &dev) :
			_device{ dev }
		{
		}

		/*
		=================================================
			destructor
		=================================================
		*/
		VMemoryManager::~VMemoryManager ()
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			ASSERT (_allocators.empty ());
		}

		/*
		=================================================
			Initialize
		=================================================
		*/
		bool VMemoryManager::Initialize ()
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			using MT = EMemoryTypeExt;

			// TODO: use custom mem allocator?
#	ifdef LOO_ENABLE_VULKAN_MEMORY_ALLOCATOR
			_allocators.push_back (_CreateVMA ());
#	else
			_allocators.push_back (AllocatorPtr{ new HostMemAllocator{ _frameGraph, MT::HostCached | MT::HostWrite | MT::ForBuffer } });
			_allocators.push_back (AllocatorPtr{ new HostMemAllocator{ _frameGraph, MT::HostCached | MT::HostRead | MT::ForBuffer } });
			_allocators.push_back (AllocatorPtr{ new DedicatedMemAllocator{ _frameGraph, MT::LocalInGPU | MT::Dedicated | MT::ForBuffer | MT::ForImage } });
			_allocators.push_back (AllocatorPtr{ new DeviceMemAllocator{ _frameGraph, MT::LocalInGPU | MT::ForBuffer | MT::ForImage } });
			_allocators.push_back (AllocatorPtr{ new VirtualMemAllocator{ _frameGraph, MT::LocalInGPU | MT::Virtual | MT::AllowAliasing | MT::ForBuffer | MT::ForImage } });
#	endif
			return true;
		}

		/*
		=================================================
			Deinitialize
		=================================================
		*/
		void VMemoryManager::Deinitialize ()
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			_allocators.clear ();
		}

		/*
		=================================================
			AllocateForImage
		=================================================
		*/
		bool VMemoryManager::AllocateForImage (VkImage image, const MemoryDesc &desc, INOUT Storage_t &data)
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			ASSERT (not _allocators.empty ());

			for (size_t i = 0; i < _allocators.size (); ++i)
			{
				auto&	alloc = _allocators[i];

				if (alloc->IsSupported (desc.type))
				{
					CHECK_ERR (alloc->AllocForImage (image, desc, OUT data));

					*data.Cast<uint> () = uint (i);
					return true;
				}
			}
			RETURN_ERR ("unsupported memory type");
		}

		/*
		=================================================
			AllocateForBuffer
		=================================================
		*/
		bool VMemoryManager::AllocateForBuffer (VkBuffer buffer, const MemoryDesc &desc, INOUT Storage_t &data)
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			ASSERT (not _allocators.empty ());

			for (size_t i = 0; i < _allocators.size (); ++i)
			{
				auto&	alloc = _allocators[i];

				if (alloc->IsSupported (desc.type))
				{
					CHECK_ERR (alloc->AllocForBuffer (buffer, desc, OUT data));

					*data.Cast<uint> () = uint (i);
					return true;
				}
			}
			RETURN_ERR ("unsupported memory type");
		}

		/*
		=================================================
			AllocateForAccelStruct
		=================================================
		*/
		bool VMemoryManager::AllocateForAccelStruct (VkAccelerationStructureNV accelStruct, const MemoryDesc &desc, OUT Storage_t &data)
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			ASSERT (not _allocators.empty ());

			for (size_t i = 0; i < _allocators.size (); ++i)
			{
				auto&	alloc = _allocators[i];

				if (alloc->IsSupported (desc.type))
				{
					CHECK_ERR (alloc->AllocateForAccelStruct (accelStruct, desc, OUT data));

					*data.Cast<uint> () = uint (i);
					return true;
				}
			}
			RETURN_ERR ("unsupported memory type");
		}

		/*
		=================================================
			Deallocate
		=================================================
		*/
		bool VMemoryManager::Deallocate (INOUT Storage_t &data)
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);

			const uint	alloc_id = *data.Cast<uint> ();
			CHECK_ERR (alloc_id < _allocators.size ());

			CHECK_ERR (_allocators[alloc_id]->Dealloc (INOUT data));
			return true;
		}

		/*
		=================================================
			GetMemoryInfo
		=================================================
		*/
		bool VMemoryManager::GetMemoryInfo (const Storage_t &data, OUT MemoryInfo_t &info) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);

			const uint	alloc_id = *data.Cast<uint> ();
			CHECK_ERR (alloc_id < _allocators.size ());

			CHECK_ERR (_allocators[alloc_id]->GetMemoryInfo (data, OUT info));
			return true;
		}


	}	
}