//
//  CUIEventCallback.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#include "CUIEventCallback.h"

void CUIEventCallback::ConnectUIEventDidPreformCallback(const __UI_EVENT_DID_PERFORM &_listener)
{
    assert(_listener != nullptr);
    m_uiEventDidPerformCallback = _listener;
}


void CUIEventCallback::DispatchUIEventDidPerform(const std::string& _command, i32 _x, i32 _y)
{
    assert(m_uiEventDidPerformCallback != nullptr);
    m_uiEventDidPerformCallback(_command, _x, _y);
}

CUIEventCallback_INTERFACE::CUIEventCallback_INTERFACE(void)
{
    ConnectUIEventCallbacks();
}

void CUIEventCallback_INTERFACE::ConnectUIEventCallbacks(void)
{
    m_uiEventPerformCallback.ConnectUIEventDidPreformCallback(std::bind(&CUIEventCallback_INTERFACE::OnUIEventPerform, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}
