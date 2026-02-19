// INode.cpp: implementation of the INode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "INode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int INode::GetRow()
{
	return 0;
}

int INode::GetCol()
{
	return 0;
}

void SetCol(int value)
{

}

void SetRow(int value)
{

}

double INode::GetHeuristic()
{
	return 0;
}

CString INode::GetNodeId()
{
	return "";
}

void INode::SetHeuristic(double h)
{
	
}

bool INode::Equal(INode *n)
{
	return false;
}

vector<INode*> *INode::GetNeighbors()
{
	return NULL;
}

void INode::SetNeighbors(vector<INode*> *arr)
{

}
