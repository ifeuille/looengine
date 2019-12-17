#include "looreflect.h"
#include "generator.h"
#include <ctime>
#include "utils.h"
#include "outputrevision.h"
#include "ghc/fs_std.hpp"

#include <Private/loometaobject_reflect_p.h>
#include <algorithm>

namespace loo
{
	// only  needs this function
	static QByteArray normalizeType (const QByteArray &ba, bool fixScope = false)
	{
		const char *s = ba.data ();
		int len = ba.size ();
		char stackbuf[64];
		char *buf = (len >= 64 ? new char[len + 1] : stackbuf);
		char *d = buf;
		char last = 0;
		while (*s && is_space (*s))
			s++;
		while (*s) {
			while (*s && !is_space (*s))
				last = *d++ = *s++;
			while (*s && is_space (*s))
				s++;
			if (*s && ((is_ident_char (*s) && is_ident_char (last))
				|| ((*s == ':') && (last == '<')))) {
				last = *d++ = ' ';
			}
		}
		*d = '\0';
		QByteArray result = normalizeTypeInternal (buf, d, fixScope);
		if (buf != stackbuf)
			delete[] buf;
		return result;
	}

	bool LooReflect::parseClassHead (ClassDef * def)
	{
		// figure out whether this is a class declaration, or only a
	   // forward or variable declaration.
		int i = 0;
		Token token;
		do {
			token = lookup (i++);
			if (token == COLON || token == LBRACE)
				break;
			if (token == SEMIC || token == RANGLE)
				return false;
		} while (token);

		if (!test (IDENTIFIER)) // typedef struct { ... }
			return false;
		QByteArray name = lexem ();

		// support "class IDENT name" and "class IDENT(IDENT) name"
		// also support "class IDENT name (final|sealed|LOO_DECL_FINAL)"
		if (test (LPAREN)) {
			until (RPAREN);
			if (!test (IDENTIFIER))
				return false;
			name = lexem ();
		}
		else  if (test (IDENTIFIER)) {
			const QByteArray lex = lexem ();
			if (lex != "final" && lex != "sealed" && lex != "LOO_DECL_FINAL")
				name = lex;
		}

		def->qualified += name;
		while (test (SCOPE)) {
			def->qualified += lexem ();
			if (test (IDENTIFIER)) {
				name = lexem ();
				def->qualified += name;
			}
		}
		def->classname = name;

		if (test (IDENTIFIER)) {
			const QByteArray lex = lexem ();
			if (lex != "final" && lex != "sealed" && lex != "LOO_DECL_FINAL")
				return false;
		}

		if (test (COLON)) {
			do {
				test (VIRTUAL);
				FunctionDef::Access access = FunctionDef::Public;
				if (test (PRIVATE))
					access = FunctionDef::Private;
				else if (test (PROTECTED))
					access = FunctionDef::Protected;
				else
					test (PUBLIC);
				test (VIRTUAL);
				const QByteArray type = parseType ().name;
				// ignore the 'class Foo : BAR(Baz)' case
				if (test (LPAREN)) {
					until (RPAREN);
				}
				else {
					def->superclassList.push_back(std::make_pair (type, access));
				}
			} while (test (COMMA));

			if (!def->superclassList.empty ()
				&& knownGadgets.find (def->superclassList.begin ()->first) != knownGadgets.end()) {
				// Q_GADGET subclasses are treated as Q_GADGETs
				knownGadgets.insert (def->classname, def->qualified);
				knownGadgets.insert (def->qualified, def->qualified);
			}
		}
		if (!test (LBRACE))
			return false;
		def->begin = index - 1;
		bool foundRBrace = until (RBRACE);
		def->end = index;
		index = def->begin + 1;
		return foundRBrace;
	}
	
	Type LooReflect::parseType ()
	{
		Type type;
		bool hasSignedOrUnsigned = false;
		bool isVoid = false;
		type.firstToken = lookup ();
		for (;;) {
			switch (next ()) {
			case SIGNED:
			case UNSIGNED:
				hasSignedOrUnsigned = true;
				LOO_FALLTHROUGH ();
			case LOO_CONST:
			case VOLATILE:
				type.name += lexem ();
				type.name += ' ';
				if (lookup (0) == VOLATILE)
					type.isVolatile = true;
				continue;
			case LOO_REFLECT_COMPAT_TOKEN:
			case LOO_INVOKABLE_TOKEN:
			case LOO_SCRIPTABLE_TOKEN:
			case LOO_SIGNALS_TOKEN:
			case LOO_SLOTS_TOKEN:
			case LOO_SIGNAL_TOKEN:
			case LOO_SLOT_TOKEN:
				type.name += lexem ();
				return type;
			case NOTOKEN:
				return type;
			default:
				prev ();
				break;
			}
			break;
		}
		test (ENUM) || test (CLASS) || test (STRUCT);
		for (;;) {
			switch (next ()) {
			case IDENTIFIER:
				// void mySlot(unsigned myArg)
				if (hasSignedOrUnsigned) {
					prev ();
					break;
				}
				LOO_FALLTHROUGH ();
			case CHAR:
			case SHORT:
			case INT:
			case LONG:
				type.name += lexem ();
				// preserve '[unsigned] long long', 'short int', 'long int', 'long double'
				if (test (LONG) || test (INT) || test (DOUBLE)) {
					type.name += ' ';
					prev ();
					continue;
				}
				break;
			case FLOAT:
			case DOUBLE:
			case LOO_VOID:
			case BOOL:
				type.name += lexem ();
				isVoid |= (lookup (0) == LOO_VOID);
				break;
			case NOTOKEN:
				return type;
			default:
				prev ();
				;
			}
			if (test (LANGLE)) {
				if (type.name.empty ()) {
					// '<' cannot start a type
					return type;
				}
				type.name += lexemUntil (RANGLE);
			}
			if (test (SCOPE)) {
				type.name += lexem ();
				type.isScoped = true;
			}
			else {
				break;
			}
		}
		while (test (LOO_CONST) || test (VOLATILE) || test (SIGNED) || test (UNSIGNED)
			|| test (STAR) || test (AND) || test (ANDAND)) {
			type.name += ' ';
			type.name += lexem ();
			if (lookup (0) == AND)
				type.referenceType = Type::Reference;
			else if (lookup (0) == ANDAND)
				type.referenceType = Type::RValueReference;
			else if (lookup (0) == STAR)
				type.referenceType = Type::Pointer;
		}
		type.rawName = type.name;
		// transform stupid things like 'const void' or 'void const' into 'void'
		if (isVoid && type.referenceType == Type::NoReference) {
			type.name = "void";
		}
		return type;
	}

	bool LooReflect::parseEnum (EnumDef * def)
	{
		bool isTypdefEnum = false; // typedef enum { ... } Foo;

		if (test (CLASS))
			def->isEnumClass = true;

		if (test (IDENTIFIER)) {
			def->name = lexem ();
		}
		else {
			if (lookup (-1) != TYPEDEF)
				return false; // anonymous enum
			isTypdefEnum = true;
		}
		if (test (COLON)) { // C++11 strongly typed enum
			// enum Foo : unsigned long { ... };
			parseType (); //ignore the result
		}
		if (!test (LBRACE))
			return false;
		do {
			if (lookup () == RBRACE) // accept trailing comma
				break;
			next (IDENTIFIER);
			def->values.push_back(lexem ());
		} while (test (EQ) ? until (COMMA) : test (COMMA));
		next (RBRACE);
		if (isTypdefEnum) {
			if (!test (IDENTIFIER))
				return false;
			def->name = lexem ();
		}
		return true;
	}

	void LooReflect::parseFunctionArguments (FunctionDef * def)
	{
		(void) (def);
		while (hasNext ()) {
			ArgumentDef  arg;
			arg.type = parseType ();
			if (arg.type.name == "void")
				break;
			if (test (IDENTIFIER))
				arg.name = lexem ();
			while (test (LBRACK)) {
				arg.rightType += lexemUntil (RBRACK);
			}
			if (test (LOO_CONST) || test (VOLATILE)) {
				arg.rightType += ' ';
				arg.rightType += lexem ();
			}
			arg.normalizedType = normalizeType (QByteArray (arg.type.name + ' ' + arg.rightType));
			arg.typeNameForCast = normalizeType (QByteArray (noRef (arg.type.name) + "(*)" + arg.rightType));
			if (test (EQ))
				arg.isDefault = true;
			def->arguments.push_back(arg);
			if (!until (COMMA))
				break;
		}

		if (!def->arguments.empty ()
			&& def->arguments.rbegin ()->normalizedType == "QPrivateSignal") {
			def->arguments.pop_back ();
			def->isPrivateSignal = true;
		}
	}

	bool LooReflect::testFunctionAttribute (FunctionDef * def)
	{
		if (index < symbols.size () && testFunctionAttribute (symbols.at (index).token, def)) {
			++index;
			return true;
		}
		return false;
	}

	bool LooReflect::testFunctionAttribute (Token tok, FunctionDef * def)
	{
		switch (tok) {
		case LOO_REFLECT_COMPAT_TOKEN:
			def->isCompat = true;
			return true;
		case LOO_INVOKABLE_TOKEN:
			def->isInvokable = true;
			return true;
		case LOO_SIGNAL_TOKEN:
			def->isSignal = true;
			return true;
		case LOO_SLOT_TOKEN:
			def->isSlot = true;
			return true;
		case LOO_SCRIPTABLE_TOKEN:
			def->isInvokable = def->isScriptable = true;
			return true;
		default: break;
		}
		return false;
	}

	bool LooReflect::testFunctionRevision (FunctionDef * def)
	{
		if (test (LOO_REVISION_TOKEN)) {
			next (LPAREN);
			QByteArray revision = lexemUntil (RPAREN);
			revision.erase (0, 1);
			revision.resize (revision.size () - 1);
			vector_chop (revision, 1);
			//revision.chop (1);
			bool ok = false;
			def->revision = toIntegral_helper<int>(revision.c_str (),&ok,0);
			if (!ok || def->revision < 0)
				error ("Invalid revision");
			return true;
		}

		return false;
	}


	bool LooReflect::parseFunction (FunctionDef * def, bool inMacro)
	{
		def->isVirtual = false;
		def->isStatic = false;
		//skip modifiers and attributes
		while (test (INLINE) || (test (STATIC) && (def->isStatic = true) == true) ||
			(test (VIRTUAL) && (def->isVirtual = true) == true) //mark as virtual
			|| testFunctionAttribute (def) || testFunctionRevision (def)) {
		}
		bool templateFunction = (lookup () == TEMPLATE);
		def->type = parseType ();
		if (def->type.name.empty ()) {
			if (templateFunction)
				error ("Template function as signal or slot");
			else
				error ();
		}
		bool scopedFunctionName = false;
		if (test (LPAREN)) {
			def->name = def->type.name;
			scopedFunctionName = def->type.isScoped;
			def->type = Type ("int");
		}
		else {
			Type tempType = parseType ();;
			while (!tempType.name.empty () && lookup () != LPAREN) {
				if (testFunctionAttribute (def->type.firstToken, def))
					; // fine
				else if (def->type.firstToken == LOO_SIGNALS_TOKEN)
					error ();
				else if (def->type.firstToken == LOO_SLOTS_TOKEN)
					error ();
				else {
					if (!def->tag.empty ())
						def->tag += ' ';
					def->tag += def->type.name;
				}
				def->type = tempType;
				tempType = parseType ();
			}
			next (LPAREN, "Not a signal or slot declaration");
			def->name = tempType.name;
			scopedFunctionName = tempType.isScoped;
		}

		// we don't support references as return types, it's too dangerous
		if (def->type.referenceType == Type::Reference) {
			QByteArray rawName = def->type.rawName;
			def->type = Type ("void");
			def->type.rawName = rawName;
		}

		def->normalizedType = normalizeType (def->type.name);

		if (!test (RPAREN)) {
			parseFunctionArguments (def);
			next (RPAREN);
		}

		// support optional macros with compiler specific options
		while (test (IDENTIFIER))
			;

		def->isConst = test (LOO_CONST);

		while (test (IDENTIFIER))
			;

		if (inMacro) {
			next (RPAREN);
			prev ();
		}
		else {
			if (test (THROW)) {
				next (LPAREN);
				until (RPAREN);
			}
			if (test (SEMIC))
				;
			else if ((def->inlineCode = test (LBRACE)))
				until (RBRACE);
			else if ((def->isAbstract = test (EQ)))
				until (SEMIC);
			else
				error ();
		}

		if (scopedFunctionName) {
			const QByteArray msg = "Function declaration " + def->name
				+ " contains extra qualification. Ignoring as signal or slot.";
			warning (msg.data ());
			return false;
		}
		return true;
	}

	bool LooReflect::parseMaybeFunction (const ClassDef * cdef, FunctionDef * def)
	{
		def->isVirtual = false;
		def->isStatic = false;
		//skip modifiers and attributes
		while (test (EXPLICIT) || test (INLINE) || (test (STATIC) && (def->isStatic = true) == true) ||
			(test (VIRTUAL) && (def->isVirtual = true) == true) //mark as virtual
			|| testFunctionAttribute (def) || testFunctionRevision (def)) {
		}
		bool tilde = test (TILDE);
		def->type = parseType ();
		if (def->type.name.empty ())
			return false;
		bool scopedFunctionName = false;
		if (test (LPAREN)) {
			def->name = def->type.name;
			scopedFunctionName = def->type.isScoped;
			if (def->name == cdef->classname) {
				def->isDestructor = tilde;
				def->isConstructor = !tilde;
				def->type = Type ();
			}
			else {
				def->type = Type ("int");
			}
		}
		else {
			Type tempType = parseType ();;
			while (!tempType.name.empty () && lookup () != LPAREN) {
				if (testFunctionAttribute (def->type.firstToken, def))
					; // fine
				else if (def->type.name == "LOO_SIGNAL")
					def->isSignal = true;
				else if (def->type.name == "LOO_SLOT")
					def->isSlot = true;
				else {
					if (!def->tag.empty ())
						def->tag += ' ';
					def->tag += def->type.name;
				}
				def->type = tempType;
				tempType = parseType ();
			}
			if (!test (LPAREN))
				return false;
			def->name = tempType.name;
			scopedFunctionName = tempType.isScoped;
		}

		// we don't support references as return types, it's too dangerous
		if (def->type.referenceType == Type::Reference) {
			QByteArray rawName = def->type.rawName;
			def->type = Type ("void");
			def->type.rawName = rawName;
		}

		def->normalizedType = normalizeType (def->type.name);

		if (!test (RPAREN)) {
			parseFunctionArguments (def);
			if (!test (RPAREN))
				return false;
		}
		def->isConst = test (LOO_CONST);
		if (scopedFunctionName
			&& (def->isSignal || def->isSlot || def->isInvokable)) {
			const QByteArray msg = "parsemaybe: Function declaration " + def->name
				+ " contains extra qualification. Ignoring as signal or slot.";
			warning (msg.data ());
			return false;
		}
		return true;
	}

	void LooReflect::parse ()
	{
		std::vector<NamespaceDef> namespaceList;
		bool templateClass = false;
		while (hasNext ()) {
			Token t = next ();
			switch (t) {
			case NAMESPACE: {
				int rewind = index;
				if (test (IDENTIFIER)) {
					QByteArray nsName = lexem ();
					LooStringList nested;
					while (test (SCOPE)) {
						next (IDENTIFIER);
						nested.append (nsName);
						nsName = lexem ();
					}
					if (test (EQ)) {
						// namespace Foo = Bar::Baz;
						until (SEMIC);
					}
					else if (test (LPAREN)) {
						// Ignore invalid code such as: 'namespace __identifier("x")' (QTBUG-56634)
						until (RPAREN);
					}
					else if (!test (SEMIC)) {
						NamespaceDef def;
						def.classname = nsName;

						next (LBRACE);
						def.begin = index - 1;
						until (RBRACE);
						def.end = index;
						index = def.begin + 1;

						const bool parseNamespace = currentFilenames.size () <= 1;
						if (parseNamespace) {
							for (int i = namespaceList.size () - 1; i >= 0; --i) {
								if (inNamespace (&namespaceList.at (i))) {
									def.qualified = namespaceList.at (i).classname + "::" + def.qualified;
								}
							}
							for (const QByteArray &ns : nested) {
								NamespaceDef parentNs;
								parentNs.classname = ns;
								parentNs.qualified = def.qualified;
								def.qualified += ns + "::";
								parentNs.begin = def.begin;
								parentNs.end = def.end;
								namespaceList.push_back(parentNs);
							}
						}

						while (parseNamespace && inNamespace (&def) && hasNext ()) {
							switch (next ()) {
							case NAMESPACE:
								if (test (IDENTIFIER)) {
									while (test (SCOPE))
										next (IDENTIFIER);
									if (test (EQ)) {
										// namespace Foo = Bar::Baz;
										until (SEMIC);
									}
									else if (!test (SEMIC)) {
										until (RBRACE);
									}
								}
								break;
							case LOO_NAMESPACE_TOKEN:
								def.hasQNamespace = true;
								break;
							case LOO_ENUMS_TOKEN:
							case LOO_ENUM_NS_TOKEN:
								parseEnumOrFlag (&def, false);
								break;
							case LOO_ENUM_TOKEN:
								error ("Q_ENUM can't be used in a Q_NAMESPACE, use Q_ENUM_NS instead");
								break;
							case LOO_FLAGS_TOKEN:
							case LOO_FLAG_NS_TOKEN:
								parseEnumOrFlag (&def, true);
								break;
							case LOO_FLAG_TOKEN:
								error ("Q_FLAG can't be used in a Q_NAMESPACE, use Q_FLAG_NS instead");
								break;
							case LOO_DECLARE_FLAGS_TOKEN:
								parseFlag (&def);
								break;
							case LOO_CLASSINFO_TOKEN:
								parseClassInfo (&def);
								break;
							case ENUM: {
								EnumDef enumDef;
								if (parseEnum (&enumDef))
									def.enumList.push_back(enumDef);
							} break;
							case CLASS:
							case STRUCT: {
								ClassDef classdef;
								if (!parseClassHead (&classdef))
									continue;
								while (inClass (&classdef) && hasNext ())
									next (); // consume all Q_XXXX macros from this class
							} break;
							default: break;
							}
						}
						namespaceList.push_back(def);
						index = rewind;
						if (!def.hasQNamespace && (!def.classInfoList.empty () || !def.enumDeclarations.empty ()))
							error ("Namespace declaration lacks LOO_NAMESPACE macro.");
					}
				}
				break;
			}
			case SEMIC:
			case RBRACE:
				templateClass = false;
				break;
			case TEMPLATE:
				templateClass = true;
				break;
			case LOO_INCLUDE_BEGIN:
				currentFilenames.push (symbol ().unquotedLexem ());
				break;
			case LOO_INCLUDE_END:
				currentFilenames.pop ();
				break;
			case LOO_DECLARE_INTERFACE_TOKEN:
				parseDeclareInterface ();
				break;
			case LOO_DECLARE_METATYPE_TOKEN:
				parseDeclareMetatype ();
				break;
			case USING:
				if (test (NAMESPACE)) {
					while (test (SCOPE) || test (IDENTIFIER))
						;
					// Ignore invalid code such as: 'using namespace __identifier("x")' (QTBUG-63772)
					if (test (LPAREN))
						until (RPAREN);
					next (SEMIC);
				}
				break;
			case CLASS:
			case STRUCT: {
				if (currentFilenames.size () <= 1)
					break;

				ClassDef def;
				if (!parseClassHead (&def))
					continue;

				while (inClass (&def) && hasNext ()) {
					switch (next ()) {
					case LOO_OBJECT_TOKEN:
						def.hasQObject = true;
						break;
					case LOO_GADGET_TOKEN:
						def.hasQGadget = true;
						break;
					default: break;
					}
				}

				if (!def.hasQObject && !def.hasQGadget)
					continue;

				for (int i = namespaceList.size () - 1; i >= 0; --i)
					if (inNamespace (&namespaceList.at (i)))
						def.qualified=namespaceList.at (i).classname + "::"+ def.qualified;

				std::unordered_map<QByteArray, QByteArray> &classHash = def.hasQObject ? knownQObjectClasses : knownGadgets;
				classHash.insert (def.classname, def.qualified);
				classHash.insert (def.qualified, def.qualified);

				continue; }
			default: break;
			}
			if ((t != CLASS && t != STRUCT) || currentFilenames.size () > 1)
				continue;
			ClassDef def;
			if (parseClassHead (&def)) {
				FunctionDef::Access access = FunctionDef::Private;
				for (int i = namespaceList.size () - 1; i >= 0; --i)
					if (inNamespace (&namespaceList.at (i)))
						def.qualified = namespaceList.at (i).classname + "::" + def.qualified;
				while (inClass (&def) && hasNext ()) {
					switch ((t = next ())) {
					case PRIVATE:
						access = FunctionDef::Private;
						if (test (LOO_SIGNALS_TOKEN))
							error ("Signals cannot have access specifier");
						break;
					case PROTECTED:
						access = FunctionDef::Protected;
						if (test (LOO_SIGNALS_TOKEN))
							error ("Signals cannot have access specifier");
						break;
					case PUBLIC:
						access = FunctionDef::Public;
						if (test (LOO_SIGNALS_TOKEN))
							error ("Signals cannot have access specifier");
						break;
					case CLASS: {
						ClassDef nestedDef;
						if (parseClassHead (&nestedDef)) {
							while (inClass (&nestedDef) && inClass (&def)) {
								t = next ();
								if (t >= LOO_META_TOKEN_BEGIN && t < LOO_META_TOKEN_END)
									error ("Meta object features not supported for nested classes");
							}
						}
					} break;
					case LOO_SIGNALS_TOKEN:
						parseSignals (&def);
						break;
					case LOO_SLOTS_TOKEN:
						switch (lookup (-1)) {
						case PUBLIC:
						case PROTECTED:
						case PRIVATE:
							parseSlots (&def, access);
							break;
						default:
							error ("Missing access specifier for slots");
						}
						break;
					case LOO_OBJECT_TOKEN:
						def.hasQObject = true;
						if (templateClass)
							error ("Template classes not supported by LOO_OBJECT");
						if (def.classname != "loo" && def.classname != "LooObject" && def.superclassList.empty ())
							error ("Class contains LOO_OBJECT macro but does not inherit from LooObject");
						break;
					case LOO_GADGET_TOKEN:
						def.hasQGadget = true;
						if (templateClass)
							error ("Template classes not supported by LOO_GADGET");
						break;
					case LOO_PROPERTY_TOKEN:
						parseProperty (&def);
						break;
					case LOO_PLUGIN_METADATA_TOKEN:
						parsePluginData (&def);
						break;
					case LOO_ENUMS_TOKEN:
					case LOO_ENUM_TOKEN:
						parseEnumOrFlag (&def, false);
						break;
					case LOO_ENUM_NS_TOKEN:
						error ("LOO_ENUM_NS can't be used in a LOO_OBJECT/LOO_GADGET, use LOO_ENUM instead");
						break;
					case LOO_FLAGS_TOKEN:
					case LOO_FLAG_TOKEN:
						parseEnumOrFlag (&def, true);
						break;
					case LOO_FLAG_NS_TOKEN:
						error ("LOO_FLAG_NS can't be used in a LOO_OBJECT/LOO_GADGET, use LOO_FLAG instead");
						break;
					case LOO_DECLARE_FLAGS_TOKEN:
						parseFlag (&def);
						break;
					case LOO_CLASSINFO_TOKEN:
						parseClassInfo (&def);
						break;
					case LOO_INTERFACES_TOKEN:
						parseInterfaces (&def);
						break;
					case LOO_PRIVATE_SLOT_TOKEN:
						parseSlotInPrivate (&def, access);
						break;
					case LOO_PRIVATE_PROPERTY_TOKEN:
						parsePrivateProperty (&def);
						break;
					case ENUM: {
						EnumDef enumDef;
						if (parseEnum (&enumDef))
							def.enumList.push_back(enumDef);
					} break;
					case SEMIC:
					case COLON:
						break;
					default:
						FunctionDef funcDef;
						funcDef.access = access;
						int rewind = index--;
						if (parseMaybeFunction (&def, &funcDef)) {
							if (funcDef.isConstructor) {
								if ((access == FunctionDef::Public) && funcDef.isInvokable) {
									def.constructorList.push_back(funcDef);
									while (funcDef.arguments.size () > 0 && funcDef.arguments.rbegin ()->isDefault) {
										funcDef.wasCloned = true;
										funcDef.arguments.pop_back ();
										def.constructorList.push_back(funcDef);
									}
								}
							}
							else if (funcDef.isDestructor) {
								// don't care about destructors
							}
							else {
								if (access == FunctionDef::Public)
									def.publicList.push_back(funcDef);
								if (funcDef.isSlot) {
									def.slotList.push_back(funcDef);
									while (funcDef.arguments.size () > 0 && funcDef.arguments.rbegin ()->isDefault) {
										funcDef.wasCloned = true;
										funcDef.arguments.pop_back ();
										def.slotList.push_back(funcDef);
									}
									if (funcDef.revision > 0)
										++def.revisionedMethods;
								}
								else if (funcDef.isSignal) {
									def.signalList.push_back(funcDef);
									while (funcDef.arguments.size () > 0 && funcDef.arguments.rbegin ()->isDefault) {
										funcDef.wasCloned = true;
										funcDef.arguments.pop_back ();
										def.signalList.push_back(funcDef);
									}
									if (funcDef.revision > 0)
										++def.revisionedMethods;
								}
								else if (funcDef.isInvokable) {
									def.methodList.push_back(funcDef);
									while (funcDef.arguments.size () > 0 && funcDef.arguments.rbegin ()->isDefault) {
										funcDef.wasCloned = true;
										funcDef.arguments.pop_back ();
										def.methodList.push_back(funcDef);
									}
									if (funcDef.revision > 0)
										++def.revisionedMethods;
								}
							}
						}
						else {
							index = rewind;
						}
					}
				}

				next (RBRACE);

				if (!def.hasQObject && !def.hasQGadget && def.signalList.empty () && def.slotList.empty ()
					&& def.propertyList.empty () && def.enumDeclarations.empty ())
					continue; // no meta object code required


				if (!def.hasQObject && !def.hasQGadget)
					error ("Class declaration lacks LOO_OBJECT macro.");

				// Add meta tags to the plugin meta data:
				if (!def.pluginData.iid.empty ())
					def.pluginData.metaArgs = metaArgs;

				checkSuperClasses (&def);
				checkProperties (&def);

				classList.push_back(def);
				std::unordered_map<QByteArray, QByteArray> &classHash = def.hasQObject ? knownQObjectClasses : knownGadgets;
				classHash.insert (def.classname, def.qualified);
				classHash.insert (def.qualified, def.qualified);
			}
		}
		for (const auto &n : std::as_const (namespaceList)) {
			if (!n.hasQNamespace)
				continue;
			ClassDef def;
			static_cast<BaseDef &>(def) = static_cast<BaseDef>(n);
			def.qualified += def.classname;
			def.hasQGadget = true;
			auto it = std::find_if (classList.begin (), classList.end (), [&def](const ClassDef &val) {
				return def.classname == val.classname && def.qualified == val.qualified;
			});
		
			if (it != classList.end ()) {
				it->classInfoList.insert(it->classInfoList.end(), def.classInfoList.begin(), def.classInfoList.end());
				it->enumDeclarations = def.enumDeclarations;//?
				//it->enumDeclarations.unite (def.enumDeclarations);
				it->enumList.insert(it->enumList.end(),def.enumList.begin(), def.enumList.end());
				it->flagAliases = (def.flagAliases);
				//it->flagAliases.unite (def.flagAliases);
			}
			else {
				knownGadgets.insert (def.classname, def.qualified);
				knownGadgets.insert (def.qualified, def.qualified);
				classList.push_back(def);
			}
		}
	}


	static bool any_type_contains (const std::vector<PropertyDef> &properties, const QByteArray &pattern)
	{
		for (const auto &p : properties) {
			if (std::find (p.type.begin (), p.type.end (), pattern) != p.type.end())
			{
				return true;
			}
		}
		return false;
	}

	static bool any_arg_contains (const std::vector<FunctionDef> &functions, const QByteArray &pattern)
	{
		for (const auto &f : functions) {
			for (const auto &arg : f.arguments) {
				if(std::find(arg.normalizedType.begin(), arg.normalizedType.end(), pattern) != arg.normalizedType.end())
					return true;
			}
		}
		return false;
	}

	static LooStringList make_candidates ()
	{
		LooStringList result;
		result
#define STREAM_SMART_POINTER(SMART_POINTER) << #SMART_POINTER
			QT_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER (STREAM_SMART_POINTER)
#undef STREAM_SMART_POINTER
#define STREAM_1ARG_TEMPLATE(TEMPLATENAME) << #TEMPLATENAME
			QT_FOR_EACH_AUTOMATIC_TEMPLATE_1ARG (STREAM_1ARG_TEMPLATE)
#undef STREAM_1ARG_TEMPLATE
			;
		return result;
	}

	static QByteArrayList requiredQtContainers (const QVector<ClassDef> &classes)
	{
		static const QByteArrayList candidates = make_candidates ();

		QByteArrayList required;
		required.reserve (candidates.size ());

		for (const auto &candidate : candidates) {
			const QByteArray pattern = candidate + '<';

			for (const auto &c : classes) {
				if (any_type_contains (c.propertyList, pattern) ||
					any_arg_contains (c.slotList, pattern) ||
					any_arg_contains (c.signalList, pattern) ||
					any_arg_contains (c.methodList, pattern)) {
					required.push_back (candidate);
					break;
				}
			}
		}

		return required;
	}


	void LooReflect::generate (FILE * out)
	{
	}

	void LooReflect::parseSlots (ClassDef * def, FunctionDef::Access access)
	{
	}

	void LooReflect::parseSignals (ClassDef * def)
	{
	}

	void LooReflect::parseProperty (ClassDef * def)
	{
	}

	void LooReflect::parsePluginData (ClassDef * def)
	{
	}

	void LooReflect::createPropertyDef (PropertyDef & def)
	{
	}

	void LooReflect::parseEnumOrFlag (BaseDef * def, bool isFlag)
	{
	}

	void LooReflect::parseFlag (BaseDef * def)
	{
	}

	void LooReflect::parseClassInfo (BaseDef * def)
	{
	}

	void LooReflect::parseInterfaces (ClassDef * def)
	{
	}

	void LooReflect::parseDeclareInterface ()
	{
	}

	void LooReflect::parseDeclareMetatype ()
	{
	}

	void LooReflect::parseSlotInPrivate (ClassDef * def, FunctionDef::Access access)
	{
	}

	void LooReflect::parsePrivateProperty (ClassDef * def)
	{
	}

	QByteArray LooReflect::lexemUntil (Token)
	{
		return QByteArray ();
	}

	bool LooReflect::until (Token)
	{
		return false;
	}

	void LooReflect::checkSuperClasses (ClassDef * def)
	{
	}

	void LooReflect::checkProperties (ClassDef * cdef)
	{
	}

}