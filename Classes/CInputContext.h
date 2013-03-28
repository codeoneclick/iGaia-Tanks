//
//  CInputMgr.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/27/13.
//
//

#ifndef CInputContext_h
#define CInputContext_h

#include "HCommon.h"
#include "IInputContext.h"

#ifndef __APPLE__

#include <windows.h>

#endif

class CInputContext : public IInputContext_INTERFACE
{
private:

protected:

#ifndef __APPLE__

    static CInputContext* m_sharedInstance;
	POINT m_mousePosition;
	bool m_isTapped;

#endif

    std::set<CInputTapRecognizerCallback_INTERFACE*> m_tapRecognizerListeners;

public:

    CInputContext(void* _glWindow);
    ~CInputContext(void);

#ifndef __APPLE__

	static CInputContext* SharedInstance(void);
	static LRESULT  CALLBACK InputProcess(HWND _HWND, UINT _message, WPARAM _paramW, LPARAM _paramL);

#endif

    void TapRecognizerPressed(i32 _x, i32 _y);
    void TapRecognizerMoved(i32 _x, i32 _y);
    void TapRecognizerReleased(i32 _x, i32 _y);

    void AddTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener);
    void RemoveTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener);
};

#endif 
