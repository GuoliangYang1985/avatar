// GLYGame.h : main header file for the GLYGAME application
//

#if !defined(AFX_GLYGAME_H__12788B46_667E_4EA7_AEF0_5AC58E90E0CF__INCLUDED_)
#define AFX_GLYGAME_H__12788B46_667E_4EA7_AEF0_5AC58E90E0CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGLYGameApp:
// See GLYGame.cpp for the implementation of this class
//

class CGLYGameApp : public CWinApp
{
public:
	CGLYGameApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLYGameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGLYGameApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLYGAME_H__12788B46_667E_4EA7_AEF0_5AC58E90E0CF__INCLUDED_)
