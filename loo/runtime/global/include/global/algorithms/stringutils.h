#ifndef LOO_GLOBAL_STRINGUTILS_H
#define LOO_GLOBAL_STRINGUTILS_H
#include "global/template/externalstring.h"
#include "global/global.h"
#include "global/extstd/typetraits.h"
#include "global/template/andornot.h"
#include "global/template/isvalidvariadicfunctionarg.h"
#include "global/extstd/enumutils.h"
#include "global/extstd/arrayutils.h"
#include "global/extstd/string_view.h"
#include "global/extstd/memutils.h"
#include "global/math/math.h"
#include "global/math/color.h"
#include "global/math/vec.h"

namespace loo
{
	using namespace std::string_literals;
	/*
=================================================
	operator << (std::string, std::string)
	operator << (std::string, nonstd::string_view)
	operator << (std::string, CStyleString)
	operator << (std::string, char)
=================================================
*/
	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&&  operator << (std::basic_string<T> &&lhs, const std::basic_string<T> &rhs)
	{
		return std::move (std::move (lhs).append (rhs));
	}

	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&  operator << (std::basic_string<T> &lhs, const std::basic_string<T> &rhs)
	{
		return lhs.append (rhs);
	}

	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&&  operator << (std::basic_string<T> &&lhs, const nonstd::basic_string_view<T> &rhs)
	{
		return std::move (std::move (lhs).append (std::basic_string<T>{rhs}));
	}

	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&  operator << (std::basic_string<T> &lhs, const nonstd::basic_string_view<T> &rhs)
	{
		return lhs.append (std::basic_string<T>{rhs});
	}

	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&&  operator << (std::basic_string<T> &&lhs, T const * const rhs)
	{
		return std::move (std::move (lhs).append (rhs));
	}

	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&  operator << (std::basic_string<T> &lhs, T const * const rhs)
	{
		return lhs.append (rhs);
	}

	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&&  operator << (std::basic_string<T> &&lhs, const T rhs)
	{
		return std::move (std::move (lhs) += rhs);
	}

	template <typename T>
	LOO_FORCEINLINE std::basic_string<T>&  operator << (std::basic_string<T> &lhs, const T rhs)
	{
		return (lhs += rhs);
	}
	//-----------------------------------------------------------------------------



	/*
	=================================================
		IsUpperCase
	=================================================
	*/
	ND_ LOO_FORCEINLINE char  IsUpperCase (const char c)
	{
		return (c >= 'A' and c <= 'Z');
	}

	/*
	=================================================
		IsLowerCase
	=================================================
	*/
	ND_ LOO_FORCEINLINE char  IsLowerCase (const char c)
	{
		return (c >= 'a' and c <= 'z');
	}

	/*
	=================================================
		ToLowerCase
	=================================================
	*/
	ND_ LOO_FORCEINLINE char  ToLowerCase (const char c)
	{
		return IsUpperCase (c) ? (c - 'A' + 'a') : c;
	}

	/*
	=================================================
		ToUpperCase
	=================================================
	*/
	ND_ LOO_FORCEINLINE char  ToUpperCase (const char c)
	{
		return IsLowerCase (c) ? (c - 'a' + 'A') : c;
	}

	/*
	=================================================
		HasSubString
	----
		returns 'true' if 'str' has substring 'substr',
		comparison is case sansitive.
	=================================================
	*/
	ND_ inline bool  HasSubString (nonstd::string_view str, nonstd::string_view substr)
	{
		return (str.find (substr) != nonstd::string_view::npos);
	}

	/*
	=================================================
		HasSubStringIC
	----
		returns 'true' if 'str' has substring 'substr',
		comparison is case insansitive.
	=================================================
	*/
	ND_ inline bool  HasSubStringIC (nonstd::string_view str, nonstd::string_view substr)
	{
		if (str.empty () or substr.empty ())
			return false;

		for (size_t i = 0, j = 0; i < str.length (); ++i)
		{
			while (i + j < str.length () and j < substr.length () and
				ToLowerCase (substr[j]) == ToLowerCase (str[i + j]))
			{
				++j;
				if (j >= substr.length ())
					return true;
			}
			j = 0;
		}
		return false;
	}

	/*
	=================================================
		StartsWith
	----
		returns 'true' if 'str' starts with substring 'substr',
		comparison is case sansitive.
	=================================================
	*/
	ND_ inline bool  StartsWith (nonstd::string_view str, nonstd::string_view substr)
	{
		if (str.length () < substr.length ())
			return false;

		for (size_t i = 0; i < substr.length (); ++i)
		{
			if (str[i] != substr[i])
				return false;
		}
		return true;
	}

	/*
	=================================================
		StartsWithIC
	----
		returns 'true' if 'str' starts with substring 'substr',
		comparison is case insansitive.
	=================================================
	*/
	ND_ inline bool  StartsWithIC (nonstd::string_view str, nonstd::string_view substr)
	{
		if (str.length () < substr.length ())
			return false;

		for (size_t i = 0; i < substr.length (); ++i)
		{
			if (ToLowerCase (str[i]) != ToLowerCase (substr[i]))
				return false;
		}
		return true;
	}

	/*
	=================================================
		EndsWith
	----
		returns 'true' if 'str' ends with substring 'substr',
		comparison is case sansitive.
	=================================================
	*/
	ND_ inline bool  EndsWith (nonstd::string_view str, nonstd::string_view substr)
	{
		if (str.length () < substr.length ())
			return false;

		for (size_t i = 1; i <= substr.length (); ++i)
		{
			if (str[str.length () - i] != substr[substr.length () - i])
				return false;
		}
		return true;
	}

	/*
	=================================================
		EndsWithIC
	----
		returns 'true' if 'str' ends with substring 'substr',
		comparison is case insansitive.
	=================================================
	*/
	ND_ inline bool  EndsWithIC (nonstd::string_view str, nonstd::string_view substr)
	{
		if (str.length () < substr.length ())
			return false;

		for (size_t i = 1; i <= substr.length (); ++i)
		{
			if (ToLowerCase (str[str.length () - i]) != ToLowerCase (substr[substr.length () - i]))
				return false;
		}
		return true;
	}

	/*
	=================================================
		FindAndReplace
	=================================================
	*/
	inline uint  FindAndReplace (std::string& str, nonstd::string_view oldStr, nonstd::string_view newStr)
	{
		std::string::size_type	pos = 0;
		uint				count = 0;

		while ((pos = nonstd::string_view{ str }.find (oldStr, pos)) != nonstd::string_view::npos)
		{
			str.replace (pos, oldStr.length (), newStr.data ());
			pos += newStr.length ();
			++count;
		}
		return count;
	}
	//-----------------------------------------------------------------------------



	/*
	=================================================
		ToString
	=================================================
	*/
	template <typename T>
	ND_ LOO_FORCEINLINE EnableIf<not IsEnum<T>, std::string>  ToString (const T &value)
	{
		return std::to_string (value);
	}

	template <typename E>
	ND_ LOO_FORCEINLINE EnableIf<IsEnum<E>, std::string>  ToString (const E &value)
	{
		using T = Conditional< (sizeof (E) > sizeof (uint32_t)), uint32_t, uint64_t >;

		return std::to_string (T (value));
	}

	ND_ LOO_FORCEINLINE std::string  ToString (const bool &value)
	{
		return value ? "true" : "false";
	}

	/*
	=================================================
		ToString
	=================================================
	*/
	template <int Radix, typename T>
	ND_ LOO_FORCEINLINE EnableIf< IsEnum<T> or IsInteger<T>, std::string>  ToString (const T &value)
	{
		constexpr bool checkbool = (Radix == 16);
		if /*constexpr*/ (checkbool)
		{
			std::stringstream	str;
			str << std::hex << BitCast<NearUInt<T>> (value);
			return str.str ();
		}
		else {
			/*STATIC_*/ASSERT_MSG( false, "not supported, yet" );
		}
	}

	/*
	=================================================
		ToString (double)
	=================================================
	*/
	ND_ inline std::string  ToString (const double &value, uint fractParts)
	{
		ASSERT (fractParts > 0 and fractParts < 100);
		fractParts = loo::math::Clamp (fractParts, 1u, 99u);

		const char	fmt[8] = { '%', '0', '.', char ('0' + fractParts / 10), char ('0' + fractParts % 10), 'f', '\0' };
		char		buf[32] = {};

		const int	len = std::snprintf (buf, CountOf (buf), fmt, value);
		ASSERT (len > 0);
		return buf;
	}

	/*
	=================================================
		ToString (Vec)
	=================================================
	*/
	template <typename T, uint I>
	ND_ inline std::string  ToString (const loo::math::Vec<T,I> &value)
	{
		std::string	str = "( ";

		for (uint i = 0; i < I; ++i)
		{
			if (i > 0)	str << ", ";
			str << ToString (value[i]);
		}
		str << " )";
		return str;
	}

	/*
	=================================================
		ToString (RGBAColor)
	=================================================
	*/
	template <typename T>
	ND_ inline std::string  ToString (const loo::math::RGBAColor<T> &value)
	{
		std::string	str = "( "s;

		for (uint i = 0; i < 4; ++i)
		{
			if (i > 0)	str << ", ";
			str << ToString (value[i]);
		}
		str << " )";
		return str;
	}

	/*
	=================================================
		ToString (Bytes)
	=================================================
	*/
	template <typename T>
	ND_ inline std::string  ToString (const Bytes<T> &value)
	{
		const T	kb = T (1) << 12;
		const T mb = T (1) << 22;
		const T	gb = T (1) << loo::math::Min (T (32), T (sizeof (T) * 8) - 1);
		const T	val = T (value);

		std::string	str;

		if (val < kb)	str << ToString (val) << " b";			else
			if (val < mb)	str << ToString (val >> 10) << " Kb";	else
				if (val < gb)	str << ToString (val >> 20) << " Mb";	else
					str << ToString (val >> 30) << " Gb";
		return str;
	}

	/*
	=================================================
		ToString (chrono::duration)
	=================================================
	*/
	template <typename T, typename Duration>
	ND_ inline std::string  ToString (const std::chrono::duration<T, Duration> &value, uint precission = 2)
	{
		using SecondsD_t = std::chrono::duration<double>;
		using MicroSecD_t = std::chrono::duration<double, std::micro>;
		using NanoSecD_t = std::chrono::duration<double, std::nano>;

		const auto	time = std::chrono::duration_cast<SecondsD_t>(value).count ();
		std::string		str;

		if (time > 59.0 * 60.0)
			str << ToString (time * (1.0 / 3600.0), precission) << " h";
		else
			if (time > 59.0)
				str << ToString (time * (1.0 / 60.0), precission) << " m";
			else
				if (time > 1.0e-1)
					str << ToString (time, precission) << " s";
				else
					if (time > 1.0e-4)
						str << ToString (time * 1.0e+3, precission) << " ms";
					else
						if (time > 1.0e-7)
							str << ToString (std::chrono::duration_cast<MicroSecD_t>(value).count (), precission) << " us";
						else
							str << ToString (std::chrono::duration_cast<NanoSecD_t>(value).count (), precission) << " ns";

		return str;
	}
}
#endif