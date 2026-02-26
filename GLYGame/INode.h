// INode.h: interface for the INode class.

#pragma once
#include <vector>

using std::vector;


class __declspec(novtable)INode
{
public:
	virtual int GetCol();
	virtual int GetRow();
	virtual void SetCol(int value);
	virtual void SetRow(int value);
	virtual double GetHeuristic();
	virtual CString GetNodeId();
	virtual bool Equal(INode* n);
	virtual void SetHeuristic(double h);
	virtual vector<INode*>* GetNeighbors();
	virtual void SetNeighbors(vector<INode*>* arr);
};
