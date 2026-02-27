// Path.cpp: implementation of the CPath class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Path.h"
using namespace std;

CPath::CPath()
{
	mCost = 0;
	mLastNode = NULL;
}

CPath::~CPath()
{
	mLastNode = NULL;
	mNodes.clear();
}

CPath* CPath::Clone()
{
	CPath* p = new CPath();
	p->IncrementCost(mCost);
	vector<INode*> temp(mNodes);
	p->SetNodes(temp);
	return p;
}

INode* CPath::GetLastNode()
{
	return mLastNode;
}

double CPath::GetF()
{
	return GetCost() + mLastNode->GetHeuristic();
}

double CPath::GetCost() const
{
	return mCost;
}

void CPath::IncrementCost(double num)
{
	mCost = GetCost() + num;
}

void CPath::SetNodes(vector<INode*> nodes)
{
	mNodes = nodes;
}

/**
 * 添加一个节点到path。
 * @param n 要添加的节点。
 */
void CPath::AddNode(INode* n)
{
	mNodes.push_back(n);
	mLastNode = n;
}

vector<INode*> CPath::GetNodes()
{
	return mNodes;
}