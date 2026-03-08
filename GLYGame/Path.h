// Path.h: interface for the CPath class.

#pragma once
#include <vector>
#include <memory>
#include "INode.h"

namespace ygl
{
	class CPath
	{
	public:
		CPath();
		~CPath() = default;

		/**
		 * Creates a deep copy of the current path.
		 * @return A new CPath object (caller takes ownership via unique_ptr).
		 */
		std::unique_ptr<CPath> Clone() const;
		/**
		 * Returns the last node in the path.
		 * @pre The path is not empty.
		 */
		INode* GetLastNode() const;
		/**
		 * Calculates the F value (cost + heuristic of last node).
		 * @pre The path is not empty.
		 */
		double GetF() const;
		double GetCost() const { return mCost; }
		void IncrementCost(double num);

		/**
		 * Appends a node to the end of the path.
		 * @param n Node to add.
		 */
		void AddNode(INode* n);

		/**
		 * Replaces the entire node list.
		 * @param nodes New list of nodes (copied).
		 */
		void SetNodes(const std::vector<INode*>& nodes);

		/**
		 * Returns a const reference to the internal node list.
		 */
		const std::vector<INode*>& GetNodes() const { return mNodes; }
	private:
		std::vector<INode*> mNodes;
		double mCost;
	};
}
