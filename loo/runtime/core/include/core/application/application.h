#ifndef LOO_CORE_APPLICATION_H
#define LOO_CORE_APPLICATION_H
#include "core/dllexporter.h"
#include "global/global.h"
#include "global/extstd/noncopyable.h"
#include "global/time.h"
#include "core/application/window.h"

namespace loo
{
	namespace core
	{
		struct ContextConfig
		{
			//std::string video_device_name;
			//std::string shaderlib_name;
			//loo::rhi::RenderSettings graphic_settings;
			vkfg::RenderSettings graphic_settings;
		};

		class CORE_EXPORT Application : public loo::noncopyable
		{
		public:
			explicit Application(const std::string& name, uint32_t appid, ContextConfig setting);
			explicit Application(const std::string& name, void* native_wnd, uint32_t appid, ContextConfig setting);

			virtual ~Application();


			void Create();
			void Destroy();
			void Suspend();
			void Resume();
			void Refresh();

			WindowPtr MakeWindow(std::string const & name, vkfg::RenderSettings const & settings);
			WindowPtr MakeWindow(std::string const & name, vkfg::RenderSettings const & settings, void* native_wnd);
			WindowPtr const & MainWnd() const
			{
				return main_wnd;
			}
			uint32_t TotalNumFrames() const;
			float FPS() const;
			float AppTime() const;
			float FrameTime() const;

			void Run();
			void Quit();

			uint32_t GetAppID ()const { return app_id; }
			bool IsMainApp ()const { return app_id == 0; }
			void Config (ContextConfig const& cfg);
			ContextConfig const& Config ()const;
		protected:
			uint32_t Update(uint64_t pass);
			void UpdateStats();


		private:
			virtual bool OnCreate() { return false; }
			virtual bool OnDestroy() { return false; }
			virtual bool OnSuspend() { return false; }
			virtual bool OnResume() { return false; }
			virtual bool OnRefresh (){return false;}
			virtual bool OnResize (uint32_t width, uint32_t height);
			virtual bool DoUpdateOverlay() = 0;
			virtual uint32_t DoUpdate(uint64_t pass) = 0;
		protected:
			ContextConfig contextConfig;
			std::string name;

			// Stats
			uint32_t total_num_frames;
			float	fps;
			float	accumulate_time;
			uint32_t num_frames;

			loo::global::Timer timer;
			float app_time;
			float frame_time;
			uint64_t pass_count;

			WindowPtr main_wnd;
			uint32_t app_id;//0 is the main

		};
	}
}
#endif