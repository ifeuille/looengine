
#ifndef LOO_CORELIB_GLOBAL_GLOBAL_H
#define LOO_CORELIB_GLOBAL_GLOBAL_H
#include <type_traits>
#include <cstddef>
#include <utility>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>
#ifndef __ASSEMBLER__
#include <assert.h>
#include <stddef.h>
#endif

/*
   LOO_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define LOO_VERSION      LOO_VERSION_CHECK(LOO_MAJOR_VERSION, LOO_MINOR_VERSION, LOO_PATCH_VERSION)

#define LOO_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

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

#include <LooCore/loosystemdetection.h>
#include <LooCore/looprocessordetection.h>
#include <LooCore/loocompilerdetection.h>

#if defined (__ELF__)
#  define LOO__OF_ELF
#endif
#if defined (__MACH__) && defined (__APPLE__)
#  define LOO__OF_MACH_O
#endif

#define LOO_UNUSED(x) (void)x;

#  define LOO_STATIC_ASSERT(Condition) static_assert(bool(Condition), #Condition)
#  define LOO_STATIC_ASSERT_X(Condition, Message) static_assert(bool(Condition), Message)

#include <algorithm>

#define LOO_NAMESPACE loo
#define LOO_NAMESPACE_BEGIN namespace LOO_NAMESPACE{
#define LOO_NAMESPACE_END }
#define LOO_USE_NAMESPACE using namespace LOO_NAMESPACE;
#define LOO_PREDECLARE_CLASS(name) class LOO_NAMESPACE::name

LOO_NAMESPACE_BEGIN
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
typedef unsigned long lulong;
typedef unsigned char luchar;
typedef unsigned short lushort;

#ifndef LOO_DISABLE_DEPRECATED_BEFORE
#define LOO_DISABLE_DEPRECATED_BEFORE LOO_VERSION_CHECK(5, 0, 0)
#endif

/*
	LOO_DEPRECATED_SINCE(major, minor) evaluates as true if the Qt version is greater than
	the deprecation point specified.

	Use it to specify from which version of Qt a function or class has been deprecated

	Example:
		#if QT_DEPRECATED_SINCE(5,1)
			QT_DEPRECATED void deprecatedFunction(); //function deprecated since Qt 5.1
		#endif

*/
#ifdef LOO_DEPRECATED
#define LOO_DEPRECATED_SINCE(major, minor) (QT_VERSION_CHECK(major, minor, 0) > QT_DISABLE_DEPRECATED_BEFORE)
#else
#define LOOLOO_DEPRECATED_SINCE(major, minor) 0
#endif

/*
   The Qt modules' export macros.
   The options are:
	- defined(QT_STATIC): Qt was built or is being built in static mode
	- defined(QT_SHARED): Qt was built or is being built in shared/dynamic mode
   If neither was defined, then QT_SHARED is implied. If Qt was compiled in static
   mode, QT_STATIC is defined in qconfig.h. In shared mode, QT_STATIC is implied
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

#define Q_DISABLE_COPY_MOVE(Class) \
    LOO_DISABLE_COPY(Class) \
    LOO_DISABLE_MOVE(Class)

/*
   No, this is not an evil backdoor. QT_BUILD_INTERNAL just exports more symbols
   for Qt's internal unit tests. If you want slower loading times and more
   symbols that can vanish from version to version, feel free to define QT_BUILD_INTERNAL.
*/
#if defined(LOO_BUILD_INTERNAL) && defined(LOO_BUILDING_QT) && defined(LOO_SHARED)
#    define LOO_AUTOTEST_EXPORT LOO_DECL_EXPORT
#elif defined(LOO_BUILD_INTERNAL) && defined(LOO_SHARED)
#    define LOO_AUTOTEST_EXPORT LOO_DECL_IMPORT
#else
#    define LOO_AUTOTEST_EXPORT
#endif

LOO_CORE_EXPORT const char *looVersion (void) LOO_DECL_NOTHROW;

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
#  define LOO_ASCII_CAST_WARN Q_DECL_DEPRECATED_X("Use fromUtf8, QStringLiteral, or QLatin1String")
#else
#  define LOO_ASCII_CAST_WARN
#endif

#if defined(__i386__) || defined(_WIN32)
#  if defined(LOO_CC_GNU)
#    define QT_FASTCALL __attribute__((regparm(3)))
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
#  define QT_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(ios) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, ios, __TVOS_NA, __WATCHOS_NA)
#  define QT_TVOS_PLATFORM_SDK_EQUAL_OR_ABOVE(tvos) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, __IPHONE_NA, tvos, __WATCHOS_NA)
#  define QT_WATCHOS_PLATFORM_SDK_EQUAL_OR_ABOVE(watchos) \
      LOO_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, __IPHONE_NA, __TVOS_NA, watchos)

#  define QT_MACOS_IOS_DEPLOYMENT_TARGET_BELOW(macos, ios) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, ios, __TVOS_NA, __WATCHOS_NA)
#  define QT_MACOS_DEPLOYMENT_TARGET_BELOW(macos) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, __IPHONE_NA, __TVOS_NA, __WATCHOS_NA)
#  define QT_IOS_DEPLOYMENT_TARGET_BELOW(ios) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, ios, __TVOS_NA, __WATCHOS_NA)
#  define QT_TVOS_DEPLOYMENT_TARGET_BELOW(tvos) \
      LOO_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, __IPHONE_NA, tvos, __WATCHOS_NA)
#  define QT_WATCHOS_DEPLOYMENT_TARGET_BELOW(watchos) \
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

#endif // Q_OS_DARWIN


/*
   Data stream functions are provided by many classes (defined in qdatastream.h)
*/

class LooDataStream;

inline void loo_noop (void) {}

/*
   Avoid "unused parameter" warnings
*/
#define LOO_UNUSED(x) (void)x;

LOO_CORE_EXPORT std::string loo_error_string (int errorCode = -1);

#if !defined(LOO_ASSERT)
#  if defined(LOO_NO_DEBUG) && !defined(LOO_FORCE_ASSERTS)
#    define LOO_ASSERT(cond) do { } while ((false) && (cond))
#  else
#    define LOO_ASSERT(cond) ((!(cond)) ? loo_assert(#cond,__FILE__,__LINE__) : loo_noop())
#  endif
#endif


////////////////////////////////////////////////////

#if defined(QT_NO_DEBUG) && !defined(QT_PAINT_DEBUG)
#define QT_NO_PAINT_DEBUG
#endif

#ifndef Q_CC_MSVC
Q_NORETURN
#endif
Q_CORE_EXPORT void qt_assert_x (const char *where, const char *what, const char *file, int line) Q_DECL_NOTHROW;

#if !defined(Q_ASSERT_X)
#  if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#    define Q_ASSERT_X(cond, where, what) do { } while ((false) && (cond))
#  else
#    define Q_ASSERT_X(cond, where, what) ((!(cond)) ? qt_assert_x(where, what,__FILE__,__LINE__) : qt_noop())
#  endif
#endif


#ifdef Q_COMPILER_STATIC_ASSERT
#define Q_STATIC_ASSERT(Condition) static_assert(bool(Condition), #Condition)
#define Q_STATIC_ASSERT_X(Condition, Message) static_assert(bool(Condition), Message)
#else
// Intentionally undefined
template <bool Test> class QStaticAssertFailure;
template <> class QStaticAssertFailure<true> {};

#define Q_STATIC_ASSERT_PRIVATE_JOIN(A, B) Q_STATIC_ASSERT_PRIVATE_JOIN_IMPL(A, B)
#define Q_STATIC_ASSERT_PRIVATE_JOIN_IMPL(A, B) A ## B
#ifdef __COUNTER__
#define Q_STATIC_ASSERT(Condition) \
    enum {Q_STATIC_ASSERT_PRIVATE_JOIN(q_static_assert_result, __COUNTER__) = sizeof(QStaticAssertFailure<!!(Condition)>)}
#else
#define Q_STATIC_ASSERT(Condition) \
    enum {Q_STATIC_ASSERT_PRIVATE_JOIN(q_static_assert_result, __LINE__) = sizeof(QStaticAssertFailure<!!(Condition)>)}
#endif /* __COUNTER__ */
#define Q_STATIC_ASSERT_X(Condition, Message) Q_STATIC_ASSERT(Condition)
#endif

Q_NORETURN Q_CORE_EXPORT void qt_check_pointer (const char *, int) Q_DECL_NOTHROW;
Q_CORE_EXPORT void qBadAlloc ();

#ifdef QT_NO_EXCEPTIONS
#  if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#    define Q_CHECK_PTR(p) qt_noop()
#  else
#    define Q_CHECK_PTR(p) do {if (!(p)) qt_check_pointer(__FILE__,__LINE__);} while (false)
#  endif
#else
#  define Q_CHECK_PTR(p) do { if (!(p)) qBadAlloc(); } while (false)
#endif

template <typename T>
inline T *q_check_ptr (T *p) { Q_CHECK_PTR (p); return p; }

typedef void (*QFunctionPointer)();

#if !defined(Q_UNIMPLEMENTED)
#  define Q_UNIMPLEMENTED() qWarning("Unimplemented code.")
#endif

Q_REQUIRED_RESULT Q_DECL_CONSTEXPR static inline Q_DECL_UNUSED bool qFuzzyCompare (double p1, double p2)
{
	return (qAbs (p1 - p2) * 1000000000000. <= qMin (qAbs (p1), qAbs (p2)));
}

Q_REQUIRED_RESULT Q_DECL_CONSTEXPR static inline Q_DECL_UNUSED bool qFuzzyCompare (float p1, float p2)
{
	return (qAbs (p1 - p2) * 100000.f <= qMin (qAbs (p1), qAbs (p2)));
}

Q_REQUIRED_RESULT Q_DECL_CONSTEXPR static inline Q_DECL_UNUSED bool qFuzzyIsNull (double d)
{
	return qAbs (d) <= 0.000000000001;
}

Q_REQUIRED_RESULT Q_DECL_CONSTEXPR static inline Q_DECL_UNUSED  bool qFuzzyIsNull (float f)
{
	return qAbs (f) <= 0.00001f;
}

/*
   This function tests a double for a null value. It doesn't
   check whether the actual value is 0 or close to 0, but whether
   it is binary 0, disregarding sign.
*/
Q_REQUIRED_RESULT static inline Q_DECL_UNUSED bool qIsNull (double d)
{
	union U {
		double d;
		quint64 u;
	};
	U val;
	val.d = d;
	return (val.u & Q_UINT64_C (0x7fffffffffffffff)) == 0;
}

/*
   This function tests a float for a null value. It doesn't
   check whether the actual value is 0 or close to 0, but whether
   it is binary 0, disregarding sign.
*/
Q_REQUIRED_RESULT static inline Q_DECL_UNUSED bool qIsNull (float f)
{
	union U {
		float f;
		quint32 u;
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

#ifdef Q_FULL_TEMPLATE_INSTANTIATION
#  define Q_DUMMY_COMPARISON_OPERATOR(C) \
    bool operator==(const C&) const { \
        qWarning(#C"::operator==(const "#C"&) was called"); \
        return false; \
    }
#else

#  define Q_DUMMY_COMPARISON_OPERATOR(C)
#endif

namespace QtPrivate
{
	namespace SwapExceptionTester { // insulate users from the "using std::swap" below
		using std::swap; // import std::swap
		template <typename T>
		void checkSwap (T &t)
			Q_DECL_NOEXCEPT_EXPR (noexcept(swap (t, t)));
		// declared, but not implemented (only to be used in unevaluated contexts (noexcept operator))
	}
} // namespace QtPrivate

template <typename T>
inline void qSwap (T &value1, T &value2)
Q_DECL_NOEXCEPT_EXPR (noexcept(QtPrivate::SwapExceptionTester::checkSwap (value1)))
{
	using std::swap;
	swap (value1, value2);
}

#if QT_DEPRECATED_SINCE(5, 0)
Q_CORE_EXPORT QT_DEPRECATED void *qMalloc (size_t size) Q_ALLOC_SIZE (1);
Q_CORE_EXPORT QT_DEPRECATED void qFree (void *ptr);
Q_CORE_EXPORT QT_DEPRECATED void *qRealloc (void *ptr, size_t size) Q_ALLOC_SIZE (2);
Q_CORE_EXPORT QT_DEPRECATED void *qMemCopy (void *dest, const void *src, size_t n);
Q_CORE_EXPORT QT_DEPRECATED void *qMemSet (void *dest, int c, size_t n);
#endif
Q_CORE_EXPORT void *qMallocAligned (size_t size, size_t alignment) Q_ALLOC_SIZE (1);
Q_CORE_EXPORT void *qReallocAligned (void *ptr, size_t size, size_t oldsize, size_t alignment) Q_ALLOC_SIZE (2);
Q_CORE_EXPORT void qFreeAligned (void *ptr);


/*
   Avoid some particularly useless warnings from some stupid compilers.
   To get ALL C++ compiler warnings, define QT_CC_WARNINGS or comment out
   the line "#define QT_NO_WARNINGS".
*/
#if !defined(QT_CC_WARNINGS)
#  define QT_NO_WARNINGS
#endif
#if defined(QT_NO_WARNINGS)
#  if defined(Q_CC_MSVC)
QT_WARNING_DISABLE_MSVC (4251) /* class 'type' needs to have dll-interface to be used by clients of class 'type2' */
QT_WARNING_DISABLE_MSVC (4244) /* conversion from 'type1' to 'type2', possible loss of data */
QT_WARNING_DISABLE_MSVC (4275) /* non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier' */
QT_WARNING_DISABLE_MSVC (4514) /* unreferenced inline function has been removed */
QT_WARNING_DISABLE_MSVC (4800) /* 'type' : forcing value to bool 'true' or 'false' (performance warning) */
QT_WARNING_DISABLE_MSVC (4097) /* typedef-name 'identifier1' used as synonym for class-name 'identifier2' */
QT_WARNING_DISABLE_MSVC (4706) /* assignment within conditional expression */
#    if _MSC_VER <= 1310 // MSVC 2003
QT_WARNING_DISABLE_MSVC (4786) /* 'identifier' : identifier was truncated to 'number' characters in the debug information */
#    endif
QT_WARNING_DISABLE_MSVC (4355) /* 'this' : used in base member initializer list */
#    if _MSC_VER < 1800 // MSVC 2013
	QT_WARNING_DISABLE_MSVC (4231) /* nonstandard extension used : 'identifier' before template explicit instantiation */
#    endif
	QT_WARNING_DISABLE_MSVC (4710) /* function not inlined */
	QT_WARNING_DISABLE_MSVC (4530) /* C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#  elif defined(Q_CC_BOR)
#    pragma option -w-inl
#    pragma option -w-aus
#    pragma warn -inl
#    pragma warn -pia
#    pragma warn -ccc
#    pragma warn -rch
#    pragma warn -sig
#  endif
#endif

namespace QtPrivate {
	template <typename T> struct QAddConst { typedef const T Type; };
}

// this adds const to non-const objects (like std::as_const)
template <typename T>
Q_DECL_CONSTEXPR typename QtPrivate::QAddConst<T>::Type &qAsConst (T &t) Q_DECL_NOTHROW { return t; }
// prevent rvalue arguments:
template <typename T>
void qAsConst (const T &&) Q_DECL_EQ_DELETE;

#ifndef QT_NO_FOREACH

namespace QtPrivate {

	template <typename T>
	class QForeachContainer {
		Q_DISABLE_COPY (QForeachContainer)
	public:
		QForeachContainer (const T &t) : c (t), i (qAsConst (c).begin ()), e (qAsConst (c).end ()) {}
		QForeachContainer (T &&t) : c (std::move (t)), i (qAsConst (c).begin ()), e (qAsConst (c).end ()) {}

		QForeachContainer (QForeachContainer &&other)
			: c (std::move (other.c)),
			i (qAsConst (c).begin ()),
			e (qAsConst (c).end ()),
			control (std::move (other.control))
		{
		}

		QForeachContainer &operator=(QForeachContainer &&other)
		{
			c = std::move (other.c);
			i = qAsConst (c).begin ();
			e = qAsConst (c).end ();
			control = std::move (other.control);
			return *this;
		}

		T c;
		typename T::const_iterator i, e;
		int control = 1;
	};

	template<typename T>
	QForeachContainer<typename std::decay<T>::type> qMakeForeachContainer (T &&t)
	{
		return QForeachContainer<typename std::decay<T>::type> (std::forward<T> (t));
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
#define Q_FOREACH(variable, container)                                \
for (auto _container_ = QtPrivate::qMakeForeachContainer(container); \
     _container_.control && _container_.i != _container_.e;         \
     ++_container_.i, _container_.control ^= 1)                     \
    for (variable = *_container_.i; _container_.control; _container_.control = 0)

#endif // QT_NO_FOREACH

#define Q_FOREVER for(;;)
#ifndef QT_NO_KEYWORDS
# ifndef QT_NO_FOREACH
#  ifndef foreach
#    define foreach Q_FOREACH
#  endif
# endif // QT_NO_FOREACH
#  ifndef forever
#    define forever Q_FOREVER
#  endif
#endif

template <typename T> static inline T *qGetPtrHelper (T *ptr) { return ptr; }
template <typename Wrapper> static inline typename Wrapper::pointer qGetPtrHelper (const Wrapper &p) { return p.data (); }

#define Q_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr)); } \
    friend class Class##Private;

#define Q_DECLARE_PRIVATE_D(Dptr, Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(Dptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(Dptr)); } \
    friend class Class##Private;

#define Q_DECLARE_PUBLIC(Class)                                    \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;

#define Q_D(Class) Class##Private * const d = d_func()
#define Q_Q(Class) Class * const q = q_func()

#define QT_TR_NOOP(x) x
#define QT_TR_NOOP_UTF8(x) x
#define QT_TRANSLATE_NOOP(scope, x) x
#define QT_TRANSLATE_NOOP_UTF8(scope, x) x
#define QT_TRANSLATE_NOOP3(scope, x, comment) {x, comment}
#define QT_TRANSLATE_NOOP3_UTF8(scope, x, comment) {x, comment}

#ifndef QT_NO_TRANSLATION // ### This should enclose the NOOPs above

// Defined in qcoreapplication.cpp
// The better name qTrId() is reserved for an upcoming function which would
// return a much more powerful QStringFormatter instead of a QString.
Q_CORE_EXPORT QString qtTrId (const char *id, int n = -1);

#define QT_TRID_NOOP(id) id

#endif // QT_NO_TRANSLATION

/*
   When RTTI is not available, define this macro to force any uses of
   dynamic_cast to cause a compile failure.
*/

#if defined(QT_NO_DYNAMIC_CAST) && !defined(dynamic_cast)
#  define dynamic_cast QT_PREPEND_NAMESPACE(qt_dynamic_cast_check)

template<typename T, typename X>
T qt_dynamic_cast_check (X, T* = 0)
{
	return T::dynamic_cast_will_always_fail_because_rtti_is_disabled;
}
#endif


#ifdef Q_QDOC

// Just for documentation generation
template<typename T>
auto qOverload (T functionPointer);
template<typename T>
auto qConstOverload (T memberFunctionPointer);
template<typename T>
auto qNonConstOverload (T memberFunctionPointer);

#elif defined(Q_COMPILER_VARIADIC_TEMPLATES)

template <typename... Args>
struct QNonConstOverload
{
	template <typename R, typename T>
	Q_DECL_CONSTEXPR auto operator()(R (T::*ptr)(Args...)) const Q_DECL_NOTHROW -> decltype(ptr)
	{
		return ptr;
	}

	template <typename R, typename T>
	static Q_DECL_CONSTEXPR auto of (R (T::*ptr)(Args...)) Q_DECL_NOTHROW -> decltype(ptr)
	{
		return ptr;
	}
};

template <typename... Args>
struct QConstOverload
{
	template <typename R, typename T>
	Q_DECL_CONSTEXPR auto operator()(R (T::*ptr)(Args...) const) const Q_DECL_NOTHROW -> decltype(ptr)
	{
		return ptr;
	}

	template <typename R, typename T>
	static Q_DECL_CONSTEXPR auto of (R (T::*ptr)(Args...) const) Q_DECL_NOTHROW -> decltype(ptr)
	{
		return ptr;
	}
};

template <typename... Args>
struct QOverload : QConstOverload<Args...>, QNonConstOverload<Args...>
{
	using QConstOverload<Args...>::of;
	using QConstOverload<Args...>::operator();
	using QNonConstOverload<Args...>::of;
	using QNonConstOverload<Args...>::operator();

	template <typename R>
	Q_DECL_CONSTEXPR auto operator()(R (*ptr)(Args...)) const Q_DECL_NOTHROW -> decltype(ptr)
	{
		return ptr;
	}

	template <typename R>
	static Q_DECL_CONSTEXPR auto of (R (*ptr)(Args...)) Q_DECL_NOTHROW -> decltype(ptr)
	{
		return ptr;
	}
};

#if defined(__cpp_variable_templates) && __cpp_variable_templates >= 201304 // C++14
template <typename... Args> Q_CONSTEXPR Q_DECL_UNUSED QOverload<Args...> qOverload = {};
template <typename... Args> Q_CONSTEXPR Q_DECL_UNUSED QConstOverload<Args...> qConstOverload = {};
template <typename... Args> Q_CONSTEXPR Q_DECL_UNUSED QNonConstOverload<Args...> qNonConstOverload = {};
#endif

#endif


class QByteArray;
Q_CORE_EXPORT QByteArray qgetenv (const char *varName);
Q_CORE_EXPORT bool qputenv (const char *varName, const QByteArray& value);
Q_CORE_EXPORT bool qunsetenv (const char *varName);

Q_CORE_EXPORT bool qEnvironmentVariableIsEmpty (const char *varName) Q_DECL_NOEXCEPT;
Q_CORE_EXPORT bool qEnvironmentVariableIsSet (const char *varName) Q_DECL_NOEXCEPT;
Q_CORE_EXPORT int  qEnvironmentVariableIntValue (const char *varName, bool *ok = Q_NULLPTR) Q_DECL_NOEXCEPT;

inline int qIntCast (double f) { return int (f); }
inline int qIntCast (float f) { return int (f); }

/*
  Reentrant versions of basic rand() functions for random number generation
*/
Q_CORE_EXPORT void qsrand (uint seed);
Q_CORE_EXPORT int qrand ();

#define QT_MODULE(x)

#if !defined(QT_BOOTSTRAPPED) && defined(QT_REDUCE_RELOCATIONS) && defined(__ELF__) && \
    (!defined(__PIC__) || (defined(__PIE__) && defined(Q_CC_GNU) && Q_CC_GNU >= 500))
#  error "You must build your code with position independent code if Qt was built with -reduce-relocations. "\
         "Compile your code with -fPIC (-fPIE is not enough)."
#endif

namespace QtPrivate {
	//like std::enable_if
	template <bool B, typename T = void> struct QEnableIf;
	template <typename T> struct QEnableIf<true, T> { typedef T Type; };

	template <bool B, typename T, typename F> struct QConditional { typedef T Type; };
	template <typename T, typename F> struct QConditional<false, T, F> { typedef F Type; };
}
LOO_NAMESPACE_END

// We need to keep QTypeInfo, QSysInfo, QFlags, qDebug & family in qglobal.h for compatibility with Qt 4.
// Be careful when changing the order of these files.
#include <LooCore/lootypeinfo.h>
#include <LooCore/loosysinfo.h>
#include <LooCore/loologging.h>
#include <LooCore/looflags.h>
#include <LooCore/looversiontagging.h>

#endif