// ItemDefinition.h: interface for the CItemDefinition class.

#pragma once
#include "XmlUtil.h"
#include "Image.h"

class CItemDefinition : public CImage
{
public:
	CItemDefinition();
	~CItemDefinition();
public:
	/**
	 * 解析xml创建数据。
	 * @pItemDefNode 当前ItemDefinition的xml数据
	 */
	void FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode);

	bool GetOverlap();
	bool GetWalkable() const;
	void SetOverlap(bool value);

	/**
	 * 设置是否可以行走。
	 */
	void SetWalkable(bool value);
public:
	//id。
	CString mDefId;
	//文件基本路径。
	CString mBaseDirectory;
	//名字。
	CString mFile;
	//所占的列数。
	int mCols;
	//所占的行数。
	int mRows;
	//x轴上的偏移量。
	int mOffsetX;
	//y轴上的偏移量。
	int mOffsetY;
private:
	//是否可行走。
	bool mWalkable;
	//是否可以覆盖
	bool mOverlap;
};
