#ifndef LOOREFLECT_UTILS_H
#define LOOREFLECT_UTILS_H
typedef std::string QByteArray;
#define LOO_FALLTHROUGH() (void)0
#include <iostream>

namespace loo
{
	inline void lWarning (const std::string& msg)
	{
		std::cout << msg.c_str () << std::endl;
	}

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


	template<typename T,typename U>
	inline int GetIndexOf (const T& t,const U& u )
	{
		int pos = -1;
		auto it = std::find (t.begin (), t.end (), u);
		if (it != t.end ())
		{
			pos = it - t.begin ();
		}
		return pos;
	}


	inline bool char_isspace (char c) {
		unsigned short  ucs4 = (unsigned short)((unsigned char)(c));
		return ucs4 == 0x20 || (ucs4 <= 0x0d && ucs4 >= 0x09)
			|| (ucs4 > 127 && (ucs4 == 0x85 || ucs4 == 0xa0 /*|| QChar::isSpace_helper (ucs4)*/));
	}
	inline QByteArray string_left (const QByteArray& that,int len)
	{
		if (len > that.size ())
		{
			return that;
		}
		if (len < 0)
		{
			len = 0;
		}
		return QByteArray (that.data (), len);
	}

	inline int string_indexof (const std::string& str, const std::string& value)
	{
		return str.find (value);
	}

	inline int string_indexof (const std::string& str, const char& value)
	{
		string_indexof (str, &value);
	}
	inline bool string_startwith (const std::string& str, const char& c)
	{
		if (str.size () > 0)
		{
			return str[0] == c;
		}
		return false;
	}

	inline bool string_endwith (const std::string& str, const char& c)
	{
		if (str.size () > 0)
		{
			return (*str.rbegin ()) == c;
		}
		return false;
	}

	inline std::string string_relace_all (std::string& str, const std::string& old_value, const std::string& new_value)
	{
		using std::string;
		while (true) {
			string::size_type   pos (0);
			if ((pos = str.find (old_value)) != string::npos)
				str.replace (pos, old_value.length (), new_value);
			else   break;
		}
		return   str;
	}
	inline std::string string_relace_all (std::string& str, const char& old_value, const char& new_value) {
		return string_relace_all (str, &old_value, &new_value);
	}

	inline bool string_endwith (const std::string& s, const std::string& sub) {
		return s.rfind (sub) == (s.length () - sub.length ()) ? true : false;
	}
	inline bool string_startwith (const std::string& s, const std::string& sub) {
		return s.find (sub) == 0 ? true : false;
	}
	inline std::string string_left (const std::string& s, std::size_t len)
	{
		return s.substr (0, len);
	}

	inline std::string string_leftJustified (const std::string& str, int width, char fill = ' ', bool truncate = false)
	{
		std::string result;
		int len = str.length ();
		int padlen = width - len;
		if (padlen > 0) {
			result.resize (len + padlen);
			if (len)
				memcpy (&result[0], str.data (), sizeof (char)*len);
			char *uc = (char*)&result[0] + len;
			while (padlen--)
				* uc++ = fill;
		}
		else {
			if (truncate)
				result = string_left (str,width);
			else
				result = str;
		}
		return result;
	}

	template<typename T>
	inline T container_last (T& v) {
		assert (v.size () > 0);
		return v[v.size () - 1];
	}

	template<typename T>
	inline void container_chop (T& v, int n)
	{
		if (n > 0)
		{
			int newSize = v.size () - n;
			if (newSize < 0)
			{
				newSize = 0;
			}
			v.resize (newSize);
		}
	}

	template<typename T>
	inline bool container_contains (const T& v, const T::value_type& value)
	{
		if (std::find (v.begin (), v.end (), value) != v.end())
		{
			return true;
		}
		return false;
	}
	template<typename T>
	inline T v_clamp (const T& mi, const T& value, const T& ma)
	{
		reutrn std::max (min, std::min (value, ma));
	}


	inline std::vector<std::string> string_split (const std::string& strtem, char a)
	{
		using namespace std;
		vector<string> strvec;

		string::size_type pos1, pos2;
		pos2 = strtem.find (a);
		pos1 = 0;
		while (string::npos != pos2)
		{
			strvec.push_back (strtem.substr (pos1, pos2 - pos1));

			pos1 = pos2 + 1;
			pos2 = strtem.find (a, pos1);
		}
		strvec.push_back (strtem.substr (pos1));
		return strvec;
	}

	//?
	inline std::string string_section (const std::string& str,char sep, int start, int end)
	{
		if(str.empty())
		{
			return str;
		}
		auto secs = string_split (str, sep);
		if (secs.size () == 0)
		{
			return "";
		}
		if (start >= secs.size () || end < 0 || start > end)
		{
			return "";
		}

		std::string ret;
		int first_i = start, last_i = end;
		for (int x = 0, i = 0; x <= end && i < secs.size (); ++i)
		{
			if (x >= start) {
				if (x == start)
					first_i = i;
				if (x == end)
					last_i = i;
				if (x > start && i > 0)
					ret += sep;
				ret += secs[i];
			}
			if (!secs[i].empty ())
			{
				++x;
			}
		}
		return ret;
	}

	std::string ws2s (const std::wstring& ws)
	{
		std::string curLocale = setlocale (LC_ALL, NULL);        // curLocale = "C";
		//setlocale (LC_ALL, "chs");
		const wchar_t* _Source = ws.c_str ();
		size_t _Dsize = 2 * ws.size () + 1;
		char *_Dest = new char[_Dsize];
		memset (_Dest, 0, _Dsize);
		wcstombs (_Dest, _Source, _Dsize);
		std::string result = _Dest;
		delete[]_Dest;
		setlocale (LC_ALL, curLocale.c_str ());
		return result;
	}

	std::wstring s2ws (const std::string& s)
	{
		//setlocale (LC_ALL, "chs");
		const char* _Source = s.c_str ();
		size_t _Dsize = s.size () + 1;
		wchar_t *_Dest = new wchar_t[_Dsize];
		wmemset (_Dest, 0, _Dsize);
		mbstowcs (_Dest, _Source, _Dsize);
		std::wstring result = _Dest;
		delete[]_Dest;
		setlocale (LC_ALL, "C");
		return result;
	}
}

#endif // !LOOREFLECT_UTILS_H
