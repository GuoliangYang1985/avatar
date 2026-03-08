// GLYGame.h : main header file for the GLYGAME application

#include "resource.h"
namespace ygl
{
	class CGLYGameApp : public CWinApp
	{
	public:
		CGLYGameApp();
	public:
		virtual BOOL InitInstance();
		DECLARE_MESSAGE_MAP()
	};
}