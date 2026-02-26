// Path.h: interface for the CPath class.

#pragma once
#include "INode.h"
#include <vector>
#include <afxtempl.h>
using std::vector;

class CPath
{
public:
	CPath();
	virtual ~CPath();
public:
	CPath* Clone();
	INode* GetLastNode();
	double GetF();
	double GetCost();
	void IncrementCost(double num);
	void SetNodes(vector<INode*> nodes);

	/**
	 * 添加一个节点到path。
	 * @param n 要添加的节点。
	 */
	void AddNode(INode* n);
	vector<INode*> GetNodes();
private:
	vector<INode*> mNodes;
	double mCost;
	INode* mLastNode;
};
