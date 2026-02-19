// XmlUtil.h: interface for the CXmlUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLUTIL_H__03065EA1_A561_4B2E_B073_6ACDE397D620__INCLUDED_)
#define AFX_XMLUTIL_H__03065EA1_A561_4B2E_B073_6ACDE397D620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#import "msxml4.dll"
using namespace MSXML2;
#endif // _MSC_VER > 1000

class CXmlUtil  
{
public:
	CXmlUtil();
	virtual ~CXmlUtil();
public:
	static int GetAttributeToInt(MSXML2::IXMLDOMElementPtr pItemDefNode, _bstr_t nodeName);
	/**
	 * 根据xml得到CString类型的值。
	 */
	static CString GetAttributeToCString(MSXML2::IXMLDOMElementPtr pItemDefNode, _bstr_t nodeName);
	static bool GetAttributeToBool(MSXML2::IXMLDOMElementPtr pItemDefNode, _bstr_t nodeName);
};

#endif // !defined(AFX_XMLUTIL_H__03065EA1_A561_4B2E_B073_6ACDE397D620__INCLUDED_)
