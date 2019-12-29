#include "modulemanager/dllloader.h"
#ifdef LOO_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif


namespace loo
{
	DllLoader::DllLoader ()
		: dll_handle_ (nullptr)
	{
	}

	DllLoader::~DllLoader ()
	{
		this->Free ();
	}

	bool DllLoader::Load (std::string const & dll_name)
	{
#ifdef LOO_PLATFORM_WINDOWS
#ifdef LOO_PLATFORM_WINDOWS_DESKTOP
		dll_handle_ = static_cast<void*>(::LoadLibraryExA (dll_name.c_str (), nullptr, 0));
#else
		std::wstring wname;
		Convert (wname, dll_name);
		dll_handle_ = static_cast<void*>(::LoadPackagedLibrary (wname.c_str (), 0));
#endif
#else
		dll_handle_ = ::dlopen (dll_name.c_str (), RTLD_LAZY);
#endif

		return (dll_handle_ != nullptr);
	}

	void DllLoader::Free ()
	{
		if (dll_handle_)
		{
#ifdef LOO_PLATFORM_WINDOWS
			::FreeLibrary (static_cast<HMODULE>(dll_handle_));
#else
			::dlclose (dll_handle_);
#endif
		}
	}

	void* DllLoader::GetProcAddress (std::string const & proc_name)
	{
#ifdef LOO_PLATFORM_WINDOWS
		return reinterpret_cast<void*>(::GetProcAddress (static_cast<HMODULE>(dll_handle_), proc_name.c_str ()));
#else
		return ::dlsym (dll_handle_, proc_name.c_str ());
#endif
	}
}
