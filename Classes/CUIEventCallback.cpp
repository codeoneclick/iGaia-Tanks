//
//  CUIEventCallback.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#include "CUIEventCallback.h"

void CUIEventCallback::ConnectEventDidPreformCallback(const __EVENT_DID_PERFORM &_listener)
{
    assert(_listener != nullptr);
    m_eventDidPerformCallback = _listener;
}


void CUIEventCallback::DispatchEventDidPerform(const std::string &_command)
{
    assert(m_eventDidPerformCallback != nullptr);
    m_eventDidPerformCallback(_command);
}

CUIEventCallback_INTERFACE::CUIEventCallback_INTERFACE(void)
{
    ConnectCallbacks();
}

void CUIEventCallback_INTERFACE::ConnectCallbacks(void)
{
    m_eventPerformCallback.ConnectEventDidPreformCallback(std::bind(&CUIEventCallback_INTERFACE::OnPerform, this, std::placeholders::_1));
}
