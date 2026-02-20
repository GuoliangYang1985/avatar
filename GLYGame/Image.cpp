// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Image.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage()
{
	mIsReady = false;
	mImage = NULL;
}

CImage::~CImage()
{	
	if (mImage != NULL)
	{	
		::delete mImage;
		mImage = NULL;
	}
}

/**
 * 加载指定素材。
 * @param strFileName 要加载素材的路径。
 */
bool CImage::Load(CString strFileName)
{
	//角色行走动画。
	int len=strFileName.GetLength()+1;
	wchar_t *pwText = new wchar_t[len];
	mImage = ::new Image(strFileName, false);
	mIsReady = true;
	return mIsReady;
}

/**
 * 卸载加载的素材
 */
void CImage::UnLoad()
{
	if (mImage != NULL)
	{	
		::delete mImage;
		mImage = NULL;
	}
	mIsReady = false;
}

/**
 * 得到Image的指针
 * @return 返回m_pImage
 */
Image *CImage::GetImage()
{
	return mImage;
}
