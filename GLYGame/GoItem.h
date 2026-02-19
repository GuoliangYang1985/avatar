#pragma once
#include "item.h"
class CGoItem :
	public CItem
{
public:
	CGoItem(void);
	~CGoItem(void);
	void FromXml(MSXML2::IXMLDOMElementPtr itemNode);
};

