
#include "global/algorithms/stringparser.h"
#include "global/math/math.h"
#include "global/extstd/defaulttypes.h"
#include "global/utils/log.h"

namespace loo
{

	/*
	=================================================
		ToEndOfLine
	=================================================
	*/
	void StringParser::ToEndOfLine (nonstd::string_view str,  size_t &pos)
	{
		if (pos < str.length () and ((str[pos] == '\n') | (str[pos] == '\r')))
			return;

		while (pos < str.length ())
		{
			const char	n = (pos + 1) >= str.length () ? 0 : str[pos + 1];

			++pos;

			if ((n == '\n') | (n == '\r'))
				return;
		}
	}

	/*
	=================================================
		ToBeginOfLine
	=================================================
	*/
	void StringParser::ToBeginOfLine (nonstd::string_view str,  size_t &pos)
	{
		pos = std::min (pos, str.length ());

		while (pos <= str.length ())
		{
			const char	p = (pos - 1) >= str.length () ? '\0' : str[pos - 1];

			if ((p == '\n') | (p == '\r') | (p == '\0'))
				return;

			--pos;
		}
		pos = 0;
	}

	/*
	=================================================
		IsBeginOfLine
	=================================================
	*/
	bool StringParser::IsBeginOfLine (nonstd::string_view str, const size_t pos)
	{
		size_t	p = pos;
		ToBeginOfLine (str,  p);
		return p == pos;
	}

	/*
	=================================================
		IsEndOfLine
	=================================================
	*/
	bool StringParser::IsEndOfLine (nonstd::string_view str, const size_t pos)
	{
		size_t	p = pos;
		ToEndOfLine (str,  p);
		return p == pos;
	}

	/*
	=================================================
		ToNextLine
	=================================================
	*/
	void StringParser::ToNextLine (nonstd::string_view str,  size_t &pos)
	{
		while (pos < str.length ())
		{
			const char	c = str[pos];
			const char	n = (pos + 1) >= str.length () ? 0 : str[pos + 1];

			++pos;

			// windows style "\r\n"
			if ((c == '\r') & (n == '\n'))
			{
				++pos;
				return;
			}

			// linux style "\n" (or mac style "\r")
			if ((c == '\n') | (c == '\r'))
				return;
		}
	}

	/*
	=================================================
		ToPrevLine
	=================================================
	*/
	void StringParser::ToPrevLine (nonstd::string_view str,  size_t &pos)
	{
		pos = std::min (pos, str.length ());

		while (pos <= str.length ())
		{
			const char	c = str[pos];
			const char	p = (pos - 1) >= str.length () ? 0 : str[pos - 1];

			--pos;

			// windows style "\r\n"
			if ((p == '\r') & (c == '\n'))
			{
				--pos;
				return;
			}

			// linux style "\n" (or mac style "\r")
			if ((p == '\n') | (p == '\r'))
				return;
		}
	}

	/*
	=================================================
		CalculateNumberOfLines
	=================================================
	*/
	size_t  StringParser::CalculateNumberOfLines (nonstd::string_view str)
	{
		size_t	lines = 0;

		for (size_t pos = 0; pos < str.length (); ++lines)
		{
			ToNextLine (str,  pos);
		}
		return lines;
	}

	/*
	=================================================
		MoveToLine
	=================================================
	*/
	bool StringParser::MoveToLine (nonstd::string_view str,  size_t &pos, size_t lineNumber)
	{
		size_t	lines = 0;

		for (; (pos < str.length ()) & (lines < lineNumber); ++lines)
		{
			ToNextLine (str,  pos);
		}
		return lines == lineNumber;
	}

	/*
	=================================================
		ReadCurrLine
	---
		Read line from begin of line to end of line
		and move to next line.
	=================================================
	*/
	void StringParser::ReadCurrLine (nonstd::string_view str,  size_t &pos, OUT nonstd::string_view &result)
	{
		ToBeginOfLine (str,  pos);

		ReadLineToEnd (str,  pos, OUT result);
	}

	/*
	=================================================
		ReadLineToEnd
	----
		Read line from current position to end of line
		and move to next line.
	=================================================
	*/
	void StringParser::ReadLineToEnd (nonstd::string_view str,  size_t &pos, OUT nonstd::string_view &result)
	{
		const size_t	prev_pos = pos;

		ToEndOfLine (str,  pos);

		result = str.substr (prev_pos, pos - prev_pos);

		ToNextLine (str,  pos);
	}

	/*
	=================================================
		ReadString
	----
		read string from " to "
	=================================================
	*/
	bool StringParser::ReadString (nonstd::string_view str,  size_t &pos, OUT nonstd::string_view &result)
	{
		result = Default;

		for (; pos < str.length (); ++pos)
		{
			if (str[pos] == '"')
				break;
		}

		CHECK (str[pos] == '"');

		const size_t	begin = ++pos;

		for (; pos < str.length (); ++pos)
		{
			const char	c = str[pos];

			if (c == '"')
			{
				result = nonstd::string_view{ str.data () + begin, pos - begin };
				++pos;
				return true;
			}
		}

		RETURN_ERR ("no pair for bracket \"");
	}

	/*
	=================================================
		ReadTo
	----
		read from 'pos' to symbol 'endSymbol'
	=================================================
	*/
	bool StringParser::ReadTo (nonstd::string_view str, nonstd::string_view endSymbol,  size_t &pos, OUT nonstd::string_view &result)
	{
		result = Default;

		size_t	start = pos;
		pos = str.find (endSymbol, start);

		if (pos == nonstd::string_view::npos)
			RETURN_ERR ("end symbol not found");

		result = str.substr (start, pos);
		return true;
	}


}
