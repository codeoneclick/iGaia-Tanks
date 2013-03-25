
#ifndef CGLContext_Win32_h
#define CGLContext_Win32_h

#include "IGLContext.h"

#ifndef __APPLE__

class CGLContext_Win32 : public IGLContext_INTERFACE
{
private:

protected:
 
    EGLDisplay m_eglDisplay;
	EGLConfig m_eglConfig;
	EGLSurface m_eglSurface;
	EGLContext m_eglContext;
	EGLNativeWindowType	m_eglWindow;
    
public:
    
	CGLContext_Win32(const HWND& _hWND, const HDC& _hDC);
    ~CGLContext_Win32(void);

    void Present(void) const;
};

#endif

#endif 