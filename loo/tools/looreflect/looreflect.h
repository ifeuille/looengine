#ifndef LOOREFLECT_LOOREFLECT_H
#define LOOREFLECT_LOOREFLECT_H

#include "parser.h"
#include "stringlist.h"
#include <unordered_map>
#include <iostream>
#include <ctype.h>

namespace loo
{
	struct Type
	{
		enum ReferenceType { NoReference, Reference, RValueReference, Pointer };
		inline Type () : isVolatile (false), isScoped (false), firstToken (NOTOKEN), referenceType (NoReference) {}
		inline explicit Type (const QByteArray &_name)
			: name (_name), rawName (name), isVolatile (false), isScoped (false), firstToken (NOTOKEN), referenceType (NoReference) {}
		QByteArray name;
		//When used as a return type, the type name may be modified to remove the references.
		// rawName is the type as found in the function signature
		QByteArray rawName;
		std::uint32_t isVolatile : 1;
		std::uint32_t isScoped : 1;
		Token firstToken;
		ReferenceType referenceType;
	};

	struct EnumDef
	{
		QByteArray name;
		std::vector<QByteArray> values;
		bool isEnumClass; // c++11 enum class
		EnumDef () : isEnumClass (false) {}
	};
	
	struct ArgumentDef
	{
		ArgumentDef () : isDefault (false) {}
		Type type;
		QByteArray rightType, normalizedType, name;
		QByteArray typeNameForCast; // type name to be used in cast from void * in metacall
		bool isDefault;
	};

	struct FunctionDef
	{
		FunctionDef () : returnTypeIsVolatile (false), access (Private), isConst (false), isVirtual (false), isStatic (false),
			inlineCode (false), wasCloned (false), isCompat (false), isInvokable (false),
			isScriptable (false), isSlot (false), isSignal (false), isPrivateSignal (false),
			isConstructor (false), isDestructor (false), isAbstract (false), revision (0) {}
		Type type;
		QByteArray normalizedType;
		QByteArray tag;
		QByteArray name;
		bool returnTypeIsVolatile;

		std::vector<ArgumentDef> arguments;

		enum Access { Private, Protected, Public };
		Access access;
		bool isConst;
		bool isVirtual;
		bool isStatic;
		bool inlineCode;
		bool wasCloned;

		QByteArray inPrivateClass;
		bool isCompat;
		bool isInvokable;
		bool isScriptable;
		bool isSlot;
		bool isSignal;
		bool isPrivateSignal;
		bool isConstructor;
		bool isDestructor;
		bool isAbstract;

		int revision;
	};

	struct PropertyDef
	{
		PropertyDef () :notifyId (-1), constant (false), final (false), gspec (ValueSpec), revision (0) {}
		QByteArray name, type, member, read, write, reset, designable, scriptable, editable, stored, user, notify, inPrivateClass;
		int notifyId;
		bool constant;
		bool final;
		enum Specification { ValueSpec, ReferenceSpec, PointerSpec };
		Specification gspec;
		bool stdCppSet () const {
			QByteArray s ("set");
			s += toupper (name[0]);
			s += name.substr (1);
			return (s == write);
		}
		int revision;
	};
	
	struct ClassInfoDef
	{
		QByteArray name;
		QByteArray value;
	};

	struct BaseDef {
		QByteArray classname;
		QByteArray qualified;
		std::vector<ClassInfoDef> classInfoList;
		std::unordered_map<QByteArray, bool> enumDeclarations;
		std::vector<EnumDef> enumList;
		std::unordered_map<QByteArray, QByteArray> flagAliases;
		int begin = 0;
		int end = 0;
	};

	struct ClassDef : BaseDef {
		std::vector<std::pair<QByteArray, FunctionDef::Access> > superclassList;

		struct Interface
		{
			Interface () {} // for QVector, don't use
			inline explicit Interface (const QByteArray &_className)
				: className (_className) {}
			QByteArray className;
			QByteArray interfaceId;
		};
		std::vector<std::vector<Interface> >interfaceList;

		bool hasQObject = false;
		bool hasQGadget = false;

		struct PluginData {
			QByteArray iid;
			std::unordered_map<std::string, QJsonArray> metaArgs;
			QJsonDocument metaData;
		} pluginData;

		std::vector<FunctionDef> constructorList;
		std::vector<FunctionDef> signalList, slotList, methodList, publicList;
		int notifyableProperties = 0;
		std::vector<PropertyDef> propertyList;
		int revisionedMethods = 0;
		int revisionedProperties = 0;

	};
	struct NamespaceDef : BaseDef {
		bool hasQNamespace = false;
	};

	class Moc : public Parser
	{
	public:
		Moc ()
			: noInclude (false), mustIncludeQPluginH (false)
		{}

		QByteArray filename;

		bool noInclude;
		bool mustIncludeQPluginH;
		QByteArray includePath;
		std::vector<QByteArray> includeFiles;
		std::vector<ClassDef> classList;
		std::unordered_map/*QMap*/<QByteArray, QByteArray> interface2IdMap;
		std::vector<QByteArray> metaTypes;
		// map from class name to fully qualified name
		std::unordered_map/*QHash*/<QByteArray, QByteArray> knownQObjectClasses;
		std::unordered_map/*QHash*/<QByteArray, QByteArray> knownGadgets;
		std::unordered_map/*QMap*/<std::string, QJsonArray> metaArgs;

		void parse ();
		void generate (FILE *out);

		bool parseClassHead (ClassDef *def);
		inline bool inClass (const ClassDef *def) const {
			return index > def->begin && index < def->end - 1;
		}

		inline bool inNamespace (const NamespaceDef *def) const {
			return index > def->begin && index < def->end - 1;
		}

		Type parseType ();

		bool parseEnum (EnumDef *def);

		bool parseFunction (FunctionDef *def, bool inMacro = false);
		bool parseMaybeFunction (const ClassDef *cdef, FunctionDef *def);

		void parseSlots (ClassDef *def, FunctionDef::Access access);
		void parseSignals (ClassDef *def);
		void parseProperty (ClassDef *def);
		void parsePluginData (ClassDef *def);
		void createPropertyDef (PropertyDef &def);
		void parseEnumOrFlag (BaseDef *def, bool isFlag);
		void parseFlag (BaseDef *def);
		void parseClassInfo (BaseDef *def);
		void parseInterfaces (ClassDef *def);
		void parseDeclareInterface ();
		void parseDeclareMetatype ();
		void parseSlotInPrivate (ClassDef *def, FunctionDef::Access access);
		void parsePrivateProperty (ClassDef *def);

		void parseFunctionArguments (FunctionDef *def);

		QByteArray lexemUntil (Token);
		bool until (Token);

		// test for Q_INVOCABLE, Q_SCRIPTABLE, etc. and set the flags
		// in FunctionDef accordingly
		bool testFunctionAttribute (FunctionDef *def);
		bool testFunctionAttribute (Token tok, FunctionDef *def);
		bool testFunctionRevision (FunctionDef *def);

		void checkSuperClasses (ClassDef *def);
		void checkProperties (ClassDef* cdef);
	};

	inline QByteArray noRef (const QByteArray &type)
	{
		if (string_endwith (type, '&'))
		{
			if (string_endwith (type, "&&"))
				return str_left (type, type.length () - 2 );
			return str_left (type, type.length () - 1);
		}
		return type;
	}
}

#endif