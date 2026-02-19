// Isometric.cpp: implementation of the CIsometric class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "Isometric.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIsometric::CIsometric(float declination)
{
	m_fTheta = declination;
	m_fAlpha = 45;
	m_fTheta *= PI / 180;
	m_fAlpha *= PI / 180;

	m_fSinTheta = sinf(m_fTheta);
	m_fCosTheta = cosf(m_fTheta);
	m_fSinAlpha = sinf(m_fAlpha);
	m_fCosAlpha = cosf(m_fAlpha);
}

CIsometric::~CIsometric()
{

}

/**
 * 由行列得到屏幕坐标
 * @param col 该点对应的列
 * @param row 该点对应的行
 * @return 屏幕坐标
 */
CGamePoint CIsometric::GetScreenCoordiation(int col, int row, float cellLength)
{
	float iso_x = col * cellLength;
	float iso_z = -row * cellLength;
	return MapToScreen(iso_x, 0, iso_z);
}

/**
 * 获取地图坐标。
 * @param tx 屏幕的x轴上的坐标。
 * @param ty 屏幕的y轴上的坐标。
 * @param cellLength 单元格的长度。
 * @return 地图上的行列
 */
CPoint CIsometric::GetMapCoordinate(float tx, float ty, float cellLength)
{
	CCoordiante cood = MapToIsoWorld(tx, ty);
	int col = (int)(cood.m_fX / cellLength);
	int row = (int)(-cood.m_fZ / cellLength);
	if (col >= 0 && row >= 0)
	{
		return CPoint(col, row);
	}
	else
	{
		return NULL;
	}
}
/**
 * 根据3D坐标系的值计算出2D屏幕坐标系的值，
 * 2D坐标系中没有z轴
 * @param xpp 3D坐标系中的x坐标，以像素为单位
 * @param ypp 3D坐标系中的y坐标，以像素为单位
 * @param zpp 3D坐标系中的z坐标，以像素为单位
 * @return 2d坐标系的坐标，以像素为单位
 */
CGamePoint CIsometric::MapToScreen(float xpp, float ypp, float zpp)
{
	float x = xpp * m_fCosAlpha + zpp * m_fSinAlpha;
	float zp = zpp * m_fCosAlpha - xpp * m_fSinAlpha;
	float y = ypp * m_fCosTheta - zp * m_fSinTheta;
	return CGamePoint(x, y);
}

/**
 * 2D像素坐标系转换为3D坐标系，3D坐标中y为0
 * @param screenX 2D坐标系中的x坐标
 * @param screenY 2D坐标系中的y坐标
 * @return 3D坐标系的坐标
 */
CCoordiante CIsometric::MapToIsoWorld(float screenX, float screenY)
{
	float z = screenX * m_fSinAlpha - screenY * m_fCosAlpha / m_fSinTheta;
	float x = (1 / m_fCosAlpha) * (screenX - z * m_fSinAlpha);
	return CCoordiante(x, 0, z);
}
