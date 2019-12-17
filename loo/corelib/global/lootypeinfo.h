#include <LooCore/looglobal.h>
#ifndef LOOTYPEINFO_H
#define LOOTYPEINFO_H
namespace loo
{

	template <typename T>
	class LooTypeInfo
	{
	public:
		enum {
			isSpecialized = std::is_enum<T>::value, // don't require every enum to be marked manually
			isPointer = false,
			isIntegral = std::is_integral<T>::value,
			isComplex = !isIntegral && !std::is_enum<T>::value,
			isStatic = true,
			isRelocatable = std::is_enum<T>::value,
			isLarge = (sizeof (T) > sizeof (void*)),
			isDummy = false, //### TODO: remove
			sizeOf = sizeof (T)
		};
	};

	template<>
	class LooTypeInfo<void>
	{
	public:
		enum {
			isSpecialized = true,
			isPointer = false,
			isIntegral = false,
			isComplex = false,
			isStatic = false,
			isRelocatable = false,
			isLarge = false,
			isDummy = false,
			sizeOf = 0
		};
	};

	template <typename T>
	class LooTypeInfo<T*>
	{
	public:
		enum {
			isSpecialized = true,
			isPointer = true,
			isIntegral = false,
			isComplex = false,
			isStatic = false,
			isRelocatable = true,
			isLarge = false,
			isDummy = false,
			sizeOf = sizeof (T*)
		};
	};

	/*!
	\class LooTypeInfoQuery
	\inmodule QtCore
	\internal
	\brief LooTypeInfoQuery is used to query the values of a given QTypeInfo<T>

	We use it because there may be some QTypeInfo<T> specializations in user
	code that don't provide certain flags that we added after Qt 5.0. They are:
	\list
	  \li isRelocatable: defaults to !isStatic
	\endlist

	DO NOT specialize this class elsewhere.
	*/
	// apply defaults for a generic QTypeInfo<T> that didn't provide the new values
	template <typename T, typename = void>
	struct LooTypeInfoQuery : public LooTypeInfo<T>
	{
		enum { isRelocatable = !LooTypeInfo<T>::isStatic };
	};

	// if QTypeInfo<T>::isRelocatable exists, use it
	template <typename T>
	struct LooTypeInfoQuery<T, typename std::enable_if<LooTypeInfo<T>::isRelocatable || true>::type> : public QLooTypeInfo<T>
	{};

	/*!
		\class QTypeInfoMerger
		\inmodule QtCore
		\internal

		\brief QTypeInfoMerger merges the QTypeInfo flags of T1, T2... and presents them
		as a QTypeInfo<T> would do.

		Let's assume that we have a simple set of structs:

		\snippet code/src_corelib_global_qglobal.cpp 50

		To create a proper QTypeInfo specialization for A struct, we have to check
		all sub-components; B, C and D, then take the lowest common denominator and call
		LOO_DECLARE_TYPEINFO with the resulting flags. An easier and less fragile approach is to
		use QTypeInfoMerger, which does that automatically. So struct A would have
		the following QTypeInfo definition:

		\snippet code/src_corelib_global_qglobal.cpp 51
	*/
	template <class T, class T1, class T2 = T1, class T3 = T1, class T4 = T1>
	class LooTypeInfoMerger
	{
	public:
		enum {
			isSpecialized = true,
			isComplex = LooTypeInfoQuery<T1>::isComplex || LooTypeInfoQuery<T2>::isComplex
			|| LooTypeInfoQuery<T3>::isComplex || LooTypeInfoQuery<T4>::isComplex,
			isStatic = LooTypeInfoQuery<T1>::isStatic || LooTypeInfoQuery<T2>::isStatic
			|| LooTypeInfoQuery<T3>::isStatic || LooTypeInfoQuery<T4>::isStatic,
			isRelocatable = LooTypeInfoQuery<T1>::isRelocatable && LooTypeInfoQuery<T2>::isRelocatable
			&& LooTypeInfoQuery<T3>::isRelocatable && LooTypeInfoQuery<T4>::isRelocatable,
			isLarge = sizeof (T) > sizeof (void*),
			isPointer = false,
			isIntegral = false,
			isDummy = false,
			sizeOf = sizeof (T)
		};
	};

#define LOO_DECLARE_MOVABLE_CONTAINER(CONTAINER) \
	template <typename T> class CONTAINER; \
	template <typename T> \
	class LooTypeInfo< CONTAINER<T> > \
	{ \
	public: \
		enum { \
			isSpecialized = true, \
			isPointer = false, \
			isIntegral = false, \
			isComplex = true, \
			isRelocatable = true, \
			isStatic = false, \
			isLarge = (sizeof(CONTAINER<T>) > sizeof(void*)), \
			isDummy = false, \
			sizeOf = sizeof(CONTAINER<T>) \
		}; \
	}

	//LOO_DECLARE_MOVABLE_CONTAINER (QList);
	//LOO_DECLARE_MOVABLE_CONTAINER (QVector);
	//LOO_DECLARE_MOVABLE_CONTAINER (QQueue);
	//LOO_DECLARE_MOVABLE_CONTAINER (QStack);
	//LOO_DECLARE_MOVABLE_CONTAINER (QLinkedList);
	//LOO_DECLARE_MOVABLE_CONTAINER (QSet);

#undef LOO_DECLARE_MOVABLE_CONTAINER

	/* These cannot be movable before ### Qt 6, for BC reasons */
#define LOO_DECLARE_MOVABLE_CONTAINER(CONTAINER) \
	template <typename K, typename V> class CONTAINER; \
	template <typename K, typename V> \
	class LooTypeInfo< CONTAINER<K, V> > \
	{ \
	public: \
		enum { \
			isSpecialized = true, \
			isPointer = false, \
			isIntegral = false, \
			isComplex = true, \
			isStatic = true, \
			isRelocatable = true, \
			isLarge = (sizeof(CONTAINER<K, V>) > sizeof(void*)), \
			isDummy = false, \
			sizeOf = sizeof(CONTAINER<K, V>) \
		}; \
	}

	//LOO_DECLARE_MOVABLE_CONTAINER (QMap);
	//LOO_DECLARE_MOVABLE_CONTAINER (QMultiMap);
	//LOO_DECLARE_MOVABLE_CONTAINER (QHash);
	//LOO_DECLARE_MOVABLE_CONTAINER (QMultiHash);


#undef LOO_DECLARE_MOVABLE_CONTAINER

	/*
	   Specialize a specific type with:

		 LOO_DECLARE_TYPEINFO(type, flags);

	   where 'type' is the name of the type to specialize and 'flags' is
	   logically-OR'ed combination of the flags below.
	*/
	enum { /* TYPEINFO flags */
		LOO_COMPLEX_TYPE = 0,
		LOO_PRIMITIVE_TYPE = 0x1,
		LOO_STATIC_TYPE = 0,
		LOO_MOVABLE_TYPE = 0x2,               // ### Qt6: merge movable and relocatable once QList no longer depends on it
		LOO_DUMMY_TYPE = 0x4,
		LOO_RELOCATABLE_TYPE = 0x8
	};

#define LOO_DECLARE_TYPEINFO_BODY(TYPE, FLAGS) \
class LooTypeInfo<TYPE > \
{ \
public: \
    enum { \
        isSpecialized = true, \
        isComplex = (((FLAGS) & LOO_PRIMITIVE_TYPE) == 0), \
        isStatic = (((FLAGS) & (LOO_MOVABLE_TYPE | LOO_PRIMITIVE_TYPE)) == 0), \
        isRelocatable = !isStatic || ((FLAGS) & LOO_RELOCATABLE_TYPE), \
        isLarge = (sizeof(TYPE)>sizeof(void*)), \
        isPointer = false, \
        isIntegral = std::is_integral< TYPE >::value, \
        isDummy = (((FLAGS) & LOO_DUMMY_TYPE) != 0), \
        sizeOf = sizeof(TYPE) \
    }; \
    static inline const char *name() { return #TYPE; } \
}

#define LOO_DECLARE_TYPEINFO(TYPE, FLAGS) \
template<> \
LOO_DECLARE_TYPEINFO_BODY(TYPE, FLAGS)

	/* Specialize QTypeInfo for QFlags<T> */
	template<typename T> class LooFlags;
	template<typename T>
	LOO_DECLARE_TYPEINFO_BODY (LooFlags<T>, LOO_PRIMITIVE_TYPE);

}

/*
   Specialize a shared type with:

	 Q_DECLARE_SHARED(type)

   where 'type' is the name of the type to specialize.  NOTE: shared
   types must define a member-swap, and be defined in the same
   namespace as Qt for this to work.

   If the type was already released without Q_DECLARE_SHARED applied,
   _and_ without an explicit LOO_DECLARE_TYPEINFO(type, Q_MOVABLE_TYPE),
   then use Q_DECLARE_SHARED_NOT_MOVABLE_UNTIL_QT6(type) to mark the
   type shared (incl. swap()), without marking it movable (which
   would change the memory layout of QList, a BiC change.
*/

#define LOO_DECLARE_SHARED_IMPL(TYPE, FLAGS) \
LOO_DECLARE_TYPEINFO(TYPE, FLAGS); \
inline void swap(TYPE &value1, TYPE &value2) \
    LOO_DECL_NOEXCEPT_EXPR(noexcept(value1.swap(value2))) \
{ value1.swap(value2); }
#define LOO_DECLARE_SHARED(TYPE) LOO_DECLARE_SHARED_IMPL(TYPE, LOO_MOVABLE_TYPE)
//#define LOO_DECLARE_SHARED_NOT_MOVABLE_UNTIL_QT6(TYPE) \
//     LOO_DECLARE_SHARED_IMPL(TYPE, QT_VERSION >= LOO_VERSION_CHECK(6,0,0) ? LOO_MOVABLE_TYPE : LOO_RELOCATABLE_TYPE)


/*
   QTypeInfo primitive specializations
*/
LOO_DECLARE_TYPEINFO (bool, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (char, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (signed char, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (luchar, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (short, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (lushort, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (int, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (luint32, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (long, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (lulong, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (lint64, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (luint64, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (float, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (double, LOO_PRIMITIVE_TYPE);
#ifndef LOO_OS_DARWIN
LOO_DECLARE_TYPEINFO (long double, LOO_PRIMITIVE_TYPE);
#endif

LOO_DECLARE_TYPEINFO (char16_t, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (char32_t, LOO_PRIMITIVE_TYPE);
LOO_DECLARE_TYPEINFO (wchar_t, LOO_PRIMITIVE_TYPE);



#endif