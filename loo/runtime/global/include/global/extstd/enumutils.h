// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "global/global.h"
#include "global/extstd/typetraits.h"

namespace loo
{

	template <typename T>
	using NearInt = Conditional< (sizeof (T) <= sizeof (int32_t)), int32_t, int64_t >;

	template <typename T>
	using NearUInt = Conditional< (sizeof (T) <= sizeof (uint32_t)), uint32_t, uint64_t >;

	/*
	=================================================
		EnumToUInt
	=================================================
	*/
	template <typename T>
	ND_ LOO_FORCEINLINE constexpr NearUInt<T>  EnumToUInt (const T &value)
	{
		STATIC_ASSERT (IsScalarOrEnum<T>, "");
		STATIC_ASSERT (sizeof (value) <= sizeof (NearUInt<T>), "");

		return NearUInt<T> (value);
	}

	/*
	=================================================
		EnumToInt
	=================================================
	*/
	template <typename T>
	ND_ LOO_FORCEINLINE constexpr NearInt<T>  EnumToInt (const T &value)
	{
		STATIC_ASSERT (IsScalarOrEnum<T>, "");
		STATIC_ASSERT (sizeof (value) <= sizeof (NearInt<T>), "");

		return NearInt<T> (value);
	}

	/*
	=================================================
		EnumEq
	----
		returns 'true' if 'lhs' has ALL bits that presented in 'rhs'
	=================================================
	*/
	template <typename T1, typename T2>
	ND_ LOO_FORCEINLINE constexpr bool  EnumEq (const T1& lhs, const T2& rhs)
	{
		STATIC_ASSERT (IsScalarOrEnum< T1 >, "");
		STATIC_ASSERT (IsScalarOrEnum< T2 >, "");
		ASSERT (rhs != T2 (0));

		return (EnumToUInt (lhs) & EnumToUInt (rhs)) == EnumToUInt (rhs);
	}

	/*
	=================================================
		EnumAny
	----
		returns 'true' if 'lhs' has ANY bit that presented in 'rhs'
	=================================================
	*/
	template <typename T1, typename T2>
	ND_ LOO_FORCEINLINE constexpr bool  EnumAny (const T1& lhs, const T2& rhs)
	{
		STATIC_ASSERT (IsScalarOrEnum< T1 >, "");
		STATIC_ASSERT (IsScalarOrEnum< T2 >, "");
		ASSERT (rhs != T2 (0));

		return !!(EnumToUInt (lhs) & EnumToUInt (rhs));
	}

}
