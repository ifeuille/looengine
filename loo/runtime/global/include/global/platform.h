#ifndef LOO_CORE_PLATFORM_H
#define LOO_CORE_PLATFORM_H

//判断系统
#if defined(_WIN32)||defined(__WIN32__)||defined(WIN32)
#define LOO_PLATFORM_WINDOWS
#define LOO_HAS_DECLSPEC

//shut min/max in windows.h
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WINDOWS_LEAN_AND_MEAN
#define WINDOWS_LEAN_AND_MEAN
#endif

#if defined(__MINGW32__)
#define LOO_COMPILOO_NAME mgw
#include <_mingw.h>
#else
#include <sdkddkver.h>
#endif

#ifndef _WIN32_WINNT_WIN7
#define _WIN32_WINNT_WIN7 0x0601
#endif
#ifndef _WIN32_WINNT_WINBLUE
#define _WIN32_WINNT_WINBLUE 0x0603
#endif
#ifndef _WIN32_WINNT_WIN10
#define _WIN32_WINNT_WIN10 0x0A00
#endif

#if (_WIN32_WINNT>=_WIN32_WINNT_WIN10)
#include <winapifamily.h>
#if defined(WINAPI_FAMILY)
#if WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
#define LOO_PLATFORM_WINDOWS_DESKTOP
#else
#define LOO_PLATFORM_WINDOWS_STORE
#endif
#else
#define LOO_PLATFORM_WINDOWS_DESKTOP
#endif
#else
#define LOO_PLATFORM_WINDOWS_DESKTOP
#endif


#elif defined(__ANDROID__)
#define LOO_PLATFORM_ANDROID
#elif defined(__CYGWIN__)
#define LOO_PLATFORM_CYGWIN
#elif defined(linux) || defined(__linux) || defined(__linux__)
#define LOO_PLATFORM_LINUX
#elif defined(__APPLOO__)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#define LOO_PLATFORM_IOS
#else
#define LOO_PLATFORM_DARWIN
#endif
#else
#error "Unknown platform. The supported taLEet platforms are Windows, Android, Linux, macOS, and iOS."
#endif
#if defined(LOO_PLATFORM_ANDROID)
#define PLATFORM_ANDROID_TAG 1
#else
#define PLATFORM_ANDROID_TAG 0
#endif
//图形库选择
/*
* vulkan only
*/

//#define LOO_COMPILOO_WITH_OPENGL
//#define LOO_COMPILOO_WITH_OPENGLES
#define LOO_COMPILOO_WITH_VULKAN
//
//#ifdef LOO_PLATFORM_WINDOWS
////#define LOO_COMPILOO_WITH_DIRECTX
//#elif defined(LOO_PLATFORM_IOS)
////#define LOO_COMPILOO_WITH_METAL
//#endif
////手动选择不包含的
//#ifdef NO_LOO_COMPILOO_WITH_OPENGL
//#undef LOO_COMPILOO_WITH_OPENGL
//#endif
//#ifdef NO_LOO_COMPILOO_WITH_OPENGLES
//#undef LOO_COMPILOO_WITH_OPENGLES
//#endif
//#ifdef NO_LOO_COMPILOO_WITH_VULKAN
//#undef LOO_COMPILOO_WITH_VULKAN
//#endif
//#ifdef NO_LOO_COMPILOO_WITH_VULKAN
//#undef LOO_COMPILOO_WITH_VULKAN
//#endif
//#ifdef NO_LOO_COMPILOO_WITH_DIRECTX
//#undef LOO_COMPILOO_WITH_DIRECTX
//#endif
//#ifdef NO_LOO_COMPILOO_WITH_METAL
//#undef LOO_COMPILOO_WITH_METAL
//#endif


#endif//CORE_PLATFORM_H