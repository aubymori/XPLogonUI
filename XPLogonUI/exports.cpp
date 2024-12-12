#include "xplogonui.h"

#define EXPORT  extern "C" __declspec(dllexport)

EXPORT void MessageView_SetActive()
{

}

EXPORT void MessageOptionControl_Create(void *actualInsance, int optionflag)
{

}

EXPORT void MessageView_SetMessage(const wchar_t *message)
{

}

EXPORT void MessageOptionControl_Destroy(void *actualInstance)
{

}


EXPORT void SecurityControlButtonsList_Clear()
{

}

EXPORT void SecurityControl_SetActive()
{
	g_securityView.SetActive();
}

EXPORT void SecurityControl_ButtonsReady()
{
	g_securityView.OnControlsReady();
}

EXPORT void SecurityOptionControl_Create(void *actualInstance)
{
	g_securityView.OnControlCreate(actualInstance);
}

EXPORT void SecurityOptionControl_Destroy(void *actualInstance)
{
	g_securityView.OnControlDestroy(actualInstance);
}

EXPORT void SecurityControl_SetInactive()
{
	g_securityView.SetInactive();
}


EXPORT void NotifyWasInSelectedCredentialView()
{

}

EXPORT void SelectedCredentialView_SetActive(const wchar_t *accountNameToDisplay, int flag)
{

}

EXPORT void EditControl_Create(void *actualInstance)
{

}

EXPORT void EditControl_Destroy(void *actualInstance)
{

}


EXPORT void StatusView_SetActive(const wchar_t *text)
{
	g_statusView.SetActive(text);
}

EXPORT void MessageOrStatusView_Destroy(void)
{
	//g_statusView.SetInactive();
}


EXPORT void UserSelect_SetActive()
{

}

EXPORT void SelectableUserOrCredentialControl_Sort()
{

}

EXPORT void SelectableUserOrCredentialControl_Create(void *actualInstance, const wchar_t *path)
{

}

EXPORT void SelectableUserOrCredentialControl_Destroy(void *actualInstance)
{

}