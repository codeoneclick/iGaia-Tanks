//
//  CSceneGraph.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CSceneGraph.h"

CSceneGraph::CSceneGraph(void)
{
    m_camera = nullptr;
    m_light = nullptr;

    m_landscape = nullptr;

    m_updateMgr = nullptr;
    m_renderMgr = nullptr;
}

CSceneGraph::~CSceneGraph(void)
{

}

void CSceneGraph::Set_Camera(CCamera* _camera)
{
    if(m_camera != nullptr)
    {
        assert(m_updateMgr != nullptr);
        m_updateMgr->RemoveEventListener(m_camera);
    }
    
    m_camera = _camera;
    assert(m_updateMgr != nullptr);
    m_updateMgr->AddEventListener(m_camera);

    for(std::set<CShape3d*>::iterator iterator = m_shapes3dContainer.begin(); iterator != m_shapes3dContainer.end(); ++iterator)
    {
        CShape3d* shape3d = *iterator;
        shape3d->Set_Camera(m_camera);
    }
}

void CSceneGraph::Set_Light(CLight* _light)
{
    m_light = _light;
    for(std::set<CShape3d*>::iterator iterator = m_shapes3dContainer.begin(); iterator != m_shapes3dContainer.end(); ++iterator)
    {
        CShape3d* shape3d = *iterator;
        shape3d->Set_Light(m_light);
    }
}

void CSceneGraph::Set_Landscape(CLandscape* _landscape)
{
    if(m_landscape != nullptr)
    {
        m_landscape->ListenUpdateMgr(false);
        m_landscape->ListenRenderMgr(false);
        m_landscape = nullptr;
    }

    m_landscape = _landscape;

    // FIXME :
    //m_landscape->Set_Clipping(glm::vec4(0.0f, 1.0f, 0.0f, 0.1f), E_RENDER_MODE_WORLD_SPACE_REFLECTION);
    //m_landscape->Set_Clipping(glm::vec4(0.0f, -1.0f, 0.0f, 0.1f), E_RENDER_MODE_WORLD_SPACE_REFRACTION);

    assert(m_updateMgr != nullptr);
    assert(m_renderMgr != nullptr);
    
    m_landscape->Set_Camera(m_camera);
    m_landscape->Set_Light(m_light);
    m_landscape->Set_UpdateMgr(m_updateMgr);
    m_landscape->Set_RenderMgr(m_renderMgr);
    m_landscape->ListenUpdateMgr(true);
    m_landscape->ListenRenderMgr(true);
}

void CSceneGraph::InsertShape3d(CShape3d *_shape3d)
{
    CShape3d* shape3d = _shape3d;

    // FIXME :
    //shape3d->Set_Clipping(glm::vec4(0.0f, 1.0f, 0.0f, 0.1f), E_RENDER_MODE_WORLD_SPACE_REFLECTION);
    //shape3d->Set_Clipping(glm::vec4(0.0f, -1.0f, 0.0f, 0.1f), E_RENDER_MODE_WORLD_SPACE_REFRACTION);

    if(m_camera != nullptr)
    {
        shape3d->Set_Camera(m_camera);
    }

    if(m_light != nullptr)
    {
        shape3d->Set_Light(m_light);
    }

    assert(m_updateMgr != nullptr);
    assert(m_renderMgr != nullptr);

    shape3d->Set_UpdateMgr(m_updateMgr);
    shape3d->Set_RenderMgr(m_renderMgr);
    shape3d->ListenUpdateMgr(true);
    shape3d->ListenRenderMgr(true);

    m_shapes3dContainer.insert(shape3d);
}

void CSceneGraph::RemoveShape3d(CShape3d *_shape3d)
{
    CShape3d* shape3d = _shape3d;
    shape3d->ListenUpdateMgr(false);
    shape3d->ListenRenderMgr(false);
    m_shapes3dContainer.erase(shape3d);
}

