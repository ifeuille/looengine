#ifndef LOO_CORE_WINDOW_H
#define LOO_CORE_WINDOW_H
#include "core/dllexporter.h"
#include "global/global.h"

#if defined(LOO_COMPILER_CLANGC2)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter" // Ignore unused parameter 'sp'
#pragma clang diagnostic ignored "-Wunused-variable" // Ignore unused variable (mpl_assertion_in_line_xxx) in boost
#endif
#include "global/extstd/signal.h"
#if defined(LOO_COMPILER_CLANGC2)
#pragma clang diagnostic pop
#endif

#if defined(LOO_PLATFORM_WINDOWS)
#include <Windows.h>

#elif defined LOO_PLATFORM_ANDROID
#include <android_native_app_glue.h>
#elif defined LOO_PLATFORM_IOS
#ifdef __OBJC__
#define OBJC_CLASS(name) @class name
#else
#define OBJC_CLASS(name) typedef struct objc_object name
#endif
OBJC_CLASS(LEngineView);
OBJC_CLASS(LEngineWindow);
OBJC_CLASS(LEngineWindowListener);
OBJC_CLASS(NSView);
#endif
#include "global/utlis.h"
#include "RHI/RenderSettings.h"

#include <cstring>
#include <iostream>

namespace loo
{
	namespace core
	{

		class CORE_EXPORT Window
		{
		public:
			enum WindowRotation
			{
				WR_Unspecified,
				WR_Identity,
				WR_Rotate90,
				WR_Rotate180,
				WR_Rotate270
			};

		public:
			Window(std::string const & name, rhi::RenderSettings const & settings, void* native_wnd);
			~Window();

#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			HWND HWnd() const
			{
				return wnd;
			}
#elif defined LOO_PLATFORM_WINDOWS_STORE
			void SetWindow(std::shared_ptr<ABI::Windows::UI::Core::ICoreWindow> const & window);

			std::shared_ptr<ABI::Windows::UI::Core::ICoreWindow> GetWindow() const
			{
				return wnd_;
			}

			void OnActivated();
			void OnSizeChanged(ABI::Windows::UI::Core::IWindowSizeChangedEventArgs* args);
			void OnVisibilityChanged(ABI::Windows::UI::Core::IVisibilityChangedEventArgs* args);
			void OnClosed();
			void OnKeyDown(ABI::Windows::UI::Core::IKeyEventArgs* args);
			void OnKeyUp(ABI::Windows::UI::Core::IKeyEventArgs* args);
			void OnPointerPressed(ABI::Windows::UI::Core::IPointerEventArgs* args);
			void OnPointerReleased(ABI::Windows::UI::Core::IPointerEventArgs* args);
			void OnPointerMoved(ABI::Windows::UI::Core::IPointerEventArgs* args);
			void OnPointerWheelChanged(ABI::Windows::UI::Core::IPointerEventArgs* args);
			void OnDpiChanged();
			void OnOrientationChanged();
			void OnDisplayContentsInvalidated();

			bool FullScreen(bool fs);
#elif defined LOO_PLATFORM_ANDROID
			::ANativeWindow* AWindow() const
			{
				return a_window_;
			}
#elif defined LOO_PLATFORM_IOS
			static void PumpEvents();
			void CreateColorRenderBuffer(ElementFormat pf);
			void FlushBuffer();
			uint2 GetGLKViewSize();
#endif

		public:
			//attribes

			int32_t Left() const
			{
				return left;
			}
			int32_t Top() const
			{
				return top;
			}

			uint32_t Width() const
			{
				return width;
			}
			uint32_t Height() const
			{
				return height;
			}

			bool Active() const
			{
				return active;
			}
			void Active(bool aactive)
			{
				active = aactive;
			}
			bool Ready() const
			{
				return ready;
			}
			void Ready(bool aready)
			{
				ready = aready;
			}
			bool Closed() const
			{
				return closed;
			}
			void Closed(bool aclosed)
			{
				closed = aclosed;
			}

			float DPIScale() const
			{
				return dpi_scale;
			}
			float EffectiveDPIScale() const
			{
				return effective_dpi_scale;
			}

			WindowRotation Rotation() const
			{
				return win_rotation;
			}
		public:
			// some events
			typedef sigslot::signal<void(Window const & wnd, bool active)> ActiveEvent;
			typedef sigslot::signal<void(Window const & wnd)> PaintEvent;
			typedef sigslot::signal<void(Window const & wnd)> EnterSizeMoveEvent;
			typedef sigslot::signal<void(Window const & wnd)> ExitSizeMoveEvent;
			typedef sigslot::signal<void(Window const & wnd, bool active)> SizeEvent;
			typedef sigslot::signal<void(Window const & wnd)> SetCursorEvent;
			typedef sigslot::signal<void(Window const & wnd, wchar_t ch)> CharEvent;
#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			typedef sigslot::signal<void(Window const & wnd, HRAWINPUT ri)> RawInputEvent;
#elif defined(LOO_PLATFORM_WINDOWS_STORE) || defined(LOO_PLATFORM_ANDROID)
			typedef sigslot::signal<void(Window const & wnd, uint32 key)> KeyDownEvent;
			typedef sigslot::signal<void(Window const & wnd, uint32 key)> KeyUpEvent;
#if defined LOO_PLATFORM_ANDROID
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt, uint32_t buttons)> MouseDownEvent;
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt, uint32_t buttons)> MouseUpEvent;
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt)> MouseMoveEvent;
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt, int32_t wheel_delta)> MouseWheelEvent;
			typedef sigslot::signal<void(Window const & wnd, int32 axis, int32_t value)> JoystickAxisEvent;
			typedef sigslot::signal<void(Window const & wnd, uint32 buttons)> JoystickButtonsEvent;
#endif
#endif
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt, uint32 id)> PointerDownEvent;
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt, uint32 id)> PointerUpEvent;
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt, uint32 id, bool down)> PointerUpdateEvent;
			typedef sigslot::signal<void(Window const & wnd, vec2 const & pt, uint32 id, int32 wheel_delta)> PointerWheelEvent;

			typedef sigslot::signal<void(Window const & wnd)> CloseEvent;

		private:
			void UpdateDpiScale(float scale);
			// system call functions
#if defined LOO_PLATFORM_WINDOWS
#if defined LOO_PLATFORM_WINDOWS_DESKTOP
		private:
			static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
			static BOOL CALLBACK EnumMonProc(HMONITOR mon, HDC dc_mon, RECT* rc_mon, LPARAM lparam);
#endif
			void KeepScreenOn();

			LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#else
			void DetectsOrientation();
#endif

			void DetectsDpi();
#elif defined LOO_PLATFORM_ANDROID
		public:
			static void HandleCMD(android_app* app, int32_t cmd);
			static int32_t HandleInput(android_app* app, AInputEvent* event);
#endif
		public:

			ActiveEvent& OnActive()
			{
				return active_event;
			}
			PaintEvent& OnPaint()
			{
				return paint_event;
			}
			EnterSizeMoveEvent& OnEnterSizeMove()
			{
				return enter_size_move_event;
			}
			ExitSizeMoveEvent& OnExitSizeMove()
			{
				return exit_size_move_event;
			}
			SizeEvent& OnSize()
			{
				return size_event;
			}
			SetCursorEvent& OnSetCursor()
			{
				return set_cursor_event;
			}
			CharEvent& OnChar()
			{
				return char_event;
			}
#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			RawInputEvent& OnRawInput()
			{
				return raw_input_event;
			}
#elif defined(LOO_PLATFORM_WINDOWS_STORE) || defined(LOO_PLATFORM_ANDROID)
			KeyDownEvent& OnKeyDown()
			{
				return key_down_event_;
			}
			KeyUpEvent& OnKeyUp()
			{
				return key_up_event_;
			}
#if defined LOO_PLATFORM_ANDROID
			MouseDownEvent& OnMouseDown()
			{
				return mouse_down_event_;
			}
			MouseUpEvent& OnMouseUp()
			{
				return mouse_up_event_;
			}
			MouseMoveEvent& OnMouseMove()
			{
				return mouse_move_event_;
			}
			MouseWheelEvent& OnMouseWheel()
			{
				return mouse_wheel_event_;
			}
			JoystickAxisEvent& OnJoystickAxis()
			{
				return joystick_axis_event_;
			}
			JoystickButtonsEvent& OnJoystickButtons()
			{
				return joystick_buttons_event_;
			}
#endif
#endif
			PointerDownEvent& OnPointerDown()
			{
				return pointer_down_event;
			}
			PointerUpEvent& OnPointerUp()
			{
				return pointer_up_event;
			}
			PointerUpdateEvent& OnPointerUpdate()
			{
				return pointer_update_event;
			}
			PointerWheelEvent& OnPointerWheel()
			{
				return pointer_wheel_event;
			}
			CloseEvent& OnClose()
			{
				return close_event;
			}
		private:
			ActiveEvent active_event;
			PaintEvent paint_event;
			EnterSizeMoveEvent enter_size_move_event;
			ExitSizeMoveEvent exit_size_move_event;
			SizeEvent size_event;
			SetCursorEvent set_cursor_event;
			CharEvent char_event;
#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			RawInputEvent raw_input_event;
#elif defined(LOO_PLATFORM_WINDOWS_STORE) || defined(LOO_PLATFORM_ANDROID) 
			KeyDownEvent key_down_event_;
			KeyUpEvent key_up_event_;
#if defined LOO_PLATFORM_ANDROID
			MouseDownEvent mouse_down_event_;
			MouseUpEvent mouse_up_event_;
			MouseMoveEvent mouse_move_event_;
			MouseWheelEvent mouse_wheel_event_;
			JoystickAxisEvent joystick_axis_event_;
			JoystickButtonsEvent joystick_buttons_event_;
#endif
#endif
			PointerDownEvent pointer_down_event;
			PointerUpEvent pointer_up_event;
			PointerUpdateEvent pointer_update_event;
			PointerWheelEvent pointer_wheel_event;
			CloseEvent close_event;
		private:

			int32_t left;
			int32_t top;
			uint32_t width;
			uint32_t height;

			bool active;
			bool ready;
			bool closed;
			bool keep_screen_on;

			float dpi_scale;
			float effective_dpi_scale;
			WindowRotation win_rotation;

#if defined LOO_PLATFORM_WINDOWS
			bool hide;
			bool external_wnd;
			std::wstring wname;

#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			uint32_t win_style;
			HWND wnd;
			WNDPROC default_wnd_proc;
#else
			std::shared_ptr<ABI::Windows::UI::Core::ICoreWindow> wnd;
			std::shared_ptr<ABI::Windows::System::Display::IDisplayRequest> disp_request_;
			std::array<uint32_t, 16> pointer_id_map_;
			bool full_screen_;
#endif

#elif defined LOO_PLATFORM_ANDROID
			::ANativeWindow* a_window_;
#elif defined LOO_PLATFORM_IOS
			LEngineView* eagl_view_;
#endif
		};

		typedef std::shared_ptr<Window> WindowPtr;
	}
}


#endif

