// ISearchable.h: interface for the ISearchable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISEARCHABLE_H__60E29106_A351_4993_973D_F0F03405AECD__INCLUDED_)
#define AFX_ISEARCHABLE_H__60E29106_A351_4993_973D_F0F03405AECD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "INode.h"
#endif // _MSC_VER > 1000

class __declspec()ISearchable  
{
public:
	virtual int GetCols();
	virtual int GetRows();
	virtual INode *GetNode(int col, int row);
	virtual float GetNodeTransitionCost(INode *n1, INode *n2);
};

#endif // !defined(AFX_ISEARCHABLE_H__60E29106_A351_4993_973D_F0F03405AECD__INCLUDED_)
