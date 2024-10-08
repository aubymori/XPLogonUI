#include "ConsoleLogonHook.h"
#include "debug.h"

void (*MessageOptionControl_Press)(void *actualInstance, const struct _KEY_EVENT_RECORD *keyrecord, int *success) = nullptr;
const wchar_t *(*MessageOptionControl_GetText)(void *actualInstance) = nullptr;

void (*SecurityOptionControl_Press)(void *actualInstance, const struct _KEY_EVENT_RECORD *keyrecord, int *success) = nullptr;
const wchar_t *(*SecurityOptionControl_getString)(void *actualInstance) = nullptr;

const wchar_t *(*EditControl_GetFieldName)(void *actualInstance) = nullptr;
const wchar_t *(*EditControl_GetInputtedText)(void *actualInstance) = nullptr;
void (*EditControl_SetInputtedText)(void *actualInstance, const wchar_t *input) = nullptr;
bool (*EditControl_isVisible)(void *actualInstance) = nullptr;

void (*ConsoleUIView__HandleKeyInputExternal)(void *instance, const struct _KEY_EVENT_RECORD *keyrecord) = nullptr;
void *(*GetConsoleUIView)() = nullptr;
void (*GetProfilePicturePathFromSID)(const wchar_t *sid, const wchar_t *outUsername, bool bHighRes) = nullptr;
void (*GetSIDFromName)(const wchar_t *username, wchar_t **sid) = nullptr;

void (*SelectableUserOrCredentialControl_GetText)(void *actualInstance, wchar_t *OutText, int MaxLength) = nullptr;
void (*SelectableUserOrCredentialControl_Press)(void *actualInstance) = nullptr;
bool (*SelectableUserOrCredentialControl_isCredentialControl)(void *actualInstance) = nullptr;

void (*HideConsoleUI)() = nullptr;
void (*ShowConsoleUI)() = nullptr;

#define LOAD_EXTERNAL(NAME)                                   \
	*(FARPROC *)&NAME = GetProcAddress(hCLHModule, #NAME);    \
	if (!NAME)                                                \
	{                                                         \
		dbgprintf(L"Failed to load CLH function %s", L#NAME); \
		return false;                                         \
	}

bool LoadExternals(void)
{
	HMODULE hCLHModule = GetModuleHandleW(L"ConsoleLogonHook.dll");
	if (!hCLHModule)
	{
		dbgprintf(L"Failed to get ConsoleLogonHook module");
		return false;
	}

	LOAD_EXTERNAL(MessageOptionControl_Press)
	LOAD_EXTERNAL(MessageOptionControl_GetText)
	LOAD_EXTERNAL(SecurityOptionControl_Press)
	LOAD_EXTERNAL(SecurityOptionControl_getString)
	LOAD_EXTERNAL(EditControl_GetFieldName)
	LOAD_EXTERNAL(EditControl_GetInputtedText)
	LOAD_EXTERNAL(EditControl_SetInputtedText)
	LOAD_EXTERNAL(EditControl_isVisible)
	LOAD_EXTERNAL(ConsoleUIView__HandleKeyInputExternal)
	LOAD_EXTERNAL(GetConsoleUIView)
	LOAD_EXTERNAL(GetProfilePicturePathFromSID)
	LOAD_EXTERNAL(GetSIDFromName)
	LOAD_EXTERNAL(SelectableUserOrCredentialControl_GetText)
	LOAD_EXTERNAL(SelectableUserOrCredentialControl_Press)
	LOAD_EXTERNAL(SelectableUserOrCredentialControl_isCredentialControl)
	LOAD_EXTERNAL(HideConsoleUI)
	LOAD_EXTERNAL(ShowConsoleUI)

	return true;
}