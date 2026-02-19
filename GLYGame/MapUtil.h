// MapUtil.h: interface for the CMapUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPUTIL_H__06A43440_C386_460A_AFF4_325A72CB1254__INCLUDED_)
#define AFX_MAPUTIL_H__06A43440_C386_460A_AFF4_325A72CB1254__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Isometric.h"
#include "Tile.h"
#endif // _MSC_VER > 1000

//const float TILE_WIDTH_3D = ISO.MapToScreen(0,0,0);
class CMapUtil  
{
public:
	CMapUtil();
	virtual ~CMapUtil();
public:
	/**
	 * 由行列得到屏幕坐标
	 * @param col 该点对应的列
	 * @param row 该点对应的行
	 * @return 屏幕坐标
	 */
	static CGamePoint GetScreenCoordinate(int col, int row);

	/**
	 * 根据屏幕坐标得到地图坐标。
	 * @param screenX 屏幕坐标中的x轴坐标。
	 * @param screenY 屏幕坐标中的y轴坐标。
	 * @return 地图的行列信息。
	 */
	static CPoint GetMapPointByScreen(float screenX, float screenY);
public:
	static CIsometric m_iso;
	static float m_fTileWidth3D;
	static float m_fTileHeight3D;
public:
	enum
	{
		TILE_WIDTH_SCREEN = 64,
		TILE_HEIGHT_SCREEN = 3,
	};
};

#endif // !defined(AFX_MAPUTIL_H__06A43440_C386_460A_AFF4_325A72CB1254__INCLUDED_)
