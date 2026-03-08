// Path.cpp: implementation of the CPath class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Path.h"
using namespace std;
namespace ygl
{
	CPath::CPath() : mCost(0.0)
	{
	}

	unique_ptr<CPath> CPath::Clone() const
	{
		auto p = make_unique<CPath>();
		p->mCost = mCost;
		p->mNodes = mNodes;  // vector copy
		return p;
	}

	INode* CPath::GetLastNode() const
	{
		return mNodes.back();
	}

	double CPath::GetF() const
	{
		return GetCost() + GetLastNode()->GetHeuristic();
	}

	void CPath::IncrementCost(double num)
	{
		mCost += num;
	}

	void CPath::SetNodes(const std::vector<INode*>& nodes)
	{
		mNodes = nodes;
	}

	void CPath::AddNode(INode* n)
	{
		mNodes.push_back(n);
	}
}