// XmlUtil.cpp: implementation of the CXmlUtil class.

#include "stdafx.h"
#include "GLYGame.h"
#include "XmlUtil.h"

static _variant_t GetAttributeValue(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrtAttribute)
{
	if (!pElement)
		return _variant_t();  // VT_EMPTY

	try
	{
		return pElement->getAttribute(bstrtAttribute);
	}
	catch (const _com_error&)
	{
		return _variant_t();  // VT_EMPTY
	}
}

static MSXML2::IXMLDOMElementPtr GetElementFromPath(MSXML2::IXMLDOMDocumentPtr pDoc, _bstr_t bstrtNode)
{
	if (!pDoc)
		return nullptr;

	try
	{
		return pDoc->selectSingleNode(bstrtNode);
	}
	catch (const _com_error&)
	{
		return nullptr;
	}
}

CXmlUtil::CXmlUtil()
{
}

CXmlUtil::~CXmlUtil()
{
}

int CXmlUtil::GetAttributeToInt(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrtAttribute)
{
	_variant_t varValue = GetAttributeValue(pElement, bstrtAttribute);
	if (varValue.vt == VT_EMPTY || varValue.vt == VT_NULL)
		return 0;

	try
	{
		varValue.ChangeType(VT_INT);  // Convert to int type.
		return varValue.intVal;
	}
	catch (const _com_error&)
	{
		return 0;
	}
}

bool CXmlUtil::GetAttributeToBool(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrtAttribute)
{
	_variant_t varValue = GetAttributeValue(pElement, bstrtAttribute);
	if (varValue.vt == VT_EMPTY || varValue.vt == VT_NULL)
		return false;

	try
	{
		varValue.ChangeType(VT_BOOL);  //Convert to bool type.
		return varValue.boolVal != 0;
	}
	catch (const _com_error&)
	{
		return false;
	}
}

float CXmlUtil::GetAttributeToFloat(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrtAttribute)
{
	_variant_t varValue = GetAttributeValue(pElement, bstrtAttribute);
	if (varValue.vt == VT_EMPTY || varValue.vt == VT_NULL)
		return 0.0f;

	try
	{
		varValue.ChangeType(VT_R4);
		return varValue.fltVal;
	}
	catch (const _com_error&)
	{
		return 0.0f;
	}
}


float CXmlUtil::GetAttributeToFloat(MSXML2::IXMLDOMDocumentPtr pXmlMapConfig,
	_bstr_t bstrtNode,
	_bstr_t bstrtAttribute)
{
	MSXML2::IXMLDOMElementPtr pElement = GetElementFromPath(pXmlMapConfig, bstrtNode);
	if (!pElement)
		return 0.0f;

	// Reuse the element - based overload.
	return GetAttributeToFloat(pElement, bstrtAttribute);
}


CString CXmlUtil::GetAttributeToCString(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrtAttribute)
{
	_variant_t varValue = GetAttributeValue(pElement, bstrtAttribute);
	if (varValue.vt == VT_EMPTY || varValue.vt == VT_NULL)
		return CString();

	try
	{
		// Convert to BSTR type, _variant_t will handle it automatically.
		_bstr_t bstrValue(varValue);
		return CString((LPCTSTR)bstrValue);
	}
	catch (const _com_error&)
	{
		return CString();
	}
}

CString CXmlUtil::GetAttributeToCString(MSXML2::IXMLDOMDocumentPtr pXmlMapConfig,
	_bstr_t bstrtNode,
	_bstr_t bstrtAttribute)
{
	MSXML2::IXMLDOMElementPtr pElement = GetElementFromPath(pXmlMapConfig, bstrtNode);
	if (!pElement)
		return CString();

	// Reuse the element - based overload.
	return GetAttributeToCString(pElement, bstrtAttribute);
}
