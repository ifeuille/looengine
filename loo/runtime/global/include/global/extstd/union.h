// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once
#include "global/global.h"


namespace loo
{
	namespace _hidden_
	{
		//template <typename... Types>	struct overloaded final : Types... { using Types::operator()...; };

		//template <typename... Types>	overloaded (Types...)->overloaded<Types...>;
	}
}	// loo


#ifdef LOO_STD_VARIANT

# include <variant>

namespace loo
{
	template <typename ...Types>	using Union = std::variant< Types... >;
	using NullUnion = std::monostate;

	template <typename T>	constexpr std::in_place_type_t<T> InPlaceIndex{};

	template <typename... Types>
	struct TypeList< std::variant<Types...> > final : TypeList< Types... >
	{};

	/*
	=================================================
		Visit
	=================================================
	*/
	template <typename ...Types, typename ...Funcs>
	LOO_FORCEINLINE constexpr decltype(auto)  Visit (Union<Types...> &un, Funcs&&... fn)
	{
		using namespace _hidden_;
		return std::visit (overloaded{ std::forward<Funcs &&> (fn)... }, un);
	}

	template <typename ...Types, typename ...Funcs>
	LOO_FORCEINLINE constexpr decltype(auto)  Visit (const Union<Types...> &un, Funcs&&... fn)
	{
		using namespace _hidden_;
		return std::visit (overloaded{ std::forward<Funcs &&> (fn)... }, un);
	}

	/*
	=================================================
		UnionGet
	=================================================
	*/
	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T&  UnionGet (Union<Types...> &un)
	{
		return std::get<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T const&  UnionGet (const Union<Types...> &un)
	{
		return std::get<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T*  UnionGetIf (Union<Types...> *un)
	{
		return std::get_if<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T const*  UnionGetIf (const Union<Types...> *un)
	{
		return std::get_if<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr bool  HoldsAlternative (const Union<Types...> &un)
	{
		return std::holds_alternative<T> (un);
	}

}	// FGC


#else
#include "global/extstd/variant.h"


namespace loo
{
	//template <typename ...Types>	using Union = nonstd::variant< Types... >;
	using NullUnion = nonstd::monostate;

	//template <typename T>	constexpr nonstd_lite_in_place_type_t(T)  InPlaceIndex{};

	//template <typename... Types> using TypeList = nonstd::variants::detail::typelist< Types... >

	//template <typename... Types>
	//struct TypeList< nonstd::variant<Types...> > final : nonstd::variants::detail::typelist< Types... >
	//{};

	/*
	=================================================
		Visit
	=================================================
	*/
	template <typename ...Types, typename ...Funcs>
	LOO_FORCEINLINE constexpr decltype(auto)  Visit (nonstd::variant<Types...> &un, Funcs&&... fn)
	{
		//using namespace _hidden_;
		//return nonstd::visit (overloaded{ std::forward<Funcs &&> (fn)... }, un);
		return nonstd::visit (std::forward<Funcs &&> (fn)..., un);
	}

	template <typename ...Types, typename ...Funcs>
	LOO_FORCEINLINE constexpr decltype(auto)  Visit (const nonstd::variant<Types...> &un, Funcs&&... fn)
	{
		//using namespace _hidden_;
		//return nonstd::visit (overloaded{ std::forward<Funcs &&> (fn)... }, un);
		return nonstd::visit (std::forward<Funcs &&> (fn)..., un);
	}

	/*
	=================================================
		UnionGet
	=================================================
	*/
	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T&  UnionGet (nonstd::variant<Types...> &un)
	{
		return nonstd::get<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T const&  UnionGet (const nonstd::variant<Types...> &un)
	{
		return nonstd::get<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T*  UnionGetIf (nonstd::variant<Types...> *un)
	{
		return nonstd::get_if<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr T const*  UnionGetIf (const nonstd::variant<Types...> *un)
	{
		return nonstd::get_if<T> (un);
	}

	template <typename T, typename ...Types>
	ND_ LOO_FORCEINLINE constexpr bool  HoldsAlternative (const nonstd::variant<Types...> &un)
	{
		return nonstd::holds_alternative<T> (un);
	}

}	// 

//#else
//
//# error Variant is not supported!

#endif	// 
