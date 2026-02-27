// Copyright (C) Guoliang Yang.
// Avatar.cpp: implementation of the CAvatar class.

#include <math.h>
#include "stdafx.h"
#include "GLYGame.h"
#include "Avatar.h"
#include "MapUtil.h"

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
	mCurRow = 0;
	mWalking = false;
}


bool CAvatar::Load(const CString& strFileName)
{
	// Load the image
	if (!CImage::Load(strFileName))
		return false;

	// Calculate frame size using floating-point division to avoid truncation
	// and eliminate conversion warnings
	mWidth = static_cast<float>(mImage->GetWidth()) / COLS;
	mHeight = static_cast<float>(mImage->GetHeight()) / ROWS;

	// Compute offsets (center and bottom adjustment)
	mOffsetX = mWidth / 2.0f;
	mOffsetY = mHeight - 8.0f;   // 8 is a fixed pixel offset

	return mIsReady;
}

/**
 * 卸载加载的素材。
 */
void CAvatar::UnLoad()
{
	CImage::UnLoad();
	Init();
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
		p.mX = p.mX - mMapOffSetX;
		p.mY = p.mY - mMapOffSetY;
		mCurRow = (GetDirection(p) - 1) % ROWS;
		if (mCurRow < 0)
		{
			mCurRow += ROWS;
		}
	}
}

/**
 * 根据下一个到到达的点得到角色方向。
 * @param point 要移动到的下一点。
 * @return 角色的方向。
 */
int CAvatar::GetDirection(CGamePoint point)
{
	float fX = point.mX - GetViewX();
	float fY = point.mY - GetViewY();
	mDistance = hypotf(fX, fY);

	// Get the angle in radians.
	mRadian = atan2f(fY, fX);
	int dir = static_cast<int>(round(mRadian / PI_4)) % ROWS;
	if (dir < 0)
		dir += ROWS;
	return dir;
}

/**
 * 计算位置。
 */
void CAvatar::CalculatePosition()
{
	//下一步移动距离
	CSpeed nextSpeed = GetNextDistance();
	mX += nextSpeed.mX;
	mY += nextSpeed.mY;
	mDistance -= nextSpeed.mInstance;
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

float CAvatar::GetNextMoveDistance() const
{
	if (mDistance <= 0.0f)
		return 0.0f;

	// Return the smaller value: remaining distance or speed
	return min(mDistance, static_cast<float>(SPEED));
}

CSpeed CAvatar::GetNextDistance() const
{
	CSpeed point;
	point.mInstance = GetNextMoveDistance();
	if (point.mInstance > 0)
	{
		point.mX = point.mInstance * cosf(mRadian);
		point.mY = point.mInstance * sinf(mRadian);
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

void CAvatar::DrawFrame(Gdiplus::Graphics& graphics)
{
	// Use floating-point rectangle for precise positioning
	Gdiplus::RectF destRect(mX, mY, mWidth, mHeight);

	// Draw the frame from the sprite sheet.
	// Source rectangle: (col * frameWidth, row * frameHeight, frameWidth, frameHeight)
	graphics.DrawImage(mImage,
		destRect,                          // destination rectangle (float)
		mWidth * mCurCol,                  // source x (float)
		mHeight * mCurRow,                  // source y (float)
		mWidth,                             // source width (float)
		mHeight,                            // source height (float)
		Gdiplus::UnitPixel);                // unit is pixels
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

int CAvatar::GetCol() const
{
	CPoint point = CMapUtil::GetMapPointByScreen(GetViewX() + mMapOffSetX, GetViewY() + mMapOffSetY);
	return point.x + 1;
}

int CAvatar::GetRow() const
{
	CPoint point = CMapUtil::GetMapPointByScreen(GetViewX() + mMapOffSetX, GetViewY() + mMapOffSetY);
	return point.y + 1;
}

float CAvatar::GetViewX() const
{
	return mX + mOffsetX;
}

float CAvatar::GetViewY() const
{
	return  mY + mOffsetY;
}