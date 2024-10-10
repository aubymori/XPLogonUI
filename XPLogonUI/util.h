#pragma once
#include <windows.h>

/**
  * Gets information about the logged on user.
  *
  * lpUsername - Buffer to receive the username. This can be NULL if you want domain only.
  * cchUsernameMax - Size of lpUsername buffer.
  * lpDomain - Buffer to receive the domain. This can be NULL if you want username only.
  * cchDomainMax - Size of lpDomain buffer.
  *
  * Return value - The session ID if successful, -1 on failure.
  */
DWORD GetLoggedOnUserInfo(LPWSTR lpUsername, UINT cchUsernameMax, LPWSTR lpDomain, UINT cchDomainMax);

/**
  * Gets a user's logon time.
  *
  * lpSystemTime - Pointer to a SYSTEMTIME structure to receive the logon time.
  *
  * Return value - true if successful, false if failed.
  */
bool GetUserLogonTime(LPSYSTEMTIME lpSystemTime);

/**
  * Is the current session that of nt authority\system?
  * In other words, are we logged out?
  */
bool IsSystemUser(void);

/**
  * Does the system display last username on LogonUI?
  */
bool IsFriendlyLogonUI(void);