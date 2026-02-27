// GLYGameDlg.h : header file

#pragma once
#include <afxtempl.h>
#include <memory>
#include "Avatar.h"
#include "BackGround.h"
#include "Item.h"
#include "ItemDefinition.h"
#include "RenderGrid.h"
#include "Astar.h"

#import "msxml4.dll"

class CGLYGameDlg : public CDialog, public ISearchable
{
public:
	CGLYGameDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CGLYGameDlg();

	/**
	 * Releases resources associated with the current scene.
	 * Cleans up COM objects, item definitions, items, and graphic resources.
	 */
	void ReleaseScene();
	enum { IDD = IDD_GLYGAME_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	/**
	 * Create a scene.
	 * @param xmlSource The XML source to load.
	 */
	void CreateScene(const CString& xmlSource);

	/**
	 * Loads map data from an XML source.
	 * @param xmlSource The XML source to load.
	 */
	bool LoadMapData(const CString& xmlSource);

	/**
	 * Handles window events.
	 * @param uMsg The message identifier.
	 * @param wParam Additional message-specific information.
	 * @param lParam Additional message-specific information.
	 * @return The result of the message processing; depends on the message.
	 */
	LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	 * Handles left mouse button press.
	 * @param modKeys Flags indicating modifier keys (Ctrl, Shift, etc.).
	 * @param point The cursor coordinates (client area).
	 */
	void LButtonDown(UINT modKeys, CPoint point);

	/**
	 * Starts the timer.
	 */
	void StartTimer();

	/**
	 * Handles timer events.
	 * @param id The timer identifier.
	 */
	void OnTimer(int id);

	/**
	 * Refresh the game screen.
	 */
	void GamePaint();

	/**
	 * Show the entire scene.
	 */
	void Show();

	/**
	 * Draw the map and all elements within the map.
	 * @param graphics GDI+ graphics object used to perform drawing operations.
	 */
	void DrawMap(Graphics& graphics);

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
	 * Gets the tile corresponding to the given screen coordinates.
	 * @param tx Screen X coordinate.
	 * @param ty Screen Y coordinate.
	 * @return Pointer to the tile at the specified screen position, or nullptr if out of bounds.
	 */
	CTile* GetTileFromScreenCoordinate(float tx, float ty) const;

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
	 * Handles window size changes.
	 * @param rect The new client rectangle of the window.
	 */
	void OnWindowSizeChanged(CRect rect);
public:
	// Character.
	CAvatar mAvatar;
	// Background.
	CBackGround mBackGround;
	// Initialization complete flag.
	bool mIsReady;
	// Map configuration information.
	MSXML2::IXMLDOMDocumentPtr mXmlMapConfig;
	// Base path for asset storage.
	CString mBaseDir;
	Image* mBack;
	// Object instances.
	std::vector<std::unique_ptr<CItem>> mArrItems;
	// Object definitions.
	std::unordered_map<CString, std::unique_ptr<CItemDefinition>> mItemDefinitions;
	// Grid layer.
	CRenderGrid mRenderGrid;
	// Number of columns occupied by the game.
	int mCols;
	// Number of rows occupied by the game.
	int mRows;
	// Used for pathfinding.
	CAstar mAstar;
	GdiplusStartupInput mGdiplusStartupInput;
	ULONG_PTR mGdiToken;
	// Map and background.
	CDC mBackDC;
	// All content of the map.¡£
	CDC mMapDC;
	CBitmap mBackMap;
	CBitmap mMap;
	float mMapX;
	float mMapY;
protected:
	HICON mIcon;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};