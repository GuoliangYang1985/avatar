// Item.h: interface for the CItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__CC38F86F_7FB7_46C8_91E2_1DDDD92E0E8F__INCLUDED_)
#define AFX_ITEM_H__CC38F86F_7FB7_46C8_91E2_1DDDD92E0E8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "XmlUtil.h"
#include "ItemDefinition.h"
#include <vector>
using namespace std;
#endif // _MSC_VER > 1000
class CTile;
class CItem  
{
public:
	CItem();
	virtual ~CItem();
public:
	void AddTile(CTile *t);
	vector<CTile *> * GetTile();
	float GetX();
	float GetY();
	/**
	 * 解析xml创建数据。
	 * @param itemNode 当前item的xml数据
	 */
	virtual void FromXml(MSXML2::IXMLDOMElementPtr itemNode);
	/**
	 * 设置item的定义。
	 */
	void SetItemDefinition(CItemDefinition *pValue);
	/**
	 * 得到item的定义。
	 */
	CItemDefinition * GetItemDefinition();
public:
	//所在列
	int m_nCol;
	//所在行
	int m_nRow;
	//所占列数
	int m_nCols;
	//所占行数
	int m_nRows;
	//x方向上的偏移量
	int m_nOffsetX;
	//y方向上的偏移量
	int m_nOffsetY;
	//对应ItemDefintion
	CString m_strSource;
	//图片
	Image *m_pImage;
	//item定义。
	CItemDefinition *m_pItemDefinition;
private:
	vector<CTile *> *m_pArrTiles;
	bool m_bInWorld;
};

#endif // !defined(AFX_ITEM_H__CC38F86F_7FB7_46C8_91E2_1DDDD92E0E8F__INCLUDED_)
