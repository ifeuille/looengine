
#include "looprocessordetection.h"

// main part: processor type
#if defined(LOO_PROCESSOR_ALPHA)
#  define ARCH_PROCESSOR "alpha"
#elif defined(LOO_PROCESSOR_ARM_32)
#  define ARCH_PROCESSOR "arm"
#elif defined(LOO_PROCESSOR_ARM_64)
#  define ARCH_PROCESSOR "arm64"
#elif defined(LOO_PROCESSOR_AVR32)
#  define ARCH_PROCESSOR "avr32"
#elif defined(LOO_PROCESSOR_BLACKFIN)
#  define ARCH_PROCESSOR "bfin"
#elif defined(LOO_PROCESSOR_X86_32)
#  define ARCH_PROCESSOR "i386"
#elif defined(LOO_PROCESSOR_X86_64)
#  define ARCH_PROCESSOR "x86_64"
#elif defined(LOO_PROCESSOR_IA64)
#  define ARCH_PROCESSOR "ia64"
#elif defined(LOO_PROCESSOR_MIPS_64)
#  define ARCH_PROCESSOR "mips64"
#elif defined(LOO_PROCESSOR_MIPS)
#  define ARCH_PROCESSOR "mips"
#elif defined(LOO_PROCESSOR_POWER_32)
#  define ARCH_PROCESSOR "power"
#elif defined(LOO_PROCESSOR_POWER_64)
#  define ARCH_PROCESSOR "power64"
#elif defined(LOO_PROCESSOR_S390_X)
#  define ARCH_PROCESSOR "s390x"
#elif defined(LOO_PROCESSOR_S390)
#  define ARCH_PROCESSOR "s390"
#elif defined(LOO_PROCESSOR_SH)
#  define ARCH_PROCESSOR "sh"
#elif defined(LOO_PROCESSORS_SPARC_64)
#  define ARCH_PROCESSOR "sparc64"
#elif defined(LOO_PROCESSOR_SPARC_V9)
#  define ARCH_PROCESSOR "sparcv9"
#elif defined(LOO_PROCESSOR_SPARC)
#  define ARCH_PROCESSOR "sparc"
#else
#  define ARCH_PROCESSOR "unknown"
#endif

// endianness
#if LOO_BYTE_ORDER == LOO_LITTLE_ENDIAN
#  define ARCH_ENDIANNESS "little_endian"
#elif LOO_BYTE_ORDER == LOO_BIG_ENDIAN
#  define ARCH_ENDIANNESS "big_endian"
#endif

// pointer type
#if defined(LOO_OS_WIN64) || (defined(LOO_OS_WINRT) && defined(_M_X64))
#  define ARCH_POINTER "llp64"
#elif defined(__LP64__) || LOO_POINTER_SIZE - 0 == 8
#  define ARCH_POINTER "lp64"
#else
#  define ARCH_POINTER "ilp32"
#endif


// secondary: ABI string (includes the dash)
#if defined(__ARM_EABI__) || defined(__mips_eabi)
#  define ARCH_ABI1 "-eabi"
#elif defined(_MIPS_SIM)
#  if _MIPS_SIM == _ABIO32
#    define ARCH_ABI1 "-o32"
#  elif _MIPS_SIM == _ABIN32
#    define ARCH_ABI1 "-n32"
#  elif _MIPS_SIM == _ABI64
#    define ARCH_ABI1 "-n64"
#  elif _MIPS_SIM == _ABIO64
#    define ARCH_ABI1 "-o64"
#  endif
#else
#  define ARCH_ABI1 ""
#endif
#if defined(__ARM_PCS_VFP) || defined(__mips_hard_float)
// Use "-hardfloat" for platforms that usually have no FPUs
// (and for the platforms which had "-hardfloat" before we established the rule)
#  define ARCH_ABI2 "-hardfloat"
#elif defined(_SOFT_FLOAT)
// Use "-softfloat" for architectures that usually have FPUs
#  define ARCH_ABI2 "-softfloat"
#else
#  define ARCH_ABI2 ""
#endif

#define ARCH_ABI ARCH_ABI1 ARCH_ABI2

#define ARCH_FULL ARCH_PROCESSOR "-" ARCH_ENDIANNESS "-" ARCH_POINTER ARCH_COORD_TYPE ARCH_ABI
