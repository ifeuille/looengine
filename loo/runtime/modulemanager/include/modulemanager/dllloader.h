#ifndef LOO_MODULEMANAGERE_DLLLOADER_H
#define LOO_MODULEMANAGERE_DLLLOADER_H
#include "modulemanager/dllexport.h"
#include "global/global.h"
#include <string>

#if defined(LOO_COMPILER_MSVC) || defined(LOO_COMPILER_CLANGC2)
#define DLL_PREFIX ""
#else
#define DLL_PREFIX "lib"
#endif
#if defined(LOO_PLATFORM_WINDOWS)
#define DLL_EXT_NAME "dll"
#elif defined(LOO_PLATFORM_DARWIN)
#define DLL_EXT_NAME "dylib"
#else
#define DLL_EXT_NAME "so"
#endif

#define DLL_SUFFIX LOO_OUTPUT_SUFFIX "." DLL_EXT_NAME

namespace loo
{
	class DllLoader
	{
	public:
		LOOMODULEMANAGER_EXPORT DllLoader ();
		LOOMODULEMANAGER_EXPORT ~DllLoader ();

		LOOMODULEMANAGER_EXPORT bool Load (std::string const & dll_name);
		LOOMODULEMANAGER_EXPORT void Free ();

		LOOMODULEMANAGER_EXPORT void* GetProcAddress (std::string const & proc_name);

	private:
		void* dll_handle_;
	};
}
#endif