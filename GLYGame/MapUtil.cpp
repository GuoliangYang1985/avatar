// MapUtil.cpp: implementation of the CMapUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "MapUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CIsometric CMapUtil::m_iso = CIsometric(30);
float CMapUtil::m_fTileWidth3D = m_iso.MapToIsoWorld(64, 0).m_fX;
float CMapUtil::m_fTileHeight3D = m_fTileWidth3D;

CMapUtil::CMapUtil()
{

}

CMapUtil::~CMapUtil()
{

}

/**
 * 由行列得到屏幕坐标
 * @param col 该点对应的列
 * @param row 该点对应的行
 * @return 屏幕坐标
 */
CGamePoint CMapUtil::GetScreenCoordinate(int col, int row)
{
	return m_iso.GetScreenCoordiation(col, row, m_fTileWidth3D);
}

/**
 * 根据屏幕坐标得到地图坐标。
 * @param screenX 屏幕坐标中的x轴坐标。
 * @param screenY 屏幕坐标中的y轴坐标。
 * @return 地图的行列信息。
 */
CPoint CMapUtil::GetMapPointByScreen(float screenX, float screenY)
{
	CPoint point = m_iso.GetMapCoordinate(screenX, screenY, m_fTileWidth3D);
	return point;
}

