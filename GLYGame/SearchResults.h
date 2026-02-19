// SearchResults.h: interface for the CSearchResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHRESULTS_H__B200585C_482D_408F_9CE5_A9438293E1AD__INCLUDED_)
#define AFX_SEARCHRESULTS_H__B200585C_482D_408F_9CE5_A9438293E1AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Path.h"
#endif // _MSC_VER > 1000

class CSearchResults  
{
public:
	CSearchResults();
	virtual ~CSearchResults();
public:
	void SetPath(CPath *p);
	CPath * GetPath();
	bool GetIsSuccess();
	void SetIsSuccess(bool val);
public:
	bool m_bSuccess;
	CPath *m_pPath;
};

#endif // !defined(AFX_SEARCHRESULTS_H__B200585C_482D_408F_9CE5_A9438293E1AD__INCLUDED_)
