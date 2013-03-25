
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
	m_hWnd = 0;
	m_hDC = 0;

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
	if (!(m_hWnd = CreateWindowEx(windowExtStyle,                                                  
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

	if (!(m_hDC = GetDC(m_hWnd)))                                                        
	{
		MessageBox(NULL, L"Can't Create GL Device Context.", L"iGaia-CartoonPanzers", MB_OK | MB_ICONEXCLAMATION);
		return;                                                        
	}

	ShowWindow(m_hWnd, SW_SHOW);  
	UpdateWindow(m_hWnd);     
}
