#include "dialog.h"
#include "xplogonui.h"
#include "debug.h"

INT_PTR CALLBACK CDialog::s_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG)
	{
		CDialog *pThis = (CDialog *)lParam;
		if (pThis)
		{
			dbgprintf(L"WM_INITDIALOG, found the instance.");
			pThis->_hWnd = hWnd;
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
		}
	}

	CDialog *pThis = (CDialog *)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	if (pThis)
		return pThis->v_DlgProc(hWnd, uMsg, wParam, lParam);
	return FALSE;
}

CDialog::CDialog(UINT uDlgID)
	: _hWnd(NULL)
	, _uDlgID(uDlgID)
{

}

CDialog::~CDialog()
{
	if (_hWnd)
		EndDialog(_hWnd, 0);
}

INT_PTR CDialog::Show(HWND hwndParent)
{
	return DialogBoxParamW(
		g_hInstDLL,
		MAKEINTRESOURCEW(_uDlgID),
		hwndParent,
		s_DlgProc,
		(LPARAM)this
	);
}

void CDialog::Position()
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);

	SetWindowPos(
		_hWnd,
		HWND_TOP,
		(GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2 + GetSystemMetrics(SM_XVIRTUALSCREEN),
		(GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 3 + GetSystemMetrics(SM_YVIRTUALSCREEN),
		0, 0,
		SWP_NOSIZE
	);
}