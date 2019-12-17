#ifndef LOOREFLECT_STRINGLIST_H
#define LOOREFLECT_STRINGLIST_H
#include <string>
#include <vector>
#include <initializer_list>
#include <set>
#include <limits>
#include <algorithm>

namespace loo
{
	
	class LooStringList :public  std::vector<std::string>
	{
	public:
		LooStringList () {}
		inline explicit LooStringList (const std::string & l) {push_back (l); }
		inline LooStringList (const std::vector<std::string> & l) :std::vector<std::string> (l) {}
		//inline LooStringList <const std::initializer_list<std::string> args):std::list<std::string> (args) {}
		inline bool contains (const std::string& str);
		inline LooStringList operator+(const std::vector<std::string>& other)const {
			LooStringList n = *this;n += other;return n;
		}
		inline LooStringList& operator<<(const std::string& str){
			push_back (str); return *this;
		}
		inline LooStringList& operator<<(const LooStringList& l) {
			*this += l; return *this;
		}
		inline LooStringList& operator<<(const LooStringList& l) {
			*this += l; return *this;
		}
		inline LooStringList& operator+=(const LooStringList& l) {
			insert (end(), l.begin (), l.end ());
			return *this;
		}

	public:
		inline void sort ();
		inline int removeDuplicates ();
		inline std::string join (const std::string& sep)const;
		inline std::string join (char sep)const;
		inline LooStringList fileter (const std::string& str)const;
		inline LooStringList& replaceInStrings (const std::string& before, const std::string& after);
		inline void swap (int i, int j)
		{
			std::swap (at (i), at (j));
		}
		inline void append (const std::string& s)
		{
			push_back (s);
		}
		inline void prepend (const std::string& s)
		{
			insert (begin (), s);
		}
	private:
		inline const int accumulatedSize (int seplen)const;

	};

	inline const int LooStringList::accumulatedSize (int seplen)const
	{
		int result = 0;
		if (!empty ()) {
			for (const auto &e : *this)
				result += e.size () + seplen;
			result -= seplen;
		}
		return result;
	}

	inline bool LooStringList::contains (const std::string& str)
	{
		return std::find (begin (), end (), str) != end ();		
	}

	inline void LooStringList::sort ()
	{
		std::sort (begin (), end ());
	}

	inline int LooStringList::removeDuplicates ()
	{
		std::size_t n = size ();
		int j = 0;
		std::set<std::string> seen;
		int setSize = 0;
		for (int i = 0; i < n; ++i) {
			const std::string &s = at (i);
			seen.insert (s);
			if (setSize == seen.size ()) // unchanged size => was already seen
				continue;
			++setSize;
			if (j != i)
				swap (i, j);
			++j;
		}
		if (n != j)
			erase (begin () + j, end ());
		return n - j;
	}

	inline std::string LooStringList::join (const std::string & sep) const
	{
		const int totalLength = accumulatedSize (sep.length ());
		const std::size_t num = size ();
		std::string res;
		if (totalLength == 0)
		{
			return res;
		}
		res.reserve (totalLength);
		for (int i = 0; i < num; ++i) {
			if (i)
			{
				res.append (sep.c_str (),sep.length());
			}
			res += at (i);//?
		}
		return res;
	}

	inline std::string loo::LooStringList::join (char sep) const
	{
		return join (&sep);
	}

	inline LooStringList LooStringList::fileter (const std::string & str) const
	{
		LooStringList res;
		for (std::size_t i = 0; i < size (); ++i)
		{
			if (at (i).find (str) != std::string::npos)
			{
				res << at (i);
			}
		}
		return res;
	}

	inline void StringReplace (std::string& src, const std::string& before, const std::string& after)
	{
		for (std::string::size_type pos (0); pos != std::string::npos; pos += after.length ())
		{
			pos = src.find (before, pos);
			if (pos != std::string::npos)
				src.replace (pos, before.length (), after);
			else
				break;
		}
	}
	inline void StringReplace (std::string& src, const char& before, const std::string& after)
	{
		StringReplace (src, before, after);
	}

	inline LooStringList & LooStringList::replaceInStrings (const std::string & before, const std::string & after)
	{
		for (std::size_t i = 0; i < size (); ++i)
		{
			StringReplace (at (i), before, after);
			/*for (std::string::size_type pos (0); pos != std::string::npos; pos += after.length ())
			{
				pos = at(i).find (before, pos);
				if (pos != std::string::npos)
					at (i).replace (pos, before.length (), after);
				else
					break;
			}*/
		}
		//at(i).replace (before, after);
	}

	enum {
		AsciiSpaceMask = (1u << (' ' - 1)) |
		(1u << ('\t' - 1)) |   // 9: HT - horizontal tab
		(1u << ('\n' - 1)) |   // 10: LF - line feed
		(1u << ('\v' - 1)) |   // 11: VT - vertical tab
		(1u << ('\f' - 1)) |   // 12: FF - form feed
		(1u << ('\r' - 1))
	};  // 13: CR - carriage return
	inline bool ascii_isspace (std::uint8_t c)
	{
		return c >= 1u && c <= 32u && (AsciiSpaceMask >> std::uint8_t (c - 1)) & 1u;
	}

	inline long long qstrtoll (const char * nptr, const char **endptr, int base, bool *ok)
	{
		*ok = true;
		errno = 0;
		char *endptr2 = 0;
		long long result = std::strtoll (nptr, &endptr2, base);
		if (endptr)
			*endptr = endptr2;
		if ((result == 0 || result == std::numeric_limits<long long>::min ()
			|| result == std::numeric_limits<long long>::max ())
			&& (errno || nptr == endptr2)) {
			*ok = false;
			return 0;
		}
		return result;
	}
	inline unsigned long long qstrtoull (const char * nptr, const char **endptr, int base, bool *ok)
	{
		// strtoull accepts negative numbers. We don't.
		// Use a different variable so we pass the original nptr to strtoul
		// (we need that so endptr may be nptr in case of failure)
		const char *begin = nptr;
		while (ascii_isspace (*begin))
			++begin;
		if (*begin == '-') {
			*ok = false;
			return 0;
		}

		*ok = true;
		errno = 0;
		char *endptr2 = 0;
		unsigned long long result = std::strtoull (nptr, &endptr2, base);
		if (endptr)
			*endptr = endptr2;
		if ((result == 0 || result == std::numeric_limits<unsigned long long>::max ())
			&& (errno || endptr2 == nptr)) {
			*ok = false;
			return 0;
		}
		return result;
	}
	inline static std::int64_t bytearrayToLongLong (const char *num, int base, bool *ok, bool *overflow)
	{
		bool _ok;
		const char *endptr;

		if (*num == '\0') {
			if (ok != 0)
				*ok = false;
			if (overflow != 0)
				*overflow = false;
			return 0;
		}

		std::int64_t l = qstrtoll (num, &endptr, base, &_ok);

		if (!_ok) {
			if (ok != 0)
				*ok = false;
			if (overflow != 0) {
				// the only way qstrtoll can fail with *endptr != '\0' on a non-empty
				// input string is overflow
				*overflow = *endptr != '\0';
			}
			return 0;
		}

		if (*endptr != '\0') {
			// we stopped at a non-digit character after converting some digits
			if (ok != 0)
				*ok = false;
			if (overflow != 0)
				*overflow = false;
			return 0;
		}

		if (ok != 0)
			*ok = true;
		if (overflow != 0)
			*overflow = false;
		return l;
	}
	inline static std::uint64_t bytearrayToUnsLongLong (const char *num, int base, bool *ok)
	{
		bool _ok;
		const char *endptr;
		std::uint64_t l = qstrtoull (num, &endptr, base, &_ok);

		if (!_ok || *endptr != '\0') {
			if (ok != 0)
				*ok = false;
			return 0;
		}

		if (ok != 0)
			*ok = true;
		return l;
	}
	inline static std::int64_t toIntegral_helper (const char* num, bool* ok, int base, std::int64_t)
	{
		return bytearrayToLongLong (num, base, ok, 0);
	}
	inline static std::uint64_t toIntegral_helper (const char* data, bool* ok, int base, std::uint64_t)
	{

	}

	template<typename T>static inline
		T toIntegral_helper (const char* data, bool* ok, int base) {
		const bool isUnsigend = T (0) - T (-1);
		typedef typename std::conditional<isUnsigend, std::uint64_t, std::int64_t>::type Int64;

		Int64 val = toIntegral_helper (data, ok, base, Int64 ());
		if (T (val) != val) {
			if (ok)
			{
				*ok = false;
			}
			val = 0;
		}
		return T (val);

	}

}
#endif