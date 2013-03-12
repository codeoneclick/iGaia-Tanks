//
//  CSceneContainer.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CSceneContainer.h"

CSceneContainer::~CSceneContainer(void)
{
    for (std::set<CGameObject3d*>::iterator iterator = m_gameObjects3dContainer.begin(); iterator != m_gameObjects3dContainer.end(); ++iterator)
    {
        CGameObject3d* gameObject3d = (*iterator);
        delete gameObject3d;
    }
    m_gameObjects3dContainer.clear();
    
    for (std::set<CLight*>::iterator iterator = m_lightsContainer.begin(); iterator != m_lightsContainer.end(); ++iterator)
    {
        CLight* light = (*iterator);
        delete light;
    }
    m_lightsContainer.clear();
    
    for (std::set<CCamera*>::iterator iterator = m_camerasContainer.begin(); iterator != m_camerasContainer.end(); ++iterator)
    {
        CCamera* camera = (*iterator);
        delete camera;
    }
    m_camerasContainer.clear();
}

void CSceneContainer::AddCamera(CCamera *_camera)
{
    m_camerasContainer.insert(_camera);
}

void CSceneContainer::AddLight(CLight *_light)
{
    m_lightsContainer.insert(_light);
}

void CSceneContainer::AddGameObject3d(CGameObject3d *_object3d)
{
    m_gameObjects3dContainer.insert(_object3d);
}

void CSceneContainer::RemoveCamera(CCamera *_camera)
{
    assert(m_camerasContainer.find(_camera) != m_camerasContainer.end());
    m_camerasContainer.erase(_camera);
    delete _camera;
}

void CSceneContainer::RemoveLight(CLight *_light)
{
    assert(m_lightsContainer.find(_light) != m_lightsContainer.end());
    m_lightsContainer.erase(_light);
    delete _light;
}

void CSceneContainer::RemoveGameObject3d(CGameObject3d *_object3d)
{
    assert(m_gameObjects3dContainer.find(_object3d) != m_gameObjects3dContainer.end());
    m_gameObjects3dContainer.erase(_object3d);
    delete _object3d;
}