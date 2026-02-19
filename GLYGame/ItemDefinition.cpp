// ItemDefinition.cpp: implementation of the CItemDefinition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "ItemDefinition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemDefinition::CItemDefinition()
{
	m_strFile = "";
	m_defId = "";
	m_strBaseDirectory = "";
	m_bWalkable = true;
	m_bOverlap = true;
	m_nCols = 0;
	m_nRows = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
}

CItemDefinition::~CItemDefinition()
{
}

/**
 * 解析xml创建数据。
 * @pItemDefNode 当前ItemDefinition的xml数据
 */
void CItemDefinition::FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode)
{
	m_nCols = CXmlUtil::GetAttributeToInt(pItemDefNode, "cols");
	m_nRows = CXmlUtil::GetAttributeToInt(pItemDefNode, "rows");
	m_nOffsetX = CXmlUtil::GetAttributeToInt(pItemDefNode, "x_offset");
	m_nOffsetY = CXmlUtil::GetAttributeToInt(pItemDefNode, "y_offset");
	m_strFile = CXmlUtil::GetAttributeToCString(pItemDefNode, "file");
	m_defId = CXmlUtil::GetAttributeToCString(pItemDefNode, "id");
	m_bWalkable = CXmlUtil::GetAttributeToBool(pItemDefNode, "walkable");
	m_bOverlap = CXmlUtil::GetAttributeToBool(pItemDefNode, "overlap");
}

bool CItemDefinition::GetWalkable()
{
	return m_bWalkable;
}

void CItemDefinition::SetWalkable(bool value)
{
	m_bWalkable = value;
}

bool CItemDefinition::GetOverlap()
{
	return m_bOverlap;
}

void CItemDefinition::SetOverlap(bool value)
{
	m_bOverlap = value;
}