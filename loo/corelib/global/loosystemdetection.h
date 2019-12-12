#ifndef LOO_CORELIB_GLOBAL_GLOBAL_H
#include <LooCore/looglobal.h>
#endif

#ifndef LOO_SYSTEMDETECTION_H
#define LOO_SYSTEMDETECTION_H

#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#  include <TargetConditionals.h>
#  if defined(TARGET_OS_MAC) && TARGET_OS_MAC
#    define LOO_OS_DARWIN
#    define LOO_OS_BSD4
#    ifdef __LP64__
#      define LOO_OS_DARWIN64
#    else
#      define LOO_OS_DARWIN32
#    endif
#    if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#      define LOO_PLATFORM_UIKIT
#      if defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
#        define LOO_OS_WATCHOS
#      elif defined(TARGET_OS_TV) && TARGET_OS_TV
#        define LOO_OS_TVOS
#      else
#        // TARGET_OS_IOS is only available in newer SDKs,
#        // so assume any other iOS-based platform is iOS for now
#        define LOO_OS_IOS
#      endif
#    else
#      // TARGET_OS_OSX is only available in newer SDKs,
#      // so assume any non iOS-based platform is macOS for now
#      define LOO_OS_MACOS
#    endif
#  else
#    error "LOO has not been ported to this Apple platform - see http://www.loo.io/developers"
#  endif
#elif defined(__ANDROID__) || defined(ANDROID)
#  define LOO_OS_ANDROID
#  define LOO_OS_LINUX
#elif defined(__CYGWIN__)
#  define LOO_OS_CYGWIN
#elif !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define LOO_OS_WIN32
#  define LOO_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  if defined(WINAPI_FAMILY)
#    ifndef WINAPI_FAMILY_PC_APP
#      define WINAPI_FAMILY_PC_APP WINAPI_FAMILY_APP
#    endif
#    if defined(WINAPI_FAMILY_PHONE_APP) && WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
#      define LOO_OS_WINRT
#    elif WINAPI_FAMILY==WINAPI_FAMILY_PC_APP
#      define LOO_OS_WINRT
#    else
#      define LOO_OS_WIN32
#    endif
#  else
#    define LOO_OS_WIN32
#  endif
#elif defined(__sun) || defined(sun)
#  define LOO_OS_SOLARIS
#elif defined(hpux) || defined(__hpux)
#  define LOO_OS_HPUX
#elif defined(__native_client__)
#  define LOO_OS_NACL
#elif defined(__EMSCRIPTEN__)
#  define LOO_OS_WASM
#elif defined(__linux__) || defined(__linux)
#  define LOO_OS_LINUX
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
#  ifndef __FreeBSD_kernel__
#    define LOO_OS_FREEBSD
#  endif
#  define LOO_OS_FREEBSD_KERNEL
#  define LOO_OS_BSD4
#elif defined(__NetBSD__)
#  define LOO_OS_NETBSD
#  define LOO_OS_BSD4
#elif defined(__OpenBSD__)
#  define LOO_OS_OPENBSD
#  define LOO_OS_BSD4
#elif defined(__INTERIX)
#  define LOO_OS_INTERIX
#  define LOO_OS_BSD4
#elif defined(_AIX)
#  define LOO_OS_AIX
#elif defined(__Lynx__)
#  define LOO_OS_LYNX
#elif defined(__GNU__)
#  define LOO_OS_HURD
#elif defined(__QNXNTO__)
#  define LOO_OS_QNX
#elif defined(__INTEGRITY)
#  define LOO_OS_INTEGRITY
#elif defined(VXWORKS) /* there is no "real" VxWorks define - this has to be set in the mkspec! */
#  define LOO_OS_VXWORKS
#elif defined(__HAIKU__)
#  define LOO_OS_HAIKU
#elif defined(__MAKEDEPEND__)
#else
#  error "LOO has not been ported to this OS - see http://www.loo-project.org/"
#endif

#if defined(LOO_OS_WIN32) || defined(LOO_OS_WIN64) || defined(LOO_OS_WINRT)
#  define LOO_OS_WINDOWS
#  define LOO_OS_WIN
#endif

#if defined(LOO_OS_WIN)
#  undef LOO_OS_UNIX
#elif !defined(LOO_OS_UNIX)
#  define LOO_OS_UNIX
#endif

// Compatibility synonyms
#ifdef LOO_OS_DARWIN
#define LOO_OS_MAC
#endif
#ifdef LOO_OS_DARWIN32
#define LOO_OS_MAC32
#endif
#ifdef LOO_OS_DARWIN64
#define LOO_OS_MAC64
#endif
#ifdef LOO_OS_MACOS
#define LOO_OS_MACX
#define LOO_OS_OSX
#endif

#ifdef LOO_OS_DARWIN
#  include <Availability.h>
#  include <AvailabilityMacros.h>
#
#  ifdef LOO_OS_MACOS
#    if !defined(__MAC_OS_X_VERSION_MIN_REQUIRED) || __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_6
#       undef __MAC_OS_X_VERSION_MIN_REQUIRED
#       define __MAC_OS_X_VERSION_MIN_REQUIRED __MAC_10_6
#    endif
#    if !defined(MAC_OS_X_VERSION_MIN_REQUIRED) || MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_6
#       undef MAC_OS_X_VERSION_MIN_REQUIRED
#       define MAC_OS_X_VERSION_MIN_REQUIRED MAC_OS_X_VERSION_10_6
#    endif
#  endif
#
#  // Numerical checks are preferred to named checks, but to be safe
#  // we define the missing version names in case LOO uses them.
#
#  if !defined(__MAC_10_11)
#       define __MAC_10_11 101100
#  endif
#  if !defined(__MAC_10_12)
#       define __MAC_10_12 101200
#  endif
#  if !defined(__MAC_10_13)
#       define __MAC_10_13 101300
#  endif
#  if !defined(__MAC_10_14)
#       define __MAC_10_14 101400
#  endif
#  if !defined(__MAC_10_15)
#       define __MAC_10_15 101500
#  endif
#  if !defined(MAC_OS_X_VERSION_10_11)
#       define MAC_OS_X_VERSION_10_11 __MAC_10_11
#  endif
#  if !defined(MAC_OS_X_VERSION_10_12)
#       define MAC_OS_X_VERSION_10_12 __MAC_10_12
#  endif
#  if !defined(MAC_OS_X_VERSION_10_13)
#       define MAC_OS_X_VERSION_10_13 __MAC_10_13
#  endif
#  if !defined(MAC_OS_X_VERSION_10_14)
#       define MAC_OS_X_VERSION_10_14 __MAC_10_14
#  endif
#  if !defined(MAC_OS_X_VERSION_10_15)
#       define MAC_OS_X_VERSION_10_15 __MAC_10_15
#  endif
#
#  if !defined(__IPHONE_10_0)
#       define __IPHONE_10_0 100000
#  endif
#  if !defined(__IPHONE_10_1)
#       define __IPHONE_10_1 100100
#  endif
#  if !defined(__IPHONE_10_2)
#       define __IPHONE_10_2 100200
#  endif
#  if !defined(__IPHONE_10_3)
#       define __IPHONE_10_3 100300
#  endif
#  if !defined(__IPHONE_11_0)
#       define __IPHONE_11_0 110000
#  endif
#  if !defined(__IPHONE_12_0)
#       define __IPHONE_12_0 120000
#  endif
#endif


#endif