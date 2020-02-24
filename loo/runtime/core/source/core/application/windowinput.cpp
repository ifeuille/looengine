#include "core/application/input.h"
#include "core/application/syseventbus.h"
#include "core/application/application.h"
#include <windowsx.h>

using namespace loo;
using namespace core;

#define DECLARE_KEY_MAP(scanCode,keyCode)\
	case scanCode:return keyCode;


KeyCode Input::TranslateKey (int scanCode)
{
	switch (scanCode)
	{
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_TAB, KeyCode::Tab);
		DECLARE_KEY_MAP (VK_CLEAR, KeyCode::Clear);
		DECLARE_KEY_MAP (VK_RETURN, KeyCode::Return);
		DECLARE_KEY_MAP (VK_PAUSE, KeyCode::Pause);
		DECLARE_KEY_MAP (VK_ESCAPE, KeyCode::Escape);
		DECLARE_KEY_MAP (VK_SPACE, KeyCode::Space);
		DECLARE_KEY_MAP (VK_EXCLAIM, KeyCode::Exclaim);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
		DECLARE_KEY_MAP (VK_BACK, KeyCode::Backspace);
	case 1:return KeyCode::None;
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
