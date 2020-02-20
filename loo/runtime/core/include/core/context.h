#ifndef LOO_CORE_CONTEXT_H
#define LOO_CORE_CONTEXT_H
#include "dllexporter.h"
#include "global/global.h"
#include "global/utlis.h"
#include "global/thread.h"
#include "global/extstd/noncopyable.h"
#include "core/application/window.h"
#include "core/application/application.h"

//#include "rhi/rendersettings.h"
//#include "rhi/graphicdevice.h"
//#include "ShaderLib/ShaderLibManager.h"
//#include "RHI/RenderSettings.h"
//#include "Application/Core.Window.h"
//#include "Application/Core.Application.h"

namespace loo
{
	namespace core
	{
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

			//void SetApplication (Application & app)
			//{
			//	application = &app;
			//}
			//bool AppValid ()const
			//{
			//	return application != nullptr;
			//}
			//Application& GetApplication ()
			//{
			//	assert (application);
			//	LOO_ASSUME (application);
			//	return *application;
			//}
			void SetApplication (int id, Application* app);
			Application* GetApplication (int id)const;

			/*bool VideoDeviceValid ()const
			{
				return graphicDevice.get () != nullptr;
			}*/

			//rhi::GraphicDevice& GetGraphicDevice ();
			//shaderlib::ShaderLibManager& GetShaderLibManager ();

			//void LoadGraphicDevice (const std::string& vd_name);
			//void LoadShaderLibManager (const std::string& shaderlib_name);

		protected:
			void DestroyAll ();
		private:
			void Init ();
			//Application* application;//main
			std::unordered_map<int, Application*> apps;
			static std::unique_ptr<Context> contextInstance;
			std::unique_ptr<loo::global::thread_pool> threadPoolInstance;
			//std::unique_ptr<rhi::GraphicDevice> graphicDevice;
			//std::unique_ptr<loo::shaderlib::ShaderLibManager> shaderLibManager;

#ifdef LOO_PLATFORM_ANDROID
			android_app* state_;
#endif
		};
	}
}

#endif
