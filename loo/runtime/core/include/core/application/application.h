#ifndef LOO_CORE_APPLICATION_H
#define LOO_CORE_APPLICATION_H
#include "global/global.h"
#include "global/extstd/noncopyable.h"
#include "global/time.h"

namespace loo
{
	namespace core
	{
		class CORE_EXPORT Application : public loo::noncopyable
		{
		public:
			explicit Application(const std::string& name);
			explicit Application(const std::string& name, void* native_wnd);

			virtual ~Application();


			void Create();
			void Destroy();
			void Suspend();
			void Resume();
			void Refresh();

			WindowPtr MakeWindow(std::string const & name, rhi::RenderSettings const & settings);
			WindowPtr MakeWindow(std::string const & name, rhi::RenderSettings const & settings, void* native_wnd);
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

			virtual void OnResize(uint32_t width, uint32_t height);
		protected:
			uint32_t Update(uint32_t pass);
			void UpdateStats();
		private:
			virtual void OnCreate()
			{
			}
			virtual void OnDestroy()
			{
			}
			virtual void OnSuspend()
			{
			}
			virtual void OnResume()
			{
			}
			virtual void DoUpdateOverlay() = 0;
			virtual uint32_t DoUpdate(uint32_t pass) = 0;
		private:

			std::string name;

			// Stats
			uint32_t total_num_frames;
			float	fps;
			float	accumulate_time;
			uint32_t num_frames;

			loo::global::Timer timer;
			float app_time;
			float frame_time;

			WindowPtr main_wnd;

		};
	}
}
#endif