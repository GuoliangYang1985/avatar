// PriorityQueue.cpp: implementation of the CPriorityQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "PriorityQueue.h"
using namespace std;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPriorityQueue::CPriorityQueue()
{
	m_pArrItems = new vector<CPath *>();
}

CPriorityQueue::~CPriorityQueue()
{
	if (m_pArrItems != NULL)
	{
		for (vector<CPath *>::iterator iter = m_pArrItems->begin(); iter != m_pArrItems->end(); ++iter)
		{
			if (*iter != NULL)
			{
				delete *iter;
				*iter = NULL;
			}
		}
		m_pArrItems->clear();
		delete m_pArrItems;
		m_pArrItems = NULL;
	}
}

bool CPriorityQueue::HasNextItem()
{
	return m_pArrItems->size() > 0;
}

CPath *CPriorityQueue::GetNextItem()
{
	CPath * p= *(m_pArrItems->begin());
	m_pArrItems->erase(m_pArrItems->begin());
	return p;
}

/**
 * 添加路径到队列。
 */
void CPriorityQueue::Enqueue(CPath *p)
{
	double val = p->GetF();
	bool added = false;
	for (vector<CPath *>::iterator iter = m_pArrItems->begin(); iter != m_pArrItems->end(); ++iter)
	{
		CPath *curr = *iter;
		if (val < curr->GetF())
		{
			m_pArrItems->insert(iter, 1, p);
			added = true;
			break;
		}
	}
	if (!added)
	{
		m_pArrItems->push_back(p);
	}
}
