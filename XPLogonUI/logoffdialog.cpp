#include "logoffdialog.h"
#include "resource.h"
#include "ConsoleLogonHook.h"

INT_PTR CALLBACK CLogOffDialog::v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
			Position();
			return TRUE;
		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return TRUE;
		case WM_COMMAND:
			switch (wParam)
			{
				case IDCANCEL:
					EndDialog(hWnd, 0);
					break;
				case IDOK:
				{
					int dummy;
					KEY_EVENT_RECORD ker = { 0 };
					ker.bKeyDown = TRUE;
					ker.wVirtualKeyCode = VK_RETURN;
					SecurityOptionControl_Press(_logOffControl, &ker, &dummy);
					EndDialog(hWnd, 0);
					break;
				}
			}
			return TRUE;
	}
	return FALSE;
}

CLogOffDialog::CLogOffDialog(void *logoffControl)
	: CDialog(IDD_LOGOFFWINDOWS_DIALOG)
	, _logOffControl(logoffControl)
{

}