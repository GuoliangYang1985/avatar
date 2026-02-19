// XmlUtil.cpp: implementation of the CXmlUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLYGame.h"
#include "XmlUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlUtil::CXmlUtil()
{

}

CXmlUtil::~CXmlUtil()
{

}

int CXmlUtil::GetAttributeToInt(MSXML2::IXMLDOMElementPtr pItemDefNode, _bstr_t nodeName)
{
	_variant_t var;
	var.ChangeType(VT_INT, &pItemDefNode->getAttribute(nodeName));
	return var.intVal;
}

/**
 * 根据xml得到CString类型的值。
 */
CString CXmlUtil::GetAttributeToCString(MSXML2::IXMLDOMElementPtr pItemDefNode, _bstr_t nodeName)
{
	_variant_t var = pItemDefNode->getAttribute(nodeName);
	CString str="";
	if (var.vt!=VT_EMPTY && var.vt!=VT_NULL)
	{
		str = (char *)(_bstr_t)pItemDefNode->getAttribute(nodeName);
	}
	return str;
}

bool CXmlUtil::GetAttributeToBool(MSXML2::IXMLDOMElementPtr pItemDefNode, _bstr_t nodeName)
{
	_variant_t var;
	var.ChangeType(VT_BOOL, &pItemDefNode->getAttribute(nodeName));
	bool bVar = (var.boolVal==0? false:true);
	return bVar;
}
