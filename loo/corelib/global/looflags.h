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
		LOO_DECL_CONSTEXPR inline LooFlag(unsigned long ai) LOO_DECL_NOTHROW : i(int(long(ai))) {}
#  endif
		LOO_DECL_CONSTEXPR inline LooFlag(luint32 ai) LOO_DECL_NOTHROW : i(int(ai)) {}
		LOO_DECL_CONSTEXPR inline LooFlag(lshort ai) LOO_DECL_NOTHROW : i(int(ai)) {}
		LOO_DECL_CONSTEXPR inline LooFlag(lushort ai) LOO_DECL_NOTHROW : i(int(luint32 (ai))) {}
		LOO_DECL_CONSTEXPR inline operator luint32() const LOO_DECL_NOTHROW { return luint32(i); }
#endif
	};
	LOO_DECLARE_TYPEINFO (LooFlag, LOO_PRIMITIVE_TYPE);

	class LooIncompatibleFlag
	{
		int i;
	public:
		LOO_DECL_CONSTEXPR inline explicit LooIncompatibleFlag (int i) LOO_DECL_NOTHROW;
		LOO_DECL_CONSTEXPR inline operator int () const LOO_DECL_NOTHROW { return i; }
	};
	LOO_DECLARE_TYPEINFO (LooIncompatibleFlag, LOO_PRIMITIVE_TYPE);

#ifndef Q_NO_TYPESAFE_FLAGS

	template<typename Enum>
	class LooFlags
	{
		LOO_STATIC_ASSERT_X ((sizeof (Enum) <= sizeof (int)),
			"LooFlags uses an int as storage, so an enum with underlying "
			"long long will overflow.");
		struct Private;
		typedef int (Private::*Zero);
	public:

		typedef int Int;

		typedef Enum enum_type;
		// compiler-generated copy/move ctor/assignment operators are fine!

		LOO_DECL_CONSTEXPR inline LooFlags (Enum f) LOO_DECL_NOTHROW : i (Int (f)) {}
		LOO_DECL_CONSTEXPR inline LooFlags (Zero = nullptr) LOO_DECL_NOTHROW : i (0) {}
		LOO_DECL_CONSTEXPR inline LooFlags (LooFlag f) LOO_DECL_NOTHROW : i (f) {}

		LOO_DECL_CONSTEXPR inline LooFlags (std::initializer_list<Enum> flags) LOO_DECL_NOTHROW
			: i (initializer_list_helper (flags.begin (), flags.end ())) {}


		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &operator&=(int mask) LOO_DECL_NOTHROW { i &= mask; return *this; }
		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &operator&=(luint32 mask) LOO_DECL_NOTHROW { i &= mask; return *this; }
		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &operator&=(Enum mask) LOO_DECL_NOTHROW { i &= Int (mask); return *this; }
		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &operator|=(LooFlags f) LOO_DECL_NOTHROW { i |= f.i; return *this; }
		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &operator|=(Enum f) LOO_DECL_NOTHROW { i |= Int (f); return *this; }
		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &operator^=(LooFlags f) LOO_DECL_NOTHROW { i ^= f.i; return *this; }
		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &operator^=(Enum f) LOO_DECL_NOTHROW { i ^= Int (f); return *this; }

		LOO_DECL_CONSTEXPR inline operator Int() const LOO_DECL_NOTHROW { return i; }

		LOO_DECL_CONSTEXPR inline LooFlags operator|(LooFlags f) const LOO_DECL_NOTHROW { return LooFlags (LooFlag (i | f.i)); }
		LOO_DECL_CONSTEXPR inline LooFlags operator|(Enum f) const LOO_DECL_NOTHROW { return LooFlags (LooFlag (i | Int (f))); }
		LOO_DECL_CONSTEXPR inline LooFlags operator^(LooFlags f) const LOO_DECL_NOTHROW { return LooFlags (LooFlag (i ^ f.i)); }
		LOO_DECL_CONSTEXPR inline LooFlags operator^(Enum f) const LOO_DECL_NOTHROW { return LooFlags (LooFlag (i ^ Int (f))); }
		LOO_DECL_CONSTEXPR inline LooFlags operator&(int mask) const LOO_DECL_NOTHROW { return LooFlags (LooFlag (i & mask)); }
		LOO_DECL_CONSTEXPR inline LooFlags operator&(luint32 mask) const LOO_DECL_NOTHROW { return LooFlags (LooFlag (i & mask)); }
		LOO_DECL_CONSTEXPR inline LooFlags operator&(Enum f) const LOO_DECL_NOTHROW { return LooFlags (LooFlag (i & Int (f))); }
		LOO_DECL_CONSTEXPR inline LooFlags operator~() const LOO_DECL_NOTHROW { return LooFlags (LooFlag (~i)); }

		LOO_DECL_CONSTEXPR inline bool operator!() const LOO_DECL_NOTHROW { return !i; }

		LOO_DECL_CONSTEXPR inline bool testFlag (Enum f) const LOO_DECL_NOTHROW { return (i & Int (f)) == Int (f) && (Int (f) != 0 || i == Int (f)); }
		LOO_DECL_RELAXED_CONSTEXPR inline LooFlags &setFlag (Enum f, bool on = true) LOO_DECL_NOTHROW
		{
			return on ? (*this |= f) : (*this &= ~f);
		}

	private:

		LOO_DECL_CONSTEXPR static inline Int initializer_list_helper (typename std::initializer_list<Enum>::const_iterator it,
			typename std::initializer_list<Enum>::const_iterator end)
			LOO_DECL_NOTHROW
		{
			return (it == end ? Int (0) : (Int (*it) | initializer_list_helper (it + 1, end)));
		}


		Int i;
	};

#define LOO_DECLARE_FLAGS(Flags, Enum)\
typedef LooFlags<Enum> Flags;

#define LOO_DECLARE_INCOMPATIBLE_FLAGS(Flags) \
LOO_DECL_CONSTEXPR inline LooIncompatibleFlag operator|(Flags::enum_type f1, int f2) LOO_DECL_NOTHROW \
{ return LooIncompatibleFlag(int(f1) | f2); }

#define LOO_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
LOO_DECL_CONSTEXPR inline LooFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) LOO_DECL_NOTHROW \
{ return LooFlags<Flags::enum_type>(f1) | f2; } \
LOO_DECL_CONSTEXPR inline LooFlags<Flags::enum_type> operator|(Flags::enum_type f1, LooFlags<Flags::enum_type> f2) LOO_DECL_NOTHROW \
{ return f2 | f1; } LOO_DECLARE_INCOMPATIBLE_FLAGS(Flags)


#else /* Q_NO_TYPESAFE_FLAGS */

#define LOO_DECLARE_FLAGS(Flags, Enum)\
typedef uint Flags;
#define LOO_DECLARE_OPERATORS_FOR_FLAGS(Flags)

#endif /* Q_NO_TYPESAFE_FLAGS */

}


#endif