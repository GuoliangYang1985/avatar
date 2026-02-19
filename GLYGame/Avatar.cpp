//////////////////////////////////////////////////////////////////////
// 
// Copyright (C) Guoliang Yang. All rights reserved.
// Avatar.cpp: implementation of the CAvatar class.
//
//////////////////////////////////////////////////////////////////////
#include <math.h>
#include "stdafx.h"
#include "GLYGame.h"
#include "Avatar.h"
#include "MapUtil.h"
using namespace std;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/**
 * 构造函数。
 */
CAvatar::CAvatar()
{
	Init();
}

/**
 * 析构函数。
 */
CAvatar::~CAvatar()
{

}

/**
 * 初始化。
 */
void CAvatar::Init()
{
	m_fX = 0;
	m_fY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
	m_nRow = 0;
	m_nCol = 0;
	m_nRows = 1;
	m_nCols = 1;
	m_nCurCol = 0;
	m_nDrect = 0;
	m_bWalking = false;
}

/**
 * 加载指定素材。
 * @param fileName 要加载素材的路径。
 */
bool CAvatar::Load(CString strFileName)
{
	CImage::Load(strFileName);
	//计算一帧动画的宽高和偏移量
	m_nWidth = m_pImage->GetWidth() / COLS;
	m_nHeight = m_pImage->GetHeight() / ROWS;
	m_nOffsetX = m_nWidth / 2;
	m_nOffsetY = m_nHeight - 8;
	return m_bIsReady;
}

/**
 * 卸载加载的素材。
 */
void CAvatar::UnLoad()
{
	CImage::UnLoad();
	m_nWidth = 0;
	m_nHeight = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
}

void CAvatar::StartWalk(CPath* pPath)
{
	if (pPath != NULL)
	{
		vector<INode*> nodes = pPath->GetNodes();
		delete pPath;
		pPath = NULL;
		m_arrCurWalkPath.clear();
		m_arrCurWalkPath = nodes;
		m_arrCurWalkPath.erase(m_arrCurWalkPath.begin());
		Walk();
	}
}

/**
 * 开始行走。
 */
void CAvatar::Walk()
{
	if (m_arrCurWalkPath.size() > 0)
	{
		m_bWalking = true;
		INode* pNode = *(m_arrCurWalkPath.begin());
		m_arrCurWalkPath.erase(m_arrCurWalkPath.begin());
		CGamePoint p = CMapUtil::GetScreenCoordinate(pNode->GetCol(), pNode->GetRow());
		p.m_fX = p.m_fX - m_nMapOffSetX;
		p.m_fY = p.m_fY - m_nMapOffSetY;
		m_nDrect = GetDirection(p);
	}
}

/**
 * 根据下一个到到达的点得到角色索方向。
 * @param point 要移动到的下一点。
 * @return 角色的方向。
 */
int CAvatar::GetDirection(CGamePoint point)
{
	float fX = point.m_fX - GetViewX();
	float fY = point.m_fY - GetViewY();
	//得到弧度制角度
	m_fRadian = atan2f(fY, fX);
	float angle = (float)(m_fRadian * 180 / PI);
	m_fDistance = sqrtf(fX * fX + fY * fY);
	unsigned int dir = FindAngleIndex(angle);
	if (dir >= ROWS)
		dir = 0;
	return dir;
}

/**
 * 输入角度，根据角度计算方向索引值。
 * @param 要输入的角度。
 * return 得到方向索引值。
 */
int CAvatar::FindAngleIndex(float angle)
{
	angle = ClamDegrees(angle);
	int index = (int)floor(angle / 45 + 0.5) - 1;
	return index;
}

/**
 * 把小于0度大于360度的角度转化为0~360度之间。
 * @param degree 需要转化的角度。
 * @return 转化后的角度在(0~360度之间)。
 */
float CAvatar::ClamDegrees(float degree)
{
	while (degree < 0)
	{
		degree += 360;
	}

	while (degree > 360)
	{
		degree -= 360;
	}
	return degree;
}

/**
 * 计算位置。
 */
void CAvatar::CalculatePosition()
{
	//下一步移动距离
	CSpeed nextSpeed = GetNextDistance();
	m_fX += nextSpeed.m_fX;
	m_fY += nextSpeed.m_fY;
	m_fDistance -= nextSpeed.m_fInstance;
	if (m_fDistance <= 0)
	{
		m_fDistance = 0;
		if (m_arrCurWalkPath.size() > 0)
		{
			Walk();
		}
		else
		{
			m_bWalking = false;
			m_nCurCol = 0;
			//AfxMessageBox("结束");
		}
	}
}

float CAvatar::GetNextMoveDistance()
{
	if (m_fDistance > 0)
	{
		float curDistance;
		if (m_fDistance < SPEED)
		{
			curDistance = m_fDistance;
		}
		else
		{
			curDistance = (float)SPEED;
		}
		return curDistance;
	}
	else
	{
		return 0;
	}
}

CSpeed CAvatar::GetNextDistance()
{
	CSpeed point;
	point.m_fInstance = GetNextMoveDistance();
	if (point.m_fInstance > 0)
	{
		point.m_fX = point.m_fInstance * cosf(m_fRadian);
		point.m_fY = point.m_fInstance * sinf(m_fRadian);
	}
	return point;
}

int CAvatar::GetCol()
{
	CGamePoint p;
	p.m_fX = GetViewX() + m_nMapOffSetX;
	p.m_fY = GetViewY() + m_nMapOffSetY;
	CPoint point = CMapUtil::GetMapPointByScreen(p.m_fX, p.m_fY);
	return point.x + 1;
}

int CAvatar::GetRow()
{
	CGamePoint p;
	p.m_fX = GetViewX() + m_nMapOffSetX;
	p.m_fY = GetViewY() + m_nMapOffSetY;
	CPoint point = CMapUtil::GetMapPointByScreen(p.m_fX, p.m_fY);
	return point.y + 1;
}

float CAvatar::GetViewX()
{
	return m_fX + m_nOffsetX;
}

float CAvatar::GetViewY()
{
	return  m_fY + m_nOffsetY;
}