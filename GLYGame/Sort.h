// Sort.h: interface for the CSort class.

#include"Item.h"

class CSort
{
public:
	CSort();
	virtual ~CSort();
public:
	/**
	 * Sort the list of items according to a specific spatial order.
	 * @param items The list of items to be sorted.
	 * @return A new list after sorting.
	 */
	static std::vector<CItem*> SortPosition(const std::vector<CItem*>& items);
};

