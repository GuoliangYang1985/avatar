// INode.h: interface for the INode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INODE_H__02B2BFC8_F7A1_4DBF_8939_B05F213045B1__INCLUDED_)
#define AFX_INODE_H__02B2BFC8_F7A1_4DBF_8939_B05F213045B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "afxtempl.h"
#include <vector>
using std::vector;
#endif // _MSC_VER > 1000

class __declspec(novtable)INode  
{
public:
	virtual int GetCol();
	virtual int GetRow();
	virtual void SetCol(int value);
	virtual void SetRow(int value);
	virtual double GetHeuristic();
	virtual CString GetNodeId();
	virtual bool Equal(INode *n);
	virtual void SetHeuristic(double h);
	virtual vector<INode*> *GetNeighbors();
	virtual void SetNeighbors(vector<INode*> *arr);
};

#endif // !defined(AFX_INODE_H__02B2BFC8_F7A1_4DBF_8939_B05F213045B1__INCLUDED_)
