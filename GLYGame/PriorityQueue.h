// PriorityQueue.h: interface for the CPriorityQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIORITYQUEUE_H__5AB1D533_E120_4B2C_B90E_94B00AEE9221__INCLUDED_)
#define AFX_PRIORITYQUEUE_H__5AB1D533_E120_4B2C_B90E_94B00AEE9221__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Path.h"
#include <afxtempl.h>
#endif // _MSC_VER > 1000

class CPriorityQueue  
{
public:
	CPriorityQueue();
	virtual ~CPriorityQueue();
public:
	bool HasNextItem();
	CPath *GetNextItem();
public:
	void Enqueue(CPath *p);
public:
	vector<CPath*> *m_pArrItems;
};

#endif // !defined(AFX_PRIORITYQUEUE_H__5AB1D533_E120_4B2C_B90E_94B00AEE9221__INCLUDED_)
