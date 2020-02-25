#pragma once
#include "core/dllexporter.h"
#include "global/types.h"
#include "core/application/window.h"
#include "core/application/keycode.h"
#include "core/application/syseventbus.h"

namespace loo
{
	namespace core
	{
		class Input;
#ifdef LOO_PLATFORM_WINDOWS
		struct MsgProcVisitFunc_Local
		{
		public:
			HWND hWnd;
			UINT uMsg;
			WPARAM wParam;
			LPARAM lParam;
			SAppEvent* event;
			SystemEventBus* bus;
			Input* input;
			loo::math::RectF screenGeometry;//todo
			std::vector< TOUCHINPUT> winTouchInputs;
			std::unordered_map<DWORD, int> touchInputIDToTouchPointID;
			std::unordered_map<int, loo::math::float2> lastTouchPositions;
			void Reset (Input* input_, HWND hWnd_,
				UINT uMsg_, WPARAM wParam_, LPARAM lParam_,
				SAppEvent* event_, SystemEventBus* bus_,
				loo::math::RectF screenGeometry_);

			bool app_event (SAppEventType type);

			bool mouse_event (SAppEventType type, KeyCode keyCode);
			bool mouse_scroll_event (float x, float y);
			bool char_event (uint32_t c, bool repeat);
			bool key_event (SAppEventType type, KeyCode c, bool repeat);
			bool touch_event ();
		};

#endif
		class CORE_EXPORT Input
		{
		public:
			Input () {}
			virtual ~Input ();
			void Init (loo::core::Window& win);
			void CleanUp();
			void Update();

			//public callback
			void cb_CharEvent (Window const &, wchar_t);

		public:// for event
			void	InitEvent (SAppEvent& event, SAppEventType type);
			KeyCode TranslateKey (int scanCode);
			
			//for windows
#ifdef LOO_PLATFORM_WINDOWS
			bool MsgProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#else

#endif

#if 1
		public:
			/*
android
http://blog.sina.com.cn/s/blog_6dd0be790101mfka.html
https://developer.android.google.cn/ndk/reference/group/input?hl=zh-cn#group___input_1gga16685eea158879e41b101ca3634de462a55ea411f927aed8964fa72fec0da444f
windows:
https://blog.csdn.net/popten/article/details/50634694

*/
// some events
			typedef sigslot::signal<Window const &, bool > ActiveEvent;
			typedef sigslot::signal<Window const &> PaintEvent;
			typedef sigslot::signal<Window const &> EnterSizeMoveEvent;
			typedef sigslot::signal<Window const &> ExitSizeMoveEvent;
			typedef sigslot::signal< Window const &, bool> SizeEvent;
			typedef sigslot::signal<Window const &> SetCursorEvent;
			typedef sigslot::signal< Window const &, wchar_t> CharEvent;

			typedef sigslot::signal< Window const &, uint32> KeyDownEvent;
			typedef sigslot::signal< Window const &, uint32> KeyUpEvent;

			typedef sigslot::signal< Window const &, loo::math::float2 const &, uint32_t> MouseDownEvent;
			typedef sigslot::signal< Window const &, loo::math::float2 const &, uint32_t> MouseUpEvent;
			typedef sigslot::signal<Window const &, loo::math::float2 const &> MouseMoveEvent;
			typedef sigslot::signal<Window const &, loo::math::float2 const &, int32_t> MouseWheelEvent;
			typedef sigslot::signal<Window const &, int32, int32_t> JoystickAxisEvent;
			typedef sigslot::signal<Window const &, uint32> JoystickButtonsEvent;
#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			typedef sigslot::signal< Window const &, HRAWINPUT> RawInputEvent;
#endif
			// single touch
			typedef sigslot::signal<Window const &, loo::math::int2 const &, uint32> PointerDownEvent;
			typedef sigslot::signal<Window const &, loo::math::int2 const &, uint32> PointerUpEvent;
			typedef sigslot::signal<Window const &, loo::math::int2 const &, uint32, bool> PointerUpdateEvent;
			typedef sigslot::signal<Window const &, loo::math::int2 const &, uint32, int32> PointerWheelEvent;

			typedef sigslot::signal<Window const &> CloseEvent;

		public:
			ActiveEvent active_event;
			PaintEvent paint_event;
			EnterSizeMoveEvent enter_size_move_event;
			ExitSizeMoveEvent exit_size_move_event;
			SizeEvent size_event;
			SetCursorEvent set_cursor_event;
			CharEvent char_event;

			KeyDownEvent key_down_event_;
			KeyUpEvent key_up_event_;

#if defined LOO_PLATFORM_WINDOWS_DESKTOP
			RawInputEvent raw_input_event;
#endif
			MouseDownEvent mouse_down_event_;
			MouseUpEvent mouse_up_event_;
			MouseMoveEvent mouse_move_event_;
			MouseWheelEvent mouse_wheel_event_;
			JoystickAxisEvent joystick_axis_event_;
			JoystickButtonsEvent joystick_buttons_event_;

			PointerDownEvent pointer_down_event;
			PointerUpEvent pointer_up_event;
			PointerUpdateEvent pointer_update_event;
			PointerWheelEvent pointer_wheel_event;
			CloseEvent close_event;
#endif
		private:
			loo::core::Window* windowptr;
			MsgProcVisitFunc_Local* visitor;

		};
	}
}