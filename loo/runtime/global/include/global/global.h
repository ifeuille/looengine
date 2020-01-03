#ifndef LOO_GLOBAL_H
#define LOO_GLOBAL_H
#pragma once

#include "global/config.h"
#include "global/Compiler.h"
#include "global/platform.h"
#include "global/architecture.h"
#include <assert.h>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define LOO_UNUSED(x) (void)(x)

namespace loo
{
	template<typename T32BITS, typename T64BITS, int PointerSize>
	struct SelectIntPointerType
	{
		// nothing here are is it an error if the partial specializations fail
	};

	template<typename T32BITS, typename T64BITS>
	struct SelectIntPointerType<T32BITS, T64BITS, 8>
	{
		typedef T64BITS TIntPointer; // select the 64 bit type
	};

	template<typename T32BITS, typename T64BITS>
	struct SelectIntPointerType<T32BITS, T64BITS, 4>
	{
		typedef T32BITS TIntPointer; // select the 32 bit type
	};
}
namespace loo
{
	typedef signed char int8;       
	typedef unsigned char uint8;  
	typedef short int16;           
	typedef unsigned short uint16;
	typedef int int32;              
	typedef unsigned int uint32;
	typedef signed long long int64;
	typedef unsigned long long uint64;
	typedef float float32;
	typedef double float64;


	typedef char ANSICHAR;
	typedef wchar_t WIDECHAR;
	typedef uint8 char8;
	typedef uint16 char16;
	typedef uint32 char32;

	typedef SelectIntPointerType<uint32, uint64, sizeof (void*)>::TIntPointer UPTRINT;	// unsigned int the same size as a pointer
	typedef SelectIntPointerType<int32, int64, sizeof (void*)>::TIntPointer PTRINT;		// signed int the same size as a pointer
	typedef UPTRINT SIZE_T;																// unsigned int the same size as a pointer
	typedef PTRINT SSIZE_T;																// signed int the same size as a pointer

}

#ifdef LOO_DEBUG
#define LOO_DBG_SUFFIX "_d"
#else
#define LOO_DBG_SUFFIX ""
#endif

#define LOO_OUTPUT_SUFFIX "_" LOO_STRINGIZE(LOO_COMPILER_NAME) LOO_STRINGIZE(LOO_COMPILER_VERSION) LOO_DBG_SUFFIX


#if defined(LOO_CXX2A_LIBRARY_ENDIAN_SUPPORT)
#include <type_traits>
#else
namespace std
{
	enum class endian
	{
		little = 0,
		big = 1,

#if defined(LOO_CPU_ARM) || defined(LOO_CPU_ARM64)
#if defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__)
		native = big
#else
		native = little
#endif
#elif defined(LOO_CPU_X86) || defined(LOO_CPU_X64) || defined(LOO_PLATFORM_WINDOWS)
		native = little
#else
#error "Unknown CPU endian."
#endif
	};
}
#endif

#if defined(LOO_CPU_ARM) || defined(LOO_CPU_ARM64)
#if defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__)
#define LOO_PLATFORM_BIG_ENDIAN
#else
#define LOO_PLATFORM_LITTLE_ENDIAN
#endif
#elif defined(LOO_CPU_X86) || defined(LOO_CPU_X64) || defined(LOO_PLATFORM_WINDOWS)
#define LOO_PLATFORM_LITTLE_ENDIAN
#else
#error "Unknown CPU endian."
#endif


#define DLL_SUFFIX LOO_OUTPUT_SUFFIX "." DLL_EXT_NAME


#define ASSERT_MSG(con,msg) assert((con)&&msg)

#ifdef LOO_COMPILER_MSVC
#define LOO_RESTRICT __restrict
#define LOO_ASSUME(x) (__assume(x))
#else
#define LOO_RESTRICT
#define LOO_ASSUME(x) (assert(x))
#endif

#endif