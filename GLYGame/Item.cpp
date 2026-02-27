// Item.cpp: implementation of the CItem class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Item.h"
#include "MapUtil.h"
#include "Tile.h"

CItem::CItem()
{
	mCol = 0;
	mRow = 0;
	mCols = 0;
	mRows = 0;
	mOffsetX = 0;
	mOffsetY = 0;
	mSource = "";
	mImage = NULL;
	mItemDefinition = NULL;
	mArrTiles = new vector<CTile*>;
	mInWorld = false;
}

CItem::~CItem()
{
	mImage = NULL;

	if (mArrTiles != NULL)
	{
		delete mArrTiles;
		mArrTiles = NULL;
	}

	if (mItemDefinition != NULL)
	{
		//不在此处创建，不在此处释放。
		//delete m_pItemDefinition;
		mItemDefinition = NULL;
	}
}

void CItem::AddTile(CTile* t)
{
	mArrTiles->push_back(t);
	mInWorld = true;
}

float CItem::GetX() const
{
	CGamePoint point = CMapUtil::GetScreenCoordinate(mCol, mRow);
	return point.mX;
}

float CItem::GetY() const
{
	CGamePoint point = CMapUtil::GetScreenCoordinate(mCol, mRow);
	return point.mY;
}

/**
 * 解析xml创建数据。
 * @param itemNode 当前item的xml数据
 */
void CItem::FromXml(MSXML2::IXMLDOMElementPtr itemNode)
{
	mSource = CXmlUtil::GetAttributeToCString(itemNode, "source");
	mCol = CXmlUtil::GetAttributeToInt(itemNode, "col");
	mRow = CXmlUtil::GetAttributeToInt(itemNode, "row");
	mInWorld = false;//CXmlUtil::GetAttributeToBool(itemNode, "isInWorld");
}

/**
 * 设置item的定义。
 */
void CItem::SetItemDefinition(CItemDefinition* pValue)
{
	mImage = pValue->mImage;
	mCols = pValue->mCols;
	mRows = pValue->mRows;
	mOffsetX = pValue->mOffsetX;
	mOffsetY = pValue->mOffsetY;
	mItemDefinition = pValue;
	pValue = NULL;
}

/**
 * 得到item的定义。
 */
CItemDefinition* CItem::GetItemDefinition()
{
	return mItemDefinition;
}

vector<CTile*>* CItem::GetTile()
{
	return mArrTiles;
}

void CItem::Draw(Graphics& graphics, float backOffsetX, float backOffsetY)
{
	float offsetX = float(GetX() + mOffsetX - backOffsetX); // Offset in the X-axis direction.
	float offsetY = float(GetY() + mOffsetY - backOffsetY); // Offset in the Y-axis direction.
	graphics.DrawImage(mImage, offsetX, offsetY, (Gdiplus::REAL)mImage->GetWidth(), (Gdiplus::REAL)mImage->GetHeight());
}