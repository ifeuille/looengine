#include "Application/Core.Application.h"
#include "Core.Context.h"

le::core::Application::Application(const std::string & name)
	:Application(name, nullptr)
{

}

le::core::Application::Application(const std::string & name, void * native_wnd)
	: name(name), total_num_frames(0),
	fps(0), accumulate_time(0), num_frames(0),
	app_time(0), frame_time(0)
{
	Context::Get().SetApplication(*this);
	ContextConfig cfg = Context::Get().Config();
	main_wnd = this->MakeWindow(name, cfg.graphic_settings, native_wnd);
#ifndef LE_PLATFORM_WINDOWS_STORE
	cfg.graphic_settings.left = main_wnd->Left();
	cfg.graphic_settings.top = main_wnd->Top();
	cfg.graphic_settings.width = main_wnd->Width();
	cfg.graphic_settings.height = main_wnd->Height();
	Context::Get().Config(cfg);
#endif
}

le::core::Application::~Application()
{
	this->Destroy();
}

void le::core::Application::Create()
{
	ContextConfig cfg = Context::Get().Config();
	//TODO
	cfg.video_device_name = "VulkanRHI";
	cfg.shaderlib_name = "ShaderLib";
	Context::Get().Config(cfg);

	Context::Get().GetShaderLibManager();

	Context::Get().GetVideoDevice();// .RenderEngineInstance ().CreateRenderWindow (name, cfg.graphic_settings);




	this->OnCreate();
	this->OnResize(cfg.graphic_settings.width, cfg.graphic_settings.height);
}

void le::core::Application::Destroy()
{
	this->OnDestroy();
	if (Context::Get().VideoDeviceValid())
	{
		//Context::Get ( ).RenderFactoryInstance ( ).RenderEngineInstance ( ).DestroyRenderWindow ( );
	}

	main_wnd.reset();

	//Context::Destroy ( );
}

void le::core::Application::Suspend()
{
	this->OnSuspend();
}

void le::core::Application::Resume()
{
	this->OnResume();
}

void le::core::Application::Refresh()
{
	//Context::Instance().RenderFactoryInstance().RenderEngineInstance().Refresh();
}

le::core::WindowPtr le::core::Application::MakeWindow(std::string const & aname, rhi::RenderSettings const & settings)
{
	return MakeSharedPtr<Window>(aname, settings, nullptr);
}

le::core::WindowPtr le::core::Application::MakeWindow(std::string const & aname, rhi::RenderSettings const & settings, void * native_wnd)
{
	return MakeSharedPtr<Window>(aname, settings, native_wnd);
}

uint32_t le::core::Application::TotalNumFrames() const
{
	return total_num_frames;
}

float le::core::Application::FPS() const
{
	return fps;
}

float le::core::Application::AppTime() const
{
	return app_time;
}

float le::core::Application::FrameTime() const
{
	return frame_time;
}

void le::core::Application::Run()
{

	//RenderEngine& re = Context::Instance ( ).RenderFactoryInstance ( ).RenderEngineInstance ( );

#if defined LE_PLATFORM_WINDOWS_DESKTOP
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
			//re.Refresh ( );
		}
	}
#elif defined LE_PLATFORM_WINDOWS_STORE
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
			re.Refresh();
		}
		else
		{
			dispatcher->ProcessEvents(CoreProcessEventsOption::CoreProcessEventsOption_ProcessOneAndAllPending);
		}
	}
#elif defined LE_PLATFORM_ANDROID
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

		re.Refresh();
	}
#elif defined LE_PLATFORM_IOS
	while (!main_wnd_->Closed())
	{
		Window::PumpEvents();
		re.Refresh();
	}
#endif

	this->OnDestroy();
}

void le::core::Application::Quit()
{
#ifdef LE_PLATFORM_WINDOWS
#ifdef LE_PLATFORM_WINDOWS_DESKTOP
	::PostQuitMessage(0);
#endif
#else
	exit(0);
#endif
}

void le::core::Application::OnResize(uint32_t width, uint32_t height)
{
	LE_UNUSED(width);
	LE_UNUSED(height);
	//this->Proj(this->ActiveCamera().NearPlane(), this->ActiveCamera().FarPlane());
}

uint32_t le::core::Application::Update(uint32_t pass)
{
	if (0 == pass)
	{
		this->UpdateStats();
		this->DoUpdateOverlay();

		//ResLoader::Get ( ).Update ( );
	}

	return this->DoUpdate(pass);
}

void le::core::Application::UpdateStats()
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
