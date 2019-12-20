
#include <string>
#include <vector>
#include <list>
#include <mutex>
#include <stdlib.h>
#include <limits>
#include <cstdarg>
#include <exception>
//#include <errors.h>

//#if defined(LOO_CC_MSVC)
//#include <crtdbg.h>
//#endif
//
//#if LOO_OS_WINRT
//#include <WS2tcpip.h>
//#endif
#if defined(LOO_OS_ANDROID) && !defined(LOO_OS_ANDROID_EMBEDDED)
#include <Private/qjni_p.h>
#endif
#include "archdetect.cpp"


namespace loo{

// Statically check assumptions about the environment we're running
// in. The idea here is to error or warn if otherwise implicit Qt
// assumptions are not fulfilled on new hardware or compilers
// (if this list becomes too long, consider factoring into a separate file)
LOO_STATIC_ASSERT_X(sizeof(int) == 4, "Loo assumes that int is 32 bits");
LOO_STATIC_ASSERT_X(UCHAR_MAX == 255, "Loo assumes that char is 8 bits");
LOO_STATIC_ASSERT_X(LOO_POINTER_SIZE == sizeof(void *), "LOO_POINTER_SIZE defined incorrectly");


const char *lVersion () LOO_DECL_NOTHROW
{
    return LOO_VERSION_STR;
}

bool lSharedBuild () LOO_DECL_NOTHROW
{
#ifdef LOO_SHARED
    return true;
#else
    return false;
#endif
}

/*!
	\internal
	The Q_CHECK_PTR macro calls this function if an allocation check
	fails.
*/
void loo_check_pointer (const char *n, int l) LOO_DECL_NOTHROW
{
	// make separate printing calls so that the first one may flush;
	// the second one could want to allocate memory (fputs prints a
	// newline and stderr auto-flushes).
	fputs ("Out of memory", stderr);
	fprintf (stderr, "  in %s, line %d\n", n, l);

	std::terminate ();
}
/*
   \internal
   Allows you to throw an exception without including <new>
   Called internally from Q_CHECK_PTR on certain OS combinations
*/
void lBadAlloc ()
{
	LOO_THROW (std::bad_alloc ());
}

#ifndef LOO_NO_EXCEPTIONS
/*
   \internal
   Allows you to call std::terminate() without including <exception>.
   Called internally from QT_TERMINATE_ON_EXCEPTION
*/
void qTerminate () LOO_DECL_NOTHROW
{
	std::terminate ();
}
#endif


/*
  The Q_ASSERT macro calls this function when the test fails.
*/
void loo_assert (const char *assertion, const char *file, int line) LOO_DECL_NOTHROW
{
	//LooMessageLogger (file, line, nullptr).fatal ("ASSERT: \"%s\" in file %s, line %d", assertion, file, line);
}

/*
  The Q_ASSERT_X macro calls this function when the test fails.
*/
void loo_assert_x (const char *where, const char *what, const char *file, int line) LOO_DECL_NOTHROW
{
	//LooMessageLogger (file, line, nullptr).fatal ("ASSERT failure in %s: \"%s\", file %s, line %d", where, what, file, line);
}

// getenv is declared as deprecated in VS2005. This function
// makes use of the new secure getenv function.
/*!
	\relates <QtGlobal>

	Returns the value of the environment variable with name \a
	varName. To get the variable string, use QByteArray::constData().
	To convert the data to a QString use QString::fromLocal8Bit().

	\note qgetenv() was introduced because getenv() from the standard
	C library was deprecated in VC2005 (and later versions). qgetenv()
	uses the new replacement function in VC, and calls the standard C
	library's implementation on all other platforms.

	\warning Don't use qgetenv on Windows if the content may contain
	non-US-ASCII characters, like file paths.

	\sa qputenv(), qEnvironmentVariableIsSet(), qEnvironmentVariableIsEmpty()
*/
std::string lgetenv (const char *varName)
{
	//QMutexLocker locker (&environmentMutex);
#if defined(_MSC_VER) && _MSC_VER >= 1400
	size_t requiredSize = 0;
	std::string buffer;
	getenv_s (&requiredSize, 0, 0, varName);
	if (requiredSize == 0)
		return buffer;
	buffer.resize (int (requiredSize));
	getenv_s (&requiredSize, &buffer[0], requiredSize, varName);
	// requiredSize includes the terminating null, which we don't want.
	LOO_ASSERT (*(buffer.rbegin ()) == ('\0'));
	buffer.resize (buffer.size() - 1);
	return buffer;
#else
	return QByteArray (::getenv (varName));
#endif
}

/*!
	\relates <QtGlobal>
	\since 5.1

	Returns whether the environment variable \a varName is empty.

	Equivalent to
	\code
	qgetenv(varName).isEmpty()
	\endcode
	except that it's potentially much faster, and can't throw exceptions.

	\sa qgetenv(), qEnvironmentVariableIsSet()
*/
bool lEnvironmentVariableIsEmpty (const char *varName) LOO_DECL_NOEXCEPT
{
	//QMutexLocker locker (&environmentMutex);
#if defined(_MSC_VER) && _MSC_VER >= 1400
	// we provide a buffer that can only hold the empty string, so
	// when the env.var isn't empty, we'll get an ERANGE error (buffer
	// too small):
	size_t dummy;
	char buffer = '\0';
	return getenv_s (&dummy, &buffer, 1, varName) != ERANGE;
#else
	const char * const value = ::getenv (varName);
	return !value || !*value;
#endif
}

int lEnvironmentVariableIntValue (const char *varName, bool *ok) LOO_DECL_NOEXCEPT
{
	static const int NumBinaryDigitsPerOctalDigit = 3;
	static const int MaxDigitsForOctalInt =
		(std::numeric_limits<std::uint32_t>::digits + NumBinaryDigitsPerOctalDigit - 1) / NumBinaryDigitsPerOctalDigit;

	//QMutexLocker locker (&environmentMutex);
#if defined(_MSC_VER) && _MSC_VER >= 1400
	// we provide a buffer that can hold any int value:
	char buffer[MaxDigitsForOctalInt + 2]; // +1 for NUL +1 for optional '-'
	size_t dummy;
	if (getenv_s (&dummy, buffer, sizeof buffer, varName) != 0) {
		if (ok)
			*ok = false;
		return 0;
	}
#else
	const char * const buffer = ::getenv (varName);
	if (!buffer || strlen (buffer) > MaxDigitsForOctalInt + 2) {
		if (ok)
			*ok = false;
		return 0;
	}
#endif
	bool ok_ = true;
	char *endptr;
	const std::int64_t value = std::strtoll (buffer, &endptr, 0/*, &ok_*/);
	if (int (value) != value || *endptr != '\0') 
	{ // this is the check in QByteArray::toInt(), keep it in sync
		if (ok)
			*ok = false;
		return 0;
	}
	else if (ok) {
		*ok = ok_;
	}
	return int (value);
}
bool lEnvironmentVariableIsSet (const char *varName) LOO_DECL_NOEXCEPT
{
	//QMutexLocker locker (&environmentMutex);
#if defined(_MSC_VER) && _MSC_VER >= 1400
	size_t requiredSize = 0;
	(void)getenv_s (&requiredSize, 0, 0, varName);
	return requiredSize != 0;
#else
	return ::getenv (varName) != 0;
#endif
}

bool lputenv (const char *varName, const std::string& value)
{
	//QMutexLocker locker (&environmentMutex);
#if defined(_MSC_VER) && _MSC_VER >= 1400
	return _putenv_s (varName, value.data ()) == 0;
#elif (defined(_POSIX_VERSION) && (_POSIX_VERSION-0) >= 200112L) || defined(Q_OS_HAIKU)
	// POSIX.1-2001 has setenv
	return setenv (varName, value.constData (), true) == 0;
#else
	QByteArray buffer (varName);
	buffer += '=';
	buffer += value;
	char* envVar = lstrdup (buffer.data ());
	int result = putenv (envVar);
	if (result != 0) // error. we have to delete the string.
		delete[] envVar;
	return result == 0;
#endif
}

bool lunsetenv (const char *varName)
{
	//QMutexLocker locker (&environmentMutex);
#if defined(_MSC_VER) && _MSC_VER >= 1400
	return _putenv_s (varName, "") == 0;
#elif (defined(_POSIX_VERSION) && (_POSIX_VERSION-0) >= 200112L) || defined(Q_OS_BSD4) || defined(Q_OS_HAIKU)
	// POSIX.1-2001, BSD and Haiku have unsetenv
	return unsetenv (varName) == 0;
#elif defined(Q_CC_MINGW)
	// On mingw, putenv("var=") removes "var" from the environment
	QByteArray buffer (varName);
	buffer += '=';
	return putenv (buffer.data ()) == 0;
#else
	// Fallback to putenv("var=") which will insert an empty var into the
	// environment and leak it
	QByteArray buffer (varName);
	buffer += '=';
	char *envVar = qstrdup (buffer.data ());
	return putenv (envVar) == 0;
#endif
}

//const char* loo_error_string (int errorCode)LOO_CORE_EXPORT
//{
//	const char* str = "";
//	return str;
//}

}