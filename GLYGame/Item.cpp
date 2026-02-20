// Item.cpp: implementation of the CItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "Item.h"
#include "MapUtil.h"
#include "Tile.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItem::CItem()
{
	m_nCol = 0;
	m_nRow = 0;
	m_nCols = 0;
	m_nRows = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
	m_strSource = "";
	m_pImage = NULL;
	m_pItemDefinition = NULL;
	m_pArrTiles = new vector<CTile *>;
	m_bInWorld = false;
}

CItem::~CItem()
{
	m_pImage = NULL;

	if (m_pArrTiles != NULL)
	{
		delete m_pArrTiles;
		m_pArrTiles = NULL;
	}

	if (m_pItemDefinition != NULL)
	{
		//不在此处创建，不在此处释放。
		//delete m_pItemDefinition;
		m_pItemDefinition = NULL;
	}
}

void CItem::AddTile(CTile *t)
{
	m_pArrTiles->push_back(t);
	m_bInWorld = true;
}

float CItem::GetX()
{
	CGamePoint point = CMapUtil::GetScreenCoordinate(m_nCol, m_nRow);
	return point.m_fX;
}

float CItem::GetY()
{
	CGamePoint point = CMapUtil::GetScreenCoordinate(m_nCol, m_nRow);
	return point.m_fY;
}

/**
 * 解析xml创建数据。
 * @param itemNode 当前item的xml数据
 */
void CItem::FromXml(MSXML2::IXMLDOMElementPtr itemNode)
{
	m_strSource = CXmlUtil::GetAttributeToCString(itemNode, "source");
	m_nCol = CXmlUtil::GetAttributeToInt(itemNode, "col");
	m_nRow = CXmlUtil::GetAttributeToInt(itemNode, "row");
	m_bInWorld = false;//CXmlUtil::GetAttributeToBool(itemNode, "isInWorld");
}

/**
 * 设置item的定义。
 */
void CItem::SetItemDefinition(CItemDefinition *pValue)
{
	m_pImage = pValue->mImage;
	m_nCols = pValue->m_nCols;
	m_nRows = pValue->m_nRows;
	m_nOffsetX = pValue->m_nOffsetX;
	m_nOffsetY = pValue->m_nOffsetY;
	m_pItemDefinition = pValue;
	pValue = NULL;
}

/**
 * 得到item的定义。
 */
CItemDefinition * CItem::GetItemDefinition()
{
	return m_pItemDefinition;
}

vector<CTile *> * CItem::GetTile()
{
	return m_pArrTiles;
}