// GLYGameDlg.cpp : implementation file

#include "stdafx.h"
#include "GLYGame.h"
#include "GLYGameDlg.h"
#include "Sort.h"
#include "MapUtil.h"

namespace ygl
{
	/**
	 * CGLYGameDlg dialog
	 */
	CGLYGameDlg::CGLYGameDlg(CWnd* pParent) : CDialog(CGLYGameDlg::IDD, pParent)
		, mIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME))
		, mGdiToken(0)
		, mMapX(0.0f)
		, mMapY(0.0f)
	{
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

		CreateScene(_T("resource/map/data/main.xml"));
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
			if (mMap.mCols > 0 && mMap.mRows > 0)
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
		mMapDC.CreateCompatibleDC(NULL);
		mMap.CreateScene(xmlSource);
		GamePaint();
	}

	void CGLYGameDlg::GamePaint()
	{
		mMap.CreateAllItemDefination();
		if (mMap.mArrItems.empty())
		{
			mMap.CreateAllItem();
			mMap.mArrItems = CSort::SortPosition(std::move(mMap.mArrItems));
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
		const int backWidth = mMap.mBack->GetWidth();
		const int backHeight = mMap.mBack->GetHeight();

		// Initialize avatar position if it's at origin (first show)
		if (mMap.mAvatar.mX <= 0.0f && mMap.mAvatar.mY <= 0.0f)
		{
			mMap.mAvatar.mX = backWidth / 2.0f;
			mMap.mAvatar.mY = backHeight / 2.0f;
		}

		// Create a compatible bitmap for the map if not already created
		if (mBitmap.GetSafeHandle() == nullptr)
		{
			mBitmap.CreateCompatibleBitmap(pWindowDC, backWidth, backHeight);
			mMapDC.SelectObject(&mBitmap);
		}

		// Draw the map onto the map DC using GDI+
		Gdiplus::Graphics graphics(mMapDC.GetSafeHdc());
		mMap.DrawMap(graphics);

		// Prepare the back buffer DC
		CBrush windowBgBrush(::GetSysColor(COLOR_WINDOW));
		mBackDC.FillRect(&clientRect, &windowBgBrush);

		// Calculate the position to blit the map onto the back buffer
		// Use rounding to convert float to int without truncation warning
		mMapX = lroundf(clientRect.Width() / 2.0f - mMap.mAvatar.GetViewX());
		mMapY = lroundf(clientRect.Height() / 2.0f - mMap.mAvatar.GetViewY());

		// Blit the map onto the back buffer
		mBackDC.BitBlt(mMapX, mMapY, backWidth, backHeight, &mMapDC, 0, 0, SRCCOPY);

		// Finally, present the back buffer to the window
		pWindowDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &mBackDC, 0, 0, SRCCOPY);

		// Release the window DC
		ReleaseDC(pWindowDC);
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
		return mMap.mRenderGrid.GetTile(point.x, point.y);
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
		const float startWorldX = mMap.mAvatar.GetViewX() + mMap.mBackGround.mOffsetX;
		const float startWorldY = mMap.mAvatar.GetViewY() + mMap.mBackGround.mOffsetY;
		CTile* pStartNode = GetTileFromScreenCoordinate(startWorldX, startWorldY);
		if (!pStartNode)
		{
			OutputDebugString(_T("Start tile not found (invalid view position).\n"));
			return;
		}

		// Convert the click point to world coordinates
		// Note: mMapX/Y are the viewport origin in world coordinates (assumed integer)
		const LONG adjustedX = point.x + static_cast<LONG>(mMap.mBackGround.mOffsetX) - mMapX;
		const LONG adjustedY = point.y + static_cast<LONG>(mMap.mBackGround.mOffsetY) - mMapY;
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
		CSearchResults result = mMap.mAstar.Search(pStartNode, pGoalNode);
		if (!result.GetIsSuccess())
		{
			OutputDebugString(_T("No walkable path found!\n"));
			return;
		}

		// Start movement along the found path
		StartTimer();
		CPath* pPath = result.GetPath();
		mMap.mAvatar.StartWalk(pPath);
	}

	void CGLYGameDlg::StartTimer()
	{
		SetTimer(1, 70, NULL);
	}

	/**
	 * Time event handling.
	 */
	void CGLYGameDlg::OnTimer(int id)
	{
		if (id == 1)
		{
			GamePaint();
			if (!mMap.mAvatar.mWalking)
			{
				KillTimer(id);
				CString gotoPath = mMap.CheckGoto();
				if (!gotoPath.IsEmpty())
				{
					ReleaseScene();
					CreateScene(gotoPath);
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

	void CGLYGameDlg::ReleaseScene()
	{
		mMap.ReleaseScene();

		// Clean up GDI objects
		if (mBitmap.m_hObject != nullptr)
		{
			mBitmap.DeleteObject(); // Delete the GDI object (e.g., bitmap)
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
}