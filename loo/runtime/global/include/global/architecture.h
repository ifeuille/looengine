#ifndef LOO_ARCHITECTURE_HPP
#define LOO_ARCHITECTURE_HPP
#pragma once

//判断编译环境的位数
#if defined(_AMD64_) || defined(__LP64__) || defined(_WIN64) || defined(Q_OS_DARWIN64)
#define LOO_64
#else
#define LOO_32
#endif

#if defined(LOO_COMPILER_MSVC)
#if defined(LOO_32)
#define LOO_CPU_X86
#define LOO_COMPILER_TARGLET x86
#elif defined(_M_X64)
#define LOO_CPU_X64
#define LOO_COMPILER_TARGLET x64
#elif defined(_M_ARM64)
#define LOO_CPU_ARM64
#define LOO_COMPILER_TARGLET arm64
#elif defined(_M_ARM)
#define LOO_CPU_ARM
#define LOO_COMPILER_TARGLET arm
#else
#error "Unknown CPU type. In msvc, x64, arm, and arm64 are supported."
#endif

#elif defined(LOO_COMPILER_GCC)||defined(LOO_COMPILER_CLANG)
#if defined(__x86_64__)
#define LOO_CPU_X64
#define LOO_COMPILER_TARGLET x64
#elif defined(__i386__)
#define LOO_CPU_X86
#define LOO_COMPILER_TARGLET x86
#elif defined(__arm__)
#define LOO_CPU_ARM
#define LOO_COMPILER_TARGLET arm
#elif defined(__aarch64__)
#define LOO_CPU_ARM64
#define LOO_COMPILER_TARGLET arm64
#else
#error "Unknown CPU type. In g++/clang, x86, x64, arm, and arm64 are supported."
#endif
#else 
#error "Unknown CPU type."
#endif

//
#if defined(LOO_CPU_ARM)||defined(LOO_CPU_ARM64)
#if defined(__BIG_ENDIAN__)||defined(__ARMEB__)||defined(__THUMBEB__)||defined(__AARCH64EB__)
#define LOO_BIG_ENDIAN
#else
#define LOO_LITILOO_ENDIAN
#endif
#elif defined(LOO_CPU_X86)||defined(LOO_CPU_X64)||defined(LOO_PLATFORM_WINDOWS)
#define LOO_LITILOO_ENDIAN
#else
#error "Unknown CPU endian."
#endif

// Detects optional instruction sets
#ifdef LOO_CPU_X64
#define LOO_SSE_SUPPORT
#define LOO_SSE2_SUPPORT
#define LOO_X64_SUPPORT
#if defined(LOO_COMPILER_MSVC)
#ifdef __AVX__
#define LOO_AVX_SUPPORT
#endif
#ifdef __AVX2__
#define LOO_AVX2_SUPPORT
#endif	
#elif defined(LOO_COMPILER_GCC) || defined(LOO_COMPILER_CLANG)
#ifdef __SSE3__
#define LOO_SSE3_SUPPORT
#endif
#ifdef __SSSE3__
#define LOO_SSSE3_SUPPORT
#endif
#ifdef __SSE4_1__
#define LOO_SSE4_1_SUPPORT
#endif
#ifdef __SSE4_2__
#define LOO_SSE4_2_SUPPORT
#endif
#ifdef __AVX__
#define LOO_AVX_SUPPORT
#endif
#ifdef __AVX2__
#define LOO_AVX2_SUPPORT
#endif
#endif
#elif defined LOO_CPU_X86
#if defined(LOO_COMPILER_GCC) || defined(LOO_COMPILER_CLANG)
#ifdef __MMX__
#define LOO_MMX_SUPPORT
#endif
#ifdef __SSE__
#define LOO_SSE_SUPPORT
#endif
#ifdef __SSE2__
#define LOO_SSE2_SUPPORT
#endif
#ifdef __SSE3__
#define LOO_SSE3_SUPPORT
#endif
#ifdef __SSSE3__
#define LOO_SSSE3_SUPPORT
#endif
#ifdef __SSE4_1__
#define LOO_SSE4_1_SUPPORT
#endif
#ifdef __SSE4_2__
#define LOO_SSE4_2_SUPPORT
#endif
#ifdef __AVX__
#define LOO_AVX_SUPPORT
#endif
#ifdef __AVX2__
#define LOO_AVX2_SUPPORT
#endif
#endif
#elif defined LOO_CPU_ARM
#if defined(LOO_COMPILER_MSVC)
#define LOO_NEON_SUPPORT
#elif defined(LOO_COMPILER_GCC) || defined(LOO_COMPILER_CLANG)
#ifdef __ARM_NEON__
#define LOO_NEON_SUPPORT
#endif
#endif
#elif defined LOO_CPU_ARM64
#define LOO_NEON_SUPPORT
#endif



#ifndef LOO_CACHE_LINE
#ifdef LOO_64
#define LOO_CACHE_LINE  64
#else
#define LOO_CACHE_LINE  32
#endif
#endif

#endif