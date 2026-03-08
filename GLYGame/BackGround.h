////////////////////////////////////////////////////////////////////// 
//
// Copyright (C) Guoliang Yang. All rights reserved.
// BackGround.h: interface for the CBackGround class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Image.h"
namespace ygl
{
	/**
	 * Map background.
	 * Created by: Guoliang Yang.
	 * Creation date: 2011-10-26.
	 */
	class CBackGround : public CImage
	{
	public:
		CBackGround();
		virtual ~CBackGround();

	public:
		// Path to the background image.
		CString mBackPath;
		// Offset along the X axis.
		float mOffsetX;
		// Offset along the Y axis.
		float mOffsetY;
		// Number of columns occupied.
		int mCols;
		// Number of rows occupied.
		int mRows;
		// Starting column for the character.
		int mStartCol;
		// Starting row for the character.
		int mStartRow;
	};
}