// Astar.cpp: implementation of the CAstar class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Astar.h"
using namespace std;

CAstar::CAstar()
{
	SetMaxSearchTime(2000);
	mStartNode = NULL;
	mGoalNode = NULL;
	mClosed = NULL;
	mGrid = NULL;
	mAllowDiag = true;
}

CAstar::~CAstar()
{
	mStartNode = NULL;
	mGoalNode = NULL;
	mGrid = NULL;
	if (mClosed != NULL)
	{
		delete mClosed;
		mClosed = NULL;
	}
}

CAstar::CAstar(ISearchable* pGrid)
{
	mGrid = pGrid;
	SetAllowDiag(true);
	if (mClosed != NULL)
	{
		delete mClosed;
		mClosed = NULL;
	}
}

void CAstar::Init(ISearchable* pGrid)
{
	mGrid = pGrid;
	SetAllowDiag(true);
}

/**
 * 使用A*算法查找从起始点到目标点的位置。
 * @param pStartNode 起始点。
 * @param pGoalNode 终止点。
 * @return 得到的寻路结果。
 */
CSearchResults CAstar::Search(INode* pStartNode, INode* pGoalNode)
{
	mStartNode = pStartNode;
	mGoalNode = pGoalNode;
	mClosed = new CMap<CString, LPCTSTR, bool, bool>();
	CSearchResults results;
	CPriorityQueue* pQueue = new CPriorityQueue();
	CPath* pPath = new CPath();
	pPath->AddNode(pStartNode);
	pQueue->Enqueue(pPath);
	pPath = NULL;
	double diag = sqrt((double)2);
	clock_t startTime = clock();
	while (pQueue->HasNextItem())
	{
		clock_t nowTime = clock();
		if ((nowTime - startTime) > mMaxSearchTime)
		{
			//OutputDebugString("寻路超时!\n");
			break;
		}
		CPath* p = pQueue->GetNextItem();
		if (p != NULL)
		{
			INode* pLastNode = p->GetLastNode();
			if (IsInClosed(pLastNode))
			{
				delete p;
				p = NULL;
				continue;
			}
			else if (pLastNode->Equal(pGoalNode))
			{
				results.SetIsSuccess(true);
				results.SetPath(p);
				break;
			}
			else
			{
				mClosed->SetAt(pLastNode->GetNodeId(), true);
				vector<INode*>* pNeighbors = GetNeighbors(pLastNode);
				if (pNeighbors != NULL)
				{
					for (vector<INode*>::iterator iter = pNeighbors->begin(); iter != pNeighbors->end(); ++iter)
					{
						INode* t = (INode*)(*iter);
						double h = sqrt(powf(float(pGoalNode->GetCol() - t->GetCol()), 2.0) + powf(float(pGoalNode->GetRow() - t->GetRow()), 2.0));
						t->SetHeuristic(h);
						CPath* pp = p->Clone();
						pp->AddNode(t);

						double cost = 0;
						if (t->GetCol() == pLastNode->GetCol() || t->GetRow() == pLastNode->GetRow())
						{
							cost = 1;
						}
						else
						{
							cost = diag;
						}
						double costMultiplier = mGrid->GetNodeTransitionCost(pLastNode, t);
						cost *= costMultiplier;
						pp->IncrementCost(cost);
						pQueue->Enqueue(pp);
					}
					pNeighbors->clear();
					delete pNeighbors;
					pNeighbors = NULL;
				}
			}
			delete p;
			p = NULL;
		}
	}
	if (pQueue != NULL)
	{
		delete pQueue;
		pQueue = NULL;
	}
	if (mClosed != NULL)
	{
		mClosed->RemoveAll();
		delete mClosed;
		mClosed = NULL;
	}
	return results;
}

vector<INode*>* CAstar::GetNeighbors(INode* n)
{
	int c = n->GetCol();
	int r = n->GetRow();
	int max_c = mGrid->GetCols();
	int max_r = mGrid->GetRows();
	vector<INode*>* pArr = new vector<INode*>();
	INode* t = NULL;
	if (c + 1 < max_c)
	{
		t = mGrid->GetNode(c + 1, r);
		pArr->push_back(t);
	}
	if (r + 1 < max_r)
	{
		t = mGrid->GetNode(c, r + 1);
		pArr->push_back(t);
	}
	if (c - 1 >= 0)
	{
		t = mGrid->GetNode(c - 1, r);
		pArr->push_back(t);
	}
	if (r - 1 >= 0)
	{
		t = mGrid->GetNode(c, r - 1);
		pArr->push_back(t);
	}

	if (mAllowDiag)
	{
		if (c - 1 > 0 && r + 1 < max_r)
		{
			t = mGrid->GetNode(c - 1, r + 1);
			pArr->push_back(t);
		}
		if (c + 1 < max_c && r + 1 < max_r)
		{
			t = mGrid->GetNode(c + 1, r + 1);
			pArr->push_back(t);
		}
		if (c - 1 > 0 && r - 1 > 0)
		{
			t = mGrid->GetNode(c - 1, r - 1);
			pArr->push_back(t);
		}
		if (c + 1 < max_c && r - 1 > 0)
		{
			t = mGrid->GetNode(c + 1, r - 1);
			pArr->push_back(t);
		}
	}
	return pArr;
}

bool CAstar::IsInClosed(INode* n)
{
	bool cur = false;
	mClosed->Lookup(n->GetNodeId(), cur);
	return cur;
}

void CAstar::SetAllowDiag(bool bAllowDiag)
{
	mAllowDiag = bAllowDiag;
}


void CAstar::SetMaxSearchTime(float fTime)
{
	mMaxSearchTime = fTime;
}
