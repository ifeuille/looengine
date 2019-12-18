#include "generator.h"
#include "outputrevision.h"
#include "utils.h"
#include <LooCore/loometatype.h>

#include "nlohmann/json.hpp"
#include <stdio.h>
#include <LooCore/loometaobject.h>
#include <algorithm>

#include <private/pmetaobject_p.h>

namespace loo
{
	std::uint32_t nameToBuiltinType (const std::string &name)
	{
		if (name.empty ())
			return 0;

		std::uint32_t tp = LooMetaType::type (name.data ());
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

	Generator::Generator (ClassDef *classDef, const std::vector<QByteArray> &metaTypes, const std::unordered_map<QByteArray, QByteArray> &knownQObjectClasses, const std::unordered_map<QByteArray, QByteArray> &knownGadgets, FILE *outfile)
		: out (outfile), cdef (classDef), metaTypes (metaTypes), knownQObjectClasses (knownQObjectClasses)
		, knownGadgets (knownGadgets)
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
		LOO_ASSERT_X (i != -1, LOO_FUNC_INFO, "We forgot to register some strings");
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
			// to chop it to find the class type in the known QObjects list.
			container_chop (objectPointerType, 1);
			if (knownQObjectClasses.find (objectPointerType) != knownQObjectClasses.end ())
				return true;
		}
		static const std::vector<QByteArray> smartPointers = std::vector<QByteArray> ()
#define STREAM_SMART_POINTER(SMART_POINTER) << #SMART_POINTER
			LOO_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER (STREAM_SMART_POINTER)
#undef STREAM_SMART_POINTER
			;

		for (const QByteArray &smartPointer : smartPointers) {
			if (string_startwith (propertyType, smartPointer + "<") && !string_endwith (propertyType, "&"))
			{
				return knownQObjectClasses.find (propertyType.substr (smartPointer.size () + 1, propertyType.size () - smartPointer.size () - 1 - 1)) != knownQObjectClasses.end ();
			}		
		}

		static const std::vector<QByteArray> oneArgTemplates = std::vector<QByteArray> ()
#define STREAM_1ARG_TEMPLATE(TEMPLATENAME) << #TEMPLATENAME
			LOO_FOR_EACH_AUTOMATIC_TEMPLATE_1ARG (STREAM_1ARG_TEMPLATE)
#undef STREAM_1ARG_TEMPLATE
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
		bool isQObject = (cdef->classname == "LooObject");
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
		fprintf (out, "#undef QT_MOC_LITERAL\n\n");

		//
		// build the data array
		//

		int index = MetaObjectPrivateFieldCount;
		fprintf (out, "static const uint qt_meta_data_%s[] = {\n", qualifiedClassNameIdentifier.data ());
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
		if (cdef->hasQGadget) {
			// Ideally, all the classes could have that flag. But this broke classes generated
			// by qdbusxml2cpp which generate code that require that we call qt_metacall for properties
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
		// Generate internal qt_static_metacall() function
		//
		const bool hasStaticMetaCall = !isQt &&
			(cdef->hasQObject || !cdef->methodList.isEmpty ()
				|| !cdef->propertyList.isEmpty () || !cdef->constructorList.isEmpty ());
		if (hasStaticMetaCall)
			generateStaticMetacall ();

		//
		// Build extra array
		//
		QList<QByteArray> extraList;
		QHash<QByteArray, QByteArray> knownExtraMetaObject = knownGadgets;
		knownExtraMetaObject.unite (knownQObjectClasses);

		for (int i = 0; i < cdef->propertyList.size(); ++i) {
			const PropertyDef &p = cdef->propertyList.at (i);
			if (isBuiltinType (p.type))
				continue;

			if (p.type.contains ('*') || p.type.contains ('<') || p.type.contains ('>'))
				continue;

			int s = p.type.lastIndexOf ("::");
			if (s <= 0)
				continue;

			QByteArray unqualifiedScope = p.type.left (s);

			// The scope may be a namespace for example, so it's only safe to include scopes that are known QObjects (QTBUG-2151)
			QHash<QByteArray, QByteArray>::ConstIterator scopeIt;

			QByteArray thisScope = cdef->qualified;
			do {
				int s = thisScope.lastIndexOf ("::");
				thisScope = thisScope.left (s);
				QByteArray currentScope = thisScope.isEmpty () ? unqualifiedScope : thisScope + "::" + unqualifiedScope;
				scopeIt = knownExtraMetaObject.constFind (currentScope);
			} while (!thisScope.isEmpty () && scopeIt == knownExtraMetaObject.constEnd ());

			if (scopeIt == knownExtraMetaObject.constEnd ())
				continue;

			const QByteArray &scope = *scopeIt;

			if (scope == "Qt")
				continue;
			if (qualifiedNameEquals (cdef->qualified, scope))
				continue;

			if (!extraList.contains (scope))
				extraList += scope;
		}

		// QTBUG-20639 - Accept non-local enums for QML signal/slot parameters.
		// Look for any scoped enum declarations, and add those to the list
		// of extra/related metaobjects for this object.
		for (auto it = cdef->enumDeclarations.keyBegin (),
			end = cdef->enumDeclarations.keyEnd (); it != end; ++it) {
			const QByteArray &enumKey = *it;
			int s = enumKey.lastIndexOf ("::");
			if (s > 0) {
				QByteArray scope = enumKey.left (s);
				if (scope != "Qt" && !qualifiedNameEquals (cdef->qualified, scope) && !extraList.contains (scope))
					extraList += scope;
			}
		}

		if (!extraList.isEmpty ()) {
			fprintf (out, "static const QMetaObject * const qt_meta_extradata_%s[] = {\n    ", qualifiedClassNameIdentifier.constData ());
			for (int i = 0; i < extraList.size(); ++i) {
				fprintf (out, "    &%s::staticMetaObject,\n", extraList.at (i).constData ());
			}
			fprintf (out, "    nullptr\n};\n\n");
		}

		//
		// Finally create and initialize the static meta object
		//
		if (isQt)
			fprintf (out, "const QMetaObject QObject::staticQtMetaObject = {\n");
		else
			fprintf (out, "const QMetaObject %s::staticMetaObject = {\n", cdef->qualified.constData ());

		if (isQObject)
			fprintf (out, "    { nullptr, ");
		else if (cdef->superclassList.size () && (!cdef->hasQGadget || knownGadgets.contains (purestSuperClass)))
			fprintf (out, "    { &%s::staticMetaObject, ", purestSuperClass.constData ());
		else
			fprintf (out, "    { nullptr, ");
		fprintf (out, "qt_meta_stringdata_%s.data,\n"
			"      qt_meta_data_%s, ", qualifiedClassNameIdentifier.constData (),
			qualifiedClassNameIdentifier.constData ());
		if (hasStaticMetaCall)
			fprintf (out, " qt_static_metacall, ");
		else
			fprintf (out, " nullptr, ");

		if (extraList.isEmpty ())
			fprintf (out, "nullptr, ");
		else
			fprintf (out, "qt_meta_extradata_%s, ", qualifiedClassNameIdentifier.constData ());
		fprintf (out, "nullptr}\n};\n\n");

		if (isQt)
			return;

		if (!cdef->hasQObject)
			return;

		fprintf (out, "\nconst QMetaObject *%s::metaObject() const\n{\n    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;\n}\n",
			cdef->qualified.constData ());

		//
		// Generate smart cast function
		//
		fprintf (out, "\nvoid *%s::qt_metacast(const char *_clname)\n{\n", cdef->qualified.constData ());
		fprintf (out, "    if (!_clname) return nullptr;\n");
		fprintf (out, "    if (!strcmp(_clname, qt_meta_stringdata_%s.stringdata0))\n"
			"        return static_cast<void*>(this);\n",
			qualifiedClassNameIdentifier.constData ());
		for (int i = 1; i < cdef->superclassList.size (); ++i) { // for all superclasses but the first one
			if (cdef->superclassList.at (i).second == FunctionDef::Private)
				continue;
			const char *cname = cdef->superclassList.at (i).first.constData ();
			fprintf (out, "    if (!strcmp(_clname, \"%s\"))\n        return static_cast< %s*>(this);\n",
				cname, cname);
		}
		for (int i = 0; i < cdef->interfaceList.size (); ++i) {
			const QVector<ClassDef::Interface> &iface = cdef->interfaceList.at (i);
			for (int j = 0; j < iface.size (); ++j) {
				fprintf (out, "    if (!strcmp(_clname, %s))\n        return ", iface.at (j).interfaceId.constData ());
				for (int k = j; k >= 0; --k)
					fprintf (out, "static_cast< %s*>(", iface.at (k).className.constData ());
				fprintf (out, "this%s;\n", QByteArray (j + 1, ')').constData ());
			}
		}
		if (!purestSuperClass.isEmpty () && !isQObject) {
			QByteArray superClass = purestSuperClass;
			fprintf (out, "    return %s::qt_metacast(_clname);\n", superClass.constData ());
		}
		else {
			fprintf (out, "    return nullptr;\n");
		}
		fprintf (out, "}\n");

		//
		// Generate internal qt_metacall()  function
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


}