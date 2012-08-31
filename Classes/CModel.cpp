
//  CModel.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CModel.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"

CModel::CModel(void)
{
    
}

CModel::~CModel(void)
{
    
}

void CModel::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    m_pMesh = static_cast<CMesh*>(CResourceMgr::Instance()->LoadSync(IResource::E_MGR_MESH, _sName));
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, true);
    m_pMaterial->Set_CullFace(GL_FRONT);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_pBoundingBox = new CBoundingBox(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
}

void CModel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
    
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pBoundingBox->Get_Mesh()->Get_VertexBufferRef(), m_pBoundingBox->Get_Mesh()->Get_IndexBufferRef(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CModel::OnTouchEven] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    for(size_t index = 0; index < m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index]->Get_DelegateType() == IDelegate::E_DELEGATE_TYPE_TOUCH)
        {
            dynamic_cast<ITouchDelegate*>(m_lDelegateOwners[index])->OnTouchEvent(this);
        }
    }
}

void CModel::Update()
{
    INode::Update();
}

void CModel::Render(CShader::E_RENDER_MODE _eMode)
{
    if(CSceneMgr::Instance()->Get_Camera()->Get_Frustum()->IsBoxInFrustum(m_pBoundingBox->Get_MaxBound() + m_vPosition, m_pBoundingBox->Get_MinBound() + m_vPosition) == CFrustum::E_FRUSTUM_RESULT_OUTSIDE || !m_bIsVisible)
    {
        return;
    }
    
    INode::Render(_eMode);
    
    m_pMaterial->Commit(_eMode);
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    CShader* pShader = m_pMaterial->Get_Shader(_eMode);
    ILight* pLight = CSceneMgr::Instance()->Get_Light();
    
    switch (_eMode)
    {
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(pShader == nullptr)
            {
                LOG("Shader MODE_SIMPLE is NULL");
            }
            
            pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            pShader->Set_Vector2(m_vTexCoordOffset, CShader::E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET);
            pShader->Set_Vector3(pLight->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == nullptr)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        case CShader::E_RENDER_MODE_REFLECTION:
        {
            if(pShader == nullptr)
            {
                LOG("Shader RENDER_MODE_REFLECTION is NULL");
            }
            
            pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            pShader->Set_Vector2(m_vTexCoordOffset, CShader::E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET);
            pShader->Set_Vector3(pLight->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == nullptr)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        case CShader::E_RENDER_MODE_REFRACTION:
        {
            if(pShader == nullptr)
            {
                LOG("Shader RENDER_MODE_REFRACTION is NULL");
            }
            
            pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            pShader->Set_Vector2(m_vTexCoordOffset, CShader::E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET);
            pShader->Set_Vector3(pLight->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == nullptr)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(pShader == nullptr)
            {
                LOG("Shader RENDER_MODE_SCREEN_NORMAL_MAP is NULL");
            }
            
            pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == nullptr)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable(_eMode);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_IndexBufferRef()->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
    
    if(CShader::E_RENDER_MODE_SIMPLE == _eMode)
    {
        m_pBoundingBox->Render();
    }
}

