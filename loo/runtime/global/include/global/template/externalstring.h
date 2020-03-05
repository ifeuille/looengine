#ifndef LOO_CORE_EXTERNALSTRING_H
#define LOO_CORE_EXTERNALSTRING_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdarg.h>
#include <algorithm>
#include <codecvt>
#include <string>
//#include <locale>
#include "global/global.h"
#include "global/extstd/typetraits.h"
#include "global/template/andornot.h"
#include "global/template/isvalidvariadicfunctionarg.h"

#if (defined WIN32) ||  (defined _WIN32)
#include<Windows.h>
#else
#include<unistd.h> 
#include<sys/types.h>
#include<strings.h>
#include <stdlib.h>
#endif

#include <limits>


namespace loo
{
	namespace global
	{
		inline bool IsNumeric ( const char* Str )
		{
			if (*Str == '-' || *Str == '+')
			{
				Str++;
			}

			bool bHasDot = false;
			while (*Str != '\0')
			{
				if (*Str == '.')
				{
					if (bHasDot)
					{
						return false;
					}
					bHasDot = true;
				}
				/*else if (!std::isdigit ( *Str, std::locale ( ) ))
				{
					return false;
				}*/

				++Str;
			}

			return true;
		}

		inline std::string Left (std::string& str, int32_t Count)
		{
			Count = std::min (Count, std::max (0, static_cast<int32_t>(str.length ())));
			std::string retString;
			retString.copy ( &str[0], Count );
			return retString;
		}

		inline bool IsNumeric ( const std::string& str )
		{
			if (str.empty ( ))
				return false;
			return IsNumeric ( str.c_str ( ) );
		}


		// This starting size catches 99.97% of printf calls - there are about 700k printf calls per level
		inline  std::string  VARARGS PrintfImpl ( const char* Fmt, ... )
		{
			char buf[STARTING_BUFFER_SIZE];

			va_list ap;
			va_start ( ap, Fmt );

			int writtenBytes{};
			writtenBytes = std::vsnprintf ( buf, STARTING_BUFFER_SIZE, Fmt, ap );
			if (!writtenBytes) {
				std::wcout << L"Cannot Output std::string" << std::endl;
				return std::string{};
			}

			va_end ( ap );
			return std::string{ buf };
		}

		template <typename FmtType, typename... Types>
		inline std::string Printf ( const FmtType& Fmt, Types... Args )
		{
			static_assert(loo::global::TAnd<loo::global::TIsValidVariadicFunctionArg<Types>...>::Value, "Invalid argument(s) passed to FString::Printf");
			
			return PrintfImpl ( Fmt, Args... );
		}

		inline bool start_with ( const std::string& str, const std::string& subStr )
		{
			if (str.length ( ) >= subStr.length ( ))
			{
				for (size_t i = 0; i < subStr.length ( ); ++i)
				{
					if (str[i] != subStr[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}

		inline std::string  replace_all ( const std::string&   str, const   std::string&   old_value, const   std::string&   new_value )
		{
			std::string result = str;
			while (true) {
				std::string::size_type   pos ( 0 );
				if ((pos = result.find ( old_value )) != std::string::npos)
					result.replace ( pos, old_value.length ( ), new_value );
				else   break;
			}
			return   result;
		}
		inline std::string&  replace_all_inline ( std::string&   str, const   std::string&   old_value, const   std::string&   new_value )
		{
			while (true) {
				std::string::size_type   pos ( 0 );
				if ((pos = str.find ( old_value )) != std::string::npos)
					str.replace ( pos, old_value.length ( ), new_value );
				else   break;
			}
			return   str;
		}
		inline std::string   replace_all_distinct ( const std::string&   str, const   std::string&   old_value, const  std::string&   new_value )
		{
			std::string result = str;
			for (std::string::size_type pos ( 0 ); pos != std::string::npos; pos += new_value.length ( )) {
				if ((pos = result.find ( old_value, pos )) != std::string::npos)
					result.replace ( pos, old_value.length ( ), new_value );
				else   break;
			}
			return   result;
		}


		inline std::size_t wc2mbs(const wchar_t *wc, std::size_t wc_size, char *mbs,std::size_t c_size)
		{
			std::size_t mbs_size;
#if (defined WIN32) ||  (defined _WIN32)
			setlocale(LC_ALL, "chs");
#else
			setlocale(LC_ALL, "zh_CN.gbk");
#endif
#if defined(LOO_COMPILER_MSVC)
			wcstombs_s (&mbs_size, mbs, wc_size, wc, c_size);
#else
			LOO_UNUSED (wc_size);
			mbs_size = wcstombs ( mbs, wc, c_size);
#endif
			return mbs_size;
		}

		inline std::size_t mbs2wc(const char *mbs, std::size_t mbs_size, wchar_t *wc,std::size_t wc_size)
		{
			std::size_t out_wc_size;
#if (defined WIN32) ||  (defined _WIN32)
			setlocale(LC_ALL, "chs");
#else
			setlocale(LC_ALL, "zh_CN.gbk");
#endif

			if (mbs_size == 0)
				mbs_size = UINT_MAX;			
#if defined(LOO_COMPILER_MSVC)
			mbstowcs_s (&out_wc_size, wc, wc_size, mbs, mbs_size);
#else
			LOO_UNUSED (wc_size);
			out_wc_size = mbstowcs (wc, mbs, mbs_size);
#endif
			return out_wc_size;
		}


		template<typename T, typename P>
		inline bool is_equal(T left, P right)
		{
			return left == right;
		}

		template<>
		inline bool is_equal(const char* left, const char* right)
		{
			return 0 == std::strcmp(left, right);
		}

		template<>
		inline bool is_equal(char* left, char* right)
		{
			return 0 == std::strcmp(left, right);
		}

		template<>
		inline bool is_equal(char* left, const char* right)
		{
			return 0 == std::strcmp(left, right);
		}

		template<>
		inline bool is_equal(const char* left, char* right)
		{
			return 0 == std::strcmp(left, right);
		}

		template<>
		inline bool is_equal(const char* left, std::string right)
		{
			return right == left;
		}
	}

	
}

#endif