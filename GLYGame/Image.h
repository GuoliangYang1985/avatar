// Image.h: interface for the CImage class.

#pragma once

class CImage
{
public:
	CImage();
	virtual ~CImage();

	// Disable copy
	CImage(const CImage&) = delete;
	CImage& operator=(const CImage&) = delete;

	/**
	 * Loads the specified asset.
	 * @param fileName Path to the asset file.
	 * @return true if loaded successfully, false otherwise.
	 */
	bool Load(const CString& fileName);

	/**
	 * Unloads the loaded asset.
	 */
	void Unload();

	/**
	 * Gets the underlying Image pointer.
	 * @return Pointer to the GDI+ Image object (may be null).
	 */
	Image* GetImage() const;

	/**
	 * Checks if the image is loaded and ready.
	 * @return true if ready, false otherwise.
	 */
	bool IsReady() const { return mIsReady; }

private:
	// Initialization flag
	bool mIsReady;

	//角色动画数据。
	Image* mImage;
};
