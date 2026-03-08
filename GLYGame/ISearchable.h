// ISearchable.h: interface for the ISearchable class.

#pragma once
#include "INode.h"
namespace ygl
{
	class __declspec()ISearchable
	{
	public:
		virtual int GetCols();
		virtual int GetRows();
		virtual INode* GetNode(int col, int row);
		virtual float GetNodeTransitionCost(INode* n1, INode* n2);
	};
}