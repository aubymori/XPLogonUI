#pragma once
#include "dialog.h"

#define SHTDN_SHUTDOWN   0
#define SHTDN_RESTART    1
#define SHTDN_SLEEP      2

class CShutDownDialog : public CDialog
{
private:
	HWND _hwndCombobox;

	INT_PTR CALLBACK v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void _OnComboboxSelect();
	void _Shutdown(DWORD dwShutdown);

public:
	CShutDownDialog();
};