#pragma once
#include "dialog.h"

class CLogOffDialog : public CDialog
{
private:
	void *_logOffControl;

public:
	INT_PTR CALLBACK v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	CLogOffDialog(void *logoffControl);
};