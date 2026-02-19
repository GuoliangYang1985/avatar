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
	m_bIsReady = false;
	m_pImage = NULL;
}

CImage::~CImage()
{	
	if (m_pImage != NULL)
	{	
		::delete m_pImage;
		m_pImage = NULL;
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
	m_pImage = ::new Image(strFileName, false);
	m_bIsReady = true;
	return m_bIsReady;
}

/**
 * 卸载加载的素材
 */
void CImage::UnLoad()
{
	if (m_pImage != NULL)
	{	
		::delete m_pImage;
		m_pImage = NULL;
	}
	m_bIsReady = false;
}

/**
 * 得到Image的指针
 * @return 返回m_pImage
 */
Image *CImage::GetImage()
{
	return m_pImage;
}
