// Image.cpp: implementation of the CImage class.

#include "stdafx.h"
#include "Image.h"

CImage::CImage() : mImage(nullptr), mIsReady(false)
{
}

CImage::~CImage()
{

}

bool CImage::Load(const CString& fileName)
{
	// Unload any previously loaded image
	Unload();

	// Load the GDI+ image
	Image* rawImage = new Image(fileName, FALSE);  // FALSE = don't use embedded color management
	if (rawImage->GetLastStatus() != Ok)
	{
		delete rawImage;
		mIsReady = false;
		return false;
	}

	mImage.reset(rawImage);
	mIsReady = true;
	return true;
}

void CImage::Unload()
{
	mImage.reset();  // Deletes the managed Image
	mIsReady = false;
}

Image* CImage::GetImage() const
{
	return mImage.get();
}
