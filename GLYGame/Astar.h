// Astar.h: interface for the CAstar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASTAR_H__F8D2946C_C584_4628_8D07_CA24F92A3EC8__INCLUDED_)
#define AFX_ASTAR_H__F8D2946C_C584_4628_8D07_CA24F92A3EC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "INode.h"
#include "SearchResults.h"
#include "ISearchable.h"
#include "Path.h"
#include "PriorityQueue.h"
#endif // _MSC_VER > 1000

class CAstar  
{
public:
	CAstar();
	CAstar(ISearchable *pGrid);
	virtual ~CAstar();
public:
	void SetMaxSearchTime(float fTime);
	void Init(ISearchable *pGrid);
	/**
	 * 使用A*算法查找从起始点到目标点的位置。
	 * @param pStartNode 起始点。
	 * @param pGoalNode 终止点。
	 * @return 得到的寻路结果。
	 */
	CSearchResults Search(INode *pStartNode, INode *pGoalNode);
	vector<INode*> *GetNeighbors(INode *n);
	bool IsInClosed(INode *n);

	void SetAllowDiag(bool bAllowDiag);
private:
	//起始点位置。
	INode *m_pStartNode;
	//目标点位置。
	INode *m_pGoalNode;
	
	CMap<CString, LPCTSTR, bool, bool> *m_pClosed;

	ISearchable *m_pGrid;
	//最大寻路时间。
	float m_fMaxSearchTime;
	bool m_bAllowDiag;
};

#endif // !defined(AFX_ASTAR_H__F8D2946C_C584_4628_8D07_CA24F92A3EC8__INCLUDED_)
