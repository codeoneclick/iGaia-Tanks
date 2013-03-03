//
//  CUpdateCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CMainLoopUpdateCallback.h"

void CMainLoopUpdateCallback::ConnectMainLoopDidUpdateCallback(const __MAIN_LOOP_DID_UPDATE &_listener)
{
    assert(_listener != nullptr);
    m_mainLoopDidUpdateCallback = _listener;
}

void CMainLoopUpdateCallback::DispatchMainLoopDidUpdate(f32 _deltatime)
{
    assert(m_mainLoopDidUpdateCallback != nullptr);
    m_mainLoopDidUpdateCallback(_deltatime);
}

CMainLoopUpdateCallback_INTERFACE::CMainLoopUpdateCallback_INTERFACE(void)
{
    ConnectMainLoopUpdateCallback();
}

void CMainLoopUpdateCallback_INTERFACE::ConnectMainLoopUpdateCallback(void)
{
    m_mainLoopUpdateCallback.ConnectMainLoopDidUpdateCallback(std::bind(&CMainLoopUpdateCallback_INTERFACE::OnUpdate, this, std::placeholders::_1));
}
