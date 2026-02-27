// ItemDefinition.cpp: implementation of the CItemDefinition class.

#include "stdafx.h"
#include "GLYGame.h"
#include "ItemDefinition.h"

CItemDefinition::CItemDefinition()
{
	mFile = "";
	mDefId = "";
	mBaseDirectory = "";
	mWalkable = true;
	mOverlap = true;
	mCols = 0;
	mRows = 0;
	mOffsetX = 0;
	mOffsetY = 0;
}

CItemDefinition::~CItemDefinition()
{
	UnLoad();
}

/**
 * 解析xml创建数据。
 * @pItemDefNode 当前ItemDefinition的xml数据
 */
void CItemDefinition::FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode)
{
	mCols = CXmlUtil::GetAttributeToInt(pItemDefNode, "cols");
	mRows = CXmlUtil::GetAttributeToInt(pItemDefNode, "rows");
	mOffsetX = CXmlUtil::GetAttributeToInt(pItemDefNode, "x_offset");
	mOffsetY = CXmlUtil::GetAttributeToInt(pItemDefNode, "y_offset");
	mFile = CXmlUtil::GetAttributeToCString(pItemDefNode, "file");
	mDefId = CXmlUtil::GetAttributeToCString(pItemDefNode, "id");
	mWalkable = CXmlUtil::GetAttributeToBool(pItemDefNode, "walkable");
	mOverlap = CXmlUtil::GetAttributeToBool(pItemDefNode, "overlap");
}

bool CItemDefinition::GetWalkable() const
{
	return mWalkable;
}

void CItemDefinition::SetWalkable(bool value)
{
	mWalkable = value;
}

bool CItemDefinition::GetOverlap()
{
	return mOverlap;
}

void CItemDefinition::SetOverlap(bool value)
{
	mOverlap = value;
}