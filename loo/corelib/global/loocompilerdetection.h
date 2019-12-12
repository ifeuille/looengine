#ifndef LOO_CORELIB_GLOBAL_GLOBAL_H
#include <LooCore/looglobal.h>
#endif

#ifndef LOO_CORELIB_LOOCOMPILER_H
#define LOO_CORELIB_LOOCOMPILER_H

//llvm/clang only


#ifdef __clang__
	#define LOO_CC_CLANG ((__clang_major__ * 100) + __clang_minor__)
#endif

#define LOO_FUNC_INFO __FUNCSIG__
#define LOO_ALIGNOF(type) __alignof(type)
#define LOO_DECL_ALIGN(n) __declspec(align(n))
#define LOO_ASSUME_IMPL(expr) __assume(expr)
#define LOO_UNREACHABLE_IMPL() __assume(0)
#define LOO_NORETURN __declspec(noreturn)
#define LOO_DECL_DEPRECATED __declspec(deprecated)
#ifndef LOO_CC_CLANG
	#define LOO_DECL_DEPRECATED_X(text) __declspec(deprecated(text))
#endif
#define LOO_DECL_EXPORT __declspec(dllexport)
#define LOO_DECL_IMPORT __declspec(dllimport)
#define LOO_MAKE_UNCHECKED_ARRAY_ITERATOR(x) stdext::make_unchecked_array_iterator(x) // Since _MSC_VER >= 1800
#define LOO_MAKE_CHECKED_ARRAY_ITERATOR(x, N) stdext::make_checked_array_iterator(x, size_t(N)) // Since _MSC_VER >= 1500

#    if defined(__apple_build_version__)
#      /* http://en.wikipedia.org/wiki/Xcode#Toolchain_Versions */
#      if __apple_build_version__ >= 8020041
#        define LOO_CC_CLANG 309
#      elif __apple_build_version__ >= 8000038
#        define LOO_CC_CLANG 308
#      elif __apple_build_version__ >= 7000053
#        define LOO_CC_CLANG 306
#      elif __apple_build_version__ >= 6000051
#        define LOO_CC_CLANG 305
#      elif __apple_build_version__ >= 5030038
#        define LOO_CC_CLANG 304
#      elif __apple_build_version__ >= 5000275
#        define LOO_CC_CLANG 303
#      elif __apple_build_version__ >= 4250024
#        define LOO_CC_CLANG 302
#      elif __apple_build_version__ >= 3180045
#        define LOO_CC_CLANG 301
#      elif __apple_build_version__ >= 2111001
#        define LOO_CC_CLANG 300
#      else
#        error "Unknown Apple Clang version"
#      endif
#    else
#      define LOO_CC_CLANG ((__clang_major__ * 100) + __clang_minor__)
#    endif

#    if __has_builtin(__builtin_assume)
#      define LOO_ASSUME_IMPL(expr)   __builtin_assume(expr)
#    else
#      define LOO_ASSUME_IMPL(expr)  if (expr){} else __builtin_unreachable()
#    endif
#    define LOO_UNREACHABLE_IMPL() __builtin_unreachable()
#    if !defined(__has_extension)
#      /* Compatibility with older Clang versions */
#      define __has_extension __has_feature
#    endif
#    if defined(__APPLE__)
     /* Apple/clang specific features */
#      define LOO_DECL_CF_RETURNS_RETAINED __attribute__((cf_returns_retained))
#      ifdef __OBJC__
#        define LOO_DECL_NS_RETURNS_AUTORELEASED __attribute__((ns_returns_autoreleased))
#      endif
#    endif
#    ifdef __EMSCRIPTEN__
#      define LOO_CC_EMSCRIPTEN
#    endif



#  define LOO_FUNC_INFO       __PRETTY_FUNCTION__
#  define LOO_ALIGNOF(type)   __alignof__(type)
#  define LOO_TYPEOF(expr)    __typeof__(expr)
#  define LOO_DECL_DEPRECATED __attribute__ ((__deprecated__))
#  define LOO_DECL_ALIGN(n)   __attribute__((__aligned__(n)))
#  define LOO_DECL_UNUSED     __attribute__((__unused__))
#  define LOO_LIKELY(expr)    __builtin_expect(!!(expr), true)
#  define LOO_UNLIKELY(expr)  __builtin_expect(!!(expr), false)
#  define LOO_NORETURN        __attribute__((__noreturn__))
#  define LOO_REQUIRED_RESULT __attribute__ ((__warn_unused_result__))
#  define LOO_DECL_PURE_FUNCTION __attribute__((pure))
#  define LOO_DECL_CONST_FUNCTION __attribute__((const))
#  define LOO_DECL_COLD_FUNCTION __attribute__((cold))


#  if __has_feature(attribute_deprecated_with_message)
#    define LOO_DECL_DEPRECATED_X(text) __attribute__ ((__deprecated__(text)))
#  endif

#  if defined(__has_warning)
#    if __has_warning("-Wunused-private-field")
#      define LOO_DECL_UNUSED_MEMBER LOO_DECL_UNUSED
#    endif
#  endif







#endif