#include "stdafx.h"
#include "GLYGame.h"
#include "Item.h"
#include "MapUtil.h"
#include "Tile.h"


CItem::CItem()
{
    // All members initialized in-class, constructor body can be empty
}

void CItem::AddTile(CTile* t)
{
    mArrTiles.push_back(t);
    mInWorld = true;
}

const std::vector<CTile*>& CItem::GetTiles() const
{
    return mArrTiles;
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

void CItem::FromXml(MSXML2::IXMLDOMElementPtr itemNode)
{
    mSource = CXmlUtil::GetAttributeToCString(itemNode, "source");
    mCol = CXmlUtil::GetAttributeToInt(itemNode, "col");
    mRow = CXmlUtil::GetAttributeToInt(itemNode, "row");
    // mInWorld is not set from XML; default false
}

void CItem::SetItemDefinition(CItemDefinition* pDef)
{
    if (pDef)
    {
        mImage = pDef->GetImage();
        mCols = pDef->mCols;
        mRows = pDef->mRows;
        mOffsetX = pDef->mOffsetX;
        mOffsetY = pDef->mOffsetY;
    }
    mItemDefinition = pDef;
}

CItemDefinition* CItem::GetItemDefinition() const
{
    return mItemDefinition;
}

void CItem::Draw(Graphics& graphics, float backOffsetX, float backOffsetY) const
{
    if (!mImage) return;

    float offsetX = GetX() + static_cast<float>(mOffsetX) - backOffsetX;
    float offsetY = GetY() + static_cast<float>(mOffsetY) - backOffsetY;
    graphics.DrawImage(mImage, offsetX, offsetY,
        static_cast<REAL>(mImage->GetWidth()),
        static_cast<REAL>(mImage->GetHeight()));
}