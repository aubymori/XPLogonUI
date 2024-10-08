#include "securityview.h"
#include "resource.h"
#include "debug.h"
#include "xplogonui.h"
#include "ConsoleLogonHook.h"
#include "logoffdialog.h"
#include "shutdowndialog.h"
#include "util.h"
#include <stdio.h>

INT_PTR CALLBACK CSecurityView::v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			// Position and size
			g_branding.SizeForBranding(hWnd, false);
			Position();

			// Fill "You are logged on as" control
			WCHAR szFormat[256], szText[1024];
			GetLoggedOnUserInfo(_wszUserName, MAX_PATH, _wszDomainName, MAX_PATH);
			LoadStringW(g_hInstDLL, IDS_LOGON_NAME_NFN_INFO, szFormat, 256);
			swprintf_s(szText, szFormat, _wszDomainName, _wszUserName);
			SetDlgItemTextW(hWnd, IDD_OPTIONS_LOGON_NAME_INFO, szText);

			WCHAR szDate[128], szTime[128], szDateText[256];
			GetUserLogonTime(&_logonTime);
			GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, NULL, &_logonTime, NULL, szDate, 128, NULL);
			GetTimeFormatEx(LOCALE_NAME_USER_DEFAULT, NULL, &_logonTime, NULL, szTime, 128);
			swprintf_s(szDateText, L"%s %s", szDate, szTime);
			SetDlgItemTextW(hWnd, IDD_OPTIONS_LOGON_DATE, szDateText);

			return TRUE;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);
			g_branding.PaintBranding(hDC, false);
			EndPaint(hWnd, &ps);
			return TRUE;
		}
		case WM_COMMAND:
			switch (wParam)
			{
				case IDD_OPTIONS_LOCK:
					_PressControl(_lockControl);
					return TRUE;
				case IDD_OPTIONS_LOGOFF:
				{
					CLogOffDialog logOffDlg(_logOffControl);
					logOffDlg.Show(hWnd);
					return TRUE;
				}
				case IDD_OPTIONS_SHUTDOWN:
				{
					CShutDownDialog shutDownDlg;
					shutDownDlg.Show(hWnd);
					return TRUE;
				}
				case IDD_OPTIONS_CHANGEPWD:
					_PressControl(_changePassControl);
					return TRUE;
				case IDD_OPTIONS_TASKLIST:
					_PressControl(_taskMgrControl);
					return TRUE;
				case IDCANCEL:
					_PressControl(_cancelControl);
					return TRUE;
			}
			return TRUE;
		case WM_NCHITTEST:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
	return FALSE;
}

void CSecurityView::_PressControl(void *instance)
{
	int dummy;
	KEY_EVENT_RECORD ker = { 0 };
	ker.bKeyDown = TRUE;
	ker.wVirtualKeyCode = VK_RETURN;
	SecurityOptionControl_Press(instance, &ker, &dummy);
}

CSecurityView::CSecurityView()
	: CCLHView(IDD_OPTIONS_DIALOG)
	, _lockControl(nullptr)
	, _logOffControl(nullptr)
	, _changePassControl(nullptr)
	, _taskMgrControl(nullptr)
	, _cancelControl(nullptr)
	, _wszUserName{ 0 }
	, _wszDomainName{ 0 }
	, _logonTime{ 0 }
{

}

void CSecurityView::SetInactive()
{
	CCLHView::SetInactive();
	dbgprintf(L"Security view deactivate");
	_controls.clear();
	_lockControl = nullptr;
	_logOffControl = nullptr;
	_changePassControl = nullptr;
	_taskMgrControl = nullptr;
	_cancelControl = nullptr;
}

void CSecurityView::OnControlCreate(void *instance)
{
	dbgprintf(L"Security view control created");
	_controls.push_back(instance);
}

void CSecurityView::OnControlDestroy(void *instance)
{
	dbgprintf(L"Security view control destroyed");
	for (size_t i = 0; i < _controls.size(); i++)
	{
		if (_controls.at(i) == instance)
			_controls.erase(_controls.begin() + i);
	}
}

void CSecurityView::OnControlsReady()
{
	dbgprintf(L"Security view controls ready");
	// Praying these never vary in order.
	_changePassControl = _controls.at(0);
	_lockControl = _controls.at(1);
	_logOffControl = _controls.at(2);
	// Skip switch user
	_taskMgrControl = _controls.at(4);
	_cancelControl = _controls.at(_controls.size() - 1);
}