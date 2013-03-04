//
//  CUpdateCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/4/13.
//
//

#include "CSceneUpdateCallback.h"

void CSceneUpdateCallback::ConnectSceneDidUpdateCallback(const __SCENE_DID_UPDATE &_listener)
{
    assert(_listener != nullptr);
    m_sceneDidUpdateCallback = _listener;
}

void CSceneUpdateCallback::DispatchSceneDidUpdate(f32 _deltatime)
{
    assert(m_sceneDidUpdateCallback != nullptr);
    m_sceneDidUpdateCallback(_deltatime);
}

CSceneUpdateCallback_INTERFACE::CSceneUpdateCallback_INTERFACE(void)
{
    ConnectSceneUpdateCallback();
}

void CSceneUpdateCallback_INTERFACE::ConnectSceneUpdateCallback(void)
{
    m_sceneUpdateCallback.ConnectSceneDidUpdateCallback(std::bind(&CSceneUpdateCallback_INTERFACE::OnUpdate, this, std::placeholders::_1));
}
