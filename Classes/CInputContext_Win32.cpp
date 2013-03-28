#include "CInputContext.h"

CInputContext* CInputContext::m_sharedInstance = nullptr;

CInputContext::CInputContext(void* _glWindow)
{
	m_isTapped = false;
	m_mousePosition = POINT();
}

CInputContext::~CInputContext(void)
{

}

CInputContext* CInputContext::SharedInstance(void)
{
	if(m_sharedInstance == nullptr)
	{
		m_sharedInstance = new CInputContext(nullptr);
	}
	return m_sharedInstance;
}

void CInputContext::AddTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE *_listener)
{
	m_tapRecognizerListeners.insert(_listener);
}

void CInputContext::RemoveTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE *_listener)
{
	m_tapRecognizerListeners.erase(_listener);
}

void CInputContext::TapRecognizerPressed(i32 _x, i32 _y)
{
	for(std::set<CInputTapRecognizerCallback_INTERFACE*>::iterator iterator = m_tapRecognizerListeners.begin(); iterator != m_tapRecognizerListeners.end(); ++iterator)
	{
		CInputTapRecognizerCallback_INTERFACE* listener = (*iterator);
		listener->Get_Commands()->DispatchInputTapRecognizerDidPressed(_x, _y);
	}
}

void CInputContext::TapRecognizerMoved(i32 _x, i32 _y)
{
	for(std::set<CInputTapRecognizerCallback_INTERFACE*>::iterator iterator = m_tapRecognizerListeners.begin(); iterator != m_tapRecognizerListeners.end(); ++iterator)
	{
		CInputTapRecognizerCallback_INTERFACE* listener = (*iterator);
		listener->Get_Commands()->DispatchInputTapRecognizerDidMoved(_x, _y);
	}
}

void CInputContext::TapRecognizerReleased(i32 _x, i32 _y)
{
	for(std::set<CInputTapRecognizerCallback_INTERFACE*>::iterator iterator = m_tapRecognizerListeners.begin(); iterator != m_tapRecognizerListeners.end(); ++iterator)
	{
		CInputTapRecognizerCallback_INTERFACE* listener = (*iterator);
		listener->Get_Commands()->DispatchInputTapRecognizerDidReleased(_x, _y);
	}
}

LRESULT CALLBACK CInputContext::InputProcess(HWND _HWND, UINT _message, WPARAM _paramW, LPARAM _paramL)  
{
	GetCursorPos(&CInputContext::SharedInstance()->m_mousePosition);
	ScreenToClient(_HWND, &CInputContext::SharedInstance()->m_mousePosition);
	switch (_message)                                                                        
	{
	case WM_ACTIVATE:                                              
		{
			return 0;                                                              
		}

	case WM_SYSCOMMAND:                                            
		{
			switch (_paramW)                                        
			{
			case SC_SCREENSAVE:                            
			case SC_MONITORPOWER:                          
				return 0;                                                      
			}
			break;                                                                  
		}

	case WM_CLOSE:                                                          
		{
			PostQuitMessage(0);                                            
			return 0;                                                      
		}

	case WM_KEYDOWN:                                                        
		{                                 
			return 0;                                                              
		}

	case WM_KEYUP:                                                          
		{                                
			return 0;                                                              
		}

	case WM_SIZE:                                                          
		{
			return 0;                                                              
		}

	case WM_RBUTTONDOWN :
		{
			return 0;              
		}
	case WM_RBUTTONUP :
		{
			return 0;      
		}

	case WM_LBUTTONDOWN :
		{
			CInputContext::SharedInstance()->TapRecognizerPressed(CInputContext::SharedInstance()->m_mousePosition.x, CInputContext::SharedInstance()->m_mousePosition.y);
			CInputContext::SharedInstance()->m_isTapped = true;
			return 0;              
		}
	case WM_LBUTTONUP :
		{
			CInputContext::SharedInstance()->TapRecognizerReleased(CInputContext::SharedInstance()->m_mousePosition.x, CInputContext::SharedInstance()->m_mousePosition.y);
			CInputContext::SharedInstance()->m_isTapped = false;
			return 0;      
		}
	}

	if(CInputContext::SharedInstance()->m_isTapped)
	{
		CInputContext::SharedInstance()->TapRecognizerMoved(CInputContext::SharedInstance()->m_mousePosition.x, CInputContext::SharedInstance()->m_mousePosition.y);
	}

	return DefWindowProc(_HWND, _message, _paramW, _paramL);
}
