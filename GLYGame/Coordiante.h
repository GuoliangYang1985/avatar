// Coordiante.h: interface for the CCoordiante class.

#pragma once

namespace ygl
{
	class CCoordiante
	{
	public:
		CCoordiante();
		CCoordiante(float x, float y, float z);
		virtual ~CCoordiante();
	public:
		float mX;
		float mY;
		float mZ;
	};
}

