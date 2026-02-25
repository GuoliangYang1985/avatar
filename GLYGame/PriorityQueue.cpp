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

CPriorityQueue::CPriorityQueue()
{
}

CPriorityQueue::~CPriorityQueue()
{
    // unique_ptr will automatically delete all contained CPath objects.
    // No explicit cleanup needed.
}

bool CPriorityQueue::HasNextItem() const
{
    return !mItems.empty();
}

CPath* CPriorityQueue::GetNextItem()
{
    // Move the smallest element to the back of the heap.
    std::pop_heap(mItems.begin(), mItems.end(), ComparePathPtr());
    // Transfer ownership from the back element to a raw pointer,
    // then remove it from the vector.
    CPath* result = mItems.back().release();
    mItems.pop_back();
    return result;
}

void CPriorityQueue::Enqueue(CPath* p)
{
    // Wrap the raw pointer in a unique_ptr and add to vector.
    mItems.push_back(std::unique_ptr<CPath>(p));
    // Re-establish heap property.
    std::push_heap(mItems.begin(), mItems.end(), ComparePathPtr());
}