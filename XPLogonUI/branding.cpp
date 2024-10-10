#include "branding.h"
#include "resource.h"
#include "xplogonui.h"
#include "debug.h"

const BRANDINGBITMAPIDS CBranding::s_brandingBitmapIds[] = {
	// BRANDING_2000
	{
		IDB_BANNER_2000_LARGE,
		IDB_BANNER_2000,
		IDB_BAR_2000,
	},
	// BRANDING_XP_X64
	{
		IDB_BANNER_XP_X64_LARGE,
		IDB_BANNER_XP_X64,
		IDB_BAR_XP
	},
	// BRANDING_XP_PRO
	{
		IDB_BANNER_XP_PRO_LARGE,
		IDB_BANNER_XP_PRO,
		IDB_BAR_XP
	},
	// BRANDING_XP_HOME
	{
		IDB_BANNER_XP_HOME_LARGE,
		IDB_BANNER_XP_HOME,
		IDB_BAR_XP
	},
};

void CBranding::s_MoveChildren(HWND hWnd, int dx, int dy)
{
	HWND hWndSibling;
	RECT rc;
	for (hWndSibling = GetWindow(hWnd, GW_CHILD); hWndSibling; hWndSibling = GetWindow(hWndSibling, GW_HWNDNEXT))
	{
		GetWindowRect(hWndSibling, &rc);
		MapWindowPoints(NULL, GetParent(hWndSibling), (LPPOINT)&rc, 2);
		OffsetRect(&rc, dx, dy);
		SetWindowPos(hWndSibling, NULL, rc.left, rc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	GetWindowRect(hWnd, &rc);
	MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)&rc, 2);
	SetWindowPos(
		hWnd, NULL, 0, 0,
		(rc.right - rc.left) + dx,
		(rc.bottom - rc.top) + dy,
		SWP_NOZORDER | SWP_NOMOVE
	);
}

CBranding::CBranding()
	: _type(BRANDING_2000)
	, _hbmBanner(NULL)
	, _hbmBannerLarge(NULL)
	, _hbmBar(NULL)
	, _wszBannerPath{ 0 }
	, _wszBannerLargePath{ 0 }
	, _wszBarPath{ 0 }
{
	LoadBranding();
}

void CBranding::LoadBranding()
{
	dbgprintf(L"Load branding");
	BRANDINGTYPE newType = BRANDING_2000;
	dbgprintf(L"registry status: %u", g_registry.QueryValue(L"BrandingType", (LPBYTE)&newType, sizeof(newType)));
	dbgprintf(L"Branding type: %u", newType);
	if (!_hbmBannerLarge || !_hbmBanner || !_hbmBar ||
	newType == BRANDING_CUSTOM || newType != _type)
	{
		_hbmBannerLarge = NULL;
		_hbmBanner = NULL;
		_hbmBar = NULL;
		_type = newType;
		if (_type == BRANDING_CUSTOM)
		{
			ZeroMemory(_wszBannerPath, sizeof(_wszBannerPath));
			ZeroMemory(_wszBannerLargePath, sizeof(_wszBannerLargePath));
			ZeroMemory(_wszBarPath, sizeof(_wszBarPath));
			g_registry.QueryValue(L"BannerPath", (LPBYTE)_wszBannerPath, sizeof(_wszBannerPath));
			g_registry.QueryValue(L"LargeBannerPath", (LPBYTE)_wszBannerLargePath, sizeof(_wszBannerLargePath));
			g_registry.QueryValue(L"BarPath", (LPBYTE)_wszBarPath, sizeof(_wszBarPath));
			_hbmBanner = (HBITMAP)LoadImageW(NULL, _wszBannerPath, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
			_hbmBannerLarge = (HBITMAP)LoadImageW(NULL, _wszBannerLargePath, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
			_hbmBar = (HBITMAP)LoadImageW(NULL, _wszBarPath, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
		}
		else
		{
			const BRANDINGBITMAPIDS *pIds = &s_brandingBitmapIds[_type];
			dbgprintf(L"Loading from IDs %u %u %u", pIds->uBannerId, pIds->uBannerSmallId, pIds->uBarId);
			_hbmBannerLarge = LoadBitmapW(g_hInstDLL, MAKEINTRESOURCEW(pIds->uBannerId));
			_hbmBanner = LoadBitmapW(g_hInstDLL, MAKEINTRESOURCEW(pIds->uBannerSmallId));
			_hbmBar = LoadBitmapW(g_hInstDLL, MAKEINTRESOURCEW(pIds->uBarId));
		}
	}
}

void CBranding::GetSize(bool fLarge, SIZE *pSize)
{
	SIZE sizeBanner, sizeBar;
	BITMAP bmBanner = { 0 }, bmBar = { 0 };
	GetObjectW(fLarge ? _hbmBannerLarge : _hbmBanner, sizeof(BITMAP), &bmBanner);
	GetObjectW(_hbmBar, sizeof(BITMAP), &bmBar);
	pSize->cx = max(bmBanner.bmWidth, bmBar.bmWidth);
	pSize->cy = bmBanner.bmHeight + bmBar.bmHeight;
}

void CBranding::SizeForBranding(HWND hWnd, bool fLarge)
{
	SIZE sizeBrand;
	GetSize(fLarge, &sizeBrand);
	s_MoveChildren(hWnd, 0, sizeBrand.cy);
}

void CBranding::PaintBranding(HDC hDC, bool fLarge, int barOffset /* = 0 */, int x /* = 0 */, int y /* = 0 */)
{
	int bannerX = 0, bannerY = 0;
	SIZE sizeBrand;
	HBITMAP hbmBanner = fLarge ? _hbmBannerLarge : _hbmBanner;
	BITMAP bmBanner, bmBar;
	GetSize(fLarge, &sizeBrand);
	GetObjectW(hbmBanner, sizeof(BITMAP), &bmBanner);
	GetObjectW(_hbmBar, sizeof(BITMAP), &bmBar);

	HDC hMemDC = CreateCompatibleDC(hDC);
	
	SelectObject(hMemDC, hbmBanner);
	if (bmBanner.bmWidth < sizeBrand.cx)
		bannerX = (sizeBrand.cx / 2) - (bmBanner.bmWidth / 2);

	bannerX += x;
	bannerY += y;

	BitBlt(
		hDC,
		bannerX, bannerY,
		bmBanner.bmWidth,
		bmBanner.bmHeight,
		hMemDC,
		0, 0,
		SRCCOPY
	);

	SelectObject(hMemDC, _hbmBar);
	BitBlt(
		hDC,
		barOffset + x, bmBanner.bmHeight + y,
		bmBar.bmWidth - barOffset,
		bmBar.bmHeight,
		hMemDC,
		0, 0,
		SRCCOPY
	);
	if (barOffset != 0)
		BitBlt(
			hDC,
			x, bmBanner.bmHeight + y,
			barOffset,
			bmBar.bmHeight,
			hMemDC,
			bmBar.bmWidth - barOffset, 0,
			SRCCOPY
		);

	DeleteDC(hMemDC);
}