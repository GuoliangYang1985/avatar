// Image.cpp: implementation of the CImage class.

#include "stdafx.h"
#include "Image.h"

CImage::CImage() : mImage(nullptr), mIsReady(false)
{
}

CImage::~CImage()
{
	if (mImage != NULL)
	{
		::delete mImage;
		mImage = NULL;
	}
}

bool CImage::Load(const CString& fileName)
{
	//角色行走动画。
	mImage = ::new Image(fileName, false);
	mIsReady = true;
	return true;
}

void CImage::Unload()
{
	if (mImage != NULL)
	{
		::delete mImage;
		mImage = NULL;
	}
	mIsReady = false;
}

Image* CImage::GetImage() const
{
	return mImage;
}
