// Copyright (C) Guoliang Yang
// Avatar.h: interface for the CAvatar class.

#pragma once
#include "GamePoint.h"
#include "Path.h"
#include "Speed.h"
#include "Image.h" 

/**
 * Character class, implementing various character actions.
 * Created by: Guoliang Yang.
 * Creation date: 2011-10-26.
 */
class CAvatar :public CImage
{
public:
	/**
	 * Constructor
	 */
	CAvatar();

	/**
	 * Destructor.
	 */
	virtual ~CAvatar();
public:
	/**
	 * Initialize
	 */
	void Init();

	/**
	 * Loads the specified avatar image.
	 * @param fileName Path to the image file.
	 * @return true if loaded successfully, false otherwise.
	 */
	bool Load(const CString& strFileName);

	/**
	 * Unload loaded assets.
	 */
	void UnLoad();

	/**
	 * Avatar walking process.
	 */
	void Walk();

	/**
	 * Start walking.
	 */
	void StartWalk(CPath* pPath);

	/**
	 * Determines the direction and distance to a target point.
	 * Updates mRadian and mDistance, and returns the direction index.
	 * 0: Right, 1: Down-Right, 2: Down, 3: Down-Left, 4: Left, 5: Up-Left, 6: Up, 7: Up-Right
	 * @param point The target point in world coordinates.
	 * @return Direction index (0-7) as defined in FindDirectionIndex.
	 */
	int GetDirection(CGamePoint point);

	/**
	 * Calculate position.
	 */
	void CalculatePosition();

	/**
	 * Get the distance for the next step.
	 * @return The distance for the next step.
	 */
	CSpeed GetNextDistance() const;

	/**
	 * Get the next step movement distance.
	 */
	float GetNextMoveDistance() const;

	/**
	 * Calculate the next frame index.
	 */
	void NextFrameIndex();

	/**
	 * Draw the current frame.
	 * @param graphics GDI+ graphics object used to perform drawing operations.
	 */
	void DrawFrame(Graphics& graphics);

	/**
	 * Draw the next frame.
	 * @param graphics GDI+ graphics object used to perform drawing operations.
	 */
	void DrawNextFrame(Graphics& graphics);

	int GetCol() const;
	int GetRow() const;

	/**
	 * Calculate the X-coordinate of the view position.
	 */
	float GetViewX() const;

	/**
	 * Calculate the Y-coordinate of the view position.
	 */
	float GetViewY() const;
public:
	// Avatar's width.
	float mWidth;

	// Avatar's height.
	float mHeight;

	// Avatar's offset on the X-axis.
	float mOffsetX;

	// Avatar's offset on the Y-axis.
	float mOffsetY;

	// Total number of cols occupied by the Avatar.
	unsigned int mCols;

	// Total number of rows occupied by the Avatar.
	unsigned int mRows;

	// Avatar's current row index.
	int mRowIndex;

	// Avatar's current col index.
	int mColIndex;

	// Distance¡£
	float mDistance;

	// X-coordinate of the Avatar image.
	float mX;

	// Y-coordinate of the Avatar image.
	float mY;

	// Map X offset.
	int mMapOffSetX;

	// Map Y offset.
	int mMapOffSetY;

	// Current walking path.
	vector<INode*> mCurWalkPath;

	// Is the avatar walking?
	bool mWalking;
public:
	// Walking speed unit.
	const unsigned int SPEED = 10;
	// Total number of rows for the Avatar.
	const unsigned int ROWS = 8;
	// Total number of cols for the Avatar.
	const unsigned int COLS = 8;
private:
	// Direction value in radians.
	float mRadian;

	// Current column number of the Avatar.
	unsigned int mCol;

	// Current row number of the Avatar.
	unsigned int mRow;
};