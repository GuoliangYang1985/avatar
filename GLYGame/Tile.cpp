// Tile.cpp
// Implementation of the CTile class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Tile.h"

using namespace std;

// Initialize static member
int CTile::IDS = 0;

CTile::CTile()
	: mArrItems(),
	mArrNeighbors(),
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
}

void CTile::AddItem(CItem* pItem)
{
	mArrItems.push_back(pItem);
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
		for (CItem* pItem : mArrItems)
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
		for (CItem* pItem : mArrItems)
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

bool CTile::GetBaseWalkablity() const  // Note: intentional misspelling
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

bool CTile::GetBasePlaceability() const
{
	return mBasePlaceability;
}

int CTile::GetCol() const
{
	return mCol;
}

int CTile::GetRow() const
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

double CTile::GetHeuristic() const
{
	return mH;
}

void CTile::SetHeuristic(double h)
{
	mH = h;
}

const CString& CTile::GetNodeId() const
{
	return mNodeId;
}

bool CTile::Equal(const INode* other)const
{
	return (other->GetCol() == mCol && other->GetRow() == mRow);
}

void CTile::SetNeighbors(const std::vector<INode*>& neighbors)
{
	mArrNeighbors = neighbors;
}

const std::vector<INode*>& CTile::GetNeighbors() const
{
	return mArrNeighbors;
}