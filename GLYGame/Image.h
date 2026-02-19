// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__7E030E84_2983_4D6E_BC03_B69CC2729F7F__INCLUDED_)
#define AFX_IMAGE_H__7E030E84_2983_4D6E_BC03_B69CC2729F7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImage  
{
public:
	CImage();
	virtual ~CImage();
public:
	/**
	 * 加载指定素材。
	 * @param strFileName 要加载素材的路径。
	 */
	bool Load(CString strFileName);
	
	/**
	 * 卸载加载的素材
	 */
	void UnLoad();

	/**
	 * 得到Image的指针
	 * @return 返回m_pImage
	 */
	Image * GetImage();
public:
	//初始化是否完成。
	bool m_bIsReady;

	//角色动画数据。
	Image *m_pImage;
};

#endif // !defined(AFX_IMAGE_H__7E030E84_2983_4D6E_BC03_B69CC2729F7F__INCLUDED_)
