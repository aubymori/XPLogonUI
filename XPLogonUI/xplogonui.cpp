#include <windows.h>
#include "xplogonui.h"
#include "ConsoleLogonHook.h"
#include "debug.h"
#include "util.h"

// Globals
CBranding g_branding;
CRegistry g_registry;
HINSTANCE g_hInstDLL = NULL;
CCLHView *g_pActiveView = nullptr;

// Views
CSecurityView g_securityView;
CStatusView   g_statusView;

static HANDLE s_hWallHostProcess = NULL;

extern "C" __declspec(dllexport) void InitUI(void)
{
	if (!LoadExternals() || IsFriendlyLogonUI())
	{
		FreeLibraryAndExitThread(g_hInstDLL, 0);
		return;
	}

	g_branding.LoadBranding();

	PROCESS_INFORMATION pi;
	STARTUPINFOW si = { 0 };
	si.cb = sizeof(si);
	if (CreateProcessW(
		L"WallpaperHost.exe",
		NULL, NULL, NULL, FALSE,
		NULL, NULL, NULL, &si, &pi
	))
	{
		dbgprintf(L"Created WallpaperHost process");
		s_hWallHostProcess = pi.hProcess;
	}
	else
	{
		dbgprintf(L"Failed to create WallpaperHost process. Last error: 0x%X", GetLastError());
	}
}

BOOL WINAPI DllMain(
	HINSTANCE hInstDLL,
	DWORD     fdwReason,
	LPVOID    lpvReserved
)
{
	g_hInstDLL = hInstDLL;
	switch (fdwReason)
	{
		case DLL_PROCESS_DETACH:
			if (s_hWallHostProcess)
			{
				dbgprintf(L"Terminating WallpaperHost process");
				TerminateProcess(s_hWallHostProcess, 0);
			}
			break;
	}
	return TRUE;
}