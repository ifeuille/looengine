#ifndef LOOREFLECT_PREPROCESSOR_H
#define LOOREFLECT_PREPROCESSOR_H

#include "parser.h"
#include <list>
#include <set>
#include <stdio.h>
#include <unordered_map>
#include "ghc/fs_std.hpp"

namespace loo
{
	struct Macro
	{
		Macro () : isFunction (false), isVariadic (false) {}
		bool isFunction;
		bool isVariadic;
		Symbols arguments;
		Symbols symbols;
	};

	typedef SubArray MacroName;

	typedef std::unordered_map<MacroName, Macro> Macros;

	class Preprocessor : public Parser
	{
	public:
		Preprocessor () {}
		static bool preprocessOnly;
		std::list<QByteArray> frameworks;
		std::set<QByteArray> preprocessedIncludes;
		std::unordered_map<QByteArray, QByteArray> nonlocalIncludePathResolutionCache;
		Macros macros;
		QByteArray resolveInclude (const QByteArray &filename, const QByteArray &relativeTo);
		//core
		Symbols preprocessed (const QByteArray &filename, std::istream& device);

		void parseDefineArguments (Macro *m);

		void skipUntilEndif ();
		bool skipBranch ();

		void substituteUntilNewline (Symbols &substituted);
		static Symbols macroExpandIdentifier (Preprocessor *that, SymbolStack &symbols, int lineNum, QByteArray *macroName);
		static void macroExpand (Symbols *into, Preprocessor *that, const Symbols &toExpand, int &index, int lineNum, bool one,
			const std::set<QByteArray> &excludeSymbols = std::set<QByteArray> ());

		int evaluateCondition ();

		enum TokenizeMode { TokenizeCpp, TokenizePreprocessor, PreparePreprocessorStatement, TokenizePreprocessorStatement, TokenizeInclude, PrepareDefine, TokenizeDefine };
		// This is the main point..
		static Symbols tokenize (const QByteArray &input, int lineNum = 1, TokenizeMode mode = TokenizeCpp);

	private:
		void until (Token t);

		void preprocess (const QByteArray &filename, Symbols &preprocessed);


	};

}

#endif // !LOOREFLECT_PREPROCESSOR_H
