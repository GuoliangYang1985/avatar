// Isometric.h: interface for the CIsometric class.

#pragma once
#include "GamePoint.h"
#include "Coordiante.h"

class CIsometric
{
public:
	CIsometric(float declination = 30);
	virtual ~CIsometric();
public:
	/**
	 * 由行列得到屏幕坐标
	 * @param col 该点对应的列
	 * @param row 该点对应的行
	 * @return 屏幕坐标
	 */
	CGamePoint GetScreenCoordiation(int col, int row, float cellLegth);

	/**
	 * 获取地图坐标。
	 * @param tx 屏幕的x轴上的坐标。
	 * @param ty 屏幕的y轴上的坐标。
	 * @param cellLength 单元格的长度。
	 * @return 地图上的行列
	 */
	CPoint GetMapCoordinate(float tx, float ty, float cellLength);

	/**
	 * 根据3D坐标系的值计算出2D屏幕坐标系的值，
	 * 2D坐标系中没有z轴
	 * @param xpp 3D坐标系中的x坐标，以像素为单位
	 * @param ypp 3D坐标系中的y坐标，以像素为单位
	 * @param zpp 3D坐标系中的z坐标，以像素为单位
	 * @return 2d坐标系的坐标，以像素为单位
	 */
	CGamePoint MapToScreen(float xpp, float ypp, float zpp);

	/**
	 * 2D像素坐标系转换为3D坐标系，3D坐标中y为0
	 * @param screenX 2D坐标系中的x坐标
	 * @param screenY 2D坐标系中的y坐标
	 * @return 3D坐标系的坐标
	 */
	CCoordiante MapToIsoWorld(float screenX, float screenY);
private:
	//θ垂直俯视角
	float mTheta;
	//sinθ
	float mSinTheta;
	//cosθ
	float mCosTheta;
	//α水平视角
	float mAlpha;
	//sinα
	float mSinAlpha;
	//cosα
	float mCosAlpha;
};