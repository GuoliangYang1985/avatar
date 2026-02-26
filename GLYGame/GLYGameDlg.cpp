// GLYGameDlg.cpp : implementation file

#include "stdafx.h"
#include "GLYGame.h"
#include "GLYGameDlg.h"
#include "MapUtil.h"
#include "XmlUtil.h"
#include "Sort.h"
#include "GoItem.h"
#include <fstream>

static bool FileExists(const std::wstring& filename) {
	DWORD attr = GetFileAttributesW(filename.c_str());
	return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

/**
 * CGLYGameDlg dialog
 */
CGLYGameDlg::CGLYGameDlg(CWnd* pParent) : CDialog(CGLYGameDlg::IDD, pParent)
{
	mIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	GdiplusStartup(&mGdiToken, &mGdiplusStartupInput, NULL);
	mBackDC.CreateCompatibleDC(NULL);
}

void CGLYGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGLYGameDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

/**
 * CGLYGameDlg message handlers
 */
BOOL CGLYGameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(mIcon, TRUE);			// Set big icon
	SetIcon(mIcon, FALSE);		// Set small icon
	ShowWindow(SW_MAXIMIZE); // Set window to maximized state.

	CreateScene(_T("resource/map/data/gly.xml"));
	return true;  // return TRUE  unless you set the focus to a control
}

void CGLYGameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (nType != SIZE_MINIMIZED) // No processing needed when minimized.
	{
		CRect rect(0, 0, cx, cy);
		OnWindowSizeChanged(rect);
	}
}

void CGLYGameDlg::OnWindowSizeChanged(CRect rect)
{
	if (mBackDC.GetSafeHdc())
	{
		// Recreate a bitmap matching the window size.
		if (mBackMap.m_hObject != nullptr)
		{
			mBackMap.DeleteObject();
		}
		CClientDC dc(this);
		mBackMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		mBackDC.SelectObject(&mBackMap);
		if (mCols > 0 && mRows > 0)
		{
			Show();
		}
	}
}

/**
 * If you add a minimize button to your dialog, you will need the code below
 * to draw the icon.  For MFC applications using the document/view model,
 * this is automatically done for you by the framework.
 */
void CGLYGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, mIcon);// Draw the icon
	}
	else
	{
		CDialog::OnPaint();
		GamePaint();
	}
}

void CGLYGameDlg::CreateScene(const CString& xmlSource)
{
	mIsReady = false;

	bool success = LoadMapData(xmlSource);
	if (!success)
	{
		return;
	}

	mMapDC.CreateCompatibleDC(NULL);

	// Create map background.
	if (!mBackGround.mIsReady)
	{
		mBackGround.Load(mBackGround.mBackPath);
	}

	// If the grid is not initialized, initialize it.
	if (!mRenderGrid.mIsReady)
	{
		mRenderGrid.CreateGrid(mCols, mRows);
		mRenderGrid.ParseTileXML(mXmlMapConfig);
	}

	if (!mAvatar.mIsReady)
	{
		mAvatar.Load("resource/avatar/male.png");
		if (mAvatar.mIsReady)
		{
			if (mBackGround.mStartCol > 0 && mBackGround.mStartRow > 0)
			{
				CGamePoint p = CMapUtil::GetScreenCoordinate(mBackGround.mStartCol, mBackGround.mStartRow);
				mAvatar.mX = p.mX - mBackGround.mOffsetX - mAvatar.mOffsetX;
				mAvatar.mY = p.mY - mBackGround.mOffsetY - mAvatar.mOffsetY;
			}
		}
	}
	GamePaint();
}

bool CGLYGameDlg::LoadMapData(const CString& xmlSource)
{
	// Initialize COM for this thread (should ideally be done once at program startup)
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		// Log or handle error (e.g., throw exception)
		TRACE(_T("CoInitialize failed\n"));
		return false;
	}

	// Create XML document instance
	hr = mXmlMapConfig.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if (FAILED(hr))
	{
		// MessageBox("Failed to create DOMDocument. Please install MS XML Parser.");
		CoUninitialize();
		return false;
	}

	// Load map configuration file
	VARIANT_BOOL success = mXmlMapConfig->load(_variant_t(xmlSource));
	if (success != VARIANT_TRUE)
	{
		// Handle load failure (e.g., file not found)
		TRACE(_T("Failed to load map XML file\n"));
		mXmlMapConfig.Release();
		CoUninitialize();
		return false;
	}

	// Get root node <map> once
	MSXML2::IXMLDOMElementPtr mapNode = mXmlMapConfig->documentElement;
	if (!mapNode)
	{
		TRACE(_T("Missing root node <map>\n"));
		return false;
	}

	// Get <background> child node once
	MSXML2::IXMLDOMElementPtr bgNode = mapNode->selectSingleNode(_T("background"));
	if (!bgNode)
	{
		TRACE(_T("Missing <background> node\n"));
		return false;
	}

	// Read attributes from <map> node
	mBackGround.mStartCol = CXmlUtil::GetAttributeToInt(mapNode, _T("start_col"));
	mBackGround.mStartRow = CXmlUtil::GetAttributeToInt(mapNode, _T("start_row"));
	mBaseDir = CXmlUtil::GetAttributeToCString(mapNode, _T("dir"));
	if (mBaseDir.IsEmpty())
	{
		mBaseDir = _T("resource/map/assets/");   // Default directory
	}

	// Read attributes from <background> node
	CString strMapPath = CXmlUtil::GetAttributeToCString(bgNode, _T("file"));
	mBackGround.mBackPath = mBaseDir + strMapPath;

	// Read background offsets and grid dimensions
	mBackGround.mOffsetX = CXmlUtil::GetAttributeToFloat(bgNode, _T("x_offset"));
	mBackGround.mOffsetY = CXmlUtil::GetAttributeToFloat(bgNode, _T("y_offset"));
	mBackGround.mCols = CXmlUtil::GetAttributeToInt(bgNode, _T("cols"));
	mBackGround.mRows = CXmlUtil::GetAttributeToInt(bgNode, _T("rows"));

	// Update avatar's map offsets (ensure both X and Y are set after both offsets are read)
	mAvatar.mMapOffSetX = static_cast<int>(mBackGround.mOffsetX);
	mAvatar.mMapOffSetY = static_cast<int>(mBackGround.mOffsetY);

	// Also store grid dimensions in dialog members if needed elsewhere
	mCols = mBackGround.mCols;
	mRows = mBackGround.mRows;

	mAstar.Init(this); // Initialize A* pathfinding with this dialog
	return true;
}

void CGLYGameDlg::GamePaint()
{
	CreateAllItemDefination();
	if (mArrItems.empty())
	{
		CreateAllItem();
		mArrItems = CSort::SortPosition(mArrItems);
	}
	Show();
}

void CGLYGameDlg::Show()
{
	// Get client area rectangle
	CRect clientRect;
	GetClientRect(&clientRect);

	// Get device context for the window
	CDC* pWindowDC = GetDC();
	if (!pWindowDC)
		return;

	// Background image dimensions
	const int backWidth = mBack->GetWidth();
	const int backHeight = mBack->GetHeight();

	// Initialize avatar position if it's at origin (first show)
	if (mAvatar.mX <= 0.0f && mAvatar.mY <= 0.0f)
	{
		mAvatar.mX = backWidth / 2.0f;
		mAvatar.mY = backHeight / 2.0f;
	}

	// Create a compatible bitmap for the map if not already created
	if (mMap.GetSafeHandle() == nullptr)
	{
		mMap.CreateCompatibleBitmap(pWindowDC, backWidth, backHeight);
		mMapDC.SelectObject(&mMap);
	}

	// Draw the map onto the map DC using GDI+
	{
		Gdiplus::Graphics graphics(mMapDC.GetSafeHdc());
		DrawMap(graphics);
		// Graphics destructor automatically releases the HDC
	}

	// Prepare the back buffer DC
	CBrush windowBgBrush(::GetSysColor(COLOR_WINDOW));
	mBackDC.FillRect(&clientRect, &windowBgBrush);

	// Calculate the position to blit the map onto the back buffer
	// Use rounding to convert float to int without truncation warning
	const float viewX = mAvatar.GetViewX();
	const float viewY = mAvatar.GetViewY();
	mMapX = lroundf(clientRect.Width() / 2.0f - viewX);
	mMapY = lroundf(clientRect.Height() / 2.0f - viewY);

	// Blit the map onto the back buffer
	mBackDC.BitBlt(mMapX, mMapY, backWidth, backHeight, &mMapDC, 0, 0, SRCCOPY);

	// Finally, present the back buffer to the window
	pWindowDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &mBackDC, 0, 0, SRCCOPY);

	// Release the window DC
	ReleaseDC(pWindowDC);
}

void CGLYGameDlg::DrawMap(Graphics& graphics)
{
	// Draw the map.
	int bWidth = mBack->GetWidth();
	int bHeight = mBack->GetHeight();
	graphics.DrawImage(mBack, 0, 0, bWidth, bHeight);

	// Draw all elements within the map.
	BOOL bFinded = false;
	for (CItem* item : mArrItems)
	{
		if (!bFinded)
		{
			if (mAvatar.GetCol() < item->mCol + item->mCols && mAvatar.GetRow() < item->mRow + item->mRows)
			{
				bFinded = true;
				mAvatar.DrawNextFrame(graphics);
			}
		}
		item->Draw(graphics, mBackGround.mOffsetX, mBackGround.mOffsetY);
	}
	if (!bFinded)
	{
		mAvatar.DrawNextFrame(graphics);
	}
}

void CGLYGameDlg::CreateAllItemDefination()
{
	if (mItemDefinitions.IsEmpty())
	{
		if (mXmlMapConfig == nullptr)
		{
			return;
		}
		MSXML2::IXMLDOMElementPtr itemDefsNode = (MSXML2::IXMLDOMElementPtr)mXmlMapConfig->selectSingleNode("map/ItemDefinitions");
		MSXML2::IXMLDOMNodeListPtr itemDefList = itemDefsNode->GetchildNodes();
		int nCount = itemDefList->length;
		for (int i = 0; i < nCount; ++i)
		{
			MSXML2::IXMLDOMElementPtr itemDefNode = itemDefList->item[i];
			MSXML2::DOMNodeType nodeType = itemDefNode->nodeType;
			if (nodeType == MSXML2::NODE_ELEMENT)
			{
				CItemDefinition* pItemDef = new CItemDefinition();
				pItemDef->mBaseDirectory = mBaseDir;
				pItemDef->FromXml(itemDefNode);
				CString strFileUrl = pItemDef->mBaseDirectory + pItemDef->mFile;
				pItemDef->Load(strFileUrl);
				mItemDefinitions.SetAt(pItemDef->mDefId, pItemDef);
				pItemDef = NULL;
			}
		}
	}
}

void CGLYGameDlg::DeleteAllItemDefination()
{
	if (!mItemDefinitions.IsEmpty())
	{
		POSITION pos = mItemDefinitions.GetStartPosition();
		while (pos != NULL)
		{
			CString strKey = "";
			CItemDefinition* pItemDef = NULL;
			mItemDefinitions.GetNextAssoc(pos, strKey, pItemDef);
			if (pItemDef != NULL)
			{
				mItemDefinitions.RemoveKey(strKey);
				pItemDef->UnLoad();
				delete pItemDef;
				pItemDef = NULL;
			}
		}
	}
}

void CGLYGameDlg::CreateAllItem()
{
	if (mXmlMapConfig == nullptr)
	{
		return;
	}
	mBack = mBackGround.GetImage();
	MSXML2::IXMLDOMElementPtr itemsNode = (MSXML2::IXMLDOMElementPtr)(mXmlMapConfig->selectSingleNode("map/Items"));
	MSXML2::IXMLDOMNodeListPtr itemList = itemsNode->GetchildNodes();

	long lCount = itemList->length;
	for (int i = 0; i < lCount; ++i)
	{
		MSXML2::IXMLDOMElementPtr itemNode = itemList->item[i];
		MSXML2::DOMNodeType nodeType = itemNode->nodeType;
		if (nodeType == MSXML2::NODE_ELEMENT)
		{
			CString type = CXmlUtil::GetAttributeToCString(itemNode, "type"); // Get the NPC type.
			CItem* pItem = NULL;
			if (type == "GoItem")
			{
				CString goToPath = CXmlUtil::GetAttributeToCString(itemNode, "onStop");
				pItem = new CGoItem(goToPath);
			}
			else
			{
				pItem = new CItem();
			}

			pItem->FromXml(itemNode);
			CItemDefinition* pItemDef;
			mItemDefinitions.Lookup(pItem->mSource, pItemDef);
			pItem->SetItemDefinition(pItemDef);
			mArrItems.push_back(pItem);
			for (int m = pItem->mCol; m < pItem->mCol + pItem->mCols; ++m)
			{
				for (int n = pItem->mRow; n < pItem->mRow + pItem->mRows; ++n)
				{
					CTile* t = GetTile(m, n);
					t->AddItem(pItem);
					pItem->AddTile(t);
				}
			}
			pItem = NULL;
			pItemDef = NULL;
		}
	}
}

/**
 * Get the cell.
 * @param tx The x-coordinate on the screen.
 * @param ty The y-coordinate on the screen.
 * @return The corresponding cell.
 */
CTile* CGLYGameDlg::GetTileFromScreenCoordinate(float tx, float ty) const
{
	CPoint point = CMapUtil::GetMapPointByScreen(tx, ty);
	return mRenderGrid.GetTile(point.x, point.y);
}

CTile* CGLYGameDlg::GetTile(int col, int row) const
{
	return mRenderGrid.GetTile(col, row);
}

LRESULT CGLYGameDlg::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN: // Left mouse button pressed.
		LButtonDown(wParam, CPoint(lParam));
		break;
	case WM_TIMER:
		OnTimer(wParam);
		break;
	default:
		return CDialog::WindowProc(uMsg, wParam, lParam);
	}
	return 0L;
}

/**
 * Left mouse button press handling.
 */
void CGLYGameDlg::LButtonDown(UINT modKeys, CPoint point)
{
	// Compute the start tile from the avatar's current view position
	const float startWorldX = mAvatar.GetViewX() + mBackGround.mOffsetX;
	const float startWorldY = mAvatar.GetViewY() + mBackGround.mOffsetY;
	CTile* pStartNode = GetTileFromScreenCoordinate(startWorldX, startWorldY);
	if (!pStartNode)
	{
		OutputDebugString(_T("Start tile not found (invalid view position).\n"));
		return;
	}

	// Convert the click point to world coordinates
	// Note: mMapX/Y are the viewport origin in world coordinates (assumed integer)
	const LONG adjustedX = point.x + static_cast<LONG>(mBackGround.mOffsetX) - mMapX;
	const LONG adjustedY = point.y + static_cast<LONG>(mBackGround.mOffsetY) - mMapY;
	CTile* pGoalNode = GetTileFromScreenCoordinate(static_cast<float>(adjustedX),
		static_cast<float>(adjustedY));
	if (!pGoalNode)
	{
		OutputDebugString(_T("Clicked tile not found (out of bounds).\n"));
		return;
	}

	// Validate the goal tile is walkable
	if (!pGoalNode->GetWalkable())
	{
		OutputDebugString(_T("The clicked point is not walkable!\n"));
		return;
	}

	// If start and goal are the same, no movement needed
	if (pStartNode->Equal(pGoalNode))
	{
		OutputDebugString(_T("The current position is the target position.\n"));
		return;
	}

	// Perform A* search
	CSearchResults result = mAstar.Search(pStartNode, pGoalNode);
	if (!result.GetIsSuccess())
	{
		OutputDebugString(_T("No walkable path found!\n"));
		return;
	}

	// Start movement along the found path
	StartTimer();
	CPath* pPath = result.GetPath();
	mAvatar.StartWalk(pPath);
}

void CGLYGameDlg::StartTimer()
{
	SetTimer(1, 70, NULL);
}

float CGLYGameDlg::GetNodeTransitionCost(INode* n1, INode* n2)
{
	float cost = 1;
	if (!((CTile*)n1)->GetWalkable() || !((CTile*)n2)->GetWalkable())
	{
		cost = 100000;
	}
	return cost;
}

/**
 * Time event handling.
 */
void CGLYGameDlg::OnTimer(int id)
{
	if (id == 1)
	{
		GamePaint();
		if (!mAvatar.mWalking)
		{
			KillTimer(id);
			for (CItem* item : mArrItems)
			{
				CGoItem* pGoItem = dynamic_cast<CGoItem*>(item);
				if (pGoItem != nullptr)
				{
					CPoint point(mAvatar.GetCol(), mAvatar.GetRow());
					if (pGoItem->HitTest(point))
					{
						CString goTo = pGoItem->mGoTo;
						if (FileExists((LPCTSTR)goTo))
						{
							ReleaseScene();
							CreateScene(goTo);
						}
						break;
					}
				}
			}
		}
	}
}

/**
 * The system calls this to obtain the cursor to display while the user drags
 * the minimized window.
 */
HCURSOR CGLYGameDlg::OnQueryDragIcon()
{
	return (HCURSOR)mIcon;
}

int CGLYGameDlg::GetCols()
{
	return mCols;
}

int CGLYGameDlg::GetRows()
{
	return mRows;
}

INode* CGLYGameDlg::GetNode(int col, int row)
{
	return GetTile(col, row);
}

void CGLYGameDlg::ReleaseScene()
{
	// Release COM resources (XML Document)
	if (mXmlMapConfig != nullptr)
	{
		mXmlMapConfig.Release();
		mXmlMapConfig = nullptr;
	}

	// Clean up item definitions
	DeleteAllItemDefination(); // Ensure this function deallocates memory properly

	// Clean up item instances
	for (CItem* item : mArrItems)
	{
		delete item; // Ensure CItem destructor handles its own resources
	}
	mArrItems.clear(); // Clear the vector after deletion
	mRenderGrid.mIsReady = false;

	// Unload character and background resources
	mAvatar.UnLoad();
	mBackGround.UnLoad();

	// Clean up GDI objects
	if (mMap.m_hObject != nullptr)
	{
		mMap.DeleteObject(); // Delete the GDI object (e.g., bitmap)
	}

	// Delete the device context
	if (mMapDC.m_hDC != nullptr)
	{
		mMapDC.DeleteDC();
	}
}

CGLYGameDlg::~CGLYGameDlg()
{
	ReleaseScene();
	CoUninitialize();
	if (mBackMap.m_hObject != nullptr)
		mBackMap.DeleteObject();

	if (mBackDC.m_hDC != nullptr)
		mBackDC.DeleteDC();
	GdiplusShutdown(mGdiToken);
}