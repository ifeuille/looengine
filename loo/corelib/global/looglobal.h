
#ifndef LOO_CORELIB_GLOBAL_GLOBAL_H
#define LOO_CORELIB_GLOBAL_GLOBAL_H
#include <type_traits>
#include <string>
#include <cstddef>
#include <utility>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#ifndef __ASSEMBLER__
#include <assert.h>
#include <stddef.h>
#endif

/*
   LOO_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define LOO_MAKE_VERSION(major, minor, patch) \
    (((major) << 16) | ((minor) << 8) | (patch))
#define LOO_VERSION_MAJOR(version) ((std::uint32_t)(version) >> 22)
#define LOO_VERSION_MINOR(version) (((std::uint32_t)(version) >> 12) & 0x3ff)
#define LOO_VERSION_PATCH(version) ((std::uint32_t)(version) & 0xfff)
// name and version
#define LOO_ENGINE_NAME  "LooEngine"

#define LOO_MAJOR_VERSION 1
#define LOO_MINOR_VERSION 0
#define LOO_PATCH_VERSION 0

//current api version
#define LOO_VERSION LOO_MAKE_VERSION(LOO_MAJOR_VERSION,LOO_MINOR_VERSION,LOO_PATCH_VERSION)
#define LOO_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#define LOO_STRINGIZE(s) LOO_DO_STRINGIZE(s)
#define LOO_DO_STRINGIZE(s) #s

#define LOO_JOIN(X,Y) LOO_DO_JOIN(X,Y)
#define LOO_DO_JOIN(X, Y) LOO_DO_JOIN2(X, Y)
#define LOO_DO_JOIN2(X, Y) X##Y

#define LOO_VERSION_STR "1.0.0"

/* These two macros makes it possible to turn the builtin line expander into a
 * string literal. */
#define LOO_STRINGIFY2(x) #x
#define LOO_STRINGIFY(x) LOO_STRINGIFY2(x)

#ifdef LOO_SHARED
    #ifdef LOO_BUILD_CORELIB
        #define LOO_CORE_EXPORT LOO_DECL_EXPORT
    #else
        #define LOO_CORE_EXPORT LOO_DECL_IMPORT
    #endif
#else
    #define LOO_CORE_EXPORT
#endif

#include "loosystemdetection.h"
#include "looprocessordetection.h"
#include "loocompilerdetection.h"
//#include <LooCore/loosystemdetection.h>
//#include <LooCore/looprocessordetection.h>
//#include <LooCore/loocompilerdetection.h>

#if defined (__ELF__)
#  define LOO__OF_ELF
#endif
#if defined (__MACH__) && defined (__APPLE__)
#  define LOO__OF_MACH_O
#endif


#  define LOO_STATIC_ASSERT(Condition) static_assert(bool(Condition), #Condition)
#  define LOO_STATIC_ASSERT_X(Condition, Message) static_assert(bool(Condition), Message)

#include <algorithm>

#define LOO_NAMESPACE loo
#define LOO_NAMESPACE_BEGIN namespace LOO_NAMESPACE{
#define LOO_NAMESPACE_END }
#define LOO_USE_NAMESPACE using namespace LOO_NAMESPACE;
#define LOO_PREDECLARE_CLASS(name) class LOO_NAMESPACE::name



//LOO_NAMESPACE_BEGIN
namespace loo {
	typedef signed char lint8;         /* 8 bit signed */
	typedef unsigned char luint8;      /* 8 bit unsigned */
	typedef short lint16;              /* 16 bit signed */
	typedef unsigned short luint16;    /* 16 bit unsigned */
	typedef int lint32;                /* 32 bit signed */
	typedef unsigned int luint32;      /* 32 bit unsigned */
	typedef signed long long lint64;
	typedef unsigned long long luint64;
	typedef float lfloat32;
	typedef double lreal;
	typedef long llong;
	typedef char lshort;
	typedef unsigned long lulong;
	typedef unsigned char luchar;
	typedef unsigned short lushort;
#if defined(LOO_OS_WIN) && !defined(LOO_CC_GNU)
#  define LOO_INT64_C(c) c ## i64    /* signed 64 bit constant */
#  define LOO_UINT64_C(c) c ## ui64   /* unsigned 64 bit constant */
#else
#ifdef __cplusplus
#  define LOO_INT64_C(c) static_cast<long long>(c ## LL)     /* signed 64 bit constant */
#  define LOO_UINT64_C(c) static_cast<unsigned long long>(c ## ULL) /* unsigned 64 bit constant */
#else
#  define LOO_INT64_C(c) ((long long)(c ## LL))               /* signed 64 bit constant */
#  define LOO_UINT64_C(c) ((unsigned long long)(c ## ULL))    /* unsigned 64 bit constant */
#endif
#endif

#ifndef LOO_DISABLE_DEPRECATED_BEFORE
#define LOO_DISABLE_DEPRECATED_BEFORE LOO_VERSION_CHECK(5, 0, 0)
#endif

#ifdef LOO_NO_EXCEPTIONS
#  define LOO_TRY if (true)
#  define LOO_CATCH(A) else
#  define LOO_THROW(A) qt_noop()
#  define LOO_RETHROW qt_noop()
#  define LOO_TERMINATE_ON_EXCEPTION(expr) do { expr; } while (false)
#else
#  define LOO_TRY try
#  define LOO_CATCH(A) catch (A)
#  define LOO_THROW(A) throw A
#  define LOO_RETHROW throw
LOO_CORE_EXPORT void lTerminate ()LOO_DECL_NOTHROW;
#  ifdef LOO_COMPILER_NOEXCEPT
#    define LOO_TERMINATE_ON_EXCEPTION(expr) do { expr; } while (false)
#  else
#    define LOO_TERMINATE_ON_EXCEPTION(expr) do { try { expr; } catch (...) { lTerminate(); } } while (false)
#  endif
#endif

	/*
		LOO_DEPRECATED_SINCE(major, minor) evaluates as true if the Qt version is greater than
		the deprecation point specified.

		Use it to specify from which version of Qt a function or class has been deprecated

		Example:
			#if LOO_DEPRECATED_SINCE(5,1)
				LOO_DEPRECATED void deprecatedFunction(); //function deprecated since Qt 5.1
			#endif

	*/
#ifdef LOO_DEPRECATED
#define LOO_DEPRECATED_SINCE(major, minor) (LOO_VERSION_CHECK(major, minor, 0) > LOO_DISABLE_DEPRECATED_BEFORE)
#else
#define LOOLOO_DEPRECATED_SINCE(major, minor) 0
#endif

	/*
	   The Qt modules' export macros.
	   The options are:
		- defined(LOO_STATIC): Qt was built or is being built in static mode
		- defined(LOO_SHARED): Qt was built or is being built in shared/dynamic mode
	   If neither was defined, then LOO_SHARED is implied. If Qt was compiled in static
	   mode, LOO_STATIC is defined in qconfig.h. In shared mode, LOO_STATIC is implied
	   for the bootstrapped tools.
	*/

#if defined(LOO_SHARED) || !defined(LOO_STATIC)
#  ifdef LOO_STATIC
#    error "Both LOO_SHARED and LOO_STATIC defined, please make up your mind"
#  endif
#  ifndef LOO_SHARED
#    define LOO_SHARED
#  endif
#  if defined(LOO_BUILD_CORE_LIB)
#    define LOO_CORE_EXPORT LOO_DECL_EXPORT
#  else
#    define LOO_CORE_EXPORT LOO_DECL_IMPORT
#  endif
#else
#  define LOO_CORE_EXPORT
#endif

#define LOO_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

#define LOO_DISABLE_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

#define LOO_DISABLE_COPY_MOVE(Class) \
    LOO_DISABLE_COPY(Class) \
    LOO_DISABLE_MOVE(Class)

	/*
	   No, this is not an evil backdoor. LOO_BUILD_INTERNAL just exports more symbols
	   for Qt's internal unit tests. If you want slower loading times and more
	   symbols that can vanish from version to version, feel free to define LOO_BUILD_INTERNAL.
	*/
#if defined(LOO_BUILD_INTERNAL) && defined(LOO_BUILDING_QT) && defined(LOO_SHARED)
#    define LOO_AUTOTEST_EXPORT LOO_DECL_EXPORT
#elif defined(LOO_BUILD_INTERNAL) && defined(LOO_SHARED)
#    define LOO_AUTOTEST_EXPORT LOO_DECL_IMPORT
#else
#    define LOO_AUTOTEST_EXPORT
#endif

	LOO_CORE_EXPORT const char *lVersion (void) LOO_DECL_NOTHROW;

#ifndef LOO_CONSTRUCTOR_FUNCTION
# define LOO_CONSTRUCTOR_FUNCTION0(AFUNC) \
    namespace { \
    static const struct AFUNC ## _ctor_class_ { \
        inline AFUNC ## _ctor_class_() { AFUNC(); } \
    } AFUNC ## _ctor_instance_; \
    }

# define LOO_CONSTRUCTOR_FUNCTION(AFUNC) LOO_CONSTRUCTOR_FUNCTION0(AFUNC)
#endif

#ifndef LOO_DESTRUCTOR_FUNCTION
# define LOO_DESTRUCTOR_FUNCTION0(AFUNC) \
    namespace { \
    static const struct AFUNC ## _dtor_class_ { \
        inline AFUNC ## _dtor_class_() { } \
        inline ~ AFUNC ## _dtor_class_() { AFUNC(); } \
    } AFUNC ## _dtor_instance_; \
    }
# define LOO_DESTRUCTOR_FUNCTION(AFUNC) LOO_DESTRUCTOR_FUNCTION0(AFUNC)
#endif

	namespace LooPrivate {
		template <class T>
		struct AlignOfHelper
		{
			char c;
			T type;

			AlignOfHelper ();
			~AlignOfHelper ();
		};

		template <class T>
		struct AlignOf_Default
		{
			enum { Value = sizeof (AlignOfHelper<T>) - sizeof (T) };
		};

		template <class T> struct AlignOf : AlignOf_Default<T> { };
		template <class T> struct AlignOf<T &> : AlignOf<T> {};
		template <size_t N, class T> struct AlignOf<T[N]> : AlignOf<T> {};

#ifdef LOO_COMPILER_RVALUE_REFS
		template <class T> struct AlignOf<T &&> : AlignOf<T> {};
#endif

#if defined(LOO_PROCESSOR_X86_32) && !defined(LOO_OS_WIN)
		template <class T> struct AlignOf_WorkaroundForI386Abi { enum { Value = sizeof (T) }; };

		// x86 ABI weirdness
		// Alignment of naked type is 8, but inside struct has alignment 4.
		template <> struct AlignOf<double> : AlignOf_WorkaroundForI386Abi<double> {};
		template <> struct AlignOf<qint64> : AlignOf_WorkaroundForI386Abi<qint64> {};
		template <> struct AlignOf<quint64> : AlignOf_WorkaroundForI386Abi<quint64> {};
#ifdef LOO_CC_CLANG
		// GCC and Clang seem to disagree wrt to alignment of arrays
		template <size_t N> struct AlignOf<double[N]> : AlignOf_Default<double> {};
		template <size_t N> struct AlignOf<qint64[N]> : AlignOf_Default<qint64> {};
		template <size_t N> struct AlignOf<quint64[N]> : AlignOf_Default<quint64> {};
#endif
#endif
	} // namespace LooPrivate

#define LOO_EMULATED_ALIGNOF(T) \
    (size_t(loo::LooPrivate::AlignOf<T>::Value))

#ifndef LOO_ALIGNOF
#define LOO_ALIGNOF(T) LOO_EMULATED_ALIGNOF(T)
#endif

/*
  quintptr and qptrdiff is guaranteed to be the same size as a pointer, i.e.

	  sizeof(void *) == sizeof(quintptr)
	  && sizeof(void *) == sizeof(qptrdiff)
*/
	template <int> struct QIntegerForSize;
	template <>    struct QIntegerForSize<1> { typedef luint8  Unsigned; typedef lint8  Signed; };
	template <>    struct QIntegerForSize<2> { typedef luint16 Unsigned; typedef lint16 Signed; };
	template <>    struct QIntegerForSize<4> { typedef luint32 Unsigned; typedef lint32 Signed; };
	template <>    struct QIntegerForSize<8> { typedef luint64 Unsigned; typedef lint64 Signed; };
#if defined(LOO_CC_GNU) && defined(__SIZEOF_INT128__)
	template <>    struct QIntegerForSize<16> { __extension__ typedef unsigned __int128 Unsigned; __extension__ typedef __int128 Signed; };
#endif
	template <class T> struct QIntegerForSizeof : QIntegerForSize<sizeof (T)> { };
	typedef QIntegerForSize<LOO_PROCESSOR_WORDSIZE>::Signed looregisterint;
	typedef QIntegerForSize<LOO_PROCESSOR_WORDSIZE>::Unsigned looregisteruint;
	typedef QIntegerForSizeof<void*>::Unsigned quintptr;
	typedef QIntegerForSizeof<void*>::Signed qptrdiff;
	typedef qptrdiff qintptr;

	/* moc compats (signals/slots) */
#ifndef LOO_REFLECT_COMPAT
#  define LOO_REFLECT_COMPAT
#else
#  undef LOO_REFLECT_COMPAT
#  define LOO_REFLECT_COMPAT
#endif

#ifdef LOO_ASCII_CAST_WARNINGS
#  define LOO_ASCII_CAST_WARN LOO_DECL_DEPRECATED_X("Use fromUtf8, QStringLiteral, or QLatin1String")
#else
#  define LOO_ASCII_CAST_WARN
#endif

#if defined(__i386__) || defined(_WIN32)
#  if defined(LOO_CC_GNU)
#    define LOO_FASTCALL __attribute__((regparm(3)))
#  elif defined(LOO_CC_MSVC)
#    define LOO_FASTCALL __fastcall
#  else
#     define LOO_FASTCALL
#  endif
#else
#  define LOO_FASTCALL
#endif



	typedef int LooNoImplicitBoolCast;

	/*
	   Utility macros and inline functions
	*/

	template <typename T>
	LOO_DECL_CONSTEXPR inline T lAbs (const T &t) { return t >= 0 ? t : -t; }

	LOO_DECL_CONSTEXPR inline int lRound (double d)
	{
		return d >= 0.0 ? int (d + 0.5) : int (d - double (int (d - 1)) + 0.5) + int (d - 1);
	}
	LOO_DECL_CONSTEXPR inline int lRound (float d)
	{
		return d >= 0.0f ? int (d + 0.5f) : int (d - float (int (d - 1)) + 0.5f) + int (d - 1);
	}

	LOO_DECL_CONSTEXPR inline lint64 lRound64 (double d)
	{
		return d >= 0.0 ? lint64 (d + 0.5) : lint64 (d - double (lint64 (d - 1)) + 0.5) + lint64 (d - 1);
	}
	LOO_DECL_CONSTEXPR inline lint64 lRound64 (float d)
	{
		return d >= 0.0f ? lint64 (d + 0.5f) : lint64 (d - float (lint64 (d - 1)) + 0.5f) + lint64 (d - 1);
	}

	template <typename T>
	LOO_DECL_CONSTEXPR inline const T &lMin (const T &a, const T &b) { return (a < b) ? a : b; }
	template <typename T>
	LOO_DECL_CONSTEXPR inline const T &lMax (const T &a, const T &b) { return (a < b) ? b : a; }
	template <typename T>
	LOO_DECL_CONSTEXPR inline const T &lBound (const T &min, const T &val, const T &max)
	{
		return lMax (min, lMin (max, val));
	}

#ifndef LOO_FORWARD_DECLARE_OBJC_CLASS
#  ifdef __OBJC__
#    define LOO_FORWARD_DECLARE_OBJC_CLASS(classname) @class classname
#  else
#    define LOO_FORWARD_DECLARE_OBJC_CLASS(classname) typedef struct objc_object classname
#  endif
#endif
#ifndef LOO_FORWARD_DECLARE_CF_TYPE
#  define LOO_FORWARD_DECLARE_CF_TYPE(type) typedef const struct __ ## type * type ## Ref
#endif
#ifndef LOO_FORWARD_DECLARE_MUTABLE_CF_TYPE
#  define LOO_FORWARD_DECLARE_MUTABLE_CF_TYPE(type) typedef struct __ ## type * type ## Ref
#endif
#ifndef LOO_FORWARD_DECLARE_CG_TYPE
#define LOO_FORWARD_DECLARE_CG_TYPE(type) typedef const struct type *type ## Ref;
#endif
#ifndef LOO_FORWARD_DECLARE_MUTABLE_CG_TYPE
#define LOO_FORWARD_DECLARE_MUTABLE_CG_TYPE(type) typedef struct type *type ## Ref;
#endif

#ifdef LOO_OS_DARWIN
#  define LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios, tvos, watchos) \
    ((defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && macos != __MAC_NA && __MAC_OS_X_VERSION_MAX_ALLOWED >= macos) || \
     (defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && ios != __IPHONE_NA && __IPHONE_OS_VERSION_MAX_ALLOWED >= ios) || \
     (defined(__TV_OS_VERSION_MAX_ALLOWED) && tvos != __TVOS_NA && __TV_OS_VERSION_MAX_ALLOWED >= tvos) || \
     (defined(__WATCH_OS_VERSION_MAX_ALLOWED) && watchos != __WATCHOS_NA && __WATCH_OS_VERSION_MAX_ALLOWED >= watchos))

#  define LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, ios, tvos, watchos) \
    ((defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && macos != __MAC_NA && __MAC_OS_X_VERSION_MIN_REQUIRED < macos) || \
     (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && ios != __IPHONE_NA && __IPHONE_OS_VERSION_MIN_REQUIRED < ios) || \
     (defined(__TV_OS_VERSION_MIN_REQUIRED) && tvos != __TVOS_NA && __TV_OS_VERSION_MIN_REQUIRED < tvos) || \
     (defined(__WATCH_OS_VERSION_MIN_REQUIRED) && watchos != __WATCHOS_NA && __WATCH_OS_VERSION_MIN_REQUIRED < watchos))

#  define LOO_MACOS_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios, __TVOS_NA, __WATCHOS_NA)
#  define LOO_MACOS_PLATFORM_SDK_EQUAL_OR_ABOVE(macos) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, __IPHONE_NA, __TVOS_NA, __WATCHOS_NA)
#  define LOO_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(ios) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, ios, __TVOS_NA, __WATCHOS_NA)
#  define LOO_TVOS_PLATFORM_SDK_EQUAL_OR_ABOVE(tvos) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, __IPHONE_NA, tvos, __WATCHOS_NA)
#  define LOO_WATCHOS_PLATFORM_SDK_EQUAL_OR_ABOVE(watchos) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, __IPHONE_NA, __TVOS_NA, watchos)

#  define LOO_MACOS_IOS_DEPLOYMENT_TARGET_BELOW(macos, ios) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, ios, __TVOS_NA, __WATCHOS_NA)
#  define LOO_MACOS_DEPLOYMENT_TARGET_BELOW(macos) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, __IPHONE_NA, __TVOS_NA, __WATCHOS_NA)
#  define LOO_IOS_DEPLOYMENT_TARGET_BELOW(ios) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, ios, __TVOS_NA, __WATCHOS_NA)
#  define LOO_TVOS_DEPLOYMENT_TARGET_BELOW(tvos) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, __IPHONE_NA, tvos, __WATCHOS_NA)
#  define LOO_WATCHOS_DEPLOYMENT_TARGET_BELOW(watchos) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, __IPHONE_NA, __TVOS_NA, watchos)

	// Compatibility synonyms, do not use
#  define LOO_MAC_PLATFORM_SDK_EQUAL_OR_ABOVE(osx, ios) LOO_MACOS_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(osx, ios)
#  define LOO_MAC_DEPLOYMENT_TARGET_BELOW(osx, ios) LOO_MACOS_IOS_DEPLOYMENT_TARGET_BELOW(osx, ios)
#  define LOO_OSX_PLATFORM_SDK_EQUAL_OR_ABOVE(osx) LOO_MACOS_PLATFORM_SDK_EQUAL_OR_ABOVE(osx)
#  define LOO_OSX_DEPLOYMENT_TARGET_BELOW(osx) LOO_MACOS_DEPLOYMENT_TARGET_BELOW(osx)


// Implemented in qcore_mac_objc.mm
	class LOO_CORE_EXPORT LooMacAutoReleasePool
	{
	public:
		LooMacAutoReleasePool ();
		~LooMacAutoReleasePool ();
	private:
		LOO_DISABLE_COPY (LooMacAutoReleasePool)
			void *pool;
	};

#endif // LOO_OS_DARWIN


	/*
	   Data stream functions are provided by many classes (defined in qdatastream.h)
	*/

	class LooDataStream;

	inline void loo_noop (void) {}

/*
	Avoid "unused parameter" warnings
*/
#define LOO_UNUSED(x) (void)x;

LOO_CORE_EXPORT const char* loo_error_string (int errorCode = -1);


LOO_CORE_EXPORT void loo_assert (const char *assertion, const char *file, int line) LOO_DECL_NOTHROW;

#if !defined(LOO_ASSERT)
#  if defined(LOO_NO_DEBUG) && !defined(LOO_FORCE_ASSERTS)
#    define LOO_ASSERT(cond) do { } while ((false) && (cond))
#  else
#    define LOO_ASSERT(cond) ((!(cond)) ? loo_assert(#cond,__FILE__,__LINE__) : loo_noop())
#  endif
#endif


	////////////////////////////////////////////////////

#if defined(LOO_NO_DEBUG) && !defined(LOO_PAINT_DEBUG)
#define LOO_NO_PAINT_DEBUG
#endif


LOO_CORE_EXPORT void loo_assert_x (const char *where, const char *what, const char *file, int line) LOO_DECL_NOTHROW;

#if !defined(LOO_ASSERT_X)
#  if defined(LOO_NO_DEBUG) && !defined(LOO_FORCE_ASSERTS)
#    define LOO_ASSERT_X(cond, where, what) do { } while ((false) && (cond))
#  else
#    define LOO_ASSERT_X(cond, where, what) ((!(cond)) ? loo_assert_x(where, what,__FILE__,__LINE__) : loo_noop())
#  endif
#endif

LOO_CORE_EXPORT void loo_check_pointer (const char *, int) LOO_DECL_NOTHROW;
LOO_CORE_EXPORT void lBadAlloc ();
LOO_CORE_EXPORT bool lSharedBuild () LOO_DECL_NOTHROW;

#ifdef LOO_NO_EXCEPTIONS
#  if defined(LOO_NO_DEBUG) && !defined(LOO_FORCE_ASSERTS)
#    define LOO_CHECK_PTR(p) loo_noop()
#  else
#    define LOO_CHECK_PTR(p) do {if (!(p)) loo_check_pointer(__FILE__,__LINE__);} while (false)
#  endif
#else
#  define LOO_CHECK_PTR(p) do { if (!(p)) lBadAlloc(); } while (false)
#endif

	template <typename T>
	inline T *loo_check_ptr (T *p) { LOO_CHECK_PTR (p); return p; }

	typedef void (*LooFunctionPointer)();

#if !defined(LOO_UNIMPLEMENTED)
#  define LOO_UNIMPLEMENTED() looWarning("Unimplemented code.")
#endif

	 LOO_DECL_CONSTEXPR static inline LOO_DECL_UNUSED bool looFuzzyCompare (double p1, double p2)
	{
		return (lAbs (p1 - p2) * 1000000000000. <= lMin (looAbs (p1), lAbs (p2)));
	}

	 LOO_DECL_CONSTEXPR static inline LOO_DECL_UNUSED bool looFuzzyCompare (float p1, float p2)
	{
		return (lAbs (p1 - p2) * 100000.f <= lMin (lAbs (p1), lAbs (p2)));
	}

	 LOO_DECL_CONSTEXPR static inline LOO_DECL_UNUSED bool looFuzzyIsNull (double d)
	{
		return lAbs (d) <= 0.000000000001;
	}

	 LOO_DECL_CONSTEXPR static inline LOO_DECL_UNUSED  bool lFuzzyIsNull (float f)
	{
		return lAbs (f) <= 0.00001f;
	}

	/*
	   This function tests a double for a null value. It doesn't
	   check whether the actual value is 0 or close to 0, but whether
	   it is binary 0, disregarding sign.
	*/
	static inline LOO_DECL_UNUSED bool lIsNull (double d)
	{
		union U {
			double d;
			luint64 u;
		};
		U val;
		val.d = d;
		return (val.u & LOO_UINT64_C (0x7fffffffffffffff)) == 0;
	}

	/*
	   This function tests a float for a null value. It doesn't
	   check whether the actual value is 0 or close to 0, but whether
	   it is binary 0, disregarding sign.
	*/
	 static inline LOO_DECL_UNUSED bool lIsNull (float f)
	{
		union U {
			float f;
			luint32 u;
		};
		U val;
		val.f = f;
		return (val.u & 0x7fffffff) == 0;
	}

	/*
	   Compilers which follow outdated template instantiation rules
	   require a class to have a comparison operator to exist when
	   a QList of this type is instantiated. It's not actually
	   used in the list, though. Hence the dummy implementation.
	   Just in case other code relies on it we better trigger a warning
	   mandating a real implementation.
	*/

#ifdef LOO_FULL_TEMPLATE_INSTANTIATION
#  define LOO_DUMMY_COMPARISON_OPERATOR(C) \
    bool operator==(const C&) const { \
        looWarning(#C"::operator==(const "#C"&) was called"); \
        return false; \
    }
#else

#  define LOO_DUMMY_COMPARISON_OPERATOR(C)
#endif

	LOO_CORE_EXPORT void *lMallocAligned (size_t size, size_t alignment);// LOO_ALLOC_SIZE (1);
	LOO_CORE_EXPORT void *lReallocAligned (void *ptr, size_t size, size_t oldsize, size_t alignment); /*LOO_ALLOC_SIZE (2)*/;
	LOO_CORE_EXPORT void lFreeAligned (void *ptr);


	/*
	   Avoid some particularly useless warnings from some stupid compilers.
	   To get ALL C++ compiler warnings, define LOO_CC_WARNINGS or comment out
	   the line "#define LOO_NO_WARNINGS".
	*/
#if !defined(LOO_CC_WARNINGS)
#  define LOO_NO_WARNINGS
#endif
#if defined(LOO_NO_WARNINGS)
#  if defined(LOO_CC_MSVC)
	LOO_WARNING_DISABLE_MSVC (4251) /* class 'type' needs to have dll-interface to be used by clients of class 'type2' */
		LOO_WARNING_DISABLE_MSVC (4244) /* conversion from 'type1' to 'type2', possible loss of data */
		LOO_WARNING_DISABLE_MSVC (4275) /* non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier' */
		LOO_WARNING_DISABLE_MSVC (4514) /* unreferenced inline function has been removed */
		LOO_WARNING_DISABLE_MSVC (4800) /* 'type' : forcing value to bool 'true' or 'false' (performance warning) */
		LOO_WARNING_DISABLE_MSVC (4097) /* typedef-name 'identifier1' used as synonym for class-name 'identifier2' */
		LOO_WARNING_DISABLE_MSVC (4706) /* assignment within conditional expression */
#    if _MSC_VER <= 1310 // MSVC 2003
		LOO_WARNING_DISABLE_MSVC (4786) /* 'identifier' : identifier was truncated to 'number' characters in the debug information */
#    endif
		LOO_WARNING_DISABLE_MSVC (4355) /* 'this' : used in base member initializer list */
#    if _MSC_VER < 1800 // MSVC 2013
		LOO_WARNING_DISABLE_MSVC (4231) /* nonstandard extension used : 'identifier' before template explicit instantiation */
#    endif
		LOO_WARNING_DISABLE_MSVC (4710) /* function not inlined */
		LOO_WARNING_DISABLE_MSVC (4530) /* C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#  elif defined(LOO_CC_BOR)
#    pragma option -w-inl
#    pragma option -w-aus
#    pragma warn -inl
#    pragma warn -pia
#    pragma warn -ccc
#    pragma warn -rch
#    pragma warn -sig
#  endif
#endif

	namespace LooPrivate {
		template <typename T> struct LooAddConst { typedef const T Type; };
	}

	// this adds const to non-const objects (like std::as_const)
	template <typename T>
	LOO_DECL_CONSTEXPR typename LooPrivate::LooAddConst<T>::Type &std::as_const (T &t) LOO_DECL_NOTHROW { return t; }

#ifndef LOO_NO_FOREACH

	namespace LooPrivate {

		template <typename T>
		class LooForeachContainer {
			LOO_DISABLE_COPY (LooForeachContainer)
		public:
			LooForeachContainer (const T &t) : c (t), i (std::as_const (c).begin ()), e (std::as_const (c).end ()) {}
			LooForeachContainer (T &&t) : c (std::move (t)), i (std::as_const (c).begin ()), e (std::as_const (c).end ()) {}

			LooForeachContainer (LooForeachContainer &&other)
				: c (std::move (other.c)),
				i (std::as_const (c).begin ()),
				e (std::as_const (c).end ()),
				control (std::move (other.control))
			{
			}

			LooForeachContainer &operator=(LooForeachContainer &&other)
			{
				c = std::move (other.c);
				i = std::as_const (c).begin ();
				e = std::as_const (c).end ();
				control = std::move (other.control);
				return *this;
			}

			T c;
			typename T::const_iterator i, e;
			int control = 1;
		};

		template<typename T>
		LooForeachContainer<typename std::decay<T>::type> lMakeForeachContainer (T &&t)
		{
			return LooForeachContainer<typename std::decay<T>::type> (std::forward<T> (t));
		}

	}
	// Explanation of the control word:
	//  - it's initialized to 1
	//  - that means both the inner and outer loops start
	//  - if there were no breaks, at the end of the inner loop, it's set to 0, which
	//    causes it to exit (the inner loop is run exactly once)
	//  - at the end of the outer loop, it's inverted, so it becomes 1 again, allowing
	//    the outer loop to continue executing
	//  - if there was a break inside the inner loop, it will exit with control still
	//    set to 1; in that case, the outer loop will invert it to 0 and will exit too
#define LOO_FOREACH(variable, container)                                \
for (auto _container_ = LooPrivate::lMakeForeachContainer(container); \
     _container_.control && _container_.i != _container_.e;         \
     ++_container_.i, _container_.control ^= 1)                     \
    for (variable = *_container_.i; _container_.control; _container_.control = 0)

#endif // LOO_NO_FOREACH

#define LOO_FOREVER for(;;)
#ifndef LOO_NO_KEYWORDS
# ifndef LOO_NO_FOREACH
#  ifndef foreach
#    define foreach LOO_FOREACH
#  endif
# endif // LOO_NO_FOREACH
#  ifndef forever
#    define forever LOO_FOREVER
#  endif
#endif

	template <typename T> static inline T *lGetPtrHelper (T *ptr) { return ptr; }
	template <typename Wrapper> static inline typename Wrapper::pointer lGetPtrHelper (const Wrapper &p) { return p.data (); }

#define LOO_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(lGetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(lGetPtrHelper(d_ptr)); } \
    friend class Class##Private;

#define LOO_DECLARE_PRIVATE_D(Dptr, Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(lGetPtrHelper(Dptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(lGetPtrHelper(Dptr)); } \
    friend class Class##Private;

#define LOO_DECLARE_PUBLIC(Class)                                    \
    inline Class* l_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* l_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;

#define LOO_D(Class) Class##Private * const d = d_func()
#define LOO_Q(Class) Class * const q = l_func()

#define LOO_TR_NOOP(x) x
#define LOO_TR_NOOP_UTF8(x) x
#define LOO_TRANSLATE_NOOP(scope, x) x
#define LOO_TRANSLATE_NOOP_UTF8(scope, x) x
#define LOO_TRANSLATE_NOOP3(scope, x, comment) {x, comment}
#define LOO_TRANSLATE_NOOP3_UTF8(scope, x, comment) {x, comment}

#ifndef LOO_NO_TRANSLATION // ### This should enclose the NOOPs above

	// Defined in qcoreapplication.cpp
	// The better name qTrId() is reserved for an upcoming function which would
	// return a much more powerful QStringFormatter instead of a QString.
	LOO_CORE_EXPORT std::string looTrId (const char *id, int n = -1);

#define LOO_TRID_NOOP(id) id

#endif // LOO_NO_TRANSLATION

	/*
	   When RTTI is not available, define this macro to force any uses of
	   dynamic_cast to cause a compile failure.
	*/

#if defined(LOO_NO_DYNAMIC_CAST) && !defined(dynamic_cast)
#  define dynamic_cast LOO_PREPEND_NAMESPACE(loo_dynamic_cast_check)

	template<typename T, typename X>
	T loo_dynamic_cast_check (X, T* = 0)
	{
		return T::dynamic_cast_will_always_fail_because_rtti_is_disabled;
	}
#endif

	typedef std::string QByteArray;
	LOO_CORE_EXPORT QByteArray lgetenv (const char *varName);
	LOO_CORE_EXPORT bool lputenv (const char *varName, const QByteArray& value);
	LOO_CORE_EXPORT bool lunsetenv (const char *varName);

	LOO_CORE_EXPORT bool lEnvironmentVariableIsEmpty (const char *varName) LOO_DECL_NOEXCEPT;
	LOO_CORE_EXPORT bool lEnvironmentVariableIsSet (const char *varName) LOO_DECL_NOEXCEPT;
	LOO_CORE_EXPORT int  lEnvironmentVariableIntValue (const char *varName, bool *ok = LOO_NULLPTR) LOO_DECL_NOEXCEPT;

	inline int lIntCast (double f) { return int (f); }
	inline int lIntCast (float f) { return int (f); }

#define LOO_MODULE(x)

#if !defined(LOO_BOOTSTRAPPED) && defined(LOO_REDUCE_RELOCATIONS) && defined(__ELF__) && \
    (!defined(__PIC__) || (defined(__PIE__) && defined(LOO_CC_GNU) && LOO_CC_GNU >= 500))
#  error "You must build your code with position independent code if Qt was built with -reduce-relocations. "\
         "Compile your code with -fPIC (-fPIE is not enough)."
#endif

	namespace LooPrivate {
		//like std::enable_if
		template <bool B, typename T = void> struct LooEnableIf;
		template <typename T> struct LooEnableIf<true, T> { typedef T Type; };

		template <bool B, typename T, typename F> struct LooConditional { typedef T Type; };
		template <typename T, typename F> struct LooConditional<false, T, F> { typedef F Type; };
	}
}//LOO_NAMESPACE_END

// We need to keep QTypeInfo, QSysInfo, QFlags, qDebug & family in qglobal.h for compatibility with Qt 4.
// Be careful when changing the order of these files.
#include <LooCore/lootypeinfo.h>
#include <LooCore/loosysinfo.h>
#include <LooCore/loologging.h>
#include <LooCore/looflags.h>
#include <LooCore/looversiontagging.h>

#endif