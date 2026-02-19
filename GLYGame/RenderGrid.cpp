// RenderGrid.cpp: implementation of the CRenderGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "RenderGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRenderGrid::CRenderGrid()
{
	int m_nCols = 0;
	int m_nRows = 0;
	m_pArrGrid = NULL;
	m_bIsReady = false;
}

CRenderGrid::~CRenderGrid()
{
	if (m_pArrGrid != NULL)
	{
		for (int i = 0; i < m_nCols; ++i)
		{
			for (int j=0; j < m_nRows; ++j)
			{
				if (m_pArrGrid[i][j] != NULL)
				{
					delete m_pArrGrid[i][j];
					m_pArrGrid[i][j] = NULL;
				}
			}
			if (m_pArrGrid[i] != NULL)
			{
				delete m_pArrGrid[i];
				m_pArrGrid[i] = NULL;
			}
		}
	
		delete m_pArrGrid;
		m_pArrGrid = NULL;
	}
}

/**
 * 创建格子二维数组。
 */
void CRenderGrid::CreateGrid(int cols, int rows)
{
	m_nCols = cols;
	m_nRows = rows;
	m_pArrGrid = new CTile **[cols];
	for (int i = 0; i < cols; ++i)
	{
		m_pArrGrid[i] = new CTile*[rows];
		for (int j=0; j < rows; ++j)
		{
			CTile *t = new CTile();
			t->m_nCol = i;
			t->m_nRow = j;
			m_pArrGrid[i][j] = t;
			t = NULL;
		}
	}
	m_bIsReady = true;
}

/**
 * 得到单元格的行和列对就的单元格。
 * @param col 当前的列值。
 * @param row 当前的行值。
 * @return 指定行列所对应的单元格。
 */
CTile *CRenderGrid::GetTile(int col, int row)
{
	return m_pArrGrid[col][row];
}

/**
 * 从地图中获取数值赋给格子。
 */
void CRenderGrid::ParseTileXML(MSXML2::IXMLDOMDocumentPtr config)
{
	MSXML2::IXMLDOMElementPtr tilesNode = (MSXML2::IXMLDOMElementPtr)config->selectSingleNode("map/Tiles");
	MSXML2::IXMLDOMNodeListPtr tilesList = tilesNode->GetchildNodes();
	int nCount = tilesList->length;
	CString str;
	for (int i=0; i < nCount; ++i)
	{
		MSXML2::IXMLDOMElementPtr tileNode = tilesList->item[i];
		MSXML2::DOMNodeType nodeType = tileNode->nodeType;
		if (nodeType == MSXML2::NODE_ELEMENT)
		{
			int nCol = CXmlUtil::GetAttributeToInt(tileNode, "col");
			int nRow = CXmlUtil::GetAttributeToInt(tileNode, "row");
			CTile *t = GetTile(nCol, nRow);
			t->FromXml(tileNode);
			t = NULL;
		}
	}
}