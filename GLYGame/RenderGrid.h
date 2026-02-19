// RenderGrid.h: interface for the CRenderGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RENDERGRID_H__58BD4DDC_15CB_489C_9985_E1D4BE762BF9__INCLUDED_)
#define AFX_RENDERGRID_H__58BD4DDC_15CB_489C_9985_E1D4BE762BF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Item.h"
#include "Tile.h"
#endif // _MSC_VER > 1000

class CRenderGrid  
{
public:
	CRenderGrid();
	virtual ~CRenderGrid();
public:
	/**
	 * 创建格子二维数组。
	 */
	void CreateGrid(int cols, int rows);
	
	/**
	 * 得到单元格的行和列对就的单元格。
	 * @param col 当前的列值。
	 * @param row 当前的行值。
	 * @return 指定行列所对应的单元格。
	 */
	CTile *GetTile(int col, int row);
	/**
	 * 从地图中获取数值赋给格子。
	 */
	void ParseTileXML(MSXML2::IXMLDOMDocumentPtr config);
public:
	//格子的列数。
	int m_nCols;
	//格子的行数。
	int m_nRows;
	//格子数组。
	CTile ***m_pArrGrid;
	//初始化完成。
	bool m_bIsReady;
};

#endif // !defined(AFX_RENDERGRID_H__58BD4DDC_15CB_489C_9985_E1D4BE762BF9__INCLUDED_)
