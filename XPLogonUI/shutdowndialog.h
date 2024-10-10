#pragma once
#include "dialog.h"

#define SHTDN_LOGOFF     0
#define SHTDN_SHUTDOWN   1
#define SHTDN_RESTART    2
#define SHTDN_SLEEP      3

class CShutDownDialog : public CDialog
{
private:
	HWND _hwndCombobox;
	void *_logOffControl;

	INT_PTR CALLBACK v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void _OnComboboxSelect();
	void _Shutdown(DWORD dwShutdown);

public:
	CShutDownDialog(void *logOffControl);
};