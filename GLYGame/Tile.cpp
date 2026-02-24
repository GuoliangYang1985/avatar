// Tile.cpp
// Implementation of the CTile class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Tile.h"

// Initialize static member
int CTile::IDS = 0;

CTile::CTile()
	: mArrItems(new std::vector<CItem*>()),
	mArrNeighbors(nullptr),
	mEnabled(true),
	mBaseWalkability(true),
	mBasePlaceability(true),
	mH(0.0),
	mWalkable(true),
	mCol(0),
	mRow(0)
{
	++IDS;
	mNodeId.Format(_T("%d"), IDS);
	mNodeType = _T("normal");
}

CTile::~CTile()
{
	delete mArrNeighbors;
	delete mArrItems;
}

void CTile::AddItem(CItem* pItem)
{
	mArrItems->push_back(pItem);
	DeterminePlaceability();
	DetermineWalkability();
}

void CTile::FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode)
{
	mBaseWalkability = CXmlUtil::GetAttributeToBool(pItemDefNode, "walkability");
	mBasePlaceability = CXmlUtil::GetAttributeToBool(pItemDefNode, "placeability");
	mWalkable = mBaseWalkability;
}

void CTile::Enable()
{
	mEnabled = true;
}

void CTile::Disable()
{
	mEnabled = false;
}

void CTile::DeterminePlaceability()
{
	bool allowsPlacement = mBasePlaceability;
	if (allowsPlacement)
	{
		for (CItem* pItem : *mArrItems)
		{
			if (!pItem->GetItemDefinition()->GetOverlap())
			{
				allowsPlacement = false;
				break;
			}
		}
	}
	mBasePlaceability = mEnabled && allowsPlacement;
}

void CTile::DetermineWalkability()
{
	bool allowsWalk = mBaseWalkability;
	if (allowsWalk)
	{
		for (CItem* pItem : *mArrItems)
		{
			if (!pItem->GetItemDefinition()->GetWalkable())
			{
				allowsWalk = false;
				break;
			}
		}
	}
	mWalkable = mEnabled && allowsWalk;
}

void CTile::SetBaseWalkability(bool value)
{
	mBaseWalkability = value;
}

bool CTile::GetBaseWalkablity()  // Note: intentional misspelling
{
	return mBaseWalkability;
}

bool CTile::GetWalkable()
{
	return mWalkable;
}

void CTile::SetBasePlaceability(bool value)
{
	mBasePlaceability = value;
}

bool CTile::GetBasePlaceability()
{
	return mBasePlaceability;
}

int CTile::GetCol()
{
	return mCol;
}

int CTile::GetRow()
{
	return mRow;
}

void CTile::SetCol(int value)
{
	mCol = value;
}

void CTile::SetRow(int value)
{
	mRow = value;
}

double CTile::GetHeuristic()
{
	return mH;
}

void CTile::SetHeuristic(double h)
{
	mH = h;
}

CString CTile::GetNodeId()
{
	return mNodeId;
}

bool CTile::Equal(INode* n)
{
	return (n->GetCol() == mCol && n->GetRow() == mRow);
}

void CTile::SetNeighbors(std::vector<INode*>* pArr)
{
	// Note: assumes ownership of the pointer; previous neighbor list is not deleted.
	mArrNeighbors = pArr;
}

std::vector<INode*>* CTile::GetNeighbors()
{
	return mArrNeighbors;
}