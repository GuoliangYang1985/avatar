#pragma once

#include "XmlUtil.h"
#include "ItemDefinition.h"
#include <vector>

class CTile;

class CItem
{
public:
    CItem();
    virtual ~CItem() = default;

    // Prohibit copying.
    CItem(const CItem&) = delete;
    CItem& operator=(const CItem&) = delete;

    // Allow movement.
    CItem(CItem&&) = default;
    CItem& operator=(CItem&&) = default;

public:
    /**
     * Adds a tile occupied by this item.
     * @param t Pointer to the tile (not owned by item).
     */
    void AddTile(CTile* t);

    /**
     * Gets the list of tiles occupied by this item.
     * @return Const reference to the vector of tile pointers.
     */
    const std::vector<CTile*>& GetTiles() const;

    /**
     * Gets the screen X coordinate of the item's base tile.
     * @return X coordinate in pixels.
     */
    float GetX() const;

    /**
     * Gets the screen Y coordinate of the item's base tile.
     * @return Y coordinate in pixels.
     */
    float GetY() const;

    /**
     * Parses item data from an XML element.
     * @param itemNode XML element containing item attributes.
     */
    virtual void FromXml(MSXML2::IXMLDOMElementPtr itemNode);

    /**
     * Sets the item definition (template) for this item.
     * @param pDef Pointer to the item definition (not owned by item).
     */
    void SetItemDefinition(CItemDefinition* pDef);

    /**
     * Gets the item definition associated with this item.
     * @return Pointer to the item definition.
     */
    CItemDefinition* GetItemDefinition() const;

    /**
     * Draws the item using GDI+.
     * @param graphics GDI+ graphics object.
     * @param backOffsetX Background X offset for parallax.
     * @param backOffsetY Background Y offset for parallax.
     */
    void Draw(Graphics& graphics, float backOffsetX, float backOffsetY) const;

public:
    // Grid column of the base tile
    int mCol = 0;
    // Grid row of the base tile
    int mRow = 0;
    // Number of columns the item occupies
    int mCols = 0;
    // Number of rows the item occupies
    int mRows = 0;
    // Pixel offset in X direction (relative to tile)
    int mOffsetX = 0;
    // Pixel offset in Y direction (relative to tile)
    int mOffsetY = 0;
    // Source identifier (matches item definition)
    CString mSource;
    // Pointer to the image (owned by item definition, not by item)
    Image* mImage = nullptr;
    // Pointer to the item definition (not owned)
    CItemDefinition* mItemDefinition = nullptr;

private:
    std::vector<CTile*> mArrTiles;   // Tiles occupied by this item
    bool mInWorld = false;            // Whether the item is placed in the world
};