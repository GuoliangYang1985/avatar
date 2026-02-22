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
	mStartCol = 30;
	mStartRow = 30;
	mCols = 0;
	mRows = 0;
	mOffsetX = 0.0;
	mOffsetY = 0.0;
	mBackPath = "";
}

CBackGround::~CBackGround()
{

}
