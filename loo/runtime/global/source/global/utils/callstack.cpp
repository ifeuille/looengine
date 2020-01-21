
#include "global/utils/callstack.h"
#include "global/utils/log.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <memory>

 // FIXME: Some platforms do not have execinfo.h (but have unwind.h)
#if !defined(LOO_PLATFORM_ANDROID) && !defined(WIN32) && !defined(__EMSCRIPTEN__)
#include <execinfo.h>
#define HAS_EXECINFO 1
#else
#define HAS_EXECINFO 0
#endif

#if !defined(NDEBUG) && !defined(WIN32)
#include <cxxabi.h>
#endif

#include <string.h>

#ifdef __EXCEPTIONS
#include <stdexcept>
#endif

namespace utils {

	struct FreeDeleter {
		void operator()(const void* pv) const { free (const_cast<void*>(pv)); }
	};

	// ------------------------------------------------------------------------------------------------

	CallStack CallStack::unwind (size_t ignore) noexcept {
		CallStack stack;
		stack.update (ignore);
		return stack;
	}

	// ------------------------------------------------------------------------------------------------

	intptr_t CallStack::operator[](size_t index) const {
		if (index >= m_frame_count) {
#ifdef __EXCEPTIONS
			throw std::out_of_range ("out-of-range access in CallStack::operator[]");
#endif
			std::abort ();
		}
		return m_stack[index].pc;
	}

	size_t CallStack::getFrameCount () const noexcept {
		return m_frame_count;
	}

	void CallStack::update (size_t ignore) noexcept {
		update_gcc (ignore);
	}

	void CallStack::update_gcc (size_t ignore) noexcept {
		// reset the object
		ssize_t size = 0;

		void* array[NUM_FRAMES];
#if HAS_EXECINFO
		size = ::backtrace (array, NUM_FRAMES);
		size -= ignore;
#endif
		for (ssize_t i = 0; i < size; i++) {
			m_stack[i].pc = intptr_t (array[ignore + i]);
		}
		size--; // the last one seems to always be 0x0

		// update how many frames we have
		m_frame_count = size_t (std::max (ssize_t (0), size));
	}

	bool CallStack::operator<(const CallStack& rhs) const {
		if (m_frame_count != rhs.m_frame_count) {
			return m_frame_count < rhs.m_frame_count;
		}
		return memcmp (m_stack, rhs.m_stack, m_frame_count * sizeof (StackFrameInfo)) < 0;
	}

	// ------------------------------------------------------------------------------------------------

	utils::CString CallStack::demangleTypeName (const char* mangled) {
#if !defined(NDEBUG) && !defined(WIN32)
		size_t len;
		int status;
		std::unique_ptr<char, FreeDeleter> demangled (abi::__cxa_demangle (mangled, nullptr, &len, &status));
		if (!status && demangled) {
			// success
			return CString (demangled.get ());
		}
		// failed to demangle string or parsing error:  return input
#endif
		return CString (mangled);
	}

	// ------------------------------------------------------------------------------------------------

	io::ostream& operator<<(io::ostream& stream, const CallStack& callstack) {
		LOO_UNUSED (callstack);
#if HAS_EXECINFO
		size_t size = callstack.getFrameCount ();
		for (size_t i = 0; i < size; i++) {
			intptr_t pc = callstack[i];
			std::unique_ptr<char*, FreeDeleter> symbols (::backtrace_symbols ((void* const*)&pc, 1));
			char const* const symbol = symbols.get ()[0];
			stream << "#" << i << " " << symbol;
			if (i < size - 1) {
				stream << io::endl;
			}
		}
#endif
		return stream;
	}

} // namespace utils
