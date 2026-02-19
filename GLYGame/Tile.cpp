// Tile.cpp: implementation of the CTile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "Tile.h"
using namespace std;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CTile::IDS= 0;
CTile::CTile()
{
	++IDS;
	m_strNodeId.Format(_T("%d"), IDS);
	m_strNodeType="normal";

	m_pArrItems = new vector<CItem *>();
	m_bBaseWalkability = true;
	m_bBasePlaceability = true;
	m_bWalkable = true;
	m_bEnabled = true;
	m_pArrNeighbors = NULL;
	m_fH = 0;
	m_nCol = 0;
	m_nRow = 0;
}

CTile::~CTile()
{
	if (m_pArrNeighbors != NULL)
	{
		delete m_pArrNeighbors;
		m_pArrNeighbors = NULL;
	}

	if (m_pArrItems != NULL)
	{
		delete m_pArrItems;
		m_pArrItems = NULL;
	}
}

void CTile::AddItem(CItem *pItem)
{
	m_pArrItems->push_back(pItem);
	DeterminePlaceability();
	DetermineWalkability();
}

void CTile::FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode)
{
	 m_bBaseWalkability = CXmlUtil::GetAttributeToBool(pItemDefNode, "walkability");
	 m_bBasePlaceability = CXmlUtil::GetAttributeToBool(pItemDefNode, "placeability");
	 m_bWalkable = m_bBaseWalkability;
}


void CTile::Enable()
{
	m_bEnabled = true;
}

/**
 * basePlaceability控制
 */ 
void CTile::DeterminePlaceability()
{
	bool bAllows = m_bBasePlaceability;
	if (bAllows)
	{
		for (vector<CItem *>::iterator iter=m_pArrItems->begin(); iter != m_pArrItems->end(); ++iter)
		{
			CItem *pItem = (CItem *)*iter;
			if (!pItem->GetItemDefinition()->GetOverlap())
			{
				bAllows = false;
				break;
			}
		}
	}
	m_bBasePlaceability = m_bEnabled && bAllows;
}

/**
 * 是否可行走的判断
 */ 
void CTile::DetermineWalkability()
{
	bool w = m_bBaseWalkability;
	if (w)
	{
		for (vector<CItem *>::iterator iter=m_pArrItems->begin(); iter != m_pArrItems->end(); ++iter)
		{
			CItem *pItem = (CItem *)*iter;
			if (!pItem->GetItemDefinition()->GetWalkable())
			{
				w = false;
				break;
			}
		}
	}
	m_bWalkable = m_bEnabled && w;
}


void CTile::SetBaseWalkability(bool value)
{
	m_bBaseWalkability = value;
}

bool CTile::GetBaseWalkablity()
{
	return m_bBaseWalkability;
}	

bool CTile::GetWalkable()
{
	return m_bWalkable;
}

void CTile::SetBasePlaceability(bool value)
{
	m_bBasePlaceability = value;
}

bool CTile::GetBasePlaceability()
{
	return m_bBasePlaceability;
}

void CTile::Disable()
{
	m_bEnabled = false;
}

int CTile::GetCol()
{
	return m_nCol;
}

int CTile::GetRow()
{
	return m_nRow;
}
void CTile::SetCol(int value)
{
	m_nCol = value;
}
void CTile::SetRow(int value)
{
	m_nRow = value;
}
double CTile::GetHeuristic()
{
	return m_fH;
}

void CTile::SetHeuristic(double h)
{
	m_fH = h;
}

CString CTile::GetNodeId()
{
	return m_strNodeId;
}

bool CTile::Equal(INode *n)
{
	bool isEqual = true;
	if (n->GetCol() != m_nCol || n->GetRow() != m_nRow)
	{
		isEqual = false;
	}
	return isEqual;
}

void CTile::SetNeighbors(vector<INode*> *pArr)
{
	m_pArrNeighbors = pArr;
}

vector<INode*> *CTile::GetNeighbors()
{
	return m_pArrNeighbors;
}