#include "core/context.h"
#include "global/mutex.h"
#include "filemanager/resloader.h"
//#include "RHI/CreateVideoDevice.h"
//#include "RHI/VideoDevice.h"
//#include "ShaderLib/ShaderLibManager.h"

#if defined(LOO_PLATFORM_ANDROID) || defined(LOO_PLATFORM_IOS)
#define LOO_STATIC_LINK_PLUGINS
#endif

#ifdef LOO_STATIC_LINK_PLUGINS
extern "C"
{
	void MakeRenderFactory(std::unique_ptr<loo::core::RenderFactory>& ptr);
	void MakeAudioFactory(std::unique_ptr<loo::core::AudioFactory>& ptr);
	void MakeInputFactory(std::unique_ptr<loo::core::InputFactory>& ptr);
	void MakeSceneManager(std::unique_ptr<loo::core::SceneManager>& ptr);
	void MakeShaderLibManagerFactory(std::unique_ptr< loo::core::ShaderLibManagerFactory>& ptr);
}
#endif
namespace loo
{
	namespace core
	{
		std::mutex singleton_mutex;
	}
}
loo::core::Context::Context()
{
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
	/*if (videoDevice)
	{
		videoDevice->Suspend();
	}*/
}

void loo::core::Context::Resume()
{
	loo::fm::ResLoader::Instance().Resume();
	//if (videoDevice)
	//{
	//	videoDevice->Resume();
	//}
}

loo::global::thread_pool & loo::core::Context::ThreadPool()
{
	return *threadPoolInstance;
}

void loo::core::Context::Config(ContextConfig const & cfg)
{
	contextConfig = cfg;
}

loo::core::ContextConfig const & loo::core::Context::Config() const
{
	return contextConfig;
}

//loo::rhi::VideoDevice & loo::core::Context::GetVideoDevice()
//{
//	if (!videoDevice)
//	{
//		std::lock_guard<std::mutex> lock(singleton_mutex);
//		if (!videoDevice)
//		{
//			this->LoadVideoDevice(contextConfig.video_device_name);
//			videoDevice->Init();
//		}
//	}
//	return *videoDevice;
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

//void loo::core::Context::LoadVideoDevice(const std::string & vd_name)
//{
//	rhi::CreateVideoDevice(videoDevice, vd_name);
//}

//#include "ShaderLib/CreateShaderLibManager.h"
//void loo::core::Context::LoadShaderLibManager(const std::string & shaderlib_name)
//{
//	shaderlib::CreateShaderLibManager(shaderLibManager, shaderlib_name);
//}

void loo::core::Context::DestroyAll()
{
	loo::fm::ResLoader::Destroy();
	//videoDevice.reset();
	//threadPoolInstance.reset();
}

void loo::core::Context::Init()
{
	const int minCount = 16;
	int count = std::thread::hardware_concurrency();
	count = count < minCount ? minCount : count;
	threadPoolInstance = loo::global::MakeUniquePtr<loo::global::thread_pool>(1, count);
	loo::fm::ResLoader::Instance().Init(*threadPoolInstance);

}
