// Path.h: interface for the CPath class.

#pragma once
#include "INode.h"
#include <vector>
#include <afxtempl.h>

class CPath
{
public:
	CPath();
	virtual ~CPath();
public:
	CPath* Clone();
	INode* GetLastNode();
	double GetF();
	double GetCost() const;
	void IncrementCost(double num);
	void SetNodes(std::vector<INode*> nodes);

	/**
	 * 添加一个节点到path。
	 * @param n 要添加的节点。
	 */
	void AddNode(INode* n);
	std::vector<INode*> GetNodes();
private:
	std::vector<INode*> mNodes;
	double mCost;
	INode* mLastNode;
};
