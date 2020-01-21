

#ifndef UTILS_CALLSTACK_H_
#define UTILS_CALLSTACK_H_

#include <stddef.h>
#include <stdint.h>
#include <typeinfo>

#include "global/utils/cstring.h"
#include "global/utils/log.h"

namespace utils {

/**
 * CallStack captures the current's thread call stack.
 */
class CallStack {
public:
    /**
     * Creates an empty call stack
     * @see CallStack::capture()
     */
    CallStack() = default;
    CallStack(const CallStack&) = default;
    ~CallStack() = default;

    /**
     * A convenience method to create and capture the stack trace in one go.
     * @param ignore number frames to ignore at the top of the stack.
     * @return A CallStack object
     */
    static CallStack unwind(size_t ignore = 0) noexcept;

    /**
     * Capture the current thread's stack and replaces the existing one if any.
     * @param ignore number frames to ignore at the top of the stack.
     */
    void update(size_t ignore = 0) noexcept;

    /**
     * Get the number of stack frames this object has recorded.
     * @return How many stack frames are accessible through operator[]
     */
    size_t getFrameCount() const noexcept;

    /**
     * Return the program-counter of each stack frame captured
     * @param index of the frame between 0 and getFramceCount()-1
     * @return the program-counter of the stack-frame recorded at index \p index
     * @throw std::out_of_range if the index is out of range
     */
    intptr_t operator [](size_t index) const;

   /** Demangles a C++ type name */
    static utils::CString demangleTypeName(const char* mangled);

    template <typename T>
    static utils::CString typeName() {
#if UTILS_HAS_RTTI
        return demangleTypeName(typeid(T).name());
#else
        return CString("<no-rtti>");
#endif
    }

    /**
     * Outputs a CallStack into a stream.
     * This will print, when possible, the demangled names of functions corresponding to the
     * program-counter recorded.
     */
    friend utils::io::ostream& operator <<(utils::io::ostream& stream, const CallStack& callstack);

    bool operator <(const CallStack& rhs) const;

    inline bool operator >(const CallStack& rhs) const {
        return rhs < *this;
    }

    inline bool operator !=(const CallStack& rhs) const {
        return *this < rhs || rhs < *this;
    }

    inline bool operator >=(const CallStack& rhs) const {
        return !operator <(rhs);
    }

    inline bool operator <=(const CallStack& rhs) const {
        return !operator >(rhs);
    }

    inline bool operator ==(const CallStack& rhs) const {
        return !operator !=(rhs);
    }

private:
    void update_gcc(size_t ignore) noexcept;

    static constexpr size_t NUM_FRAMES = 20;

    struct StackFrameInfo {
        intptr_t pc;
    };

    size_t m_frame_count = 0;
    StackFrameInfo m_stack[NUM_FRAMES];
};

} // namespace utils

#endif // UTILS_CALLSTACK_H_
