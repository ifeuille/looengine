#include "global/global.h"
#ifdef LOO_PLATFORM_WINDOWS_DESKTOP
#include "global/utlis.h"
#include "core/application/window.h"
#include "global/math/math.h"

#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#include <VersionHelpers.h>
#include <ShellScalingAPI.h>
#endif
#include <windowsx.h>

#ifndef GET_KEYSTATE_WPARAM
#define GET_KEYSTATE_WPARAM(wParam) (LOWORD(wParam))
#endif
#include "global/extstd/signal.h"


namespace loo
{
	namespace core
	{
		LRESULT Window::WndProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
		{
			Window* win = reinterpret_cast<Window*>(::GetWindowLongPtrW ( hWnd, GWLP_USERDATA ));
			if (win != nullptr)
			{
				return win->MsgProc ( hWnd, uMsg, wParam, lParam );
			}
			else
			{
				return ::DefWindowProc ( hWnd, uMsg, wParam, lParam );
			}
		}

#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
		BOOL Window::EnumMonProc ( HMONITOR mon, HDC dc_mon, RECT* rc_mon, LPARAM lparam )
		{
			LOO_UNUSED ( dc_mon );
			LOO_UNUSED ( rc_mon );

			HMODULE shcore = ::LoadLibraryEx ( TEXT ( "SHCore.dll" ), nullptr, 0 );
			if (shcore)
			{
				typedef HRESULT ( CALLBACK *GetDpiForMonitorFunc )(HMONITOR mon, MONITOR_DPI_TYPE dpi_type, UINT* dpi_x, UINT* dpi_y);
				GetDpiForMonitorFunc DynamicGetDpiForMonitor
					= reinterpret_cast<GetDpiForMonitorFunc>(::GetProcAddress ( shcore, "GetDpiForMonitor" ));
				if (DynamicGetDpiForMonitor)
				{
					UINT dpi_x, dpi_y;
					if (S_OK == DynamicGetDpiForMonitor ( mon, MDT_DEFAULT, &dpi_x, &dpi_y ))
					{
						Window* win = reinterpret_cast<Window*>(lparam);
						win->UpdateDpiScale ( std::max ( win->dpi_scale, static_cast<float>(std::max ( dpi_x, dpi_y )) / USER_DEFAULT_SCREEN_DPI ) );
					}
				}

				::FreeLibrary ( shcore );
			}

			return TRUE;
		}
#endif

		Window::Window ( std::string const & name, vkfg::RenderSettings const & settings, void* native_wnd )
			: active ( false ), ready ( false ), closed ( false ), keep_screen_on ( settings.keep_screen_on ),
			dpi_scale ( 1 ), effective_dpi_scale ( 1 ), win_rotation ( WR_Identity ), hide ( settings.hide_win )
		{
			this->DetectsDpi ( );
			this->KeepScreenOn ( );

			loo::global::Convert ( wname, name );

			if (native_wnd != nullptr)
			{
				wnd = static_cast<HWND>(native_wnd);
				default_wnd_proc = reinterpret_cast<WNDPROC>(::GetWindowLongPtrW ( wnd, GWLP_WNDPROC ));
				::SetWindowLongPtrW ( wnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc) );
				external_wnd = true;
			}
			else
			{
				HINSTANCE hInst = ::GetModuleHandle ( nullptr );

				// Register the window class
				WNDCLASSEXW wc;
				wc.cbSize = sizeof ( wc );
				wc.style = CS_HREDRAW | CS_VREDRAW;
				wc.lpfnWndProc = WndProc;
				wc.cbClsExtra = 0;
				wc.cbWndExtra = sizeof ( this );
				wc.hInstance = hInst;
				wc.hIcon = nullptr;
				wc.hCursor = ::LoadCursor ( nullptr, IDC_ARROW );
				wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject ( BLACK_BRUSH ));
				wc.lpszMenuName = nullptr;
				wc.lpszClassName = wname.c_str ( );
				wc.hIconSm = nullptr;
				::RegisterClassExW ( &wc );

				if (settings.full_screen)
				{
					win_style = WS_POPUP;
				}
				else
				{
					win_style = WS_OVERLAPPEDWINDOW;
				}

				RECT rc = { 0, 0, static_cast<LONG>(settings.width * dpi_scale + 0.5f), static_cast<LONG>(settings.height * dpi_scale + 0.5f) };
				::AdjustWindowRect ( &rc, win_style, false );

				// Create our main window
				// Pass pointer to self
				wnd = ::CreateWindowW ( wname.c_str ( ), wname.c_str ( ), win_style, settings.left, settings.top,
					rc.right - rc.left, rc.bottom - rc.top, 0, 0, hInst, nullptr );

				default_wnd_proc = ::DefWindowProc;
				external_wnd = false;
			}

			RECT rc;
			::GetClientRect ( wnd, &rc );
			left = rc.left;
			top = rc.top;
			width = rc.right - rc.left;
			height = rc.bottom - rc.top;

			::SetWindowLongPtrW ( wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this) );

			::ShowWindow ( wnd, hide ? SW_HIDE : SW_SHOWNORMAL );
			::UpdateWindow ( wnd );

			ready = true;
		}

		Window::~Window ( )
		{
			if (keep_screen_on)
			{
#if defined(LOO_PLATFORM_WINDOWS_DESKTOP)
				::SetThreadExecutionState ( ES_CONTINUOUS );
#endif
			}

			if (wnd != nullptr)
			{
				::SetWindowLongPtrW ( wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr) );
				if (!external_wnd)
				{
					::DestroyWindow ( wnd );
				}

				wnd = nullptr;
			}
		}

		LRESULT Window::MsgProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
		{
		/*	sigslot::signal<void (loo::core::Window const & )> s;
			s(*this);*/
			switch (uMsg)
			{
			case WM_ACTIVATE:
				active = (WA_INACTIVE != LOWORD ( wParam ));
				this->OnActive ( )(*this, active);
				break;

			case WM_ERASEBKGND:
				return 1;

			case WM_PAINT:
				this->OnPaint ( )(*this);
				break;

			case WM_ENTERSIZEMOVE:
				// Previent rendering while moving / sizing
				ready = false;
				this->OnEnterSizeMove ( )(*this);
				break;

			case WM_EXITSIZEMOVE:
				this->OnExitSizeMove ( )(*this);
				ready = true;
				break;

			case WM_SIZE:
			{
				RECT rc;
				::GetClientRect ( wnd, &rc );
				left = rc.left;
				top = rc.top;
				width = rc.right - rc.left;
				height = rc.bottom - rc.top;

				// Check to see if we are losing or gaining our window.  Set the
				// active flag to match
				if ((SIZE_MAXHIDE == wParam) || (SIZE_MINIMIZED == wParam))
				{
					active = false;
					this->OnSize ( )(*this, false);
				}
				else
				{
					active = true;
					this->OnSize ( )(*this, true);
				}
			}
			break;

			case WM_GETMINMAXINFO:
				// Prevent the window from going smaller than some minimu size
				reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = 100;
				reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = 100;
				break;

			case WM_SETCURSOR:
				this->OnSetCursor ( )(*this);
				break;

			case WM_CHAR:
				this->OnChar ( )(*this, static_cast<wchar_t>(wParam));
				break;

			case WM_INPUT:
				this->OnRawInput ( )(*this, reinterpret_cast<HRAWINPUT>(lParam));
				break;

#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
			case WM_POINTERDOWN:
			{
				POINT pt = { GET_X_LPARAM ( lParam ), GET_Y_LPARAM ( lParam ) };
				::ScreenToClient ( this->HWnd ( ), &pt );
				this->OnPointerDown ( )(*this, loo::math::vec2 ( pt.x, pt.y ), GET_POINTERID_WPARAM ( wParam ));
			}
			break;

			case WM_POINTERUP:
			{
				POINT pt = { GET_X_LPARAM ( lParam ), GET_Y_LPARAM ( lParam ) };
				::ScreenToClient ( this->HWnd ( ), &pt );
				this->OnPointerUp ( )(*this, loo::math::vec2 ( pt.x, pt.y ), GET_POINTERID_WPARAM ( wParam ));
			}
			break;

			case WM_POINTERUPDATE:
			{
				POINT pt = { GET_X_LPARAM ( lParam ), GET_Y_LPARAM ( lParam ) };
				::ScreenToClient ( this->HWnd ( ), &pt );
				this->OnPointerUpdate ( )(*this, loo::math::vec2 ( pt.x, pt.y ), GET_POINTERID_WPARAM ( wParam ),
					IS_POINTER_INCONTACT_WPARAM ( wParam ));
			}
			break;

			case WM_POINTERWHEEL:
			{
				POINT pt = { GET_X_LPARAM ( lParam ), GET_Y_LPARAM ( lParam ) };
				::ScreenToClient ( this->HWnd ( ), &pt );
				this->OnPointerWheel ( )(*this, loo::math::vec2 ( pt.x, pt.y ), GET_POINTERID_WPARAM ( wParam ),
					GET_WHEEL_DELTA_WPARAM ( wParam ));
			}
			break;

			case WM_DPICHANGED:
			{
				RECT rc;
				::GetClientRect ( wnd, &rc );
				rc.left = static_cast<int32_t>(rc.left / dpi_scale + 0.5f);
				rc.top = static_cast<int32_t>(rc.top / dpi_scale + 0.5f);
				rc.right = static_cast<uint32_t>(rc.right / dpi_scale + 0.5f);
				rc.bottom = static_cast<uint32_t>(rc.bottom / dpi_scale + 0.5f);

				this->UpdateDpiScale ( static_cast<float>(HIWORD ( wParam )) / USER_DEFAULT_SCREEN_DPI );

				rc.left = static_cast<int32_t>(rc.left * dpi_scale + 0.5f);
				rc.top = static_cast<int32_t>(rc.top * dpi_scale + 0.5f);
				rc.right = static_cast<uint32_t>(rc.right * dpi_scale + 0.5f);
				rc.bottom = static_cast<uint32_t>(rc.bottom * dpi_scale + 0.5f);

				::AdjustWindowRect ( &rc, win_style, false );

				::SetWindowPos ( this->HWnd ( ), HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOREPOSITION );
			}
			break;
#endif

			case WM_CLOSE:
				this->OnClose ( )(*this);
				active = false;
				ready = false;
				closed = true;
				::PostQuitMessage ( 0 );
				return 0;

			case WM_SYSCOMMAND:
				if (keep_screen_on)
				{
					switch (wParam)
					{
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
						return 0;

					default:
						break;
					}
				}
				break;
			}

			return default_wnd_proc ( hWnd, uMsg, wParam, lParam );
		}

		void Window::DetectsDpi ( )
		{
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
			HMODULE shcore = ::LoadLibraryEx ( TEXT ( "SHCore.dll" ), nullptr, 0 );
			if (shcore)
			{
				typedef HRESULT ( WINAPI *SetProcessDpiAwarenessFunc )(PROCESS_DPI_AWARENESS value);
				SetProcessDpiAwarenessFunc DynamicSetProcessDpiAwareness
					= reinterpret_cast<SetProcessDpiAwarenessFunc>(::GetProcAddress ( shcore, "SetProcessDpiAwareness" ));

				DynamicSetProcessDpiAwareness ( PROCESS_PER_MONITOR_DPI_AWARE );

				::FreeLibrary ( shcore );
			}

			typedef NTSTATUS ( WINAPI *RtlGetVersionFunc )(OSVERSIONINFOEXW* pVersionInformation);
			HMODULE ntdll = ::GetModuleHandleW ( L"ntdll.dll" );
			LOO_ASSUME ( ntdll != nullptr );
			RtlGetVersionFunc DynamicRtlGetVersion = reinterpret_cast<RtlGetVersionFunc>(::GetProcAddress ( ntdll, "RtlGetVersion" ));
			if (DynamicRtlGetVersion)
			{
				OSVERSIONINFOEXW os_ver_info;
				os_ver_info.dwOSVersionInfoSize = sizeof ( os_ver_info );
				DynamicRtlGetVersion ( &os_ver_info );

				if ((os_ver_info.dwMajorVersion > 6) || ((6 == os_ver_info.dwMajorVersion) && (os_ver_info.dwMinorVersion >= 3)))
				{
					HDC desktop_dc = ::GetDC ( nullptr );
					::EnumDisplayMonitors ( desktop_dc, nullptr, EnumMonProc, reinterpret_cast<LPARAM>(this) );
					::ReleaseDC ( nullptr, desktop_dc );
				}
			}
#endif
		}

		void Window::KeepScreenOn ( )
		{
			if (keep_screen_on)
			{
#if defined(LOO_PLATFORM_WINDOWS_DESKTOP)
				::SetThreadExecutionState ( ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED );
#endif
			}
		}
	}
}


#endif