//#include "Resource/Core.ResIdentifier.h"
#include "global/global.h"
#ifdef LOO_PLATFORM_WINDOWS
#include <windows.h>
#ifdef LOO_PLATFORM_WINDOWS_STORE
//#include "global/thread.h"
#endif
#else
#include <cerrno>
#include <cstdlib>
#include <cwchar>
#include <clocale>
#endif
#include "global/thread.h"
#include <vector>
#include <algorithm>
#include <assert.h>
#include <clocale>
#include "global/utlis.h"

namespace loo
{
	namespace global
	{
		// 把一个wstring转化为string
	/////////////////////////////////////////////////////////////////////////////////
		std::string& Convert (std::string& dest, nonstd::wstring_view src)
		{
#if defined LOO_PLATFORM_WINDOWS
			int const mbs_len = WideCharToMultiByte (CP_ACP, 0, src.data (), static_cast<int>(src.size ()), nullptr, 0, nullptr, nullptr);
			std::vector<char> tmp (mbs_len + 1);
			WideCharToMultiByte (CP_ACP, 0, src.data (), static_cast<int>(src.size ()), &tmp[0], mbs_len, nullptr, nullptr);
#elif defined LOO_PLATFORM_ANDROID
			// Hack for wcstombs
			std::vector<char> tmp;
			for (auto ch : src)
			{
				if (ch < 0x80)
				{
					tmp.push_back (static_cast<char>(ch));
				}
				else
				{
					tmp.push_back (static_cast<char>((ch >> 0) & 0xFF));
					tmp.push_back (static_cast<char>((ch >> 8) & 0xFF));
				}
			}
			tmp.push_back ('\0');
#else
			std::setlocale (LC_CTYPE, "");

			size_t const mbs_len = wcstombs (nullptr, src.data (), src.size ());
			std::vector<char> tmp (mbs_len + 1);
			wcstombs (&tmp[0], src.data (), tmp.size ());
#endif

			dest.assign (tmp.begin (), tmp.end () - 1);

			return dest;
		}

		// 把一个string转化为string
		/////////////////////////////////////////////////////////////////////////////////
		std::string& Convert (std::string& dest, nonstd::string_view src)
		{
			dest = std::string (src);

			return dest;
		}

		// 把一个string转化为wstring
		/////////////////////////////////////////////////////////////////////////////////
		std::wstring& Convert (std::wstring& dest, nonstd::string_view src)
		{
#if defined LOO_PLATFORM_WINDOWS
			int const wcs_len = MultiByteToWideChar (CP_ACP, 0, src.data (), static_cast<int>(src.size ()), nullptr, 0);
			std::vector<wchar_t> tmp (wcs_len + 1);
			MultiByteToWideChar (CP_ACP, 0, src.data (), static_cast<int>(src.size ()), &tmp[0], wcs_len);
#elif defined LOO_PLATFORM_ANDROID
			// Hack for mbstowcs
			std::vector<wchar_t> tmp;
			for (auto iter = src.begin (); iter != src.end (); ++iter)
			{
				unsigned char ch = *iter;
				wchar_t wch = ch;
				if (ch >= 0x80)
				{
					++iter;
					if (iter != src.end ())
					{
						wch |= (*iter) << 8;
					}
				}
				tmp.push_back (wch);
			}
			tmp.push_back (L'\0');
#else
			std::setlocale (LC_CTYPE, "");

			size_t const wcs_len = mbstowcs (nullptr, src.data (), src.size ());
			std::vector<wchar_t> tmp (wcs_len + 1);
			mbstowcs (&tmp[0], src.data (), src.size ());
#endif

			dest.assign (tmp.begin (), tmp.end () - 1);

			return dest;
		}

		// 把一个wstring转化为wstring
		/////////////////////////////////////////////////////////////////////////////////
		std::wstring& Convert (std::wstring& dest, nonstd::wstring_view src)
		{
			dest = std::wstring (src);

			return dest;
		}

		// 暂停几毫秒
		/////////////////////////////////////////////////////////////////////////////////
		void Sleep (uint32_t ms)
		{
#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			::Sleep (ms);
#else
			std::this_thread::sleep_for (std::chrono::milliseconds (ms));
#endif
		}

		// Endian的切换
		/////////////////////////////////////////////////////////////////////////////////


		// 获取上一个错误代码
		/////////////////////////////////////////////////////////////////////////////////
		uint32_t LastError ()
		{
#ifdef LOO_PLATFORM_WINDOWS
			return ::GetLastError ();
#else
			return errno;
#endif
		}

	/*	std::string ReadShortString (ResIdentifierPtr const & res)
		{
			uint8_t len;
			res->read (&len, sizeof (len));

			std::string tmp;
			if (len > 0)
			{
				tmp.resize (len);
				res->read (&tmp[0], len * sizeof (tmp[0]));
			}

			return tmp;
		}*/

		void WriteShortString (std::ostream& os, nonstd::string_view str)
		{
			uint8_t len = static_cast<uint8_t>(std::min (str.size (), static_cast<size_t>(255)));
			os.write (reinterpret_cast<char*>(&len), sizeof (len));

			if (len > 0)
			{
				os.write (str.data (), len * sizeof (str[0]));
			}
		}

		template <>
		inline void EndianSwitch<2> (void* p) noexcept
		{
			uint8_t* bytes = static_cast<uint8_t*>(p);
			std::swap (bytes[0], bytes[1]);
		}

		template <>
		void EndianSwitch<4> (void* p) noexcept
		{
			uint8_t* bytes = static_cast<uint8_t*>(p);
			std::swap (bytes[0], bytes[3]);
			std::swap (bytes[1], bytes[2]);
		}

		template <>
		void EndianSwitch<8> (void* p) noexcept
		{
			uint8_t* bytes = static_cast<uint8_t*>(p);
			std::swap (bytes[0], bytes[7]);
			std::swap (bytes[1], bytes[6]);
			std::swap (bytes[2], bytes[5]);
			std::swap (bytes[3], bytes[4]);
		}
	}
}
