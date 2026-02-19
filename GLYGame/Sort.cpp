// Sort.cpp: implementation of the CSort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "Sort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSort::CSort()
{

}

CSort::~CSort()
{

}

void CSort::SortPosition(CMap<CString, LPCTSTR, CItem, CItem> items)
{
	if (!items.IsEmpty())
	{
		int nlength = items.GetCount();
		POSITION pos = items.GetStartPosition();
		for (int i=0; i < nlength; ++i)
		{
			CString strRefId;
			CItem *pItem;
			items.GetNextAssoc(pos, strRefId ,(CItem &)pItem);
			OutputDebugString(strRefId+"\n");
		}
	}
}

