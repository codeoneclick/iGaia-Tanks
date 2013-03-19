//
//  CRotateControllerCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/19/13.
//
//

#include "CRotateControllerCallback.h"

void CRotateControllerCallback::ConnectRotateControllerDidUpdateCallback(const __ROTATE_CONTROLLER_DID_UPDATE &_listener)
{
    assert(_listener != nullptr);
    m_rotateControllerDidUpdateCallback = _listener;
}

void CRotateControllerCallback::DispatchRotateControllerDidUpdate(ui32 _direction)
{
    assert(m_rotateControllerDidUpdateCallback != nullptr);
    m_rotateControllerDidUpdateCallback(_direction);
}

CRotateControllerCallback_INTERFACE::CRotateControllerCallback_INTERFACE(void)
{
    ConnectCallbacks();
}

void CRotateControllerCallback_INTERFACE::ConnectCallbacks(void)
{
    m_rotateControllerCallback.ConnectRotateControllerDidUpdateCallback(std::bind(&CRotateControllerCallback_INTERFACE::OnRotateControllerUpdate, this, std::placeholders::_1));
}
