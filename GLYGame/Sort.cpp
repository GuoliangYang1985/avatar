// Sort.cpp: implementation of the CSort class.

#include "stdafx.h"
#include "Sort.h"

CSort::CSort()
{

}

CSort::~CSort()
{

}

std::vector<CItem*> CSort::SortPosition(const std::vector<CItem*>& items) {
	std::vector<CItem*> result;
	result.reserve(items.size());  // Pre-allocate space to improve efficiency.

	for (CItem* nsi : items) {
		bool inserted = false;
		// Find the insertion position in the sorted result.
		for (auto it = result.begin(); it != result.end(); ++it) {
			CItem* si = *it;
			if (nsi->mCol < (si->mCol + si->mCols - 1) &&
				nsi->mRow < (si->mRow + si->mRows - 1)) {
				result.insert(it, nsi);
				inserted = true;
				break;
			}
		}
		if (!inserted) {
			result.push_back(nsi);
		}
	}
	return result;
}