//
//  CSceneUpdateMgr.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CSceneUpdateMgr.h"

CSceneUpdateMgr::CSceneUpdateMgr(void)
{

}

CSceneUpdateMgr::~CSceneUpdateMgr(void)
{

}

void CSceneUpdateMgr::AddEventListener(CSceneUpdateCallback_INTERFACE *_listener)
{
    m_listeners.insert(_listener);
}

void CSceneUpdateMgr::RemoveEventListener(CSceneUpdateCallback_INTERFACE *_listener)
{
    m_listeners.erase(_listener);
}

void CSceneUpdateMgr::OnUpdate(f32 _deltatime)
{
    for(std::set<CSceneUpdateCallback_INTERFACE*>::iterator iterator_ = m_listeners.begin(); iterator_ != m_listeners.end(); ++iterator_)
    {
        CSceneUpdateCallback_INTERFACE* listener = (*iterator_);
        listener->Get_Commands()->DispatchSceneDidUpdate(_deltatime);
    }
}