// GamePoint.cpp: implementation of the CGamePoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "GamePoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGamePoint::CGamePoint()
{

}

CGamePoint::CGamePoint(float x, float y)
{
	m_fX = x;
	m_fY = y;
}

CGamePoint::~CGamePoint()
{

}
