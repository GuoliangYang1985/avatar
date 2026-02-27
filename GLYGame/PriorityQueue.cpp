// PriorityQueue.cpp: implementation of the CPriorityQueue class.

#include "stdafx.h"
#include "GLYGame.h"
#include "PriorityQueue.h"

// Comparison functor for heap ordering (min-heap based on F value)
struct ComparePathPtr
{
    bool operator()(const std::unique_ptr<CPath>& a, const std::unique_ptr<CPath>& b) const
    {
        // We want a min-heap, so return true if a's F is greater than b's F.
        return a->GetF() > b->GetF();
    }
};

bool CPriorityQueue::HasNextItem() const
{
    return !mItems.empty();
}

std::unique_ptr<CPath> CPriorityQueue::GetNextItem()
{
    std::pop_heap(mItems.begin(), mItems.end(), ComparePathPtr());
    auto top = std::move(mItems.back());
    mItems.pop_back();
    return top;
}

void CPriorityQueue::Enqueue(std::unique_ptr<CPath> p)
{
    mItems.push_back(std::move(p));
    std::push_heap(mItems.begin(), mItems.end(), ComparePathPtr());
}