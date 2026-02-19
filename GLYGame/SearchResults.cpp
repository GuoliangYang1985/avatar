// SearchResults.cpp: implementation of the CSearchResults class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "SearchResults.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSearchResults::CSearchResults()
{
	m_bSuccess = false;
	m_pPath = NULL;
}

CSearchResults::~CSearchResults()
{	
	m_pPath = NULL;
}

void CSearchResults::SetPath(CPath *p)
{
	m_pPath = p;
}

CPath *CSearchResults::GetPath()
{
	return m_pPath;
}

bool CSearchResults::GetIsSuccess()
{
	return m_bSuccess;
}

void CSearchResults::SetIsSuccess(bool val)
{
	m_bSuccess = val;
}
