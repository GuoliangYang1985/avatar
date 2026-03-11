// ItemDefinition.h: interface for the CItemDefinition class.

#pragma once
#include "XmlUtil.h"
#include "Image.h"

namespace ygl
{
	class CItemDefinition : public CImage
	{
	public:
		CItemDefinition();
		~CItemDefinition();
	public:
		/**
		 * Parse XML to create data.
		 * @pItemDefNode pItemDefNode XML data for the current ItemDefinition.
		 */
		void FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode);

		bool GetOverlap();
		bool GetWalkable() const;
		void SetOverlap(bool value);

		/**
		 * Set whether it is walkable.
		 * @param value Whether it is walkable.
		 */
		void SetWalkable(bool value);
	public:
		// id¡£
		CString mDefId;
		// Base path of the file.
		CString mBaseDirectory;
		// File name.
		CString mFile;
		// Number of columns occupied.
		int mCols;
		// Number of rows occupied.
		int mRows;
		// Offset on the X-axis.
		int mOffsetX;
		// Offset on the Y-axis.
		int mOffsetY;
	private:
		// Is it walkable.
		bool mWalkable;
		// Whether it can be overlapped.
		bool mOverlap;
	};
}