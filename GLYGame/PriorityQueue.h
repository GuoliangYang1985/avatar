// PriorityQueue.h: interface for the CPriorityQueue class.

#pragma once

#include "Path.h"
#include <vector>
#include <memory>   // for std::unique_ptr
#include <algorithm> // for std::push_heap, std::pop_heap

/**
 * Priority queue for CPath objects, ordered by their F value (lowest first).
 * The queue owns the CPath objects and automatically deletes them when destroyed.
 */
class CPriorityQueue
{
public:
    CPriorityQueue();
    // No need for virtual destructor unless used polymorphically
    ~CPriorityQueue();

    // Disable copy (unique_ptr cannot be copied)
    CPriorityQueue(const CPriorityQueue&) = delete;
    CPriorityQueue& operator=(const CPriorityQueue&) = delete;

    // Allow move
    CPriorityQueue(CPriorityQueue&&) = default;
    CPriorityQueue& operator=(CPriorityQueue&&) = default;

    /**
     * Checks if the queue contains any items.
     * @return true if at least one item exists, false otherwise.
     */
    bool HasNextItem() const;

    /**
     * Retrieves and removes the item with the smallest F value.
     * @return Pointer to the CPath object. The caller does NOT take ownership;
     *         the object is removed from the queue and will be destroyed when the queue is cleared.
     * @pre HasNextItem() must be true.
     */
    CPath* GetNextItem();

    /**
     * Inserts a CPath object into the queue. The queue takes ownership.
     * @param p Raw pointer to a CPath object allocated with new.
     */
    void Enqueue(CPath* p);

private:
    // Internal storage: vector of unique_ptr ensures automatic cleanup.
    std::vector<std::unique_ptr<CPath>> mItems;
};
