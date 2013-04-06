//
//  CMoveControllerView_iOS.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#ifndef CMoveGamepadView_h
#define CMoveGamepadView_h

#include "HCommon.h"
#include "IUIView.h"
#include "CUIEventCallback.h"
#include "CMoveControllerCallback.h"
#include "HGameEnum.h"

class CMoveGamepadView :
public IUIView_INTERFACE,
public CUIEventCallback_INTERFACE
{
private:
    
    std::set<CMoveControllerCallback_INTERFACE*> m_listeners;
    void InvokeCallback(E_MOVE_CONTROLLER_DIRECTION _direction);
    
protected:
    
    void OnUIEventPerform(const std::string& _command, i32 _x, i32 _y);
    
public:
    
	CMoveGamepadView(void);
	~CMoveGamepadView(void);
    
    void AddEventListener(CMoveControllerCallback_INTERFACE* _listener);
    void RemoveEventListener(CMoveControllerCallback_INTERFACE* _listener);
};

#endif