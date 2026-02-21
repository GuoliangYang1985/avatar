// GLYGameDlg.h : header file
//

#if !defined(AFX_GLYGAMEDLG_H__C2D68685_30D8_4E6D_B7A3_49B9DDEB3446__INCLUDED_)
#define AFX_GLYGAMEDLG_H__C2D68685_30D8_4E6D_B7A3_49B9DDEB3446__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#include "Avatar.h"
#include "BackGround.h"
#include "Item.h"
#include "ItemDefinition.h"
#include "RenderGrid.h"
#include "Astar.h"
#import "msxml4.dll"
using namespace MSXML2;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGLYGameDlg dialog

class CGLYGameDlg : public CDialog, public ISearchable
{
	// Construction
public:
	CGLYGameDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CGLYGameDlg();
	enum { IDD = IDD_GLYGAME_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	//创建背景。
	void CreateBackGroud();
	//事件处理。
	LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//鼠标左键按下处理。
	void LButtonDown(UINT modKeys, CPoint point);
	//开始计时器。
	void StartTimer();
	//时间处理。
	void OnTimer(int id);
	//画指定alpha值的矩形。
	void DrawAlphaRect(CDC* pDC, CRect& r, COLORREF clr, unsigned char alpha);
	//刷新游戏画面。
	void GamePaint();
	/**
	 * 画出所有有序元素。
	 */
	void DrawSortedAll();

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
	 * 解析所有素材定义数据并创建与之对应的对象。
	 */
	void CreateAllItemDefination();
	/**
	 * 删除ItemDefination。
	 */
	void DeleteAllItemDefination();
	/**
	 * 解析所有素材数据并创建与之对应的对象。
	 */
	void CreateAllItem();
	/**
	 * 加载地图数据。
	 */
	void LoadMapData();
	/**
	 * 得到CString类型的属性值。
	 * @param pXmlMapConfig xml配置文件。
	 * @bstrtNode 节点名。
	 * @bstrtAttribute 属性名。
	 * @return CString类型的属性值。
	 */
	CString GetAttribute(MSXML2::IXMLDOMDocumentPtr pXmlMapConfig, _bstr_t bstrtNode, _bstr_t bstrtAttribute);
	/**
	 * 得到float类型的属性值。
	 * @param pXmlMapConfig xml配置文件。
	 * @bstrtNode 节点名。
	 * @bstrtAttribute 属性名。
	 * @return float类型的属性值。
	 */
	float GetAttributeF(MSXML2::IXMLDOMDocumentPtr pXmlMapConfig, _bstr_t bstrtNode, _bstr_t bstrtAttribute);
	/**
	 * 获取单元格。
	 * @param tx 屏幕的x轴坐标。
	 * @param ty 屏幕的y轴坐标。
	 * @return 得到对应的单元格。
	 */
	CTile* GetTileFromScreenCoordinate(float tx, float ty);
	CTile* GetTile(int col, int row);
	float GetNodeTransitionCost(INode* n1, INode* n2);
	/**
	 * 排序。
	 */
	void SortPosition();

	int GetCols();
	int GetRows();
	INode* GetNode(int col, int row);
	/**
	 * 窗口大小发生变化处理。
	 */
	void OnWindowSizeChanged(CRect rect);
public:
	//角色。
	CAvatar mAvatar;
	//背景。
	CBackGround mBackGround;
	//是否初始化完成。
	bool m_bIsReady;
	//地图配置信息。
	MSXML2::IXMLDOMDocumentPtr mXmlMapConfig;
	//素材存放根路径。
	CString mBaseDir;
	Image* mBack;
	//物件实例。
	vector<CItem*>* mArrItems;
	//物件定义。
	CMap<CString, LPCTSTR, CItemDefinition*, CItemDefinition*> m_itemDefinitions;
	//网格层。
	CRenderGrid mRenderGrid;
	//游戏所占的列数。
	int mCols;
	//游戏所占的行数。
	int mRows;
	//用于寻路。
	CAstar mAstar;

	GdiplusStartupInput mGdiplusStartupInput;
	ULONG_PTR mGdiToken;
	//地图和背景。
	CDC mBackDC;
	//地图的所有内容。
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

#endif
