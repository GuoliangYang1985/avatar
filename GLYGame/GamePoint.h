// GamePoint.h: interface for the CGamePoint class.

#pragma once
namespace ygl
{
	class CGamePoint
	{
	public:
		float mX;
		float mY;
	public:
		CGamePoint();
		CGamePoint(float x, float y);
		virtual ~CGamePoint();
	};
}