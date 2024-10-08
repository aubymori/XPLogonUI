#pragma once
#include "dialog.h"

class CCLHView : public CDialog
{
protected:
	using CDialog::CDialog;
	static DWORD CALLBACK s_DlgThreadProc(LPVOID lpParam);
	
public:
	virtual void SetActive();
	virtual void SetInactive();
};