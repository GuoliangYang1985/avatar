// Sort.h: interface for the CSort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SORT_H__1A53E494_4632_416E_BABC_22726233BC1C__INCLUDED_)
#define AFX_SORT_H__1A53E494_4632_416E_BABC_22726233BC1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include<afxtempl.h>
#include"Item.h"
#endif // _MSC_VER > 1000

class CSort  
{
public:
	CSort();
	virtual ~CSort();
public:
	static void SortPosition(CMap<CString, LPCTSTR, CItem, CItem> items);
};

#endif // !defined(AFX_SORT_H__1A53E494_4632_416E_BABC_22726233BC1C__INCLUDED_)
