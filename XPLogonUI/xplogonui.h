#pragma once
#include <windows.h>
#include "branding.h"
#include "registry.h"
#include "clhview.h"
#include "securityview.h"

extern CBranding g_branding;
extern CRegistry g_registry;
extern HINSTANCE g_hInstDLL;
extern CCLHView *g_pActiveView;

// Views
extern CSecurityView g_securityView;