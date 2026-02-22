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
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mOffsetX = 0;
	mOffsetY = 0;
	mRow = 0;
	mCol = 0;
	mRows = 1;
	mCols = 1;
	mCurCol = 2;
	mDrect = 0;
	mWalking = false;
}

/**
 * 加载指定素材。
 * @param fileName 要加载素材的路径。
 */
bool CAvatar::Load(CString strFileName)
{
	CImage::Load(strFileName);
	//计算一帧动画的宽高和偏移量
	mWidth = mImage->GetWidth() / COLS;
	mHeight = mImage->GetHeight() / ROWS;
	mOffsetX = mWidth / 2;
	mOffsetY = mHeight - 8;
	return mIsReady;
}

/**
 * 卸载加载的素材。
 */
void CAvatar::UnLoad()
{
	CImage::UnLoad();
	mWidth = 0;
	mHeight = 0;
	mOffsetX = 0;
	mOffsetY = 0;
}

void CAvatar::StartWalk(CPath* pPath)
{
	if (pPath != NULL)
	{
		vector<INode*> nodes = pPath->GetNodes();
		delete pPath;
		pPath = NULL;
		mCurWalkPath.clear();
		mCurWalkPath = nodes;
		mCurWalkPath.erase(mCurWalkPath.begin());
		Walk();
	}
}

/**
 * 开始行走。
 */
void CAvatar::Walk()
{
	if (mCurWalkPath.size() > 0)
	{
		mWalking = true;
		INode* pNode = *(mCurWalkPath.begin());
		mCurWalkPath.erase(mCurWalkPath.begin());
		CGamePoint p = CMapUtil::GetScreenCoordinate(pNode->GetCol(), pNode->GetRow());
		p.m_fX = p.m_fX - mMapOffSetX;
		p.m_fY = p.m_fY - mMapOffSetY;
		mDrect = GetDirection(p);
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
	mRadian = atan2f(fY, fX);
	float angle = (float)(mRadian * 180 / PI);
	mDistance = sqrtf(fX * fX + fY * fY);
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
	mX += nextSpeed.m_fX;
	mY += nextSpeed.m_fY;
	mDistance -= nextSpeed.m_fInstance;
	if (mDistance <= 0)
	{
		mDistance = 0;
		if (mCurWalkPath.size() > 0)
		{
			Walk();
		}
		else
		{
			mWalking = false;
			mCurCol = 0;
			//AfxMessageBox("结束");
		}
	}
}

float CAvatar::GetNextMoveDistance()
{
	if (mDistance > 0)
	{
		float curDistance;
		if (mDistance < SPEED)
		{
			curDistance = mDistance;
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
		point.m_fX = point.m_fInstance * cosf(mRadian);
		point.m_fY = point.m_fInstance * sinf(mRadian);
	}
	return point;
}

void CAvatar::NextFrameIndex()
{
	if (mWalking)
	{
		++mCurCol; //指向要绘制的帧
	}
	if (mCurCol >= COLS)
	{
		mCurCol = 0;
	}
}

void CAvatar::DrawFrame(Graphics& graphics)
{
	Rect rect(mX, mY, mWidth, mHeight);
	graphics.DrawImage(mImage, rect, mWidth * mCurCol, mHeight * mDrect, mWidth, mHeight, UnitPixel);
}

void CAvatar::DrawNextFrame(Graphics& graphics)
{
	if (mWalking)
	{
		NextFrameIndex();
		GetNextDistance();
		CalculatePosition();
	}
	DrawFrame(graphics);
}

int CAvatar::GetCol()
{
	CPoint point = CMapUtil::GetMapPointByScreen(GetViewX() + mMapOffSetX, GetViewY() + mMapOffSetY);
	return point.x + 1;
}

int CAvatar::GetRow()
{
	CPoint point = CMapUtil::GetMapPointByScreen(GetViewX() + mMapOffSetX, GetViewY() + mMapOffSetY);
	return point.y + 1;
}

float CAvatar::GetViewX()
{
	return mX + mOffsetX;
}

float CAvatar::GetViewY()
{
	return  mY + mOffsetY;
}