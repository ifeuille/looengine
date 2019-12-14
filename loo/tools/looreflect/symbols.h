#ifndef LOOREFLECT_SYMBOLS_H
#define LOOREFLECT_SYMBOLS_H
#include "token.h"
#include <string>
#include <vector>
#include <stack>
#include <set>
typedef std::string QByteArray;

namespace loo
{
	struct SubArray
	{
		inline SubArray () :from (0), len (-1) {}
		inline SubArray (const QByteArray &a) : array (a), from (0), len (a.size ()) {}
		inline SubArray (const char *s) : array (s), from (0) { len = array.size (); }
		inline SubArray (const QByteArray &a, int from, int len) : array (a), from (from), len (len) {}
		QByteArray array;
		int from, len;
		inline bool operator==(const SubArray &other) const {
			if (len != other.len)
				return false;
			for (int i = 0; i < len; ++i)
				if (array.at (from + i) != other.array.at (other.from + i))
					return false;
			return true;
		}
	};

	inline std::uint32_t qHash (const SubArray &key)
	{
		//std::string substr = key.array.substr (key.from, key.len);
		return qHash (key.array.substr (key.from, key.len));
		//return qHash (QLatin1String (key.array.data () + key.from, key.len));
	}

	struct Symbol
	{
		inline Symbol () : lineNum (-1), token (NOTOKEN), from (0), len (-1) {}
		inline Symbol (int lineNum, Token token) :
			lineNum (lineNum), token (token), from (0), len (-1) {}
		inline Symbol (int lineNum, Token token, const QByteArray &lexem) :
			lineNum (lineNum), token (token), lex (lexem), from (0) {
			len = lex.size ();
		}
		inline Symbol (int lineNum, Token token, const QByteArray &lexem, int from, int len) :
			lineNum (lineNum), token (token), lex (lexem), from (from), len (len) {}
		int lineNum;
		Token token;
		inline QByteArray lexem () const { return lex.substr (from, len); }
		inline QByteArray unquotedLexem () const { return lex.substr (from + 1, len - 2); }
		inline operator SubArray() const { return SubArray (lex, from, len); }
		bool operator==(const Symbol& o) const
		{
			return SubArray (lex, from, len) == SubArray (o.lex, o.from, o.len);
		}
		QByteArray lex;
		int from, len;
	};

	typedef std::vector<Symbol> Symbols;

	struct SafeSymbols {
		Symbols symbols;
		QByteArray expandedMacro;
		std::set<QByteArray> excludedSymbols;
		int index;
	};

	class SymbolStack :public std::stack<SafeSymbols>
	{
	public:
		inline bool hasNext () {
			while (!empty () && top ().index >= top ().symbols.size ())
				pop ();
			return !empty ();
		}
		inline Token next () {
			while (!empty () && top ().index >= top ().symbols.size ())
				pop ();
			if (empty ())
				return NOTOKEN;
			return top ().symbols.at (top ().index++).token;
		}
		bool test (Token);
		inline const Symbol &symbol () const { return top ().symbols.at (top ().index - 1); }
		inline Token token () { return symbol ().token; }
		inline QByteArray lexem () const { return symbol ().lexem (); }
		inline QByteArray unquotedLexem () { return symbol ().unquotedLexem (); }

		bool dontReplaceSymbol (const QByteArray &name);
		std::set<QByteArray> excludeSymbols ();
	};

	inline bool SymbolStack::test (Token token)
	{
		int stackPos = size () - 1;
		while (stackPos >= 0 && c.at (stackPos).index >= c.at (stackPos).symbols.size ())
			--stackPos;
		if (stackPos < 0)
			return false;
		if (c.at (stackPos).symbols.at (c.at (stackPos).index).token == token) {
			next ();
			return true;
		}
		return false;
	}

	inline bool SymbolStack::dontReplaceSymbol (const QByteArray &name)
	{
		for (int i = 0; i < size (); ++i) {
			if (name == c.at (i).expandedMacro || c.at (i).excludedSymbols.find (name) != c.at (i).excludedSymbols.end())
				return true;
		}
		return false;
	}

	inline std::set<QByteArray> SymbolStack::excludeSymbols ()
	{
		std::set<QByteArray> set;
		for (int i = 0; i < size (); ++i) {
			set.insert (c.at (i).expandedMacro);
			auto symbols = c.at (i).excludedSymbols;
			for (auto it = symbols.end (); it != symbols.begin (); --it)
			{
				set.insert (*it);
			}
			/*set << c.at (i).expandedMacro;
			set += c.at (i).excludedSymbols;*/
		}
		return set;
	}

}

#endif // !LOOREFLECT_SYMBOLS_H
