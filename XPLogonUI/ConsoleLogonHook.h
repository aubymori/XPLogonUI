#pragma once
#include <windows.h>

extern void (*MessageOptionControl_Press)(void *actualInstance, const struct _KEY_EVENT_RECORD *keyrecord, int *success);
extern const wchar_t *(*MessageOptionControl_GetText)(void *actualInstance);

extern void (*SecurityOptionControl_Press)(void *actualInstance, const struct _KEY_EVENT_RECORD *keyrecord, int *success);
extern const wchar_t *(*SecurityOptionControl_getString)(void *actualInstance);

extern const wchar_t *(*EditControl_GetFieldName)(void *actualInstance);
extern const wchar_t *(*EditControl_GetInputtedText)(void *actualInstance);
extern void (*EditControl_SetInputtedText)(void *actualInstance, const wchar_t *input);
extern bool (*EditControl_isVisible)(void *actualInstance);

extern void (*ConsoleUIView__HandleKeyInputExternal)(void *instance, const struct _KEY_EVENT_RECORD *keyrecord);
extern void *(*GetConsoleUIView)();
extern void (*GetProfilePicturePathFromSID)(const wchar_t *sid, const wchar_t *outUsername, bool bHighRes);
extern void (*GetSIDFromName)(const wchar_t *username, wchar_t **sid);

extern void (*SelectableUserOrCredentialControl_GetText)(void *actualInstance, wchar_t *OutText, int MaxLength);
extern void (*SelectableUserOrCredentialControl_Press)(void *actualInstance);
extern bool (*SelectableUserOrCredentialControl_isCredentialControl)(void *actualInstance);

extern void (*HideConsoleUI)();
extern void (*ShowConsoleUI)();

bool LoadExternals(void);