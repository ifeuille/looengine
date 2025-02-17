#include "core/context.h"
#include "global/mutex.h"
#include "filemanager/resloader.h"
//#include "RHI/CreateVideoDevice.h"
//#include "RHI/VideoDevice.h"
//#include "ShaderLib/ShaderLibManager.h"
#include "modulemanager/modulemanager.h"
#include "global/utils/log.h"

#if defined(LOO_PLATFORM_WINDOWS)
#include <windows.h>
#if defined(LOO_PLATFORM_WINDOWS_DESKTOP)
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#include <VersionHelpers.h>
#endif
#endif
#elif defined(LOO_PLATFORM_ANDROID)
#include <android_native_app_glue.h>
#endif

#if defined(LOO_PLATFORM_ANDROID) || defined(LOO_PLATFORM_IOS)
#define LOO_STATIC_LINK_PLUGINS
#endif

//#ifdef LOO_STATIC_LINK_PLUGINS
//extern "C"
//{
//	void MakeRenderFactory(std::unique_ptr<loo::core::RenderFactory>& ptr);
//	void MakeAudioFactory(std::unique_ptr<loo::core::AudioFactory>& ptr);
//	void MakeInputFactory(std::unique_ptr<loo::core::InputFactory>& ptr);
//	void MakeSceneManager(std::unique_ptr<loo::core::SceneManager>& ptr);
//	void MakeShaderLibManagerFactory(std::unique_ptr< loo::core::ShaderLibManagerFactory>& ptr);
//}
//#endif
namespace loo
{
	namespace core
	{
		std::mutex singleton_mutex;
	}
}
loo::core::Context::Context()
{
#ifdef LOO_PLATFORM_ANDROID
	state_ = get_app ();
#endif
	Init();
}
loo::core::Context::~Context()
{
}

std::unique_ptr<loo::core::Context> loo::core::Context::contextInstance = nullptr;
loo::core::Context & loo::core::Context::Get()
{
	if (!contextInstance)
	{
		loo::global::MutextUniqueLock lock(singleton_mutex);
		if (!contextInstance)
		{
			contextInstance = loo::global::MakeUniquePtr<Context>();
		}
	}
	return *contextInstance;
}

void loo::core::Context::Destroy()
{
	std::lock_guard<std::mutex> lock(singleton_mutex);
	if (contextInstance)
	{
		contextInstance->DestroyAll();
		contextInstance.reset();
	}
}

void loo::core::Context::Suspend()
{
	loo::fm::ResLoader::Instance().Suspend();
	//if (graphicDevice)
	//{
	//	graphicDevice->Suspend();
	//}
}

void loo::core::Context::Resume()
{
	loo::fm::ResLoader::Instance().Resume();
	//if (graphicDevice)
	//{
	//	graphicDevice->Resume();
	//}
}

loo::global::thread_pool & loo::core::Context::ThreadPool()
{
	return *threadPoolInstance;
}


//loo::rhi::GraphicDevice & loo::core::Context::GetGraphicDevice()
//{
//	if (!graphicDevice)
//	{
//		std::lock_guard<std::mutex> lock(singleton_mutex);
//		if (!graphicDevice)
//		{
//			this->LoadGraphicDevice(contextConfig.video_device_name);
//			graphicDevice->Init();
//		}
//	}
//	return *graphicDevice;
//}

//loo::shaderlib::ShaderLibManager & loo::core::Context::GetShaderLibManager()
//{
//	if (!shaderLibManager)
//	{
//		std::lock_guard<std::mutex> lock(singleton_mutex);
//		if (!shaderLibManager)
//		{
//			this->LoadShaderLibManager(contextConfig.shaderlib_name);
//			shaderLibManager->Init();
//		}
//	}
//	return *shaderLibManager;
//}


//#include "ShaderLib/CreateShaderLibManager.h"
//void loo::core::Context::LoadShaderLibManager(const std::string & shaderlib_name)
//{
//	shaderlib::CreateShaderLibManager(shaderLibManager, shaderlib_name);
//}


//void loo::core::Context::LoadGraphicDevice (const std::string & vd_name)
//{
//	//VulkanRHI
//	const std::string module_name = vd_name + DLL_SUFFIX;
//#ifndef LOO_STATIC_LINK_PLUGINS
//	loo::FModuleManager::Get ().FreeModuleByName (module_name);
//	loo::IModuleInterface* mi = loo::FModuleManager::Get ().LoadModule (module_name);
//	int error_code = 0;
//	if (mi)
//	{
//		loo::rhi::VideoDeviceModule* vdm = static_cast<loo::rhi::VideoDeviceModule*>(mi);
//		if (vdm)
//		{
//			vdm->CreateVideoDevice (graphicDevice);
//			if (!graphicDevice)
//			{
//				error_code = 1;
//			}
//		}
//		else
//		{
//			error_code = 2;
//		}
//	}
//	else
//	{
//		error_code = 3;
//	}
//
//
//	if (error_code != 0)
//	{
//		loo::FModuleManager::Get ().FreeModuleByName (module_name);
//		switch (error_code)
//		{
//		case 1:
//			utils::slog.e << "CORE ERROR:" << "CreateVideoDeviceWindows: vdm->CreateRHI ( ptr ) failed. " << utils::io::endl;
//			break;
//		case 2:
//			utils::slog.e << "CORE ERROR:" << "CreateVideoDeviceWindows: static_cast<le::rhi::VideoDeviceModule*>(mi)  failed." << utils::io::endl;
//			break;
//		case 3:
//			utils::slog.e << "CORE ERROR:" << "CreateVideoDeviceWindows: LoadModule " << module_name<<" failed."<< utils::io::endl;
//			break;
//		default:
//			break;
//		}
//	}
//#else
//	MakeRenderFactory (ptr);
//#endif
//}

loo::core::Application * loo::core::Context::GetApplication (int id)const
{
	auto it = apps.find (id);
	if (it == apps.end ())
	{
		return nullptr;
	}
	return it->second;
}

void loo::core::Context::SetApplication (int id, Application * app)
{
	if (!app)
	{
		return;
	}
	apps[id] = app;
}

void loo::core::Context::DestroyAll()
{
	loo::fm::ResLoader::Destroy();
	//graphicDevice.reset();
	//threadPoolInstance.reset();
}

void loo::core::Context::Init()
{
	const int minCount = 16;
	int count = std::thread::hardware_concurrency();
	count = count < minCount ? minCount : count;
	threadPoolInstance = loo::global::MakeUniquePtr<loo::global::thread_pool>(1, count);
	loo::fm::ResLoader::Instance().Init(*threadPoolInstance
#if defined(LOO_PLATFORM_ANDROID)
		, state_
#endif
	);

}
