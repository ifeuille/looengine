#ifndef LOO_MODULEMANAGERE_MODULEINTERFACE_H
#define LOO_MODULEMANAGERE_MODULEINTERFACE_H

namespace loo
{
	//有多种使用方法
	//直接用核心类继承它，然后load，z之后强转
	//或者转写一个自己的module 工厂，来创建核心类
	class IModuleInterface
	{
	public:

		virtual bool IsSupport ()
		{
			return true;
		}

	};
}

#define REGISTER_MODULE(ModuleImplClass,DLLEXPORTNAME)\
extern "C" DLLEXPORTNAME loo::IModuleInterface* InitializeModule() \
{ \
	return new ModuleImplClass(); \
}

#endif