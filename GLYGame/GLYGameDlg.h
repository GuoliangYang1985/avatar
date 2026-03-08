// GLYGameDlg.h : header file

#pragma once
#include <afxtempl.h>
#include "Map.h"

namespace ygl
{
	class CGLYGameDlg : public CDialog
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
		 * Gets the tile corresponding to the given screen coordinates.
		 * @param tx Screen X coordinate.
		 * @param ty Screen Y coordinate.
		 * @return Pointer to the tile at the specified screen position, or nullptr if out of bounds.
		 */
		CTile* GetTileFromScreenCoordinate(float tx, float ty) const;


		/**
		 * Handles window size changes.
		 * @param rect The new client rectangle of the window.
		 */
		void OnWindowSizeChanged(CRect rect);
	public:
		CMap mMap;
		GdiplusStartupInput mGdiplusStartupInput;
		ULONG_PTR mGdiToken;
		// Map and background.
		CDC mBackDC;
		// All content of the map.¡£
		CDC mMapDC;
		CBitmap mBackMap;
		CBitmap mBitmap;
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
}