#ifndef LOOREFLECT_UTILS_H
#define LOOREFLECT_UTILS_H
typedef std::string QByteArray;
#define LOO_FALLTHROUGH() (void)0
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
	inline std::string str_left (const std::string& s, std::size_t len)
	{
		return s.substr (0, len);
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
}

#endif // !LOOREFLECT_UTILS_H
