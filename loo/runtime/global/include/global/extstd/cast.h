// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once
#include "global/global.h"
#include "global/extstd/bitmath.h"
#include "global/extstd/ptr.h"

namespace loo
{

	/*
	=================================================
		Cast
	=================================================
	*/
	template <typename R, typename T>
	ND_ inline std::shared_ptr<R>  Cast (const std::shared_ptr<T> &other)
	{
		return std::static_pointer_cast<R>(other);
	}

	/*
	=================================================
		DynCast
	=================================================
	*/
	template <typename R, typename T>
	ND_ inline std::shared_ptr<R>  DynCast (const std::shared_ptr<T> &other)
	{
		return std::dynamic_pointer_cast<R>(other);
	}

	/*
	=================================================
		CheckPointerAlignment
	=================================================
	*/
	template <typename R, typename T>
	ND_ inline bool  CheckPointerAlignment (T const* ptr)
	{
		constexpr size_t	align = alignof(R);

		STATIC_ASSERT (IsPowerOfTwo (align), "Align must be power of 2");

		return (sizeof (R) < align) or not (size_t (ptr) & (align - 1));
	}

	/*
	=================================================
		Cast
	=================================================
	*/
	template <typename R, typename T>
	ND_ inline constexpr R const volatile*  Cast (T const volatile* value)
	{
		ASSERT (CheckPointerAlignment<R> (value));
		return static_cast<R const volatile *>(static_cast<void const volatile *>(value));
	}

	template <typename R, typename T>
	ND_ inline constexpr R volatile*  Cast (T volatile* value)
	{
		ASSERT (CheckPointerAlignment<R> (value));
		return static_cast<R volatile *>(static_cast<void volatile *>(value));
	}

	template <typename R, typename T>
	ND_ inline constexpr R const*  Cast (T const* value)
	{
		ASSERT (CheckPointerAlignment<R> (value));
		return static_cast<R const *>(static_cast<void const *>(value));
	}

	template <typename R, typename T>
	ND_ inline constexpr R*  Cast (T* value)
	{
		ASSERT (CheckPointerAlignment<R> (value));
		return static_cast<R *>(static_cast<void *>(value));
	}

	template <typename R, typename T>
	ND_ inline constexpr Ptr<R const>  Cast (Ptr<T const> value)
	{
		return Cast<R> (value.operator->());
	}

	template <typename R, typename T>
	ND_ inline constexpr Ptr<R>  Cast (Ptr<T> value)
	{
		return Cast<R> (value.operator->());
	}

	/*
	=================================================
		DynCast
	=================================================
	*/
	template <typename R, typename T>
	ND_ inline constexpr R const*  DynCast (T const* value)
	{
		return dynamic_cast<R const *>(value);
	}

	template <typename R, typename T>
	ND_ inline constexpr R*  DynCast (T* value)
	{
		return dynamic_cast<R *>(value);
	}

	template <typename R, typename T>
	ND_ inline constexpr Ptr<R const>  DynCast (Ptr<T const> value)
	{
		return DynCast<R> (value.operator->());
	}

	template <typename R, typename T>
	ND_ inline constexpr Ptr<R>  DynCast (Ptr<T> value)
	{
		return DynCast<R> (value.operator->());
	}

	/*
	=================================================
		BitCast
	=================================================
	*/
	template <typename To, typename From>
	ND_ inline constexpr To  BitCast (const From& src)
	{
		STATIC_ASSERT (sizeof (To) == sizeof (From), "must be same size!");
		STATIC_ASSERT (alignof(To) == alignof(From), "must be same align!");
		//STATIC_ASSERT( std::is_trivially_copyable<From>::value and std::is_trivial<To>::value, "must be trivial types!" );

		To	dst;
		std::memcpy (&dst, &src, sizeof (To));
		return dst;
	}


}	// 
