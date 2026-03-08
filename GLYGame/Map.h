#pragma once
#include <memory>
#include "Avatar.h"
#include "Astar.h"
#include "BackGround.h"
#include "Item.h"
#include "RenderGrid.h"
#import "msxml4.dll"

namespace ygl
{
	class CMap : public ISearchable
	{
	public:
		CMap();
		~CMap();
		/**
		 * Loads map data from an XML source.
		 * @param xmlSource The XML source to load.
		 */
		bool LoadMapData(const CString& xmlSource);

		/**
		 * Create a scene.
		 * @param xmlSource The XML source to load.
		 */
		void CreateScene(const CString& xmlSource);

		/**
		 * Parses all material definition data and creates corresponding objects.
		 */
		void CreateAllItemDefination();

		/**
		 * Deletes all item definitions.
		 */
		void DeleteAllItemDefination();

		/**
		 * Parses all material data and creates corresponding objects.
		 */
		void CreateAllItem();

		/**
		 * Draw the map and all elements within the map.
		 * @param graphics GDI+ graphics object used to perform drawing operations.
		 */
		void DrawMap(Graphics& graphics);

		/**
		 * Gets the tile at the specified grid column and row.
		 * @param col Column index.
		 * @param row Row index.
		 * @return Pointer to the tile, or nullptr if indices are invalid.
		 */
		CTile* GetTile(int col, int row) const;


		/**
		 * Calculates the transition cost between two nodes for pathfinding.
		 * @param n1 Pointer to the first node.
		 * @param n2 Pointer to the second node.
		 * @return The cost value (e.g., distance or movement cost).
		 */
		float GetNodeTransitionCost(INode* n1, INode* n2);

		/**
		 * Gets the number of columns in the grid.
		 * @return Total column count.
		 */
		int GetCols();

		/**
		 * Gets the number of rows in the grid.
		 * @return Total row count.
		 */
		int GetRows();

		/**
		 * Gets the node at the specified grid column and row.
		 * @param col Column index.
		 * @param row Row index.
		 * @return Pointer to the node (likely a CTile or pathfinding node), or nullptr if invalid.
		 */
		INode* GetNode(int col, int row);

		/**
		 * Releases resources associated with the current scene.
		 * Cleans up COM objects, item definitions, items, and graphic resources.
		 */
		void ReleaseScene();
	public:
		// Character.
		CAvatar mAvatar;
		// Background.
		CBackGround mBackGround;
		// Number of columns occupied by the game.
		int mCols;
		// Number of rows occupied by the game.
		int mRows;
		// Grid layer.
		CRenderGrid mRenderGrid;
		// Used for pathfinding.
		CAstar mAstar;
		// Map configuration information.
		MSXML2::IXMLDOMDocumentPtr mXmlMapConfig;
		// Object definitions.
		std::unordered_map<CString, std::unique_ptr<CItemDefinition>> mItemDefinitions;
		// Object instances.
		std::vector<std::unique_ptr<CItem>> mArrItems;
		// Base path for asset storage.
		CString mBaseDir;
		Image* mBack;
	};
}