#ifndef LOO_OBJECTDEFS_H
#define LOO_OBJECTDEFS_H


#include "looobjectdefs_impl.h"

namespace loo
{

#ifndef LOO_REFLECT_OUTPUT_REVISION
#define LOO_REFLECT_OUTPUT_REVISION 67
#endif

	// The following macros can be defined by tools that understand Qt
	// to have the information from the macro.
#ifndef LOO_ANNOTATE_CLASS
# ifndef LOO_COMPILER_VARIADIC_MACROS
#  define LOO_ANNOTATE_CLASS(type, x)
# else
#  define LOO_ANNOTATE_CLASS(type, ...)
# endif
#endif
#ifndef LOO_ANNOTATE_CLASS2
# define LOO_ANNOTATE_CLASS2(type, a1, a2)
#endif
#ifndef LOO_ANNOTATE_FUNCTION
# define LOO_ANNOTATE_FUNCTION(x)
#endif
#ifndef LOO_ANNOTATE_ACCESS_SPECIFIER
# define LOO_ANNOTATE_ACCESS_SPECIFIER(x)
#endif

// The following macros are our "extensions" to C++
// They are used, strictly speaking, only by the moc.

#ifndef LOO_REFLECT_RUN
#ifndef LOO_NO_META_MACROS
# if defined(LOO_NO_KEYWORDS)
#  define LOO_NO_EMIT
# else
#   ifndef LOO_NO_SIGNALS_SLOTS_KEYWORDS
#     define slots LOO_SLOTS
#     define signals LOO_SIGNALS
#   endif
# endif
# define LOO_SLOTS LOO_ANNOTATE_ACCESS_SPECIFIER(loo_slot)
# define LOO_SIGNALS public LOO_ANNOTATE_ACCESS_SPECIFIER(loo_signal)
# define LOO_PRIVATE_SLOT(d, signature) LOO_ANNOTATE_CLASS2(loo_private_slot, d, signature)
# define LOO_EMIT
#ifndef LOO_NO_EMIT
# define emit
#endif
#ifndef LOO_CLASSINFO
# define LOO_CLASSINFO(name, value)
#endif
#define LOO_PLUGIN_METADATA(x) LOO_ANNOTATE_CLASS(loo_plugin_metadata, x)
#define LOO_INTERFACES(x) LOO_ANNOTATE_CLASS(loo_interfaces, x)
#ifdef LOO_COMPILER_VARIADIC_MACROS
# define LOO_PROPERTY(...) LOO_ANNOTATE_CLASS(loo_property, __VA_ARGS__)
#else
# define LOO_PROPERTY(text) LOO_ANNOTATE_CLASS(loo_property, text)
#endif
#define LOO_PRIVATE_PROPERTY(d, text) LOO_ANNOTATE_CLASS2(loo_private_property, d, text)
#ifndef LOO_REVISION
# define LOO_REVISION(v)
#endif
#define LOO_OVERRIDE(text) LOO_ANNOTATE_CLASS(loo_override, text)
#define LOODOC_PROPERTY(text) LOO_ANNOTATE_CLASS(loo_qdoc_property, text)
#define LOO_ENUMS(x) LOO_ANNOTATE_CLASS(loo_enums, x)
#define LOO_FLAGS(x) LOO_ANNOTATE_CLASS(loo_enums, x)
#define LOO_ENUM_IMPL(ENUM) \
    friend LOO_DECL_CONSTEXPR const LooMetaObject *loo_getEnumMetaObject(ENUM) LOO_DECL_NOEXCEPT { return &staticMetaObject; } \
    friend LOO_DECL_CONSTEXPR const char *qt_getEnumName(ENUM) LOO_DECL_NOEXCEPT { return #ENUM; }
#define LOO_ENUM(x) LOO_ENUMS(x) LOO_ENUM_IMPL(x)
#define LOO_FLAG(x) LOO_FLAGS(x) LOO_ENUM_IMPL(x)
#define LOO_ENUM_NS_IMPL(ENUM) \
    inline LOO_DECL_CONSTEXPR const LooMetaObject *loo_getEnumMetaObject(ENUM) LOO_DECL_NOEXCEPT { return &staticMetaObject; } \
    inline LOO_DECL_CONSTEXPR const char *qt_getEnumName(ENUM) LOO_DECL_NOEXCEPT { return #ENUM; }
#define LOO_ENUM_NS(x) LOO_ENUMS(x) LOO_ENUM_NS_IMPL(x)
#define LOO_FLAG_NS(x) LOO_FLAGS(x) LOO_ENUM_NS_IMPL(x)
#define LOO_SCRIPTABLE LOO_ANNOTATE_FUNCTION(loo_scriptable)
#define LOO_INVOKABLE  LOO_ANNOTATE_FUNCTION(loo_invokable)
#define LOO_SIGNAL LOO_ANNOTATE_FUNCTION(loo_signal)
#define LOO_SLOT LOO_ANNOTATE_FUNCTION(loo_slot)
#endif // LOO_NO_META_MACROS

#define LOO_NO_TRANSLATION
#ifndef LOO_NO_TRANSLATION
// full set of tr functions
#  define LOO_TR_FUNCTIONS \
    static inline std::string tr(const char *s, const char *c = LOO_NULLPTR, int n = -1) \
        { return staticMetaObject.tr(s, c, n); } \
    LOO_DEPRECATED static inline std::string trUtf8(const char *s, const char *c = LOO_NULLPTR, int n = -1) \
        { return staticMetaObject.tr(s, c, n); }
#else
// inherit the ones from LooObject
# define LOO_TR_FUNCTIONS
#endif

#define LOO_OBJECT_CHECK  /* empty, unused since Qt 5.2 */

#if defined(LOO_CC_INTEL)
// Cannot redefine the visibility of a method in an exported class
# define LOO_DECL_HIDDEN_STATIC_METACALL
#else
# define LOO_DECL_HIDDEN_STATIC_METACALL LOO_DECL_HIDDEN
#endif

#if defined(LOO_CC_CLANG) && LOO_CC_CLANG >= 306
#  define LOO_OBJECT_NO_OVERRIDE_WARNING      LOO_WARNING_DISABLE_CLANG("-Winconsistent-missing-override")
#elif defined(LOO_CC_GNU) && !defined(LOO_CC_INTEL) && LOO_CC_GNU >= 501
#  define LOO_OBJECT_NO_OVERRIDE_WARNING      LOO_WARNING_DISABLE_GCC("-Wsuggest-override")
#else
#  define LOO_OBJECT_NO_OVERRIDE_WARNING
#endif

#if defined(LOO_CC_GNU) && !defined(LOO_CC_INTEL) && LOO_CC_GNU >= 600
#  define LOO_OBJECT_NO_ATTRIBUTES_WARNING    LOO_WARNING_DISABLE_GCC("-Wattributes")
#else
#  define LOO_OBJECT_NO_ATTRIBUTES_WARNING
#endif

/* qmake ignore LOO_OBJECT */
#define LOO_OBJECT \
public: \
    LOO_WARNING_PUSH \
    LOO_OBJECT_NO_OVERRIDE_WARNING \
    static const LooMetaObject staticMetaObject; \
    virtual const LooMetaObject *metaObject() const; \
    virtual void *loo_metacast(const char *); \
    virtual int loo_metacall(LooMetaObject::Call, int, void **); \
    LOO_TR_FUNCTIONS \
private: \
    LOO_OBJECT_NO_ATTRIBUTES_WARNING \
    LOO_DECL_HIDDEN_STATIC_METACALL static void loo_static_metacall(LooObject *, LooMetaObject::Call, int, void **); \
    LOO_WARNING_POP \
    struct LooPrivateSignal {}; \
    LOO_ANNOTATE_CLASS(loo_lobject, "")

/* qmake ignore LOO_OBJECT */
#define LOO_OBJECT_FAKE LOO_OBJECT LOO_ANNOTATE_CLASS(loo_fake, "")

#ifndef LOO_NO_META_MACROS
/* qmake ignore LOO_GADGET */
#define LOO_GADGET \
public: \
    static const LooMetaObject staticMetaObject; \
    void loo_check_for_LooGADGET_macro(); \
    typedef void LooGadgetHelper; \
private: \
    LOO_WARNING_PUSH \
    LOO_OBJECT_NO_ATTRIBUTES_WARNING \
    LOO_DECL_HIDDEN_STATIC_METACALL static void loo_static_metacall(LooObject *, LooMetaObject::Call, int, void **); \
    LOO_WARNING_POP \
    LOO_ANNOTATE_CLASS(loo_qgadget, "") \
    /*end*/

/* qmake ignore LOO_NAMESPACE */
#define LOO_NAMESPACE \
    extern const LooMetaObject staticMetaObject; \
    LOO_ANNOTATE_CLASS(loo_lnamespace, "") \
    /*end*/

#endif // LOO_NO_META_MACROS

#else // LOO_REFLECT_RUN
#define slots slots
#define signals signals
#define LOO_SLOTS LOO_SLOTS
#define LOO_SIGNALS LOO_SIGNALS
#define LOO_CLASSINFO(name, value) LOO_CLASSINFO(name, value)
#define LOO_INTERFACES(x) LOO_INTERFACES(x)
#define LOO_PROPERTY(text) LOO_PROPERTY(text)
#define LOO_PRIVATE_PROPERTY(d, text) LOO_PRIVATE_PROPERTY(d, text)
#define LOO_REVISION(v) LOO_REVISION(v)
#define LOO_OVERRIDE(text) LOO_OVERRIDE(text)
#define LOO_ENUMS(x) LOO_ENUMS(x)
#define LOO_FLAGS(x) LOO_FLAGS(x)
#define LOO_ENUM(x) LOO_ENUM(x)
#define LOO_FLAGS(x) LOO_FLAGS(x)
 /* qmake ignore LOO_OBJECT */
#define LOO_OBJECT LOO_OBJECT
 /* qmake ignore LOO_OBJECT */
#define LOO_OBJECT_FAKE LOO_OBJECT_FAKE
 /* qmake ignore LOO_GADGET */
#define LOO_GADGET LOO_GADGET
#define LOO_SCRIPTABLE LOO_SCRIPTABLE
#define LOO_INVOKABLE LOO_INVOKABLE
#define LOO_SIGNAL LOO_SIGNAL
#define LOO_SLOT LOO_SLOT
#endif //LOO_REFLECT_RUN

#ifdef LOO_CLANG_QDOC
#undef LOO_GADGET
#define LOO_GADGET
#endif

#ifndef LOO_NO_META_MACROS
// macro for onaming members
#ifdef METHOD
#undef METHOD
#endif
#ifdef SLOT
#undef SLOT
#endif
#ifdef SIGNAL
#undef SIGNAL
#endif
#endif // LOO_NO_META_MACROS

	LOO_CORE_EXPORT const char *lFlagLocation (const char *method);

#ifndef LOO_NO_META_MACROS
#ifndef LOO_NO_DEBUG
# define LLOCATION "\0" __FILE__ ":" LOO_STRINGIFY(__LINE__)
# ifndef LOO_NO_KEYWORDS
#  define METHOD(a)   lFlagLocation("0"#a LLOCATION)
# endif
# define SLOT(a)     lFlagLocation("1"#a LLOCATION)
# define SIGNAL(a)   lFlagLocation("2"#a LLOCATION)
#else
# ifndef LOO_NO_KEYWORDS
#  define METHOD(a)   "0"#a
# endif
# define SLOT(a)     "1"#a
# define SIGNAL(a)   "2"#a
#endif

#define LMETHOD_CODE  0                        // member type codes
#define LSLOT_CODE    1
#define LSIGNAL_CODE  2
#endif // LOO_NO_META_MACROS

#define LOO_ARG(type, data) LooArgument<type >(#type, data)
#define LOO_RETURN_ARG(type, data) LooReturnArgument<type >(#type, data)

	class LooObject;
	class LooMetaMethod;
	class LooMetaEnum;
	class LooMetaProperty;
	class LooMetaClassInfo;


	class LOO_CORE_EXPORT LooGenericArgument
	{
	public:
		inline LooGenericArgument (const char *aName = LOO_NULLPTR, const void *aData = LOO_NULLPTR)
			: _data (aData), _name (aName) {}
		inline void *data () const { return const_cast<void *>(_data); }
		inline const char *name () const { return _name; }

	private:
		const void *_data;
		const char *_name;
	};

	class LOO_CORE_EXPORT LooGenericReturnArgument : public LooGenericArgument
	{
	public:
		inline LooGenericReturnArgument (const char *aName = LOO_NULLPTR, void *aData = LOO_NULLPTR)
			: LooGenericArgument (aName, aData)
		{}
	};

	template <class T>
	class LooArgument : public LooGenericArgument
	{
	public:
		inline LooArgument (const char *aName, const T &aData)
			: LooGenericArgument (aName, static_cast<const void *>(&aData))
		{}
	};
	template <class T>
	class LooArgument<T &> : public LooGenericArgument
	{
	public:
		inline LooArgument (const char *aName, T &aData)
			: LooGenericArgument (aName, static_cast<const void *>(&aData))
		{}
	};


	template <typename T>
	class LooReturnArgument : public LooGenericReturnArgument
	{
	public:
		inline LooReturnArgument (const char *aName, T &aData)
			: LooGenericReturnArgument (aName, static_cast<void *>(&aData))
		{}
	};

	struct LOO_CORE_EXPORT LooMetaObject
	{
		class Connection;
		const char *className () const;
		const LooMetaObject *superClass () const;

		bool inherits (const LooMetaObject *metaObject) const LOO_DECL_NOEXCEPT;
		LooObject *cast (LooObject *obj) const;
		const LooObject *cast (const LooObject *obj) const;

#ifndef LOO_NO_TRANSLATION
		std::string tr (const char *s, const char *c, int n = -1) const;
#endif // LOO_NO_TRANSLATION

		int methodOffset () const;
		int enumeratorOffset () const;
		int propertyOffset () const;
		int classInfoOffset () const;

		int constructorCount () const;
		int methodCount () const;
		int enumeratorCount () const;
		int propertyCount () const;
		int classInfoCount () const;

		int indexOfConstructor (const char *constructor) const;
		int indexOfMethod (const char *method) const;
		int indexOfSignal (const char *signal) const;
		int indexOfSlot (const char *slot) const;
		int indexOfEnumerator (const char *name) const;
		int indexOfProperty (const char *name) const;
		int indexOfClassInfo (const char *name) const;

		LooMetaMethod constructor (int index) const;
		LooMetaMethod method (int index) const;
		LooMetaEnum enumerator (int index) const;
		LooMetaProperty property (int index) const;
		LooMetaClassInfo classInfo (int index) const;
		LooMetaProperty userProperty () const;

		static bool checkConnectArgs (const char *signal, const char *method);
		static bool checkConnectArgs (const LooMetaMethod &signal,
			const LooMetaMethod &method);
		static QByteArray normalizedSignature (const char *method);
		static QByteArray normalizedType (const char *type);

		// internal index-based connect
		static Connection connect (const LooObject *sender, int signal_index,
			const LooObject *receiver, int method_index,
			int type = 0, int *types = LOO_NULLPTR);
		// internal index-based disconnect
		static bool disconnect (const LooObject *sender, int signal_index,
			const LooObject *receiver, int method_index);
		static bool disconnectOne (const LooObject *sender, int signal_index,
			const LooObject *receiver, int method_index);
		// internal slot-name based connect
		static void connectSlotsByName (LooObject *o);

		// internal index-based signal activation
		static void activate (LooObject *sender, int signal_index, void **argv);
		static void activate (LooObject *sender, const LooMetaObject *, int local_signal_index, void **argv);
		static void activate (LooObject *sender, int signal_offset, int local_signal_index, void **argv);

		static bool invokeMethod (LooObject *obj, const char *member,
			loo::ConnectionType,
			LooGenericReturnArgument ret,
			LooGenericArgument val0 = LooGenericArgument (LOO_NULLPTR),
			LooGenericArgument val1 = LooGenericArgument (),
			LooGenericArgument val2 = LooGenericArgument (),
			LooGenericArgument val3 = LooGenericArgument (),
			LooGenericArgument val4 = LooGenericArgument (),
			LooGenericArgument val5 = LooGenericArgument (),
			LooGenericArgument val6 = LooGenericArgument (),
			LooGenericArgument val7 = LooGenericArgument (),
			LooGenericArgument val8 = LooGenericArgument (),
			LooGenericArgument val9 = LooGenericArgument ());

		static inline bool invokeMethod (LooObject *obj, const char *member,
			LooGenericReturnArgument ret,
			LooGenericArgument val0 = LooGenericArgument (LOO_NULLPTR),
			LooGenericArgument val1 = LooGenericArgument (),
			LooGenericArgument val2 = LooGenericArgument (),
			LooGenericArgument val3 = LooGenericArgument (),
			LooGenericArgument val4 = LooGenericArgument (),
			LooGenericArgument val5 = LooGenericArgument (),
			LooGenericArgument val6 = LooGenericArgument (),
			LooGenericArgument val7 = LooGenericArgument (),
			LooGenericArgument val8 = LooGenericArgument (),
			LooGenericArgument val9 = LooGenericArgument ())
		{
			return invokeMethod (obj, member, loo::AutoConnection, ret, val0, val1, val2, val3,
				val4, val5, val6, val7, val8, val9);
		}

		static inline bool invokeMethod (LooObject *obj, const char *member,
			loo::ConnectionType type,
			LooGenericArgument val0 = LooGenericArgument (LOO_NULLPTR),
			LooGenericArgument val1 = LooGenericArgument (),
			LooGenericArgument val2 = LooGenericArgument (),
			LooGenericArgument val3 = LooGenericArgument (),
			LooGenericArgument val4 = LooGenericArgument (),
			LooGenericArgument val5 = LooGenericArgument (),
			LooGenericArgument val6 = LooGenericArgument (),
			LooGenericArgument val7 = LooGenericArgument (),
			LooGenericArgument val8 = LooGenericArgument (),
			LooGenericArgument val9 = LooGenericArgument ())
		{
			return invokeMethod (obj, member, type, LooGenericReturnArgument (), val0, val1, val2,
				val3, val4, val5, val6, val7, val8, val9);
		}

		static inline bool invokeMethod (LooObject *obj, const char *member,
			LooGenericArgument val0 = LooGenericArgument (LOO_NULLPTR),
			LooGenericArgument val1 = LooGenericArgument (),
			LooGenericArgument val2 = LooGenericArgument (),
			LooGenericArgument val3 = LooGenericArgument (),
			LooGenericArgument val4 = LooGenericArgument (),
			LooGenericArgument val5 = LooGenericArgument (),
			LooGenericArgument val6 = LooGenericArgument (),
			LooGenericArgument val7 = LooGenericArgument (),
			LooGenericArgument val8 = LooGenericArgument (),
			LooGenericArgument val9 = LooGenericArgument ())
		{
			return invokeMethod (obj, member, loo::AutoConnection, LooGenericReturnArgument (), val0,
				val1, val2, val3, val4, val5, val6, val7, val8, val9);
		}

		LooObject *newInstance (LooGenericArgument val0 = LooGenericArgument (LOO_NULLPTR),
			LooGenericArgument val1 = LooGenericArgument (),
			LooGenericArgument val2 = LooGenericArgument (),
			LooGenericArgument val3 = LooGenericArgument (),
			LooGenericArgument val4 = LooGenericArgument (),
			LooGenericArgument val5 = LooGenericArgument (),
			LooGenericArgument val6 = LooGenericArgument (),
			LooGenericArgument val7 = LooGenericArgument (),
			LooGenericArgument val8 = LooGenericArgument (),
			LooGenericArgument val9 = LooGenericArgument ()) const;

		enum Call {
			InvokeMetaMethod,
			ReadProperty,
			WriteProperty,
			ResetProperty,
			QueryPropertyDesignable,
			QueryPropertyScriptable,
			QueryPropertyStored,
			QueryPropertyEditable,
			QueryPropertyUser,
			CreateInstance,
			IndexOfMethod,
			RegisterPropertyMetaType,
			RegisterMethodArgumentMetaType
		};

		int static_metacall (Call, int, void **) const;
		static int metacall (LooObject *, Call, int, void **);

		struct { // private data
			const LooMetaObject *superdata;
			const QByteArrayData *stringdata;
			const luint32 *data;
			typedef void (*StaticMetacallFunction)(LooObject *, LooMetaObject::Call, int, void **);
			StaticMetacallFunction static_metacall;
			const LooMetaObject * const *relatedMetaObjects;
			void *extradata; //reserved for future use
		} d;
	};

	class LOO_CORE_EXPORT LooMetaObject::Connection {
		void *d_ptr; //QObjectPrivate::Connection*
		explicit Connection (void *data) : d_ptr (data) {  }
		friend class LooObject;
		friend class QObjectPrivate;
		friend struct LooMetaObject;
		bool isConnected_helper () const;
	public:
		~Connection ();
		Connection ();
		Connection (const Connection &other);
		Connection &operator=(const Connection &other);

		typedef void *Connection::*RestrictedBool;
		operator RestrictedBool() const { return d_ptr && isConnected_helper () ? &Connection::d_ptr : LOO_NULLPTR; }
#endif

#ifdef LOO_COMPILER_RVALUE_REFS
		inline Connection (Connection &&o) : d_ptr (o.d_ptr) { o.d_ptr = LOO_NULLPTR; }
		inline Connection &operator=(Connection &&other)
		{
			qSwap (d_ptr, other.d_ptr); return *this;
		}
#endif
	};

	inline const LooMetaObject *LooMetaObject::superClass () const
	{
		return d.superdata;
	}

	namespace LooPrivate {
		/* Trait that tells is a the Object has a LOO_OBJECT macro */
		template <typename Object> struct HasLOO_OBJECT_Macro {
			template <typename T>
			static char test (int (T::*)(LooMetaObject::Call, int, void **));
			static int test (int (Object::*)(LooMetaObject::Call, int, void **));
			enum { Value = sizeof (test (&Object::qt_metacall)) == sizeof (int) };
		};
	}
}


#endif