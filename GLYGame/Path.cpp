// Path.cpp: implementation of the CPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "Path.h"
using namespace std;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPath::CPath()
{
	m_cost = 0;
	m_pLastNode = NULL;
}

CPath::~CPath()
{
	m_pLastNode = NULL;
	m_nodes.clear();
}

CPath *CPath::Clone()
{
	CPath *p = new CPath();
	p->IncrementCost(m_cost);
	vector<INode*> temp(m_nodes);
	p->SetNodes(temp);
	return p;
}

INode * CPath::GetLastNode()
{
	return m_pLastNode;
}

double CPath::GetF()
{
	return GetCost() + m_pLastNode->GetHeuristic();
}

double CPath::GetCost()
{
	return m_cost;
}

void CPath::IncrementCost(double num)
{
	m_cost = GetCost() + num;
}

void CPath::SetNodes(vector<INode*> nodes)
{
	m_nodes = nodes;
}

/**
 * 添加一个节点到path。
 * @param n 要添加的节点。
 */
void CPath::AddNode(INode *n)
{
	m_nodes.push_back(n);
	m_pLastNode = n;
}

vector<INode*> CPath::GetNodes()
{
	return m_nodes;
}
