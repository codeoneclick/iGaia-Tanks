
#include "CMainLoop.h"

class CMainLoop_Win32
{
private:

protected:

	std::set<CMainLoopUpdateCallback_INTERFACE*> m_listeners;
	static CMainLoop_Win32* m_sharedInstance;

public:

	CMainLoop_Win32(void);
	~CMainLoop_Win32(void);

	static CMainLoop_Win32* SharedInstance(void);

	void ConnectToMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener);
	void DisconnectFromMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener);
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