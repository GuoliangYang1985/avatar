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
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <math.h>

#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#include "gdiplus.h"
using namespace Gdiplus;
#pragma comment(lib, "GdiPlus.lib")
#endif

#ifndef PI
#define PI 3.141592653589793f
#endif

#endif // _AFX_NO_AFXCMN_SUPPORT
