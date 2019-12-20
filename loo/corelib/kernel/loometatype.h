#ifndef LOOMETATYPE_H
#define LOOMETATYPE_H
#include <LooCore/looglobal.h>

#include <new>
#include <list>
#include <map>


namespace loo
{

	template <typename T>
	struct LooMetaTypeId2;

	//typename <typename T>
	//inline LOO_DECL_CONSTEXPR int looMetaTypeId ();

	// F is a tuple: (LooMetaType::TypeName, LooMetaType::TypeNameID, RealType)
#define LOO_FOR_EACH_STATIC_PRIMITIVE_TYPE(F)\
    F(Void, 43, void) \
    F(Bool, 1, bool) \
    F(Int, 2, int) \
    F(UInt, 3, luint32) \
    F(LongLong, 4, lint64) \
    F(ULongLong, 5, luint64) \
    F(Double, 6, double) \
    F(Long, 32, long) \
    F(Short, 33, short) \
    F(Char, 34, char) \
    F(ULong, 35, lulong) \
    F(UShort, 36, lushort) \
    F(UChar, 37, luchar) \
    F(Float, 38, float) \
    F(SChar, 40, signed char) \
    F(Nullptr, 51, std::nullptr_t) \

#define LOO_FOR_EACH_STATIC_PRIMITIVE_POINTER(F)\
    F(VoidStar, 31, void*) \

#define LOO_FOR_EACH_STATIC_CORE_CLASS(F) //\
//    F(QChar, 7, QChar) \
//    F(std::string, 10, std::string) \
//    F(QStringList, 11, QStringList) \
//    F(QByteArray, 12, QByteArray) \
//    F(QBitArray, 13, QBitArray) \
//    F(QDate, 14, QDate) \
//    F(LOOime, 15, LOOime) \
//    F(QDateTime, 16, QDateTime) \
//    F(QUrl, 17, QUrl) \
//    F(QLocale, 18, QLocale) \
//    F(QRect, 19, QRect) \
//    F(QRectF, 20, QRectF) \
//    F(QSize, 21, QSize) \
//    F(QSizeF, 22, QSizeF) \
//    F(QLine, 23, QLine) \
//    F(QLineF, 24, QLineF) \
//    F(QPoint, 25, QPoint) \
//    F(QPointF, 26, QPointF) \
//    F(QRegExp, 27, QRegExp) \
//    F(QEasingCurve, 29, QEasingCurve) \
//    F(QUuid, 30, QUuid) \
//    F(LooVariant, 41, LooVariant) \
//    F(QModelIndex, 42, QModelIndex) \
//    F(QRegularExpression, 44, QRegularExpression) \
//    F(QJsonValue, 45, QJsonValue) \
//    F(QJsonObject, 46, QJsonObject) \
//    F(QJsonArray, 47, QJsonArray) \
//    F(QJsonDocument, 48, QJsonDocument) \
//    F(QPersistentModelIndex, 50, QPersistentModelIndex) \

#define LOO_FOR_EACH_STATIC_CORE_POINTER(F)//\
//    F(QObjectStar, 39, QObject*)

#define LOO_FOR_EACH_STATIC_CORE_TEMPLATE(F)//\
    //F(QVariantMap, 8, QVariantMap) \
    //F(QVariantList, 9, QVariantList) \
    //F(QVariantHash, 28, QVariantHash) \
    //F(QByteArrayList, 49, QByteArrayList) \

// ### FIXME kill that set
#define LOO_FOR_EACH_STATIC_HACKS_TYPE(F)\
    F(LooMetaTypeId2<lreal>::MetaType, -1, lreal)

// F is a tuple: (LooMetaType::TypeName, LooMetaType::TypeNameID, AliasingType, "RealType")
#define LOO_FOR_EACH_STATIC_ALIAS_TYPE(F)\
    F(ULong, -1, lulong, "unsigned long") \
    F(UInt, -1, luint32, "unsigned int") \
    F(UShort, -1, lushort, "unsigned short") \
    F(UChar, -1, luchar, "unsigned char") \
    F(LongLong, -1, lint32, "long long") \
    F(ULongLong, -1, luint32, "unsigned long long") \
    F(SChar, -1, signed char, "qint8") \
    F(UChar, -1, luchar, "quint8") \
    F(Short, -1, short, "qint16") \
    F(UShort, -1, lushort, "quint16") \
    F(Int, -1, int, "qint32") \
    F(UInt, -1, luint32, "quint32") \
    F(LongLong, -1, lint32, "qint64") \
    F(ULongLong, -1, luint32, "quint64") 

#define LOO_FOR_EACH_STATIC_TYPE(F)\
    LOO_FOR_EACH_STATIC_PRIMITIVE_TYPE(F)\
    LOO_FOR_EACH_STATIC_CORE_CLASS(F)\
    LOO_FOR_EACH_STATIC_CORE_TEMPLATE(F)

#define LOO_DEFINE_METATYPE_ID(TypeName, Id, Name) \
    TypeName = Id,

#define LOO_FOR_EACH_AUTOMATIC_TEMPLATE_1ARG(F) /*\
    F(std::vector) \
    F(std::vector) \
    F(QQueue) \
    F(QStack) \
    F(QSet) \
    F(QLinkedList)*/

#define LOO_FOR_EACH_AUTOMATIC_TEMPLATE_2ARG(F)/* \
    F(std::unordered_map, class) \
    F(std::unordered_map, class) \
    F(std::pair, struct)*/

#define LOO_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER(F) /*\
    F(QSharedPointer) \
    F(QWeakPointer) \
    F(QPointer)*/

	class QDataStream;
	class LooMetaTypeInterface;
	struct LooMetaObject;

	namespace LooPrivate
	{
		/*!
			This template is used for implicit conversion from type From to type To.
			\internal
		*/
		template<typename From, typename To>
		To convertImplicit (const From& from)
		{
			return from;
		}

		//todo debug
#if !defined(LOO_NO_DEBUG_STREAM)  && defined(HEHEHE)
		struct AbstractDebugStreamFunction
		{
			typedef void (*Stream)(const AbstractDebugStreamFunction *, QDebug&, const void *);
			typedef void (*Destroy)(AbstractDebugStreamFunction *);
			explicit AbstractDebugStreamFunction (Stream s = LOO_NULLPTR, Destroy d = LOO_NULLPTR)
				: stream (s), destroy (d) {}
			LOO_DISABLE_COPY (AbstractDebugStreamFunction)
				Stream stream;
			Destroy destroy;
		};

		template<typename T>
		struct BuiltInDebugStreamFunction : public AbstractDebugStreamFunction
		{
			BuiltInDebugStreamFunction ()
				: AbstractDebugStreamFunction (stream, destroy) {}
			static void stream (const AbstractDebugStreamFunction *, QDebug& dbg, const void *r)
			{
				const T *rhs = static_cast<const T *>(r);
				operator<<(dbg, *rhs);
			}

			static void destroy (AbstractDebugStreamFunction *_this)
			{
				delete static_cast<BuiltInDebugStreamFunction *>(_this);
			}
		};
#endif

		struct AbstractComparatorFunction
		{
			typedef bool (*LessThan)(const AbstractComparatorFunction *, const void *, const void *);
			typedef bool (*Equals)(const AbstractComparatorFunction *, const void *, const void *);
			typedef void (*Destroy)(AbstractComparatorFunction *);
			explicit AbstractComparatorFunction (LessThan lt = LOO_NULLPTR, Equals e = LOO_NULLPTR, Destroy d = LOO_NULLPTR)
				: lessThan (lt), equals (e), destroy (d) {}
			LOO_DISABLE_COPY (AbstractComparatorFunction)
				LessThan lessThan;
			Equals equals;
			Destroy destroy;
		};

		template<typename T>
		struct BuiltInComparatorFunction : public AbstractComparatorFunction
		{
			BuiltInComparatorFunction ()
				: AbstractComparatorFunction (lessThan, equals, destroy) {}
			static bool lessThan (const AbstractComparatorFunction *, const void *l, const void *r)
			{
				const T *lhs = static_cast<const T *>(l);
				const T *rhs = static_cast<const T *>(r);
				return *lhs < *rhs;
			}

			static bool equals (const AbstractComparatorFunction *, const void *l, const void *r)
			{
				const T *lhs = static_cast<const T *>(l);
				const T *rhs = static_cast<const T *>(r);
				return *lhs == *rhs;
			}

			static void destroy (AbstractComparatorFunction *_this)
			{
				delete static_cast<BuiltInComparatorFunction *>(_this);
			}
		};

		template<typename T>
		struct BuiltInEqualsComparatorFunction : public AbstractComparatorFunction
		{
			BuiltInEqualsComparatorFunction ()
				: AbstractComparatorFunction (LOO_NULLPTR, equals, destroy) {}
			static bool equals (const AbstractComparatorFunction *, const void *l, const void *r)
			{
				const T *lhs = static_cast<const T *>(l);
				const T *rhs = static_cast<const T *>(r);
				return *lhs == *rhs;
			}

			static void destroy (AbstractComparatorFunction *_this)
			{
				delete static_cast<BuiltInEqualsComparatorFunction *>(_this);
			}
		};

		struct AbstractConverterFunction
		{
			typedef bool (*Converter)(const AbstractConverterFunction *, const void *, void*);
			explicit AbstractConverterFunction (Converter c = LOO_NULLPTR)
				: convert (c) {}
			LOO_DISABLE_COPY (AbstractConverterFunction)
				Converter convert;
		};

		template<typename From, typename To>
		struct ConverterMemberFunction : public AbstractConverterFunction
		{
			explicit ConverterMemberFunction (To (From::*function)() const)
				: AbstractConverterFunction (convert),
				m_function (function) {}
			~ConverterMemberFunction ();
			static bool convert (const AbstractConverterFunction *_this, const void *in, void *out)
			{
				const From *f = static_cast<const From *>(in);
				To *t = static_cast<To *>(out);
				const ConverterMemberFunction *_typedThis =
					static_cast<const ConverterMemberFunction *>(_this);
				*t = (f->*_typedThis->m_function)();
				return true;
			}

			To (From::* const m_function)() const;
		};

		template<typename From, typename To>
		struct ConverterMemberFunctionOk : public AbstractConverterFunction
		{
			explicit ConverterMemberFunctionOk (To (From::*function)(bool *) const)
				: AbstractConverterFunction (convert),
				m_function (function) {}
			~ConverterMemberFunctionOk ();
			static bool convert (const AbstractConverterFunction *_this, const void *in, void *out)
			{
				const From *f = static_cast<const From *>(in);
				To *t = static_cast<To *>(out);
				bool ok = false;
				const ConverterMemberFunctionOk *_typedThis =
					static_cast<const ConverterMemberFunctionOk *>(_this);
				*t = (f->*_typedThis->m_function)(&ok);
				if (!ok)
					*t = To ();
				return ok;
			}

			To (From::* const m_function)(bool*) const;
		};

		template<typename From, typename To, typename UnaryFunction>
		struct ConverterFunctor : public AbstractConverterFunction
		{
			explicit ConverterFunctor (UnaryFunction function)
				: AbstractConverterFunction (convert),
				m_function (function) {}
			~ConverterFunctor ();
			static bool convert (const AbstractConverterFunction *_this, const void *in, void *out)
			{
				const From *f = static_cast<const From *>(in);
				To *t = static_cast<To *>(out);
				const ConverterFunctor *_typedThis =
					static_cast<const ConverterFunctor *>(_this);
				*t = _typedThis->m_function (*f);
				return true;
			}

			UnaryFunction m_function;
		};

		template<typename T, bool>
		struct ValueTypeIsMetaType;
		template<typename T, bool>
		struct AssociativeValueTypeIsMetaType;
		template<typename T, bool>
		struct IsMetaTypePair;
		template<typename, typename>
		struct MetaTypeSmartPointerHelper;


	}

	class LOO_CORE_EXPORT LooMetaType {
		enum ExtensionFlag {
			NoExtensionFlags,
			CreateEx = 0x1, DestroyEx = 0x2,
			ConstructEx = 0x4, DestructEx = 0x8,
			NameEx = 0x10, SizeEx = 0x20,
			CtorEx = 0x40, DtorEx = 0x80,
			FlagsEx = 0x100, MetaObjectEx = 0x200
		};
	public:

		// The code that actually gets compiled.
		enum Type {
			// these are merged with LooVariant
			LOO_FOR_EACH_STATIC_TYPE (LOO_DEFINE_METATYPE_ID)

			FirstCoreType = Bool,
			LastCoreType = Nullptr,

			LReal = sizeof (double) == sizeof (double) ? Double : Float,

			UnknownType = 0,
			User = 1024
		};

		enum TypeFlag {
			NeedsConstruction = 0x1,
			NeedsDestruction = 0x2,
			MovableType = 0x4,
			PointerToQObject = 0x8,
			IsEnumeration = 0x10,
			SharedPointerToQObject = 0x20,
			WeakPointerToQObject = 0x40,
			TrackingPointerToQObject = 0x80,
			WasDeclaredAsMetaType = 0x100,
			IsGadget = 0x200
		};
		LOO_DECLARE_FLAGS (TypeFlags, TypeFlag)

			typedef void (*Deleter)(void *);
		typedef void *(*Creator)(const void *);

		typedef void (*Destructor)(void *);
		typedef void *(*Constructor)(void *, const void *);

		typedef void (*SaveOperator)(QDataStream &, const void *);
		typedef void (*LoadOperator)(QDataStream &, void *);
#ifndef LOO_NO_DATASTREAM
		static void registerStreamOperators (const char *typeName, SaveOperator saveOp,
			LoadOperator loadOp);
		static void registerStreamOperators (int type, SaveOperator saveOp,
			LoadOperator loadOp);
#endif
		static int registerType (const char *typeName, Deleter deleter,
			Creator creator);
		static int registerType (const char *typeName, Deleter deleter,
			Creator creator,
			Destructor destructor,
			Constructor constructor,
			int size,
			LooMetaType::TypeFlags flags,
			const LooMetaObject *metaObject);
		static bool unregisterType (int type);
		static int registerNormalizedType (const std::string &normalizedTypeName, Deleter deleter,
			Creator creator,
			Destructor destructor,
			Constructor constructor,
			int size,
			LooMetaType::TypeFlags flags,
			const LooMetaObject *metaObject);
		static int registerNormalizedType (const std::string &normalizedTypeName, Destructor destructor,
			Constructor constructor,
			int size,
			LooMetaType::TypeFlags flags,
			const LooMetaObject *metaObject);
		static int registerTypedef (const char *typeName, int aliasId);
		static int registerNormalizedTypedef (const std::string &normalizedTypeName, int aliasId);
		static int type (const char *typeName);

		static int type (const std::string &typeName);
		static const char *typeName (int type);
		static int sizeOf (int type);
		static TypeFlags typeFlags (int type);
		static const LooMetaObject *metaObjectForType (int type);
		static bool isRegistered (int type);
		static void *create (int type, const void *copy = LOO_NULLPTR);

		static void destroy (int type, void *data);
		static void *construct (int type, void *where, const void *copy);
		static void destruct (int type, void *where);

#ifndef LOO_NO_DATASTREAM
		static bool save (QDataStream &stream, int type, const void *data);
		static bool load (QDataStream &stream, int type, void *data);
#endif

		explicit LooMetaType (const int type); // ### Qt6: drop const
		inline ~LooMetaType ();

		inline bool isValid () const;
		inline bool isRegistered () const;
		inline int sizeOf () const;
		inline TypeFlags flags () const;
		inline const LooMetaObject *metaObject () const;

		inline void *create (const void *copy = LOO_NULLPTR) const;
		inline void destroy (void *data) const;
		inline void *construct (void *where, const void *copy = LOO_NULLPTR) const;
		inline void destruct (void *data) const;

	public:
		template<typename T>
		static bool registerComparators ()
		{
			LOO_STATIC_ASSERT_X ((!LooMetaTypeId2<T>::IsBuiltIn),
				"LooMetaType::registerComparators: The type must be a custom type.");

			const int typeId = looMetaTypeId<T> ();
			static const LooPrivate::BuiltInComparatorFunction<T> f;
			return registerComparatorFunction (&f, typeId);
		}
		template<typename T>
		static bool registerEqualsComparator ()
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<T>::IsBuiltIn),
				"LooMetaType::registerEqualsComparator: The type must be a custom type.");
			const int typeId = looMetaTypeId<T> ();
			static const LooPrivate::BuiltInEqualsComparatorFunction<T> f;
			return registerComparatorFunction (&f, typeId);
		}

		template<typename T>
		static bool hasRegisteredComparators ()
		{
			return hasRegisteredComparators (looMetaTypeId<T> ());
		}
		static bool hasRegisteredComparators (int typeId);


#ifndef LOO_NO_DEBUG_STREAM
		template<typename T>
		static bool registerDebugStreamOperator ()
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<T>::IsBuiltIn),
				"LooMetaType::registerDebugStreamOperator: The type must be a custom type.");

			const int typeId = looMetaTypeId<T> ();
			static const LooPrivate::BuiltInDebugStreamFunction<T> f;
			return registerDebugStreamOperatorFunction (&f, typeId);
		}
		template<typename T>
		static bool hasRegisteredDebugStreamOperator ()
		{
			return hasRegisteredDebugStreamOperator (looMetaTypeId<T> ());
		}
		static bool hasRegisteredDebugStreamOperator (int typeId);
#endif

		// implicit conversion supported like double -> float
		template<typename From, typename To>
		static bool registerConverter ()
		{
			return registerConverter<From, To> (LooPrivate::convertImplicit<From, To>);
		}

#ifdef Q_QDOC
		template<typename MemberFunction, int>
		static bool registerConverter (MemberFunction function);
		template<typename MemberFunctionOk, char>
		static bool registerConverter (MemberFunctionOk function);
		template<typename UnaryFunction>
		static bool registerConverter (UnaryFunction function);
#else
		// member function as in "std::string QFont::toString() const"
		template<typename From, typename To>
		static bool registerConverter (To (From::*function)() const)
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<To>::IsBuiltIn || !LooMetaTypeId2<From>::IsBuiltIn),
				"LooMetaType::registerConverter: At least one of the types must be a custom type.");

			const int fromTypeId = looMetaTypeId<From> ();
			const int toTypeId = looMetaTypeId<To> ();
			static const LooPrivate::ConverterMemberFunction<From, To> f (function);
			return registerConverterFunction (&f, fromTypeId, toTypeId);
		}

		// member function as in "double std::string::toDouble(bool *ok = LOO_NULLPTR) const"
		template<typename From, typename To>
		static bool registerConverter (To (From::*function)(bool*) const)
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<To>::IsBuiltIn || !LooMetaTypeId2<From>::IsBuiltIn),
				"LooMetaType::registerConverter: At least one of the types must be a custom type.");

			const int fromTypeId = looMetaTypeId<From> ();
			const int toTypeId = looMetaTypeId<To> ();
			static const LooPrivate::ConverterMemberFunctionOk<From, To> f (function);
			return registerConverterFunction (&f, fromTypeId, toTypeId);
		}

		// functor or function pointer
		template<typename From, typename To, typename UnaryFunction>
		static bool registerConverter (UnaryFunction function)
		{
			LOO_STATIC_ASSERT_X ((!LooMetaTypeId2<To>::IsBuiltIn || !LooMetaTypeId2<From>::IsBuiltIn),
				"LooMetaType::registerConverter: At least one of the types must be a custom type.");

			const int fromTypeId = looMetaTypeId<From> ();
			const int toTypeId = looMetaTypeId<To> ();
			static const LooPrivate::ConverterFunctor<From, To, UnaryFunction> f (function);
			return registerConverterFunction (&f, fromTypeId, toTypeId);
		}
#endif

		static bool convert (const void *from, int fromTypeId, void *to, int toTypeId);
		static bool compare (const void *lhs, const void *rhs, int typeId, int* result);
		static bool equals (const void *lhs, const void *rhs, int typeId, int* result);
		//static bool debugStream (QDebug& dbg, const void *rhs, int typeId);

		template<typename From, typename To>
		static bool hasRegisteredConverterFunction ()
		{
			return hasRegisteredConverterFunction (looMetaTypeId<From> (), looMetaTypeId<To> ());
		}

		static bool hasRegisteredConverterFunction (int fromTypeId, int toTypeId);

	private:
		static LooMetaType typeInfo (const int type);
		inline LooMetaType (const ExtensionFlag extensionFlags, const LooMetaTypeInterface *info,
			Creator creator,
			Deleter deleter,
			SaveOperator saveOp,
			LoadOperator loadOp,
			Constructor constructor,
			Destructor destructor,
			luint32 sizeOf,
			luint32 theTypeFlags,
			int typeId,
			const LooMetaObject *metaObject);
		LooMetaType (const LooMetaType &other);
		LooMetaType &operator =(const LooMetaType &);
		inline bool isExtended (const ExtensionFlag flag) const { return m_extensionFlags & flag; }

		// Methods used for future binary compatible extensions
		void ctor (const LooMetaTypeInterface *info);
		void dtor ();
		luint32 sizeExtended () const;
		LooMetaType::TypeFlags flagsExtended () const;
		const LooMetaObject *metaObjectExtended () const;
		void *createExtended (const void *copy = LOO_NULLPTR) const;
		void destroyExtended (void *data) const;
		void *constructExtended (void *where, const void *copy = LOO_NULLPTR) const;
		void destructExtended (void *data) const;

		static bool registerComparatorFunction (const LooPrivate::AbstractComparatorFunction *f, int type);

		// ### Qt6: FIXME: Remove the special Q_CC_MSVC handling, it was introduced to maintain BC.
#if !defined(Q_NO_TEMPLATE_FRIENDS) && !defined(Q_CC_MSVC)
#ifndef Q_QDOC
		template<typename, bool> friend struct LooPrivate::ValueTypeIsMetaType;
		template<typename, typename> friend struct LooPrivate::ConverterMemberFunction;
		template<typename, typename> friend struct LooPrivate::ConverterMemberFunctionOk;
		template<typename, typename, typename> friend struct LooPrivate::ConverterFunctor;
		template<typename, bool> friend struct LooPrivate::AssociativeValueTypeIsMetaType;
		template<typename, bool> friend struct LooPrivate::IsMetaTypePair;
		template<typename, typename> friend struct LooPrivate::MetaTypeSmartPointerHelper;
#endif
#else
	public:
#endif
		static bool registerConverterFunction (const LooPrivate::AbstractConverterFunction *f, int from, int to);
		static void unregisterConverterFunction (int from, int to);
	private:

		Creator m_creator_unused;
		Deleter m_deleter_unused;
		SaveOperator m_saveOp;
		LoadOperator m_loadOp;
		Constructor m_constructor;
		Destructor m_destructor;
		void *m_extension; // space reserved for future use
		luint32 m_size;
		luint32 m_typeFlags;
		luint32 m_extensionFlags;
		int m_typeId;
		const LooMetaObject *m_metaObject;
	};


#undef LOO_DEFINE_METATYPE_ID

	LOO_DECLARE_OPERATORS_FOR_FLAGS (LooMetaType::TypeFlags)

#if 0
	//==============

		namespace LooPrivate {

		template<typename From, typename To>
		ConverterMemberFunction<From, To>::~ConverterMemberFunction ()
		{
			LooMetaType::unregisterConverterFunction (looMetaTypeId<From> (), looMetaTypeId<To> ());
		}
		template<typename From, typename To>
		ConverterMemberFunctionOk<From, To>::~ConverterMemberFunctionOk ()
		{
			LooMetaType::unregisterConverterFunction (looMetaTypeId<From> (), looMetaTypeId<To> ());
		}
		template<typename From, typename To, typename UnaryFunction>
		ConverterFunctor<From, To, UnaryFunction>::~ConverterFunctor ()
		{
			LooMetaType::unregisterConverterFunction (looMetaTypeId<From> (), looMetaTypeId<To> ());
		}

	}

#define LOO_METATYPE_PRIVATE_DECLARE_TYPEINFO(C, F)  \
    }                                               \
    LOO_DECLARE_TYPEINFO(LooMetaTypePrivate:: C, (F)); \
    namespace LooMetaTypePrivate {

	namespace LooMetaTypePrivate {
		template <typename T, bool Accepted = true>
		struct LooMetaTypeFunctionHelper {
			static void Destruct (void *t)
			{
				LOO_UNUSED (t) // Silence MSVC that warns for POD types.
					static_cast<T*>(t)->~T ();
			}

			static void *Construct (void *where, const void *t)
			{
				if (t)
					return new (where) T (*static_cast<const T*>(t));
				return new (where) T;
			}
#ifndef LOO_NO_DATASTREAM
			static void Save (QDataStream &stream, const void *t)
			{
				stream << *static_cast<const T*>(t);
			}

			static void Load (QDataStream &stream, void *t)
			{
				stream >> *static_cast<T*>(t);
			}
#endif // LOO_NO_DATASTREAM
		};

		template <typename T>
		struct LooMetaTypeFunctionHelper<T, /* Accepted */ false> {
			static void Destruct (void *) {}
			static void *Construct (void *, const void *) { return LOO_NULLPTR; }
#ifndef LOO_NO_DATASTREAM
			static void Save (QDataStream &, const void *) {}
			static void Load (QDataStream &, void *) {}
#endif // LOO_NO_DATASTREAM
		};
		template <>
		struct LooMetaTypeFunctionHelper<void, /* Accepted */ true>
			: public LooMetaTypeFunctionHelper<void, /* Accepted */ false>
		{};

		struct VariantData
		{
			VariantData (const int metaTypeId_,
				const void *data_,
				const luint32 flags_)
				: metaTypeId (metaTypeId_)
				, data (data_)
				, flags (flags_)
			{
			}
			VariantData (const VariantData &other)
				: metaTypeId (other.metaTypeId), data (other.data), flags (other.flags) {}
			const int metaTypeId;
			const void *data;
			const luint32 flags;
		private:
			// copy constructor allowed to be implicit to silence level 4 warning from MSVC
			VariantData &operator=(const VariantData &) = delete;
		};

		template<typename const_iterator>
		struct IteratorOwnerCommon
		{
			static void assign (void **ptr, const_iterator iterator)
			{
				*ptr = new const_iterator (iterator);
			}
			static void assign (void **ptr, void * const * src)
			{
				*ptr = new const_iterator (*static_cast<const_iterator*>(*src));
			}

			static void advance (void **iterator, int step)
			{
				const_iterator &it = *static_cast<const_iterator*>(*iterator);
				std::advance (it, step);
			}

			static void destroy (void **ptr)
			{
				delete static_cast<const_iterator*>(*ptr);
			}

			static bool equal (void * const *it, void * const *other)
			{
				return *static_cast<const_iterator*>(*it) == *static_cast<const_iterator*>(*other);
			}
		};

		template<typename const_iterator>
		struct IteratorOwner : IteratorOwnerCommon<const_iterator>
		{
			static const void *getData (void * const *iterator)
			{
				return &**static_cast<const_iterator*>(*iterator);
			}

			static const void *getData (const_iterator it)
			{
				return &*it;
			}
		};

		struct LOO_CORE_EXPORT VectorBoolElements
		{
			static const bool true_element;
			static const bool false_element;
		};

		template<>
		struct IteratorOwner<std::vector<bool>::const_iterator> : IteratorOwnerCommon<std::vector<bool>::const_iterator>
		{
		public:
			static const void *getData (void * const *iterator)
			{
				return **static_cast<std::vector<bool>::const_iterator*>(*iterator) ?
					&VectorBoolElements::true_element : &VectorBoolElements::false_element;
			}

			static const void *getData (const std::vector<bool>::const_iterator& it)
			{
				return *it ? &VectorBoolElements::true_element : &VectorBoolElements::false_element;
			}
		};

		template<typename value_type>
		struct IteratorOwner<const value_type*>
		{
		private:
			// We need to disable typed overloads of assign() and getData() if the value_type
			// is void* to avoid overloads conflicts. We do it by injecting unaccessible Dummy
			// type as part of the overload signature.
			struct Dummy {};
			typedef typename LooPrivate::if_<LooPrivate::is_same<value_type, void*>::value, Dummy, value_type>::type value_type_OR_Dummy;
		public:
			static void assign (void **ptr, const value_type_OR_Dummy *iterator)
			{
				*ptr = const_cast<value_type*>(iterator);
			}
			static void assign (void **ptr, void * const * src)
			{
				*ptr = static_cast<value_type*>(*src);
			}

			static void advance (void **iterator, int step)
			{
				value_type *it = static_cast<value_type*>(*iterator);
				std::advance (it, step);
				*iterator = it;
			}

			static void destroy (void **)
			{
			}

			static const void *getData (void * const *iterator)
			{
				return *iterator;
			}

			static const void *getData (const value_type_OR_Dummy *it)
			{
				return it;
			}

			static bool equal (void * const *it, void * const *other)
			{
				return static_cast<value_type*>(*it) == static_cast<value_type*>(*other);
			}
		};

		enum IteratorCapability
		{
			ForwardCapability = 1,
			BiDirectionalCapability = 2,
			RandomAccessCapability = 4
		};

		template<typename T, typename Category = typename std::iterator_traits<typename T::const_iterator>::iterator_category>
		struct CapabilitiesImpl;

		template<typename T>
		struct CapabilitiesImpl<T, std::forward_iterator_tag>
		{
			enum { IteratorCapabilities = ForwardCapability };
		};
		template<typename T>
		struct CapabilitiesImpl<T, std::bidirectional_iterator_tag>
		{
			enum { IteratorCapabilities = BiDirectionalCapability | ForwardCapability };
		};
		template<typename T>
		struct CapabilitiesImpl<T, std::random_access_iterator_tag>
		{
			enum { IteratorCapabilities = RandomAccessCapability | BiDirectionalCapability | ForwardCapability };
		};

		template<typename T>
		struct ContainerAPI : CapabilitiesImpl<T>
		{
			static int size (const T *t) { return int (std::distance (t->begin (), t->end ())); }
		};

		template<typename T>
		struct ContainerAPI<std::vector<T> > : CapabilitiesImpl<std::vector<T> >
		{
			static int size (const std::vector<T> *t) { return t->size (); }
		};

		template<typename T>
		struct ContainerAPI<std::vector<T> > : CapabilitiesImpl<std::vector<T> >
		{
			static int size (const std::vector<T> *t) { return t->size (); }
		};

		template<typename T>
		struct ContainerAPI<std::vector<T> > : CapabilitiesImpl<std::vector<T> >
		{
			static int size (const std::vector<T> *t) { return int (t->size ()); }
		};

		template<typename T>
		struct ContainerAPI<std::list<T> > : CapabilitiesImpl<std::list<T> >
		{
			static int size (const std::list<T> *t) { return int (t->size ()); }
		};

		class LooSequentialIterableImpl
		{
		public:
			const void * _iterable;
			void *_iterator;
			int _metaType_id;
			luint32 _metaType_flags;
			luint32 _iteratorCapabilities;
			typedef int (*sizeFunc)(const void *p);
			typedef const void * (*atFunc)(const void *p, int);
			typedef void (*moveIteratorFunc)(const void *p, void **);
			typedef void (*advanceFunc)(void **p, int);
			typedef VariantData (*getFunc)(void * const *p, int metaTypeId, luint32 flags);
			typedef void (*destroyIterFunc)(void **p);
			typedef bool (*equalIterFunc)(void * const *p, void * const *other);
			typedef void (*copyIterFunc)(void **, void * const *);

			sizeFunc _size;
			atFunc _at;
			moveIteratorFunc _moveToBegin;
			moveIteratorFunc _moveToEnd;
			advanceFunc _advance;
			getFunc _get;
			destroyIterFunc _destroyIter;
			equalIterFunc _equalIter;
			copyIterFunc _copyIter;

			template<class T>
			static int sizeImpl (const void *p)
			{
				return ContainerAPI<T>::size (static_cast<const T*>(p));
			}

			template<class T>
			static const void* atImpl (const void *p, int idx)
			{
				typename T::const_iterator i = static_cast<const T*>(p)->begin ();
				std::advance (i, idx);
				return IteratorOwner<typename T::const_iterator>::getData (i);
			}

			template<class T>
			static void moveToBeginImpl (const void *container, void **iterator)
			{
				IteratorOwner<typename T::const_iterator>::assign (iterator, static_cast<const T*>(container)->begin ());
			}

			template<class T>
			static void moveToEndImpl (const void *container, void **iterator)
			{
				IteratorOwner<typename T::const_iterator>::assign (iterator, static_cast<const T*>(container)->end ());
			}

			template<class T>
			static VariantData getImpl (void * const *iterator, int metaTypeId, luint32 flags)
			{
				return VariantData (metaTypeId, IteratorOwner<typename T::const_iterator>::getData (iterator), flags);
			}

		public:
			template<class T> LooSequentialIterableImpl (const T*p)
				: _iterable (p)
				, _iterator (LOO_NULLPTR)
				, _metaType_id (looMetaTypeId<typename T::value_type> ())
				, _metaType_flags (LooTypeInfo<typename T::value_type>::isPointer)
				, _iteratorCapabilities (ContainerAPI<T>::IteratorCapabilities)
				, _size (sizeImpl<T>)
				, _at (atImpl<T>)
				, _moveToBegin (moveToBeginImpl<T>)
				, _moveToEnd (moveToEndImpl<T>)
				, _advance (IteratorOwner<typename T::const_iterator>::advance)
				, _get (getImpl<T>)
				, _destroyIter (IteratorOwner<typename T::const_iterator>::destroy)
				, _equalIter (IteratorOwner<typename T::const_iterator>::equal)
				, _copyIter (IteratorOwner<typename T::const_iterator>::assign)
			{
			}

			LooSequentialIterableImpl ()
				: _iterable (LOO_NULLPTR)
				, _iterator (LOO_NULLPTR)
				, _metaType_id (LooMetaType::UnknownType)
				, _metaType_flags (0)
				, _iteratorCapabilities (0)
				, _size (LOO_NULLPTR)
				, _at (LOO_NULLPTR)
				, _moveToBegin (LOO_NULLPTR)
				, _moveToEnd (LOO_NULLPTR)
				, _advance (LOO_NULLPTR)
				, _get (LOO_NULLPTR)
				, _destroyIter (LOO_NULLPTR)
				, _equalIter (LOO_NULLPTR)
				, _copyIter (LOO_NULLPTR)
			{
			}

			inline void moveToBegin () { _moveToBegin (_iterable, &_iterator); }
			inline void moveToEnd () { _moveToEnd (_iterable, &_iterator); }
			inline bool equal (const LooSequentialIterableImpl&other) const { return _equalIter (&_iterator, &other._iterator); }
			inline LooSequentialIterableImpl &advance (int i) {
				LOO_ASSERT (i > 0 || _iteratorCapabilities & BiDirectionalCapability);
				_advance (&_iterator, i);
				return *this;
			}

			inline VariantData getCurrent () const { return _get (&_iterator, _metaType_id, _metaType_flags); }

			VariantData at (int idx) const
			{
				return VariantData (_metaType_id, _at (_iterable, idx), _metaType_flags);
			}

			int size () const { LOO_ASSERT (_iterable); return _size (_iterable); }

			inline void destroyIter () { _destroyIter (&_iterator); }

			void copy (const LooSequentialIterableImpl &other)
			{
				*this = other;
				_copyIter (&_iterator, &other._iterator);
			}
		};
		LOO_METATYPE_PRIVATE_DECLARE_TYPEINFO (LooSequentialIterableImpl, LOO_MOVABLE_TYPE)

			template<typename From>
		struct QSequentialIterableConvertFunctor
		{
			LooSequentialIterableImpl operator()(const From &f) const
			{
				return LooSequentialIterableImpl (&f);
			}
		};
	}

	namespace LooMetaTypePrivate {
		template<typename T, bool = std::is_same<typename T::const_iterator::value_type, typename T::mapped_type>::value>
		struct AssociativeContainerAccessor
		{
			static const typename T::key_type& getKey (const typename T::const_iterator &it)
			{
				return it.key ();
			}

			static const typename T::mapped_type& getValue (const typename T::const_iterator &it)
			{
				return it.value ();
			}
		};

		template<typename T, bool = std::is_same<typename T::const_iterator::value_type, std::pair<const typename T::key_type, typename T::mapped_type> >::value>
		struct StlStyleAssociativeContainerAccessor;

		template<typename T>
		struct StlStyleAssociativeContainerAccessor<T, true>
		{
			static const typename T::key_type& getKey (const typename T::const_iterator &it)
			{
				return it->first;
			}

			static const typename T::mapped_type& getValue (const typename T::const_iterator &it)
			{
				return it->second;
			}
		};

		template<typename T>
		struct AssociativeContainerAccessor<T, false> : public StlStyleAssociativeContainerAccessor<T>
		{
		};

		class QAssociativeIterableImpl
		{
		public:
			const void *_iterable;
			void *_iterator;
			int _metaType_id_key;
			luint32 _metaType_flags_key;
			int _metaType_id_value;
			luint32 _metaType_flags_value;
			typedef int (*sizeFunc)(const void *p);
			typedef void (*findFunc)(const void *container, const void *p, void **iterator);
			typedef void (*beginFunc)(const void *p, void **);
			typedef void (*advanceFunc)(void **p, int);
			typedef VariantData (*getFunc)(void * const *p, int metaTypeId, luint32 flags);
			typedef void (*destroyIterFunc)(void **p);
			typedef bool (*equalIterFunc)(void * const *p, void * const *other);
			typedef void (*copyIterFunc)(void **, void * const *);

			sizeFunc _size;
			findFunc _find;
			beginFunc _begin;
			beginFunc _end;
			advanceFunc _advance;
			getFunc _getKey;
			getFunc _getValue;
			destroyIterFunc _destroyIter;
			equalIterFunc _equalIter;
			copyIterFunc _copyIter;

			template<class T>
			static int sizeImpl (const void *p)
			{
				return int (std::distance (static_cast<const T*>(p)->begin (),
					static_cast<const T*>(p)->end ()));
			}

			template<class T>
			static void findImpl (const void *container, const void *p, void **iterator)
			{
				IteratorOwner<typename T::const_iterator>::assign (iterator,
					static_cast<const T*>(container)->find (*static_cast<const typename T::key_type*>(p)));
			}

			template<class T>
			static void advanceImpl (void **p, int step)
			{
				std::advance (*static_cast<typename T::const_iterator*>(*p), step);
			}

			template<class T>
			static void beginImpl (const void *container, void **iterator)
			{
				IteratorOwner<typename T::const_iterator>::assign (iterator, static_cast<const T*>(container)->begin ());
			}

			template<class T>
			static void endImpl (const void *container, void **iterator)
			{
				IteratorOwner<typename T::const_iterator>::assign (iterator, static_cast<const T*>(container)->end ());
			}

			template<class T>
			static VariantData getKeyImpl (void * const *iterator, int metaTypeId, luint32 flags)
			{
				return VariantData (metaTypeId, &AssociativeContainerAccessor<T>::getKey (*static_cast<typename T::const_iterator*>(*iterator)), flags);
			}

			template<class T>
			static VariantData getValueImpl (void * const *iterator, int metaTypeId, luint32 flags)
			{
				return VariantData (metaTypeId, &AssociativeContainerAccessor<T>::getValue (*static_cast<typename T::const_iterator*>(*iterator)), flags);
			}

		public:
			template<class T> QAssociativeIterableImpl (const T*p)
				: _iterable (p)
				, _iterator (LOO_NULLPTR)
				, _metaType_id_key (looMetaTypeId<typename T::key_type> ())
				, _metaType_flags_key (LooTypeInfo<typename T::key_type>::isPointer)
				, _metaType_id_value (looMetaTypeId<typename T::mapped_type> ())
				, _metaType_flags_value (LooTypeInfo<typename T::mapped_type>::isPointer)
				, _size (sizeImpl<T>)
				, _find (findImpl<T>)
				, _begin (beginImpl<T>)
				, _end (endImpl<T>)
				, _advance (advanceImpl<T>)
				, _getKey (getKeyImpl<T>)
				, _getValue (getValueImpl<T>)
				, _destroyIter (IteratorOwner<typename T::const_iterator>::destroy)
				, _equalIter (IteratorOwner<typename T::const_iterator>::equal)
				, _copyIter (IteratorOwner<typename T::const_iterator>::assign)
			{
			}

			QAssociativeIterableImpl ()
				: _iterable (LOO_NULLPTR)
				, _iterator (LOO_NULLPTR)
				, _metaType_id_key (LooMetaType::UnknownType)
				, _metaType_flags_key (0)
				, _metaType_id_value (LooMetaType::UnknownType)
				, _metaType_flags_value (0)
				, _size (LOO_NULLPTR)
				, _find (LOO_NULLPTR)
				, _begin (LOO_NULLPTR)
				, _end (LOO_NULLPTR)
				, _advance (LOO_NULLPTR)
				, _getKey (LOO_NULLPTR)
				, _getValue (LOO_NULLPTR)
				, _destroyIter (LOO_NULLPTR)
				, _equalIter (LOO_NULLPTR)
				, _copyIter (LOO_NULLPTR)
			{
			}

			inline void begin () { _begin (_iterable, &_iterator); }
			inline void end () { _end (_iterable, &_iterator); }
			inline bool equal (const QAssociativeIterableImpl&other) const { return _equalIter (&_iterator, &other._iterator); }
			inline QAssociativeIterableImpl &advance (int i) { _advance (&_iterator, i); return *this; }

			inline void destroyIter () { _destroyIter (&_iterator); }

			inline VariantData getCurrentKey () const { return _getKey (&_iterator, _metaType_id_key, _metaType_flags_key); }
			inline VariantData getCurrentValue () const { return _getValue (&_iterator, _metaType_id_value, _metaType_flags_value); }

			inline void find (const VariantData &key)
			{
				_find (_iterable, key.data, &_iterator);
			}

			int size () const { LOO_ASSERT (_iterable); return _size (_iterable); }

			void copy (const QAssociativeIterableImpl &other)
			{
				*this = other;
				_copyIter (&_iterator, &other._iterator);
			}
		};
		LOO_METATYPE_PRIVATE_DECLARE_TYPEINFO (QAssociativeIterableImpl, LOO_MOVABLE_TYPE)

			template<typename From>
		struct QAssociativeIterableConvertFunctor
		{
			QAssociativeIterableImpl operator()(const From& f) const
			{
				return QAssociativeIterableImpl (&f);
			}
		};

		class LooPairVariantInterfaceImpl
		{
			const void *_pair;
			int _metaType_id_first;
			luint32 _metaType_flags_first;
			int _metaType_id_second;
			luint32 _metaType_flags_second;

			typedef VariantData (*getFunc)(const void * const *p, int metaTypeId, luint32 flags);

			getFunc _getFirst;
			getFunc _getSecond;

			template<class T>
			static VariantData getFirstImpl (const void * const *pair, int metaTypeId, luint32 flags)
			{
				return VariantData (metaTypeId, &static_cast<const T*>(*pair)->first, flags);
			}
			template<class T>
			static VariantData getSecondImpl (const void * const *pair, int metaTypeId, luint32 flags)
			{
				return VariantData (metaTypeId, &static_cast<const T*>(*pair)->second, flags);
			}

		public:
			template<class T> LooPairVariantInterfaceImpl (const T*p)
				: _pair (p)
				, _metaType_id_first (looMetaTypeId<typename T::first_type> ())
				, _metaType_flags_first (LooTypeInfo<typename T::first_type>::isPointer)
				, _metaType_id_second (looMetaTypeId<typename T::second_type> ())
				, _metaType_flags_second (LooTypeInfo<typename T::second_type>::isPointer)
				, _getFirst (getFirstImpl<T>)
				, _getSecond (getSecondImpl<T>)
			{
			}

			LooPairVariantInterfaceImpl ()
				: _pair (LOO_NULLPTR)
				, _metaType_id_first (LooMetaType::UnknownType)
				, _metaType_flags_first (0)
				, _metaType_id_second (LooMetaType::UnknownType)
				, _metaType_flags_second (0)
				, _getFirst (LOO_NULLPTR)
				, _getSecond (LOO_NULLPTR)
			{
			}

			inline VariantData first () const { return _getFirst (&_pair, _metaType_id_first, _metaType_flags_first); }
			inline VariantData second () const { return _getSecond (&_pair, _metaType_id_second, _metaType_flags_second); }
		};
		LOO_METATYPE_PRIVATE_DECLARE_TYPEINFO (LooPairVariantInterfaceImpl, LOO_MOVABLE_TYPE)

			template<typename From>
		struct QPairVariantInterfaceConvertFunctor;

		template<typename T, typename U>
		struct QPairVariantInterfaceConvertFunctor<std::pair<T, U> >
		{
			LooPairVariantInterfaceImpl operator()(const std::pair<T, U>& f) const
			{
				return LooPairVariantInterfaceImpl (&f);
			}
		};

		template<typename T, typename U>
		struct QPairVariantInterfaceConvertFunctor<std::pair<T, U> >
		{
			LooPairVariantInterfaceImpl operator()(const std::pair<T, U>& f) const
			{
				return LooPairVariantInterfaceImpl (&f);
			}
		};

	}

	class QObject;
	class QWidget;

#define LOO_FORWARD_DECLARE_SHARED_POINTER_TYPES_ITER(Name) \
    template <class T> class Name; \

	LOO_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER (LOO_FORWARD_DECLARE_SHARED_POINTER_TYPES_ITER)

		namespace LooPrivate
	{
		template<typename T>
		struct IsPointerToTypeDerivedFromQObject
		{
			enum { Value = false };
		};

		// Specialize to avoid sizeof(void) warning
		template<>
		struct IsPointerToTypeDerivedFromQObject<void*>
		{
			enum { Value = false };
		};
		template<>
		struct IsPointerToTypeDerivedFromQObject<const void*>
		{
			enum { Value = false };
		};
		template<>
		struct IsPointerToTypeDerivedFromQObject<QObject*>
		{
			enum { Value = true };
		};

		template<typename T>
		struct IsPointerToTypeDerivedFromQObject<T*>
		{
			typedef qint8 yes_type;
			typedef qint64 no_type;

#ifndef LOO_NO_QOBJECT
			static yes_type checkType (QObject*);
#endif
			static no_type checkType (...);
			Q_STATIC_ASSERT_X (sizeof (T), "Type argument of LOO_DECLARE_METATYPE(T*) must be fully defined");
			enum { Value = sizeof (checkType (static_cast<T*>(LOO_NULLPTR))) == sizeof (yes_type) };
		};

		template<typename T, typename Enable = void>
		struct IsGadgetHelper { enum { Value = false }; };

		template<typename T>
		struct IsGadgetHelper<T, typename T::QtGadgetHelper>
		{
			template <typename X>
			static char checkType (void (X::*)());
			static void *checkType (void (T::*)());
			enum { Value = sizeof (checkType (&T::qt_check_for_QGADGET_macro)) == sizeof (void *) };
		};


		LOO_WARNING_PUSH
			// In C++03 mode, clang consider local or unnamed type and throw a warning instead of ignoring them
			LOO_WARNING_DISABLE_CLANG ("-Wunnamed-type-template-args")
			LOO_WARNING_DISABLE_CLANG ("-Wlocal-type-template-args")
			template<typename T> char qt_getEnumMetaObject (const T&);

		template<typename T>
		struct IsQEnumHelper {
			static const T &declval ();
			// If the type was declared with Q_ENUM, the friend qt_getEnumMetaObject() declared in the
			// Q_ENUM macro will be chosen by ADL, and the return type will be LooMetaObject*.
			// Otherwise the chosen overload will be the catch all template function
			// qt_getEnumMetaObject(T) which returns 'char'
			enum { Value = sizeof (qt_getEnumMetaObject (declval ())) == sizeof (LooMetaObject*) };
		};
		template<> struct IsQEnumHelper<void> { enum { Value = false }; };
		LOO_WARNING_POP

			template<typename T, typename Enable = void>
		struct MetaObjectForType
		{
			static inline const LooMetaObject *value () { return LOO_NULLPTR; }
		};
		template<>
		struct MetaObjectForType<void>
		{
			static inline const LooMetaObject *value () { return LOO_NULLPTR; }
		};
		template<typename T>
		struct MetaObjectForType<T*, typename std::enable_if<IsPointerToTypeDerivedFromQObject<T*>::Value>::Type>
		{
			static inline const LooMetaObject *value () { return &T::staticMetaObject; }
		};
		template<typename T>
		struct MetaObjectForType<T, typename std::enable_if<IsGadgetHelper<T>::Value>::Type>
		{
			static inline const LooMetaObject *value () { return &T::staticMetaObject; }
		};
		template<typename T>
		struct MetaObjectForType<T, typename std::enable_if<IsQEnumHelper<T>::Value>::Type >
		{
			static inline const LooMetaObject *value () { return qt_getEnumMetaObject (T ()); }
		};

		template<typename T>
		struct IsSharedPointerToTypeDerivedFromQObject
		{
			enum { Value = false };
		};

		template<typename T>
		struct IsSharedPointerToTypeDerivedFromQObject<std::shared_ptr<T> > : IsPointerToTypeDerivedFromQObject<T*>
		{
		};

		template<typename T>
		struct IsWeakPointerToTypeDerivedFromQObject
		{
			enum { Value = false };
		};

		template<typename T>
		struct IsWeakPointerToTypeDerivedFromQObject<QWeakPointer<T> > : IsPointerToTypeDerivedFromQObject<T*>
		{
		};

		template<typename T>
		struct IsTrackingPointerToTypeDerivedFromQObject
		{
			enum { Value = false };
		};

		template<typename T>
		struct IsTrackingPointerToTypeDerivedFromQObject<QPointer<T> >
		{
			enum { Value = true };
		};

		template<typename T>
		struct IsSequentialContainer
		{
			enum { Value = false };
		};

		template<typename T>
		struct IsAssociativeContainer
		{
			enum { Value = false };
		};

		template<typename T, bool = LooPrivate::IsSequentialContainer<T>::Value>
		struct SequentialContainerConverterHelper
		{
			static bool registerConverter (int)
			{
				return false;
			}
		};

		template<typename T, bool = LooMetaTypeId2<typename T::value_type>::Defined>
		struct ValueTypeIsMetaType
		{
			static bool registerConverter (int)
			{
				return false;
			}
		};

		template<typename T>
		struct SequentialContainerConverterHelper<T, true> : ValueTypeIsMetaType<T>
		{
		};

		template<typename T, bool = LooPrivate::IsAssociativeContainer<T>::Value>
		struct AssociativeContainerConverterHelper
		{
			static bool registerConverter (int)
			{
				return false;
			}
		};

		template<typename T, bool = LooMetaTypeId2<typename T::mapped_type>::Defined>
		struct AssociativeValueTypeIsMetaType
		{
			static bool registerConverter (int)
			{
				return false;
			}
		};

		template<typename T, bool = LooMetaTypeId2<typename T::key_type>::Defined>
		struct KeyAndValueTypeIsMetaType
		{
			static bool registerConverter (int)
			{
				return false;
			}
		};

		template<typename T>
		struct KeyAndValueTypeIsMetaType<T, true> : AssociativeValueTypeIsMetaType<T>
		{
		};

		template<typename T>
		struct AssociativeContainerConverterHelper<T, true> : KeyAndValueTypeIsMetaType<T>
		{
		};

		template<typename T, bool = LooMetaTypeId2<typename T::first_type>::Defined
			&& LooMetaTypeId2<typename T::second_type>::Defined>
			struct IsMetaTypePair
		{
			static bool registerConverter (int)
			{
				return false;
			}
		};

		template<typename T>
		struct IsMetaTypePair<T, true>
		{
			inline static bool registerConverter (int id);
		};

		template<typename T>
		struct IsPair
		{
			static bool registerConverter (int)
			{
				return false;
			}
		};
		template<typename T, typename U>
		struct IsPair<std::pair<T, U> > : IsMetaTypePair<std::pair<T, U> > {};
		template<typename T, typename U>
		struct IsPair<std::pair<T, U> > : IsMetaTypePair<std::pair<T, U> > {};

		template<typename T>
		struct MetaTypePairHelper : IsPair<T> {};

		template<typename T, typename = void>
		struct MetaTypeSmartPointerHelper
		{
			static bool registerConverter (int) { return false; }
		};

		LOO_CORE_EXPORT bool isBuiltinType (const QByteArray &type);
	} // namespace LooPrivate

	template <typename T, int =
		LooPrivate::IsPointerToTypeDerivedFromQObject<T>::Value ? LooMetaType::PointerToQObject :
		LooPrivate::IsGadgetHelper<T>::Value ? LooMetaType::IsGadget :
		LooPrivate::IsQEnumHelper<T>::Value ? LooMetaType::IsEnumeration : 0>
		struct QMetaTypeIdQObject
	{
		enum {
			Defined = 0
		};
	};

	template <typename T>
	struct QMetaTypeId : public QMetaTypeIdQObject<T>
	{
	};

	template <typename T>
	struct LooMetaTypeId2
	{
		enum { Defined = QMetaTypeId<T>::Defined, IsBuiltIn = false };
		static inline LOO_DECL_CONSTEXPR int qt_metatype_id () { return QMetaTypeId<T>::qt_metatype_id (); }
	};

	template <typename T>
	struct LooMetaTypeId2<const T&> : LooMetaTypeId2<T> {};

	template <typename T>
	struct LooMetaTypeId2<T&> { enum { Defined = false }; };

	namespace LooPrivate {
		template <typename T, bool Defined = LooMetaTypeId2<T>::Defined>
		struct QMetaTypeIdHelper {
			static inline LOO_DECL_CONSTEXPR int qt_metatype_id ()
			{
				return LooMetaTypeId2<T>::qt_metatype_id ();
			}
		};
		template <typename T> struct QMetaTypeIdHelper<T, false> {
			static inline LOO_DECL_CONSTEXPR int qt_metatype_id ()
			{
				return -1;
			}
		};

#ifndef Q_COMPILER_VARIADIC_TEMPLATES
		// Function pointers don't derive from QObject
		template <class Result> struct IsPointerToTypeDerivedFromQObject<Result (*)()> { enum { Value = false }; };
		template <class Result, class Arg0> struct IsPointerToTypeDerivedFromQObject<Result (*)(Arg0)> { enum { Value = false }; };
		template <class Result, class Arg0, class Arg1> struct IsPointerToTypeDerivedFromQObject<Result (*)(Arg0, Arg1)> { enum { Value = false }; };
		template <class Result, class Arg0, class Arg1, class Arg2> struct IsPointerToTypeDerivedFromQObject<Result (*)(Arg0, Arg1, Arg2)> { enum { Value = false }; };
#else
		template <typename Result, typename... Args>
		struct IsPointerToTypeDerivedFromQObject<Result (*)(Args...)> { enum { Value = false }; };
#endif

		template<typename T>
		struct QMetaTypeTypeFlags
		{
			enum {
				Flags = (LOOypeInfoQuery<T>::isRelocatable ? LooMetaType::MovableType : 0)
				| (LooTypeInfo<T>::isComplex ? LooMetaType::NeedsConstruction : 0)
				| (LooTypeInfo<T>::isComplex ? LooMetaType::NeedsDestruction : 0)
				| (IsPointerToTypeDerivedFromQObject<T>::Value ? LooMetaType::PointerToQObject : 0)
				| (IsSharedPointerToTypeDerivedFromQObject<T>::Value ? LooMetaType::SharedPointerToQObject : 0)
				| (IsWeakPointerToTypeDerivedFromQObject<T>::Value ? LooMetaType::WeakPointerToQObject : 0)
				| (IsTrackingPointerToTypeDerivedFromQObject<T>::Value ? LooMetaType::TrackingPointerToQObject : 0)
				| (Q_IS_ENUM (T) ? LooMetaType::IsEnumeration : 0)
				| (IsGadgetHelper<T>::Value ? LooMetaType::IsGadget : 0)
			};
		};

		template<typename T, bool defined>
		struct MetaTypeDefinedHelper
		{
			enum DefinedType { Defined = defined };
		};

		template<typename SmartPointer>
		struct QSmartPointerConvertFunctor
		{
			QObject* operator()(const SmartPointer &p) const
			{
				return p.operator->();
			}
		};

		template<typename T>
		struct QSmartPointerConvertFunctor<QWeakPointer<T> >
		{
			QObject* operator()(const QWeakPointer<T> &p) const
			{
				return p.data ();
			}
		};
	}

	template <typename T>
	int qRegisterNormalizedMetaType (const LOO_PREPEND_NAMESPACE (QByteArray) &normalizedTypeName
#ifndef Q_QDOC
		, T * dummy = 0
		, typename LooPrivate::MetaTypeDefinedHelper<T, LooMetaTypeId2<T>::Defined && !LooMetaTypeId2<T>::IsBuiltIn>::DefinedType defined = LooPrivate::MetaTypeDefinedHelper<T, LooMetaTypeId2<T>::Defined && !LooMetaTypeId2<T>::IsBuiltIn>::Defined
#endif
	)
	{
#ifndef LOO_NO_QOBJECT
		Q_ASSERT_X (normalizedTypeName == LooMetaObject::normalizedType (normalizedTypeName.constData ()), "qRegisterNormalizedMetaType", "qRegisterNormalizedMetaType was called with a not normalized type name, please call qRegisterMetaType instead.");
#endif
		const int typedefOf = dummy ? -1 : LooPrivate::QMetaTypeIdHelper<T>::qt_metatype_id ();
		if (typedefOf != -1)
			return LooMetaType::registerNormalizedTypedef (normalizedTypeName, typedefOf);

		LooMetaType::TypeFlags flags (LooPrivate::QMetaTypeTypeFlags<T>::Flags);

		if (defined)
			flags |= LooMetaType::WasDeclaredAsMetaType;

		const int id = LooMetaType::registerNormalizedType (normalizedTypeName,
			LooMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Destruct,
			LooMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Construct,
			int (sizeof (T)),
			flags,
			LooPrivate::MetaObjectForType<T>::value ());

		if (id > 0) {
			LooPrivate::SequentialContainerConverterHelper<T>::registerConverter (id);
			LooPrivate::AssociativeContainerConverterHelper<T>::registerConverter (id);
			LooPrivate::MetaTypePairHelper<T>::registerConverter (id);
			LooPrivate::MetaTypeSmartPointerHelper<T>::registerConverter (id);
		}

		return id;
	}

	template <typename T>
	int qRegisterMetaType (const char *typeName
#ifndef Q_QDOC
		, T * dummy = LOO_NULLPTR
		, typename LooPrivate::MetaTypeDefinedHelper<T, LooMetaTypeId2<T>::Defined && !LooMetaTypeId2<T>::IsBuiltIn>::DefinedType defined = LooPrivate::MetaTypeDefinedHelper<T, LooMetaTypeId2<T>::Defined && !LooMetaTypeId2<T>::IsBuiltIn>::Defined
#endif
	)
	{
#ifdef LOO_NO_QOBJECT
		LOO_PREPEND_NAMESPACE (QByteArray) normalizedTypeName = typeName;
#else
		LOO_PREPEND_NAMESPACE (QByteArray) normalizedTypeName = LooMetaObject::normalizedType (typeName);
#endif
		return qRegisterNormalizedMetaType<T> (normalizedTypeName, dummy, defined);
	}

#ifndef LOO_NO_DATASTREAM
	template <typename T>
	void qRegisterMetaTypeStreamOperators (const char *typeName
#ifndef Q_QDOC
		, T * /* dummy */ = LOO_NULLPTR
#endif
	)
	{
		qRegisterMetaType<T> (typeName);
		LooMetaType::registerStreamOperators (typeName, LooMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Save,
			LooMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Load);
	}
#endif // LOO_NO_DATASTREAM

	template <typename T>
	inline LOO_DECL_CONSTEXPR int looMetaTypeId ()
	{
		Q_STATIC_ASSERT_X (LooMetaTypeId2<T>::Defined, "Type is not registered, please use the LOO_DECLARE_METATYPE macro to make it known to Qt's meta-object system");
		return LooMetaTypeId2<T>::qt_metatype_id ();
	}

	template <typename T>
	inline LOO_DECL_CONSTEXPR int qRegisterMetaType ()
	{
		return looMetaTypeId<T> ();
	}

#ifndef LOO_NO_QOBJECT
	template <typename T>
	struct QMetaTypeIdQObject<T*, LooMetaType::PointerToQObject>
	{
		enum {
			Defined = 1
		};

		static int qt_metatype_id ()
		{
			static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER (0);
			if (const int id = metatype_id.loadAcquire ())
				return id;
			const char * const cName = T::staticMetaObject.className ();
			QByteArray typeName;
			typeName.reserve (int (strlen (cName)) + 1);
			typeName.append (cName).append ('*');
			const int newId = qRegisterNormalizedMetaType<T*> (
				typeName,
				reinterpret_cast<T**>(quintptr (-1)));
			metatype_id.storeRelease (newId);
			return newId;
		}
	};

	template <typename T>
	struct QMetaTypeIdQObject<T, LooMetaType::IsGadget>
	{
		enum {
			Defined = LooPrivate::is_default_constructible<T>::value
		};

		static int qt_metatype_id ()
		{
			static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER (0);
			if (const int id = metatype_id.loadAcquire ())
				return id;
			const char * const cName = T::staticMetaObject.className ();
			const int newId = qRegisterNormalizedMetaType<T> (
				cName,
				reinterpret_cast<T*>(quintptr (-1)));
			metatype_id.storeRelease (newId);
			return newId;
		}
	};

	template <typename T>
	struct QMetaTypeIdQObject<T, LooMetaType::IsEnumeration>
	{
		enum {
			Defined = 1
		};

		static int qt_metatype_id ()
		{
			static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER (0);
			if (const int id = metatype_id.loadAcquire ())
				return id;
			const char *eName = qt_getEnumName (T ());
			const char *cName = qt_getEnumMetaObject (T ())->className ();
			QByteArray typeName;
			typeName.reserve (int (strlen (cName) + 2 + strlen (eName)));
			typeName.append (cName).append ("::").append (eName);
			const int newId = qRegisterNormalizedMetaType<T> (
				typeName,
				reinterpret_cast<T*>(quintptr (-1)));
			metatype_id.storeRelease (newId);
			return newId;
		}
	};
#endif

#ifndef LOO_NO_DATASTREAM
	template <typename T>
	inline int qRegisterMetaTypeStreamOperators ()
	{
		int id = looMetaTypeId<T> ();
		LooMetaType::registerStreamOperators (id, LooMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Save,
			LooMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Load);
		return id;
	}
#endif

#define Q_DECLARE_OPAQUE_POINTER(POINTER)                               \
    LOO_BEGIN_NAMESPACE namespace LooPrivate {                            \
        template <>                                                     \
        struct IsPointerToTypeDerivedFromQObject<POINTER >              \
        {                                                               \
            enum { Value = false };                                     \
        };                                                              \
    } LOO_END_NAMESPACE                                                  \
    /**/

#define LOO_DECLARE_METATYPE(TYPE) Q_DECLARE_METATYPE_IMPL(TYPE)
#define Q_DECLARE_METATYPE_IMPL(TYPE)                                   \
    LOO_BEGIN_NAMESPACE                                                  \
    template <>                                                         \
    struct QMetaTypeId< TYPE >                                          \
    {                                                                   \
        enum { Defined = 1 };                                           \
        static int qt_metatype_id()                                     \
            {                                                           \
                static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
                if (const int id = metatype_id.loadAcquire())           \
                    return id;                                          \
                const int newId = qRegisterMetaType< TYPE >(#TYPE,      \
                              reinterpret_cast< TYPE *>(quintptr(-1))); \
                metatype_id.storeRelease(newId);                        \
                return newId;                                           \
            }                                                           \
    };                                                                  \
    LOO_END_NAMESPACE


#define Q_DECLARE_BUILTIN_METATYPE(TYPE, METATYPEID, NAME) \
    LOO_BEGIN_NAMESPACE \
    template<> struct LooMetaTypeId2<NAME> \
    { \
        enum { Defined = 1, IsBuiltIn = true, MetaType = METATYPEID };   \
        static inline LOO_DECL_CONSTEXPR int qt_metatype_id() { return METATYPEID; } \
    }; \
    LOO_END_NAMESPACE

#define LOO_FORWARD_DECLARE_STATIC_TYPES_ITER(TypeName, TypeId, Name) \
    class Name;

	LOO_FOR_EACH_STATIC_CORE_CLASS (LOO_FORWARD_DECLARE_STATIC_TYPES_ITER)

#undef LOO_FORWARD_DECLARE_STATIC_TYPES_ITER

		typedef std::vector<LooVariant> QVariantList;
	typedef std::unordered_map<std::string, LooVariant> QVariantMap;
	typedef std::unordered_map<std::string, LooVariant> QVariantHash;
	typedef std::vector<QByteArray> QByteArrayList;

#define Q_DECLARE_METATYPE_TEMPLATE_1ARG(SINGLE_ARG_TEMPLATE) \
LOO_BEGIN_NAMESPACE \
template <typename T> \
struct QMetaTypeId< SINGLE_ARG_TEMPLATE<T> > \
{ \
    enum { \
        Defined = LooMetaTypeId2<T>::Defined \
    }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (const int id = metatype_id.load()) \
            return id; \
        const char *tName = LooMetaType::typeName(looMetaTypeId<T>()); \
        LOO_ASSERT(tName); \
        const int tNameLen = int(qstrlen(tName)); \
        QByteArray typeName; \
        typeName.reserve(int(sizeof(#SINGLE_ARG_TEMPLATE)) + 1 + tNameLen + 1 + 1); \
        typeName.append(#SINGLE_ARG_TEMPLATE, int(sizeof(#SINGLE_ARG_TEMPLATE)) - 1) \
            .append('<').append(tName, tNameLen); \
        if (typeName.endsWith('>')) \
            typeName.append(' '); \
        typeName.append('>'); \
        const int newId = qRegisterNormalizedMetaType< SINGLE_ARG_TEMPLATE<T> >( \
                        typeName, \
                        reinterpret_cast< SINGLE_ARG_TEMPLATE<T> *>(quintptr(-1))); \
        metatype_id.storeRelease(newId); \
        return newId; \
    } \
}; \
namespace LooPrivate { \
template<typename T> \
struct IsSequentialContainer<SINGLE_ARG_TEMPLATE<T> > \
{ \
    enum { Value = true }; \
}; \
} \
LOO_END_NAMESPACE

#define Q_DECLARE_METATYPE_TEMPLATE_2ARG(DOUBLE_ARG_TEMPLATE) \
LOO_BEGIN_NAMESPACE \
template<typename T, typename U> \
struct QMetaTypeId< DOUBLE_ARG_TEMPLATE<T, U> > \
{ \
    enum { \
        Defined = LooMetaTypeId2<T>::Defined && LooMetaTypeId2<U>::Defined \
    }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (const int id = metatype_id.loadAcquire()) \
            return id; \
        const char *tName = LooMetaType::typeName(looMetaTypeId<T>()); \
        const char *uName = LooMetaType::typeName(looMetaTypeId<U>()); \
        LOO_ASSERT(tName); \
        LOO_ASSERT(uName); \
        const int tNameLen = int(qstrlen(tName)); \
        const int uNameLen = int(qstrlen(uName)); \
        QByteArray typeName; \
        typeName.reserve(int(sizeof(#DOUBLE_ARG_TEMPLATE)) + 1 + tNameLen + 1 + uNameLen + 1 + 1); \
        typeName.append(#DOUBLE_ARG_TEMPLATE, int(sizeof(#DOUBLE_ARG_TEMPLATE)) - 1) \
            .append('<').append(tName, tNameLen).append(',').append(uName, uNameLen); \
        if (typeName.endsWith('>')) \
            typeName.append(' '); \
        typeName.append('>'); \
        const int newId = qRegisterNormalizedMetaType< DOUBLE_ARG_TEMPLATE<T, U> >(\
                        typeName, \
                        reinterpret_cast< DOUBLE_ARG_TEMPLATE<T, U> *>(quintptr(-1))); \
        metatype_id.storeRelease(newId); \
        return newId; \
    } \
}; \
LOO_END_NAMESPACE

	namespace LooPrivate {

		template<typename T, bool /* isSharedPointerToQObjectDerived */ = false>
		struct SharedPointerMetaTypeIdHelper
		{
			enum {
				Defined = 0
			};
			static int qt_metatype_id ()
			{
				return -1;
			}
		};

	}

#define Q_DECLARE_SMART_POINTER_METATYPE(SMART_POINTER) \
LOO_BEGIN_NAMESPACE \
namespace LooPrivate { \
template<typename T> \
struct SharedPointerMetaTypeIdHelper<SMART_POINTER<T>, true> \
{ \
    enum { \
        Defined = 1 \
    }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (const int id = metatype_id.loadAcquire()) \
            return id; \
        const char * const cName = T::staticMetaObject.className(); \
        QByteArray typeName; \
        typeName.reserve(int(sizeof(#SMART_POINTER) + 1 + strlen(cName) + 1)); \
        typeName.append(#SMART_POINTER, int(sizeof(#SMART_POINTER)) - 1) \
            .append('<').append(cName).append('>'); \
        const int newId = qRegisterNormalizedMetaType< SMART_POINTER<T> >( \
                        typeName, \
                        reinterpret_cast< SMART_POINTER<T> *>(quintptr(-1))); \
        metatype_id.storeRelease(newId); \
        return newId; \
    } \
}; \
template<typename T> \
struct MetaTypeSmartPointerHelper<SMART_POINTER<T> , \
        typename std::enable_if<IsPointerToTypeDerivedFromQObject<T*>::Value >::Type> \
{ \
    static bool registerConverter(int id) \
    { \
        const int toId = LooMetaType::QObjectStar; \
        if (!LooMetaType::hasRegisteredConverterFunction(id, toId)) { \
            LooPrivate::QSmartPointerConvertFunctor<SMART_POINTER<T> > o; \
            static const LooPrivate::ConverterFunctor<SMART_POINTER<T>, \
                                    QObject*, \
                                    QSmartPointerConvertFunctor<SMART_POINTER<T> > > f(o); \
            return LooMetaType::registerConverterFunction(&f, id, toId); \
        } \
        return true; \
    } \
}; \
} \
template <typename T> \
struct QMetaTypeId< SMART_POINTER<T> > \
    : LooPrivate::SharedPointerMetaTypeIdHelper< SMART_POINTER<T>, \
                                                LooPrivate::IsPointerToTypeDerivedFromQObject<T*>::Value> \
{ \
};\
LOO_END_NAMESPACE

#define LOO_DECLARE_SEQUENTIAL_CONTAINER_METATYPE_ITER(TEMPLATENAME) \
    LOO_BEGIN_NAMESPACE \
    template <class T> class TEMPLATENAME; \
    LOO_END_NAMESPACE \
    Q_DECLARE_METATYPE_TEMPLATE_1ARG(TEMPLATENAME)

	LOO_END_NAMESPACE

		LOO_FOR_EACH_AUTOMATIC_TEMPLATE_1ARG (LOO_DECLARE_SEQUENTIAL_CONTAINER_METATYPE_ITER)

#undef LOO_DECLARE_SEQUENTIAL_CONTAINER_METATYPE_ITER

#define LOO_DECLARE_SEQUENTIAL_CONTAINER_METATYPE Q_DECLARE_METATYPE_TEMPLATE_1ARG

		//LOO_DECLARE_SEQUENTIAL_CONTAINER_METATYPE (std::vector)
		//LOO_DECLARE_SEQUENTIAL_CONTAINER_METATYPE (std::list)

#define LOO_FORWARD_DECLARE_METATYPE_TEMPLATE_2ARG_ITER(TEMPLATENAME, CPPTYPE) \
    LOO_BEGIN_NAMESPACE \
    template <class T1, class T2> CPPTYPE TEMPLATENAME; \
    LOO_END_NAMESPACE \

		LOO_FOR_EACH_AUTOMATIC_TEMPLATE_2ARG (LOO_FORWARD_DECLARE_METATYPE_TEMPLATE_2ARG_ITER)

#undef LOO_DECLARE_METATYPE_TEMPLATE_2ARG_ITER

#define LOO_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE(TEMPLATENAME) \
    LOO_BEGIN_NAMESPACE \
    namespace LooPrivate { \
    template<typename T, typename U> \
    struct IsAssociativeContainer<TEMPLATENAME<T, U> > \
    { \
        enum { Value = true }; \
    }; \
    } \
    LOO_END_NAMESPACE \
    Q_DECLARE_METATYPE_TEMPLATE_2ARG(TEMPLATENAME)

	/*	LOO_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE (std::unordered_map)
		LOO_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE (std::unordered_map)
		LOO_DECLARE_ASSOCIATIVE_CONTAINER_METATYPE (std::map)

		Q_DECLARE_METATYPE_TEMPLATE_2ARG (std::pair)
		Q_DECLARE_METATYPE_TEMPLATE_2ARG (std::pair)*/

#define Q_DECLARE_METATYPE_TEMPLATE_SMART_POINTER_ITER(TEMPLATENAME) \
    Q_DECLARE_SMART_POINTER_METATYPE(TEMPLATENAME)


		LOO_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER (Q_DECLARE_METATYPE_TEMPLATE_SMART_POINTER_ITER)

		LOO_BEGIN_NAMESPACE

#undef Q_DECLARE_METATYPE_TEMPLATE_SMART_POINTER_ITER

		inline LooMetaType::LooMetaType (const ExtensionFlag extensionFlags, const LooMetaTypeInterface *info,
			Creator creator,
			Deleter deleter,
			SaveOperator saveOp,
			LoadOperator loadOp,
			Constructor constructor,
			Destructor destructor,
			luint32 size,
			luint32 theTypeFlags,
			int typeId,
			const LooMetaObject *_metaObject)
		: m_creator_unused (creator)
		, m_deleter_unused (deleter)
		, m_saveOp (saveOp)
		, m_loadOp (loadOp)
		, m_constructor (constructor)
		, m_destructor (destructor)
		, m_extension (LOO_NULLPTR)
		, m_size (size)
		, m_typeFlags (theTypeFlags)
		, m_extensionFlags (extensionFlags)
		, m_typeId (typeId)
		, m_metaObject (_metaObject)
	{
		if (/*/*Q_UNLIKELY*/*/ (isExtended (CtorEx) || typeId == LooMetaType::Void))
			ctor (info);
	}

	inline LooMetaType::~LooMetaType ()
	{
		if (/*/*Q_UNLIKELY*/*/ (isExtended (DtorEx)))
			dtor ();
	}

	inline bool LooMetaType::isValid () const
	{
		return m_typeId != UnknownType;
	}

	inline bool LooMetaType::isRegistered () const
	{
		return isValid ();
	}

	inline void *LooMetaType::create (const void *copy) const
	{
		// ### TODO Qt6 remove the extension
		return createExtended (copy);
	}

	inline void LooMetaType::destroy (void *data) const
	{
		// ### TODO Qt6 remove the extension
		destroyExtended (data);
	}

	inline void *LooMetaType::construct (void *where, const void *copy) const
	{
		if (/*Q_UNLIKELY*/ (isExtended (ConstructEx)))
			return constructExtended (where, copy);
		return m_constructor (where, copy);
	}

	inline void LooMetaType::destruct (void *data) const
	{
		if (/*Q_UNLIKELY*/ (isExtended (DestructEx)))
			return destructExtended (data);
		if (/*Q_UNLIKELY*/ (!data))
			return;
		m_destructor (data);
	}

	inline int LooMetaType::sizeOf () const
	{
		if (/*Q_UNLIKELY*/ (isExtended (SizeEx)))
			return sizeExtended ();
		return m_size;
	}

	inline LooMetaType::TypeFlags LooMetaType::flags () const
	{
		if (/*Q_UNLIKELY*/ (isExtended (FlagsEx)))
			return flagsExtended ();
		return LooMetaType::TypeFlags (m_typeFlags);
	}

	inline const LooMetaObject *LooMetaType::metaObject () const
	{
		if (/*Q_UNLIKELY*/ (isExtended (MetaObjectEx)))
			return metaObjectExtended ();
		return m_metaObject;
	}

	LOO_END_NAMESPACE


		LOO_FOR_EACH_STATIC_TYPE (Q_DECLARE_BUILTIN_METATYPE)

		LOO_DECLARE_METATYPE (LooMetaTypePrivate::LooSequentialIterableImpl)
		LOO_DECLARE_METATYPE (LooMetaTypePrivate::QAssociativeIterableImpl)
		LOO_DECLARE_METATYPE (LooMetaTypePrivate::LooPairVariantInterfaceImpl)

		LOO_BEGIN_NAMESPACE

		template <typename T>
	inline bool LooPrivate::IsMetaTypePair<T, true>::registerConverter (int id)
	{
		const int toId = looMetaTypeId<LooMetaTypePrivate::LooPairVariantInterfaceImpl> ();
		if (!LooMetaType::hasRegisteredConverterFunction (id, toId)) {
			LooMetaTypePrivate::QPairVariantInterfaceConvertFunctor<T> o;
			static const LooPrivate::ConverterFunctor<T,
				LooMetaTypePrivate::LooPairVariantInterfaceImpl,
				LooMetaTypePrivate::QPairVariantInterfaceConvertFunctor<T> > f (o);
			return LooMetaType::registerConverterFunction (&f, id, toId);
		}
		return true;
	}

	namespace LooPrivate {
		template<typename T>
		struct ValueTypeIsMetaType<T, true>
		{
			static bool registerConverter (int id)
			{
				const int toId = looMetaTypeId<LooMetaTypePrivate::LooSequentialIterableImpl> ();
				if (!LooMetaType::hasRegisteredConverterFunction (id, toId)) {
					LooMetaTypePrivate::QSequentialIterableConvertFunctor<T> o;
					static const LooPrivate::ConverterFunctor<T,
						LooMetaTypePrivate::LooSequentialIterableImpl,
						LooMetaTypePrivate::QSequentialIterableConvertFunctor<T> > f (o);
					return LooMetaType::registerConverterFunction (&f, id, toId);
				}
				return true;
			}
		};

		template<typename T>
		struct AssociativeValueTypeIsMetaType<T, true>
		{
			static bool registerConverter (int id)
			{
				const int toId = looMetaTypeId<LooMetaTypePrivate::QAssociativeIterableImpl> ();
				if (!LooMetaType::hasRegisteredConverterFunction (id, toId)) {
					LooMetaTypePrivate::QAssociativeIterableConvertFunctor<T> o;
					static const LooPrivate::ConverterFunctor<T,
						LooMetaTypePrivate::QAssociativeIterableImpl,
						LooMetaTypePrivate::QAssociativeIterableConvertFunctor<T> > f (o);
					return LooMetaType::registerConverterFunction (&f, id, toId);
				}
				return true;
			}
		};
	}
#endif
}


#endif