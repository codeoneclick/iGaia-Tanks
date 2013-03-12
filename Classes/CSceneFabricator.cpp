//
//  CSceneFabricator.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CSceneFabricator.h"

CSceneFabricator::CSceneFabricator(void)
{
    m_sceneContainer = new CSceneContainer();
    m_resourceMgrsFacade = new CResourceMgrsFacade();
    m_shaderComposite = nullptr;
}

CSceneFabricator::~CSceneFabricator(void)
{
    delete m_sceneContainer;
}

CCamera* CSceneFabricator::CreateCamera(f32 _fov, f32 _near, f32 _far,const glm::vec4& _viewport)
{
    CCamera* camera = new CCamera(_fov, _near, _far, _viewport);
    assert(m_sceneContainer != nullptr);
    m_sceneContainer->AddCamera(camera);
    return camera;
}

CLight* CSceneFabricator::CreateLight(void)
{
    CLight* light = new CLight();
    assert(m_sceneContainer != nullptr);
    m_sceneContainer->AddLight(light);
    return light;
}

CShape3d* CSceneFabricator::CreateShape3d(const std::string& _filename)
{
    assert(m_resourceMgrsFacade != nullptr);
    assert(m_shaderComposite != nullptr);
    assert(m_sceneContainer != nullptr);
    CShape3d* shape3d = new CShape3d();
    shape3d->Load(m_resourceMgrsFacade, m_shaderComposite, _filename);
    m_sceneContainer->AddGameObject3d(shape3d);
    return shape3d;
}

void CSceneFabricator::DeleteShape3d(CShape3d *_shape3d)
{
    assert(m_sceneContainer != nullptr);
    m_sceneContainer->RemoveGameObject3d(_shape3d);
}
