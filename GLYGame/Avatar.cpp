// Copyright (C) Guoliang Yang.
// Avatar.cpp: implementation of the CAvatar class.

#include <math.h>
#include "stdafx.h"
#include "GLYGame.h"
#include "Avatar.h"
#include "MapUtil.h"

using namespace std;

CAvatar::CAvatar()
{
	Init();
}

CAvatar::~CAvatar()
{

}

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
	mColIndex = 2;
	mRowIndex = 0;
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
		mRowIndex = (GetDirection(p) - 1) % ROWS;
		if (mRowIndex < 0)
		{
			mRowIndex += ROWS;
		}
	}
}

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

void CAvatar::CalculatePosition()
{
	// Next step movement distance.
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
			mColIndex = 0;
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
		++mColIndex; // Point to the next frame.
	}
	if (mColIndex >= COLS)
	{
		mColIndex = 0;
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
		mWidth * mColIndex,                  // source x (float)
		mHeight * mRowIndex,                  // source y (float)
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