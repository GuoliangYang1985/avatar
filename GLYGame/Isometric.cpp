// Isometric.cpp: implementation of the CIsometric class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Isometric.h"


CIsometric::CIsometric(float declination)
{
	mTheta = declination;
	mAlpha = 45;
	mTheta *= PI / 180;
	mAlpha *= PI / 180;

	mSinTheta = sinf(mTheta);
	mCosTheta = cosf(mTheta);
	mSinAlpha = sinf(mAlpha);
	mCosAlpha = cosf(mAlpha);
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
	int col = static_cast<int>(std::round(cood.mX / cellLength));
	int row = static_cast<int>(std::round(-cood.mZ / cellLength));
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
	float x = xpp * mCosAlpha + zpp * mSinAlpha;
	float zp = zpp * mCosAlpha - xpp * mSinAlpha;
	float y = ypp * mCosTheta - zp * mSinTheta;
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
	float z = screenX * mSinAlpha - screenY * mCosAlpha / mSinTheta;
	float x = (1 / mCosAlpha) * (screenX - z * mSinAlpha);
	return CCoordiante(x, 0, z);
}
