
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

bool TestEGLError(HWND hWnd, char* pszLocation)
{

	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS)
	{
		//TCHAR pszStr[256];
		//_stprintf(pszStr, L"%s failed (%d).\n", pszLocation, iErr);
		MessageBox(hWnd, L"EGL error", L"iGaia-CartoonPanzers", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

CGLWindow_Win32::CGLWindow_Win32(void)
{
	m_eglDisplay = 0;
	m_eglConfig = 0;
	m_eglSurface = 0;
	m_eglContext = 0;
	m_eglWindow = 0;

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

	m_eglWindow = hWnd;

	m_eglDisplay = eglGetDisplay(hDC);

	if(m_eglDisplay == EGL_NO_DISPLAY)
		m_eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);

	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(m_eglDisplay, &iMajorVersion, &iMinorVersion))
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
	if (!eglChooseConfig(m_eglDisplay, pi32ConfigAttribs, &m_eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		MessageBox(0, L"eglChooseConfig() failed.", L"iGaia-CartoonPanzers", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, m_eglWindow, NULL);

	if(m_eglSurface == EGL_NO_SURFACE)
	{
		eglGetError();
		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, NULL, NULL);
	}

	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, NULL, ai32ContextAttribs);

	eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
	
	ShowWindow(hWnd, SW_SHOW);  
	UpdateWindow(hWnd);     
}

void CGLWindow_Win32::Process(void)
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
}