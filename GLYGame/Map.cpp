#include <fstream>
#include "stdafx.h"
#include "Map.h"
#include "MapUtil.h"
#include "GoItem.h"

namespace ygl
{
	static bool FileExists(const std::wstring& filename) {
		DWORD attr = GetFileAttributesW(filename.c_str());
		return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
	}

	CMap::CMap() : mBaseDir(_T(""))
		, mXmlMapConfig(nullptr)
		, mBack(nullptr)
		, mCols(0)
		, mRows(0)
	{

	}
	bool CMap::LoadMapData(const CString& xmlSource)
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

	void CMap::CreateScene(const CString& xmlSource)
	{
		bool success = LoadMapData(xmlSource);
		if (!success)
		{
			return;
		}

		// Create map background.
		if (!mBackGround.IsReady())
		{
			mBackGround.Load(mBackGround.mBackPath);
		}

		// If the grid is not initialized, initialize it.
		if (!mRenderGrid.mIsReady)
		{
			mRenderGrid.CreateGrid(mCols, mRows);
			mRenderGrid.ParseTileXML(mXmlMapConfig);
		}

		if (!mAvatar.IsReady())
		{
			mAvatar.Load("resource/avatar/male.png");
			if (mAvatar.IsReady())
			{
				if (mBackGround.mStartCol > 0 && mBackGround.mStartRow > 0)
				{
					CGamePoint p = CMapUtil::GetScreenCoordinate(mBackGround.mStartCol, mBackGround.mStartRow);
					mAvatar.mX = p.mX - mBackGround.mOffsetX - mAvatar.mOffsetX;
					mAvatar.mY = p.mY - mBackGround.mOffsetY - mAvatar.mOffsetY;
				}
			}
		}
	}

	void CMap::CreateAllItemDefination()
	{
		if (!mItemDefinitions.empty() || !mXmlMapConfig)
			return;
		MSXML2::IXMLDOMElementPtr itemDefsNode = (MSXML2::IXMLDOMElementPtr)mXmlMapConfig->selectSingleNode("map/ItemDefinitions");
		if (!itemDefsNode)
			return;
		MSXML2::IXMLDOMNodeListPtr itemDefList = itemDefsNode->GetchildNodes();
		int nCount = itemDefList->length;
		for (int i = 0; i < nCount; ++i)
		{
			MSXML2::IXMLDOMElementPtr itemDefNode = itemDefList->item[i];
			MSXML2::DOMNodeType nodeType = itemDefNode->nodeType;
			if (nodeType == MSXML2::NODE_ELEMENT)
			{
				auto pItemDef = std::make_unique<CItemDefinition>();
				pItemDef->mBaseDirectory = mBaseDir;
				pItemDef->FromXml(itemDefNode);
				CString strFileUrl = pItemDef->mBaseDirectory + pItemDef->mFile;
				if (pItemDef->Load(strFileUrl))
				{
					mItemDefinitions.emplace(pItemDef->mDefId, std::move(pItemDef));
				}
			}
		}
	}

	void CMap::DeleteAllItemDefination()
	{
		mItemDefinitions.clear();
	}

	void CMap::CreateAllItem()
	{
		if (mXmlMapConfig == nullptr)
			return;

		mBack = mBackGround.GetImage();// Get background image.

		// Locate the <Items> node.
		MSXML2::IXMLDOMElementPtr itemsNode = mXmlMapConfig->selectSingleNode("map/Items");
		if (itemsNode == nullptr)
			return;

		MSXML2::IXMLDOMNodeListPtr itemList = itemsNode->GetchildNodes();
		long count = itemList->length;

		for (long i = 0; i < count; ++i)
		{
			MSXML2::IXMLDOMElementPtr itemNode = itemList->item[i];
			if (itemNode->nodeType != MSXML2::NODE_ELEMENT)
				continue;

			// Triggered upon completion of walking.
			CString goToPath = CXmlUtil::GetAttributeToCString(itemNode, _T("onStop"));
			bool find = false;
			if (goToPath.IsEmpty())
			{
				find = false;
			}
			else
			{
				if (FileExists((LPCTSTR)goToPath))
				{
					find = true;
				}
				else if (FileExists((LPCTSTR)(_T("resource/map/") + goToPath)))
				{
					find = true;
					goToPath = "resource/map/" + goToPath;
				}
			}
			std::unique_ptr<CItem> pItem;
			if (find)
			{
				pItem = std::make_unique<CGoItem>(goToPath);
			}
			else
			{
				pItem = std::make_unique<CItem>();
			}

			pItem->FromXml(itemNode); // Populate item attributes from XML.
			auto it = mItemDefinitions.find(pItem->mSource); // Find the corresponding item definition.
			if (it != mItemDefinitions.end())
			{
				pItem->SetItemDefinition(it->second.get()); // Pass in raw pointer.
			}
			else
			{
				// Definition missing, log error and skip this item.
				TRACE(_T("Warning: Item definition '%s' not found\n"), (LPCTSTR)pItem->mSource);
				continue;
			}

			// Add item to the global list.
			CItem* rawItem = pItem.get();
			mArrItems.push_back(std::move(pItem));

			// Update the grid cells occupied by the item.
			int startCol = rawItem->mCol;
			int startRow = rawItem->mRow;
			int endCol = startCol + rawItem->mCols;
			int endRow = startRow + rawItem->mRows;
			for (int col = startCol; col < endCol; ++col)
			{
				for (int row = startRow; row < endRow; ++row)
				{
					CTile* tile = (CTile*)GetNode(col, row);
					if (tile)
					{
						tile->AddItem(rawItem);
						rawItem->AddTile(tile);
					}
					else
					{
						TRACE(_T("Warning: Tile (%d, %d) out of bounds for item\n"), col, row);
					}
				}
			}
		}
	}

	void CMap::DrawMap(Graphics& graphics)
	{
		// Draw the map.
		int bWidth = mBack->GetWidth();
		int bHeight = mBack->GetHeight();
		graphics.DrawImage(mBack, 0, 0, bWidth, bHeight);

		// Draw all elements within the map.
		BOOL bFinded = false;
		for (const auto& item : mArrItems)
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

	float CMap::GetNodeTransitionCost(INode* n1, INode* n2)
	{
		float cost = 1;
		if (!((CTile*)n1)->GetWalkable() || !((CTile*)n2)->GetWalkable())
		{
			cost = 100000;
		}
		return cost;
	}

	int CMap::GetCols()
	{
		return mCols;
	}

	int CMap::GetRows()
	{
		return mRows;
	}

	INode* CMap::GetNode(int col, int row)
	{
		return mRenderGrid.GetTile(col, row);
	}

	CString CMap::CheckGoto()
	{
		for (const auto& itemPtr : mArrItems)
		{
			if (CGoItem* pGoItem = dynamic_cast<CGoItem*>(itemPtr.get()))
			{
				CPoint point(mAvatar.GetCol(), mAvatar.GetRow());
				if (pGoItem->HitTest(point))
				{
					CString goTo = pGoItem->mGoTo;
					if (FileExists((LPCTSTR)goTo))
					{
						return goTo;
					}
					break;
				}
			}
		}
		return _T("");
	}

	void CMap::ReleaseScene()
	{
		// Release COM resources (XML Document)
		if (mXmlMapConfig != nullptr)
		{
			mXmlMapConfig.Release();
		}

		mArrItems.clear(); // Clear the vector after deletion
		mRenderGrid.mIsReady = false;

		// Unload character and background resources
		mAvatar.Unload();
		mBackGround.Unload();
		DeleteAllItemDefination(); // Clean up item definitions
	}

	CMap::~CMap()
	{
		ReleaseScene();
	}
}