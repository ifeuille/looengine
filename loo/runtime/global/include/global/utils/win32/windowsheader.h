
#pragma once

#ifdef LOO_PLATFORM_WINDOWS

#	define NOMINMAX
#	define NOMCX
#	define NOIME
#	define NOSERVICE
#	define WIN32_LEAN_AND_MEAN

# ifdef LOO_COMPILER_MSVC
#	pragma warning (push)
#	pragma warning (disable: 4668)
#	include <Windows.h>
#	pragma warning (pop)

# else
#	include <Windows.h>
# endif


#undef DeleteFile
#undef CreateWindow
#undef CreateDirectory

#endif	// PLATFORM_WINDOWS
