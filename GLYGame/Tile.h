// Tile.h
// Declaration of the CTile class, representing a tile in the game grid.
#pragma once

#include "INode.h"
#include "Item.h"
#include <vector>

// Forward declarations
class CItem;

class CTile : public INode
{
public:
	CTile();
	virtual ~CTile();

	// Item management
	void AddItem(CItem* pItem);

	// Initialization from XML
	void FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode);

	// Tile state
	void Enable();
	void Disable();
	void DeterminePlaceability();

	// INode interface implementation
	virtual bool Equal(const INode* other)const override;
	virtual int GetCol()const override;
	virtual int GetRow()const override;
	virtual void SetCol(int value) override;
	virtual void SetRow(int value) override;
	virtual double GetHeuristic()const override;
	virtual void SetHeuristic(double h) override;
	virtual const CString& GetNodeId() const override;
	virtual const std::vector<INode*>& GetNeighbors() const override;
	virtual void SetNeighbors(const std::vector<INode*>& neighbors) override;
	virtual bool GetWalkable();

	// Base properties accessors
	bool GetBasePlaceability() const;
	void SetBasePlaceability(bool value);
	bool GetBaseWalkablity() const;
	void SetBaseWalkability(bool value);

	// Public member variables (consider making private with accessors in future)
	// Column index of the tile
	int mCol;
	// Row index of the tile
	int mRow;
	// Type of the node
	CString mNodeType;
	// Unique identifier
	CString mNodeId;
	// Collection of items on this tile
	vector<CItem*>* mArrItems;
	// Static counter for generating unique IDs
	static int IDS;

private:
	// Internal methods
	/**
	 * Recalculates walkability based on items and base flag
	 */
	void DetermineWalkability();

	// Private members
	// Neighboring nodes for pathfinding
	std::vector<INode*> mArrNeighbors;
	// Whether the tile is enabled
	bool mEnabled;
	// Base walkability flag
	bool mBaseWalkability;
	// Base placeability flag
	bool mBasePlaceability;
	// Heuristic value for A* search
	double mH;
	// Actual walkability after considering items
	bool mWalkable;
};