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
	void AddTile(CTile* t);
	vector<CTile*>* GetTile();
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
	void SetItemDefinition(CItemDefinition* pValue);
	/**
	 * 得到item的定义。
	 */
	CItemDefinition* GetItemDefinition();

	void Draw(Graphics& graphics, float backOffsetX, float backOffsetY);
public:
	//所在列
	int mCol;
	//所在行
	int mRow;
	//所占列数
	int mCols;
	//所占行数
	int mRows;
	//x方向上的偏移量
	int mOffsetX;
	//y方向上的偏移量
	int mOffsetY;
	//对应ItemDefintion
	CString mSource;
	//图片
	Image* mImage;
	//item定义。
	CItemDefinition* mItemDefinition;
private:
	vector<CTile*>* mArrTiles;
	bool mInWorld;
};

#endif // !defined(AFX_ITEM_H__CC38F86F_7FB7_46C8_91E2_1DDDD92E0E8F__INCLUDED_)