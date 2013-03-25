
#include "CMainLoop.h"

class CMainLoop_Win32
{
private:

protected:

	std::set<CMainLoopUpdateCallback_INTERFACE*> m_listeners;
	static CMainLoop_Win32* m_sharedInstance;

	void OnUpdate(f32 _deltatime);

public:

	CMainLoop_Win32(void);
	~CMainLoop_Win32(void);

	static CMainLoop_Win32* SharedInstance(void);

	void ConnectToMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener);
	void DisconnectFromMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener);

	void Run(void);
};

CMainLoop_Win32* CMainLoop_Win32::m_sharedInstance = nullptr;

CMainLoop_Win32* CMainLoop_Win32::SharedInstance(void)
{
	if(m_sharedInstance == nullptr)
	{
		m_sharedInstance = new CMainLoop_Win32();
	}
	return m_sharedInstance;
}

CMainLoop_Win32::CMainLoop_Win32(void)
{

}

CMainLoop_Win32::~CMainLoop_Win32(void)
{

}

void CMainLoop_Win32::Run(void)
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while(WM_QUIT != msg.message)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			OnUpdate(0.0f);
		}
	}
}

void CMainLoop_Win32::OnUpdate(f32 _deltatime)
{
	 for (std::set<CMainLoopUpdateCallback_INTERFACE*>::iterator iterator = m_listeners.begin(); iterator != m_listeners.end(); ++iterator)
    {
        CMainLoopUpdateCallback_INTERFACE* listener = *iterator;
        listener->Get_Commands()->DispatchMainLoopDidUpdate(0.0f);
    }
}

void CMainLoop_Win32::ConnectToMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener)
{
	 m_listeners.insert(_listener);
}

void CMainLoop_Win32::DisconnectFromMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener)
{
	 m_listeners.erase(_listener);
}

void ConnectToMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener)
{
	CMainLoop_Win32::SharedInstance()->ConnectToMainLoop(_listener);
}

void DisconnectFromMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener)
{
	CMainLoop_Win32::SharedInstance()->DisconnectFromMainLoop(_listener);
}

void Run(void)
{
	CMainLoop_Win32::SharedInstance()->Run();
}