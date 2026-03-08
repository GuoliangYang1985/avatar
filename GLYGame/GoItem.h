#pragma once
#include "item.h"
namespace ygl
{
	class CGoItem :public CItem
	{
	public:
		CString mGoTo;
	public:
		CGoItem(CString goTo);
		~CGoItem(void);
		/**
		 * Checks whether a given point (in client coordinates) falls inside the item.
		 * @param point The point to test, typically from a mouse message.
		 * @return true if the point is within the item's interactive area.
		 */
		bool HitTest(CPoint point);
	};
}