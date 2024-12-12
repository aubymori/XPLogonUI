#pragma once
#include "clhview.h"

class CStatusView : public CCLHView
{
private:
	HWND _hwndMessage;
	int _cxBrand;
	int _barOffset;
	WCHAR _wszInitialText[512];

	INT_PTR CALLBACK v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CStatusView();
	void SetActive(LPCWSTR lpszText);
	void SetInactive();
};