#include "stdafx.h"
#include "RenderGrid.h"

CRenderGrid::CRenderGrid()
	: mCols(0), mRows(0), mIsReady(false)
{
}

void CRenderGrid::CreateGrid(int cols, int rows)
{
	mGrid.clear();
	mGrid.resize(cols);

	for (int i = 0; i < cols; ++i)
	{
		mGrid[i].resize(rows);
		for (int j = 0; j < rows; ++j)
		{
			auto tile = std::make_unique<CTile>();
			tile->m_nCol = i;
			tile->m_nRow = j;
			mGrid[i][j] = std::move(tile);
		}
	}

	mCols = cols;
	mRows = rows;
	mIsReady = true;
}

CTile* CRenderGrid::GetTile(int col, int row) const
{
	if (col < 0 || col >= static_cast<int>(mGrid.size()) ||
		row < 0 || row >= static_cast<int>(mGrid[col].size()))
		return nullptr;

	return mGrid[col][row].get();
}

void CRenderGrid::ParseTileXML(MSXML2::IXMLDOMDocumentPtr config)
{
	MSXML2::IXMLDOMElementPtr tilesNode =
		static_cast<MSXML2::IXMLDOMElementPtr>(config->selectSingleNode("map/Tiles"));
	if (!tilesNode)
		return;

	MSXML2::IXMLDOMNodeListPtr tilesList = tilesNode->GetchildNodes();
	int nCount = tilesList->length;

	for (int i = 0; i < nCount; ++i)
	{
		MSXML2::IXMLDOMElementPtr tileNode = tilesList->item[i];
		if (tileNode->nodeType == MSXML2::NODE_ELEMENT)
		{
			int nCol = CXmlUtil::GetAttributeToInt(tileNode, "col");
			int nRow = CXmlUtil::GetAttributeToInt(tileNode, "row");
			CTile* t = GetTile(nCol, nRow);
			if (t)
			{
				t->FromXml(tileNode);
			}
		}
	}
}