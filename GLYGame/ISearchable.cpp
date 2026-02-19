// ISearchable.cpp: implementation of the ISearchable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ISearchable.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int ISearchable::GetCols()
{
	return 0;
}

int ISearchable::GetRows()
{
	return 0;
}

INode *ISearchable::GetNode(int col, int row)
{
	INode *n=NULL;
	return n;
}

float ISearchable::GetNodeTransitionCost(INode *n1, INode *n2)
{
	return 0;
}
