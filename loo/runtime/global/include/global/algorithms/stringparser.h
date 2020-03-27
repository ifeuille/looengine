
#pragma once

#include "global/algorithms/stringutils.h"

namespace loo
{

	//
	// String Parser
	//

	struct StringParser final
	{
	public:
		static void  ToEndOfLine (nonstd::string_view str,  size_t &pos);
		static void  ToBeginOfLine (nonstd::string_view str,  size_t &pos);
		static void  ToNextLine (nonstd::string_view str,  size_t &pos);
		static void  ToPrevLine (nonstd::string_view str,  size_t &pos);

		ND_ static bool  IsBeginOfLine (nonstd::string_view str, size_t pos);
		ND_ static bool  IsEndOfLine (nonstd::string_view str, size_t pos);

		ND_ static size_t CalculateNumberOfLines (nonstd::string_view str);

		static bool  MoveToLine (nonstd::string_view str,  size_t &pos, size_t lineNumber);

		static void  ReadCurrLine (nonstd::string_view str,  size_t &pos, OUT nonstd::string_view &result);
		static void  ReadLineToEnd (nonstd::string_view str,  size_t &pos, OUT nonstd::string_view &result);

		static bool  ReadTo (nonstd::string_view str, nonstd::string_view endSymbol,  size_t &pos, OUT nonstd::string_view &result);

		static bool  ReadString (nonstd::string_view str,  size_t &pos, OUT nonstd::string_view &result);
	};


}
