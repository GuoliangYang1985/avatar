// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <unordered_map>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <math.h>

#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#include "gdiplus.h"
using namespace Gdiplus;
#pragma comment(lib, "GdiPlus.lib")
#endif

static constexpr float PI = 3.14159265358979323846f;
static constexpr float PI_4 = PI / 4.0f;

#endif // _AFX_NO_AFXCMN_SUPPORT
