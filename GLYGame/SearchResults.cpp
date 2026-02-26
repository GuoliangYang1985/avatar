// SearchResults.cpp: implementation of the CSearchResults class.

#include "stdafx.h"
#include "GLYGame.h"
#include "SearchResults.h"

CSearchResults::CSearchResults()
{
	mSuccess = false;
	mPath = NULL;
}

CSearchResults::~CSearchResults()
{
	mPath = NULL;
}

void CSearchResults::SetPath(CPath* p)
{
	mPath = p;
}

CPath* CSearchResults::GetPath()
{
	return mPath;
}

bool CSearchResults::GetIsSuccess()
{
	return mSuccess;
}

void CSearchResults::SetIsSuccess(bool val)
{
	mSuccess = val;
}