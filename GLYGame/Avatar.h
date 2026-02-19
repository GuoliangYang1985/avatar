////////////////////////////////////////////////////////////////////// 
//
// Copyright (C) Guoliang Yang. All rights reserved.
// Avatar.h: interface for the CAvatar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVATAR_H__D486AAC9_7611_4190_B1B6_8F6B2C01F659__INCLUDED_)
#define AFX_AVATAR_H__D486AAC9_7611_4190_B1B6_8F6B2C01F659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "GamePoint.h"
#include "Path.h"
#include "Speed.h"
#include "Image.h"
#endif 

//角色的总行数。
const unsigned int ROWS = 8;
//角色的总列数。
const unsigned int COLS = 8;
/**
 * 角色类，实现角色的各种动作。
 * 创建人：杨国梁。
 * 创建时间：2011-10-26。
 */
class CAvatar :public CImage
{
public:
	/**
	 * 构造函数。
	 */
	CAvatar();

	/**
	 * 析构函数。
	 */
	virtual ~CAvatar();
public:
	/**
	 * 初始化。
	 */
	void Init();

	/**
	 * 加载指定素材。
	 * @param strFileName 要加载素材的路径。
	 */
	bool Load(CString strFileName);

	/**
	 * 卸载加载的素材
	 */
	void UnLoad();
	/**
	 * 行走。
	 */
	void Walk();

	/**
	 * 开始移动
	 */
	void StartWalk(CPath* pPath);

	/**
	 * 根据下一个到到达的点得到角色索方向。
	 * @param point 要移动到的下一点。
	 * @return 角色的方向。
	 */
	int GetDirection(CGamePoint point);

	/**
	 * 输入角度，根据角度计算方向索引值。
	 * @param 要输入的角度。
	 * return 得到方向索引值。
	 */
	int FindAngleIndex(float angle);

	/**
	 * 把小于0度大于360度的角度转化为0~360度之间。
	 * @param degree 需要转化的角度。
	 * @return 转化后的角度在(0~360度之间)。
	 */
	float ClamDegrees(float degree);

	/**
	 * 计算位置
	 */
	void CalculatePosition();

	/**
	 * 得到下一步要行走的距离
	 * @return 下一步要行走的距离
	 */
	CSpeed GetNextDistance();

	/**
	 * 得到下一步移动距离
	 */
	float GetNextMoveDistance();
	int GetCol();
	int GetRow();

	/**
	 * 计算视图位置的X坐标。
	 */
	float GetViewX();

	/**
	 * 计算视图位置的Y坐标。
	 */
	float GetViewY();
public:
	//角色的宽度。
	unsigned int m_nWidth;

	//角色的高度。
	unsigned int m_nHeight;

	//角色X轴上的偏移量
	unsigned int m_nOffsetX;

	//角色Y轴上的偏移量
	unsigned int m_nOffsetY;

	//角色所占行数。
	unsigned int m_nCols;

	//角色所占列数。
	unsigned int m_nRows;

	//角色当前方向。
	int m_nDrect;

	//角色当前列数
	int m_nCurCol;

	//弧度制方向。
	float m_fRadian;

	//距离。
	float m_fDistance;

	//绘制位置x。
	float m_fX;

	//绘制位置y。
	float m_fY;

	//地图x偏移量。
	int m_nMapOffSetX;

	int m_nMapOffSetY;

	//当前行走路径。
	vector<INode*> m_arrCurWalkPath;

	//角色是否在行走
	bool m_bWalking;
private:
	//角色所在列数。
	unsigned int m_nCol;

	//角色所在行数。
	unsigned int m_nRow;
public:
	//角色方向
	enum
	{
		RIGHT,		//0			右		
		RIGHT_DOWN, //1			右下		
		DOWN,		//2			下
		LEFT_DOWN,	//3			左下
		LEFT,		//4			左
		LEFT_UP,	//5			左上
		UP,			//6			上
		RIGHT_UP,	//7			右上

		SPEED = 10, //行走单位速度
	};
};
#endif