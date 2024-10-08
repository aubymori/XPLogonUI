#pragma once
#include <windows.h>

class CDialog
{
protected:
	HWND _hWnd;
	UINT _uDlgID;

	static INT_PTR CALLBACK s_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual INT_PTR CALLBACK v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	CDialog(UINT uDlgID);
public:
	~CDialog();
	INT_PTR Show(HWND hwndParent);
	void Position();
};