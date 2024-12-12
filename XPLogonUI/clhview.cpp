#include "clhview.h"
#include "xplogonui.h"
#include "debug.h"
#include "ConsoleLogonHook.h"

DWORD CALLBACK CCLHView::s_DlgThreadProc(LPVOID lpParam)
{
	dbgprintf(L"Dialog thread begin");
	((CCLHView *)lpParam)->Show(NULL);
	dbgprintf(L"Dialog thread end");
	ExitThread(0);
	return 0;
}

void CCLHView::SetActive()
{
	if (g_pActiveView == this)
		return;

	if (g_pActiveView)
		g_pActiveView->SetInactive();
	g_pActiveView = this;
	HideConsoleUI();
	CreateThread(NULL, NULL, s_DlgThreadProc, this, NULL, NULL);
}

void CCLHView::SetInactive()
{
	if (g_pActiveView != this)
		return;

	if (_hWnd)
	{
		EndDialog(_hWnd, 0);
		_hWnd = NULL;
	}

	if (g_pActiveView)
		g_pActiveView = nullptr;

	ShowConsoleUI();
}