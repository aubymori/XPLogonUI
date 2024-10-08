#pragma once
#include <windows.h>

class CRegistry
{
private:
	static LPCWSTR s_szSubkey;
	HKEY _hkey;
	void _OpenKey();

public:
	CRegistry();

	LSTATUS QueryValue(LPCWSTR lpValueName, LPBYTE lpData, DWORD cbData, LPDWORD lpType = nullptr);
	LSTATUS SetValue(LPCWSTR lpValueName, DWORD dwType, LPCBYTE lpData, DWORD cbData);
};