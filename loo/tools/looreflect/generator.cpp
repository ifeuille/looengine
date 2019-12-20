#include "generator.h"
#include "outputrevision.h"
#include "utils.h"
//#include <LooCore/loometatype.h>

#include "nlohmann/json.hpp"
#include <stdio.h>
//#include <LooCore/loometaobject.h>
#include <algorithm>

#include <Private/loometaobject_p.h>

namespace loo
{
#define LOO_DEFINE_METATYPE_ID(TypeName, Id, Name) \
    TypeName = Id,

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
    F(Nullptr, 51, std::nullptr_t) 

#define LOO_FOR_EACH_STATIC_TYPE(F)\
    LOO_FOR_EACH_STATIC_PRIMITIVE_TYPE(F)

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

#define LOO_ADD_STATIC_METATYPE(MetaTypeName, MetaTypeId, RealName) \
    { #RealName, sizeof(#RealName) - 1, MetaTypeId },
#define LOO_ADD_STATIC_METATYPE_ALIASES_ITER(MetaTypeName, MetaTypeId, AliasingName, RealNameStr) \
    { RealNameStr, sizeof(RealNameStr) - 1, LooMetaType::MetaTypeName },

	
	struct LooMetaType {
		enum Type {
			// these are merged with LooVariant
			LOO_FOR_EACH_STATIC_TYPE (LOO_DEFINE_METATYPE_ID)

			FirstCoreType = Bool,
			LastCoreType = Nullptr,

			QReal = sizeof (double) == sizeof (double) ? Double : Float,

			UnknownType = 0,
			User = 1024
		};

		static int type (const char *typeName);
	};

	static const struct { const char * typeName; int typeNameLength; int type; } types[] = {
		LOO_FOR_EACH_STATIC_TYPE (LOO_ADD_STATIC_METATYPE)
		LOO_FOR_EACH_STATIC_ALIAS_TYPE (LOO_ADD_STATIC_METATYPE_ALIASES_ITER)
		//LOO_FOR_EACH_STATIC_HACKS_TYPE (LOO_ADD_STATIC_METATYPE_HACKS_ITER)
		{
		0, 0, LooMetaType::UnknownType
		}
	};
	static inline int qMetaTypeStaticType (const char *typeName, int length)
	{
		int i = 0;
		while (types[i].typeName && ((length != types[i].typeNameLength)
			|| memcmp (typeName, types[i].typeName, length))) {
			++i;
		}
		return types[i].type;
	}

	int LooMetaType::type (const char *typeName)
	{
		return qMetaTypeStaticType (typeName, strlen (typeName));
	}



	//enum MetaObjectFlags {
	//	DynamicMetaObject = 0x01,
	//	RequiresVariantMetaObject = 0x02,
	//	PropertyAccessInStaticMetaCall = 0x04 // since Qt 5.5, property code is in the static metacall
	//};

	//enum { MetaObjectPrivateFieldCount = 64 / sizeof (int) };

}

namespace loo
{

	std::uint32_t nameToBuiltinType (const std::string &name)
	{
		if (name.empty ())
			return 0;

		std::uint32_t tp = qMetaTypeStaticType (name.data (), name.length ());//LooMetaType::type (name.data ());//获取内置类型的ID非内置类型应该是运行是注册的
		return tp < std::uint32_t (LooMetaType::User) ? tp : std::uint32_t (LooMetaType::UnknownType);
	}


	/*
	  Returns \c true if the type is a built-in type.
	*/
	bool isBuiltinType (const std::string &type)
	{
		int id = LooMetaType::type (type.data ());
		if (id == LooMetaType::UnknownType)
			return false;
		return (id < LooMetaType::User);
	}

	static const char *metaTypeEnumValueString (int type)
	{
#define RETURN_METATYPENAME_STRING(MetaTypeName, MetaTypeId, RealType) \
    case LooMetaType::MetaTypeName: return #MetaTypeName;

		switch (type) {
			LOO_FOR_EACH_STATIC_TYPE (RETURN_METATYPENAME_STRING)
		}
#undef RETURN_METATYPENAME_STRING
		return 0;
	}

	Generator::Generator (
		ClassDef *classDef, 
		const std::vector<QByteArray> &metaTypes, 
		const std::unordered_map<QByteArray, QByteArray> &knownLooObjectClasses, 
		const std::unordered_map<QByteArray, QByteArray> &knownGadgets, FILE *outfile)
		: out (outfile), 
		cdef (classDef), 
		metaTypes (metaTypes), 
		knownLooObjectClasses (knownLooObjectClasses), 
		knownGadgets (knownGadgets)
	{
		if (cdef->superclassList.size ())
			purestSuperClass = cdef->superclassList.begin ()->first;
	}
		
	static inline int lengthOfEscapeSequence (const QByteArray &s, int i)
	{
		if (s.at (i) != '\\' || i >= s.length () - 1)
			return 1;
		const int startPos = i;
		++i;
		char ch = s.at (i);
		if (ch == 'x') {
			++i;
			while (i < s.length () && is_hex_char (s.at (i)))
				++i;
		}
		else if (is_octal_char (ch)) {
			while (i < startPos + 4
				&& i < s.length ()
				&& is_octal_char (s.at (i))) {
				++i;
			}
		}
		else { // single character escape sequence
			i = std::min (i + 1, (int)s.length ());
		}
		return i - startPos;
	}

	void Generator::strreg (const QByteArray &s)
	{
		if (std::find (strings.begin (), strings.end (), s) != strings.end ())
		{
			strings.push_back (s);
		}
	}

	int Generator::stridx (const QByteArray &s)
	{
		int i = GetIndexOf (strings, s);
		assert (i != -1&& "We forgot to register some strings");
		return i;
	}

	// Returns the sum of all parameters (including return type) for the given
	// \a list of methods. This is needed for calculating the size of the methods'
	// parameter type/name meta-data.
	static int aggregateParameterCount (const std::vector<FunctionDef> &list)
	{
		int sum = 0;
		for (int i = 0; i < list.size (); ++i)
			sum += list.at (i).arguments.size () + 1; // +1 for return type
		return sum;
	}

	bool Generator::registerableMetaType (const QByteArray &propertyType)
	{
		if (container_contains (metaTypes, propertyType))
		{
			return true;
		}
		if(string_endwith(propertyType,'*')){
			QByteArray objectPointerType = propertyType;
			// The objects container stores class names, such as 'QState', 'QLabel' etc,
			// not 'QState*', 'QLabel*'. The propertyType does contain the '*', so we need
			// to chop it to find the class type in the known LooObjects list.
			container_chop (objectPointerType, 1);
			if (knownLooObjectClasses.find (objectPointerType) != knownLooObjectClasses.end ())
				return true;
		}
		static const std::vector<QByteArray> smartPointers = std::vector<QByteArray> ()
			//只能指针
//#define STREAM_SMART_POINTER(SMART_POINTER) << #SMART_POINTER
//			LOO_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER (STREAM_SMART_POINTER)
//#undef STREAM_SMART_POINTER
			;

		for (const QByteArray &smartPointer : smartPointers) {
			if (string_startwith (propertyType, smartPointer + "<") && !string_endwith (propertyType, "&"))
			{
				return knownLooObjectClasses.find (propertyType.substr (smartPointer.size () + 1, propertyType.size () - smartPointer.size () - 1 - 1)) != knownLooObjectClasses.end ();
			}		
		}
		//模板
		static const std::vector<QByteArray> oneArgTemplates = std::vector<QByteArray> ()
//#define STREAM_1ARG_TEMPLATE(TEMPLATENAME) << #TEMPLATENAME
//			LOO_FOR_EACH_AUTOMATIC_TEMPLATE_1ARG (STREAM_1ARG_TEMPLATE)
//#undef STREAM_1ARG_TEMPLATE
			;
		for (const QByteArray &oneArgTemplateType : oneArgTemplates) {
			if (string_startwith (propertyType, oneArgTemplateType + "<") && string_endwith (propertyType, ">")){
				const int argumentSize = propertyType.size () - oneArgTemplateType.size () - 1
					// The closing '>'
					- 1
					// templates inside templates have an extra whitespace char to strip.
					- (propertyType.at (propertyType.size () - 2) == ' ' ? 1 : 0);
				const QByteArray templateArg = propertyType.substr (oneArgTemplateType.size () + 1, argumentSize);
				return isBuiltinType (templateArg) || registerableMetaType (templateArg);
			}
		}
		return false;
	}

	/* returns \c true if name and qualifiedName refers to the same name.
	 * If qualified name is "A::B::C", it returns \c true for "C", "B::C" or "A::B::C" */
	static bool qualifiedNameEquals (const QByteArray &qualifiedName, const QByteArray &name)
	{
		if (qualifiedName == name)
			return true;
		int index = string_indexof (qualifiedName,"::");
		if (index == -1)
			return false;
		return qualifiedNameEquals (qualifiedName.substr (index + 2), name);
	}

	//core
	void Generator::generateCode ()
	{
		bool isQt = (cdef->classname == "Loo");
		bool isLooObject = (cdef->classname == "LooObject");
		bool isConstructible = !cdef->constructorList.empty ();

		// filter out undeclared enumerators and sets
		{
			std::vector<EnumDef> enumList;
			for (int i = 0; i < cdef->enumList.size (); ++i) {
				EnumDef def = cdef->enumList.at (i);
				if (cdef->enumDeclarations.find (def.name) != cdef->enumDeclarations.end()) {
					enumList.push_back(def);
				}
				QByteArray alias;
				if (cdef->flagAliases.find (def.name) != cdef->flagAliases.end ()){
					alias = cdef->flagAliases[def.name];
				}
				if (cdef->enumDeclarations.find (alias) != cdef->enumDeclarations.end()) {
					def.name = alias;
					enumList.push_back(def);
				}
			}
			cdef->enumList = enumList;
		}

		//
		// Register all strings used in data section
		//
		strreg (cdef->qualified);
		registerClassInfoStrings ();
		registerFunctionStrings (cdef->signalList);
		registerFunctionStrings (cdef->slotList);
		registerFunctionStrings (cdef->methodList);
		registerFunctionStrings (cdef->constructorList);
		registerPropertyStrings ();
		registerEnumStrings ();

		QByteArray qualifiedClassNameIdentifier = cdef->qualified;
		string_relace_all (qualifiedClassNameIdentifier, ':', '_');

		//
		// Build stringdata struct
		//
		const int constCharArraySizeLimit = 65535;
		fprintf (out, "struct loo_meta_stringdata_%s_t {\n", qualifiedClassNameIdentifier.data ());
		fprintf (out, "    LooByteArrayData data[%d];\n", strings.size ());
		{
			int stringDataLength = 0;
			int stringDataCounter = 0;
			for (int i = 0; i < strings.size (); ++i) {
				int thisLength = strings.at (i).length () + 1;
				stringDataLength += thisLength;
				if (stringDataLength / constCharArraySizeLimit) {
					// save previous stringdata and start computing the next one.
					fprintf (out, "    char stringdata%d[%d];\n", stringDataCounter++, stringDataLength - thisLength);
					stringDataLength = thisLength;
				}
			}
			fprintf (out, "    char stringdata%d[%d];\n", stringDataCounter, stringDataLength);

		}
		fprintf (out, "};\n");

		// Macro that expands into a QByteArrayData. The offset member is
		// calculated from 1) the offset of the actual characters in the
		// stringdata.stringdata member, and 2) the stringdata.data index of the
		// QByteArrayData being defined. This calculation relies on the
		// QByteArrayData::data() implementation returning simply "this + offset".
		fprintf (out, "#define LOO_REFLECT_LITERAL(idx, ofs, len) \\\n"
			"    LOO_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \\\n"
			"    lptrdiff(offsetof(loo_meta_stringdata_%s_t, stringdata0) + ofs \\\n"
			"        - idx * sizeof(LooByteArrayData)) \\\n"
			"    )\n",
			qualifiedClassNameIdentifier.data ());

		fprintf (out, "static const loo_meta_stringdata_%s_t loo_meta_stringdata_%s = {\n",
			qualifiedClassNameIdentifier.data (), qualifiedClassNameIdentifier.data ());
		fprintf (out, "    {\n");
		{
			int idx = 0;
			for (int i = 0; i < strings.size (); ++i) {
				const QByteArray &str = strings.at (i);
				fprintf (out, "LOO_REFLECT_LITERAL(%d, %d, %d)", i, idx, str.length ());
				if (i != strings.size () - 1)
					fputc (',', out);
				const QByteArray comment = str.length () > 32 ? string_left(str,29) + "..." : str;
				fprintf (out, " // \"%s\"\n", comment.data ());
				idx += str.length () + 1;
				for (int j = 0; j < str.length (); ++j) {
					if (str.at (j) == '\\') {
						int cnt = lengthOfEscapeSequence (str, j) - 1;
						idx -= cnt;
						j += cnt;
					}
				}
			}
			fprintf (out, "\n    },\n");
		}

		//
		// Build stringdata array
		//
		fprintf (out, "    \"");
		int col = 0;
		int len = 0;
		int stringDataLength = 0;
		for (int i = 0; i < strings.size (); ++i) {
			QByteArray s = strings.at (i);
			len = s.length ();
			stringDataLength += len + 1;
			if (stringDataLength >= constCharArraySizeLimit) {
				fprintf (out, "\",\n    \"");
				stringDataLength = len + 1;
				col = 0;
			}
			else if (i)
				fputs ("\\0", out); // add \0 at the end of each string

			if (col && col + len >= 72) {
				fprintf (out, "\"\n    \"");
				col = 0;
			}
			else if (len && s.at (0) >= '0' && s.at (0) <= '9') {
				fprintf (out, "\"\"");
				len += 2;
			}
			int idx = 0;
			while (idx < s.length ()) {
				if (idx > 0) {
					col = 0;
					fprintf (out, "\"\n    \"");
				}
				int spanLen = std::min (70, (int)s.length () - idx);
				// don't cut escape sequences at the end of a line
				int backSlashPos = s.find_last_of ('\\', idx + spanLen - 1);
				if (backSlashPos >= idx) {
					int escapeLen = lengthOfEscapeSequence (s, backSlashPos);
					spanLen = v_clamp<int> (spanLen, backSlashPos + escapeLen - idx, s.length () - idx);
				}
				fprintf (out, "%.*s", spanLen, s.data () + idx);
				idx += spanLen;
				col += spanLen;
			}
			col += len + 2;
		}

		// Terminate stringdata struct
		fprintf (out, "\"\n};\n");
		fprintf (out, "#undef LOO_MOC_LITERAL\n\n");

		//
		// build the data array
		//

		int index = MetaObjectPrivateFieldCount;
		fprintf (out, "static const std::uint32_t loo_meta_data_%s[] = {\n", qualifiedClassNameIdentifier.data ());
		fprintf (out, "\n // content:\n");
		fprintf (out, "    %4d,       // revision\n", int (7));
		fprintf (out, "    %4d,       // classname\n", stridx (cdef->qualified));
		fprintf (out, "    %4d, %4d, // classinfo\n", cdef->classInfoList.size (), cdef->classInfoList.size () ? index : 0);
		index += cdef->classInfoList.size () * 2;

		int methodCount = cdef->signalList.size () + cdef->slotList.size () + cdef->methodList.size ();
		fprintf (out, "    %4d, %4d, // methods\n", methodCount, methodCount ? index : 0);
		index += methodCount * 5;
		if (cdef->revisionedMethods)
			index += methodCount;
		int paramsIndex = index;
		int totalParameterCount = aggregateParameterCount (cdef->signalList)
			+ aggregateParameterCount (cdef->slotList)
			+ aggregateParameterCount (cdef->methodList)
			+ aggregateParameterCount (cdef->constructorList);
		index += totalParameterCount * 2 // types and parameter names
			- methodCount // return "parameters" don't have names
			- cdef->constructorList.size (); // "this" parameters don't have names

		fprintf (out, "    %4d, %4d, // properties\n", cdef->propertyList.size(), cdef->propertyList.size() ? index : 0);
		index += cdef->propertyList.size () * 3;
		if (cdef->notifyableProperties)
			index += cdef->propertyList.size();
		if (cdef->revisionedProperties)
			index += cdef->propertyList.size();
		fprintf (out, "    %4d, %4d, // enums/sets\n", cdef->enumList.size(), cdef->enumList.size() ? index : 0);

		int enumsIndex = index;
		for (int i = 0; i < cdef->enumList.size(); ++i)
			index += 4 + (cdef->enumList.at (i).values.size() * 2);
		fprintf (out, "    %4d, %4d, // constructors\n", isConstructible ? cdef->constructorList.size() : 0,
			isConstructible ? index : 0);

		int flags = 0;
		if (cdef->hasLooGadget) {
			// Ideally, all the classes could have that flag. But this broke classes generated
			// by qdbusxml2cpp which generate code that require that we call loo_metacall for properties
			flags |= PropertyAccessInStaticMetaCall;
		}
		fprintf (out, "    %4d,       // flags\n", flags);
		fprintf (out, "    %4d,       // signalCount\n", cdef->signalList.size());


		//
		// Build classinfo array
		//
		generateClassInfos ();

		//
		// Build signals array first, otherwise the signal indices would be wrong
		//
		generateFunctions (cdef->signalList, "signal", MethodSignal, paramsIndex);

		//
		// Build slots array
		//
		generateFunctions (cdef->slotList, "slot", MethodSlot, paramsIndex);

		//
		// Build method array
		//
		generateFunctions (cdef->methodList, "method", MethodMethod, paramsIndex);

		//
		// Build method version arrays
		//
		if (cdef->revisionedMethods) {
			generateFunctionRevisions (cdef->signalList, "signal");
			generateFunctionRevisions (cdef->slotList, "slot");
			generateFunctionRevisions (cdef->methodList, "method");
		}

		//
		// Build method parameters array
		//
		generateFunctionParameters (cdef->signalList, "signal");
		generateFunctionParameters (cdef->slotList, "slot");
		generateFunctionParameters (cdef->methodList, "method");
		if (isConstructible)
			generateFunctionParameters (cdef->constructorList, "constructor");

		//
		// Build property array
		//
		generateProperties ();

		//
		// Build enums array
		//
		generateEnums (enumsIndex);

		//
		// Build constructors array
		//
		if (isConstructible)
			generateFunctions (cdef->constructorList, "constructor", MethodConstructor, paramsIndex);

		//
		// Terminate data array
		//
		fprintf (out, "\n       0        // eod\n};\n\n");

		//
		// Generate internal loo_static_metacall() function
		//
		const bool hasStaticMetaCall = !isQt &&
			(cdef->hasLooObject || !cdef->methodList.empty ()
				|| !cdef->propertyList.empty () || !cdef->constructorList.empty ());
		if (hasStaticMetaCall)
			generateStaticMetacall ();

		//
		// Build extra array
		//
		std::vector<QByteArray> extraList;
		std::unordered_map<QByteArray, QByteArray> knownExtraMetaObject = knownGadgets;
		knownExtraMetaObject.insert(knownLooObjectClasses.begin(), knownLooObjectClasses.end());

		for (int i = 0; i < cdef->propertyList.size(); ++i) {
			const PropertyDef &p = cdef->propertyList.at (i);
			if (isBuiltinType (p.type))
				continue;

			if (container_contains(p.type, '*') ||
				container_contains(p.type, '<') ||
				container_contains(p.type, '>'))
			{
				continue;
			}

			int s = p.type.find_last_of ("::");
			if (s <= 0)
				continue;

			QByteArray unqualifiedScope = string_left(p.type, s);

			// The scope may be a namespace for example, so it's only safe to include scopes that are known LooObjects (QTBUG-2151)
			std::unordered_map<QByteArray, QByteArray>::const_iterator scopeIt;

			QByteArray thisScope = cdef->qualified;
			do {
				int s = thisScope.find_last_of ("::");
				thisScope = string_left(thisScope, s); 
				QByteArray currentScope = thisScope.empty () ? unqualifiedScope : thisScope + "::" + unqualifiedScope;
				scopeIt = knownExtraMetaObject.find (currentScope);
			} while (!thisScope.empty () && scopeIt == knownExtraMetaObject.end ());

			if (scopeIt == knownExtraMetaObject.end ())
				continue;

			const QByteArray &scope = scopeIt->second;

			if (scope == "Loo")
				continue;
			if (qualifiedNameEquals (cdef->qualified, scope))
				continue;

			if (!container_contains(extraList, scope))
				extraList.push_back(scope);
		}

		// QTBUG-20639 - Accept non-local enums for QML signal/slot parameters.
		// Look for any scoped enum declarations, and add those to the list
		// of extra/related metaobjects for this object.
		for (auto it = cdef->enumDeclarations.begin (),
			end = cdef->enumDeclarations.end (); it != end; ++it) {
			const QByteArray &enumKey = it->first;
			int s = enumKey.find_last_of ("::");
			if (s > 0) {
				QByteArray scope = string_left(enumKey, s);
				if (scope != "Loo" && !qualifiedNameEquals (cdef->qualified, scope) && !container_contains(extraList,scope))
					extraList.push_back(scope);
			}
		}

		if (!extraList.empty ()) {
			fprintf (out, "static const LooMetaObject * const loo_meta_extradata_%s[] = {\n    ", qualifiedClassNameIdentifier.data ());
			for (int i = 0; i < extraList.size(); ++i) {
				fprintf (out, "    &%s::staticMetaObject,\n", extraList[i].data ());
			}
			fprintf (out, "    nullptr\n};\n\n");
		}

		//
		// Finally create and initialize the static meta object
		//
		if (isQt)
			fprintf (out, "const LooMetaObject LooObject::staticQtMetaObject = {\n");
		else
			fprintf (out, "const LooMetaObject %s::staticMetaObject = {\n", cdef->qualified.data ());

		if (isLooObject)
			fprintf (out, "    { nullptr, ");
		else if (cdef->superclassList.size () && (!cdef->hasLooGadget || knownGadgets.find (purestSuperClass) != knownGadgets.end()))
			fprintf (out, "    { &%s::staticMetaObject, ", purestSuperClass.data ());
		else
			fprintf (out, "    { nullptr, ");
		fprintf (out, "loo_meta_stringdata_%s.data,\n"
			"      loo_meta_data_%s, ", qualifiedClassNameIdentifier.data (),
			qualifiedClassNameIdentifier.data ());
		if (hasStaticMetaCall)
			fprintf (out, " loo_static_metacall, ");
		else
			fprintf (out, " nullptr, ");

		if (extraList.empty ())
			fprintf (out, "nullptr, ");
		else
			fprintf (out, "loo_meta_extradata_%s, ", qualifiedClassNameIdentifier.data ());
		fprintf (out, "nullptr}\n};\n\n");

		if (isQt)
			return;

		if (!cdef->hasLooObject)
			return;

		fprintf (out, "\nconst LooMetaObject *%s::metaObject() const\n{\n    return LooObject::d_ptr->metaObject ? LooObject::d_ptr->dynamicMetaObject() : &staticMetaObject;\n}\n",
			cdef->qualified.data ());

		//
		// Generate smart cast function
		//
		fprintf (out, "\nvoid *%s::loo_metacast(const char *_clname)\n{\n", cdef->qualified.data ());
		fprintf (out, "    if (!_clname) return nullptr;\n");
		fprintf (out, "    if (!strcmp(_clname, loo_meta_stringdata_%s.stringdata0))\n"
			"        return static_cast<void*>(this);\n",
			qualifiedClassNameIdentifier.data ());
		for (int i = 1; i < cdef->superclassList.size (); ++i) { // for all superclasses but the first one
			if (cdef->superclassList.at (i).second == FunctionDef::Private)
				continue;
			const char *cname = cdef->superclassList.at (i).first.data ();
			fprintf (out, "    if (!strcmp(_clname, \"%s\"))\n        return static_cast< %s*>(this);\n",
				cname, cname);
		}
		for (int i = 0; i < cdef->interfaceList.size (); ++i) {
			const std::vector<ClassDef::Interface> &iface = cdef->interfaceList.at (i);
			for (int j = 0; j < iface.size (); ++j) {
				fprintf (out, "    if (!strcmp(_clname, %s))\n        return ", iface.at (j).interfaceId.data ());
				for (int k = j; k >= 0; --k)
					fprintf (out, "static_cast< %s*>(", iface.at (k).className.data ());
				fprintf (out, "this%s;\n", QByteArray (j + 1, ')').data ());
			}
		}
		if (!purestSuperClass.empty () && !isLooObject) {
			QByteArray superClass = purestSuperClass;
			fprintf (out, "    return %s::loo_metacast(_clname);\n", superClass.data ());
		}
		else {
			fprintf (out, "    return nullptr;\n");
		}
		fprintf (out, "}\n");

		//
		// Generate internal loo_metacall()  function
		//
		generateMetacall ();

		//
		// Generate internal signal functions
		//
		for (int signalindex = 0; signalindex < cdef->signalList.size (); ++signalindex)
			generateSignal (&cdef->signalList[signalindex], signalindex);

		//
		// Generate plugin meta data
		//
		generatePluginMetaData ();
	}


	void Generator::registerClassInfoStrings ()
	{
		for (int i = 0; i < cdef->classInfoList.size (); ++i) {
			const ClassInfoDef &c = cdef->classInfoList.at (i);
			strreg (c.name);
			strreg (c.value);
		}
	}

	void Generator::generateClassInfos()
	{
		if (cdef->classInfoList.empty())
			return;

		fprintf(out, "\n // classinfo: key, value\n");

		for (int i = 0; i < cdef->classInfoList.size(); ++i) {
			const ClassInfoDef &c = cdef->classInfoList.at(i);
			fprintf(out, "    %4d, %4d,\n", stridx(c.name), stridx(c.value));
		}
	}

	void Generator::registerFunctionStrings(const std::vector<FunctionDef>& list)
	{
		for (int i = 0; i < list.size(); ++i) {
			const FunctionDef &f = list.at(i);

			strreg(f.name);
			if (!isBuiltinType(f.normalizedType))
				strreg(f.normalizedType);
			strreg(f.tag);

			int argsCount = f.arguments.size();
			for (int j = 0; j < argsCount; ++j) {
				const ArgumentDef &a = f.arguments.at(j);
				if (!isBuiltinType(a.normalizedType))
					strreg(a.normalizedType);
				strreg(a.name);
			}
		}
	}


	void Generator::registerByteArrayVector(const std::vector<QByteArray> &list)
	{
		for (const QByteArray &ba : list)
			strreg(ba);
	}

	void Generator::generateFunctions(const std::vector<FunctionDef>& list, const char *functype, int type, int &paramsIndex)
	{
		if (list.empty())
			return;
		fprintf(out, "\n // %ss: name, argc, parameters, tag, flags\n", functype);

		for (int i = 0; i < list.size(); ++i) {
			const FunctionDef &f = list.at(i);

			QByteArray comment;
			unsigned char flags = type;
			if (f.access == FunctionDef::Private) {
				flags |= AccessPrivate;
				comment.append("Private");
			}
			else if (f.access == FunctionDef::Public) {
				flags |= AccessPublic;
				comment.append("Public");
			}
			else if (f.access == FunctionDef::Protected) {
				flags |= AccessProtected;
				comment.append("Protected");
			}
			if (f.isCompat) {
				flags |= MethodCompatibility;
				comment.append(" | MethodCompatibility");
			}
			if (f.wasCloned) {
				flags |= MethodCloned;
				comment.append(" | MethodCloned");
			}
			if (f.isScriptable) {
				flags |= MethodScriptable;
				comment.append(" | isScriptable");
			}
			if (f.revision > 0) {
				flags |= MethodRevisioned;
				comment.append(" | MethodRevisioned");
			}

			int argc = f.arguments.size();
			fprintf(out, "    %4d, %4d, %4d, %4d, 0x%02x /* %s */,\n",
				stridx(f.name), argc, paramsIndex, stridx(f.tag), flags, comment.data());

			paramsIndex += 1 + argc * 2;
		}
	}


	void Generator::generateFunctionRevisions(const std::vector<FunctionDef>& list, const char *functype)
	{
		if (list.size())
			fprintf(out, "\n // %ss: revision\n", functype);
		for (int i = 0; i < list.size(); ++i) {
			const FunctionDef &f = list.at(i);
			fprintf(out, "    %4d,\n", f.revision);
		}
	}

	void Generator::generateFunctionParameters(const std::vector<FunctionDef>& list, const char *functype)
	{
		if (list.empty())
			return;
		fprintf(out, "\n // %ss: parameters\n", functype);
		for (int i = 0; i < list.size(); ++i) {
			const FunctionDef &f = list.at(i);
			fprintf(out, "    ");

			// Types
			int argsCount = f.arguments.size();
			for (int j = -1; j < argsCount; ++j) {
				if (j > -1)
					fputc(' ', out);
				const QByteArray &typeName = (j < 0) ? f.normalizedType : f.arguments.at(j).normalizedType;
				generateTypeInfo(typeName, /*allowEmptyName=*/f.isConstructor);
				fputc(',', out);
			}

			// Parameter names
			for (int j = 0; j < argsCount; ++j) {
				const ArgumentDef &arg = f.arguments.at(j);
				fprintf(out, " %4d,", stridx(arg.name));
			}

			fprintf(out, "\n");
		}
	}


	void Generator::generateTypeInfo(const QByteArray &typeName, bool allowEmptyName)
	{
		LOO_UNUSED(allowEmptyName);
		if (isBuiltinType(typeName)) {
			int type;
			const char *valueString;
			if (typeName == "lreal") {
				type = LooMetaType::UnknownType;
				valueString = "LReal";
			}
			else {
				type = nameToBuiltinType(typeName);
				valueString = metaTypeEnumValueString(type);
			}
			if (valueString) {
				fprintf(out, "LooMetaType::%s", valueString);
			}
			else {
				assert(type != LooMetaType::UnknownType);
				fprintf(out, "%4d", type);
			}
		}
		else {
			assert (!typeName.empty() || allowEmptyName);
			fprintf(out, "0x%.8x | %d", IsUnresolvedType, stridx(typeName));
		}
	}

	void Generator::registerPropertyStrings()
	{
		for (int i = 0; i < cdef->propertyList.size(); ++i) {
			const PropertyDef &p = cdef->propertyList.at(i);
			strreg(p.name);
			if (!isBuiltinType(p.type))
				strreg(p.type);
		}
	}

	void Generator::generateProperties()
	{
		//
		// Create meta data
		//

		if (cdef->propertyList.size())
			fprintf(out, "\n // properties: name, type, flags\n");
		for (int i = 0; i < cdef->propertyList.size(); ++i) {
			const PropertyDef &p = cdef->propertyList.at(i);
			std::uint32_t flags = Invalid;
			if (!isBuiltinType(p.type))
				flags |= EnumOrFlag;
			if (!p.member.empty() && !p.constant)
				flags |= Writable;
			if (!p.read.empty() || !p.member.empty())
				flags |= Readable;
			if (!p.write.empty()) {
				flags |= Writable;
				if (p.stdCppSet())
					flags |= StdCppSet;
			}
			if (!p.reset.empty())
				flags |= Resettable;

			//         if (p.override)
			//             flags |= Override;

			if (p.designable.empty())
				flags |= ResolveDesignable;
			else if (p.designable != "false")
				flags |= Designable;

			if (p.scriptable.empty())
				flags |= ResolveScriptable;
			else if (p.scriptable != "false")
				flags |= Scriptable;

			if (p.stored.empty())
				flags |= ResolveStored;
			else if (p.stored != "false")
				flags |= Stored;

			if (p.editable.empty())
				flags |= ResolveEditable;
			else if (p.editable != "false")
				flags |= Editable;

			if (p.user.empty())
				flags |= ResolveUser;
			else if (p.user != "false")
				flags |= User;

			if (p.notifyId != -1)
				flags |= Notify;

			if (p.revision > 0)
				flags |= Revisioned;

			if (p.constant)
				flags |= Constant;
			if (p.final)
				flags |= Final;

			fprintf(out, "    %4d, ", stridx(p.name));
			generateTypeInfo(p.type);
			fprintf(out, ", 0x%.8x,\n", flags);
		}

		if (cdef->notifyableProperties) {
			fprintf(out, "\n // properties: notify_signal_id\n");
			for (int i = 0; i < cdef->propertyList.size(); ++i) {
				const PropertyDef &p = cdef->propertyList.at(i);
				if (p.notifyId == -1) {
					fprintf(out, "    %4d,\n",
						0);
				}
				else if (p.notifyId > -1) {
					fprintf(out, "    %4d,\n",
						p.notifyId);
				}
				else {
					const int indexInStrings = GetIndexOf(strings, p.notify);
					fprintf(out, "    %4d,\n",
						indexInStrings | IsUnresolvedSignal);
				}
			}
		}
		if (cdef->revisionedProperties) {
			fprintf(out, "\n // properties: revision\n");
			for (int i = 0; i < cdef->propertyList.size(); ++i) {
				const PropertyDef &p = cdef->propertyList.at(i);
				fprintf(out, "    %4d,\n", p.revision);
			}
		}
	}

	void Generator::registerEnumStrings()
	{
		for (int i = 0; i < cdef->enumList.size(); ++i) {
			const EnumDef &e = cdef->enumList.at(i);
			strreg(e.name);
			for (int j = 0; j < e.values.size(); ++j)
				strreg(e.values.at(j));
		}
	}

	void Generator::generateEnums(int index)
	{
		if (cdef->enumDeclarations.empty())
			return;

		fprintf(out, "\n // enums: name, alias, flags, count, data\n");
		index += 5 * cdef->enumList.size();
		int i;
		for (i = 0; i < cdef->enumList.size(); ++i) {
			const EnumDef &e = cdef->enumList.at(i);
			int flags = 0;
			if (cdef->enumDeclarations[e.name])
				flags |= EnumIsFlag;
			if (e.isEnumClass)
				flags |= EnumIsScoped;
			fprintf(out, "    %4d, %4d, 0x%.1x, %4d, %4d,\n",
				stridx(e.name),
				cdef->enumDeclarations[e.name] ? 1 : 0,
				flags,
				e.values.size(),
				index);
			index += e.values.size() * 2;
		}

		fprintf(out, "\n // enum data: key, value\n");
		for (i = 0; i < cdef->enumList.size(); ++i) {
			const EnumDef &e = cdef->enumList.at(i);
			for (int j = 0; j < e.values.size(); ++j) {
				const QByteArray &val = e.values.at(j);
				QByteArray code = cdef->qualified.data();
				if (e.isEnumClass)
					code += "::" + e.name;
				code += "::" + val;
				fprintf(out, "    %4d, std::uint32_t(%s),\n",
					stridx(val), code.data());
			}
		}
	}

	void Generator::generateMetacall()
	{
		bool isLooObject = (cdef->classname == "LooObject");

		fprintf(out, "\nint %s::loo_metacall(LooMetaObject::Call _c, int _id, void **_a)\n{\n",
			cdef->qualified.data());

		if (!purestSuperClass.empty() && !isLooObject) {
			QByteArray superClass = purestSuperClass;
			fprintf(out, "    _id = %s::loo_metacall(_c, _id, _a);\n", superClass.data());
		}


		bool needElse = false;
		std::vector<FunctionDef> methodList;
		methodList.insert(methodList.end(), cdef->signalList.begin(), cdef->signalList.end());
		methodList.insert(methodList.end(), cdef->slotList.begin(), cdef->slotList.end());
		methodList.insert(methodList.end(), cdef->methodList.begin(), cdef->methodList.end());

		// If there are no methods or properties, we will return _id anyway, so
		// don't emit this comparison -- it is unnecessary, and it makes coverity
		// unhappy.
		if (methodList.size() || cdef->propertyList.size()) {
			fprintf(out, "    if (_id < 0)\n        return _id;\n");
		}

		fprintf(out, "    ");

		if (methodList.size()) {
			needElse = true;
			fprintf(out, "if (_c == LooMetaObject::InvokeMetaMethod) {\n");
			fprintf(out, "        if (_id < %d)\n", methodList.size());
			fprintf(out, "            loo_static_metacall(this, _c, _id, _a);\n");
			fprintf(out, "        _id -= %d;\n    }", methodList.size());

			fprintf(out, " else if (_c == LooMetaObject::RegisterMethodArgumentMetaType) {\n");
			fprintf(out, "        if (_id < %d)\n", methodList.size());

			if (methodsWithAutomaticTypesHelper(methodList).empty())
				fprintf(out, "            *reinterpret_cast<int*>(_a[0]) = -1;\n");
			else
				fprintf(out, "            loo_static_metacall(this, _c, _id, _a);\n");
			fprintf(out, "        _id -= %d;\n    }", methodList.size());

		}

		if (cdef->propertyList.size()) {
			bool needDesignable = false;
			bool needScriptable = false;
			bool needStored = false;
			bool needEditable = false;
			bool needUser = false;
			for (int i = 0; i < cdef->propertyList.size(); ++i) {
				const PropertyDef &p = cdef->propertyList.at(i);
				needDesignable |= string_endwith(p.designable,')');
				needScriptable |= string_endwith(p.scriptable,')');
				needStored |= string_endwith(p.stored, ')');
				needEditable |= string_endwith(p.editable, ')');
				needUser |= string_endwith(p.user, ')');
			}

			fprintf(out, "\n#ifndef LOO_NO_PROPERTIES\n    ");
			if (needElse)
				fprintf(out, "else ");
			fprintf(out,
				"if (_c == LooMetaObject::ReadProperty || _c == LooMetaObject::WriteProperty\n"
				"            || _c == LooMetaObject::ResetProperty || _c == LooMetaObject::RegisterPropertyMetaType) {\n"
				"        loo_static_metacall(this, _c, _id, _a);\n"
				"        _id -= %d;\n    }", cdef->propertyList.size());

			fprintf(out, " else ");
			fprintf(out, "if (_c == LooMetaObject::QueryPropertyDesignable) {\n");
			if (needDesignable) {
				fprintf(out, "        bool *_b = reinterpret_cast<bool*>(_a[0]);\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (!string_endwith(p.designable,')'))
						continue;
					fprintf(out, "        case %d: *_b = %s; break;\n",
						propindex, p.designable.data());
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}
			fprintf(out,
				"        _id -= %d;\n"
				"    }", cdef->propertyList.size());

			fprintf(out, " else ");
			fprintf(out, "if (_c == LooMetaObject::QueryPropertyScriptable) {\n");
			if (needScriptable) {
				fprintf(out, "        bool *_b = reinterpret_cast<bool*>(_a[0]);\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (!string_endwith(p.scriptable, ')'))
						continue;
					fprintf(out, "        case %d: *_b = %s; break;\n",
						propindex, p.scriptable.data());
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}
			fprintf(out,
				"        _id -= %d;\n"
				"    }", cdef->propertyList.size());

			fprintf(out, " else ");
			fprintf(out, "if (_c == LooMetaObject::QueryPropertyStored) {\n");
			if (needStored) {
				fprintf(out, "        bool *_b = reinterpret_cast<bool*>(_a[0]);\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (!string_endwith(p.stored, ')'))
						continue;
					fprintf(out, "        case %d: *_b = %s; break;\n",
						propindex, p.stored.data());
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}
			fprintf(out,
				"        _id -= %d;\n"
				"    }", cdef->propertyList.size());

			fprintf(out, " else ");
			fprintf(out, "if (_c == LooMetaObject::QueryPropertyEditable) {\n");
			if (needEditable) {
				fprintf(out, "        bool *_b = reinterpret_cast<bool*>(_a[0]);\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (!string_endwith(p.editable,')'))
						continue;
					fprintf(out, "        case %d: *_b = %s; break;\n",
						propindex, p.editable.data());
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}
			fprintf(out,
				"        _id -= %d;\n"
				"    }", cdef->propertyList.size());


			fprintf(out, " else ");
			fprintf(out, "if (_c == LooMetaObject::QueryPropertyUser) {\n");
			if (needUser) {
				fprintf(out, "        bool *_b = reinterpret_cast<bool*>(_a[0]);\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (!string_endwith(p.user, ')'))
						continue;
					fprintf(out, "        case %d: *_b = %s; break;\n",
						propindex, p.user.data());
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}
			fprintf(out,
				"        _id -= %d;\n"
				"    }", cdef->propertyList.size());

			fprintf(out, "\n#endif // LOO_NO_PROPERTIES");
		}
		if (methodList.size() || cdef->propertyList.size())
			fprintf(out, "\n    ");
		fprintf(out, "return _id;\n}\n");
	}


	std::multimap<QByteArray, int> Generator::automaticPropertyMetaTypesHelper()
	{
		std::multimap<QByteArray, int> automaticPropertyMetaTypes;
		for (int i = 0; i < cdef->propertyList.size(); ++i) {
			const QByteArray propertyType = cdef->propertyList.at(i).type;
			if (registerableMetaType(propertyType) && !isBuiltinType(propertyType))
				automaticPropertyMetaTypes.insert(std::make_pair(propertyType, i));
		}
		return automaticPropertyMetaTypes;
	}

	std::unordered_map<int, std::multimap<QByteArray, int> > Generator::methodsWithAutomaticTypesHelper(const std::vector<FunctionDef> &methodList)
	{
		std::unordered_map<int, std::multimap<QByteArray, int> > methodsWithAutomaticTypes;
		for (int i = 0; i < methodList.size(); ++i) {
			const FunctionDef &f = methodList.at(i);
			for (int j = 0; j < f.arguments.size(); ++j) {
				const QByteArray argType = f.arguments.at(j).normalizedType;
				if (registerableMetaType(argType) && !isBuiltinType(argType))
					methodsWithAutomaticTypes[i].insert(std::make_pair(argType, j));
			}
		}
		return methodsWithAutomaticTypes;
	}

	void Generator::generateStaticMetacall()
	{
		fprintf(out, "void %s::loo_static_metacall(LooObject *_o, LooMetaObject::Call _c, int _id, void **_a)\n{\n",
			cdef->qualified.data());

		bool needElse = false;
		bool isUsed_a = false;

		if (!cdef->constructorList.empty()) {
			fprintf(out, "    if (_c == LooMetaObject::CreateInstance) {\n");
			fprintf(out, "        switch (_id) {\n");
			for (int ctorindex = 0; ctorindex < cdef->constructorList.size(); ++ctorindex) {
				fprintf(out, "        case %d: { %s *_r = new %s(", ctorindex,
					cdef->classname.data(), cdef->classname.data());
				const FunctionDef &f = cdef->constructorList.at(ctorindex);
				int offset = 1;

				int argsCount = f.arguments.size();
				for (int j = 0; j < argsCount; ++j) {
					const ArgumentDef &a = f.arguments.at(j);
					if (j)
						fprintf(out, ",");
					fprintf(out, "(*reinterpret_cast< %s>(_a[%d]))", a.typeNameForCast.data(), offset++);
				}
				if (f.isPrivateSignal) {
					if (argsCount > 0)
						fprintf(out, ", ");
					fprintf(out, "%s", QByteArray("LooPrivateSignal()").data());
				}
				fprintf(out, ");\n");
				fprintf(out, "            if (_a[0]) *reinterpret_cast<%s**>(_a[0]) = _r; } break;\n",
					cdef->hasLooGadget ? "void" : "LooObject");
			}
			fprintf(out, "        default: break;\n");
			fprintf(out, "        }\n");
			fprintf(out, "    }");
			needElse = true;
			isUsed_a = true;
		}

		std::vector<FunctionDef> methodList;
		methodList.insert(methodList.end(), cdef->signalList.begin(), cdef->signalList.end());
		methodList.insert(methodList.end(), cdef->slotList.begin(), cdef->slotList.end());
		methodList.insert(methodList.end(), cdef->methodList.begin(), cdef->methodList.end());

		if (!methodList.empty()) {
			if (needElse)
				fprintf(out, " else ");
			else
				fprintf(out, "    ");
			fprintf(out, "if (_c == LooMetaObject::InvokeMetaMethod) {\n");
			if (cdef->hasLooObject) {
#ifndef LOO_NO_DEBUG
				fprintf(out, "        LOO_ASSERT(staticMetaObject.cast(_o));\n");
#endif
				fprintf(out, "        auto *_t = static_cast<%s *>(_o);\n", cdef->classname.data());
			}
			else {
				fprintf(out, "        auto *_t = reinterpret_cast<%s *>(_o);\n", cdef->classname.data());
			}
			fprintf(out, "        LOO_UNUSED(_t)\n");
			fprintf(out, "        switch (_id) {\n");
			for (int methodindex = 0; methodindex < methodList.size(); ++methodindex) {
				const FunctionDef &f = methodList.at(methodindex);
				assert (!f.normalizedType.empty());
				fprintf(out, "        case %d: ", methodindex);
				if (f.normalizedType != "void")
					fprintf(out, "{ %s _r = ", noRef(f.normalizedType).data());
				fprintf(out, "_t->");
				if (f.inPrivateClass.size())
					fprintf(out, "%s->", f.inPrivateClass.data());
				fprintf(out, "%s(", f.name.data());
				int offset = 1;

				int argsCount = f.arguments.size();
				for (int j = 0; j < argsCount; ++j) {
					const ArgumentDef &a = f.arguments.at(j);
					if (j)
						fprintf(out, ",");
					fprintf(out, "(*reinterpret_cast< %s>(_a[%d]))", a.typeNameForCast.data(), offset++);
					isUsed_a = true;
				}
				if (f.isPrivateSignal) {
					if (argsCount > 0)
						fprintf(out, ", ");
					fprintf(out, "%s", "LooPrivateSignal()");
				}
				fprintf(out, ");");
				if (f.normalizedType != "void") {
					fprintf(out, "\n            if (_a[0]) *reinterpret_cast< %s*>(_a[0]) = std::move(_r); } ",
						noRef(f.normalizedType).data());
					isUsed_a = true;
				}
				fprintf(out, " break;\n");
			}
			fprintf(out, "        default: ;\n");
			fprintf(out, "        }\n");
			fprintf(out, "    }");
			needElse = true;

			std::unordered_map<int, std::multimap<QByteArray, int> > methodsWithAutomaticTypes = methodsWithAutomaticTypesHelper(methodList);

			if (!methodsWithAutomaticTypes.empty()) {
				fprintf(out, " else if (_c == LooMetaObject::RegisterMethodArgumentMetaType) {\n");
				fprintf(out, "        switch (_id) {\n");
				fprintf(out, "        default: *reinterpret_cast<int*>(_a[0]) = -1; break;\n");
				std::unordered_map<int, std::multimap<QByteArray, int> >::const_iterator it = methodsWithAutomaticTypes.begin();
				const std::unordered_map<int, std::multimap<QByteArray, int> >::const_iterator end = methodsWithAutomaticTypes.end();
				for (; it != end; ++it) {
					fprintf(out, "        case %d:\n", it->first);
					fprintf(out, "            switch (*reinterpret_cast<int*>(_a[1])) {\n");
					fprintf(out, "            default: *reinterpret_cast<int*>(_a[0]) = -1; break;\n");
					auto jt = it->second.begin();// it->begin();
					const auto jend = it->second.end();// it->end();
					while (jt != jend) {
						fprintf(out, "            case %d:\n", jt->second);
						const QByteArray &lastKey = jt->first;
						++jt;
						if (jt == jend || jt->first != lastKey)
							fprintf(out, "                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< %s >(); break;\n", lastKey.data());
					}
					fprintf(out, "            }\n");
					fprintf(out, "            break;\n");
				}
				fprintf(out, "        }\n");
				fprintf(out, "    }");
				isUsed_a = true;
			}

		}
		if (!cdef->signalList.empty()) {
			assert (needElse); // if there is signal, there was method.
			fprintf(out, " else if (_c == LooMetaObject::IndexOfMethod) {\n");
			fprintf(out, "        int *result = reinterpret_cast<int *>(_a[0]);\n");
			bool anythingUsed = false;
			for (int methodindex = 0; methodindex < cdef->signalList.size(); ++methodindex) {
				const FunctionDef &f = cdef->signalList.at(methodindex);
				if (f.wasCloned || !f.inPrivateClass.empty() || f.isStatic)
					continue;
				anythingUsed = true;
				fprintf(out, "        {\n");
				fprintf(out, "            using _t = %s (%s::*)(", f.type.rawName.data(), cdef->classname.data());

				int argsCount = f.arguments.size();
				for (int j = 0; j < argsCount; ++j) {
					const ArgumentDef &a = f.arguments.at(j);
					if (j)
						fprintf(out, ", ");
					fprintf(out, "%s", QByteArray(a.type.name + ' ' + a.rightType).data());
				}
				if (f.isPrivateSignal) {
					if (argsCount > 0)
						fprintf(out, ", ");
					fprintf(out, "%s", "LooPrivateSignal");
				}
				if (f.isConst)
					fprintf(out, ") const;\n");
				else
					fprintf(out, ");\n");
				fprintf(out, "            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&%s::%s)) {\n",
					cdef->classname.data(), f.name.data());
				fprintf(out, "                *result = %d;\n", methodindex);
				fprintf(out, "                return;\n");
				fprintf(out, "            }\n        }\n");
			}
			if (!anythingUsed)
				fprintf(out, "        LOO_UNUSED(result);\n");
			fprintf(out, "    }");
			needElse = true;
		}

		const std::multimap<QByteArray, int> automaticPropertyMetaTypes = automaticPropertyMetaTypesHelper();

		if (!automaticPropertyMetaTypes.empty()) {
			if (needElse)
				fprintf(out, " else ");
			else
				fprintf(out, "    ");
			fprintf(out, "if (_c == LooMetaObject::RegisterPropertyMetaType) {\n");
			fprintf(out, "        switch (_id) {\n");
			fprintf(out, "        default: *reinterpret_cast<int*>(_a[0]) = -1; break;\n");
			auto it = automaticPropertyMetaTypes.begin();
			const auto end = automaticPropertyMetaTypes.end();
			while (it != end) {
				fprintf(out, "        case %d:\n", it->second);
				const QByteArray &lastKey = it->first;
				++it;
				if (it == end || it->first != lastKey)
					fprintf(out, "            *reinterpret_cast<int*>(_a[0]) = lRegisterMetaType< %s >(); break;\n", lastKey.data());
			}
			fprintf(out, "        }\n");
			fprintf(out, "    }\n");
			isUsed_a = true;
			needElse = true;
		}

		if (!cdef->propertyList.empty()) {
			bool needGet = false;
			bool needTempVarForGet = false;
			bool needSet = false;
			bool needReset = false;
			for (int i = 0; i < cdef->propertyList.size(); ++i) {
				const PropertyDef &p = cdef->propertyList.at(i);
				needGet |= !p.read.empty() || !p.member.empty();
				if (!p.read.empty() || !p.member.empty())
					needTempVarForGet |= (p.gspec != PropertyDef::PointerSpec
						&& p.gspec != PropertyDef::ReferenceSpec);

				needSet |= !p.write.empty() || (!p.member.empty() && !p.constant);
				needReset |= !p.reset.empty();
			}
			fprintf(out, "\n#ifndef LOO_NO_PROPERTIES\n    ");

			if (needElse)
				fprintf(out, "else ");
			fprintf(out, "if (_c == LooMetaObject::ReadProperty) {\n");
			if (needGet) {
				if (cdef->hasLooObject) {
#ifndef LOO_NO_DEBUG
					fprintf(out, "        LOO_ASSERT(staticMetaObject.cast(_o));\n");
#endif
					fprintf(out, "        auto *_t = static_cast<%s *>(_o);\n", cdef->classname.data());
				}
				else {
					fprintf(out, "        auto *_t = reinterpret_cast<%s *>(_o);\n", cdef->classname.data());
				}
				fprintf(out, "        LOO_UNUSED(_t)\n");
				if (needTempVarForGet)
					fprintf(out, "        void *_v = _a[0];\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (p.read.empty() && p.member.empty())
						continue;
					QByteArray prefix = "_t->";
					if (p.inPrivateClass.size()) {
						prefix += p.inPrivateClass + "->";
					}
					if (p.gspec == PropertyDef::PointerSpec)
						fprintf(out, "        case %d: _a[0] = const_cast<void*>(reinterpret_cast<const void*>(%s%s())); break;\n",
							propindex, prefix.data(), p.read.data());
					else if (p.gspec == PropertyDef::ReferenceSpec)
						fprintf(out, "        case %d: _a[0] = const_cast<void*>(reinterpret_cast<const void*>(&%s%s())); break;\n",
							propindex, prefix.data(), p.read.data());
					else if (cdef->enumDeclarations.find(p.type) != cdef->enumDeclarations.end() &&
						cdef->enumDeclarations.find(p.type)->second)
					{
						fprintf(out, "        case %d: *reinterpret_cast<int*>(_v) = QFlag(%s%s()); break;\n",
							propindex, prefix.data(), p.read.data());
					}
					else if (!p.read.empty())
						fprintf(out, "        case %d: *reinterpret_cast< %s*>(_v) = %s%s(); break;\n",
							propindex, p.type.data(), prefix.data(), p.read.data());
					else
						fprintf(out, "        case %d: *reinterpret_cast< %s*>(_v) = %s%s; break;\n",
							propindex, p.type.data(), prefix.data(), p.member.data());
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}

			fprintf(out, "    }");

			fprintf(out, " else ");
			fprintf(out, "if (_c == LooMetaObject::WriteProperty) {\n");

			if (needSet) {
				if (cdef->hasLooObject) {
#ifndef LOO_NO_DEBUG
					fprintf(out, "        LOO_ASSERT(staticMetaObject.cast(_o));\n");
#endif
					fprintf(out, "        auto *_t = static_cast<%s *>(_o);\n", cdef->classname.data());
				}
				else {
					fprintf(out, "        auto *_t = reinterpret_cast<%s *>(_o);\n", cdef->classname.data());
				}
				fprintf(out, "        LOO_UNUSED(_t)\n");
				fprintf(out, "        void *_v = _a[0];\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (p.constant)
						continue;
					if (p.write.empty() && p.member.empty())
						continue;
					QByteArray prefix = "_t->";
					if (p.inPrivateClass.size()) {
						prefix += p.inPrivateClass + "->";
					}
					if (cdef->enumDeclarations.find(p.type)!= cdef->enumDeclarations.end() &&
						cdef->enumDeclarations.find(p.type)->second) {
						fprintf(out, "        case %d: %s%s(QFlag(*reinterpret_cast<int*>(_v))); break;\n",
							propindex, prefix.data(), p.write.data());
					}
					else if (!p.write.empty()) {
						fprintf(out, "        case %d: %s%s(*reinterpret_cast< %s*>(_v)); break;\n",
							propindex, prefix.data(), p.write.data(), p.type.data());
					}
					else {
						fprintf(out, "        case %d:\n", propindex);
						fprintf(out, "            if (%s%s != *reinterpret_cast< %s*>(_v)) {\n",
							prefix.data(), p.member.data(), p.type.data());
						fprintf(out, "                %s%s = *reinterpret_cast< %s*>(_v);\n",
							prefix.data(), p.member.data(), p.type.data());
						if (!p.notify.empty() && p.notifyId > -1) {
							const FunctionDef &f = cdef->signalList.at(p.notifyId);
							if (f.arguments.size() == 0)
								fprintf(out, "                Q_EMIT _t->%s();\n", p.notify.data());
							else if (f.arguments.size() == 1 && f.arguments.at(0).normalizedType == p.type)
								fprintf(out, "                Q_EMIT _t->%s(%s%s);\n",
									p.notify.data(), prefix.data(), p.member.data());
						}
						else if (!p.notify.empty() && p.notifyId < -1) {
							fprintf(out, "                Q_EMIT _t->%s();\n", p.notify.data());
						}
						fprintf(out, "            }\n");
						fprintf(out, "            break;\n");
					}
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}

			fprintf(out, "    }");

			fprintf(out, " else ");
			fprintf(out, "if (_c == LooMetaObject::ResetProperty) {\n");
			if (needReset) {
				if (cdef->hasLooObject) {
#ifndef LOO_NO_DEBUG
					fprintf(out, "        LOO_ASSERT(staticMetaObject.cast(_o));\n");
#endif
					fprintf(out, "        %s *_t = static_cast<%s *>(_o);\n", cdef->classname.data(), cdef->classname.data());
				}
				else {
					fprintf(out, "        %s *_t = reinterpret_cast<%s *>(_o);\n", cdef->classname.data(), cdef->classname.data());
				}
				fprintf(out, "        LOO_UNUSED(_t)\n");
				fprintf(out, "        switch (_id) {\n");
				for (int propindex = 0; propindex < cdef->propertyList.size(); ++propindex) {
					const PropertyDef &p = cdef->propertyList.at(propindex);
					if (!string_endwith(p.reset,')'))
						continue;
					QByteArray prefix = "_t->";
					if (p.inPrivateClass.size()) {
						prefix += p.inPrivateClass + "->";
					}
					fprintf(out, "        case %d: %s%s; break;\n",
						propindex, prefix.data(), p.reset.data());
				}
				fprintf(out, "        default: break;\n");
				fprintf(out, "        }\n");
			}
			fprintf(out, "    }");
			fprintf(out, "\n#endif // LOO_NO_PROPERTIES");
			needElse = true;
		}

		if (needElse)
			fprintf(out, "\n");

		if (methodList.empty()) {
			fprintf(out, "    LOO_UNUSED(_o);\n");
			if (cdef->constructorList.empty() && automaticPropertyMetaTypes.empty() && methodsWithAutomaticTypesHelper(methodList).empty()) {
				fprintf(out, "    LOO_UNUSED(_id);\n");
				fprintf(out, "    LOO_UNUSED(_c);\n");
			}
		}
		if (!isUsed_a)
			fprintf(out, "    LOO_UNUSED(_a);\n");

		fprintf(out, "}\n\n");
	}

	void Generator::generateSignal(FunctionDef *def, int index)
	{
		if (def->wasCloned || def->isAbstract)
			return;
		fprintf(out, "\n// SIGNAL %d\n%s %s::%s(",
			index, def->type.name.data(), cdef->qualified.data(), def->name.data());

		QByteArray thisPtr = "this";
		const char *constQualifier = "";

		if (def->isConst) {
			thisPtr = "const_cast< " + cdef->qualified + " *>(this)";
			constQualifier = "const";
		}

		assert (!def->normalizedType.empty());
		if (def->arguments.empty() && def->normalizedType == "void" && !def->isPrivateSignal) {
			fprintf(out, ")%s\n{\n"
				"    LooMetaObject::activate(%s, &staticMetaObject, %d, nullptr);\n"
				"}\n", constQualifier, thisPtr.data(), index);
			return;
		}

		int offset = 1;
		for (int j = 0; j < def->arguments.size(); ++j) {
			const ArgumentDef &a = def->arguments.at(j);
			if (j)
				fprintf(out, ", ");
			fprintf(out, "%s _t%d%s", a.type.name.data(), offset++, a.rightType.data());
		}
		if (def->isPrivateSignal) {
			if (!def->arguments.empty())
				fprintf(out, ", ");
			fprintf(out, "LooPrivateSignal _t%d", offset++);
		}

		fprintf(out, ")%s\n{\n", constQualifier);
		if (def->type.name.size() && def->normalizedType != "void") {
			QByteArray returnType = noRef(def->normalizedType);
			fprintf(out, "    %s _t0{};\n", returnType.data());
		}

		fprintf(out, "    void *_a[] = { ");
		if (def->normalizedType == "void") {
			fprintf(out, "nullptr");
		}
		else {
			if (def->returnTypeIsVolatile)
				fprintf(out, "const_cast<void*>(reinterpret_cast<const volatile void*>(std::addressof(_t0)))");
			else
				fprintf(out, "const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0)))");
		}
		int i;
		for (i = 1; i < offset; ++i)
			if (i <= def->arguments.size() && def->arguments.at(i - 1).type.isVolatile)
				fprintf(out, ", const_cast<void*>(reinterpret_cast<const volatile void*>(std::addressof(_t%d)))", i);
			else
				fprintf(out, ", const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t%d)))", i);
		fprintf(out, " };\n");
		fprintf(out, "    LooMetaObject::activate(%s, &staticMetaObject, %d, _a);\n", thisPtr.data(), index);
		if (def->normalizedType != "void")
			fprintf(out, "    return _t0;\n");
		fprintf(out, "}\n");
	}

	/*static CborError jsonValueToCbor(CborEncoder *parent, const QJsonValue &v);
	static CborError jsonObjectToCbor(CborEncoder *parent, const QJsonObject &o)
	{
		auto it = o.constBegin();
		auto end = o.constEnd();
		CborEncoder map;
		cbor_encoder_create_map(parent, &map, o.size());

		for (; it != end; ++it) {
			QByteArray key = it.key().toUtf8();
			cbor_encode_text_string(&map, key.data(), key.size());
			jsonValueToCbor(&map, it.value());
		}
		return cbor_encoder_close_container(parent, &map);
	}
*/
/*static CborError jsonArrayToCbor(CborEncoder *parent, const QJsonArray &a)
{
	CborEncoder array;
	cbor_encoder_create_array(parent, &array, a.size());
	for (const QJsonValue &v : a)
		jsonValueToCbor(&array, v);
	return cbor_encoder_close_container(parent, &array);
}

static CborError jsonValueToCbor(CborEncoder *parent, const QJsonValue &v)
{
	switch (v.type()) {
	case QJsonValue::Null:
	case QJsonValue::Undefined:
		return cbor_encode_null(parent);
	case QJsonValue::Bool:
		return cbor_encode_boolean(parent, v.toBool());
	case QJsonValue::Array:
		return jsonArrayToCbor(parent, v.toArray());
	case QJsonValue::Object:
		return jsonObjectToCbor(parent, v.toObject());
	case QJsonValue::String: {
		QByteArray s = v.toString().toUtf8();
		return cbor_encode_text_string(parent, s.data(), s.size());
	}
	case QJsonValue::Double: {
		double d = v.toDouble();
		if (d == floor(d) && fabs(d) <= (Q_INT64_C(1) << std::numeric_limits<double>::digits))
			return cbor_encode_int(parent, qint64(d));
		return cbor_encode_double(parent, d);
	}
	}
	Q_UNREACHABLE();
	return CborUnknownError;
}*/

	void Generator::generatePluginMetaData()
	{
		if (cdef->pluginData.iid.empty())
			return;

		fputs("\nLOO_PLUGIN_METADATA_SECTION\n"
			"static constexpr unsigned char loo_pluginMetaData[] = {\n"
			"    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',\n"
			"    // metadata version, Qt version, architectural requirements\n"
			"    0, LOO_VERSION_MAJOR, LOO_VERSION_MINOR, qPluginArchRequirements(),", out);


		//CborDevice dev(out);
		//CborEncoder enc;
		//cbor_encoder_init_writer(&enc, CborDevice::callback, &dev);

		//CborEncoder map;
		//cbor_encoder_create_map(&enc, &map, CborIndefiniteLength);

		//dev.nextItem("\"IID\"");
		//cbor_encode_int(&map, int(LooPluginMetaDataKeys::IID));
		//cbor_encode_text_string(&map, cdef->pluginData.iid.data(), cdef->pluginData.iid.size());

		//dev.nextItem("\"className\"");
		//cbor_encode_int(&map, int(LooPluginMetaDataKeys::ClassName));
		//cbor_encode_text_string(&map, cdef->classname.data(), cdef->classname.size());

		//QJsonObject o = cdef->pluginData.metaData.object();
		//if (!o.empty()) {
		//	dev.nextItem("\"MetaData\"");
		//	cbor_encode_int(&map, int(LooPluginMetaDataKeys::MetaData));
		//	jsonObjectToCbor(&map, o);
		//}

		//// Add -M args from the command line:
		//for (auto it = cdef->pluginData.metaArgs.cbegin(), end = cdef->pluginData.metaArgs.cend(); it != end; ++it) {
		//	const nlohmann::json &a = it->second;
		//	QByteArray key = it->first;
		//	dev.nextItem(QByteArray("command-line \"" + key + "\"").data());
		//	cbor_encode_text_string(&map, key.data(), key.size());
		//	jsonArrayToCbor(&map, a);
		//}

		//// Close the CBOR map manually
		//dev.nextItem();
		//cbor_encoder_close_container(&enc, &map);
		//fputs("\n};\n", out);

		//// 'Use' all namespaces.
		//int pos = cdef->qualified.find_last_of("::");
		//for (; pos != -1; pos = cdef->qualified.find_first_of("::", pos + 2))
		//	fprintf(out, "using namespace %s;\n", string_left(cdef->qualified,pos).data());
		//fprintf(out, "LOO_MOC_EXPORT_PLUGIN(%s, %s)\n\n",
		//	cdef->qualified.data(), cdef->classname.data());
	}

	/*LOO_WARNING_DISABLE_GCC("-Wunused-function")
		LOO_WARNING_DISABLE_CLANG("-Wunused-function")
		LOO_WARNING_DISABLE_CLANG("-Wundefined-internal")*/
		//LOO_WARNING_DISABLE_MSVC(4334) // '<<': result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)

#define CBOR_ENCODER_WRITER_CONTROL     1
#define CBOR_ENCODER_WRITE_FUNCTION     CborDevice::callback

}