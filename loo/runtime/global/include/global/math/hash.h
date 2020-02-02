#ifndef LOO_GLOBAL_HASH_HPP
#define LOO_GLOBAL_HASH_HPP
#include "global/global.h"
#include "global/extstd/string_view.h"

namespace loo
{
	namespace global
	{
#define PRIME_NUM 0x9e3779b9

#ifdef LOO_COMPILER_MSVC
#pragma warning(disable: 4307) // The hash here could cause integral constant overflow
#endif

		size_t constexpr CTHashImpl (char const * str, size_t seed)
		{
			return 0 == *str ? seed : CTHashImpl (str + 1, seed ^ (static_cast<size_t>(*str) + PRIME_NUM + (seed << 6) + (seed >> 2)));
		}

#if defined(LOO_COMPILER_MSVC) && (_MSC_VER < 1914)
		template <size_t N>
		struct EnsureConst
		{
			static size_t constexpr value = N;
		};

#define CT_HASH(x) (loo::global::EnsureConst<CTHashImpl(x, 0)>::value)
#else
#define CT_HASH(x) (loo::global::CTHashImpl(x, 0))
#endif

		template <typename SizeT>
		inline void HashCombineImpl (SizeT& seed, SizeT value)
		{
			seed ^= value + PRIME_NUM + (seed << 6) + (seed >> 2);
		}

		inline size_t RT_HASH (char const * str)
		{
			size_t seed = 0;
			while (*str != 0)
			{
				HashCombineImpl (seed, static_cast<size_t>(*str));
				++str;
			}
			return seed;
		}

#undef PRIME_NUM

		template <typename T>
		inline size_t HashValue (T v)
		{
			return static_cast<size_t>(v);
		}

		template <typename T>
		inline size_t HashValue (T* v)
		{
			return static_cast<size_t>(reinterpret_cast<ptrdiff_t>(v));
		}

		template <typename T>
		inline void HashCombine (size_t& seed, T const & v)
		{
			return HashCombineImpl (seed, HashValue (v));
		}

		template <typename T>
		inline void HashRange (size_t& seed, T first, T last)
		{
			for (; first != last; ++first)
			{
				HashCombine (seed, *first);
			}
		}

		template <typename T>
		inline size_t HashRange (T first, T last)
		{
			size_t seed = 0;
			HashRange (seed, first, last);
			return seed;
		}
	}
}


#endif		// LOO_HASH_HPP
