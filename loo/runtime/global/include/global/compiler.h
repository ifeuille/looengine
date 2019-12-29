#ifndef LOO_CORE_COMPILER_HPP
#define LOO_CORE_COMPILER_HPP

// Detects supported compilers
#if defined(__clang__)
	// Clang++

#if __cplusplus < 201402L
#error "-std=c++14 must be turned on."
#endif

#define LOO_COMPILER_CLANG
#define LOO_COMPILER_NAME clang

#define CLANG_VERSION KFL_JOIN(__clang_major__, __clang_minor__)

#if __cplusplus > 201402L
#define LOO_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT
#endif

#if defined(__APPLOO__)
#if CLANG_VERSION >= 61
#define LOO_COMPILER_VERSION CLANG_VERSION
#else
#error "Unsupported compiler version. Please install Apple clang++ 6.1 or up."
#endif

#define LOO_CXX17_LIBRARY_SIZE_AND_MORE_SUPPORT
#if CLANG_VERSION >= 90
#define LOO_CXX17_LIBRARY_STRING_VIEW_SUPPORT
#endif

#define LOO_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#define LOO_SYMBOL_IMPORT
#elif defined(__ANDROID__)
#if CLANG_VERSION >= 50
#define LOO_COMPILER_VERSION CLANG_VERSION
#else
#error "Unsupported compiler version. Please install clang++ 5.0 (NDK 16) or up."
#endif

#define LOO_CXX17_LIBRARY_ANY_SUPPORT
#define LOO_CXX17_LIBRARY_OPTIONAL_SUPPORT
#define LOO_CXX17_LIBRARY_SIZE_AND_MORE_SUPPORT
#define LOO_CXX17_LIBRARY_STRING_VIEW_SUPPORT

#define LOO_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#define LOO_SYMBOL_IMPORT
#elif defined(__c2__)
#if CLANG_VERSION >= 36
#define LOO_COMPILER_VERSION CLANG_VERSION
#else
#error "Unsupported compiler version. Please install clang++ 3.6 or up."
#endif

#define LOO_COMPILER_CLANGC2

#define LOO_CXX17_LIBRARY_SIZE_AND_MORE_SUPPORT
#define LOO_TS_LIBRARY_FILESYSTEM_SUPPORT

#define LOO_SYMBOL_EXPORT __declspec(dllexport)
#define LOO_SYMBOL_IMPORT __declspec(dllimport)

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#ifndef _SCL_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_DEPRECATE
#endif
#else
#error "Clang++ on an unknown platform. Only Apple+, Android, and Windows are supported."
#endif

#define LOO_ATTRIBUTE_NORETURN __attribute__((noreturn))
#define LOO_BUILTIN_UNREACHABLE __builtin_unreachable()
#elif defined(__GNUC__)
// GNU C++

#define LOO_COMPILER_GCC

#include <bits/c++config.h>
#ifdef _GLIBCXX_USE_FLOAT128
#undef _GLIBCXX_USE_FLOAT128
#endif
#ifdef _GLIBCXX_USE_INT128
#undef _GLIBCXX_USE_INT128
#endif

#define GCC_VERSION KFL_JOIN(__GNUC__, __GNUC_MINOR__)

#if GCC_VERSION >= 71
#define LOO_COMPILER_VERSION GCC_VERSION
#else
#error "Unsupported compiler version. Please install g++ 7.1 or up."
#endif

#if __cplusplus < 201703L
#error "-std=c++1z must be turned on."
#endif
#if !defined(_GLIBCXX_HAS_GTHREADS)
#error "_GLIBCXX_HAS_GTHREADS must be turned on."
#endif

#define LOO_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT
#define LOO_CXX17_LIBRARY_ANY_SUPPORT
#define LOO_CXX17_LIBRARY_OPTIONAL_SUPPORT
#define LOO_CXX17_LIBRARY_SIZE_AND_MORE_SUPPORT
#define LOO_CXX17_LIBRARY_STRING_VIEW_SUPPORT
#define LOO_TS_LIBRARY_FILESYSTEM_SUPPORT

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define LOO_SYMBOL_EXPORT __attribute__((__dllexport__))
#define LOO_SYMBOL_IMPORT __attribute__((__dllimport__))
#else
#define LOO_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#define LOO_SYMBOL_IMPORT
#endif

#define LOO_ATTRIBUTE_NORETURN __attribute__((noreturn))
#define LOO_BUILTIN_UNREACHABLE __builtin_unreachable()


// Function type macros.
#define LOO_VARARGS															/* Functions with variable arguments */
#define LOO_CDECL															/* Standard C function */
#define LOO_STDCALL															/* Standard calling convention */
#if LOO_DEBUG
#define LOO_FORCEINLINE inline 											/* Don't force code to be inline, or you'll run into -Wignored-attributes */
#else
#define LOO_FORCEINLINE inline __attribute__ ((always_inline))			/* Force code to be inline */
#endif 
#define LOO_FORCENOINLINE __attribute__((noinline))							/* Force code to NOT be inline */
#define LOO_FUNCTION_CHECK_RETURN_END __attribute__ ((warn_unused_result))	/* Wrap a function signature in this to warn that callers should not ignore the return value. */
#define LOO_FUNCTION_NO_RETURN_END __attribute__ ((noreturn))				/* Wrap a function signature in this to indicate that the function never returns. */

#ifndef DISABLOO_DEPRECATION
#pragma clang diagnostic warning "-Wdeprecated-declarations"

	/**
	* Macro for marking up deprecated code, functions and types.
	*
	* Features that are marked as deprecated are scheduled to be removed from the code base
	* in a future release. If you are using a deprecated feature in your code, you should
	* replace it before upgrading to the next release. See the Upgrade Notes in the release
	* notes for the release in which the feature was marked deprecated.
	*
	* Sample usage (note the slightly different syntax for classes and structures):
	*
	*		DEPRECATED(4.xx, "Message")
	*		void Function();
	*
	*		struct DEPRECATED(4.xx, "Message") MODULOO_API MyStruct
	*		{
	*			// StructImplementation
	*		};
	*		class DEPRECATED(4.xx, "Message") MODULOO_API MyClass
	*		{
	*			// ClassImplementation
	*		};
	*
	* @param VERSION The release number in which the feature was marked deprecated.
	* @param MESSAGE A message containing upgrade notes.
	*/
#define LOO_DEPRECATED(VERSION, MESSAGE) __attribute__((deprecated(MESSAGE " Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.")))

#define LOO_PRAGMA_DISABLOO_DEPRECATION_WARNINGS \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")

#define LOO_PRAGMA_ENABLOO_DEPRECATION_WARNINGS \
		_Pragma("clang diagnostic pop")
#endif // DISABLOO_DEPRECATION

#define UNLIKELY(x)			__builtin_expect(!!(x), 0)

#elif defined(_MSC_VER)
#define LOO_COMPILER_MSVC
#define LOO_COMPILER_NAME vc

#define LOO_HAS_DECLSPEC
#define LOO_SYMBOL_EXPORT __declspec(dllexport)
#define LOO_SYMBOL_IMPORT __declspec(dllimport)

#if _MSC_VER >= 1910
#define LOO_COMPILER_VERSION 141
#elif _MSC_VER >1900
#define LOO_COMPILER_VERSION 140
#else
#error "Unsupported compiler version. Please install vc14 or up."
#endif


#pragma warning(disable: 4251) // STL classes are not dllexport.
#pragma warning(disable: 4819) // Allow non-ANSI characters.
#pragma warning(disable: 4201) // ÄäÃûunion

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#ifndef _SCL_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_DEPRECATE
#endif

#define LOO_ATTRIBUTE_NORETURN __declspec(noreturn)
#define LOO_BUILTIN_UNREACHABLE __assume(false)

// Function type macros.
#define LOO_VARARGS     __cdecl											/* Functions with variable arguments */
#define LOO_CDECL	    __cdecl											/* Standard C function */
#define LOO_STDCALL		__stdcall										/* Standard calling convention */
#define LOO_FORCEINLINE __forceinline									/* Force code to be inline */
#define LOO_FORCENOINLINE __declspec(noinline)							/* Force code to NOT be inline */
#define LOO_FUNCTION_NO_RETURN_START __declspec(noreturn)				/* Indicate that the function never returns. */
#define LOO_FUNCTION_NON_NULL_RETURN_START _Ret_notnull_				/* Indicate that the function never returns nullptr. */

// Hints compiler that expression is true; generally restricted to comparisons against constants
//#if !defined(__clang__) || defined(_MSC_VER)	// Clang only supports __assume when using -fms-extensions
//#define LOO_ASSUME(expr) __assume(expr)
//#endif

#ifndef DISABLOO_DEPRECATION
#if !defined(__clang__)
#define LOO_DEPRECATED(VERSION, MESSAGE) __declspec(deprecated(MESSAGE " Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile."))

#define LOO_PRAGMA_DISABLOO_DEPRECATION_WARNINGS \
			__pragma (warning(push)) \
			__pragma (warning(disable:4995)) \
			__pragma (warning(disable:4996))

#define LOO_PRAGMA_ENABLOO_DEPRECATION_WARNINGS \
			__pragma (warning(pop))
#endif
#endif // DISABLOO_DEPRECATION

#define UNLIKELY(x)			(x)

#else
#error "Unknown compiler. Please install vc, g++, or clang."
#endif

//#ifdef LOO_CORE_SOURCE		// Build dll
//#define LOO_CORE_API LOO_SYMBOL_EXPORT
//#else							
// Use dll
//#define LOO_CORE_API LOO_SYMBOL_IMPORT
//#endif

enum { INDEX_NONE = -1 };
enum { UNICODE_BOM = 0xfeff };

enum EForceInit
{
	ForceInit,
	ForceInitToZero
};
enum ENoInit { NoInit };


#ifndef VARARGS
#define VARARGS									/* Functions with variable arguments */
#endif

// If we don't have a platform-specific define for the TEXT macro, define it now.
#if !defined(TEXT) && !LOO_BUILD_DOCS
#define LOO_TEXT_PASTE(x) L ## x
#define LOO_TEXT(x) TEXT_PASTE(x)
#endif

// Branch prediction hints
#if !defined (__c2__) && defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define LOO_LIKELY(x) __builtin_expect(x, 1)
#define LOO_UNLIKELY(x) __builtin_expect(x, 0)
#endif
#else
#define LOO_LIKELY(x) x
#define LOO_UNLIKELY(x) x
#endif
#if defined(_MSC_VER) && (_MSC_VER <= 1800)
# define LOO_CONSTEXPR
#else
# define LOO_CONSTEXPR constexpr
#endif
#define LOO_CONSTEXPR_OR_CONST constexpr

#define LOO_ASSERT(x,msg) assert(x&&msg);



#endif 
//LOO_COMPILER_HPP