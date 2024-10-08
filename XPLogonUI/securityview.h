#pragma once
#include "clhview.h"
#include <vector>

class CSecurityView : public CCLHView
{
private:
	std::vector<void *> _controls;
	void *_lockControl;
	void *_logOffControl;
	void *_changePassControl;
	void *_taskMgrControl;
	void *_cancelControl;

	// Display info
	WCHAR _wszUserName[MAX_PATH];
	WCHAR _wszDomainName[MAX_PATH];
	SYSTEMTIME _logonTime;

	INT_PTR CALLBACK v_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void _PressControl(void *instance);

public:
	CSecurityView();
	void SetInactive();

	void OnControlCreate(void *instance);
	void OnControlDestroy(void *instance);
	void OnControlsReady();
};