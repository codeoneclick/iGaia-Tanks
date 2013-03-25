
#ifndef CGLWindow_Win32_h
#define CGLWindow_Win32_h

#include "HCommon.h"

class CGLWindow_Win32
{
private:

	EGLDisplay	m_eglDisplay;
	EGLConfig	m_eglConfig;
	EGLSurface	m_eglSurface;
	EGLContext	m_eglContext;
	EGLNativeWindowType	m_eglWindow;

protected:

public:

	CGLWindow_Win32(void);
	~CGLWindow_Win32(void);

	void Process(void);
};


#endif