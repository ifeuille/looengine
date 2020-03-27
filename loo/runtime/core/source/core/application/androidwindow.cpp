

#include "global/global.h"
#ifdef LOO_PLATFORM_ANDROID

#include <android/window.h>
#include "global/math/math.h"
#include "global/utlis.h"
#include "core/application/application.h"
#include "core/application/window.h"
#include <android_native_app_glue.h>
#include "core/context.h"

namespace loo
{
	namespace core
	{
		Window::Window(std::string const & name, vkfg::RenderSettings const & settings, Application* _app, void* native_wnd)
				: active (false), ready (false), closed (false), keep_screen_on (settings.keep_screen_on),
                app(_app), dpi_scale (1), effective_dpi_scale (1), win_rotation (WR_Identity)
		{
			LOO_UNUSED(name);
#ifdef LOO_PLATFORM_ANDROID
			state = loo::core::Context::Get ().AppState();
#endif
			a_window = static_cast<ANativeWindow*>(native_wnd);

			state->userData = this;
			state->onAppCmd = HandleCMD;
			state->onInputEvent = HandleInput;

			while (nullptr == a_window)
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
				} while ((nullptr == a_window) && (ident >= 0));
			}

			left = settings.left;
			top = settings.top;
			width = ANativeWindow_getWidth(a_window);
			height = ANativeWindow_getHeight(a_window);

			if (keep_screen_on)
			{
				ANativeActivity_setWindowFlags(state->activity, AWINDOW_FLAG_KEEP_SCREEN_ON, 0);
			}
		}

		Window::~Window()
		{
			if (keep_screen_on)
			{
				ANativeActivity_setWindowFlags(state->activity, 0, AWINDOW_FLAG_KEEP_SCREEN_ON);
			}
		}

		void Window::HandleCMD(android_app* app, int32_t cmd)
		{
			Window* win = static_cast<Window*>(app->userData);
			Application* myapp = win->GetApp ();
			switch (cmd)
			{
				case APP_CMD_SAVE_STATE:
					myapp->Suspend();
					break;

				case APP_CMD_RESUME:
					if (win->ready)
					{
						myapp->Resume();
					}
					break;

				case APP_CMD_INIT_WINDOW:
					win->a_window = app->window;
					break;

				case APP_CMD_TERM_WINDOW:
					win->OnClose()(*win);
					win->active = false;
					win->ready = false;
					win->closed = true;
					break;

				case APP_CMD_GAINED_FOCUS:
					win->active = true;
					win->ready = true;
					win->OnActive()(*win, true);
					break;

				case APP_CMD_LOST_FOCUS:
					win->active = false;
					win->OnActive()(*win, false);
					break;

				case APP_CMD_WINDOW_RESIZED:
				case APP_CMD_CONTENT_RECT_CHANGED:
					win->left = app->contentRect.left;
					win->top = app->contentRect.top;
					win->width = app->contentRect.right;
					win->height = app->contentRect.bottom;
					win->active = true;
					win->ready = true;
					win->OnSize()(*win, true);
					break;
			}
		}

		int32_t Window::HandleInput(android_app* app, AInputEvent* event)
		{
			Window* win = static_cast<Window*>(app->userData);
			Input& input = win->GetApp ()->GetInput ();
			return input.InputProc (app,event);
		}
	}

}

#endif
