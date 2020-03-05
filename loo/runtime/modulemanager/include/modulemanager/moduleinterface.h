#ifndef LOO_MODULEMANAGERE_MODULEINTERFACE_H
#define LOO_MODULEMANAGERE_MODULEINTERFACE_H
#include "modulemanager/dllexport.h"
namespace loo
{
	//�ж���ʹ�÷���
	//ֱ���ú�����̳�����Ȼ��load��z֮��ǿת
	//����תдһ���Լ���module ������������������
	class LOOMODULEMANAGER_EXPORT IModuleInterface
	{
	public:
		virtual ~IModuleInterface () {}
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