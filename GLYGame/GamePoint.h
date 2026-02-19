// GamePoint.h: interface for the CGamePoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEPOINT_H__0FDA35FD_E239_4219_90B5_85BCF83283AC__INCLUDED_)
#define AFX_GAMEPOINT_H__0FDA35FD_E239_4219_90B5_85BCF83283AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGamePoint  
{
public:
	float m_fX;
	float m_fY;
public:
	CGamePoint();
	CGamePoint(float x, float y);
	virtual ~CGamePoint();

};

#endif // !defined(AFX_GAMEPOINT_H__0FDA35FD_E239_4219_90B5_85BCF83283AC__INCLUDED_)
