// GLYGame.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GLYGame.h"
#include "GLYGameDlg.h"

CGLYGameApp theApp;

BEGIN_MESSAGE_MAP(CGLYGameApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CGLYGameApp::CGLYGameApp()
{

}

BOOL CGLYGameApp::InitInstance()
{
	AfxEnableControlContainer();
	CGLYGameDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
