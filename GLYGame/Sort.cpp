// Sort.cpp: implementation of the CSort class.
#include "stdafx.h"
#include "Sort.h"

CSort::CSort()
{

}

CSort::~CSort()
{

}

std::vector<std::unique_ptr<CItem>> CSort::SortPosition(std::vector<std::unique_ptr<CItem>> items)
{
	// 提取原始指针向量
	std::vector<CItem*> ptrs;
	ptrs.reserve(items.size());
	for (const auto& ptr : items) {
		ptrs.push_back(ptr.get());
	}

	// 对原始指针进行排序（保持原算法）
	std::vector<CItem*> sortedPtrs;
	sortedPtrs.reserve(items.size());
	for (CItem* nsi : ptrs) {
		bool inserted = false;
		for (auto it = sortedPtrs.begin(); it != sortedPtrs.end(); ++it) {
			CItem* si = *it;
			if (nsi->mCol < (si->mCol + si->mCols - 1) &&
				nsi->mRow < (si->mRow + si->mRows - 1)) {
				sortedPtrs.insert(it, nsi);
				inserted = true;
				break;
			}
		}
		if (!inserted) {
			sortedPtrs.push_back(nsi);
		}
	}

	// 建立指针到索引的映射（快速查找）
	std::unordered_map<CItem*, size_t> ptrToIndex;
	for (size_t i = 0; i < items.size(); ++i) {
		ptrToIndex[items[i].get()] = i;
	}

	// 按排序后的指针顺序移动 unique_ptr
	std::vector<std::unique_ptr<CItem>> result;
	result.reserve(items.size());
	for (CItem* p : sortedPtrs) {
		auto it = ptrToIndex.find(p);
		if (it != ptrToIndex.end()) {
			result.push_back(std::move(items[it->second]));
		}
	}
	return result;
}