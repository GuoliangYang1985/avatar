// Path.h: interface for the CPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATH_H__AC389E74_C7AB_4CFA_9A9B_CE25324BF79D__INCLUDED_)
#define AFX_PATH_H__AC389E74_C7AB_4CFA_9A9B_CE25324BF79D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "INode.h"
#include <vector>
#include <afxtempl.h>
using std::vector;
#endif // _MSC_VER > 1000

class CPath  
{
public:
	CPath();
	virtual ~CPath();
public:
	CPath *Clone();
	INode *GetLastNode();
	double GetF();
	double GetCost();
	void IncrementCost(double num);
	void SetNodes(vector<INode*> nodes);

	/**
	 * 添加一个节点到path。
	 * @param n 要添加的节点。
	 */
	void AddNode(INode *n);
	vector<INode*> GetNodes();
private:
	vector<INode*> m_nodes;
	double m_cost;
	INode *m_pLastNode;
};

#endif // !defined(AFX_PATH_H__AC389E74_C7AB_4CFA_9A9B_CE25324BF79D__INCLUDED_)
