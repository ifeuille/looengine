#ifndef LOOREFLECT_BUILTIN_PODTYPE_H
#define LOOREFLECT_BUILTIN_PODTYPE_H
#pragma once
#include "looreflect/looreflect.h"

#define TYPES                                       \
    X(bool, Bool, "%d")                             \
    X(char, Char, "%d")                             \
    X(short, Short, "%d")                           \
    X(int, Int, "%d")                               \
    X(long, Long, "%ld")                            \
    X(long long, LongLong, "%lld")                  \
    X(float, Float, "%.9g")                         \
    X(double, Double, "%.17g")                      \
    X(long double, LongDouble, "%.21Lg")            \
    X(unsigned char, UnsignedChar, "%u")            \
    X(unsigned short, UnsignedShort, "%u")          \
    X(unsigned int, UnsignedInt, "%u")              \
    X(unsigned long, UnsignedLong, "%lu")           \
    X(unsigned long long, UnsignedLongLong, "%llu") \

#define XSTRINGIFY(s) #s
#define STRINGIFY(s) XSTRINGIFY(s)

namespace looreflect {
	namespace detail {
#define X(T, NAME, FMT) \
	inline LooType const *LooGetTypeImpl(LooTypeTag<T>) noexcept { \
		struct NAME : public LooType { \
			using LooType::LooType; \
			virtual void \
			dump(void const *instance, FILE *file = stdout) const noexcept{ \
				fprintf(file, FMT, *(T const *)instance); \
			} \
			virtual bool is_pod () const noexcept override { return true; };\
		}; \
		static NAME type{ sizeof(T), Hash(STRINGIFY(T)), STRINGIFY(T), }; \
		return &type; \
	}

	/* void is special. */
	inline LooType const *	LooGetTypeImpl (LooTypeTag<void>) noexcept	{
		struct Void : public LooType {
			using LooType::LooType;
			virtual void dump (void const *instance, FILE *file = stdout) const noexcept{
				fprintf (file, "%p", instance);
			}
			virtual bool is_pod () const noexcept override { return true; };
		};
		static Void type{ 0, Hash ("void"), "void" };
		return &type;
	}

	TYPES

#undef X
//#undef TYPES
	}
}
#undef XSTRINGIFY
#undef STRINGIFY

#endif