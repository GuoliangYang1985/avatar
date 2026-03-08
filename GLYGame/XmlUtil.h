// XmlUtil.h: interface for the CXmlUtil class.

#pragma once
#import "msxml4.dll"
namespace ygl
{
	class CXmlUtil
	{
	public:
		CXmlUtil();
		virtual ~CXmlUtil();

	public:
		/**
		 * Retrieves an attribute value as an integer.
		 * @param pElement XML element pointer.
		 * @param bstrAttribute Attribute name.
		 * @return Integer value, or 0 if attribute is missing or conversion fails.
		 */
		static int GetAttributeToInt(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrAttribute);

		/**
		 * Retrieves an attribute value as a boolean.
		 * @param pElement XML element pointer.
		 * @param bstrAttribute Attribute name.
		 * @return Boolean value, or false if attribute is missing or conversion fails.
		 */
		static bool GetAttributeToBool(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrAttribute);

		/**
		 * Retrieves an attribute value as a float, using an XML document and a node path.
		 * @param pXmlDoc XML document pointer.
		 * @param bstrNode Node XPath or name.
		 * @param bstrAttribute Attribute name.
		 * @return Float value, or 0.0f if node/attribute is missing or conversion fails.
		 */
		static float GetAttributeToFloat(MSXML2::IXMLDOMDocumentPtr pXmlDoc, _bstr_t bstrNode, _bstr_t bstrAttribute);

		/**
		 * Retrieves an attribute value as a float, directly from an XML element.
		 * @param pElement XML element pointer.
		 * @param bstrAttribute Attribute name.
		 * @return Float value, or 0.0f if attribute is missing or conversion fails.
		 */
		static float GetAttributeToFloat(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrAttribute);

		/**
		 * Retrieves an attribute value as a CString, using an XML document and a node path.
		 * @param pXmlDoc XML document pointer.
		 * @param bstrNode Node XPath or name.
		 * @param bstrAttribute Attribute name.
		 * @return CString value, or empty string if node/attribute is missing or an error occurs.
		 */
		static CString GetAttributeToCString(MSXML2::IXMLDOMDocumentPtr pXmlDoc, _bstr_t bstrNode, _bstr_t bstrAttribute);

		/**
		 * Retrieves an attribute value as a CString, directly from an XML element.
		 * @param pElement XML element pointer.
		 * @param bstrAttribute Attribute name.
		 * @return CString value, or empty string if attribute is missing or an error occurs.
		 */
		static CString GetAttributeToCString(MSXML2::IXMLDOMElementPtr pElement, _bstr_t bstrAttribute);
	};
}