// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILE_H__B9000307_4C73_4A8A_A73B_22A51321BA11__INCLUDED_)
#define AFX_TILE_H__B9000307_4C73_4A8A_A73B_22A51321BA11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include"INode.h"
#include"Item.h"
#endif // _MSC_VER > 1000
class CTile:public INode
{
public:
	CTile();
	virtual ~CTile();
public:
	void AddItem(CItem *pItem);
	void FromXml(MSXML2::IXMLDOMElementPtr pItemDefNode);
	void DeterminePlaceability();
	void Disable();
	void Enable();
	bool Equal(INode *n);
	bool GetBasePlaceability();
	int GetCol();
	int GetRow();	
	void SetCol(int value);
	void SetRow(int value);
	double GetHeuristic();
	vector<INode*> *GetNeighbors();
	CString GetNodeId();
	bool GetWalkable();
	void SetHeuristic(double h);
	void SetNeighbors(vector<INode*> *pArr);
	void SetBaseWalkability(bool value);
	bool GetBaseWalkablity();
	void SetBasePlaceability(bool value);
private:
	/**
	 * 是否可行走的判断
	 */
	void DetermineWalkability();
public:
	//当前格子的列数。
	int m_nCol;
	//当前格子的行数。
	int m_nRow;
	CString m_strNodeType;
	//ID
	CString m_strNodeId;
	//场景中所有素材的集合。
	vector<CItem*> *m_pArrItems;
private:
	//临近数组
	vector<INode *> *m_pArrNeighbors;
	bool m_bEnabled;
	//当前格子是否可以行走。
	bool m_bBaseWalkability;
	//当前格子是否可以摆置。
	bool m_bBasePlaceability;
	double m_fH;
	//是否是障碍。
	bool m_bWalkable;
public:
	static int IDS;
};

#endif // !defined(AFX_TILE_H__B9000307_4C73_4A8A_A73B_22A51321BA11__INCLUDED_)
