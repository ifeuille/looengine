#include "looreflect.h"
#include "generator.h"
#include <ctime>
#include "utils.h"
#include "outputrevision.h"
#include "ghc/fs_std.hpp"
#include "ghc/fs_utils.hpp"
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
				// LOO_GADGET subclasses are treated as LOO_GADGETs
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
			//revision.resize (revision.size () - 1);
			container_chop (revision, 1);
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
								def.hasLooNamespace = true;
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
						if (!def.hasLooNamespace && (!def.classInfoList.empty () || !def.enumDeclarations.empty ()))
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
						def.hasLooObject = true;
						break;
					case LOO_GADGET_TOKEN:
						def.hasLooGadget = true;
						break;
					default: break;
					}
				}

				if (!def.hasLooObject && !def.hasLooGadget)
					continue;

				for (int i = namespaceList.size () - 1; i >= 0; --i)
					if (inNamespace (&namespaceList.at (i)))
						def.qualified=namespaceList.at (i).classname + "::"+ def.qualified;

				std::unordered_map<QByteArray, QByteArray> &classHash = def.hasLooObject ? knownQObjectClasses : knownGadgets;
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
						def.hasLooObject = true;
						if (templateClass)
							error ("Template classes not supported by LOO_OBJECT");
						if (def.classname != "loo" && def.classname != "LooObject" && def.superclassList.empty ())
							error ("Class contains LOO_OBJECT macro but does not inherit from LooObject");
						break;
					case LOO_GADGET_TOKEN:
						def.hasLooGadget = true;
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

				if (!def.hasLooObject && !def.hasLooGadget && def.signalList.empty () && def.slotList.empty ()
					&& def.propertyList.empty () && def.enumDeclarations.empty ())
					continue; // no meta object code required


				if (!def.hasLooObject && !def.hasLooGadget)
					error ("Class declaration lacks LOO_OBJECT macro.");

				// Add meta tags to the plugin meta data:
				if (!def.pluginData.iid.empty ())
					def.pluginData.metaArgs = metaArgs;

				checkSuperClasses (&def);
				checkProperties (&def);

				classList.push_back(def);
				std::unordered_map<QByteArray, QByteArray> &classHash = def.hasLooObject ? knownQObjectClasses : knownGadgets;
				classHash.insert (def.classname, def.qualified);
				classHash.insert (def.qualified, def.qualified);
			}
		}
		for (const auto &n : std::as_const (namespaceList)) {
			if (!n.hasLooNamespace)
				continue;
			ClassDef def;
			static_cast<BaseDef &>(def) = static_cast<BaseDef>(n);
			def.qualified += def.classname;
			def.hasLooGadget = true;
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

	//todo
	static LooStringList make_candidates ()
	{
		//ƒ⁄÷√±‰¡ø
		LooStringList result;
		result
//#define STREAM_SMART_POINTER(SMART_POINTER) << #SMART_POINTER
//			LOO_FOR_EACH_AUTOMATIC_TEMPLATE_SMART_POINTER (STREAM_SMART_POINTER)
#undef STREAM_SMART_POINTER
//#define STREAM_1ARG_TEMPLATE(TEMPLATENAME) << #TEMPLATENAME
//			LOO_FOR_EACH_AUTOMATIC_TEMPLATE_1ARG (STREAM_1ARG_TEMPLATE)
#undef STREAM_1ARG_TEMPLATE
			;
		return result;
	}

	static LooStringList requiredLooContainers (const std::vector<ClassDef> &classes)
	{
		static const LooStringList candidates = make_candidates ();

		LooStringList required;
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
		QByteArray fn = filename;
		int i = filename.length () - 1;
		while (i > 0 && filename.at (i - 1) != '/' && filename.at (i - 1) != '\\')
			--i;                                // skip path
		if (i >= 0)
			fn = filename.substr (i);
		fprintf (out, "/****************************************************************************\n"
			"** Meta object code from reading C++ file '%s'\n**\n", fn.data ());
		fprintf (out, "** Created by: The Loo Meta Object Compiler version %d \n**\n", mocOutputRevision);
		fprintf (out, "** WARNING! All changes made in this file will be lost!\n"
			"*****************************************************************************/\n\n");


		if (!noInclude) {
			if (includePath.size () && (*(includePath.rbegin ())) != ('/'))
				includePath += '/';
			for (int i = 0; i < includeFiles.size (); ++i) {
				QByteArray inc = includeFiles.at (i);
				if (inc.at (0) != '<' && inc.at (0) != '"') {
					if (includePath.size () && includePath != "./")
						inc = (includePath) +inc;
					inc = '\"' + inc + '\"';
				}
				fprintf (out, "#include %s\n", inc.data ());
			}
		}
		if (classList.size () && classList.begin ()->classname == "Qt")
			fprintf (out, "#include LooCore/lobject.h>\n");

		fprintf (out, "#include <string>\n"); 
		fprintf (out, "#include <LooCore/lmetatype.h>\n");  // For QMetaType::Type
		if (mustIncludeQPluginH)
			fprintf (out, "#include <LooCore/lplugin.h>\n");

		const auto qtContainers = requiredLooContainers (classList);
		for (const QByteArray &qtContainer : qtContainers)
			fprintf (out, "#include <QtCore/%s>\n", qtContainer.data ());


		fprintf (out, "#if !defined(LOO_REFLECT_OUTPUT_REVISION)\n"
			"#error \"The header file '%s' doesn't include <LooObject>.\"\n", fn.data ());
		fprintf (out, "#elif LOO_REFLECT_OUTPUT_REVISION != %d\n", mocOutputRevision);
		fprintf (out, "#error \"This file was generated using the moc from %s."
			" It\"\n#error \"cannot be used with the include files from"
			" this version of Loo.\"\n#error \"(The moc has changed too"
			" much.)\"\n", "1.0.0");
		fprintf (out, "#endif\n\n");

		fprintf (out, "LOO_BEGIN_MOC_NAMESPACE\n");
		fprintf (out, "LOO_WARNING_PUSH\n");
		fprintf (out, "LOO_WARNING_DISABLE_DEPRECATED\n");

		fputs ("", out);
		for (i = 0; i < classList.size (); ++i) {
			Generator generator (&classList[i], metaTypes, knownQObjectClasses, knownGadgets, out);
			generator.generateCode ();
		}
		fputs ("", out);

		fprintf (out, "LOO_WARNING_POP\n");
		fprintf (out, "LOO_END_MOC_NAMESPACE\n");
	}

	void LooReflect::parseSlots (ClassDef * def, FunctionDef::Access access)
	{
		int defaultRevision = -1;
		if (test (LOO_REVISION_TOKEN)) {
			next (LPAREN);
			QByteArray revision = lexemUntil (RPAREN);
			revision.erase (0, 1);
			container_chop (revision, 1);
			bool ok = false;
			defaultRevision = toIntegral_helper<int> (revision.data (), &ok, 0);// revision.toInt (&ok);
			if (!ok || defaultRevision < 0)
				error ("Invalid revision");
		}

		next (COLON);
		while (inClass (def) && hasNext ()) {
			switch (next ()) {
			case PUBLIC:
			case PROTECTED:
			case PRIVATE:
			case LOO_SIGNALS_TOKEN:
			case LOO_SLOTS_TOKEN:
				prev ();
				return;
			case SEMIC:
				continue;
			case FRIEND:
				until (SEMIC);
				continue;
			case USING:
				error ("'using' directive not supported in 'slots' section");
			default:
				prev ();
			}

			FunctionDef funcDef;
			funcDef.access = access;
			if (!parseFunction (&funcDef))
				continue;
			if (funcDef.revision > 0) {
				++def->revisionedMethods;
			}
			else if (defaultRevision != -1) {
				funcDef.revision = defaultRevision;
				++def->revisionedMethods;
			}
			def->slotList.push_back(funcDef);
			while (funcDef.arguments.size () > 0 && funcDef.arguments.rbegin ()->isDefault) {
				funcDef.wasCloned = true;
				funcDef.arguments.pop_back ();
				def->slotList.push_back(funcDef);
			}
		}
	}

	void LooReflect::parseSignals (ClassDef * def)
	{
		int defaultRevision = -1;
		if (test (LOO_REVISION_TOKEN)) {
			next (LPAREN);
			QByteArray revision = lexemUntil (RPAREN);
			revision.erase (0, 1);
			container_chop (revision, 1);
			bool ok = false;
			defaultRevision = toIntegral_helper<int> (revision.data (), &ok, 0);
			if (!ok || defaultRevision < 0)
				error ("Invalid revision");
		}

		next (COLON);
		while (inClass (def) && hasNext ()) {
			switch (next ()) {
			case PUBLIC:
			case PROTECTED:
			case PRIVATE:
			case LOO_SIGNALS_TOKEN:
			case LOO_SLOTS_TOKEN:
				prev ();
				return;
			case SEMIC:
				continue;
			case FRIEND:
				until (SEMIC);
				continue;
			case USING:
				error ("'using' directive not supported in 'signals' section");
			default:
				prev ();
			}
			FunctionDef funcDef;
			funcDef.access = FunctionDef::Public;
			parseFunction (&funcDef);
			if (funcDef.isVirtual)
				warning ("Signals cannot be declared virtual");
			if (funcDef.inlineCode)
				error ("Not a signal declaration");
			if (funcDef.revision > 0) {
				++def->revisionedMethods;
			}
			else if (defaultRevision != -1) {
				funcDef.revision = defaultRevision;
				++def->revisionedMethods;
			}
			def->signalList.push_back(funcDef);
			while (funcDef.arguments.size () > 0 && funcDef.arguments.rbegin ()->isDefault) {
				funcDef.wasCloned = true;
				funcDef.arguments.pop_back ();
				def->signalList.push_back (funcDef);
			}
		}
	}

	void LooReflect::createPropertyDef (PropertyDef & propDef)
	{
		QByteArray type = parseType ().name;
		if (type.empty ())
			error ();
		propDef.designable = propDef.scriptable = propDef.stored = "true";
		propDef.user = "false";
		/*
		  The LOO_PROPERTY construct cannot contain any commas, since
		  commas separate macro arguments. We therefore expect users
		  to type "LooMap" instead of "LooMap<QString, QVariant>". For
		  coherence, we also expect the same for
		  LooValueList<QVariant>, the other template class supported by
		  LooVariant.
		*/
		type = normalizeType (type);
		if (type == "LooMap")
			type = "LooMap<LooString,LooVariant>";
		else if (type == "LooValueList")
			type = "LooValueList<LooVariant>";
		else if (type == "LongLong")
			type = "lint64";
		else if (type == "ULongLong")
			type = "luint64";

		propDef.type = type;

		next ();
		propDef.name = lexem ();
		while (test (IDENTIFIER)) {
			const QByteArray l = lexem ();
			if (l[0] == 'C' && l == "CONSTANT") {
				propDef.constant = true;
				continue;
			}
			else if (l[0] == 'F' && l == "FINAL") {
				propDef.final = true;
				continue;
			}

			QByteArray v, v2;
			if (test (LPAREN)) {
				v = lexemUntil (RPAREN);
				v = v.substr (1, v.length () - 2); // removes the '(' and ')'
			}
			else if (test (INTEGER_LITERAL)) {
				v = lexem ();
				if (l != "REVISION")
					error (1);
			}
			else {
				next (IDENTIFIER);
				v = lexem ();
				if (test (LPAREN))
					v2 = lexemUntil (RPAREN);
				else if (v != "true" && v != "false")
					v2 = "()";
			}
			switch (l[0]) {
			case 'M':
				if (l == "MEMBER")
					propDef.member = v;
				else
					error (2);
				break;
			case 'R':
				if (l == "READ")
					propDef.read = v;
				else if (l == "RESET")
					propDef.reset = v + v2;
				else if (l == "REVISION") {
					bool ok = false;
					propDef.revision = toIntegral_helper<int> (v.data (), &ok, 0);
					if (!ok || propDef.revision < 0)
						error (1);
				}
				else
					error (2);
				break;
			case 'S':
				if (l == "SCRIPTABLE")
					propDef.scriptable = v + v2;
				else if (l == "STORED")
					propDef.stored = v + v2;
				else
					error (2);
				break;
			case 'W': if (l != "WRITE") error (2);
				propDef.write = v;
				break;
			case 'D': if (l != "DESIGNABLE") error (2);
				propDef.designable = v + v2;
				break;
			case 'E': if (l != "EDITABLE") error (2);
				propDef.editable = v + v2;
				break;
			case 'N': if (l != "NOTIFY") error (2);
				propDef.notify = v;
				break;
			case 'U': if (l != "USER") error (2);
				propDef.user = v + v2;
				break;
			default:
				error (2);
			}
		}
		if (propDef.read.empty () && propDef.member.empty ()) {
			const QByteArray msg = "Property declaration " + propDef.name
				+ " has no READ accessor function or associated MEMBER variable. The property will be invalid.";
			warning (msg.data ());
		}
		if (propDef.constant && !propDef.write.empty ()) {
			const QByteArray msg = "Property declaration " + propDef.name
				+ " is both WRITEable and CONSTANT. CONSTANT will be ignored.";
			propDef.constant = false;
			warning (msg.data ());
		}
		if (propDef.constant && !propDef.notify.empty ()) {
			const QByteArray msg = "Property declaration " + propDef.name
				+ " is both NOTIFYable and CONSTANT. CONSTANT will be ignored.";
			propDef.constant = false;
			warning (msg.data ());
		}
	}

	void LooReflect::parseProperty (ClassDef * def)
	{
		next (LPAREN);
		PropertyDef propDef;
		createPropertyDef (propDef);
		next (RPAREN);

		if (!propDef.notify.empty ())
			def->notifyableProperties++;
		if (propDef.revision > 0)
			++def->revisionedProperties;
		def->propertyList.push_back(propDef);
	}

	static QByteArray readFile2String (fs::ifstream& ifs) {
		fs::ifstream::pos_type fileSize = ifs.tellg ();
		ifs.seekg (0, std::ios::beg);

		std::vector<char> bytes (fileSize);
		ifs.read (bytes.data (), fileSize);

		return QByteArray (bytes.data (), fileSize);
	}

	void LooReflect::parsePluginData (ClassDef * def)
	{
		next (LPAREN);
		QByteArray metaData;
		while (test (IDENTIFIER)) {
			QByteArray l = lexem ();
			if (l == "IID") {
				next (STRING_LITERAL);
				def->pluginData.iid = unquotedLexem ();
			}
			else if (l == "FILE") {
				next (STRING_LITERAL);
				QByteArray metaDataFile = unquotedLexem ();
				fs::directory_entry fi (
					fs::combine_path_file (currentFilenames.top ().data (),
						metaDataFile.data ())
				);
				//QFileInfo fi (QFileInfo (QString::fromLocal8Bit (currentFilenames.top ().constData ())).dir (), QString::fromLocal8Bit (metaDataFile.constData ()));
				for (int j = 0; j < includes.size () && !fi.exists (); ++j) {
					const IncludePath &p = includes.at (j);
					if (p.isFrameworkPath)
						continue;
					fi.assign (fs::combine_path_file (p.path.data (),
						metaDataFile.data ()));					
					// try again, maybe there's a file later in the include paths with the same name
					if (fi.is_directory ()) {
						fi = fs::directory_entry ();
						continue;
					}
				}
				if (!fi.exists ()) {
					const QByteArray msg = "Plugin Metadata file " + lexem ()
						+ " does not exist. Declaration will be ignored";
					error (msg.data ());
					return;
				}
				fs::ifstream file (fi.path(), std::ios::in);//?
				if (!file.is_open ())
				{
					QByteArray msg = "Plugin Metadata file " + lexem () + " could not be opened: "
						+ file.exceptions;
					error (msg.data ());
					return;
				}
				metaData = readFile2String (file);// file.readAll ();
			}
		}

		if (!metaData.empty ()) {
			def->pluginData.metaData = nlohmann::json (metaData);// QJsonDocument::fromJson (metaData);
			if (!def->pluginData.metaData.is_object ()) {
				const QByteArray msg = "Plugin Metadata file " + lexem ()
					+ " does not contain a valid JSON object. Declaration will be ignored";
				warning (msg.data ());
				def->pluginData.iid = QByteArray ();
				return;
			}
		}

		mustIncludeQPluginH = true;
		next (RPAREN);
	}

	void LooReflect::parsePrivateProperty (ClassDef * def)
	{
		next (LPAREN);
		PropertyDef propDef;
		next (IDENTIFIER);
		propDef.inPrivateClass = lexem ();
		while (test (SCOPE)) {
			propDef.inPrivateClass += lexem ();
			next (IDENTIFIER);
			propDef.inPrivateClass += lexem ();
		}
		// also allow void functions
		if (test (LPAREN)) {
			next (RPAREN);
			propDef.inPrivateClass += "()";
		}

		next (COMMA);

		createPropertyDef (propDef);

		if (!propDef.notify.empty ())
			def->notifyableProperties++;
		if (propDef.revision > 0)
			++def->revisionedProperties;

		def->propertyList.push_back(propDef);
	}

	void LooReflect::parseEnumOrFlag (BaseDef * def, bool isFlag)
	{
		next (LPAREN);
		QByteArray identifier;
		while (test (IDENTIFIER)) {
			identifier = lexem ();
			while (test (SCOPE) && test (IDENTIFIER)) {
				identifier += "::";
				identifier += lexem ();
			}
			def->enumDeclarations[identifier] = isFlag;
		}
		next (RPAREN);
	}

	void LooReflect::parseFlag (BaseDef * def)
	{
		next (LPAREN);
		QByteArray flagName, enumName;
		while (test (IDENTIFIER)) {
			flagName = lexem ();
			while (test (SCOPE) && test (IDENTIFIER)) {
				flagName += "::";
				flagName += lexem ();
			}
		}
		next (COMMA);
		while (test (IDENTIFIER)) {
			enumName = lexem ();
			while (test (SCOPE) && test (IDENTIFIER)) {
				enumName += "::";
				enumName += lexem ();
			}
		}

		def->flagAliases.insert (enumName, flagName);
		next (RPAREN);
	}

	void LooReflect::parseClassInfo (BaseDef * def)
	{
		next (LPAREN);
		ClassInfoDef infoDef;
		next (STRING_LITERAL);
		infoDef.name = symbol ().unquotedLexem ();
		next (COMMA);
		if (test (STRING_LITERAL)) {
			infoDef.value = symbol ().unquotedLexem ();
		}
		else {
			// support Q_CLASSINFO("help", QT_TR_NOOP("blah"))
			next (IDENTIFIER);
			next (LPAREN);
			next (STRING_LITERAL);
			infoDef.value = symbol ().unquotedLexem ();
			next (RPAREN);
		}
		next (RPAREN);
		def->classInfoList.push_back(infoDef);
	}

	void LooReflect::parseInterfaces (ClassDef * def)
	{
		next (LPAREN);
		while (test (IDENTIFIER)) {
			std::vector<ClassDef::Interface> iface;
			iface.push_back(ClassDef::Interface (lexem ()));
			while (test (SCOPE)) {
				iface.rbegin()->className += lexem ();
				next (IDENTIFIER);
				iface.rbegin ()->className += lexem ();
			}
			while (test (COLON)) {
				next (IDENTIFIER);
				iface.push_back(ClassDef::Interface (lexem ()));
				while (test (SCOPE)) {
					iface.rbegin ()->className += lexem ();
					next (IDENTIFIER);
					iface.rbegin ()->className += lexem ();
				}
			}
			// resolve from classnames to interface ids
			for (int i = 0; i < iface.size (); ++i) {
				const QByteArray iid = interface2IdMap.find (iface.at (i).className)->second;
				if (iid.empty ())
					error ("Undefined interface");

				iface[i].interfaceId = iid;
			}
			def->interfaceList.push_back(iface);
		}
		next (RPAREN);
	}

	void LooReflect::parseDeclareInterface ()
	{
		next (LPAREN);
		QByteArray itf;
		next (IDENTIFIER);
		itf += lexem ();
		while (test (SCOPE)) {
			itf += lexem ();
			next (IDENTIFIER);
			itf += lexem ();
		}
		next (COMMA);
		QByteArray iid;
		if (test (STRING_LITERAL)) {
			iid = lexem ();
		}
		else {
			next (IDENTIFIER);
			iid = lexem ();
		}
		interface2IdMap.insert (itf, iid);
		next (RPAREN);
	}

	void LooReflect::parseDeclareMetatype ()
	{
		next (LPAREN);
		QByteArray typeName = lexemUntil (RPAREN);
		typeName.erase (0, 1);
		container_chop (typeName, 1);
		metaTypes.push_back (typeName);
	}

	void LooReflect::parseSlotInPrivate (ClassDef * def, FunctionDef::Access access)
	{
		next (LPAREN);
		FunctionDef funcDef;
		next (IDENTIFIER);
		funcDef.inPrivateClass = lexem ();
		// also allow void functions
		if (test (LPAREN)) {
			next (RPAREN);
			funcDef.inPrivateClass += "()";
		}
		next (COMMA);
		funcDef.access = access;
		parseFunction (&funcDef, true);
		def->slotList.push_back(funcDef);
		while (funcDef.arguments.size () > 0 && funcDef.arguments.rbegin ()->isDefault) {
			funcDef.wasCloned = true;
			funcDef.arguments.pop_back ();
			def->slotList.push_back(funcDef);
		}
		if (funcDef.revision > 0)
			++def->revisionedMethods;
	}

	QByteArray LooReflect::lexemUntil (Token target)
	{
		int from = index;
		until (target);
		QByteArray s;
		while (from <= index) {
			QByteArray n = symbols.at (from++ - 1).lexem ();
			if (s.size () && n.size ()) {
				char prev = s.at (s.size () - 1);
				char next = n.at (0);
				if ((is_ident_char (prev) && is_ident_char (next))
					|| (prev == '<' && next == ':')
					|| (prev == '>' && next == '>'))
					s += ' ';
			}
			s += n;
		}
		return s;
	}

	bool LooReflect::until (Token target)
	{
		int braceCount = 0;
		int brackCount = 0;
		int parenCount = 0;
		int angleCount = 0;
		if (index) {
			switch (symbols.at (index - 1).token) {
			case LBRACE: ++braceCount; break;
			case LBRACK: ++brackCount; break;
			case LPAREN: ++parenCount; break;
			case LANGLE: ++angleCount; break;
			default: break;
			}
		}

		//when searching commas within the default argument, we should take care of template depth (anglecount)
		// unfortunatelly, we do not have enough semantic information to know if '<' is the operator< or
		// the beginning of a template type. so we just use heuristics.
		int possible = -1;

		while (index < symbols.size ()) {
			Token t = symbols.at (index++).token;
			switch (t) {
			case LBRACE: ++braceCount; break;
			case RBRACE: --braceCount; break;
			case LBRACK: ++brackCount; break;
			case RBRACK: --brackCount; break;
			case LPAREN: ++parenCount; break;
			case RPAREN: --parenCount; break;
			case LANGLE:
				if (parenCount == 0 && braceCount == 0)
					++angleCount;
				break;
			case RANGLE:
				if (parenCount == 0 && braceCount == 0)
					--angleCount;
				break;
			case GTGT:
				if (parenCount == 0 && braceCount == 0) {
					angleCount -= 2;
					t = RANGLE;
				}
				break;
			default: break;
			}
			if (t == target
				&& braceCount <= 0
				&& brackCount <= 0
				&& parenCount <= 0
				&& (target != RANGLE || angleCount <= 0)) {
				if (target != COMMA || angleCount <= 0)
					return true;
				possible = index;
			}

			if (target == COMMA && t == EQ && possible != -1) {
				index = possible;
				return true;
			}

			if (braceCount < 0 || brackCount < 0 || parenCount < 0
				|| (target == RANGLE && angleCount < 0)) {
				--index;
				break;
			}

			if (braceCount <= 0 && t == SEMIC) {
				// Abort on semicolon. Allow recovering bad template parsing (QTBUG-31218)
				break;
			}
		}

		if (target == COMMA && angleCount != 0 && possible != -1) {
			index = possible;
			return true;
		}

		return false;
	}

	void LooReflect::checkSuperClasses (ClassDef * def)
	{
		const QByteArray firstSuperclass = def->superclassList[0].first;

		if (knownQObjectClasses.find (firstSuperclass) == knownQObjectClasses.end()) {
			// enable once we /require/ include paths
#if 0
			const QByteArray msg
				= "Class "
				+ def->className
				+ " contains the LOO_OBJECT macro and inherits from "
				+ def->superclassList[0]
				+ " but that is not a known LooObject subclass. You may get compilation errors.";
			warning (msg.constData ());
#endif
			return;
		}
		for (int i = 1; i < def->superclassList.size (); ++i) {
			const QByteArray superClass = def->superclassList.at (i).first;
			if (knownQObjectClasses.find (superClass) != knownQObjectClasses.end()) {
				const QByteArray msg
					= "Class "
					+ def->classname
					+ " inherits from two LooObject subclasses "
					+ firstSuperclass
					+ " and "
					+ superClass
					+ ". This is not supported!";
				warning (msg.data ());
			}

			if (interface2IdMap.find (superClass)!= interface2IdMap.end()) {
				bool registeredInterface = false;
				for (int i = 0; i < def->interfaceList.size (); ++i)
					if (def->interfaceList.at (i).begin ()->className == superClass) {
						registeredInterface = true;
						break;
					}

				if (!registeredInterface) {
					const QByteArray msg
						= "Class "
						+ def->classname
						+ " implements the interface "
						+ superClass
						+ " but does not list it in LOO_INTERFACES. qobject_cast to "
						+ superClass
						+ " will not work!";
					warning (msg.data ());
				}
			}
		}
	}

	void LooReflect::checkProperties (ClassDef * cdef)
	{
		//
   // specify get function, for compatibiliy we accept functions
   // returning pointers, or const char * for QByteArray.
   //
		std::set<QByteArray> definedProperties;
		for (int i = 0; i < cdef->propertyList.size (); ++i) {
			PropertyDef &p = cdef->propertyList[i];
			if (p.read.empty () && p.member.empty ())
				continue;
			if (definedProperties.find (p.name) != definedProperties.end()) {
				QByteArray msg = "The property '" + p.name + "' is defined multiple times in class " + cdef->classname + ".";
				warning (msg.data ());
			}
			definedProperties.insert (p.name);

			for (int j = 0; j < cdef->publicList.size (); ++j) {
				const FunctionDef &f = cdef->publicList.at (j);
				if (f.name != p.read)
					continue;
				if (!f.isConst) // get  functions must be const
					continue;
				if (f.arguments.size ()) // and must not take any arguments
					continue;
				PropertyDef::Specification spec = PropertyDef::ValueSpec;
				QByteArray tmp = f.normalizedType;
				if (p.type == "QByteArray" && tmp == "const char *")
					tmp = "QByteArray";
				if (QByteArray_left (tmp,6) == "const ")
					tmp = tmp.substr (6);
				if (p.type != tmp && string_endwith (tmp,'*')) {
					container_chop (tmp, 1);
					spec = PropertyDef::PointerSpec;
				}
				else if (string_endwith(f.type.name ,'&')) { // raw type, not normalized type
					spec = PropertyDef::ReferenceSpec;
				}
				if (p.type != tmp)
					continue;
				p.gspec = spec;
				break;
			}
			if (!p.notify.empty ()) {
				int notifyId = -1;
				for (int j = 0; j < cdef->signalList.size (); ++j) {
					const FunctionDef &f = cdef->signalList.at (j);
					if (f.name != p.notify) {
						continue;
					}
					else {
						notifyId = j /* Signal indexes start from 0 */;
						break;
					}
				}
				p.notifyId = notifyId;
				if (notifyId == -1) {
					QByteArray msg = "NOTIFY signal '" + p.notify + "' of property '" + p.name
						+ "' does not exist in class " + cdef->classname + ".";
					error (msg.data ());
				}
			}
		}
	}

}