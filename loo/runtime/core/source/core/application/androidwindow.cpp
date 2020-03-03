

#include "global/global.h"
#ifdef LOO_PLATFORM_ANDROID

#include <android/window.h>
#include "global/math/math.h"
#include "global/utlis.h"
#include "core/application/application.h"
#include "core/application/window.h"


namespace loo
{
	namespace core
	{
		Window::Window(std::string const & name, RenderSettings const & settings, Application* _app, void* native_wnd)
				: active_(false), ready_(false), closed_(false), keep_screen_on_(settings.keep_screen_on),
                app(_app), dpi_scale_(1), effective_dpi_scale_(1), win_rotation_(WR_Identity)
		{
			KFL_UNUSED(name);

			a_window_ = static_cast<ANativeWindow*>(native_wnd);

			android_app* state = Context::Instance().AppState();
			state->userData = this;
			state->onAppCmd = HandleCMD;
			state->onInputEvent = HandleInput;

			while (nullptr == a_window_)
			{
				// Read all pending events.
				int ident;
				int events;
				android_poll_source* source;

				do
				{
					ident = ALooper_pollAll(0, nullptr, &events, reinterpret_cast<void**>(&source));

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
				} while ((nullptr == a_window_) && (ident >= 0));
			}

			left_ = settings.left;
			top_ = settings.top;
			width_ = ANativeWindow_getWidth(a_window_);
			height_ = ANativeWindow_getHeight(a_window_);

			if (keep_screen_on_)
			{
				ANativeActivity_setWindowFlags(state->activity, AWINDOW_FLAG_KEEP_SCREEN_ON, 0);
			}
		}

		Window::~Window()
		{
			if (keep_screen_on_)
			{
				android_app* state = Context::Instance().AppState();
				ANativeActivity_setWindowFlags(state->activity, 0, AWINDOW_FLAG_KEEP_SCREEN_ON);
			}
		}

		void Window::HandleCMD(android_app* app, int32_t cmd)
		{
			Window* win = static_cast<Window*>(app->userData);
			switch (cmd)
			{
				case APP_CMD_SAVE_STATE:
					Context::Instance().AppInstance().Suspend();
					break;

				case APP_CMD_RESUME:
					if (win->ready_)
					{
						Context::Instance().AppInstance().Resume();
					}
					break;

				case APP_CMD_INIT_WINDOW:
					win->a_window_ = app->window;
					break;

				case APP_CMD_TERM_WINDOW:
					win->OnClose()(*win);
					win->active_ = false;
					win->ready_ = false;
					win->closed_ = true;
					break;

				case APP_CMD_GAINED_FOCUS:
					win->active_ = true;
					win->ready_ = true;
					win->OnActive()(*win, true);
					break;

				case APP_CMD_LOST_FOCUS:
					win->active_ = false;
					win->OnActive()(*win, false);
					break;

				case APP_CMD_WINDOW_RESIZED:
				case APP_CMD_CONTENT_RECT_CHANGED:
					win->left_ = app->contentRect.left;
					win->top_ = app->contentRect.top;
					win->width_ = app->contentRect.right;
					win->height_ = app->contentRect.bottom;
					win->active_ = true;
					win->ready_ = true;
					win->OnSize()(*win, true);
					break;
			}
		}

		int32_t Window::HandleInput(android_app* app, AInputEvent* event)
		{
			Input& input = app->GetInput ();
			return input.InputProc (app,event);
		}
	}

}

#endif
