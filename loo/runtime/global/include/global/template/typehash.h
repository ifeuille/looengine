#ifndef LE_ORE_TEMPLATE_CORETYPEHASH_H
#define LE_ORE_TEMPLATE_CORETYPEHASH_H
#include "global/global.h"
#include "global/template/enumasbyte.h"

namespace loo
{
	namespace global
	{


		/**
		 * Combines two hash values to get a third.
		 * Note - this function is not commutative.
		 */
		inline loo::uint32 HashCombine (loo::uint32 A, loo::uint32 C)
		{
			loo::uint32 B = 0x9e3779b9;
			A += B;

			A -= B; A -= C; A ^= (C >> 13);
			B -= C; B -= A; B ^= (A << 8);
			C -= A; C -= B; C ^= (B >> 13);
			A -= B; A -= C; A ^= (C >> 12);
			B -= C; B -= A; B ^= (A << 16);
			C -= A; C -= B; C ^= (B >> 5);
			A -= B; A -= C; A ^= (C >> 3);
			B -= C; B -= A; B ^= (A << 10);
			C -= A; C -= B; C ^= (B >> 15);

			return C;
		}


		inline loo::uint32 PointerHash (const void* Key, loo::uint32 C = 0)
		{
			// Avoid LHS stalls on PS3 and Xbox 360
#ifdef LOO_64
	// Ignoring the lower 4 bits since they are likely zero anyway.
	// Higher bits are more significant in 64 bit builds.
			auto PtrInt = reinterpret_cast<UPTRINT>(Key) >> 4;
#else
			auto PtrInt = reinterpret_cast<loo::uint32>(Key);
#endif

			return HashCombine (PtrInt, C);
		}


		//
		// Hash functions for common types.
		//

		inline loo::uint32 GetTypeHash (const uint8 A)
		{
			return A;
		}

		inline loo::uint32 GetTypeHash (const int8 A)
		{
			return A;
		}

		inline loo::uint32 GetTypeHash (const uint16 A)
		{
			return A;
		}

		inline loo::uint32 GetTypeHash (const int16 A)
		{
			return A;
		}

		inline loo::uint32 GetTypeHash (const int32 A)
		{
			return A;
		}

		inline loo::uint32 GetTypeHash (const loo::uint32 A)
		{
			return A;
		}

		inline loo::uint32 GetTypeHash (const uint64 A)
		{
			return (loo::uint32)A + ((loo::uint32)(A >> 32) * 23);
		}

		inline loo::uint32 GetTypeHash (const int64 A)
		{
			return (loo::uint32)A + ((loo::uint32)(A >> 32) * 23);
		}

#if LOO_PLATFORM_MAC
		inline loo::uint32 GetTypeHash (const __uint128_t A)
		{
			loo::uint64 Low = (uint64)A;
			loo::uint64 High = (loo::uint64)(A >> 64);
			return GetTypeHash (Low) ^ GetTypeHash (High);
		}
#endif

		inline loo::uint32 GetTypeHash (float Value)
		{
			return *(loo::uint32*)&Value;
		}

		inline loo::uint32 GetTypeHash (double Value)
		{
			return GetTypeHash (*(uint64*)&Value);
		}

		//inline uint32 GetTypeHash (const TCHAR* S)
		//{
		//	return FCrc::Strihash_DEPRECATED (S);
		//}

		inline loo::uint32 GetTypeHash (const void* A)
		{
			return PointerHash (A);
		}

		inline loo::uint32 GetTypeHash (void* A)
		{
			return PointerHash (A);
		}

		template <typename EnumType>
		LOO_FORCEINLINE  typename std::enable_if<loo::global::TIsEnum<EnumType>::Value, loo::uint32>::Type GetTypeHash (EnumType E)
		{
			return GetTypeHash ((__underlying_type (EnumType))E);
		}

		namespace UE4TypeHash_Private
		{
			template <loo::uint32 ArgToCombine, loo::uint32 ArgCount>
			struct TGetTupleHashHelper
			{
				template <typename TupleType>
				FORCEINLINE static uint32 Do (uint32 Hash, const TupleType& Tuple)
				{
					return TGetTupleHashHelper<ArgToCombine + 1, ArgCount>::Do (HashCombine (Hash, GetTypeHash (Tuple.template Get<ArgToCombine> ())), Tuple);
				}
			};

			template <loo::uint32 ArgIndex>
			struct TGetTupleHashHelper<ArgIndex, ArgIndex>
			{
				template <typename TupleType>
				FORCEINLINE static uint32 Do (uint32 Hash, const TupleType& Tuple)
				{
					return Hash;
				}
			};
		}

		template <typename... Types>
		LOO_FORCEINLINE loo::uint32 GetTypeHash (const std::tuple<Types...>& Tuple)
		{
			return UE4TypeHash_Private::TGetTupleHashHelper<1u, sizeof...(Types)>::Do (GetTypeHash (Tuple.template Get<0> ()), Tuple);
		}

		LOO_FORCEINLINE loo::uint32 GetTypeHash (const std::tuple<>& Tuple)
		{
			return 0;
		}
	}
}


#endif