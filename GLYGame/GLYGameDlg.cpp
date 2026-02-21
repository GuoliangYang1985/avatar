// GLYGameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GLYGame.h"
#include "GLYGameDlg.h"
#include "MapUtil.h"
#include "XmlUtil.h"
#include "Sort.h"
#include "GoItem.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
 * CGLYGameDlg dialog
 */
CGLYGameDlg::CGLYGameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGLYGameDlg::IDD, pParent)
{
	mIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsReady = false;
	mArrItems = new vector<CItem*>();

	GdiplusStartup(&mGdiToken, &mGdiplusStartupInput, NULL);
	mMapDC.CreateCompatibleDC(NULL);// 创建兼容DC
	mBackDC.CreateCompatibleDC(NULL);
}

CGLYGameDlg::~CGLYGameDlg()
{
	if (mXmlMapConfig != NULL)
	{
		mXmlMapConfig.Release();
		mXmlMapConfig = NULL;
		CoUninitialize();
	}
	DeleteAllItemDefination();
	if (mArrItems != NULL)
	{
		vector<CItem*>::iterator iter;
		for (iter = mArrItems->begin(); iter != mArrItems->end(); ++iter)
		{
			if (*iter != NULL)
			{
				delete* iter;
				*iter = NULL;
			}
		}
		mArrItems->clear();
		delete mArrItems;
		mArrItems = NULL;
	}
	mAvatar.UnLoad();
	mBackGround.UnLoad();
	mBackDC.DeleteDC();
	mMapDC.DeleteDC();
	GdiplusShutdown(mGdiToken);//卸载gdi+
}

void CGLYGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGLYGameDlg, CDialog)
	//{{AFX_MSG_MAP(CGLYGameDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
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


	//窗口最大化
	ShowWindow(SW_MAXIMIZE);
	//加载地图数据
	LoadMapData();
	return true;  // return TRUE  unless you set the focus to a control
}

void CGLYGameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (nType != SIZE_MINIMIZED) // 最小化时通常无需处理
	{
		CRect rect(0, 0, cx, cy); // 直接用传入的 cx, cy
		OnWindowSizeChanged(rect);
	}
}

void CGLYGameDlg::OnWindowSizeChanged(CRect rect)
{
	if (mBackDC.GetSafeHdc())
	{
		// 重新创建与窗口大小匹配的位图
		CClientDC dc(this);
		mBackMap.DeleteObject();
		mBackMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		mBackDC.SelectObject(&mBackMap);
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

		// Draw the icon
		dc.DrawIcon(x, y, mIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	CreateBackGroud();//创建背景

	//如果网格没有初始化，则初始化。
	if (!mRenderGrid.m_bIsReady)
	{
		mRenderGrid.CreateGrid(mCols, mRows);
		mRenderGrid.ParseTileXML(mXmlMapConfig);
	}

	if (!mAvatar.mIsReady)
	{
		mAvatar.Load("resource/avatar/male.png");
		if (mAvatar.mIsReady)
		{
			CGamePoint p = CMapUtil::GetScreenCoordinate(mBackGround.m_nStartCol, mBackGround.m_nStartRow);
			mAvatar.mX = p.m_fX - mBackGround.m_offsetX - mAvatar.mOffsetX;
			mAvatar.mY = p.m_fY - mBackGround.m_offsetY - mAvatar.mOffsetY;
		}
	}
	GamePaint();
}

/**
 * 刷新游戏画面
 */
void CGLYGameDlg::GamePaint()
{
	CreateAllItemDefination();
	DrawSortedAll();
	RenderAll();
}

void CGLYGameDlg::DrawSortedAll()
{
	if (mArrItems->size() <= 0)
	{
		CreateAllItem();
		SortPosition();
		RenderAll();
	}
}

void CGLYGameDlg::RenderAll()
{
	CRect rect;
	GetClientRect(&rect);// 获取客户端范围
	CDC* hdc = GetDC();// 获取源设备DC

	int bWidth = mBack->GetWidth();
	int bHeight = mBack->GetHeight();

	if (mMap.GetSafeHandle() == NULL)
	{
		mMap.CreateCompatibleBitmap(hdc, bWidth, bHeight);
		mMapDC.SelectObject(&mMap);// 兼容DC选入赚容位图
	}

	Graphics graphics(mMapDC.GetSafeHdc());
	graphics.DrawImage(mBack, 0, 0, bWidth, bHeight);
	graphics.ReleaseHDC(mMapDC.GetSafeHdc());

	BOOL bFinded = false;
	for (CItem* item : *mArrItems)
	{
		if (!bFinded)
		{
			if (mAvatar.GetCol() < item->m_nCol + item->m_nCols && mAvatar.GetRow() < item->m_nRow + item->m_nRows)
			{
				bFinded = true;
				mAvatar.ShowNextFrame(graphics);
			}
		}
		float offsetX = float(item->GetX() + item->m_nOffsetX - mBackGround.m_offsetX); // Offset in the X-axis direction.
		float offsetY = float(item->GetY() + item->m_nOffsetY - mBackGround.m_offsetY); // Offset in the Y-axis direction.
		Image* pImage = item->m_pImage;
		graphics.DrawImage(pImage, offsetX, offsetY, (Gdiplus::REAL)pImage->GetWidth(), (Gdiplus::REAL)pImage->GetHeight());
	}
	if (!bFinded)
	{
		mAvatar.ShowNextFrame(graphics);
	}
	mMapX = (rect.Width() - bWidth) / 2.0f - mAvatar.mX - mBackGround.m_offsetX;
	mMapY = (rect.Height() - bHeight) / 2.0f - mAvatar.mY + 800;

	// Use the window's background color to fill the map background.
	CBrush blackBrush(::GetSysColor(COLOR_WINDOW));
	mBackDC.FillRect(&rect, &blackBrush);
	mBackDC.BitBlt(mMapX, mMapY, bWidth, bHeight, &mMapDC, 0, 0, SRCCOPY);

	hdc->BitBlt(0, 0, rect.Width(), rect.Height(), &mBackDC, 0, 0, SRCCOPY);
	graphics.ReleaseHDC(mBackDC.GetSafeHdc());
}

/**
 * 解析所有素材定义数据并创建与之对应ItemDefination。
 */
void CGLYGameDlg::CreateAllItemDefination()
{
	if (m_itemDefinitions.IsEmpty())
	{
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
				pItemDef->m_strBaseDirectory = mBaseDir;
				pItemDef->FromXml(itemDefNode);
				CString strFileUrl = pItemDef->m_strBaseDirectory + pItemDef->m_strFile;
				pItemDef->Load(strFileUrl);
				m_itemDefinitions.SetAt(pItemDef->m_defId, pItemDef);
				pItemDef = NULL;
			}
		}
	}
}

/**
 * 删除ItemDefination。
 */
void CGLYGameDlg::DeleteAllItemDefination()
{
	if (!m_itemDefinitions.IsEmpty())
	{
		POSITION pos = m_itemDefinitions.GetStartPosition();
		while (pos != NULL)
		{
			CString strKey = "";
			CItemDefinition* pItemDef = NULL;
			m_itemDefinitions.GetNextAssoc(pos, strKey, pItemDef);
			if (pItemDef != NULL)
			{
				m_itemDefinitions.RemoveKey(strKey);
				pItemDef->UnLoad();
				delete pItemDef;
				pItemDef = NULL;
			}
		}
	}
}

/**
 * 解析所有素材数据并创建与之对应的对象。
 */
void CGLYGameDlg::CreateAllItem()
{
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
			CString type = CXmlUtil::GetAttributeToCString(itemNode, "type");// 得到NPC类型。
			CItem* pItem = NULL;
			if (type == "GoItem")
			{
				pItem = new CGoItem();
			}
			else
			{
				pItem = new CItem();
			}

			pItem->FromXml(itemNode);
			CItemDefinition* pItemDef;
			m_itemDefinitions.Lookup(pItem->m_strSource, pItemDef);
			pItem->SetItemDefinition(pItemDef);
			mArrItems->push_back(pItem);
			for (int i = pItem->m_nCol; i < pItem->m_nCol + pItem->m_nCols; ++i)
			{
				for (int j = pItem->m_nRow; j < pItem->m_nRow + pItem->m_nRows; ++j)
				{
					CTile* t = GetTile(i, j);
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
 * 排序
 */
void CGLYGameDlg::SortPosition()
{
	if (mArrItems->size() > 0)
	{
		vector<CItem*>* pArrItems = new vector<CItem*>();
		vector<CItem*>::iterator iter;
		for (iter = mArrItems->begin(); iter != mArrItems->end(); ++iter)
		{
			CItem* nsi = *iter;
			bool added = false;
			vector<CItem*>::iterator iter1;
			for (iter1 = pArrItems->begin(); iter1 != pArrItems->end(); ++iter1)
			{
				CItem* si = *iter1;
				if (nsi->m_nCol < (si->m_nCol + si->m_nCols - 1) && nsi->m_nRow < (si->m_nRow + si->m_nRows - 1))
				{
					pArrItems->insert(iter1, 1, nsi);
					added = true;
					break;
				}
			}
			if (!added)
			{
				pArrItems->push_back(nsi);
			}
		}

		delete mArrItems;
		mArrItems = pArrItems;
		pArrItems = NULL;
	}
}

/**
 * 加载地图数据
 */
void CGLYGameDlg::LoadMapData()
{
	CoInitialize(NULL);
	HRESULT	hResult = mXmlMapConfig.CreateInstance(__uuidof(DOMDocument30));
	if (!SUCCEEDED(hResult))
	{
		//MessageBox("创建DOMDocument对象，请检查是否安装了MS XML Parser运行库！");
	}
	mXmlMapConfig->load("resource/map/gly.xml");
	CString strDir = GetAttribute(mXmlMapConfig, "map", "dir");
	mBaseDir = strDir;
	CString	strMapPath = GetAttribute(mXmlMapConfig, "map/background", "file");
	mBackGround.m_strBackPath = strDir + strMapPath;
	mBackGround.m_offsetX = GetAttributeF(mXmlMapConfig, "map/background", "x_offset");
	mAvatar.mMapOffSetX = (int)mBackGround.m_offsetX;
	mAvatar.mMapOffSetY = (int)mBackGround.m_offsetY;
	mBackGround.m_offsetY = GetAttributeF(mXmlMapConfig, "map/background", "y_offset");
	mCols = mBackGround.m_nCols = (int)GetAttributeF(mXmlMapConfig, "map/background", "cols");
	mRows = mBackGround.m_nRows = (int)GetAttributeF(mXmlMapConfig, "map/background", "rows");
	mAstar.Init(this);
}

/**
 * 得到CString类型的属性值。
 * @param pXmlMapConfig xml配置文件。
 * @bstrtNode 节点名。
 * @bstrtAttribute 属性名。
 * @return CString类型的属性值。
 */
CString CGLYGameDlg::GetAttribute(MSXML2::IXMLDOMDocumentPtr pXmlMapConfig, _bstr_t bstrtNode, _bstr_t bstrtAttribute)
{
	MSXML2::IXMLDOMElementPtr childNode;
	childNode = (MSXML2::IXMLDOMElementPtr)(pXmlMapConfig->selectSingleNode(bstrtNode));
	VARIANT varDir;
	varDir = childNode->getAttribute(bstrtAttribute);
	CString strDir = (char*)(_bstr_t)varDir;
	return strDir;
}

/**
 * 得到float类型的属性值。
 * @param pXmlMapConfig xml配置文件。
 * @bstrtNode 节点名。
 * @bstrtAttribute 属性名。
 * @return float类型的属性值。
 */
float CGLYGameDlg::GetAttributeF(MSXML2::IXMLDOMDocumentPtr pXmlMapConfig, _bstr_t bstrtNode, _bstr_t bstrtAttribute)
{
	return (float)_ttoi(GetAttribute(pXmlMapConfig, bstrtNode, bstrtAttribute));
}

/**
 * 获取单元格。
 * @param tx 屏幕的x轴坐标。
 * @param ty 屏幕的y轴坐标。
 * @return 得到对应的单元格。
 */
CTile* CGLYGameDlg::GetTileFromScreenCoordinate(float tx, float ty)
{
	CPoint point = CMapUtil::GetMapPointByScreen(tx, ty);
	return mRenderGrid.GetTile(point.x, point.y);
}

CTile* CGLYGameDlg::GetTile(int col, int row)
{
	return mRenderGrid.GetTile(col, row);
}

/**
 * 创建背景
 */
void CGLYGameDlg::CreateBackGroud()
{
	if (!mBackGround.mIsReady)
	{
		mBackGround.Load(mBackGround.m_strBackPath);
	}
}

/**
 * 事件处理
 */
LRESULT CGLYGameDlg::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN: //按下鼠标左键
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
 * 	鼠标左键按下处理。
 */
void CGLYGameDlg::LButtonDown(UINT modKeys, CPoint point)
{
	//计算起始点。
	CGamePoint p;
	p.m_fX = mAvatar.GetViewX() + mBackGround.m_offsetX;
	p.m_fY = mAvatar.GetViewY() + mBackGround.m_offsetY;
	CTile* pStartNode = GetTileFromScreenCoordinate(p.m_fX, p.m_fY);

	//计算终点。
	point.x += (long)mBackGround.m_offsetX - mMapX;
	point.y += (long)mBackGround.m_offsetY - mMapY;

	CTile* pGoalNode = GetTileFromScreenCoordinate((float)point.x, (float)point.y);

	if (!pGoalNode->GetWalkable())
	{
		OutputDebugString(_T("点的地方不可以行走!\n"));
		return;
	}

	if (pStartNode->Equal(pGoalNode))
	{
		OutputDebugString(_T("当前位置就是要到达的位置!"));
		return;
	}
	CSearchResults result = mAstar.Search(pStartNode, pGoalNode);
	if (!result.GetIsSuccess())
	{
		OutputDebugString(_T("没有寻到可行走路径!\n"));
		return;
	}
	StartTimer();
	CPath* pPath = result.GetPath();
	mAvatar.StartWalk(pPath);
}

/**
 * 开始计时器
 */
void CGLYGameDlg::StartTimer()
{
	SetTimer(1, 70, NULL);
}

/**
 * 画指定透明度的矩形
 */
void CGLYGameDlg::DrawAlphaRect(CDC* pDC, CRect& r, COLORREF clr, unsigned char alpha)
{
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.FillSolidRect(0, 0, r.Width(), r.Height(), clr);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha;
	bf.AlphaFormat = 0;

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, r.Width(), r.Height());
	CBitmap* pOldBitmap = memdc.SelectObject(&bmp);
	::AlphaBlend(pDC->m_hDC, r.left, r.top, r.Width(), r.Height(), memdc.m_hDC, 0, 0, r.Width(), r.Height(), bf);
	memdc.SelectObject(pOldBitmap);
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
 * 时间处理
 */
void CGLYGameDlg::OnTimer(int id)
{
	if (id == 1)
	{
		GamePaint();
		if (!mAvatar.mWalking)
		{
			RenderAll();
			KillTimer(id);
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