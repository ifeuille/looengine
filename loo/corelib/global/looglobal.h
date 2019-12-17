
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

#  define Q_STATIC_ASSERT(Condition) static_assert(bool(Condition), #Condition)
#  define Q_STATIC_ASSERT_X(Condition, Message) static_assert(bool(Condition), Message)

#include <algorithm>

#define LOO_NAMESPACE loo
#define LOO_NAMESPACE_BEGIN namespace LOO_NAMESPACE{
#define LOO_NAMESPACE_END }
#define LOO_USE_NAMESPACE using namespace LOO_NAMESPACE;
#define LOO_PREDECLARE_CLASS(name) class LOO_NAMESPACE::name


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



#define LOO_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

#define LOO_DISABLE_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

#define Q_DISABLE_COPY_MOVE(Class) \
    LOO_DISABLE_COPY(Class) \
    LOO_DISABLE_MOVE(Class)

#endif