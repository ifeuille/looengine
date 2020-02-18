#include "core/application/application.h"
#include "core/context.h"

loo::core::Application::Application (const std::string & name, uint32_t appid, ContextConfig setting)
	:Application (name, nullptr, appid, setting)
{

}

loo::core::Application::Application (const std::string & name, void * native_wnd, uint32_t appid, ContextConfig setting)
	: name(name), total_num_frames(0),
	fps(0), accumulate_time(0), num_frames(0),
	app_time(0), frame_time(0), pass_count (0), app_id(appid)
{
	Context::Get ().SetApplication (*this);
	Config (setting);
	setting = Config ();
	main_wnd = this->MakeWindow (name, setting.graphic_settings, native_wnd);
#ifndef LOO_PLATFORM_WINDOWS_STORE
	setting.graphic_settings.left = main_wnd->Left ();
	setting.graphic_settings.top = main_wnd->Top ();
	setting.graphic_settings.width = main_wnd->Width ();
	setting.graphic_settings.height = main_wnd->Height ();

	Config (setting);
#endif

}

loo::core::Application::~Application()
{
	this->Destroy();
}

void loo::core::Application::Create()
{
	ContextConfig cfg = Config ();
	//TODO
	//cfg.video_device_name = "vulkanrhi";
	//cfg.shaderlib_name = "shaderlib";
	Config (cfg);

	//Context::Get().GetShaderLibManager();

	//Context::Get().GetGraphicDevice();// .RenderEngineInstance ().CreateRenderWindow (name, cfg.graphic_settings);




	this->OnCreate();
	this->OnResize(cfg.graphic_settings.width, cfg.graphic_settings.height);
}

void loo::core::Application::Destroy()
{
	this->OnDestroy();
	//if (Context::Get().VideoDeviceValid())
	{
		//Context::Get ( ).RenderFactoryInstance ( ).RenderEngineInstance ( ).DestroyRenderWindow ( );
	}

	main_wnd.reset();

	Context::Destroy ( );
}

void loo::core::Application::Suspend()
{
	this->OnSuspend();
}

void loo::core::Application::Resume()
{
	this->OnResume();
}

void loo::core::Application::Refresh()
{
	Update (pass_count);
	this->OnRefresh ();
}

loo::core::WindowPtr loo::core::Application::MakeWindow(std::string const & aname, vkfg::RenderSettings const & settings)
{
	return MakeWindow (aname, settings, nullptr);
}

loo::core::WindowPtr loo::core::Application::MakeWindow (std::string const & aname, vkfg::RenderSettings const & settings,void * native_wnd)
{
	return loo::global::MakeSharedPtr<Window>(aname, settings, this, native_wnd);
}

uint32_t loo::core::Application::TotalNumFrames() const
{
	return total_num_frames;
}

float loo::core::Application::FPS() const
{
	return fps;
}

float loo::core::Application::AppTime() const
{
	return app_time;
}

float loo::core::Application::FrameTime() const
{
	return frame_time;
}

void loo::core::Application::Run()
{

	//RenderEngine& re = Context::Instance ( ).RenderFactoryInstance ( ).RenderEngineInstance ( );

#if defined LOO_PLATFORM_WINDOWS_DESKTOP
	bool gotMsg;
	MSG  msg;

	::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		// 如果窗口是激活的，用 PeekMessage()以便我们可以用空闲时间渲染场景
		// 不然, 用 GetMessage() 减少 CPU 占用率
		if (main_wnd->Active())
		{
			gotMsg = (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0);
		}
		else
		{
			gotMsg = (::GetMessage(&msg, nullptr, 0, 0) != 0);
		}

		if (gotMsg)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			Refresh ();
		}
	}
#elif defined LOO_PLATFORM_WINDOWS_STORE
	ComPtr<ICoreWindowStatic> core_win_stat;
	TIFHR(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(),
		&core_win_stat));

	ComPtr<ICoreWindow> core_win;
	core_win_stat->GetForCurrentThread(&core_win);

	ComPtr<ICoreDispatcher> dispatcher;
	core_win->get_Dispatcher(&dispatcher);

	while (!main_wnd_->Closed())
	{
		if (main_wnd_->Active())
		{
			dispatcher->ProcessEvents(CoreProcessEventsOption::CoreProcessEventsOption_ProcessAllIfPresent);
			Refresh ();
		}
		else
		{
			dispatcher->ProcessEvents(CoreProcessEventsOption::CoreProcessEventsOption_ProcessOneAndAllPending);
		}
	}
#elif defined LOO_PLATFORM_ANDROID
	while (!main_wnd_->Closed())
	{
		// Read all pending events.
		int ident;
		int events;
		android_poll_source* source;

		android_app* state = Context::Instance().AppState();

		do
		{
			ident = ALooper_pollAll(main_wnd_->Active() ? 0 : -1, nullptr, &events, reinterpret_cast<void**>(&source));

			// Process this event.
			if (source != nullptr)
			{
				source->process(state, source);
			}

			// Check if we are exiting.
			if (state->destroyRequested != 0)
			{
				return;
			}
		} while (ident >= 0);

		Refresh ();
	}
#elif defined LOO_PLATFORM_IOS
	while (!main_wnd_->Closed())
	{
		Window::PumpEvents();
		Refresh ();
	}
#endif

	this->OnDestroy();
}

void loo::core::Application::Quit()
{
#ifdef LOO_PLATFORM_WINDOWS
#ifdef LOO_PLATFORM_WINDOWS_DESKTOP
	::PostQuitMessage(0);
#endif
#else
	exit(0);
#endif
}


bool loo::core::Application::OnResize(uint32_t width, uint32_t height)
{
	LOO_UNUSED(width);
	LOO_UNUSED(height);
	//this->Proj(this->ActiveCamera().NearPlane(), this->ActiveCamera().FarPlane());
	return false;
}

uint32_t loo::core::Application::Update(uint64_t pass)
{
	if (0 == pass)
	{
		this->UpdateStats();
		this->DoUpdateOverlay();

		//ResLoader::Get ( ).Update ( );
	}

	return this->DoUpdate(pass);
}

void loo::core::Application::UpdateStats()
{
	++total_num_frames;

	// measure statistics
	frame_time = static_cast<float>(timer.elapsed());
	++num_frames;
	accumulate_time += frame_time;
	app_time += frame_time;

	// check if new second
	if (accumulate_time > 1)
	{
		// new second - not 100% precise
		fps = num_frames / accumulate_time;

		accumulate_time = 0;
		num_frames = 0;
	}

	timer.restart();
}

void loo::core::Application::Config (ContextConfig const & cfg)
{
	contextConfig = cfg;
}

loo::core::ContextConfig const & loo::core::Application::Config () const
{
	return contextConfig;
}