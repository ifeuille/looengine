#include "core/application/input.h"
#include "core/application/syseventbus.h"
#include "core/application/application.h"
#include <windowsx.h>

using namespace loo;
using namespace core;

#define DECLARE_KEY_MAP(scanCode,keyCode)\
	case scanCode:return keyCode;
#define DECLARE_JOYSTICK_BTNS(index)\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button0);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button1);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button2);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button3);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button4);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button5);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button6);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button7);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button8);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button9);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button10);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button11);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button12);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button13);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button14);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button15);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button16);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button17);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button18);\
DECLARE_KEY_MAP(VK_BACK, KeyCode::Joystick##index##Button19);\

KeyCode Input::TranslateKey (int scanCode)
{
	//kVirtKeyToKeyCode
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
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Greater);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Question);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::At);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftBracket);
		DECLARE_KEY_MAP(VK_OEM_5, KeyCode::Backslash);
		DECLARE_KEY_MAP(VK_OEM_102, KeyCode::Backslash);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::RightBracket);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Caret);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Underscore);
		DECLARE_KEY_MAP(VK_OEM_3, KeyCode::BackQuote);
		DECLARE_KEY_MAP(VK_OEM_8, KeyCode::BackQuote);

		DECLARE_KEY_MAP('A', KeyCode::A);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::B);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::C);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::D);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::E);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::F);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::G);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::H);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::I);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::J);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::K);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::L);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::M);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::N);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::O);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::P);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Q);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::R);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::S);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::T);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::U);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::V);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::W);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::X);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Y);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Z);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftCurlyBracket);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Pipe);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::RightCurlyBracket);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Tilde);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Delete);
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
		DECLARE_KEY_MAP(VK_BACK, KeyCode::KeypadMultiply);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::KeypadMinus);
		DECLARE_KEY_MAP(VK_ADD, KeyCode::KeypadPlus);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::KeypadEnter);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::KeypadEquals);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::UpArrow);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::DownArrow);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::RightArrow);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftArrow);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Insert);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Home);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::End);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::PageUp);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::PageDown);
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
		DECLARE_KEY_MAP(VK_BACK, KeyCode::ScrollLock);
		DECLARE_KEY_MAP(VK_RSHIFT, KeyCode::RightShift);
		DECLARE_KEY_MAP(VK_LSHIFT, KeyCode::LeftShift);
		DECLARE_KEY_MAP(VK_SHIFT, KeyCode::LeftShift);

		DECLARE_KEY_MAP(VK_RCONTROL, KeyCode::RightControl);
		DECLARE_KEY_MAP(VK_LCONTROL, KeyCode::LeftControl);
		DECLARE_KEY_MAP(VK_CONTROL, KeyCode::LeftControl);

		DECLARE_KEY_MAP(VK_BACK, KeyCode::RightAlt);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftAlt);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::RightCommand);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::RightApple);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftCommand);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftApple);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::LeftWindows);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::RightWindows);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::AltGr);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Help);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Print);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::SysReq);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Break);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Menu);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse0);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse1);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse2);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse3);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse4);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse5);
		DECLARE_KEY_MAP(VK_BACK, KeyCode::Mouse6);
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



struct MsgProcVisitFunc_Local
{
public:
	HWND hWnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
	SAppEvent& event;
	SystemEventBus& bus;
	Input& input;
	MsgProcVisitFunc_Local (Input& input_,HWND hWnd_, UINT uMsg_, WPARAM wParam_, LPARAM lParam_, SAppEvent& event_, SystemEventBus& bus_)
		:input(input_),hWnd (hWnd_), uMsg (uMsg_), wParam (wParam_), lParam (lParam_), event (event_), bus (bus_) {}

	bool app_event (SAppEventType type)
	{
		input.InitEvent (event, type);
		return bus.Dispatch (event);
	}
	
	bool mouse_event (SAppEventType type,KeyCode keyCode)
	{
		input.InitEvent (event, type);
		event.keyCode = keyCode;
		event.modifiers = _sapp_win32_mods ();
		event.mouseX = GET_X_LPARAM (lParam);
		event.mouseY = GET_Y_LPARAM (lParam);
		
		return bus.Dispatch (event);
	}
	bool mouse_scroll_event (float x,float y)
	{
		input.InitEvent (event, SAppEventType::SAPP_EVENTTYPE_MOUSE_SCROLL);
		event.modifiers = _sapp_win32_mods ();
		event.mouseX = -x/30.0f;
		event.mouseY = x/30.0f;

		return bus.Dispatch (event);
	}
	bool char_event (uint32_t c, bool repeat)
	{
		input.InitEvent (event,SAppEventType::SAPP_EVENTTYPE_CHAR);
		event.modifiers = _sapp_win32_mods ();
		event.charCode = c;
		event.keyRepeat = repeat;
		return bus.Dispatch (event);
	}
	bool key_event (SAppEventType type,KeyCode c,bool repeat)
	{
		input.InitEvent (event, type);
		event.modifiers = _sapp_win32_mods ();
		event.keyCode = c;
		event.keyRepeat = repeat;
		return bus.Dispatch (event);
	}
};


bool loo::core::Input::MsgProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Application* app = windowptr->GetApp ();
	SystemEventBus& bus = app->GetEventBus ();
	SAppEvent& event = app->GetEvent ();
	MsgProcVisitFunc_Local visit (*this,hWnd, uMsg, wParam, lParam, event, bus);
	switch (uMsg)
	{
	case WM_SIZE:
	{
		const bool iconified = wParam == SIZE_MINIMIZED;
		if (iconified != windowptr->Iconified()) {
			windowptr->Iconified () = iconified;
			if (iconified) {
				visit.app_event (SAppEventType::SAPP_EVENTTYPE_ICONIFIED);
			}
			else {
				visit.app_event (SAppEventType::SAPP_EVENTTYPE_RESTORED);
			}
		}
	}
	break;
	case WM_SETCURSOR:
		if (true) {//_sapp.desc.user_cursor
			if (LOWORD (lParam) == HTCLIENT) {
				visit.app_event (SAppEventType::SAPP_EVENTTYPE_UPDATE_CURSOR);
				return 1;
			}
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_DOWN, KeyCode::Mouse0);
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_DOWN, KeyCode::Mouse1);
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_DOWN, KeyCode::Mouse2);
		break;
	case WM_LBUTTONUP:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_UP, KeyCode::Mouse0);
		break;
	case WM_RBUTTONUP:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_UP, KeyCode::Mouse1);
		break;
	case WM_MBUTTONUP:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_UP, KeyCode::Mouse2);
		break;
	case WM_MOUSEMOVE:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_MOVE, KeyCode::None);
		break;
	case WM_MOUSELEAVE:
		return visit.mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_LEAVE, KeyCode::None);
		break;
	case WM_MOUSEWHEEL:
		return visit.mouse_scroll_event (0.0f, (float)((SHORT)HIWORD (wParam)));
		break;
	case WM_MOUSEHWHEEL:
		return visit.mouse_scroll_event ((float)((SHORT)HIWORD (wParam)), 0.0f);
		break;
	case WM_CHAR:
		return visit.char_event (wParam, !!(lParam & 0x40000000));
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		return visit.key_event (SAppEventType::SAPP_EVENTTYPE_KEY_DOWN, TranslateKey((int)(HIWORD (lParam) & 0x1FF)), !!(lParam & 0x40000000));
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		return visit.key_event (SAppEventType::SAPP_EVENTTYPE_KEY_UP, TranslateKey ((int)(HIWORD (lParam) & 0x1FF)), false);
		break;
	default:
#if (_WIN32_WINNT > _WIN32_WINNT_WIN7)
	case WM_TOUCH:
	{
		std::cout << "WM_TOUCH" << std::endl;
		//https://docs.microsoft.com/zh-cn/windows/win32/wintouch/detecting-and-tracking-multiple-touch-points?redirectedfrom=MSDN
	}break;
#endif
	}
	
	return bus.Dispatch (event);
}
