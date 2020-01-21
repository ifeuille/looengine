#include "modulemanager/modulemanager.h"
#include "global/global.h"


loo::FModuleManager& loo::FModuleManager::Get ()
{
	static FModuleManager* instance = nullptr;
	static std::mutex singleton_mutex_mmgr;
	if (!instance)
	{
		std::unique_lock<std::mutex> lock (singleton_mutex_mmgr);
		if (!instance)
		{
			instance = new FModuleManager ();
		}
	}
	return *instance;
}

loo::IModuleInterface * loo::FModuleManager::GetModule (const std::string name)
{
	FModuleManager& moduleMgr = FModuleManager::Get ();
	loo::IModuleInterface* moduleInterface = nullptr;
	moduleInterface = moduleMgr.GetModuleExist (name);
	if (moduleInterface)
	{
		return moduleInterface;
	}
	else
	{
		moduleInterface = moduleMgr.LoadModule (name);
		return moduleInterface;
	}
	return nullptr;
}

void loo::FModuleManager::FreeAll ()
{
	std::unordered_map<std::string, FModuleInfo>::iterator it = Modules.begin ();
	for (; it != Modules.end (); ++it)
	{
		if (it->second.ModuleInterface)
		{
			delete it->second.ModuleInterface;
		}
		it->second.Handle->Free ();
	}
	Modules.clear ();
}

loo::IModuleInterface * loo::FModuleManager::GetModuleExist (const std::string name)
{
	std::unique_lock<std::shared_mutex> shareLock (ModulesMutex);
	std::unordered_map<std::string, FModuleInfo>::iterator it = Modules.find (name);
	if (it != Modules.end ())
	{
		FModuleInfo& info = it->second;
		if (info.IsValid&&info.ModuleInterface)
		{
			return info.ModuleInterface;
		}
	}
	return nullptr;
}

loo::IModuleInterface * loo::FModuleManager::LoadModule (const std::string name)
{
	FModuleInfo moduleinfo;
	moduleinfo.Handle = std::make_shared<DllLoader> ();
	std::unique_lock<std::shared_mutex> uniqueLock (ModulesMutex);
	if (moduleinfo.Handle->Load (name))
	{
		FInitializeModuleFunctionPtr iniPtr = (FInitializeModuleFunctionPtr)moduleinfo.Handle->GetProcAddress ("InitializeModule");
		if (iniPtr)
		{
			IModuleInterface* moduleInterface = iniPtr ();
			if (moduleInterface)
			{
				moduleinfo.IsValid = true;
				moduleinfo.ModuleInterface = moduleInterface;
#if defined(LE_DEBUG)
				loo::LogInfo () << "Load module %s success!" << name.c_str () << std::endl;;
#endif
				Modules.insert (std::make_pair (name, moduleinfo));
			}
		}
	}
	if (!moduleinfo.ModuleInterface)
	{
		std::cout<< "Load module %s failed!" << name.c_str () << std::endl;
	}
	return moduleinfo.ModuleInterface;
}

void loo::FModuleManager::FreeModuleByName (const std::string name)
{
	std::unordered_map<std::string, FModuleInfo>::iterator it = Modules.find (name);
	if (it != Modules.end ())
	{
		if (it->second.ModuleInterface)
		{
			delete it->second.ModuleInterface;
		}
		it->second.Handle->Free ();
		Modules.erase (it);
	}
}
