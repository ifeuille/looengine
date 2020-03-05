#pragma once

#include "global/global.h"

#ifdef LOO_COMPILER_MSVC
# include <intrin.h>
# pragma intrinsic( _BitScanForward, _BitScanReverse )
# ifdef LOO_64
#	pragma intrinsic( _BitScanForward64, _BitScanReverse64 )
# endif
#endif

namespace loo
{

	/*
	=================================================
		IsPowerOfTwo
	=================================================
	*/
	template <typename T>
	ND_ inline constexpr bool  IsPowerOfTwo (const T &x)
	{
		return (x != 0) & ((x & (x - T (1))) == T (0));
	}

	/*
	=================================================
		IntLog2 / GetPowerOfTwo / BitScanReverse
	=================================================
	*/
	template <typename T>
	ND_ inline int  IntLog2 (const T& x)
	{
		constexpr int	INVALID_INDEX = std::numeric_limits<int>::min ();

#ifdef LOO_COMPILER_MSVC
		unsigned long	index;
		//if /*constexpr*/ (sizeof (T) > sizeof (uint32))
		//	return _BitScanReverse64 (OUT &index, x) ? index : INVALID_INDEX;
		//else
			return _BitScanReverse (OUT &index, x) ? index : INVALID_INDEX;

#elif defined(LOO_COMPILER_GCC) or defined(LOO_COMPILER_CLANG)
		/*if constexpr (sizeof (x) > sizeof (uint))
			return x ? (sizeof (x) * 8) - 1 - __builtin_clzll (x) : INVALID_INDEX;
		else*/
			return x ? (sizeof (x) * 8) - 1 - __builtin_clz (x) : INVALID_INDEX;

#else
		//return std::ilogb( x );
#endif
	}
	template <>
	ND_ inline int  IntLog2 (const uint64& x)
	{
		constexpr int	INVALID_INDEX = std::numeric_limits<int>::min ();

#ifdef LOO_COMPILER_MSVC
		unsigned long	index;
		return _BitScanReverse64 (OUT &index, x) ? index : INVALID_INDEX;

#elif defined(LOO_COMPILER_GCC) or defined(LOO_COMPILER_CLANG)
		return x ? (sizeof (x) * 8) - 1 - __builtin_clzll (x) : INVALID_INDEX;

#else
		//return std::ilogb( x );
#endif
	}
	template <>
	ND_ inline int  IntLog2 (const int64& x)
	{
		constexpr int	INVALID_INDEX = std::numeric_limits<int>::min ();

#ifdef LOO_COMPILER_MSVC
		unsigned long	index;
		return _BitScanReverse64 (OUT &index, x) ? index : INVALID_INDEX;

#elif defined(LOO_COMPILER_GCC) or defined(LOO_COMPILER_CLANG)
		return x ? (sizeof (x) * 8) - 1 - __builtin_clzll (x) : INVALID_INDEX;

#else
		//return std::ilogb( x );
#endif
	}
	template <typename T>
	ND_ inline int  BitScanReverse (const T& x)
	{
		return IntLog2 (x);
	}

	/*
	=================================================
		BitScanForward
	=================================================
	*/
	template <typename T>
	ND_ inline int  LooBitScanForward (const T& x)
	{
#ifdef LOO_COMPILER_MSVC
		constexpr int	INVALID_INDEX = std::numeric_limits<int>::min ();
		unsigned long	index;
		constexpr bool checkbool = sizeof (x) > sizeof (uint32);
		if /*constexpr*/ (/*sizeof (x) > sizeof (uint32)*/checkbool)
			return (_BitScanForward64) (OUT &index, x) ? index : INVALID_INDEX;
		else
			return (_BitScanForward) (OUT &index, x) ? index : INVALID_INDEX;

#elif defined(LOO_COMPILER_GCC) or defined(LOO_COMPILER_CLANG)
		constexpr bool checkbool = (sizeof (x) > sizeof (uint));
		if /*constexpr*/ (checkbool)
			return __builtin_ffsll (x) - 1;
		else
			return __builtin_ffs (x) - 1;

#else
#error add BitScanForward implementation
#endif
	}

	/*
	=================================================
		BitCount
	=================================================
	*/
	struct BitCountHelper
	{
		template<typename T>
		size_t operator()(const T& x)
		{
			//constexpr int si = sizeof (x);
			constexpr bool checkbool1 = (sizeof (x) == 8);
			constexpr bool checkbool2 = (sizeof (x) <= 4);
			if (checkbool1)
			{
				return std::bitset<64> (x).count ();
			}
			else if (checkbool2)
			{
				return std::bitset<32> (x).count ();
			}
			ASSERT (false);
		}
	};
	template <typename T>
	ND_ inline size_t  BitCount (const T& x)
	{
		STATIC_ASSERT (IsUnsignedInteger<T>,"");
		return BitCountHelper()(x);
		//if constexpr (sizeof (x) == 8)
		//	return std::bitset<64>(x).count ();
		//else if constexpr (sizeof (x) <= 4)
		//	return std::bitset<32> (x).count ();
	}


}	// 
