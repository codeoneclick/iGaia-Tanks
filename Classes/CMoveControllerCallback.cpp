//
//  CMoveControllerCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#include "CMoveControllerCallback.h"

void CMoveControllerCallback::ConnectMoveControllerDidUpdateCallback(const __MOVE_CONTROLLER_DID_UPDATE &_listener)
{
    assert(_listener != nullptr);
    m_moveControllerDidUpdateCallback = _listener;
}

void CMoveControllerCallback::DispatchMoveControllerDidUpdate(ui32 _direction)
{
    assert(m_moveControllerDidUpdateCallback != nullptr);
    m_moveControllerDidUpdateCallback(_direction);
}

CMoveControllerCallback_INTERFACE::CMoveControllerCallback_INTERFACE(void)
{
    ConnectCallbacks();
}

void CMoveControllerCallback_INTERFACE::ConnectCallbacks(void)
{
    m_moveControllerCallback.ConnectMoveControllerDidUpdateCallback(std::bind(&CMoveControllerCallback_INTERFACE::OnMoveControllerUpdate, this, std::placeholders::_1));
}
