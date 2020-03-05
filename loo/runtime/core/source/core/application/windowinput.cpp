#include "global/global.h"
#ifdef LOO_PLATFORM_WINDOWS
#include <windowsx.h>
#include "core/application/input.h"
#include "core/application/application.h"


using namespace loo;
using namespace core;

namespace loo
{
	namespace core
	{
		struct MsgProcVisitFunc_Local
		{
		public:
			HWND hWnd;
			UINT uMsg;
			WPARAM wParam;
			LPARAM lParam;
			SAppEvent* event;
			Input* input;
			loo::math::RectF screenGeometry;//todo
			std::vector< TOUCHINPUT> winTouchInputs;
			std::unordered_map<DWORD, int> touchInputIDToTouchPointID;
			std::unordered_map<int, loo::math::float2> lastTouchPositions;
			void Reset (Input* input_, HWND hWnd_,
				UINT uMsg_, WPARAM wParam_, LPARAM lParam_,
				SAppEvent* event_, 
				loo::math::RectF screenGeometry_);

			bool app_event (SAppEventType type);

			bool mouse_event (SAppEventType type, KeyCode keyCode);
			bool mouse_scroll_event (float x, float y);
			bool char_event (uint32_t c, bool repeat);
			bool key_event (SAppEventType type, KeyCode c, bool repeat);
			bool touch_event ();
		};

	}
}


KeyCode Input::TranslateKey (int scanCode)
{

#define DECLARE_KEY_MAP(scanCode,keyCode)\
	case scanCode:return keyCode;

	//kVirtKeyToKeyCode
	//https://wenku.baidu.com/view/18cc927bf56527d3240c844769eae009581ba27e.html
	switch (scanCode)
	{
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_TAB, KeyCode::Tab);
		DECLARE_KEY_MAP (VK_CLEAR, KeyCode::Clear);
		DECLARE_KEY_MAP (VK_RETURN, KeyCode::Return);
		DECLARE_KEY_MAP (VK_PAUSE, KeyCode::Pause);
		DECLARE_KEY_MAP (VK_ESCAPE, KeyCode::Escape);
		DECLARE_KEY_MAP (VK_SPACE, KeyCode::Space);
		//DECLARE_KEY_MAP (VK_EXCLAIM, KeyCode::Exclaim);
		//DECLARE_KEY_MAP (VK_QUOTE, KeyCode::DoubleQuote);
		//DECLARE_KEY_MAP (VK_HASH, KeyCode::Hash);
		//DECLARE_KEY_MAP (VK_DOLLAR, KeyCode::Dollar);
		//DECLARE_KEY_MAP (VK_BACK, KeyCode::Percent);
		//DECLARE_KEY_MAP (VK_BACK, KeyCode::Ampersand);
		DECLARE_KEY_MAP (VK_OEM_7, KeyCode::Quote);
		//DECLARE_KEY_MAP (VK_BACK, KeyCode::LeftParen);
		//DECLARE_KEY_MAP (VK_BACK, KeyCode::RightParen);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Asterisk);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Plus);
		DECLARE_KEY_MAP(VK_OEM_COMMA, KeyCode::Comma);
		DECLARE_KEY_MAP(VK_OEM_MINUS, KeyCode::Minus);
		DECLARE_KEY_MAP(VK_OEM_PERIOD, KeyCode::Period);
		DECLARE_KEY_MAP(VK_OEM_2, KeyCode::Slash);
		DECLARE_KEY_MAP('0', KeyCode::Alpha0);
		DECLARE_KEY_MAP('1', KeyCode::Alpha1);
		DECLARE_KEY_MAP('2', KeyCode::Alpha2);
		DECLARE_KEY_MAP('3', KeyCode::Alpha3);
		DECLARE_KEY_MAP('4', KeyCode::Alpha4);
		DECLARE_KEY_MAP('5', KeyCode::Alpha5);
		DECLARE_KEY_MAP('6', KeyCode::Alpha6);
		DECLARE_KEY_MAP('7', KeyCode::Alpha7);
		DECLARE_KEY_MAP('8', KeyCode::Alpha8);
		DECLARE_KEY_MAP('9', KeyCode::Alpha9);
		DECLARE_KEY_MAP(VK_OEM_PLUS, KeyCode::Equals);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Greater);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Question);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::At);
		DECLARE_KEY_MAP(VK_OEM_4, KeyCode::LeftBracket);
		DECLARE_KEY_MAP(VK_OEM_5, KeyCode::Backslash);
		DECLARE_KEY_MAP(VK_OEM_102, KeyCode::Backslash);
		DECLARE_KEY_MAP(VK_OEM_6, KeyCode::RightBracket);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Caret);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Underscore);
		DECLARE_KEY_MAP(VK_OEM_3, KeyCode::BackQuote);
		DECLARE_KEY_MAP(VK_OEM_8, KeyCode::BackQuote);

		DECLARE_KEY_MAP('A', KeyCode::A);
		DECLARE_KEY_MAP('B', KeyCode::B);
		DECLARE_KEY_MAP('C', KeyCode::C);
		DECLARE_KEY_MAP('D', KeyCode::D);
		DECLARE_KEY_MAP('E', KeyCode::E);
		DECLARE_KEY_MAP('F', KeyCode::F);
		DECLARE_KEY_MAP('G', KeyCode::G);
		DECLARE_KEY_MAP('H', KeyCode::H);
		DECLARE_KEY_MAP('I', KeyCode::I);
		DECLARE_KEY_MAP('J', KeyCode::J);
		DECLARE_KEY_MAP('K', KeyCode::K);
		DECLARE_KEY_MAP('L', KeyCode::L);
		DECLARE_KEY_MAP('M', KeyCode::M);
		DECLARE_KEY_MAP('N', KeyCode::N);
		DECLARE_KEY_MAP('O', KeyCode::O);
		DECLARE_KEY_MAP('P', KeyCode::P);
		DECLARE_KEY_MAP('Q', KeyCode::Q);
		DECLARE_KEY_MAP('R', KeyCode::R);
		DECLARE_KEY_MAP('S', KeyCode::S);
		DECLARE_KEY_MAP('T', KeyCode::T);
		DECLARE_KEY_MAP('U', KeyCode::U);
		DECLARE_KEY_MAP('V', KeyCode::V);
		DECLARE_KEY_MAP('W', KeyCode::W);
		DECLARE_KEY_MAP('X', KeyCode::X);
		DECLARE_KEY_MAP('Y', KeyCode::Y);
		DECLARE_KEY_MAP('Z', KeyCode::Z);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftCurlyBracket);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Pipe);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::RightCurlyBracket);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Tilde);
		DECLARE_KEY_MAP(VK_DELETE, KeyCode::Delete);
		DECLARE_KEY_MAP(VK_NUMPAD0, KeyCode::Keypad0);
		DECLARE_KEY_MAP(VK_NUMPAD1, KeyCode::Keypad1);
		DECLARE_KEY_MAP(VK_NUMPAD2, KeyCode::Keypad2);
		DECLARE_KEY_MAP(VK_NUMPAD3, KeyCode::Keypad3);
		DECLARE_KEY_MAP(VK_NUMPAD4, KeyCode::Keypad4);
		DECLARE_KEY_MAP(VK_NUMPAD5, KeyCode::Keypad5);
		DECLARE_KEY_MAP(VK_NUMPAD6, KeyCode::Keypad6);
		DECLARE_KEY_MAP(VK_NUMPAD7, KeyCode::Keypad7);
		DECLARE_KEY_MAP(VK_NUMPAD8, KeyCode::Keypad8);
		DECLARE_KEY_MAP(VK_NUMPAD9, KeyCode::Keypad9);
		DECLARE_KEY_MAP(VK_DECIMAL, KeyCode::KeypadPeriod);
		DECLARE_KEY_MAP(VK_DIVIDE, KeyCode::KeypadDivide);
		DECLARE_KEY_MAP(VK_MULTIPLY, KeyCode::KeypadMultiply);
		DECLARE_KEY_MAP(VK_SUBTRACT, KeyCode::KeypadMinus);
		DECLARE_KEY_MAP(VK_ADD, KeyCode::KeypadPlus);
		DECLARE_KEY_MAP(WM_TOUCH, KeyCode::KeypadEnter);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::KeypadEquals);
		DECLARE_KEY_MAP(VK_UP, KeyCode::UpArrow);
		DECLARE_KEY_MAP(VK_DOWN, KeyCode::DownArrow);
		DECLARE_KEY_MAP(VK_RIGHT, KeyCode::RightArrow);
		DECLARE_KEY_MAP(VK_LEFT, KeyCode::LeftArrow);
		DECLARE_KEY_MAP(VK_INSERT, KeyCode::Insert);
		DECLARE_KEY_MAP(VK_HOME, KeyCode::Home);
		DECLARE_KEY_MAP(VK_END, KeyCode::End);
		DECLARE_KEY_MAP(VK_PRIOR, KeyCode::PageUp);
		DECLARE_KEY_MAP(VK_NEXT, KeyCode::PageDown);
		DECLARE_KEY_MAP(VK_F1, KeyCode::F1);
		DECLARE_KEY_MAP(VK_F2, KeyCode::F2);
		DECLARE_KEY_MAP(VK_F3, KeyCode::F3);
		DECLARE_KEY_MAP(VK_F4, KeyCode::F4);
		DECLARE_KEY_MAP(VK_F5, KeyCode::F5);
		DECLARE_KEY_MAP(VK_F6, KeyCode::F6);
		DECLARE_KEY_MAP(VK_F7, KeyCode::F7);
		DECLARE_KEY_MAP(VK_F8, KeyCode::F8);
		DECLARE_KEY_MAP(VK_F9, KeyCode::F9);
		DECLARE_KEY_MAP(VK_F10, KeyCode::F10);
		DECLARE_KEY_MAP(VK_F11, KeyCode::F11);
		DECLARE_KEY_MAP(VK_F12, KeyCode::F12);
		DECLARE_KEY_MAP(VK_F13, KeyCode::F13);
		DECLARE_KEY_MAP(VK_F14, KeyCode::F14);
		DECLARE_KEY_MAP(VK_F15, KeyCode::F15);
		DECLARE_KEY_MAP(VK_NUMLOCK, KeyCode::Numlock);
		DECLARE_KEY_MAP(VK_CAPITAL, KeyCode::CapsLock);
		DECLARE_KEY_MAP(VK_SCROLL, KeyCode::ScrollLock);
		DECLARE_KEY_MAP(VK_RSHIFT, KeyCode::RightShift);
		DECLARE_KEY_MAP(VK_LSHIFT, KeyCode::LeftShift);
		DECLARE_KEY_MAP(VK_SHIFT, KeyCode::LeftShift);

		DECLARE_KEY_MAP(VK_RCONTROL, KeyCode::RightControl);
		DECLARE_KEY_MAP(VK_LCONTROL, KeyCode::LeftControl);
		DECLARE_KEY_MAP(VK_CONTROL, KeyCode::LeftControl);

		DECLARE_KEY_MAP(VK_RMENU, KeyCode::RightAlt);
		DECLARE_KEY_MAP(VK_LMENU, KeyCode::LeftAlt);
		DECLARE_KEY_MAP(VK_RWIN, KeyCode::RightCommand);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::RightApple);
		DECLARE_KEY_MAP(VK_LWIN, KeyCode::LeftCommand);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftApple);
		//DECLARE_KEY_MAP(VK_LWIN, KeyCode::LeftWindows);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::RightWindows);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::AltGr);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Help);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Print);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::SysReq);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Break);
		DECLARE_KEY_MAP(VK_APPS, KeyCode::Menu);
		DECLARE_KEY_MAP(VK_LBUTTON, KeyCode::Mouse0);
		DECLARE_KEY_MAP(VK_RBUTTON, KeyCode::Mouse1);
		DECLARE_KEY_MAP(VK_MBUTTON, KeyCode::Mouse2);
#if(_WIN32_WINNT >= 0x0500)
		DECLARE_KEY_MAP (VK_XBUTTON1, KeyCode::Mouse3);
		DECLARE_KEY_MAP (VK_XBUTTON2, KeyCode::Mouse4);
#endif /* _WIN32_WINNT >= 0x0500 */
		DECLARE_KEY_MAP(VK_CANCEL, KeyCode::Mouse5);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse6);
		

		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton0);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton1);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton3);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton4);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton5);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton6);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton7);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton8);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton9);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton10);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton11);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton12);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton13);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton14);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton15);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton16);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton17);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton18);
		//DECLARE_KEY_MAP(VK_BACK, KeyCode::JoystickButton19);
		//DECLARE_JOYSTICK_BTNS(1);
		//DECLARE_JOYSTICK_BTNS(2);
		//DECLARE_JOYSTICK_BTNS(3);
		//DECLARE_JOYSTICK_BTNS(4);
		//DECLARE_JOYSTICK_BTNS(5);
		//DECLARE_JOYSTICK_BTNS(6);
		//DECLARE_JOYSTICK_BTNS(7);
		//DECLARE_JOYSTICK_BTNS(8);
		default:return KeyCode::None;
	}
#undef DECLARE_KEY_MAP
}

uint32 _sapp_win32_mods (void) {
	uint32 mods = 0;
	mods |= (GetKeyState (VK_LSHIFT) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_LSHIFT) : 0);
	mods |= (GetKeyState (VK_RSHIFT) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_RSHIFT) : 0);
	mods |= (GetKeyState (VK_LCONTROL) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_LCTRL) : 0);
	mods |= (GetKeyState (VK_RCONTROL) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_RCTRL) : 0);
	mods |= (GetKeyState (VK_LMENU) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_LALT) : 0);
	mods |= (GetKeyState (VK_RMENU) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_RALT) : 0);
	mods |= (GetKeyState (VK_LWIN) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_LMETA) : 0);
	mods |= (GetKeyState (VK_RWIN) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_RMETA) : 0);
	mods |= (GetKeyState (VK_CAPITAL) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_CAPSLOCK) : 0);
	mods |= (GetKeyState (VK_NUMLOCK) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_NUMLOCK) : 0);
	mods |= (GetKeyState (VK_SCROLL) & 0x80 ? (uint32)(SAppModifierType::SAPP_MODIFIER_SCROLLLOCK) : 0);

	return mods;
}

uint queryMouseButtons ()
{
	uint result = 0;
	const bool mouseSwapped = GetSystemMetrics (SM_SWAPBUTTON);
	if (GetAsyncKeyState (VK_LBUTTON) < 0)
		result |=(uint) (mouseSwapped ? KeyCode::Mouse1 : KeyCode::Mouse0);
	if (GetAsyncKeyState (VK_RBUTTON) < 0)
		result |= (uint)(mouseSwapped ? KeyCode::Mouse0 : KeyCode::Mouse1);
	if (GetAsyncKeyState (VK_MBUTTON) < 0)
		result |= (uint)KeyCode::Mouse2;
	if (GetAsyncKeyState (VK_XBUTTON1) < 0)
		result |= (uint)KeyCode::Mouse3;
	if (GetAsyncKeyState (VK_XBUTTON2) < 0)
		result |= (uint)KeyCode::Mouse4;
	return result;
}

namespace loo
{
	namespace core
	{
		void MsgProcVisitFunc_Local::Reset (Input* input_, HWND hWnd_,
			UINT uMsg_, WPARAM wParam_, LPARAM lParam_,
			SAppEvent* event_, 
			loo::math::RectF screenGeometry_)
		{
			input = input_;
			hWnd = hWnd_;
			uMsg = uMsg_;
			wParam = wParam_;
			lParam = lParam_;
			event = event_;
			screenGeometry = screenGeometry_;
		}

		bool MsgProcVisitFunc_Local::app_event (SAppEventType type)
		{
			input->InitEvent (*event, type);
			return EventManager::Get ().sendEvent (event);
		}

		bool MsgProcVisitFunc_Local::mouse_event (SAppEventType type, KeyCode keyCode)
		{
			input->InitEvent (*event, type);
			event->keyCode = keyCode;
			event->modifiers = _sapp_win32_mods ();
			event->mouseX = GET_X_LPARAM (lParam);
			event->mouseY = GET_Y_LPARAM (lParam);

			return EventManager::Get ().sendEvent (event);
		}
		bool MsgProcVisitFunc_Local::mouse_scroll_event (float x, float y)
		{
			input->InitEvent (*event, SAppEventType::SAPP_EVENTTYPE_MOUSE_SCROLL);
			event->modifiers = _sapp_win32_mods ();

			event->scrollX = -x / 30.0f;
			event->scrollY = y / 30.0f;

			EventManager::Get ().sendEvent (event);
			return true;
		}
		bool MsgProcVisitFunc_Local::char_event (uint32_t c, bool repeat)
		{
			input->InitEvent (*event, SAppEventType::SAPP_EVENTTYPE_CHAR);
			event->modifiers = _sapp_win32_mods ();
			event->charCode = c;
			event->keyRepeat = repeat;
			return EventManager::Get ().sendEvent (event);
		}
		bool MsgProcVisitFunc_Local::key_event (SAppEventType type, KeyCode c, bool repeat)
		{
			input->InitEvent (*event, type);
			event->modifiers = _sapp_win32_mods ();
			event->keyCode = c;
			event->keyRepeat = repeat;
			return EventManager::Get ().sendEvent (event);
		}
		bool MsgProcVisitFunc_Local::touch_event ()
		{
			//QWindowsMouseHandler::translateTouchEvent
			input->InitEvent (*event, SAppEventType::SAPP_EVENTTYPE_TOUCHES);
			const int winTouchPointCount = int (wParam);
			winTouchInputs.clear ();
			//int realTouchCount = winTouchPointCount > SAPP_MAX_TOUCHPOINTS ? SAPP_MAX_TOUCHPOINTS : winTouchPointCount;
			int realTouchCount = winTouchPointCount;
			//if (realTouchCount <= 0)	return false;
			winTouchInputs.resize (realTouchCount);
			memset (winTouchInputs.data (), 0, sizeof (TOUCHINPUT) * size_t (winTouchPointCount));
			GetTouchInputInfo ((HTOUCHINPUT)(lParam), UINT (wParam), winTouchInputs.data (), sizeof (TOUCHINPUT));
			uint allStates = 0;
			event->touches.clear ();
			event->touches.reserve (realTouchCount);
			for (int i = 0; i < realTouchCount; ++i)
			{
				const TOUCHINPUT &winTouchInput = winTouchInputs[i];
				auto it = touchInputIDToTouchPointID.find (winTouchInput.dwID);
				int id = -1;
				if (it == touchInputIDToTouchPointID.end ())
				{
					id = (int)touchInputIDToTouchPointID.size ();
					touchInputIDToTouchPointID.insert (std::make_pair (winTouchInput.dwID, id));
				}
				TouchPoint touchPoint;
				touchPoint.pressure = 1.0;
				touchPoint.id = id;
				auto it_lastPoint = lastTouchPositions.find (id);
				if (it_lastPoint != lastTouchPositions.end ())
				{
					touchPoint.normalPosition = it_lastPoint->second;
				}
				const loo::math::float2 screenPos = loo::math::float2 (winTouchInput.x / 100.0f, winTouchInput.y / 100.0f);
				if (winTouchInput.dwMask & TOUCHINPUTMASKF_CONTACTAREA)
				{
					loo::math::float2 normalPosition = loo::math::float2 (
						screenPos.x / screenGeometry.Width (),
						screenPos.y / screenGeometry.Height ());
					const bool stationaryTouchPoint = loo::math::All (normalPosition == touchPoint.normalPosition);
					touchPoint.normalPosition = normalPosition;

					if (winTouchInput.dwFlags & TOUCHEVENTF_DOWN) {
						touchPoint.state = TouchPointState::TouchPointPressed;
						lastTouchPositions.insert (std::make_pair (id, touchPoint.normalPosition));
					}
					else if (winTouchInput.dwFlags & TOUCHEVENTF_UP) {
						touchPoint.state = TouchPointState::TouchPointReleased;
						lastTouchPositions.erase (id);
					}
					else {
						touchPoint.state = (stationaryTouchPoint
							? TouchPointState::TouchPointStationary
							: TouchPointState::TouchPointMoved);
						lastTouchPositions.insert (std::make_pair (id, touchPoint.normalPosition));
					}
				}
				allStates |= (uint)touchPoint.state;
				event->touches.push_back (touchPoint);
			}
			CloseTouchInputHandle ((HTOUCHINPUT)(lParam));
			if (allStates == (uint)TouchPointState::TouchPointReleased)
				touchInputIDToTouchPointID.clear ();
			return EventManager::Get ().sendEvent (event);
		}
	}
}

void loo::core::Input::Init (loo::core::Window& win)
{
	windowptr = &win;
	//windowptr->OnChar ().connect (&Input::cb_CharEvent,this);
	visitor = new MsgProcVisitFunc_Local ();
}

void loo::core::Input::CleanUp ()
{
	delete visitor;
}

bool loo::core::Input::MsgProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!windowptr)return false;
	Application* app = windowptr->GetApp ();
	SAppEvent& event = app->GetEvent ();
	auto cfg = app->Config ();
	auto rs = cfg.graphic_settings;
	visitor->Reset (this, hWnd, uMsg, wParam, lParam, &event,
		loo::math::RectF((float)windowptr->Left(), (float)windowptr->Top(), (float)windowptr->Width(), (float)windowptr->Height()));
	bool handled = false;
	switch (uMsg)
	{
	case WM_SIZE:
	{
		const bool iconified = wParam == SIZE_MINIMIZED;
		if (iconified != windowptr->Iconified()) {
			windowptr->Iconified () = iconified;
			if (iconified) {
				handled =  visitor->app_event (SAppEventType::SAPP_EVENTTYPE_ICONIFIED);
			}
			else {
				handled = visitor->app_event (SAppEventType::SAPP_EVENTTYPE_RESTORED);
			}
		}
	}
	break;
	case WM_SETCURSOR:
		if (true) {//_sapp.desc.user_cursor
			if (LOWORD (lParam) == HTCLIENT) {
				handled = visitor->app_event (SAppEventType::SAPP_EVENTTYPE_UPDATE_CURSOR);
			}
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		handled = visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_DOWN, KeyCode::Mouse0);
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		handled = visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_DOWN, KeyCode::Mouse1);
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		return visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_DOWN, KeyCode::Mouse2);
		break;
	case WM_LBUTTONUP:
		handled = visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_UP, KeyCode::Mouse0);
		break;
	case WM_RBUTTONUP:
		handled = visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_UP, KeyCode::Mouse1);
		break;
	case WM_MBUTTONUP:
		handled = visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_UP, KeyCode::Mouse2);
		break;
	case WM_MOUSEMOVE:
		handled = visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_MOVE, KeyCode::None);
		break;
	case WM_MOUSELEAVE:
		handled = visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_LEAVE, KeyCode::None);
		break;
	case WM_MOUSEWHEEL:
		handled = visitor->mouse_scroll_event (0.0f, (float)((SHORT)HIWORD (wParam)));
		break;
	case WM_MOUSEHWHEEL:
		handled = visitor->mouse_scroll_event ((float)((SHORT)HIWORD (wParam)), 0.0f);
		break;
	case WM_CHAR:
		handled = visitor->char_event (uint32_t(wParam), !!(lParam & 0x40000000));
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		handled = visitor->key_event (SAppEventType::SAPP_EVENTTYPE_KEY_DOWN, TranslateKey((int)(HIWORD (lParam) & 0x1FF)), !!(lParam & 0x40000000));
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		handled = visitor->key_event (SAppEventType::SAPP_EVENTTYPE_KEY_UP, TranslateKey ((int)(HIWORD (lParam) & 0x1FF)), false);
		break;
#if (_WIN32_WINNT > _WIN32_WINNT_WIN7)
	case WM_TOUCH:
	{
		std::cout << "WM_TOUCH" << std::endl;
		handled = visitor->touch_event ();
		//https://docs.microsoft.com/zh-cn/windows/win32/wintouch/detecting-and-tracking-multiple-touch-points?redirectedfrom=MSDN
	}break;
#endif
	default:break;
	}
	
	return handled;
}
#endif