// INode.h: interface for the INode class.

#pragma once
#include <vector>

class __declspec(novtable)INode
{
public:
	virtual ~INode() {}

	virtual int GetCol()const = 0;
	virtual int GetRow()const = 0;
	virtual void SetCol(int value) = 0;
	virtual void SetRow(int value) = 0;

	virtual double GetHeuristic()const = 0;
	virtual void SetHeuristic(double h) = 0;

	virtual const CString& GetNodeId() const = 0;

	virtual bool Equal(const INode* other)const = 0;

	virtual const std::vector<INode*>& GetNeighbors() const = 0;
	virtual void SetNeighbors(const std::vector<INode*>& neighbors) = 0;
};