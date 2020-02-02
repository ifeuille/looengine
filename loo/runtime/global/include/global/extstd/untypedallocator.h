// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once
#include "global/extstd/memutils.h"
#include "global/extstd/bytes.h"

namespace loo
{

	template <typename T>
	struct StdAllocator;


	//
	// Untyped Default Allocator
	//

	struct UntypedAllocator
	{
		// types
		template <typename T>	using StdAllocator_t = StdAllocator<T>;

		// methods
		ND_ LOO_ALLOCATOR static void*  Allocate (BytesU size)
		{
			return ::operator new (size_t (size), std::nothrow_t{});
		}

		static void  Deallocate (void *ptr)
		{
			::operator delete (ptr, std::nothrow_t ());
		}

		static void  Deallocate (void *ptr, BytesU size)
		{
			::operator delete (ptr, size_t (size));
		}

		ND_ bool  operator == (const UntypedAllocator &) const
		{
			return true;
		}
	};



	//
	// Untyped Aligned Allocator
	//

	struct UntypedAlignedAllocator
	{
		// types
		template <typename T>	using StdAllocator_t = StdAllocator<T>;

		// methods
		ND_ LOO_ALLOCATOR static void*  Allocate (BytesU sizeBytes, BytesU alignment)
		{
			assert (0 == (int32 (alignment)&(int32(alignment) - 1))&& "AllocateAligned 0==(alignment&(alignment-1))");

			//分配为对其的内存快,并换换为u32类型
			void* rawAddress = (void*)malloc (sizeof (void*) + int32 (sizeBytes) + int32 (alignment));

			//地址对齐
			void** temp = (void**)rawAddress + 1;
			void** alignedData = (void**)(((size_t)temp + int32 (alignment) - 1)&(-int32 (alignment)));
			alignedData[-1] = rawAddress;
			return alignedData;
			//return ::operator new (size_t (size), std::align_val_t (size_t (align)), std::nothrow_t{});
		}

		static void  Deallocate (void *ptr, BytesU align)
		{
			LOO_UNUSED (align);
			if (ptr)
			{
				free (((void**)ptr)[-1]);
			}
			//::operator delete (ptr, std::align_val_t (size_t (align)), std::nothrow_t ());
		}

		static void  Deallocate (void *ptr, BytesU size, BytesU align)
		{
			LOO_UNUSED (align);
			LOO_UNUSED (size);
			if (ptr)
			{
				free (((void**)ptr)[-1]);
			}
			//::operator delete (ptr, size_t (size), std::align_val_t (size_t (align)));
		}

		ND_ bool  operator == (const UntypedAlignedAllocator &) const
		{
			return true;
		}
	};



	//
	// STD Allocator
	//

	template <typename T>
	struct StdAllocator final : std::allocator<T>
	{
		StdAllocator () {}
		StdAllocator (const UntypedAllocator &) {}
		StdAllocator (const UntypedAlignedAllocator &) {}
	};


}	// 
