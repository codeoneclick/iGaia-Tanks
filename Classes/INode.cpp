//
//  INode.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "INode.h"
#include "CSceneMgr.h"
#include "CResourceMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CWindow.h"
#include "CSettings.h"

INode::INode(void)
{
    m_scale    = glm::vec3(1.0f, 1.0f, 1.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_texcoordOffset = glm::vec2(0.0f, 0.0f);
    
    m_material = new CMaterial();
    m_mesh = nullptr;
    
    m_visible = true;
}

INode::~INode(void)
{
    if(m_mesh->Get_CreationMode() == IResource::E_CREATION_MODE_CUSTOM)
    {
        SAFE_DELETE(m_mesh);
    }
    SAFE_DELETE(m_material);
}

void INode::Set_Texture(CTexture *_texture, int _index, CTexture::E_WRAP_MODE _wrap)
{
    m_material->Set_Texture(_texture, _index, _wrap);
}

void INode::Set_Texture(const std::string &_name, int _index, CTexture::E_WRAP_MODE _wrap, IResource::E_THREAD _thread)
{
    m_pMaterial->Set_Texture(this, _sName, _index, _eWrap, _eThread);
}

void INode::Set_Shader(CShader::E_RENDER_MODE _eMode, IResource::E_SHADER _eShader)
{
    m_pMaterial->Set_Shader(this, _eMode, _eShader);
}

CShader* INode::Get_Shader(CShader::E_RENDER_MODE _eMode)
{
    return m_pMaterial->Get_Shader(_eMode);
}

CTexture* INode::Get_Texture(unsigned int _index)
{
    return m_pMaterial->Get_Texture(_index);
}

void INode::Set_RenderMode(CShader::E_RENDER_MODE _eMode, bool _value)
{
    m_pMaterial->Set_RenderMode(_eMode, _value);
}

bool INode::Get_RenderMode(CShader::E_RENDER_MODE _eMode)
{
    return m_pMaterial->Get_RenderMode(_eMode);
}

void INode::Update(void)
{
    m_mRotation = glm::rotate(glm::mat4(1.0f), m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_mRotation = glm::rotate(m_mRotation, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_mRotation = glm::rotate(m_mRotation, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    
    m_mTranslation = glm::translate(glm::mat4(1.0f), m_vPosition);

    m_mScale = glm::scale(glm::mat4(1.0f), m_vScale);
    
    m_mWorld = m_mTranslation * m_mRotation * m_mScale;
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    m_mWVP = pCamera->Get_Projection() * pCamera->Get_View() * m_mWorld;
    
    if(m_pBoundingBox != nullptr)
    {
        m_pBoundingBox->Set_MaxBound(m_pMesh->Get_MaxBound());
        m_pBoundingBox->Set_MinBound(m_pMesh->Get_MinBound());
        m_pBoundingBox->Set_WorldMatrix(m_mWorld);
    }
}

void INode::Render(CShader::E_RENDER_MODE _eMode)
{
    CSettings::g_iCurrentTrianglesPerFrame += m_pMesh->Get_IndexBufferRef()->Get_NumWorkingIndexes() / 3;
}





