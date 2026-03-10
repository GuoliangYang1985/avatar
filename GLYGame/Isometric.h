// Isometric.h: interface for the CIsometric class.

#pragma once
#include "GamePoint.h"
#include "Coordiante.h"

namespace ygl
{
	class CIsometric
	{
	public:
		CIsometric(float declination = 30);
		~CIsometric();
	public:
		/**
		 * Convert row and column indices to screen coordinates.
		 * @param col Column index of the point.
		 * @param row  row Row index of the point.
		 * @return Screen coordinates
		 */
		CGamePoint GetScreenCoordiation(int col, int row, float cellLegth);

		/**
		 * Get map coordinates.
		 * @param tx X-coordinate on the screen.
		 * @param ty Y-coordinate on the screen.
		 * @param cellLength cellLength Length of a grid cell.
		 * @return Row and column on the map.
		 */
		CPoint GetMapCoordinate(float tx, float ty, float cellLength);

		/**
		 * Convert 3D coordinate system values to 2D screen coordinate system values.
		 * Note: The 2D coordinate system has no Z-axis.
		 * @param xpp X-coordinate in the 3D coordinate system (in pixels).
		 * @param ypp Y-coordinate in the 3D coordinate system (in pixels).
		 * @param zpp Z-coordinate in the 3D coordinate system (in pixels).
		 * @return Coordinates in the 2D screen coordinate system (in pixels).
		 */
		CGamePoint MapToScreen(float xpp, float ypp, float zpp);

		/**
		 * Convert 2D pixel coordinate system to 3D coordinate system.
		 * Note: In the resulting 3D coordinates, the Y value is set to 0.
		 * @param screenX X-coordinate in the 2D coordinate system.
		 * @param screenY Y-coordinate in the 2D coordinate system.
		 * @return Coordinates in the 3D coordinate system (with Y = 0).
		 */
		CCoordiante MapToIsoWorld(float screenX, float screenY);
	private:
		// Vertical viewing angle Theta.
		float mTheta;
		// sin Theta
		float mSinTheta;
		// cos Theta
		float mCosTheta;
		// Horizontal viewing angle Alpha
		float mAlpha;
		// sin Alpha
		float mSinAlpha;
		// cos Alpha
		float mCosAlpha;
	};
}