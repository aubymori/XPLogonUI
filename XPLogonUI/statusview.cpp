#include "statusview.h"
#include "resource.h"
#include "xplogonui.h"

INT_PTR CALLBACK CStatusView::v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			SIZE sizeBrand;
			g_branding.GetSize(false, &sizeBrand);
			_cxBrand = sizeBrand.cx;
			
			Position();
			g_branding.SizeForBranding(hWnd, false);

			SetTimer(hWnd, 20, 20, nullptr);
			_hwndMessage = GetDlgItem(hWnd, IDC_STATUS_MESSAGE_TEXT);
			SetWindowTextW(_hwndMessage, _wszInitialText);
			return TRUE;
		}
		case WM_TIMER:
		{
			HDC hDC = GetDC(hWnd);
			g_branding.PaintBranding(hDC, false, _barOffset);
			_barOffset = (_barOffset + 5) % _cxBrand;
			ReleaseDC(hWnd, hDC);
			return TRUE;
		}
	}
	return FALSE;
}

CStatusView::CStatusView()
	: CCLHView(IDD_STATUS_MESSAGE_DIALOG)
	, _hwndMessage(NULL)
	, _cxBrand(0)
	, _barOffset(0)
	, _wszInitialText{ 0 }
{
	
}

void CStatusView::SetActive(LPCWSTR lpszText)
{
	if (!lpszText)
		return;

	if (g_pActiveView != this)
	{
		wcscpy_s(_wszInitialText, lpszText);
		CCLHView::SetActive();
		return;
	}
	else if (_hwndMessage)
	{
		SetWindowTextW(_hwndMessage, lpszText);
	}
}

void CStatusView::SetInactive()
{
	CCLHView::SetInactive();
	_hwndMessage = NULL;
	_barOffset = 0;
	ZeroMemory(_wszInitialText, sizeof(_wszInitialText));
}