//
//  INode.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "CGameObject3d.h"


CGameObject3d::CGameObject3d(void)
{
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
    m_texcoordDisplacement = glm::vec2(0.0f, 0.0f);

    for(ui32 i = 0; i < E_RENDER_MODE_WORLD_SPACE_MAX; ++i)
    {
        m_materials[i] = nullptr;
    }

    m_mesh = nullptr;

    m_camera = nullptr;
    m_light = nullptr;

    m_renderMgr = nullptr;
    m_updateMgr = nullptr;
}

CGameObject3d::~CGameObject3d(void)
{
    
}

glm::vec3 CGameObject3d::Get_MaxBound(void)
{
    assert(m_mesh != nullptr);
    return m_mesh->Get_MaxBound();
}

glm::vec3 CGameObject3d::Get_MinBound(void)
{
    assert(m_mesh != nullptr);
    return m_mesh->Get_MinBound();
}

void CGameObject3d::Set_Texture(CTexture* _texture, E_TEXTURE_SLOT _slot, E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_materials[_mode] != nullptr);
    m_materials[_mode]->Set_Texture(_texture, _slot);
}

void CGameObject3d::ListenRenderMgr(bool _value)
{
    assert(m_renderMgr != nullptr);
    if(_value)
    {
        for(ui32 i = 0; i < E_RENDER_MODE_WORLD_SPACE_MAX; ++i)
        {
            if(m_materials[i] != nullptr)
            {
                m_renderMgr->AddEventListener(this, static_cast<E_RENDER_MODE_WORLD_SPACE>(i));
            }
        }
    }
    else
    {
        for(ui32 i = 0; i < E_RENDER_MODE_WORLD_SPACE_MAX; ++i)
        {
            if(m_materials[i] != nullptr)
            {
                m_renderMgr->RemoveEventListener(this, static_cast<E_RENDER_MODE_WORLD_SPACE>(i));
            }
        }
    }
}

void CGameObject3d::ListenUpdateMgr(bool _value)
{
    assert(m_updateMgr != nullptr);
    if(_value)
    {
        m_updateMgr->AddEventListener(this);
    }
    else
    {
        m_updateMgr->RemoveEventListener(this);
    }
}

void CGameObject3d::OnResourceDidLoad(IResource_INTERFACE* _resource)
{
    
}

void CGameObject3d::OnUpdate(f32 _deltatime)
{
    m_matrixRotation = glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_matrixRotation = glm::rotate(m_matrixRotation, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_matrixRotation = glm::rotate(m_matrixRotation, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    m_matrixTranslation = glm::translate(glm::mat4(1.0f), m_position);
    m_matrixScale = glm::scale(glm::mat4(1.0f), m_scale);
    m_matrixWorld = m_matrixTranslation * m_matrixRotation * m_matrixScale;
}

void CGameObject3d::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_materials[_mode] != nullptr);
    m_materials[_mode]->Bind();
    assert(m_mesh != nullptr);
    m_mesh->Bind(m_materials[_mode]->Get_Shader()->Get_VertexSlots());
}

void CGameObject3d::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_mesh != nullptr);
    m_mesh->Draw();
}

void CGameObject3d::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_materials[_mode] != nullptr);
    m_materials[_mode]->Unbind();
    assert(m_mesh != nullptr);
    m_mesh->Unbind(m_materials[_mode]->Get_Shader()->Get_VertexSlots());
}
