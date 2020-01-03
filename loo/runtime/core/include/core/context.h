#ifndef LOO_CORE_CONTEXT_H
#define LOO_CORE_CONTEXT_H
#include "dllexporter.h"
#include "global/global.h"
#include "global/utlis.h"
#include "global/thread.h"
#include "global/extstd/noncopyable.h"
#include "core/application/window.h"
#include "core/application/application.h"


#include "RHI/VideoDevice.h"
#include "ShaderLib/ShaderLibManager.h"
#include "RHI/RenderSettings.h"
#include "Application/Core.Window.h"
#include "Application/Core.Application.h"

namespace loo
{
	namespace core
	{
		struct ContextConfig
		{
			std::string video_device_name;
			std::string shaderlib_name;
			le::rhi::RenderSettings graphic_settings;
		};

		class CORE_EXPORT Context :loo::noncopyable
		{
		public:
			Context ();
			~Context ();
			static Context& Get ();
			static void Destroy ();
			void Suspend ();
			void Resume ();

#ifdef LOO_PLATFORM_ANDROID
			android_app* AppState () const
			{
				return state_;
			}
#endif
			loo::global::thread_pool& ThreadPool ();
			void Config (ContextConfig const& cfg);
			ContextConfig const& Config ()const;

			void SetApplication (Application & app)
			{
				application = &app;
			}
			bool AppValid ()const
			{
				return application != nullptr;
			}
			Application& GetApplication ()
			{
				assert (application);
				LOO_ASSUME (application);
				return *application;
			}

			/*bool VideoDeviceValid ()const
			{
				return videoDevice.get () != nullptr;
			}*/

		/*	rhi::VideoDevice& GetVideoDevice ();
			shaderlib::ShaderLibManager& GetShaderLibManager ();*/

			void LoadVideoDevice (const std::string& vd_name);
			void LoadShaderLibManager (const std::string& shaderlib_name);

		protected:
			void DestroyAll ();
		private:
			void Init ();
			Application* application;
			static std::unique_ptr<Context> contextInstance;
			std::unique_ptr<loo::global::thread_pool> threadPoolInstance;
		/*	std::unique_ptr<rhi::VideoDevice> videoDevice;
			std::unique_ptr<le::shaderlib::ShaderLibManager> shaderLibManager;*/

			ContextConfig contextConfig;
#ifdef LOO_PLATFORM_ANDROID
			android_app* state_;
#endif
		};
	}
}

#endif
