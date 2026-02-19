////////////////////////////////////////////////////////////////////// 
//
// Copyright (C) Guoliang Yang. All rights reserved.
// BackGround.h: interface for the CBackGround class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKGROUND_H__2BD13712_8734_4859_8F53_15CFDCE09E59__INCLUDED_)
#define AFX_BACKGROUND_H__2BD13712_8734_4859_8F53_15CFDCE09E59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Image.h"
#endif // _MSC_VER > 1000

/**
 * 地图背景。
 * 创建人：杨国梁。
 * 创建时间：2011-10-26。
 */
class CBackGround:public CImage
{
public:
	CBackGround();
	virtual ~CBackGround();
public:
	//背景路径
	CString m_strBackPath;
	//在x轴上的偏移量
	float m_offsetX;
	//在y轴上的偏移量
	float m_offsetY;
	//所占的列数。
	int m_nCols; 
	//所占的行数。
	int m_nRows;
	//人物初始位置col。
	int m_nStartCol;
	//人物初始位置row。
	int m_nStartRow;
};

#endif // !defined(AFX_BACKGROUND_H__2BD13712_8734_4859_8F53_15CFDCE09E59__INCLUDED_)
