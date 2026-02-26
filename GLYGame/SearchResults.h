// SearchResults.h: interface for the CSearchResults class.

#pragma once
#include "Path.h"

class CSearchResults
{
public:
	CSearchResults();
	virtual ~CSearchResults();
public:
	void SetPath(CPath* p);
	CPath* GetPath();
	bool GetIsSuccess();
	void SetIsSuccess(bool val);
public:
	bool mSuccess;
	CPath* mPath;
};
