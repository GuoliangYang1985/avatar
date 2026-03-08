#include "stdafx.h"
#include "GoItem.h"
namespace ygl
{
	CGoItem::CGoItem(CString goTo)
	{
		mGoTo = goTo;
	}

	CGoItem::~CGoItem(void)
	{
	}

	bool CGoItem::HitTest(CPoint point)
	{
		CRect rect(mCol, mRow, mCol + mCols + 1, mRow + mRows + 1);
		return rect.PtInRect(point);
	}
}