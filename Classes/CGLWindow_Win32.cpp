
#include "CGLWindow_Win32.h"
#include "CCommon.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_SYSCOMMAND:
		{
			switch (wParam)
			{

			}
			break;
		}
	case WM_KEYDOWN:

		break;

	case WM_KEYUP:

		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 1;

	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

CGLWindow_Win32::CGLWindow_Win32(void)
{
	EGLDisplay	eglDisplay	= 0;
	EGLConfig	eglConfig	= 0;
	EGLSurface	eglSurface	= 0;
	EGLContext	eglContext	= 0;
	EGLNativeWindowType	eglWindow	= 0;

	HWND hWnd = 0;
	HDC	hDC	= 0;

	WNDCLASS windowClass;                                    
	DWORD windowExtStyle =  WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;                        
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;                    
	RECT windowRectangle;                                
	windowRectangle.left = 0;                      
	windowRectangle.right = Get_ScreenWidth();                
	windowRectangle.top = 0;                        
	windowRectangle.bottom = Get_ScreenHeight();                      

	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  
	windowClass.lpfnWndProc = (WNDPROC)WndProc;          
	windowClass.cbClsExtra = 0;                                                                    
	windowClass.cbWndExtra = 0;                                                            
	windowClass.hInstance = GetModuleHandle(NULL);                                            
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);                  
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);                  
	windowClass.hbrBackground = NULL;                                                                
	windowClass.lpszMenuName = NULL;                                                
	windowClass.lpszClassName = L"iGaia-CartoonPanzers";                                            

	if (!RegisterClass(&windowClass))                                                                      
	{
		MessageBox(NULL,L"Failed To Register The Window Class.", L"iGaia-CartoonPanzers" ,MB_OK | MB_ICONEXCLAMATION);
		return;                                                                                
	}

	AdjustWindowRectEx(&windowRectangle, windowStyle, false , windowExtStyle);
	if (!(hWnd = CreateWindowEx(windowExtStyle,                                                  
		L"iGaia-CartoonPanzers",                                              
		L"iGaia-CartoonPanzers",                                                              
		windowStyle |                                                  
		WS_CLIPSIBLINGS |                                      
		WS_CLIPCHILDREN,                                        
		0, 0,                                                          
		windowRectangle.right - windowRectangle.left,  
		windowRectangle.bottom - windowRectangle.top,  
		NULL,                                                          
		NULL,                                                          
		GetModuleHandle(NULL),                                                      
		NULL)))                                                
	{
		MessageBox(NULL, L"Window Creation Error.", L"iGaia-CartoonPanzers", MB_OK | MB_ICONEXCLAMATION);            
		return;                                                        
	}

	if (!(hDC = GetDC(hWnd)))                                                        
	{
		MessageBox(NULL, L"Can't Create GL Device Context.", L"iGaia-CartoonPanzers", MB_OK | MB_ICONEXCLAMATION);
		return;                                                        
	}

	eglDisplay = eglGetDisplay(hDC);

	if(eglDisplay == EGL_NO_DISPLAY)
		eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);

	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
	{
		MessageBox(0, L"eglInitialize() failed.", L"iGaia-CartoonPanzers", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	eglBindAPI(EGL_OPENGL_ES_API);

	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,	0,
		EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		EGL_DEPTH_SIZE,	EGL_DONT_CARE,
		EGL_NONE
	};

	int iConfigs;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		MessageBox(0, L"eglChooseConfig() failed.", L"iGaia-CartoonPanzers", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);

	if(eglSurface == EGL_NO_SURFACE)
	{
		eglGetError();
		eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}

	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	eglSwapBuffers(eglDisplay, eglSurface);
	
	ShowWindow(hWnd, SW_SHOW);  
	UpdateWindow(hWnd);     
}
