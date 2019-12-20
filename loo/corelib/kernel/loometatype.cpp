#if 0
#include "loometatype.h"
#include "looobjectdefs.h"
#include <string>
#include "loovariant.h"
#include <vector>

namespace loo
{
#define NS(x) LOO_PREPEND_NAMESPACE(x)

namespace {
	struct DefinedTypesFilter {
		template<typename T>
		struct Acceptor {
			static const bool IsAccepted = LooMetaTypePrivate::TypeDefinition<T>::IsAvailable && LooModulesPrivate::LooTypeModuleInfo<T>::IsCore;
		};
	};
} // namespace


#define LOO_ADD_STATIC_METATYPE(MetaTypeName, MetaTypeId, RealName) \
    { #RealName, sizeof(#RealName) - 1, MetaTypeId },

#define LOO_ADD_STATIC_METATYPE_ALIASES_ITER(MetaTypeName, MetaTypeId, AliasingName, RealNameStr) \
    { RealNameStr, sizeof(RealNameStr) - 1, LooMetaType::MetaTypeName },

#define LOO_ADD_STATIC_METATYPE_HACKS_ITER(MetaTypeName, TypeId, Name) \
    LOO_ADD_STATIC_METATYPE(MetaTypeName, MetaTypeName, Name)

//这里缓存所有内置类型的类型映射信息
static const struct { const char * typeName; int typeNameLength; int type; } types[] = {
	LOO_FOR_EACH_STATIC_TYPE (LOO_ADD_STATIC_METATYPE)
	LOO_FOR_EACH_STATIC_ALIAS_TYPE (LOO_ADD_STATIC_METATYPE_ALIASES_ITER)
	//LOO_FOR_EACH_STATIC_HACKS_TYPE (LOO_ADD_STATIC_METATYPE_HACKS_ITER)
	{
	0, 0, LooMetaType::UnknownType
	}
};

LOO_CORE_EXPORT const LooMetaTypeInterface *qMetaTypeGuiHelper = 0;
LOO_CORE_EXPORT const LooMetaTypeInterface *qMetaTypeWidgetsHelper = 0;
LOO_CORE_EXPORT const LooMetaObject *qMetaObjectWidgetsHelper = 0;

class LooCustomTypeInfo : public LooMetaTypeInterface
{
public:
	LooCustomTypeInfo ()
		: alias (-1)
	{
		LooMetaTypeInterface empty = LOO_METATYPE_INTERFACE_INIT (void);
		*static_cast<LooMetaTypeInterface*>(this) = empty;
	}
	std::string typeName;
	int alias;
};

template<typename T, typename Key>
class LooMetaTypeFunctionRegistry
{
public:
	~LooMetaTypeFunctionRegistry ()
	{
		const QWriteLocker locker (&lock);
		map.clear ();
	}

	bool contains (Key k) const
	{
		const QReadLocker locker (&lock);
		return map.contains (k);
	}

	bool insertIfNotContains (Key k, const T *f)
	{
		const QWriteLocker locker (&lock);
		const T* &fun = map[k];
		if (fun != 0)
			return false;
		fun = f;
		return true;
	}

	const T *function (Key k) const
	{
		const QReadLocker locker (&lock);
		return map.value (k, 0);
	}

	void remove (int from, int to)
	{
		const Key k (from, to);
		const QWriteLocker locker (&lock);
		map.remove (k);
	}
private:
	mutable QReadWriteLock lock;
	QHash<Key, const T *> map;
};

typedef LooMetaTypeFunctionRegistry<LooPrivate::AbstractConverterFunction, std::pair<int, int> >
LooMetaTypeConverterRegistry;
typedef LooMetaTypeFunctionRegistry<LooPrivate::AbstractComparatorFunction, int>
LooMetaTypeComparatorRegistry;
//typedef LooMetaTypeFunctionRegistry<LooPrivate::AbstractDebugStreamFunction, int>
//LooMetaTypeDebugStreamRegistry;

namespace
{
	union CheckThatItIsPod
	{   // This should break if LooMetaTypeInterface is not a POD type
		LooMetaTypeInterface iface;
	};
}

LOO_DECLARE_TYPEINFO (LooCustomTypeInfo, LOO_MOVABLE_TYPE);
LOO_GLOBAL_STATIC (std::vector<LooCustomTypeInfo>, customTypes)
LOO_GLOBAL_STATIC (QReadWriteLock, customTypesLock)
LOO_GLOBAL_STATIC (LooMetaTypeConverterRegistry, customTypesConversionRegistry)
LOO_GLOBAL_STATIC (LooMetaTypeComparatorRegistry, customTypesComparatorRegistry)
LOO_GLOBAL_STATIC (LooMetaTypeDebugStreamRegistry, customTypesDebugStreamRegistry)

/*!
	\fn bool LooMetaType::registerConverter()
	\since 5.2
	Registers the possibility of an implicit conversion from type From to type To in the meta
	type system. Returns \c true if the registration succeeded, otherwise false.
*/

/*!
	\fn bool LooMetaType::registerConverter(MemberFunction function)
	\since 5.2
	\overload
	Registers a method \a function like To From::function() const as converter from type From
	to type To in the meta type system. Returns \c true if the registration succeeded, otherwise false.
*/

/*!
	\fn bool LooMetaType::registerConverter(MemberFunctionOk function)
	\since 5.2
	\overload
	Registers a method \a function like To From::function(bool *ok) const as converter from type From
	to type To in the meta type system. Returns \c true if the registration succeeded, otherwise false.
*/

/*!
	\fn bool LooMetaType::registerConverter(UnaryFunction function)
	\since 5.2
	\overload
	Registers a unary function object \a function as converter from type From
	to type To in the meta type system. Returns \c true if the registration succeeded, otherwise false.
*/

/*!
	\fn bool LooMetaType::registerComparators()
	\since 5.2
	Registers comparison operators for the user-registered type T. This requires T to have
	both an operator== and an operator<.
	Returns \c true if the registration succeeded, otherwise false.
*/

/*!
	\fn bool LooMetaType::registerEqualsComparator()
	\since 5.5
	Registers equals operator for the user-registered type T. This requires T to have
	an operator==.
	Returns \c true if the registration succeeded, otherwise false.
*/

#ifndef LOO_NO_DEBUG_STREAM
/*!
	\fn bool LooMetaType::registerDebugStreamOperator()
	Registers the debug stream operator for the user-registered type T. This requires T to have
	an operator<<(QDebug dbg, T).
	Returns \c true if the registration succeeded, otherwise false.
*/
#endif

/*!
	Registers function \a f as converter function from type id \a from to \a to.
	If there's already a conversion registered, this does nothing but deleting \a f.
	Returns \c true if the registration succeeded, otherwise false.
	\since 5.2
	\internal
*/
bool LooMetaType::registerConverterFunction (const LooPrivate::AbstractConverterFunction *f, int from, int to)
{
	if (!customTypesConversionRegistry ()->insertIfNotContains (qMakePair (from, to), f)) {
		qWarning ("Type conversion already registered from type %s to type %s",
			LooMetaType::typeName (from), LooMetaType::typeName (to));
		return false;
	}
	return true;
}

/*!
	\internal

	Invoked automatically when a converter function object is destroyed.
 */
void LooMetaType::unregisterConverterFunction (int from, int to)
{
	if (customTypesConversionRegistry.isDestroyed ())
		return;
	customTypesConversionRegistry ()->remove (from, to);
}

bool LooMetaType::registerComparatorFunction (const LooPrivate::AbstractComparatorFunction *f, int type)
{
	if (!customTypesComparatorRegistry ()->insertIfNotContains (type, f)) {
		qWarning ("Comparators already registered for type %s", LooMetaType::typeName (type));
		return false;
	}
	return true;
}

/*!
	\fn bool LooMetaType::hasRegisteredComparators()
	Returns \c true, if the meta type system has registered comparators for type T.
	\since 5.2
 */

 /*!
	 Returns \c true, if the meta type system has registered comparators for type id \a typeId.
	 \since 5.2
  */
bool LooMetaType::hasRegisteredComparators (int typeId)
{
	return customTypesComparatorRegistry ()->contains (typeId);
}

#ifndef LOO_NO_DEBUG_STREAM
bool LooMetaType::registerDebugStreamOperatorFunction (const LooPrivate::AbstractDebugStreamFunction *f,
	int type)
{
	if (!customTypesDebugStreamRegistry ()->insertIfNotContains (type, f)) {
		qWarning ("Debug stream operator already registered for type %s", LooMetaType::typeName (type));
		return false;
	}
	return true;
}

/*!
	\fn bool LooMetaType::hasRegisteredDebugStreamOperator()
	Returns \c true, if the meta type system has a registered debug stream operator for type T.
	\since 5.2
 */

 /*!
	 Returns \c true, if the meta type system has a registered debug stream operator for type
	 id \a typeId.
	 \since 5.2
 */
bool LooMetaType::hasRegisteredDebugStreamOperator (int typeId)
{
	return customTypesDebugStreamRegistry ()->contains (typeId);
}
#endif

/*!
	Converts the object at \a from from \a fromTypeId to the preallocated space at \a to
	typed \a toTypeId. Returns \c true, if the conversion succeeded, otherwise false.
	\since 5.2
*/
bool LooMetaType::convert (const void *from, int fromTypeId, void *to, int toTypeId)
{
	const LooPrivate::AbstractConverterFunction * const f =
		customTypesConversionRegistry ()->function (qMakePair (fromTypeId, toTypeId));
	return f && f->convert (f, from, to);
}

/*!
	Compares the objects at \a lhs and \a rhs. Both objects need to be of type \a typeId.
	\a result is set to less than, equal to or greater than zero, if \a lhs is less than, equal to
	or greater than \a rhs. Returns \c true, if the comparison succeeded, otherwise \c false.
	\since 5.2
*/
bool LooMetaType::compare (const void *lhs, const void *rhs, int typeId, int* result)
{
	const LooPrivate::AbstractComparatorFunction * const f =
		customTypesComparatorRegistry ()->function (typeId);
	if (!f)
		return false;
	if (f->equals (f, lhs, rhs))
		*result = 0;
	else if (f->lessThan)
		*result = f->lessThan (f, lhs, rhs) ? -1 : 1;
	else
		return false;
	return true;
}

/*!
	Compares the objects at \a lhs and \a rhs. Both objects need to be of type \a typeId.
	\a result is set to zero, if \a lhs equals to rhs. Returns \c true, if the comparison
	succeeded, otherwise \c false.
	\since 5.5
*/
bool LooMetaType::equals (const void *lhs, const void *rhs, int typeId, int *result)
{
	const LooPrivate::AbstractComparatorFunction * const f
		= customTypesComparatorRegistry ()->function (typeId);
	if (!f)
		return false;
	if (f->equals (f, lhs, rhs))
		*result = 0;
	else
		*result = -1;
	return true;
}

/*!
	Streams the object at \a rhs of type \a typeId to the debug stream \a dbg. Returns \c true
	on success, otherwise false.
	\since 5.2
*/
bool LooMetaType::debugStream (QDebug& dbg, const void *rhs, int typeId)
{
	const LooPrivate::AbstractDebugStreamFunction * const f = customTypesDebugStreamRegistry ()->function (typeId);
	if (!f)
		return false;
	f->stream (f, dbg, rhs);
	return true;
}

/*!
	\fn bool LooMetaType::hasRegisteredConverterFunction()
	Returns \c true, if the meta type system has a registered conversion from type From to type To.
	\since 5.2
	\overload
	*/

	/*!
		Returns \c true, if the meta type system has a registered conversion from meta type id \a fromTypeId
		to \a toTypeId
		\since 5.2
	*/
bool LooMetaType::hasRegisteredConverterFunction (int fromTypeId, int toTypeId)
{
	return customTypesConversionRegistry ()->contains (qMakePair (fromTypeId, toTypeId));
}

#ifndef LOO_NO_DATASTREAM
/*!
	\internal
*/
void LooMetaType::registerStreamOperators (const char *typeName, SaveOperator saveOp,
	LoadOperator loadOp)
{
	registerStreamOperators (type (typeName), saveOp, loadOp);
}

/*!
	\internal
*/
void LooMetaType::registerStreamOperators (int idx, SaveOperator saveOp,
	LoadOperator loadOp)
{
	if (idx < User)
		return; //builtin types should not be registered;
	std::vector<LooCustomTypeInfo> *ct = customTypes ();
	if (!ct)
		return;
	QWriteLocker locker (customTypesLock ());
	LooCustomTypeInfo &inf = (*ct)[idx - User];
	inf.saveOp = saveOp;
	inf.loadOp = loadOp;
}
#endif // LOO_NO_DATASTREAM

/*!
	Returns the type name associated with the given \a typeId, or 0 if no
	matching type was found. The returned pointer must not be deleted.

	\sa type(), isRegistered(), Type
*/
const char *LooMetaType::typeName (int typeId)
{
	const uint type = typeId;
	// In theory it can be filled during compilation time, but for some reason template code
	// that is able to do it causes GCC 4.6 to generate additional 3K of executable code. Probably
	// it is not worth of it.
	static const char *namesCache[LooMetaType::HighestInternalId + 1];

	const char *result;
	if (type <= LooMetaType::HighestInternalId && ((result = namesCache[type])))
		return result;

#define LOO_METATYPE_TYPEID_TYPENAME_CONVERTER(MetaTypeName, TypeId, RealName) \
        case LooMetaType::MetaTypeName: result = #RealName; break;

	switch (LooMetaType::Type (type)) {
		LOO_FOR_EACH_STATIC_TYPE (LOO_METATYPE_TYPEID_TYPENAME_CONVERTER)

	default: {
			if (LOO_UNLIKELY (type < LooMetaType::User)) {
				return 0; // It can happen when someone cast int to QVariant::Type, we should not crash...
			}
			else {
				const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
				QReadLocker locker (customTypesLock ());
				return ct && uint (ct->count ()) > type - LooMetaType::User && !ct->at (type - LooMetaType::User).typeName.isEmpty ()
					? ct->at (type - LooMetaType::User).typeName.constData ()
					: 0;
			}
		}
	}
#undef LOO_METATYPE_TYPEID_TYPENAME_CONVERTER

	LOO_ASSERT (type <= LooMetaType::HighestInternalId);
	namesCache[type] = result;
	return result;
}

/*!
	\internal
	Similar to LooMetaType::type(), but only looks in the static set of types.
*/
static inline int qMetaTypeStaticType (const char *typeName, int length)
{
	int i = 0;
	while (types[i].typeName && ((length != types[i].typeNameLength)
		|| memcmp (typeName, types[i].typeName, length))) {
		++i;
	}
	return types[i].type;
}

/*!
	\internal
	Similar to LooMetaType::type(), but only looks in the custom set of
	types, and doesn't lock the mutex.
	The extra \a firstInvalidIndex parameter is an easy way to avoid
	iterating over customTypes() a second time in registerNormalizedType().
*/
static int qMetaTypeCustomType_unlocked (const char *typeName, int length, int *firstInvalidIndex = 0)
{
	//自定义类型查询
	const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
	if (!ct)
		return LooMetaType::UnknownType;

	if (firstInvalidIndex)
		*firstInvalidIndex = -1;
	for (int v = 0; v < ct->count (); ++v) {
		const LooCustomTypeInfo &customInfo = ct->at (v);
		if ((length == customInfo.typeName.size ())
			&& !memcmp (typeName, customInfo.typeName.constData (), length)) {
			if (customInfo.alias >= 0)
				return customInfo.alias;
			return v + LooMetaType::User;
		}
		if (firstInvalidIndex && (*firstInvalidIndex < 0) && customInfo.typeName.isEmpty ())
			*firstInvalidIndex = v;
	}
	return LooMetaType::UnknownType;
}

/*!
	\internal

	This function is needed until existing code outside of qtbase
	has been changed to call the new version of registerType().
 */
int LooMetaType::registerType (const char *typeName, Deleter deleter,
	Creator creator)
{
	return registerType (typeName, deleter, creator,
		QtMetaTypePrivate::LooMetaTypeFunctionHelper<void>::Destruct,
		QtMetaTypePrivate::LooMetaTypeFunctionHelper<void>::Construct, 0, TypeFlags (), 0);
}

/*!
	\internal
	\since 5.5

	Unregisters the user type with the given \a typeId and all its aliases.
	Returns \c true if the type was unregistered or \c false otherwise.

	This function was added for QML to be able to deregister types after
	they are unloaded to prevent an infinite increase in custom types for
	applications that are unloading/reloading components often.
 */
bool LooMetaType::unregisterType (int type)
{
	QWriteLocker locker (customTypesLock ());
	std::vector<LooCustomTypeInfo> *ct = customTypes ();

	// check if user type
	if ((type < User) || ((type - User) >= ct->size ()))
		return false;

	// only types without LOO_DECLARE_METATYPE can be unregistered
	if (ct->data ()[type - User].flags & WasDeclaredAsMetaType)
		return false;

	// invalidate type and all its alias entries
	for (int v = 0; v < ct->count (); ++v) {
		if (((v + User) == type) || (ct->at (v).alias == type))
			ct->data ()[v].typeName.clear ();
	}
	return true;
}


/*!
	\internal
	\since 5.0

	Registers a user type for marshalling, with \a typeName, a \a
	deleter, a \a creator, a \a destructor, a \a constructor, and
	a \a size. Returns the type's handle, or -1 if the type could
	not be registered.
 */
int LooMetaType::registerType (const char *typeName, Deleter deleter,
	Creator creator,
	Destructor destructor,
	Constructor constructor,
	int size, TypeFlags flags, const LooMetaObject *metaObject)
{
#ifdef LOO_NO_QOBJECT
	NS (std::string) normalizedTypeName = typeName;
#else
	NS (std::string) normalizedTypeName = LooMetaObject::normalizedType (typeName);
#endif

	return registerNormalizedType (normalizedTypeName, deleter, creator, destructor, constructor, size, flags, metaObject);
}


/*!
  \internal
  \since 5.0
  \overload
  Don't use, kept for binary compatibility

  ### TODO Qt6: remove me
*/
int LooMetaType::registerNormalizedType (const NS (std::string) &normalizedTypeName, Deleter deleter,
	Creator creator,
	Destructor destructor,
	Constructor constructor,
	int size, TypeFlags flags, const LooMetaObject *metaObject)
{
	LOO_UNUSED (deleter);
	LOO_UNUSED (creator);
	return registerNormalizedType (normalizedTypeName, destructor, constructor, size, flags, metaObject);
}


/*!
	\internal
	\since 5.5

	Registers a user type for marshalling, with \a normalizedTypeName,
	a \a destructor, a \a constructor, and a \a size. Returns the type's
	handle, or -1 if the type could not be registered.

	\note normalizedTypeName is not checked for conformance with
	Qt's normalized format, so it must already conform.
 */
int LooMetaType::registerNormalizedType (const std::string &normalizedTypeName,
	Destructor destructor,
	Constructor constructor,
	int size, TypeFlags flags, const LooMetaObject *metaObject)
{
	std::vector<LooCustomTypeInfo> *ct = customTypes ();
	if (!ct || normalizedTypeName.isEmpty () || !destructor || !constructor)
		return -1;

	int idx = qMetaTypeStaticType (normalizedTypeName.constData (),
		normalizedTypeName.size ());

	int previousSize = 0;
	int previousFlags = 0;
	if (idx == UnknownType) {
		QWriteLocker locker (customTypesLock ());
		int posInVector = -1;
		idx = qMetaTypeCustomType_unlocked (normalizedTypeName.constData (),
			normalizedTypeName.size (),
			&posInVector);
		if (idx == UnknownType) {
			LooCustomTypeInfo inf;
			inf.typeName = normalizedTypeName;
#ifndef LOO_NO_DATASTREAM
			inf.loadOp = 0;
			inf.saveOp = 0;
#endif
			inf.alias = -1;
			inf.constructor = constructor;
			inf.destructor = destructor;
			inf.size = size;
			inf.flags = flags;
			inf.metaObject = metaObject;
			if (posInVector == -1) {
				idx = ct->size () + User;
				ct->append (inf);
			}
			else {
				idx = posInVector + User;
				ct->data ()[posInVector] = inf;
			}
			return idx;
		}

		if (idx >= User) {
			previousSize = ct->at (idx - User).size;
			previousFlags = ct->at (idx - User).flags;

			// Set new/additional flags in case of old library/app.
			// Ensures that older code works in conjunction with new Qt releases
			// requiring the new flags.
			if (flags != previousFlags) {
				LooCustomTypeInfo &inf = ct->data ()[idx - User];
				inf.flags |= flags;
				if (metaObject)
					inf.metaObject = metaObject;
			}
		}
	}

	if (idx < User) {
		previousSize = LooMetaType::sizeOf (idx);
		previousFlags = LooMetaType::typeFlags (idx);
	}

	if (LOO_UNLIKELY (previousSize != size)) {
		qFatal ("LooMetaType::registerType: Binary compatibility break "
			"-- Size mismatch for type '%s' [%i]. Previously registered "
			"size %i, now registering size %i.",
			normalizedTypeName.constData (), idx, previousSize, size);
	}

	// these flags cannot change in a binary compatible way:
	const int binaryCompatibilityFlag = PointerToQObject | IsEnumeration | SharedPointerToQObject
		| WeakPointerToQObject | TrackingPointerToQObject;
	if (LOO_UNLIKELY ((previousFlags ^ flags) & binaryCompatibilityFlag)) {

		const char *msg = "LooMetaType::registerType: Binary compatibility break. "
			"\nType flags for type '%s' [%i] don't match. Previously "
			"registered TypeFlags(0x%x), now registering TypeFlags(0x%x). ";

		qFatal (msg, normalizedTypeName.constData (), idx, previousFlags, int (flags));
	}

	return idx;
}

/*!
	\internal
	\since 4.7

	Registers a user type for marshalling, as an alias of another type (typedef)
*/
int LooMetaType::registerTypedef (const char* typeName, int aliasId)
{
#ifdef LOO_NO_QOBJECT
	NS (std::string) normalizedTypeName = typeName;
#else
	NS (std::string) normalizedTypeName = LooMetaObject::normalizedType (typeName);
#endif

	return registerNormalizedTypedef (normalizedTypeName, aliasId);
}

/*!
	\internal
	\since 5.0

	Registers a user type for marshalling, as an alias of another type (typedef).
	Note that normalizedTypeName is not checked for conformance with Qt's normalized format,
	so it must already conform.
*/
int LooMetaType::registerNormalizedTypedef (const NS (std::string) &normalizedTypeName, int aliasId)
{
	std::vector<LooCustomTypeInfo> *ct = customTypes ();
	if (!ct || normalizedTypeName.isEmpty ())
		return -1;

	int idx = qMetaTypeStaticType (normalizedTypeName.constData (),
		normalizedTypeName.size ());

	if (idx == UnknownType) {
		QWriteLocker locker (customTypesLock ());
		int posInVector = -1;
		idx = qMetaTypeCustomType_unlocked (normalizedTypeName.constData (),
			normalizedTypeName.size (),
			&posInVector);

		if (idx == UnknownType) {
			LooCustomTypeInfo inf;
			inf.typeName = normalizedTypeName;
			inf.alias = aliasId;
			if (posInVector == -1)
				ct->append (inf);
			else
				ct->data ()[posInVector] = inf;
			return aliasId;
		}
	}

	if (idx != aliasId) {
		qWarning ("LooMetaType::registerTypedef: "
			"-- Type name '%s' previously registered as typedef of '%s' [%i], "
			"now registering as typedef of '%s' [%i].",
			normalizedTypeName.constData (), LooMetaType::typeName (idx), idx,
			LooMetaType::typeName (aliasId), aliasId);
	}
	return idx;
}

/*!
	Returns \c true if the datatype with ID \a type is registered;
	otherwise returns \c false.

	\sa type(), typeName(), Type
*/
bool LooMetaType::isRegistered (int type)
{
	// predefined type
	if ((type >= FirstCoreType && type <= LastCoreType)
		|| (type >= FirstGuiType && type <= LastGuiType)
		|| (type >= FirstWidgetsType && type <= LastWidgetsType)) {
		return true;
	}

	QReadLocker locker (customTypesLock ());
	const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
	return ((type >= User) && (ct && ct->count () > type - User) && !ct->at (type - User).typeName.isEmpty ());
}

//分配ID
template <bool tryNormalizedType>
static inline int qMetaTypeTypeImpl (const char *typeName, int length)
{
	if (!length)
		return LooMetaType::UnknownType;
	//内置类型
	int type = qMetaTypeStaticType (typeName, length);
	if (type == LooMetaType::UnknownType) {
		QReadLocker locker (customTypesLock ());
		//是否已经分配自定义
		type = qMetaTypeCustomType_unlocked (typeName, length);
#ifndef LOO_NO_QOBJECT
		if ((type == LooMetaType::UnknownType) && tryNormalizedType) {
			//全名
			const std::string normalizedTypeName = LooMetaObject::normalizedType (typeName);
			//静态
			type = qMetaTypeStaticType (normalizedTypeName.constData (),
				normalizedTypeName.size ());
			if (type == LooMetaType::UnknownType) {
				type = qMetaTypeCustomType_unlocked (normalizedTypeName.constData (),
					normalizedTypeName.size ());
			}
		}
#endif
	}
	return type;
}

/*!
	Returns a handle to the type called \a typeName, or LooMetaType::UnknownType if there is
	no such type.

	\sa isRegistered(), typeName(), Type
*/
int LooMetaType::type (const char *typeName)
{
	return qMetaTypeTypeImpl</*tryNormalizedType=*/true> (typeName, strlen (typeName));
}

/*!
	\a internal

	Similar to LooMetaType::type(); the only difference is that this function
	doesn't attempt to normalize the type name (i.e., the lookup will fail
	for type names in non-normalized form).
*/
int qMetaTypeTypeInternal (const char *typeName)
{
	return qMetaTypeTypeImpl</*tryNormalizedType=*/false> (typeName, qstrlen (typeName));
}

/*!
	\since 5.5
	\overload

	Returns a handle to the type called \a typeName, or 0 if there is
	no such type.

	\sa isRegistered(), typeName()
*/
int LooMetaType::type (const LOO_PREPEND_NAMESPACE (std::string) &typeName)
{
	return qMetaTypeTypeImpl</*tryNormalizedType=*/true> (typeName.constData (), typeName.size ());
}

#ifndef LOO_NO_DATASTREAM
/*!
	Writes the object pointed to by \a data with the ID \a type to
	the given \a stream. Returns \c true if the object is saved
	successfully; otherwise returns \c false.

	The type must have been registered with qRegisterMetaType() and
	qRegisterMetaTypeStreamOperators() beforehand.

	Normally, you should not need to call this function directly.
	Instead, use QVariant's \c operator<<(), which relies on save()
	to stream custom types.

	\sa load(), qRegisterMetaTypeStreamOperators()
*/
bool LooMetaType::save (QDataStream &stream, int type, const void *data)
{
	if (!data || !isRegistered (type))
		return false;

	switch (type) {
	case LooMetaType::UnknownType:
	case LooMetaType::Void:
	case LooMetaType::VoidStar:
	case LooMetaType::QObjectStar:
	case LooMetaType::QModelIndex:
	case LooMetaType::QPersistentModelIndex:
	case LooMetaType::QJsonValue:
	case LooMetaType::QJsonObject:
	case LooMetaType::QJsonArray:
	case LooMetaType::QJsonDocument:
		return false;
	case LooMetaType::Long:
		stream << qlonglong (*static_cast<const long *>(data));
		break;
	case LooMetaType::Int:
		stream << *static_cast<const int *>(data);
		break;
	case LooMetaType::Short:
		stream << *static_cast<const short *>(data);
		break;
	case LooMetaType::Char:
		// force a char to be signed
		stream << *static_cast<const signed char *>(data);
		break;
	case LooMetaType::ULong:
		stream << qulonglong (*static_cast<const ulong *>(data));
		break;
	case LooMetaType::UInt:
		stream << *static_cast<const uint *>(data);
		break;
	case LooMetaType::LongLong:
		stream << *static_cast<const qlonglong *>(data);
		break;
	case LooMetaType::ULongLong:
		stream << *static_cast<const qulonglong *>(data);
		break;
	case LooMetaType::UShort:
		stream << *static_cast<const ushort *>(data);
		break;
	case LooMetaType::SChar:
		stream << *static_cast<const signed char *>(data);
		break;
	case LooMetaType::UChar:
		stream << *static_cast<const uchar *>(data);
		break;
	case LooMetaType::Bool:
		stream << qint8 (*static_cast<const bool *>(data));
		break;
	case LooMetaType::Float:
		stream << *static_cast<const float *>(data);
		break;
	case LooMetaType::Double:
		stream << *static_cast<const double *>(data);
		break;
	case LooMetaType::QChar:
		stream << *static_cast<const NS (QChar) *>(data);
		break;
#ifndef LOO_BOOTSTRAPPED
	case LooMetaType::QVariantMap:
		stream << *static_cast<const NS (QVariantMap)*>(data);
		break;
	case LooMetaType::QVariantHash:
		stream << *static_cast<const NS (QVariantHash)*>(data);
		break;
	case LooMetaType::QVariantList:
		stream << *static_cast<const NS (QVariantList)*>(data);
		break;
	case LooMetaType::QVariant:
		stream << *static_cast<const NS (QVariant)*>(data);
		break;
	case LooMetaType::QByteArrayList:
		stream << *static_cast<const NS (QByteArrayList)*>(data);
		break;
#endif
	case LooMetaType::std::string:
		stream << *static_cast<const NS (std::string)*>(data);
		break;
	case LooMetaType::QString:
		stream << *static_cast<const NS (QString)*>(data);
		break;
	case LooMetaType::QStringList:
		stream << *static_cast<const NS (QStringList)*>(data);
		break;
#ifndef LOO_BOOTSTRAPPED
	case LooMetaType::QBitArray:
		stream << *static_cast<const NS (QBitArray)*>(data);
		break;
#endif
	case LooMetaType::QDate:
		stream << *static_cast<const NS (QDate)*>(data);
		break;
	case LooMetaType::QTime:
		stream << *static_cast<const NS (QTime)*>(data);
		break;
	case LooMetaType::QDateTime:
		stream << *static_cast<const NS (QDateTime)*>(data);
		break;
#ifndef LOO_BOOTSTRAPPED
	case LooMetaType::QUrl:
		stream << *static_cast<const NS (QUrl)*>(data);
		break;
#endif
	case LooMetaType::QLocale:
		stream << *static_cast<const NS (QLocale)*>(data);
		break;
#ifndef LOO_NO_GEOM_VARIANT
	case LooMetaType::QRect:
		stream << *static_cast<const NS (QRect)*>(data);
		break;
	case LooMetaType::QRectF:
		stream << *static_cast<const NS (QRectF)*>(data);
		break;
	case LooMetaType::QSize:
		stream << *static_cast<const NS (QSize)*>(data);
		break;
	case LooMetaType::QSizeF:
		stream << *static_cast<const NS (QSizeF)*>(data);
		break;
	case LooMetaType::QLine:
		stream << *static_cast<const NS (QLine)*>(data);
		break;
	case LooMetaType::QLineF:
		stream << *static_cast<const NS (QLineF)*>(data);
		break;
	case LooMetaType::QPoint:
		stream << *static_cast<const NS (QPoint)*>(data);
		break;
	case LooMetaType::QPointF:
		stream << *static_cast<const NS (QPointF)*>(data);
		break;
#endif
#ifndef LOO_NO_REGEXP
	case LooMetaType::QRegExp:
		stream << *static_cast<const NS (QRegExp)*>(data);
		break;
#endif
#ifndef LOO_BOOTSTRAPPED
#ifndef LOO_NO_REGULAREXPRESSION
	case LooMetaType::QRegularExpression:
		stream << *static_cast<const NS (QRegularExpression)*>(data);
		break;
#endif // LOO_NO_REGULAREXPRESSION
	case LooMetaType::QEasingCurve:
		stream << *static_cast<const NS (QEasingCurve)*>(data);
		break;
#endif // LOO_BOOTSTRAPPED
	case LooMetaType::QFont:
	case LooMetaType::QPixmap:
	case LooMetaType::QBrush:
	case LooMetaType::QColor:
	case LooMetaType::QPalette:
	case LooMetaType::QImage:
	case LooMetaType::QPolygon:
	case LooMetaType::QPolygonF:
	case LooMetaType::QRegion:
	case LooMetaType::QBitmap:
	case LooMetaType::QCursor:
	case LooMetaType::QKeySequence:
	case LooMetaType::QPen:
	case LooMetaType::QTextLength:
	case LooMetaType::QTextFormat:
	case LooMetaType::QMatrix:
	case LooMetaType::QTransform:
	case LooMetaType::QMatrix4x4:
	case LooMetaType::std::vector2D:
	case LooMetaType::std::vector3D:
	case LooMetaType::std::vector4D:
	case LooMetaType::QQuaternion:
	case LooMetaType::QIcon:
		if (!qMetaTypeGuiHelper)
			return false;
		qMetaTypeGuiHelper[type - FirstGuiType].saveOp (stream, data);
		break;
	case LooMetaType::QSizePolicy:
		if (!qMetaTypeWidgetsHelper)
			return false;
		qMetaTypeWidgetsHelper[type - FirstWidgetsType].saveOp (stream, data);
		break;
	case LooMetaType::QUuid:
		stream << *static_cast<const NS (QUuid)*>(data);
		break;
	default: {
		const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
		if (!ct)
			return false;

		SaveOperator saveOp = 0;
		{
			QReadLocker locker (customTypesLock ());
			saveOp = ct->at (type - User).saveOp;
		}

		if (!saveOp)
			return false;
		saveOp (stream, data);
		break; }
	}

	return true;
}

/*!
	Reads the object of the specified \a type from the given \a
	stream into \a data. Returns \c true if the object is loaded
	successfully; otherwise returns \c false.

	The type must have been registered with qRegisterMetaType() and
	qRegisterMetaTypeStreamOperators() beforehand.

	Normally, you should not need to call this function directly.
	Instead, use QVariant's \c operator>>(), which relies on load()
	to stream custom types.

	\sa save(), qRegisterMetaTypeStreamOperators()
*/
bool LooMetaType::load (QDataStream &stream, int type, void *data)
{
	if (!data || !isRegistered (type))
		return false;

	switch (type) {
	case LooMetaType::UnknownType:
	case LooMetaType::Void:
	case LooMetaType::VoidStar:
	case LooMetaType::QObjectStar:
	case LooMetaType::QModelIndex:
	case LooMetaType::QPersistentModelIndex:
	case LooMetaType::QJsonValue:
	case LooMetaType::QJsonObject:
	case LooMetaType::QJsonArray:
	case LooMetaType::QJsonDocument:
		return false;
	case LooMetaType::Long: {
		qlonglong l;
		stream >> l;
		*static_cast<long *>(data) = long (l);
		break; }
	case LooMetaType::Int:
		stream >> *static_cast<int *>(data);
		break;
	case LooMetaType::Short:
		stream >> *static_cast<short *>(data);
		break;
	case LooMetaType::Char:
		// force a char to be signed
		stream >> *static_cast<signed char *>(data);
		break;
	case LooMetaType::ULong: {
		qulonglong ul;
		stream >> ul;
		*static_cast<ulong *>(data) = ulong (ul);
		break; }
	case LooMetaType::UInt:
		stream >> *static_cast<uint *>(data);
		break;
	case LooMetaType::LongLong:
		stream >> *static_cast<qlonglong *>(data);
		break;
	case LooMetaType::ULongLong:
		stream >> *static_cast<qulonglong *>(data);
		break;
	case LooMetaType::UShort:
		stream >> *static_cast<ushort *>(data);
		break;
	case LooMetaType::SChar:
		stream >> *static_cast<signed char *>(data);
		break;
	case LooMetaType::UChar:
		stream >> *static_cast<uchar *>(data);
		break;
	case LooMetaType::Bool: {
		qint8 b;
		stream >> b;
		*static_cast<bool *>(data) = b;
		break; }
	case LooMetaType::Float:
		stream >> *static_cast<float *>(data);
		break;
	case LooMetaType::Double:
		stream >> *static_cast<double *>(data);
		break;
	case LooMetaType::QChar:
		stream >> *static_cast<NS (QChar)*>(data);
		break;
#ifndef LOO_BOOTSTRAPPED
	case LooMetaType::QVariantMap:
		stream >> *static_cast<NS (QVariantMap)*>(data);
		break;
	case LooMetaType::QVariantHash:
		stream >> *static_cast<NS (QVariantHash)*>(data);
		break;
	case LooMetaType::QVariantList:
		stream >> *static_cast<NS (QVariantList)*>(data);
		break;
	case LooMetaType::QVariant:
		stream >> *static_cast<NS (QVariant)*>(data);
		break;
	case LooMetaType::QByteArrayList:
		stream >> *static_cast<NS (QByteArrayList)*>(data);
		break;
#endif
	case LooMetaType::std::string:
		stream >> *static_cast<NS (std::string)*>(data);
		break;
	case LooMetaType::QString:
		stream >> *static_cast<NS (QString)*>(data);
		break;
	case LooMetaType::QStringList:
		stream >> *static_cast<NS (QStringList)*>(data);
		break;
#ifndef LOO_BOOTSTRAPPED
	case LooMetaType::QBitArray:
		stream >> *static_cast<NS (QBitArray)*>(data);
		break;
#endif
	case LooMetaType::QDate:
		stream >> *static_cast<NS (QDate)*>(data);
		break;
	case LooMetaType::QTime:
		stream >> *static_cast<NS (QTime)*>(data);
		break;
	case LooMetaType::QDateTime:
		stream >> *static_cast<NS (QDateTime)*>(data);
		break;
#ifndef LOO_BOOTSTRAPPED
	case LooMetaType::QUrl:
		stream >> *static_cast<NS (QUrl)*>(data);
		break;
#endif
	case LooMetaType::QLocale:
		stream >> *static_cast<NS (QLocale)*>(data);
		break;
#ifndef LOO_NO_GEOM_VARIANT
	case LooMetaType::QRect:
		stream >> *static_cast<NS (QRect)*>(data);
		break;
	case LooMetaType::QRectF:
		stream >> *static_cast<NS (QRectF)*>(data);
		break;
	case LooMetaType::QSize:
		stream >> *static_cast<NS (QSize)*>(data);
		break;
	case LooMetaType::QSizeF:
		stream >> *static_cast<NS (QSizeF)*>(data);
		break;
	case LooMetaType::QLine:
		stream >> *static_cast<NS (QLine)*>(data);
		break;
	case LooMetaType::QLineF:
		stream >> *static_cast<NS (QLineF)*>(data);
		break;
	case LooMetaType::QPoint:
		stream >> *static_cast<NS (QPoint)*>(data);
		break;
	case LooMetaType::QPointF:
		stream >> *static_cast<NS (QPointF)*>(data);
		break;
#endif
#ifndef LOO_NO_REGEXP
	case LooMetaType::QRegExp:
		stream >> *static_cast<NS (QRegExp)*>(data);
		break;
#endif
#ifndef LOO_BOOTSTRAPPED
#ifndef LOO_NO_REGULAREXPRESSION
	case LooMetaType::QRegularExpression:
		stream >> *static_cast<NS (QRegularExpression)*>(data);
		break;
#endif // LOO_NO_REGULAREXPRESSION
	case LooMetaType::QEasingCurve:
		stream >> *static_cast<NS (QEasingCurve)*>(data);
		break;
#endif // LOO_BOOTSTRAPPED
	case LooMetaType::QFont:
	case LooMetaType::QPixmap:
	case LooMetaType::QBrush:
	case LooMetaType::QColor:
	case LooMetaType::QPalette:
	case LooMetaType::QImage:
	case LooMetaType::QPolygon:
	case LooMetaType::QPolygonF:
	case LooMetaType::QRegion:
	case LooMetaType::QBitmap:
	case LooMetaType::QCursor:
	case LooMetaType::QKeySequence:
	case LooMetaType::QPen:
	case LooMetaType::QTextLength:
	case LooMetaType::QTextFormat:
	case LooMetaType::QMatrix:
	case LooMetaType::QTransform:
	case LooMetaType::QMatrix4x4:
	case LooMetaType::std::vector2D:
	case LooMetaType::std::vector3D:
	case LooMetaType::std::vector4D:
	case LooMetaType::QQuaternion:
	case LooMetaType::QIcon:
		if (!qMetaTypeGuiHelper)
			return false;
		qMetaTypeGuiHelper[type - FirstGuiType].loadOp (stream, data);
		break;
	case LooMetaType::QSizePolicy:
		if (!qMetaTypeWidgetsHelper)
			return false;
		qMetaTypeWidgetsHelper[type - FirstWidgetsType].loadOp (stream, data);
		break;
	case LooMetaType::QUuid:
		stream >> *static_cast<NS (QUuid)*>(data);
		break;
	default: {
		const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
		if (!ct)
			return false;

		LoadOperator loadOp = 0;
		{
			QReadLocker locker (customTypesLock ());
			loadOp = ct->at (type - User).loadOp;
		}

		if (!loadOp)
			return false;
		loadOp (stream, data);
		break; }
	}
	return true;
}
#endif // LOO_NO_DATASTREAM

/*!
	Returns a copy of \a copy, assuming it is of type \a type. If \a
	copy is zero, creates a default constructed instance.

	\sa destroy(), isRegistered(), Type
*/
void *LooMetaType::create (int type, const void *copy)
{
	LooMetaType info (type);
	if (int size = info.sizeOf ())
		return info.construct (operator new(size), copy);
	return 0;
}

/*!
	Destroys the \a data, assuming it is of the \a type given.

	\sa create(), isRegistered(), Type
*/
void LooMetaType::destroy (int type, void *data)
{
	LooMetaType info (type);
	info.destruct (data);
	operator delete(data);
}

namespace {
	class TypeConstructor {
		template<typename T, bool IsAcceptedType = DefinedTypesFilter::Acceptor<T>::IsAccepted>
		struct ConstructorImpl {
			static void *Construct (const int /*type*/, void *where, const void *copy) { return QtMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Construct (where, copy); }
		};
		template<typename T>
		struct ConstructorImpl<T, /* IsAcceptedType = */ false> {
			static void *Construct (const int type, void *where, const void *copy)
			{
				if (QModulesPrivate::QTypeModuleInfo<T>::IsGui)
					return LOO_LIKELY (qMetaTypeGuiHelper) ? qMetaTypeGuiHelper[type - LooMetaType::FirstGuiType].constructor (where, copy) : 0;

				if (QModulesPrivate::QTypeModuleInfo<T>::IsWidget)
					return LOO_LIKELY (qMetaTypeWidgetsHelper) ? qMetaTypeWidgetsHelper[type - LooMetaType::FirstWidgetsType].constructor (where, copy) : 0;

				// This point can be reached only for known types that definition is not available, for example
				// in bootstrap mode. We have no other choice then ignore it.
				return 0;
			}
		};
	public:
		TypeConstructor (const int type, void *where)
			: m_type (type)
			, m_where (where)
		{}

		template<typename T>
		void *delegate (const T *copy) { return ConstructorImpl<T>::Construct (m_type, m_where, copy); }
		void *delegate (const void *) { return m_where; }
		void *delegate (const LooMetaTypeSwitcher::UnknownType*) { return m_where; }
		void *delegate (const LooMetaTypeSwitcher::NotBuiltinType *copy) { return customTypeConstructor (m_type, m_where, copy); }

	private:
		static void *customTypeConstructor (const int type, void *where, const void *copy)
		{
			LooMetaType::Constructor ctor;
			const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
			{
				QReadLocker locker (customTypesLock ());
				if (LOO_UNLIKELY (type < LooMetaType::User || !ct || ct->count () <= type - LooMetaType::User))
					return 0;
				ctor = ct->at (type - LooMetaType::User).constructor;
			}
			LOO_ASSERT_X (ctor, "void *LooMetaType::construct(int type, void *where, const void *copy)", "The type was not properly registered");
			return ctor (where, copy);
		}

		const int m_type;
		void *m_where;
	};
} // namespace

/*!
	\since 5.0

	Constructs a value of the given \a type in the existing memory
	addressed by \a where, that is a copy of \a copy, and returns
	\a where. If \a copy is zero, the value is default constructed.

	This is a low-level function for explicitly managing the memory
	used to store the type. Consider calling create() if you don't
	need this level of control (that is, use "new" rather than
	"placement new").

	You must ensure that \a where points to a location that can store
	a value of type \a type, and that \a where is suitably aligned.
	The type's size can be queried by calling sizeOf().

	The rule of thumb for alignment is that a type is aligned to its
	natural boundary, which is the smallest power of 2 that is bigger
	than the type, unless that alignment is larger than the maximum
	useful alignment for the platform. For practical purposes,
	alignment larger than 2 * sizeof(void*) is only necessary for
	special hardware instructions (e.g., aligned SSE loads and stores
	on x86).

	\sa destruct(), sizeOf()
*/
void *LooMetaType::construct (int type, void *where, const void *copy)
{
	if (!where)
		return 0;
	TypeConstructor constructor (type, where);
	return LooMetaTypeSwitcher::switcher<void*> (constructor, type, copy);
}


namespace {
	class TypeDestructor {
		template<typename T, bool IsAcceptedType = DefinedTypesFilter::Acceptor<T>::IsAccepted>
		struct DestructorImpl {
			static void Destruct (const int /* type */, void *where) { QtMetaTypePrivate::LooMetaTypeFunctionHelper<T>::Destruct (where); }
		};
		template<typename T>
		struct DestructorImpl<T, /* IsAcceptedType = */ false> {
			static void Destruct (const int type, void *where)
			{
				if (QModulesPrivate::QTypeModuleInfo<T>::IsGui) {
					if (LOO_LIKELY (qMetaTypeGuiHelper))
						qMetaTypeGuiHelper[type - LooMetaType::FirstGuiType].destructor (where);
					return;
				}
				if (QModulesPrivate::QTypeModuleInfo<T>::IsWidget) {
					if (LOO_LIKELY (qMetaTypeWidgetsHelper))
						qMetaTypeWidgetsHelper[type - LooMetaType::FirstWidgetsType].destructor (where);
					return;
				}
				// This point can be reached only for known types that definition is not available, for example
				// in bootstrap mode. We have no other choice then ignore it.
			}
		};
	public:
		TypeDestructor (const int type)
			: m_type (type)
		{}

		template<typename T>
		void delegate (const T *where) { DestructorImpl<T>::Destruct (m_type, const_cast<T*>(where)); }
		void delegate (const void *) {}
		void delegate (const LooMetaTypeSwitcher::UnknownType*) {}
		void delegate (const LooMetaTypeSwitcher::NotBuiltinType *where)
		{
			customTypeDestructor (m_type, const_cast<void *>(static_cast<const void *>(where)));
		}

	private:
		static void customTypeDestructor (const int type, void *where)
		{
			LooMetaType::Destructor dtor;
			const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
			{
				QReadLocker locker (customTypesLock ());
				if (LOO_UNLIKELY (type < LooMetaType::User || !ct || ct->count () <= type - LooMetaType::User))
					return;
				dtor = ct->at (type - LooMetaType::User).destructor;
			}
			LOO_ASSERT_X (dtor, "void LooMetaType::destruct(int type, void *where)", "The type was not properly registered");
			dtor (where);
		}

		const int m_type;
	};
} // namespace

/*!
	\since 5.0

	Destructs the value of the given \a type, located at \a where.

	Unlike destroy(), this function only invokes the type's
	destructor, it doesn't invoke the delete operator.

	\sa construct()
*/
void LooMetaType::destruct (int type, void *where)
{
	if (!where)
		return;
	TypeDestructor destructor (type);
	LooMetaTypeSwitcher::switcher<void> (destructor, type, where);
}


namespace {
	class SizeOf {
		template<typename T, bool IsAcceptedType = DefinedTypesFilter::Acceptor<T>::IsAccepted>
		struct SizeOfImpl {
			static int Size (const int) { return QTypeInfo<T>::sizeOf; }
		};
		template<typename T>
		struct SizeOfImpl<T, /* IsAcceptedType = */ false> {
			static int Size (const int type)
			{
				if (QModulesPrivate::QTypeModuleInfo<T>::IsGui)
					return LOO_LIKELY (qMetaTypeGuiHelper) ? qMetaTypeGuiHelper[type - LooMetaType::FirstGuiType].size : 0;

				if (QModulesPrivate::QTypeModuleInfo<T>::IsWidget)
					return LOO_LIKELY (qMetaTypeWidgetsHelper) ? qMetaTypeWidgetsHelper[type - LooMetaType::FirstWidgetsType].size : 0;

				// This point can be reached only for known types that definition is not available, for example
				// in bootstrap mode. We have no other choice then ignore it.
				return 0;
			}
		};

	public:
		SizeOf (int type)
			: m_type (type)
		{}

		template<typename T>
		int delegate (const T*) { return SizeOfImpl<T>::Size (m_type); }
		int delegate (const LooMetaTypeSwitcher::UnknownType*) { return 0; }
		int delegate (const LooMetaTypeSwitcher::NotBuiltinType*) { return customTypeSizeOf (m_type); }
	private:
		static int customTypeSizeOf (const int type)
		{
			const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
			QReadLocker locker (customTypesLock ());
			if (LOO_UNLIKELY (type < LooMetaType::User || !ct || ct->count () <= type - LooMetaType::User))
				return 0;
			return ct->at (type - LooMetaType::User).size;
		}

		const int m_type;
	};
} // namespace

/*!
	\since 5.0

	Returns the size of the given \a type in bytes (i.e. sizeof(T),
	where T is the actual type identified by the \a type argument).

	This function is typically used together with construct()
	to perform low-level management of the memory used by a type.

	\sa construct()
*/
int LooMetaType::sizeOf (int type)
{
	SizeOf sizeOf (type);
	return LooMetaTypeSwitcher::switcher<int> (sizeOf, type, 0);
}

namespace {
	class Flags
	{
		template<typename T, bool IsAcceptedType = DefinedTypesFilter::Acceptor<T>::IsAccepted>
		struct FlagsImpl
		{
			static quint32 Flags (const int /* type */)
			{
				return LooPrivate::LooMetaTypeTypeFlags<T>::Flags;
			}
		};
		template<typename T>
		struct FlagsImpl<T, /* IsAcceptedType = */ false>
		{
			static quint32 Flags (const int type)
			{
				if (QModulesPrivate::QTypeModuleInfo<T>::IsGui)
					return LOO_LIKELY (qMetaTypeGuiHelper) ? qMetaTypeGuiHelper[type - LooMetaType::FirstGuiType].flags : 0;

				if (QModulesPrivate::QTypeModuleInfo<T>::IsWidget)
					return LOO_LIKELY (qMetaTypeWidgetsHelper) ? qMetaTypeWidgetsHelper[type - LooMetaType::FirstWidgetsType].flags : 0;

				// This point can be reached only for known types that definition is not available, for example
				// in bootstrap mode. We have no other choice then ignore it.
				return 0;
			}
		};
	public:
		Flags (const int type)
			: m_type (type)
		{}
		template<typename T>
		quint32 delegate (const T*) { return FlagsImpl<T>::Flags (m_type); }
		quint32 delegate (const void*) { return 0; }
		quint32 delegate (const LooMetaTypeSwitcher::UnknownType*) { return 0; }
		quint32 delegate (const LooMetaTypeSwitcher::NotBuiltinType*) { return customTypeFlags (m_type); }
	private:
		const int m_type;
		static quint32 customTypeFlags (const int type)
		{
			const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
			if (LOO_UNLIKELY (!ct || type < LooMetaType::User))
				return 0;
			QReadLocker locker (customTypesLock ());
			if (LOO_UNLIKELY (ct->count () <= type - LooMetaType::User))
				return 0;
			return ct->at (type - LooMetaType::User).flags;
		}
	};
}  // namespace

/*!
	\since 5.0

	Returns flags of the given \a type.

	\sa LooMetaType::TypeFlags
*/
LooMetaType::TypeFlags LooMetaType::typeFlags (int type)
{
	Flags flags (type);
	return static_cast<LooMetaType::TypeFlags>(LooMetaTypeSwitcher::switcher<quint32> (flags, type, 0));
}

#ifndef LOO_BOOTSTRAPPED
namespace {
	class MetaObject
	{
	public:
		MetaObject (const int type)
			: m_type (type)
		{}

		template<typename T, bool IsAcceptedType = DefinedTypesFilter::Acceptor<T>::IsAccepted>
		struct MetaObjectImpl
		{
			static const LooMetaObject *MetaObject (int /*type*/)
			{
				return LooPrivate::MetaObjectForType<T>::value ();
			}
		};
		template<typename T>
		struct MetaObjectImpl<T, /* IsAcceptedType = */ false>
		{
			static const LooMetaObject *MetaObject (int type) {
				if (QModulesPrivate::QTypeModuleInfo<T>::IsGui)
					return LOO_LIKELY (qMetaTypeGuiHelper) ? qMetaTypeGuiHelper[type - LooMetaType::FirstGuiType].metaObject : 0;
				if (QModulesPrivate::QTypeModuleInfo<T>::IsWidget)
					return LOO_LIKELY (qMetaTypeWidgetsHelper) ? qMetaTypeWidgetsHelper[type - LooMetaType::FirstWidgetsType].metaObject : 0;
				return 0;
			}
		};

		template <typename T>
		const LooMetaObject *delegate (const T *) { return MetaObjectImpl<T>::MetaObject (m_type); }
		const LooMetaObject *delegate (const void*) { return 0; }
		const LooMetaObject *delegate (const LooMetaTypeSwitcher::UnknownType*) { return 0; }
		const LooMetaObject *delegate (const LooMetaTypeSwitcher::NotBuiltinType*) { return customMetaObject (m_type); }
	private:
		const int m_type;
		static const LooMetaObject *customMetaObject (const int type)
		{
			const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
			if (LOO_UNLIKELY (!ct || type < LooMetaType::User))
				return 0;
			QReadLocker locker (customTypesLock ());
			if (LOO_UNLIKELY (ct->count () <= type - LooMetaType::User))
				return 0;
			return ct->at (type - LooMetaType::User).metaObject;
		}
	};
}  // namespace
#endif

/*!
	\since 5.0

	returns LooMetaType::metaObject for \a type

	\sa metaObject()
*/
const LooMetaObject *LooMetaType::metaObjectForType (int type)
{
#ifndef LOO_BOOTSTRAPPED
	MetaObject mo (type);
	return LooMetaTypeSwitcher::switcher<const LooMetaObject*> (mo, type, 0);
#else
	LOO_UNUSED (type);
	return 0;
#endif
}

/*!
	\fn int qRegisterMetaType(const char *typeName)
	\relates LooMetaType
	\threadsafe

	Registers the type name \a typeName for the type \c{T}. Returns
	the internal ID used by LooMetaType. Any class or struct that has a
	public default constructor, a public copy constructor and a public
	destructor can be registered.

	This function requires that \c{T} is a fully defined type at the point
	where the function is called. For pointer types, it also requires that the
	pointed to type is fully defined. Use LOO_DECLARE_OPAQUE_POINTER() to be able
	to register pointers to forward declared types.

	After a type has been registered, you can create and destroy
	objects of that type dynamically at run-time.

	This example registers the class \c{MyClass}:

	\snippet code/src_corelib_kernel_qmetatype.cpp 4

	This function is useful to register typedefs so they can be used
	by QMetaProperty, or in QueuedConnections

	\snippet code/src_corelib_kernel_qmetatype.cpp 9

	\warning This function is useful only for registering an alias (typedef)
	for every other use case LOO_DECLARE_METATYPE and qMetaTypeId() should be used instead.

	\sa {LooMetaType::}{qRegisterMetaTypeStreamOperators()}, {LooMetaType::}{isRegistered()},
		LOO_DECLARE_METATYPE()
*/

/*!
	\fn void qRegisterMetaTypeStreamOperators(const char *typeName)
	\relates LooMetaType
	\threadsafe

	Registers the stream operators for the type \c{T} called \a
	typeName.

	Afterward, the type can be streamed using LooMetaType::load() and
	LooMetaType::save(). These functions are used when streaming a
	QVariant.

	\snippet code/src_corelib_kernel_qmetatype.cpp 5

	The stream operators should have the following signatures:

	\snippet code/src_corelib_kernel_qmetatype.cpp 6

	\sa qRegisterMetaType(), LooMetaType::isRegistered(), LOO_DECLARE_METATYPE()
*/

/*! \typedef LooMetaType::Deleter
	\internal
*/
/*! \typedef LooMetaType::Creator
	\internal
*/
/*! \typedef LooMetaType::SaveOperator
	\internal
*/
/*! \typedef LooMetaType::LoadOperator
	\internal
*/
/*! \typedef LooMetaType::Destructor
	\internal
*/
/*! \typedef LooMetaType::Constructor
	\internal
*/

/*!
	\fn int qRegisterMetaType()
	\relates LooMetaType
	\threadsafe
	\since 4.2

	Call this function to register the type \c T. \c T must be declared with
	LOO_DECLARE_METATYPE(). Returns the meta type Id.

	Example:

	\snippet code/src_corelib_kernel_qmetatype.cpp 7

	This function requires that \c{T} is a fully defined type at the point
	where the function is called. For pointer types, it also requires that the
	pointed to type is fully defined. Use LOO_DECLARE_OPAQUE_POINTER() to be able
	to register pointers to forward declared types.

	After a type has been registered, you can create and destroy
	objects of that type dynamically at run-time.

	To use the type \c T in QVariant, using LOO_DECLARE_METATYPE() is
	sufficient. To use the type \c T in queued signal and slot connections,
	\c{qRegisterMetaType<T>()} must be called before the first connection
	is established.

	Also, to use type \c T with the QObject::property() API,
	\c{qRegisterMetaType<T>()} must be called before it is used, typically
	in the constructor of the class that uses \c T, or in the \c{main()}
	function.

	\sa LOO_DECLARE_METATYPE()
 */

 /*!
	 \fn int qMetaTypeId()
	 \relates LooMetaType
	 \threadsafe
	 \since 4.1

	 Returns the meta type id of type \c T at compile time. If the
	 type was not declared with LOO_DECLARE_METATYPE(), compilation will
	 fail.

	 Typical usage:

	 \snippet code/src_corelib_kernel_qmetatype.cpp 8

	 LooMetaType::type() returns the same ID as qMetaTypeId(), but does
	 a lookup at runtime based on the name of the type.
	 LooMetaType::type() is a bit slower, but compilation succeeds if a
	 type is not registered.

	 \sa LOO_DECLARE_METATYPE(), LooMetaType::type()
 */

namespace {
	class TypeInfo {
		template<typename T, bool IsAcceptedType = DefinedTypesFilter::Acceptor<T>::IsAccepted>
		struct TypeInfoImpl
		{
			TypeInfoImpl (const uint /* type */, LooMetaTypeInterface &info)
			{
				LooMetaTypeInterface tmp = LOO_METATYPE_INTERFACE_INIT_NO_DATASTREAM (T);
				info = tmp;
			}
		};

		template<typename T>
		struct TypeInfoImpl<T, /* IsAcceptedType = */ false>
		{
			TypeInfoImpl (const uint type, LooMetaTypeInterface &info)
			{
				if (QModulesPrivate::QTypeModuleInfo<T>::IsGui) {
					if (LOO_LIKELY (qMetaTypeGuiHelper))
						info = qMetaTypeGuiHelper[type - LooMetaType::FirstGuiType];
					return;
				}
				if (QModulesPrivate::QTypeModuleInfo<T>::IsWidget) {
					if (LOO_LIKELY (qMetaTypeWidgetsHelper))
						info = qMetaTypeWidgetsHelper[type - LooMetaType::FirstWidgetsType];
					return;
				}
			}
		};
	public:
		LooMetaTypeInterface info;
		TypeInfo (const uint type)
			: m_type (type)
		{
			LooMetaTypeInterface tmp = LOO_METATYPE_INTERFACE_INIT_EMPTY ();
			info = tmp;
		}
		template<typename T>
		void delegate (const T*) { TypeInfoImpl<T> (m_type, info); }
		void delegate (const LooMetaTypeSwitcher::UnknownType*) {}
		void delegate (const LooMetaTypeSwitcher::NotBuiltinType*) { customTypeInfo (m_type); }
	private:
		void customTypeInfo (const uint type)
		{
			const std::vector<LooCustomTypeInfo> * const ct = customTypes ();
			if (LOO_UNLIKELY (!ct))
				return;
			QReadLocker locker (customTypesLock ());
			if (LOO_LIKELY (uint (ct->count ()) > type - LooMetaType::User))
				info = ct->at (type - LooMetaType::User);
		}

		const uint m_type;
	};
} // namespace

/*!
	\fn LooMetaType LooMetaType::typeInfo(const int type)
	\internal
*/
LooMetaType LooMetaType::typeInfo (const int type)
{
	TypeInfo typeInfo (type);
	LooMetaTypeSwitcher::switcher<void> (typeInfo, type, 0);
	return typeInfo.info.constructor ? LooMetaType (static_cast<ExtensionFlag>(LooMetaType::CreateEx | LooMetaType::DestroyEx)
		, static_cast<const LooMetaTypeInterface *>(0) // typeInfo::info is a temporary variable, we can't return address of it.
		, 0 // unused
		, 0 // unused
		, typeInfo.info.saveOp
		, typeInfo.info.loadOp
		, typeInfo.info.constructor
		, typeInfo.info.destructor
		, typeInfo.info.size
		, typeInfo.info.flags
		, type
		, typeInfo.info.metaObject)
		: LooMetaType (UnknownType);
}

/*!
	 \fn LooMetaType::LooMetaType(const int typeId)
	 \since 5.0

	 Constructs a LooMetaType object that contains all information about type \a typeId.
*/
LooMetaType::LooMetaType (const int typeId)
	: m_typeId (typeId)
{
	if (LOO_UNLIKELY (typeId == UnknownType)) {
		// Constructs invalid LooMetaType instance.
		m_extensionFlags = 0xffffffff;
		LOO_ASSERT (!isValid ());
	}
	else {
		// TODO it can be better.
		*this = LooMetaType::typeInfo (typeId);
		if (m_typeId == UnknownType)
			m_extensionFlags = 0xffffffff;
		else if (m_typeId == LooMetaType::Void)
			m_extensionFlags = CreateEx | DestroyEx | ConstructEx | DestructEx;
	}
}

/*!
	 \fn LooMetaType::LooMetaType(const LooMetaType &other)
	 \since 5.0

	 Copy constructs a LooMetaType object.
*/
LooMetaType::LooMetaType (const LooMetaType &other)
	: m_creator_unused (other.m_creator_unused)
	, m_deleter_unused (other.m_deleter_unused)
	, m_saveOp (other.m_saveOp)
	, m_loadOp (other.m_loadOp)
	, m_constructor (other.m_constructor)
	, m_destructor (other.m_destructor)
	, m_extension (other.m_extension) // space reserved for future use
	, m_size (other.m_size)
	, m_typeFlags (other.m_typeFlags)
	, m_extensionFlags (other.m_extensionFlags)
	, m_typeId (other.m_typeId)
	, m_metaObject (other.m_metaObject)
{}

LooMetaType &LooMetaType::operator =(const LooMetaType &other)
{
	m_creator_unused = other.m_creator_unused;
	m_deleter_unused = other.m_deleter_unused;
	m_saveOp = other.m_saveOp;
	m_loadOp = other.m_loadOp;
	m_constructor = other.m_constructor;
	m_destructor = other.m_destructor;
	m_size = other.m_size;
	m_typeFlags = other.m_typeFlags;
	m_extensionFlags = other.m_extensionFlags;
	m_extension = other.m_extension; // space reserved for future use
	m_typeId = other.m_typeId;
	m_metaObject = other.m_metaObject;
	return *this;
}

/*!
	\fn void LooMetaType::ctor(const LooMetaTypeInterface *info)
	\internal

	Method used for future binary compatible extensions.  The function may be
	called from within LooMetaType's constructor to force a library call from
	inlined code.
*/
void LooMetaType::ctor (const LooMetaTypeInterface *info)
{
	// Special case for Void type, the type is valid but not constructible.
	// In future we may consider to remove this assert and extend this function to initialize
	// differently m_extensionFlags for different types. Currently it is not needed.
	LOO_ASSERT (m_typeId == LooMetaType::Void);
	LOO_UNUSED (info);
	m_extensionFlags = CreateEx | DestroyEx | ConstructEx | DestructEx;
}

/*!
	\fn void LooMetaType::dtor()
	\internal

	Method used for future binary compatible extensions.  The function may be
	called from within LooMetaType's destructor to force a library call from
	inlined code.
*/
void LooMetaType::dtor ()
{}

/*!
	\fn void *LooMetaType::createExtended(const void *copy) const
	\internal

	Method used for future binary compatible extensions. The function may be called
	during LooMetaType::create to force library call from inlined code.

	### TODO Qt6 remove the extension
*/
void *LooMetaType::createExtended (const void *copy) const
{
	if (m_typeId == LooMetaType::UnknownType)
		return 0;
	return m_constructor (operator new(m_size), copy);
}

/*!
	\fn void LooMetaType::destroyExtended(void *data) const
	\internal

	Method used for future binary compatible extensions. The function may be called
	during LooMetaType::destroy to force library call from inlined code.

	### TODO Qt6 remove the extension
*/
void LooMetaType::destroyExtended (void *data) const
{
	m_destructor (data);
	operator delete(data);
}

/*!
	\fn void *LooMetaType::constructExtended(void *where, const void *copy) const
	\internal

	Method used for future binary compatible extensions. The function may be called
	during LooMetaType::construct to force library call from inlined code.
*/
void *LooMetaType::constructExtended (void *where, const void *copy) const
{
	LOO_UNUSED (where);
	LOO_UNUSED (copy);
	return 0;
}

/*!
	\fn void LooMetaType::destructExtended(void *data) const
	\internal

	Method used for future binary compatible extensions. The function may be called
	during LooMetaType::destruct to force library call from inlined code.
*/
void LooMetaType::destructExtended (void *data) const
{
	LOO_UNUSED (data);
}

/*!
	\fn uint LooMetaType::sizeExtended() const
	\internal

	Method used for future binary compatible extensions. The function may be
	called from within LooMetaType::size to force a library call from
	inlined code.
*/
uint LooMetaType::sizeExtended () const
{
	return 0;
}

/*!
	\fn LooMetaType::TypeFlags LooMetaType::flagsExtended() const
	\internal

	Method used for future binary compatible extensions.  The function may be
	called from within LooMetaType::flags to force a library call from
	inlined code.
*/
LooMetaType::TypeFlags LooMetaType::flagsExtended () const
{
	return 0;
}

/*!
	\brief LooMetaType::metaObjectExtended
	\internal

	Method used for future binary compatible extensions. The function may be
	called from within LooMetaType::metaObject to force a library call from
	inlined code.
*/
const LooMetaObject *LooMetaType::metaObjectExtended () const
{
	return 0;
}


namespace LooPrivate
{
	const LooMetaObject *metaObjectForQWidget ()
	{
		if (!qMetaTypeWidgetsHelper)
			return 0;
		return qMetaObjectWidgetsHelper;
	}
}

namespace QtMetaTypePrivate {
	const bool VectorBoolElements::true_element = true;
	const bool VectorBoolElements::false_element = false;
}

}
#endif