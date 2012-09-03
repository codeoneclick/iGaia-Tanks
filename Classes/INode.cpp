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
    m_vScale    = glm::vec3(1.0f, 1.0f, 1.0f);
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vTexCoordOffset = glm::vec2(0.0f, 0.0f);
    
    m_pMaterial = new CMaterial();
    m_pBoundingBox = nullptr;
    m_pMesh = nullptr;
    m_bIsVisible = true;
    
    m_pResourceEventSignature = [this](IResource* _pResource, IResource::EventHandle iEventHandle)->void
    {
        switch (_pResource->Get_ResourceType())
        {
            case IResource::E_RESOURCE_TYPE_MESH:
                std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
                m_pMesh = static_cast<CMesh*>(_pResource);
                for(unsigned int i = 0; i < CShader::E_RENDER_MODE_MAX; ++i)
                {
                    CShader* pShader = m_pMaterial->Get_Shader(static_cast<CShader::E_RENDER_MODE>(i));
                    if(pShader != NULL)
                    {
                        m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(static_cast<CShader::E_RENDER_MODE>(i), pShader);
                    }
                }
                
                break;
            case IResource::E_RESOURCE_TYPE_TEXTURE:
                std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
                if(m_lTextureLoadingQueue.find(_pResource->Get_Name()) != m_lTextureLoadingQueue.end())
                {
                    unsigned int index = m_lTextureLoadingQueue[_pResource->Get_Name()];
                    m_pMaterial->Set_Texture(static_cast<CTexture*>(_pResource), index, CTexture::E_WRAP_MODE_REPEAT);
                    m_lTextureLoadingQueue.erase(_pResource->Get_Name());
                }
                break;
            default:
                break;
        }
    };
}

INode::~INode(void)
{
    std::cout<<"[INode::~INode] delete"<<std::endl;
    
    for(auto& iEventHandler : m_lResourceEventHandles)
    {
        CResourceMgr::Instance()->RemoveEventListener(iEventHandler);
    }
    m_lResourceEventHandles.clear();
    
    m_lDelegateOwners.clear();
    SAFE_DELETE(m_pBoundingBox);
    if(m_pMesh->Get_CreationMode() == IResource::E_CREATION_MODE_CUSTOM)
    {
        SAFE_DELETE(m_pMesh);
    }
    SAFE_DELETE(m_pMaterial);
}

void INode::Set_Rotation(const glm::vec3 &_vRotation)
{
    m_vRotation = _vRotation;
    m_vRotation.x = CMathHelper::Instance()->Get_WrapAngle(m_vRotation.x, 0.0f, 360.0f);
    m_vRotation.y = CMathHelper::Instance()->Get_WrapAngle(m_vRotation.y, 0.0f, 360.0f);
    m_vRotation.z = CMathHelper::Instance()->Get_WrapAngle(m_vRotation.z, 0.0f, 360.0f);
}

void INode::Set_Texture(CTexture *_pTexture, int _index, CTexture::E_WRAP_MODE _eWrap)
{
    m_pMaterial->Set_Texture(_pTexture, _index, _eWrap);
}

void INode::Set_Texture(const std::string &_sName, int _index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread)
{
    m_lTextureLoadingQueue[_sName] = _index;
    CResourceMgr::Instance()->AddEventListener(_sName, IResource::E_MGR_TEXTURE, _eThread, m_pResourceEventSignature);
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

void INode::Add_DelegateOwner(IDelegate *_pDelegateOwner)
{
    for(size_t index = 0; index< m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index] == _pDelegateOwner)
        {
            std::cout<<"[INode::Add_DelegateOwner] Error - can not add same delegate owner"<<std::endl;
            return;
        }
    }
    m_lDelegateOwners.push_back(_pDelegateOwner);
}

void INode::Remove_DelegateOwner(IDelegate *_pDelegateOwner)
{
    for(size_t index = 0; index < m_lDelegateOwners.size(); ++index)
    {
        if(m_lDelegateOwners[index] == _pDelegateOwner)
        {
            m_lDelegateOwners.erase(m_lDelegateOwners.begin() + index);
        }
    }
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
    
    if(m_pBoundingBox != nullptr && m_pMesh != nullptr)
    {
        m_pBoundingBox->Set_MaxMinPoints(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
        m_pBoundingBox->Set_WorldMatrix(m_mWorld);
    }
}

void INode::Render(CShader::E_RENDER_MODE _eMode)
{
    if(m_pMesh != nullptr)
    CSettings::g_iCurrentTrianglesPerFrame += m_pMesh->Get_IndexBufferRef()->Get_NumWorkingIndexes() / 3;
}





