// Coordiante.cpp: implementation of the CCoordiante class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "Coordiante.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoordiante::CCoordiante()
{

}

CCoordiante::CCoordiante(float x, float y, float z)
{
	m_fX = x;
	m_fY = y;
	m_fZ = z;
}
CCoordiante::~CCoordiante()
{

}
