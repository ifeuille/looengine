#ifndef LOO_MODULEMANAGER_MODULEMANAGER_H
#define LOO_MODULEMANAGER_MODULEMANAGER_H
#include "modulemanager/dllexport.h"
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <string>
#include <shared_mutex>
#include "modulemanager/moduleinterface.h"
#include "modulemanager/dllloader.h"

namespace loo
{
	typedef IModuleInterface* (*FInitializeModuleFunctionPtr)(void);

	class LOOMODULEMANAGER_EXPORT FModuleManager
	{
	protected:
		struct FModuleInfo
		{
			std::string Name;
			std::shared_ptr<DllLoader> Handle;
			bool IsValid;
			IModuleInterface* ModuleInterface;
			FModuleInfo () :Name (), Handle (nullptr), IsValid (false), ModuleInterface (nullptr) {}
		};
	public:
		static FModuleManager& Get ();
		static IModuleInterface* GetModule (const std::string name);
		void FreeAll ();
		//bool IsModuleLoaded ( const std::string name );
		IModuleInterface* GetModuleExist (const std::string name);
		IModuleInterface* LoadModule (const std::string name);

		void FreeModule(const std::string name);
	private:
		std::unordered_map<std::string, FModuleInfo> Modules;
		std::shared_mutex ModulesMutex;
	};
}

#endif