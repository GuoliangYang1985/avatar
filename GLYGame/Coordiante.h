// Coordiante.h: interface for the CCoordiante class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COORDIANTE_H__D7BF3E02_A6DD_4F7A_BA97_37DA35DB1E73__INCLUDED_)
#define AFX_COORDIANTE_H__D7BF3E02_A6DD_4F7A_BA97_37DA35DB1E73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCoordiante  
{
public:
	CCoordiante();
	CCoordiante(float x, float y, float z);
	virtual ~CCoordiante();
public:
	float m_fX;
	float m_fY;
	float m_fZ;
};

#endif // !defined(AFX_COORDIANTE_H__D7BF3E02_A6DD_4F7A_BA97_37DA35DB1E73__INCLUDED_)
