// ItemDefinition.h: interface for the CItemDefinition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMDEFINITION_H__5C709F27_3F77_4CCB_B6ED_4779064CBB4B__INCLUDED_)
#define AFX_ITEMDEFINITION_H__5C709F27_3F77_4CCB_B6ED_4779064CBB4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "XmlUtil.h"
#include "Image.h"
#endif // _MSC_VER > 1000

class CItemDefinition: public CImage
{
public:
	CItemDefinition();
	virtual ~CItemDefinition();
public:
	/**
	 * 解析xml创建数据。
	 * @pItemDefNode 当前ItemDefinition的xml数据
	 */
	void FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode);

	bool GetOverlap();
	bool GetWalkable();
	void SetOverlap(bool value);

	/**
	 * 设置是否可以行走。
	 */
	void SetWalkable(bool value);
public:
	//id。
	CString m_defId;
	//文件基本路径。
	CString m_strBaseDirectory;
	//名字。
	CString m_strFile;
	//所占的列数。
	int m_nCols;
	//所占的行数。
	int m_nRows;
	//x轴上的偏移量。
	int m_nOffsetX;
	//y轴上的偏移量。
	int m_nOffsetY;
private:
	//是否可行走。
	bool m_bWalkable;
	//是否可以覆盖
	bool m_bOverlap;
};

#endif // !defined(AFX_ITEMDEFINITION_H__5C709F27_3F77_4CCB_B6ED_4779064CBB4B__INCLUDED_)
