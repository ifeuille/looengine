/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "global/utils/log.h"
#include <string>


#ifdef LOO_PLATFORM_ANDROID
#   include <android/log.h>
#   ifndef UTILS_LOG_TAG
#       define UTILS_LOG_TAG "looengine"
#   endif
#endif

#if (!UTILS_TINY_IO)
#   include <iostream>
#endif

namespace utils {

#if (UTILS_TINY_IO)
	namespace io {

		thread_local ostream::Buffer ostream::mData;
		//UTILS_DEFINE_TLS(ostream::Buffer) ostream::mData;

		
		void ostream::Buffer::advance (std::int64_t n) noexcept {
			if (n > 0) {
				size_t written = n < (std::int64_t)size ? size_t (n) : size;
				curr += written;
				size -= written;
			}
		}

		
		void ostream::Buffer::reset () noexcept {
			curr = mStorage;
			size = sizeof (mStorage);
		}


		const char* ostream::getFormat (ostream::type t) const noexcept {
			switch (t) {
			case type::SHORT:       return mShowHex ? "0x%hx" : "%hd";
			case type::USHORT:      return mShowHex ? "0x%hx" : "%hu";
			case type::INT:         return mShowHex ? "0x%x" : "%d";
			case type::UINT:        return mShowHex ? "0x%x" : "%u";
			case type::LONG:        return mShowHex ? "0x%lx" : "%ld";
			case type::ULONG:       return mShowHex ? "0x%lx" : "%lu";
			case type::LONG_LONG:   return mShowHex ? "0x%llx" : "%lld";
			case type::ULONG_LONG:  return mShowHex ? "0x%llx" : "%llu";
			case type::DOUBLE:      return "%f";
			case type::LONG_DOUBLE: return "%Lf";
			}
			return "%d";
		}

		ostream& ostream::operator<<(short value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::SHORT), value));
			return *this;
		}

		ostream& ostream::operator<<(unsigned short value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::USHORT), value));
			return *this;
		}

		ostream& ostream::operator<<(int value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::INT), value));
			return *this;
		}

		ostream& ostream::operator<<(unsigned int value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::UINT), value));
			return *this;
		}

		ostream& ostream::operator<<(long value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::LONG), value));
			return *this;
		}

		ostream& ostream::operator<<(unsigned long value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::ULONG), value));
			return *this;
		}

		ostream& ostream::operator<<(long long value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::LONG_LONG), value));
			return *this;
		}

		ostream& ostream::operator<<(unsigned long long value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::ULONG_LONG), value));
			return *this;
		}

		ostream& ostream::operator<<(float value) noexcept {
			return operator<<((double)value);
		}

		ostream& ostream::operator<<(double value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::DOUBLE), value));
			return *this;
		}

		ostream& ostream::operator<<(long double value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, getFormat (type::LONG_DOUBLE), value));
			return *this;
		}

		ostream& ostream::operator<<(bool value) noexcept {
			return operator<<((int)value);
		}

		ostream& ostream::operator<<(const char* string) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, "%s", string));
			return *this;
		}

		ostream& ostream::operator<<(const void* value) noexcept {
			Buffer& buf = getBuffer ();
			buf.advance (snprintf (buf.curr, buf.size, "%p", value));
			return *this;
		}

		ostream& ostream::flush () noexcept {
			Buffer& buf = getBuffer ();
#ifdef LOO_PLATFORM_ANDROID
			switch (mPriority) {
			case EDEBUG:
				__android_log_write (ANDROID_LOG_DEBUG, UTILS_LOG_TAG, buf.get ());
				break;
			case EERROR:
				__android_log_write (ANDROID_LOG_ERROR, UTILS_LOG_TAG, buf.get ());
				break;
			case EWARNING:
				__android_log_write (ANDROID_LOG_WARN, UTILS_LOG_TAG, buf.get ());
				break;
			case EINFO:
				__android_log_write (ANDROID_LOG_INFO, UTILS_LOG_TAG, buf.get ());
				break;
			}
#else
			switch (mPriority) {
			case EDEBUG:
			case EWARNING:
			case EINFO:
				fprintf (stdout, "%s", buf.get ());
				break;
			case EERROR:
				fprintf (stderr, "%s", buf.get ());
				break;
			}
#endif
			buf.reset ();
			return *this;
		}

		ostream& ostream::hex () noexcept {
			mShowHex = true;
			return *this;
		}

		ostream& ostream::dec () noexcept {
			mShowHex = false;
			return *this;
		}

		static ostream cout (ostream::Priority::EDEBUG);
		static ostream cerr (ostream::Priority::EERROR);
		static ostream cwarn (ostream::Priority::EWARNING);
		static ostream cinfo (ostream::Priority::EINFO);

	} // namespace io


	Loggers slog = {
			io::cout,   // debug
			io::cerr,   // error
			io::cwarn,  // warning
			io::cinfo   // info
	};

#else // UTILS_TINY_IO

#ifdef LOO_PLATFORM_ANDROID
	static constexpr const size_t LOG_BUFFER_SIZE = 1024;

	class AndroidStreamBuffer : public std::streambuf {
	public:
		explicit AndroidStreamBuffer (android_LogPriority priority) {
			mPriority = priority;
			setp (mBuffer, mBuffer + LOG_BUFFER_SIZE - 1);
		}

	private:
		int overflow (int c) {
			if (c != traits_type::eof ()) {
				*pptr () = traits_type::to_char_type (c);
				pbump (1);
				if (sync () >= 0) {
					return c;
				}
			}

			return traits_type::eof ();
		}

		int sync () {
			if (pbase () != pptr ()) {
				char buffer[LOG_BUFFER_SIZE + 1];
				std::ptrdiff_t length = pptr () - pbase ();
				memcpy (buffer, pbase (), length);
				buffer[length] = '\0';
				pbump (-length);

				__android_log_write (mPriority, UTILS_LOG_TAG, buffer);
			}
			return 0;
		}

		android_LogPriority mPriority;
		char mBuffer[LOG_BUFFER_SIZE];
	};

	static std::ostream android_cout (new AndroidStreamBuffer (ANDROID_LOG_DEBUG));
	static std::ostream android_cerr (new AndroidStreamBuffer (ANDROID_LOG_ERROR));
	static std::ostream android_cwarn (new AndroidStreamBuffer (ANDROID_LOG_WARN));
	static std::ostream android_cinfo (new AndroidStreamBuffer (ANDROID_LOG_INFO));

	Loggers slog = {
		android_cout,   // debug
		android_cerr,   // error
		android_cwarn,  // warning
		android_cinfo   // info
	};

#else // ANDROID

	Loggers slog = {
		std::cout,  // debug
		std::cerr,  // error
		std::cout,  // warning
		std::cout   // info
	};

#endif

#endif // UTILS_TINY_IO

} // namespace utils
