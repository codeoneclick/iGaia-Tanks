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
    m_camerasContainer.erase(_camera);
}

void CSceneContainer::RemoveLight(CLight *_light)
{
    m_lightsContainer.erase(_light);
}

void CSceneContainer::RemoveGameObject3d(CGameObject3d *_object3d)
{
    m_gameObjects3dContainer.erase(_object3d);
}