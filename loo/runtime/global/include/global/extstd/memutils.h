// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once
#include "global/global.h"
#include "global/extstd/bytes.h"

namespace loo
{

	/*
	=================================================
		AddressOf
	=================================================
	*/
	template <typename T>
	inline decltype(auto)  AddressOf (T &value)
	{
		return std::addressof (value);
	}

	/*
	=================================================
		PlacementNew
	=================================================
	*/
	template <typename T, typename ...Types>
	inline T *  PlacementNew ( void *ptr, Types&&... args)
	{
		assert (CheckPointerAlignment<T> (ptr));
		return (new(ptr) T{ std::forward<Types &&> (args)... });
	}

	/*
	=================================================
		MemCopy
	=================================================
	*/
	template <typename T1, typename T2>
	inline void  MemCopy (T1 &dst, const T2 &src)
	{
		static_assert (sizeof (dst) >= sizeof (src),"");
		//STATIC_ASSERT( std::is_trivial_v<T1> and std::is_trivial_v<T2> , "");	// TODO
		static_assert (not IsConst<T1>,"");

		std::memcpy (&dst, &src, sizeof (src));
	}

	inline void  MemCopy (void *dst, BytesU dstSize, const void *src, BytesU srcSize)
	{
		ASSERT (srcSize <= dstSize);
		ASSERT (dst and src);

		std::memcpy (dst, src, size_t (std::min (srcSize, dstSize)));
	}

	/*
	=================================================
		AllocOnStack
	=================================================
	*
		ND_ forceinline void* AllocOnStack (BytesU size)
		{
		#ifdef PLATFORM_WINDOWS
			return _alloca( size_t(size) );
		#else
			return alloca( size_t(size) );
		#endif
		}*/


}	// 
