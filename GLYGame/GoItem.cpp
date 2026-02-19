#include "stdafx.h"
#include "GoItem.h"


CGoItem::CGoItem(void)
{
}


CGoItem::~CGoItem(void)
{
}


void CGoItem::FromXml(MSXML2::IXMLDOMElementPtr itemNode)
{
	CItem::FromXml(itemNode);
}
