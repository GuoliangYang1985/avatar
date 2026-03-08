// RenderGrid.h: interface for the CRenderGrid class.
#pragma once

#include "Item.h"
#include "Tile.h"
#include <vector>
#include <memory>
namespace ygl
{
	class CRenderGrid
	{
	public:
		CRenderGrid();
		virtual ~CRenderGrid() = default;

		// Disable copy semantics (unique_ptr members are move-only)
		CRenderGrid(const CRenderGrid&) = delete;
		CRenderGrid& operator=(const CRenderGrid&) = delete;

		// Enable move semantics for efficiency
		CRenderGrid(CRenderGrid&&) = default;
		CRenderGrid& operator=(CRenderGrid&&) = default;

	public:
		/**
		 * Creates a 2D grid of tiles.
		 * @param cols Number of columns.
		 * @param rows Number of rows.
		 */
		void CreateGrid(int cols, int rows);

		/**
		 * Gets the tile at the specified column and row.
		 * @param col The column index.
		 * @param row The row index.
		 * @return Pointer to the tile, or nullptr if indices are out of bounds.
		 */
		CTile* GetTile(int col, int row) const;

		/**
		 * Parses tile data from the XML configuration and assigns values to the grid.
		 * @param config XML document pointer containing tile definitions.
		 */
		void ParseTileXML(MSXML2::IXMLDOMDocumentPtr config);

	public:
		// Number of columns in the grid.
		int mCols = 0;
		// Number of rows in the grid.
		int mRows = 0;
		// 2D array of tiles managed by unique_ptr.
		std::vector<std::vector<std::unique_ptr<CTile>>> mGrid;
		// Flag indicating whether the grid has been initialized.
		bool mIsReady = false;
	};
}