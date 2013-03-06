//
//  INode.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "INode.h"


INode::INode(void)
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

INode::~INode(void)
{
    
}

INode* INode::Load(CResourceMgrsFacade* _resourceMgrsFacade, const std::string& _name)
{
    
}

glm::vec3 INode::Get_MaxBound(void)
{
    assert(m_mesh != nullptr);
    return m_mesh->Get_MaxBound();
}

glm::vec3 INode::Get_MinBound(void)
{
    assert(m_mesh != nullptr);
    return m_mesh->Get_MinBound();
}

void INode::Set_Texture(CTexture* _texture, E_TEXTURE_SLOT _slot, E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_materials[_mode] != nullptr);
    m_materials[_mode]->Set_Texture(_texture, _slot);
}

void INode::ListenRenderMgr(bool _value)
{
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

void INode::ListenUpdateMgr(bool _value)
{
    
}

void INode::OnResourceDidLoad(IResource_INTERFACE* _resource)
{
    
}

void INode::OnUpdate(f32 _deltatime)
{
    
}

void INode::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{

}

void INode::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
{

}

void INode::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    
}

//INode::INode(void)
//{
//    m_vScale    = glm::vec3(1.0f, 1.0f, 1.0f);
//    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
//    m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
//    m_vTexCoordOffset = glm::vec2(0.0f, 0.0f);
//
//    m_pMaterial = new CMaterial();
//    m_pBoundingBox = NULL;
//    m_pMesh = NULL;
//    m_bIsVisible = true;
//}
//
//INode::~INode(void)
//{
//    std::cout<<"[INode::~INode] delete"<<std::endl;
//    CResourceMgr::Instance()->Cancel_Load(this);
//    m_lDelegateOwners.clear();
//    SAFE_DELETE(m_pBoundingBox);
//    if(m_pMesh->Get_CreationMode() == IResource::E_CREATION_MODE_CUSTOM)
//    {
//        SAFE_DELETE(m_pMesh);
//    }
//    SAFE_DELETE(m_pMaterial);
//}
//
//void INode::Set_Rotation(const glm::vec3 &_vRotation)
//{
//    m_vRotation = _vRotation;
//    m_vRotation.x = CMathHelper::Instance()->Get_WrapAngle(m_vRotation.x, 0.0f, 360.0f);
//    m_vRotation.y = CMathHelper::Instance()->Get_WrapAngle(m_vRotation.y, 0.0f, 360.0f);
//    m_vRotation.z = CMathHelper::Instance()->Get_WrapAngle(m_vRotation.z, 0.0f, 360.0f);
//}
//
//void INode::Set_Texture(CTexture *_pTexture, int _index, CTexture::E_WRAP_MODE _eWrap)
//{
//    m_pMaterial->Set_Texture(_pTexture, _index, _eWrap);
//}
//
//void INode::Set_Texture(const std::string &_sName, int _index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread)
//{
//    m_pMaterial->Set_Texture(this, _sName, _index, _eWrap, _eThread);
//}
//
//void INode::Set_Shader(CShader::E_RENDER_MODE _eMode, IResource::E_SHADER _eShader)
//{
//    m_pMaterial->Set_Shader(this, _eMode, _eShader);
//}
//
//CShader* INode::Get_Shader(CShader::E_RENDER_MODE _eMode)
//{
//    return m_pMaterial->Get_Shader(_eMode);
//}
//
//CTexture* INode::Get_Texture(unsigned int _index)
//{
//    return m_pMaterial->Get_Texture(_index);
//}
//
//void INode::Set_RenderMode(CShader::E_RENDER_MODE _eMode, bool _value)
//{
//    m_pMaterial->Set_RenderMode(_eMode, _value);
//}
//
//bool INode::Get_RenderMode(CShader::E_RENDER_MODE _eMode)
//{
//    return m_pMaterial->Get_RenderMode(_eMode);
//}
//
//void INode::Add_DelegateOwner(IDelegate *_pDelegateOwner)
//{
//    for(size_t index = 0; index< m_lDelegateOwners.size(); index++)
//    {
//        if(m_lDelegateOwners[index] == _pDelegateOwner)
//        {
//            std::cout<<"[INode::Add_DelegateOwner] Error - can not add same delegate owner"<<std::endl;
//            return;
//        }
//    }
//    m_lDelegateOwners.push_back(_pDelegateOwner);
//}
//
//void INode::Remove_DelegateOwner(IDelegate *_pDelegateOwner)
//{
//    std::vector<IDelegate*>::iterator pBeginIterator = m_lDelegateOwners.begin();
//    std::vector<IDelegate*>::iterator pEndIterator = m_lDelegateOwners.end();
//    while (pBeginIterator != pEndIterator)
//    {
//        if((*pBeginIterator) == _pDelegateOwner)
//        {
//            m_lDelegateOwners.erase(pBeginIterator);
//            return;
//        }
//        ++pBeginIterator;
//    }
//}
//
//void INode::OnResourceDidLoad(IResource* _pResource, E_RESOURCE_TYPE _eResourceType)
//{
//    
//}
//
//void INode::Update(void)
//{
//    m_mRotation = glm::rotate(glm::mat4(1.0f), m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
//    m_mRotation = glm::rotate(m_mRotation, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
//    m_mRotation = glm::rotate(m_mRotation, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
//    
//    m_mTranslation = glm::translate(glm::mat4(1.0f), m_vPosition);
//    
//    m_mScale = glm::scale(glm::mat4(1.0f), m_vScale);
//    
//    m_mWorld = m_mTranslation * m_mRotation * m_mScale;
//    
//    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
//    
//    m_mWVP = pCamera->Get_Projection() * pCamera->Get_View() * m_mWorld;
//    
//    if(m_pBoundingBox != NULL)
//    {
//        m_pBoundingBox->Set_MaxMinPoints(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
//        m_pBoundingBox->Set_WorldMatrix(m_mWorld);
//    }
//}
//
//void INode::Render(CShader::E_RENDER_MODE _eMode)
//{
//    CSettings::g_iCurrentTrianglesPerFrame += m_pMesh->Get_IndexBufferRef()->Get_NumWorkingIndexes() / 3;
//}





