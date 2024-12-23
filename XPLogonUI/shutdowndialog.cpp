#include "shutdowndialog.h"
#include "resource.h"
#include "xplogonui.h"
#include <powrprof.h>
#include <windowsx.h>
#include "ConsoleLogonHook.h"
#include "util.h"

INT_PTR CALLBACK CShutDownDialog::v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            g_branding.SizeForBranding(hWnd, false);
            Position();

            // Init combobox
            _hwndCombobox = GetDlgItem(hWnd, IDC_EXITOPTIONS_COMBO);
            WCHAR szBuffer[256];

            // Log off text is unique in that it containes current username.
            if (_logOffControl)
            {
                WCHAR szFormat[256], szUserName[256] = { 0 };
                LoadStringW(g_hInstDLL, IDS_LOGOFF_NAME, szFormat, 256);
                GetLoggedOnUserInfo(szUserName, 256, nullptr, 0);
                swprintf_s(szBuffer, szFormat, szUserName);
                ComboBox_AddString(_hwndCombobox, szBuffer);
            }

            LoadStringW(g_hInstDLL, IDS_SHUTDOWN_NAME, szBuffer, 256);
            ComboBox_AddString(_hwndCombobox, szBuffer);
            LoadStringW(g_hInstDLL, IDS_RESTART_NAME, szBuffer, 256);
            ComboBox_AddString(_hwndCombobox, szBuffer);
            LoadStringW(g_hInstDLL, IDS_SLEEP_NAME, szBuffer, 256);
            ComboBox_AddString(_hwndCombobox, szBuffer);
            // Select "Shut down" item
            ComboBox_SetCurSel(_hwndCombobox, (_logOffControl != nullptr));
            _OnComboboxSelect();

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
            if (HIWORD(wParam) == CBN_SELCHANGE)
                _OnComboboxSelect();
            else
                switch (wParam)
                {
                    case IDOK:
                        _Shutdown(ComboBox_GetCurSel(_hwndCombobox));
                        EndDialog(hWnd, 0);
                        break;
                    case IDCANCEL:
                        EndDialog(hWnd, 0);
                        break;
                }
            return TRUE;
    }
    return FALSE;
}

void CShutDownDialog::_OnComboboxSelect()
{
    int index = ComboBox_GetCurSel(_hwndCombobox);
    // Log off item is above shutdown, increase index to account for it not
    // existing
    if (!_logOffControl)
        index++;
    UINT uID = 0;
    switch (index)
    {
        case SHTDN_LOGOFF:
            uID = IDS_LOGOFF_DESC;
            break;
        case SHTDN_SHUTDOWN:
            uID = IDS_SHUTDOWN_DESC;
            break;
        case SHTDN_RESTART:
            uID = IDS_RESTART_DESC;
            break;
        case SHTDN_SLEEP:
            uID = IDS_SLEEP_DESC;
            break;
    }

    WCHAR szBuffer[256];
    LoadStringW(g_hInstDLL, uID, szBuffer, 256);
    SetDlgItemTextW(_hWnd, IDC_EXITOPTIONS_DESCRIPTION, szBuffer);
}

void CShutDownDialog::_Shutdown(DWORD dwShutdown)
{
	switch (dwShutdown)
	{
        case SHTDN_LOGOFF:
            if (_logOffControl)
            {
                int dummy;
                KEY_EVENT_RECORD ker = { 0 };
                ker.bKeyDown = TRUE;
                ker.wVirtualKeyCode = VK_RETURN;
                SecurityOptionControl_Press(_logOffControl, &ker, &dummy);
            }
            break;
        case SHTDN_SHUTDOWN:
            InitiateSystemShutdownW(
                NULL,
                NULL,
                0,
                FALSE,
                FALSE
            );
            break;
        case SHTDN_RESTART:
            ExitWindowsEx(EWX_REBOOT, 0);
            break;
        case SHTDN_SLEEP:
            SetSuspendState(FALSE, TRUE, FALSE);
            break;
	}
}

CShutDownDialog::CShutDownDialog(void *logOffControl)
	: CDialog(IDD_EXITWINDOWS_DIALOG)
    , _hwndCombobox(NULL)
    , _logOffControl(logOffControl)
{
    /* Apply the needed privilege for shutting down */
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;

    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
    LookupPrivilegeValueW(NULL, SE_SHUTDOWN_NAME, &luid);

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
}