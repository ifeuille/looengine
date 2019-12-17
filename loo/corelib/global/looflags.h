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
		LOO_DECL_CONSTEXPR inline QFlag (int ai) Q_DECL_NOTHROW : i (ai) {}
		Q_DECL_CONSTEXPR inline operator int () const Q_DECL_NOTHROW { return i; }

#if !defined(Q_CC_MSVC)
		// Microsoft Visual Studio has buggy behavior when it comes to
		// unsigned enums: even if the enum is unsigned, the enum tags are
		// always signed
#  if !defined(__LP64__) && !defined(Q_QDOC)
		Q_DECL_CONSTEXPR inline QFlag (long ai) Q_DECL_NOTHROW : i (int (ai)) {}
		Q_DECL_CONSTEXPR inline QFlag (ulong ai) Q_DECL_NOTHROW : i (int (long (ai))) {}
#  endif
		Q_DECL_CONSTEXPR inline QFlag (uint ai) Q_DECL_NOTHROW : i (int (ai)) {}
		Q_DECL_CONSTEXPR inline QFlag (short ai) Q_DECL_NOTHROW : i (int (ai)) {}
		Q_DECL_CONSTEXPR inline QFlag (ushort ai) Q_DECL_NOTHROW : i (int (uint (ai))) {}
		Q_DECL_CONSTEXPR inline operator uint() const Q_DECL_NOTHROW { return uint (i); }
#endif
	};
	Q_DECLARE_TYPEINFO (QFlag, Q_PRIMITIVE_TYPE);

}


#endif