#ifndef LOO_GLOBAL_UTLIS_H
#define LOO_GLOBAL_UTLIS_H
#pragma once
#include "global/global.h"
#include <string>
#include "global/extstd/string_view.h"
using namespace std;

namespace loo
{
	namespace global
	{
		inline uint32_t
			SetMask (uint32_t n) noexcept
		{
			return 1UL << n;
		}
		template <uint32_t n>
		struct Mask
		{
			enum { value = 1UL << n };
		};

		inline uint32_t
			GetBit (uint32_t x, uint32_t n) noexcept
		{
			return (x >> n) & 1;
		}

		inline uint32_t
			SetBit (uint32_t x, uint32_t n)
		{
			return x | SetMask (n);
		}

		inline uint16_t
			LO_U8 (uint16_t x) noexcept
		{
			return x & 0xFF;
		}

		inline uint16_t
			HI_U8 (uint16_t x) noexcept
		{
			return x >> 8;
		}


		inline uint32_t
			LO_U16 (uint32_t x) noexcept
		{
			return x & 0xFFFF;
		}

		inline uint32_t
			HI_U16 (uint32_t x) noexcept
		{
			return x >> 16;
		}


		inline uint16_t
			HI_LO_SwapU8 (uint16_t x) noexcept
		{
			return (LO_U8 (x) << 8) | HI_U8 (x);
		}


		inline uint32_t
			HI_LO_SwapU16 (uint32_t x) noexcept
		{
			return (LO_U16 (x) << 16) | HI_U16 (x);
		}


		inline uint32_t
			MakeMask (uint32_t n) noexcept
		{
			return (1UL << (n + 1)) - 1;
		}


		template <unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3>
		struct MakeFourCC
		{
			enum { value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24) };
		};

		std::string& Convert (std::string& dest, nonstd::string_view src);
		std::string& Convert (std::string& dest, nonstd::wstring_view src);
		std::wstring& Convert (std::wstring& dest, nonstd::string_view src);
		std::wstring& Convert (std::wstring& dest, nonstd::wstring_view src);


		void Sleep (uint32_t ms);



		template <int size>
		void EndianSwitch (void* p) noexcept;

		

		template <typename T>
		T Native2BE (T x) noexcept
		{
			/*LE_IF_CONSTEXPR*/if (std::endian::native == std::endian::little)
			{
				EndianSwitch<sizeof (T)> (&x);
			}
			return x;
		}
		template <typename T>
		T Native2LE (T x) noexcept
		{
			/*LE_IF_CONSTEXPR*/if (std::endian::native == std::endian::big)
			{
				EndianSwitch<sizeof (T)> (&x);
			}
			return x;
		}

		template <typename T>
		T BE2Native (T x) noexcept
		{
			return Native2BE (x);
		}
		template <typename T>
		T LE2Native (T x) noexcept
		{
			return Native2LE (x);
		}


		template <typename To, typename From>
		inline To
			checked_cast (From p) noexcept
		{
			assert (dynamic_cast<To>(p) == static_cast<To>(p));
			return static_cast<To>(p);
		}

		template <typename To, typename From>
		inline std::shared_ptr<To>
			checked_pointer_cast (std::shared_ptr<From> const & p) noexcept
		{
			assert (std::dynamic_pointer_cast<To>(p) == std::static_pointer_cast<To>(p));
			return std::static_pointer_cast<To>(p);
		}

		uint32_t LastError ();

		//std::string ReadShortString (ResIdentifierPtr const & res);
		void WriteShortString (std::ostream& os, nonstd::string_view str);

		template <typename T, typename... Args>
		inline std::shared_ptr<T> MakeSharedPtr (Args&&... args)
		{
			return std::make_shared<T> (std::forward<Args> (args)...);
		}

		template <typename T, typename... Args>
		inline std::unique_ptr<T> MakeUniquePtrHelper (std::false_type, Args&&... args)
		{
			return std::make_unique<T> (std::forward<Args> (args)...);
		}

		template <typename T, typename... Args>
		inline std::unique_ptr<T> MakeUniquePtrHelper (std::true_type, size_t size)
		{
			static_assert(0 == std::extent<T>::value,
				"make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

			return std::make_unique<T> (size);
		}

		template <typename T, typename... Args>
		inline std::unique_ptr<T> MakeUniquePtr (Args&&... args)
		{
			return MakeUniquePtrHelper<T> (std::is_array<T> (), std::forward<Args> (args)...);
		}
	}
}
#endif