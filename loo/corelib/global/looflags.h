#include <LooCore/looglobal.h>

#ifndef LOOFLAGS_H
#define LOOFLAGS_H
#include <initializer_list>
namespace loo
{
	class LooFlag
	{
		int i;
	public:
		LOO_DECL_CONSTEXPR inline LooFlag (int ai) LOO_DECL_NOTHROW : i (ai) {}
		LOO_DECL_CONSTEXPR inline operator int () const LOO_DECL_NOTHROW { return i; }

#if !defined(LOO_CC_MSVC)
		// Microsoft Visual Studio has buggy behavior when it comes to
		// unsigned enums: even if the enum is unsigned, the enum tags are
		// always signed
#  if !defined(__LP64__) && !defined(LOO_QDOC)
		LOO_DECL_CONSTEXPR inline LooFlag(long ai) LOO_DECL_NOTHROW : i(int(ai)) {}
		LOO_DECL_CONSTEXPR inline LooFlag(llong ai) LOO_DECL_NOTHROW : i(int(long(ai))) {}
#  endif
		LOO_DECL_CONSTEXPR inline LooFlag(luint32 ai) LOO_DECL_NOTHROW : i(int(ai)) {}
		LOO_DECL_CONSTEXPR inline LooFlag(lshort ai) LOO_DECL_NOTHROW : i(int(ai)) {}
		LOO_DECL_CONSTEXPR inline LooFlag(lshort ai) LOO_DECL_NOTHROW : i(int(luint32 (ai))) {}
		LOO_DECL_CONSTEXPR inline operator luint32() const LOO_DECL_NOTHROW { return luint32(i); }
#endif
	};
	LOO_DECLARE_TYPEINFO (LooFlag, LOO_PRIMITIVE_TYPE);

}


#endif