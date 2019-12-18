#ifndef LOOMETATYPE_H
#define LOOMETATYPE_H
#include <LooCore/looglobal.h>

#include <new>
#include <list>
#include <map>


namespace loo
{

	template<typename T>
	struct LooMetaTypeId2;

	typename<typename T> inline LOO_DECL_CONSTEXPR inline looMetaTypeId ();

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
//    F(QString, 10, QString) \
//    F(QStringList, 11, QStringList) \
//    F(QByteArray, 12, QByteArray) \
//    F(QBitArray, 13, QBitArray) \
//    F(QDate, 14, QDate) \
//    F(QTime, 15, QTime) \
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
//    F(QVariant, 41, QVariant) \
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
    F(ULongLong, -1, luint32, "quint64") /*\
    F(QVariantList, -1, QVariantList, "QList<QVariant>") \
    F(QVariantMap, -1, QVariantMap, "QMap<QString,QVariant>") \
    F(QVariantHash, -1, QVariantHash, "QHash<QString,QVariant>") \
    F(QByteArrayList, -1, QByteArrayList, "QList<QByteArray>") \*/

#define LOO_FOR_EACH_STATIC_TYPE(F)\
    LOO_FOR_EACH_STATIC_PRIMITIVE_TYPE(F)\
    LOO_FOR_EACH_STATIC_PRIMITIVE_POINTER(F)\
    LOO_FOR_EACH_STATIC_CORE_CLASS(F)\
    LOO_FOR_EACH_STATIC_CORE_POINTER(F)\
    LOO_FOR_EACH_STATIC_CORE_TEMPLATE(F)

#define LOO_DEFINE_METATYPE_ID(TypeName, Id, Name) \
    TypeName = Id,

#define LOO_FOR_EACH_AUTOMATIC_TEMPLATE_1ARG(F) /*\
    F(QList) \
    F(QVector) \
    F(QQueue) \
    F(QStack) \
    F(QSet) \
    F(QLinkedList)*/

#define LOO_FOR_EACH_AUTOMATIC_TEMPLATE_2ARG(F)/* \
    F(QHash, class) \
    F(QMap, class) \
    F(QPair, struct)*/

#define LOO_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER(F) /*\
    F(QSharedPointer) \
    F(QWeakPointer) \
    F(QPointer)*/

	class QDataStream;
	class LooMetaTypeInterface;
	struct QMetaObject;

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
#if !defined(QT_NO_DEBUG_STREAM)  && defined(HEHEHE)
		struct AbstractDebugStreamFunction
		{
			typedef void (*Stream)(const AbstractDebugStreamFunction *, QDebug&, const void *);
			typedef void (*Destroy)(AbstractDebugStreamFunction *);
			explicit AbstractDebugStreamFunction (Stream s = LOO_NULLPTR, Destroy d = Q_NULLPTR)
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
				: AbstractComparatorFunction (Q_NULLPTR, equals, destroy) {}
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
#ifndef LOO_LOODOC
		// The code that actually gets compiled.
		enum Type {
			// these are merged with QVariant
			LOO_FOR_EACH_STATIC_TYPE (LOO_DEFINE_METATYPE_ID)

			FirstCoreType = Bool,
			LastCoreType = Nullptr,

			QReal = sizeof (lreal) == sizeof (double) ? Double : Float,

			UnknownType = 0,
			User = 1024
		};
#else
		// If we are using QDoc it fakes the Type enum looks like this.
		enum Type {
			UnknownType = 0, Bool = 1, Int = 2, UInt = 3, LongLong = 4, ULongLong = 5,
			Double = 6, Long = 32, Short = 33, Char = 34, ULong = 35, UShort = 36,
			UChar = 37, Float = 38,
			VoidStar = 31,
			QChar = 7, QString = 10, QStringList = 11, QByteArray = 12,
			QBitArray = 13, QDate = 14, QTime = 15, QDateTime = 16, QUrl = 17,
			QLocale = 18, QRect = 19, QRectF = 20, QSize = 21, QSizeF = 22,
			QLine = 23, QLineF = 24, QPoint = 25, QPointF = 26, QRegExp = 27,
			QEasingCurve = 29, QUuid = 30, QVariant = 41, QModelIndex = 42,
			QPersistentModelIndex = 50, QRegularExpression = 44,
			QJsonValue = 45, QJsonObject = 46, QJsonArray = 47, QJsonDocument = 48,
			QByteArrayList = 49, QObjectStar = 39, SChar = 40,
			Void = 43,
			QVariantMap = 8, QVariantList = 9, QVariantHash = 28,
			QFont = 64, QPixmap = 65, QBrush = 66, QColor = 67, QPalette = 68,
		

			QSizePolicy = 121,
			User = 1024
		};
#endif

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
#ifndef QT_NO_DATASTREAM
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
			const QMetaObject *metaObject);
		static bool unregisterType (int type);
		static int registerNormalizedType (const QT_PREPEND_NAMESPACE (QByteArray) &normalizedTypeName, Deleter deleter,
			Creator creator,
			Destructor destructor,
			Constructor constructor,
			int size,
			LooMetaType::TypeFlags flags,
			const QMetaObject *metaObject);
		static int registerNormalizedType (const QT_PREPEND_NAMESPACE (QByteArray) &normalizedTypeName, Destructor destructor,
			Constructor constructor,
			int size,
			LooMetaType::TypeFlags flags,
			const QMetaObject *metaObject);
		static int registerTypedef (const char *typeName, int aliasId);
		static int registerNormalizedTypedef (const QT_PREPEND_NAMESPACE (QByteArray) &normalizedTypeName, int aliasId);
		static int type (const char *typeName);

		static int type (const QT_PREPEND_NAMESPACE (QByteArray) &typeName);
		static const char *typeName (int type);
		static int sizeOf (int type);
		static TypeFlags typeFlags (int type);
		static const QMetaObject *metaObjectForType (int type);
		static bool isRegistered (int type);
		static void *create (int type, const void *copy = Q_NULLPTR);

		static void destroy (int type, void *data);
		static void *construct (int type, void *where, const void *copy);
		static void destruct (int type, void *where);

#ifndef QT_NO_DATASTREAM
		static bool save (QDataStream &stream, int type, const void *data);
		static bool load (QDataStream &stream, int type, void *data);
#endif

		explicit LooMetaType (const int type); // ### Qt6: drop const
		inline ~LooMetaType ();

		inline bool isValid () const;
		inline bool isRegistered () const;
		inline int sizeOf () const;
		inline TypeFlags flags () const;
		inline const QMetaObject *metaObject () const;

		inline void *create (const void *copy = Q_NULLPTR) const;
		inline void destroy (void *data) const;
		inline void *construct (void *where, const void *copy = Q_NULLPTR) const;
		inline void destruct (void *data) const;

	public:
		template<typename T>
		static bool registerComparators ()
		{
			LOO_STATIC_ASSERT_X ((!LooMetaTypeId2<T>::IsBuiltIn),
				"LooMetaType::registerComparators: The type must be a custom type.");

			const int typeId = lMetaTypeId<T> ();
			static const LooPrivate::BuiltInComparatorFunction<T> f;
			return registerComparatorFunction (&f, typeId);
		}
		template<typename T>
		static bool registerEqualsComparator ()
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<T>::IsBuiltIn),
				"LooMetaType::registerEqualsComparator: The type must be a custom type.");
			const int typeId = qMetaTypeId<T> ();
			static const LooPrivate::BuiltInEqualsComparatorFunction<T> f;
			return registerComparatorFunction (&f, typeId);
		}

		template<typename T>
		static bool hasRegisteredComparators ()
		{
			return hasRegisteredComparators (qMetaTypeId<T> ());
		}
		static bool hasRegisteredComparators (int typeId);


#ifndef QT_NO_DEBUG_STREAM
		template<typename T>
		static bool registerDebugStreamOperator ()
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<T>::IsBuiltIn),
				"LooMetaType::registerDebugStreamOperator: The type must be a custom type.");

			const int typeId = qMetaTypeId<T> ();
			static const LooPrivate::BuiltInDebugStreamFunction<T> f;
			return registerDebugStreamOperatorFunction (&f, typeId);
		}
		template<typename T>
		static bool hasRegisteredDebugStreamOperator ()
		{
			return hasRegisteredDebugStreamOperator (qMetaTypeId<T> ());
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
		// member function as in "QString QFont::toString() const"
		template<typename From, typename To>
		static bool registerConverter (To (From::*function)() const)
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<To>::IsBuiltIn || !LooMetaTypeId2<From>::IsBuiltIn),
				"LooMetaType::registerConverter: At least one of the types must be a custom type.");

			const int fromTypeId = qMetaTypeId<From> ();
			const int toTypeId = qMetaTypeId<To> ();
			static const LooPrivate::ConverterMemberFunction<From, To> f (function);
			return registerConverterFunction (&f, fromTypeId, toTypeId);
		}

		// member function as in "double QString::toDouble(bool *ok = Q_NULLPTR) const"
		template<typename From, typename To>
		static bool registerConverter (To (From::*function)(bool*) const)
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<To>::IsBuiltIn || !LooMetaTypeId2<From>::IsBuiltIn),
				"LooMetaType::registerConverter: At least one of the types must be a custom type.");

			const int fromTypeId = qMetaTypeId<From> ();
			const int toTypeId = qMetaTypeId<To> ();
			static const LooPrivate::ConverterMemberFunctionOk<From, To> f (function);
			return registerConverterFunction (&f, fromTypeId, toTypeId);
		}

		// functor or function pointer
		template<typename From, typename To, typename UnaryFunction>
		static bool registerConverter (UnaryFunction function)
		{
			Q_STATIC_ASSERT_X ((!LooMetaTypeId2<To>::IsBuiltIn || !LooMetaTypeId2<From>::IsBuiltIn),
				"LooMetaType::registerConverter: At least one of the types must be a custom type.");

			const int fromTypeId = qMetaTypeId<From> ();
			const int toTypeId = qMetaTypeId<To> ();
			static const LooPrivate::ConverterFunctor<From, To, UnaryFunction> f (function);
			return registerConverterFunction (&f, fromTypeId, toTypeId);
		}
#endif

		static bool convert (const void *from, int fromTypeId, void *to, int toTypeId);
		static bool compare (const void *lhs, const void *rhs, int typeId, int* result);
		static bool equals (const void *lhs, const void *rhs, int typeId, int* result);
		static bool debugStream (QDebug& dbg, const void *rhs, int typeId);

		template<typename From, typename To>
		static bool hasRegisteredConverterFunction ()
		{
			return hasRegisteredConverterFunction (qMetaTypeId<From> (), qMetaTypeId<To> ());
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
			const QMetaObject *metaObject);
		LooMetaType (const LooMetaType &other);
		LooMetaType &operator =(const LooMetaType &);
		inline bool isExtended (const ExtensionFlag flag) const { return m_extensionFlags & flag; }

		// Methods used for future binary compatible extensions
		void ctor (const LooMetaTypeInterface *info);
		void dtor ();
		luint32 sizeExtended () const;
		LooMetaType::TypeFlags flagsExtended () const;
		const QMetaObject *metaObjectExtended () const;
		void *createExtended (const void *copy = Q_NULLPTR) const;
		void destroyExtended (void *data) const;
		void *constructExtended (void *where, const void *copy = Q_NULLPTR) const;
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
		const QMetaObject *m_metaObject;
	};

}


#endif