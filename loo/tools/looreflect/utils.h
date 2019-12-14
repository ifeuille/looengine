#ifndef LOOREFLECT_UTILS_H
#define LOOREFLECT_UTILS_H

namespace loo
{

	inline bool is_whitespace (char s)
	{
		return (s == ' ' || s == '\t' || s == '\n');
	}

	inline bool is_space (char s)
	{
		return (s == ' ' || s == '\t');
	}

	inline bool is_ident_start (char s)
	{
		return ((s >= 'a' && s <= 'z')
			|| (s >= 'A' && s <= 'Z')
			|| s == '_' || s == '$'
			);
	}

	inline bool is_ident_char (char s)
	{
		return ((s >= 'a' && s <= 'z')
			|| (s >= 'A' && s <= 'Z')
			|| (s >= '0' && s <= '9')
			|| s == '_' || s == '$'
			);
	}

	inline bool is_identifier (const char *s, int len)
	{
		if (len < 1)
			return false;
		if (!is_ident_start (*s))
			return false;
		for (int i = 1; i < len; ++i)
			if (!is_ident_char (s[i]))
				return false;
		return true;
	}

	inline bool is_digit_char (char s)
	{
		return (s >= '0' && s <= '9');
	}

	inline bool is_octal_char (char s)
	{
		return (s >= '0' && s <= '7');
	}

	inline bool is_hex_char (char s)
	{
		return ((s >= 'a' && s <= 'f')
			|| (s >= 'A' && s <= 'F')
			|| (s >= '0' && s <= '9')
			);
	}

	inline const char *skipQuote (const char *data)
	{
		while (*data && (*data != '\"')) {
			if (*data == '\\') {
				++data;
				if (!*data) break;
			}
			++data;
		}

		if (*data)  //Skip last quote
			++data;
		return data;
	}
}

#endif // !LOOREFLECT_UTILS_H
