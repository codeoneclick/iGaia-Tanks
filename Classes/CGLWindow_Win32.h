
#ifndef CGLWindow_Win32_h
#define CGLWindow_Win32_h

#include "HCommon.h"

class CGLWindow_Win32
{
private:

	HWND m_hWnd;
	HDC	m_hDC;

protected:

public:

	CGLWindow_Win32(void);
	~CGLWindow_Win32(void);

	inline HWND Get_HWND(void)
	{
		return m_hWnd;
	};

	inline HDC Get_HDC(void)
	{
		return m_hDC;
	};
};


#endif