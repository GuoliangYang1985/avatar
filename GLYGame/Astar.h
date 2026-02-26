// Astar.h: interface for the CAstar class.

#pragma once
#include "INode.h"
#include "SearchResults.h"
#include "ISearchable.h"
#include "Path.h"
#include "PriorityQueue.h"

class CAstar
{
public:
	CAstar();
	CAstar(ISearchable* pGrid);
	virtual ~CAstar();
public:
	void SetMaxSearchTime(float fTime);
	void Init(ISearchable* pGrid);
	/**
	 * 使用A*算法查找从起始点到目标点的位置。
	 * @param pStartNode 起始点。
	 * @param pGoalNode 终止点。
	 * @return 得到的寻路结果。
	 */
	CSearchResults Search(INode* pStartNode, INode* pGoalNode);
	vector<INode*>* GetNeighbors(INode* n);
	bool IsInClosed(INode* n);

	void SetAllowDiag(bool bAllowDiag);
private:
	//起始点位置。
	INode* mStartNode;
	//目标点位置。
	INode* mGoalNode;

	CMap<CString, LPCTSTR, bool, bool>* mClosed;

	ISearchable* mGrid;
	//最大寻路时间。
	float mMaxSearchTime;
	bool mAllowDiag;
};
