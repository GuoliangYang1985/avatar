// Astar.cpp: implementation of the CAstar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "Astar.h"
using namespace std;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAstar::CAstar()
{
	SetMaxSearchTime(2000);
	m_pStartNode = NULL;
	m_pGoalNode = NULL;
	m_pClosed = NULL;
	m_pGrid = NULL;
	m_bAllowDiag = true;
}

CAstar::~CAstar()
{
	m_pStartNode = NULL;
	m_pGoalNode = NULL;
	m_pGrid = NULL;
	if (m_pClosed != NULL)
	{
		delete m_pClosed;
		m_pClosed = NULL;
	}	
}

CAstar::CAstar(ISearchable *pGrid)
{
	m_pGrid = pGrid;
	SetAllowDiag(true);
	if (m_pClosed != NULL)
	{
		delete m_pClosed;
		m_pClosed =	NULL;
	}
}

void CAstar::Init(ISearchable *pGrid)
{
	m_pGrid = pGrid;
	SetAllowDiag(true);
}

/**
 * 使用A*算法查找从起始点到目标点的位置。
 * @param pStartNode 起始点。
 * @param pGoalNode 终止点。
 * @return 得到的寻路结果。
 */
CSearchResults CAstar::Search(INode *pStartNode, INode *pGoalNode)
{
	m_pStartNode = pStartNode;
	m_pGoalNode = pGoalNode;
	m_pClosed = new CMap<CString, LPCTSTR, bool, bool>();
	CSearchResults results;
	CPriorityQueue *pQueue = new CPriorityQueue();
	CPath *pPath = new CPath();
	pPath->AddNode(pStartNode);
	pQueue->Enqueue(pPath);
	pPath = NULL;
	double diag = sqrt((double)2);
	clock_t startTime = clock();
	while (pQueue->HasNextItem())
	{
		clock_t nowTime = clock();
		if ((nowTime - startTime) > m_fMaxSearchTime)
		{
			//OutputDebugString("寻路超时!\n");
			break;
		}
		CPath *p = pQueue->GetNextItem();
		if (p != NULL)
		{
			INode *pLastNode = p->GetLastNode();
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
				m_pClosed->SetAt(pLastNode->GetNodeId(), true);
				vector<INode*> *pNeighbors = GetNeighbors(pLastNode);
				if (pNeighbors != NULL)
				{
					for (vector<INode*>::iterator iter=pNeighbors->begin(); iter != pNeighbors->end(); ++iter)
					{
						INode *t = (INode*)(*iter);
						double h = sqrt(powf(float(pGoalNode->GetCol() - t->GetCol()), 2.0)+ powf(float(pGoalNode->GetRow() - t->GetRow()), 2.0));
						t->SetHeuristic(h);
						CPath *pp = p->Clone(); 
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
						double costMultiplier = m_pGrid->GetNodeTransitionCost(pLastNode, t);
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
	if (m_pClosed != NULL)
	{
		m_pClosed->RemoveAll();
		delete m_pClosed;
		m_pClosed = NULL;
	}
	return results;
}

vector<INode*>* CAstar::GetNeighbors(INode *n)
{
	int c = n->GetCol();
	int r = n->GetRow();
	int max_c = m_pGrid->GetCols();
	int max_r = m_pGrid->GetRows();
	vector<INode*> *pArr = new vector<INode*>();
	INode *t = NULL;
	if (c + 1 < max_c)
	{
		t =	m_pGrid->GetNode(c + 1,  r);
		pArr->push_back(t);
	}
	if (r + 1 < max_r)
	{
		t = m_pGrid->GetNode(c, r + 1);
		pArr->push_back(t);
	}
	if (c - 1 >= 0)
	{
		t = m_pGrid->GetNode(c - 1, r);
		pArr->push_back(t);
	}
	if (r - 1 >= 0)
	{
		t = m_pGrid->GetNode(c, r - 1);
		pArr->push_back(t);
	}

	if (m_bAllowDiag)
	{
		if (c - 1 > 0 && r + 1 < max_r)
		{
			t = m_pGrid->GetNode(c - 1, r + 1);
			pArr->push_back(t);
		}
		if (c + 1 < max_c && r + 1 < max_r)
		{
			t = m_pGrid->GetNode(c + 1, r + 1);
			pArr->push_back(t);
		}
		if (c - 1 > 0 && r - 1 > 0)
		{
			t = m_pGrid->GetNode(c - 1, r - 1);
			pArr->push_back(t);
		}
		if (c + 1 < max_c && r - 1 > 0)
		{
			t = m_pGrid->GetNode(c + 1, r - 1);
			pArr->push_back(t);
		}
	}
	return pArr;
}

bool CAstar::IsInClosed(INode *n)
{
	bool cur = false;
	m_pClosed->Lookup(n->GetNodeId(), cur);
	return cur;
}

void CAstar::SetAllowDiag(bool bAllowDiag)
{
	m_bAllowDiag = bAllowDiag;
}


void CAstar::SetMaxSearchTime(float fTime)
{
	m_fMaxSearchTime = fTime;
}
