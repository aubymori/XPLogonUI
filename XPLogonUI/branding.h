#pragma once
#include <windows.h>

typedef enum _BRANDINGTYPE
{
	BRANDING_2000 = 0,
	BRANDING_XP_X64,
	BRANDING_XP_PRO,
	BRANDING_XP_HOME,
	BRANDING_CUSTOM
} BRANDINGTYPE;

typedef struct _BRANDINGBITMAPIDS
{
	UINT uBannerId;
	UINT uBannerSmallId;
	UINT uBarId;
} BRANDINGBITMAPIDS;

class CBranding
{
private:
	static const BRANDINGBITMAPIDS s_brandingBitmapIds[];

	BRANDINGTYPE _type;
	HBITMAP _hbmBanner;
	HBITMAP _hbmBannerLarge;
	HBITMAP _hbmBar;
	WCHAR _wszBannerPath[MAX_PATH];
	WCHAR _wszBannerLargePath[MAX_PATH];
	WCHAR _wszBarPath[MAX_PATH];

	static void s_MoveChildren(HWND hWnd, int dx, int dy);
public:
	CBranding();
	void LoadBranding();
	void GetSize(bool fLarge, SIZE *pSize);
	void SizeForBranding(HWND hWnd, bool fLarge);
	void PaintBranding(HDC hDC, bool fLarge, int barOffset = 0);
};