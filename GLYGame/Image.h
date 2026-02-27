// Image.h: interface for the CImage class.

#pragma once

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
	Image* GetImage() const;
public:
	//初始化是否完成。
	bool mIsReady;

	//角色动画数据。
	Image* mImage;
};
