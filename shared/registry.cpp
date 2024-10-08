#include "registry.h"

LPCWSTR CRegistry::s_szSubkey = L"SOFTWARE\\XPLogonUI";

void CRegistry::_OpenKey()
{
	if (!_hkey)
		RegOpenKeyExW(
			HKEY_LOCAL_MACHINE,
			s_szSubkey,
			NULL,
			KEY_READ | KEY_WRITE,
			&_hkey
		);
}

CRegistry::CRegistry()
	: _hkey(NULL)
{
}

LSTATUS CRegistry::QueryValue(LPCWSTR lpValueName, LPBYTE lpData, DWORD cbData, LPDWORD lpType)
{
	_OpenKey();
	return RegQueryValueExW(_hkey, lpValueName, NULL, lpType, lpData, &cbData);
}

LSTATUS CRegistry::SetValue(LPCWSTR lpValueName, DWORD dwType, LPCBYTE lpData, DWORD cbData)
{
	_OpenKey();
	return RegSetValueExW(_hkey, lpValueName, NULL, dwType, lpData, cbData);
}