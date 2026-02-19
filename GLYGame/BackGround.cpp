////////////////////////////////////////////////////////////////////// 
//
// Copyright (C) Guoliang Yang. All rights reserved.
// BackGround.cpp: implementation of the CBackGround class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "BackGround.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBackGround::CBackGround()
{
	m_nStartCol = 30;
	m_nStartRow = 30;
	m_nCols = 0;
	m_nRows = 0;
	m_offsetX = 0.0;
	m_offsetY = 0.0;
	m_strBackPath = "";
}

CBackGround::~CBackGround()
{

}
