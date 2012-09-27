//
//  CWater.cpp
//  iGaia
//
//  Created by sergey.sergeev on 3/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "COcean.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoord.h"

const int COcean::k_ELEMENT_NUM_INDEXES = 6;
const int COcean::k_ELEMENT_NUM_VERTEXES = 4;

COcean* COcean::m_pInstance = nullptr;

COcean* COcean::Instance(void)
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new COcean();
        m_pInstance->_Load(nullptr);
    }
    return m_pInstance;
}


COcean::COcean(void)
{
    m_iWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width() - 1;
    m_iHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height() - 1;
    m_fWaterHeight = -0.1f;
}

COcean::~COcean(void)
{
    m_pInstance = nullptr;
}

void COcean::_Load(void* data)
{
    CVertexBufferPositionTexcoord* pVertexBuffer = new CVertexBufferPositionTexcoord(4, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pVertexBuffer->Lock());
    
    pVertexBufferData[0].m_vPosition = glm::vec3( 0.0f + 0.1f,     m_fWaterHeight,  0.0f + 0.1f );
    pVertexBufferData[1].m_vPosition = glm::vec3( m_iWidth - 0.1f, m_fWaterHeight,  0.0f + 0.1f );
    pVertexBufferData[2].m_vPosition = glm::vec3( m_iWidth - 0.1f, m_fWaterHeight,  m_iHeight - 0.1f );
    pVertexBufferData[3].m_vPosition = glm::vec3( 0.0f + 0.1f,     m_fWaterHeight,  m_iHeight - 0.1f);
    
    pVertexBufferData[0].m_vTexcoord = glm::vec2( 0.0f,  0.0f );
    pVertexBufferData[1].m_vTexcoord = glm::vec2( 1.0f,  0.0f );
    pVertexBufferData[2].m_vTexcoord = glm::vec2( 1.0f,  1.0f );
    pVertexBufferData[3].m_vTexcoord = glm::vec2( 0.0f,  1.0f );
    
    CIndexBuffer* pIndexBuffer = new CIndexBuffer(6, GL_STATIC_DRAW);
    unsigned short* pIndexesBufferData = pIndexBuffer->Get_SourceData();
    
    pIndexesBufferData[0] = 0;
    pIndexesBufferData[1] = 1;
    pIndexesBufferData[2] = 2;
    pIndexesBufferData[3] = 0;
    pIndexesBufferData[4] = 2;
    pIndexesBufferData[5] = 3;
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_VertexBufferRef(pVertexBuffer);
    m_pMesh->Set_IndexBufferRef(pIndexBuffer);
    m_pMesh->Get_VertexBufferRef()->Commit();
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, true);
    m_pMaterial->Set_CullFace(GL_FRONT);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    m_pBoundingBox = new CBoundingBox(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
    
    glm::vec2 vScaleFactor = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_ScaleFactor();
    Set_Scale(glm::vec3(vScaleFactor.x, 1.0f, vScaleFactor.y));
}

//void COcean::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
//{
    
//}

void COcean::Update()
{
    INode::Update();
}

void COcean::Render(CShader::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    CShader* pShader = m_pMaterial->Get_Shader(_eMode);
    
    m_pMaterial->Commit(_eMode);
    
    static float fTimer = 0.0f;
    fTimer += 0.005f;
    
    switch (_eMode)
    {
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }

            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            pShader->Set_Matrix4x4(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            pShader->Set_CustomFloat(fTimer, "EXT_Timer");
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == NULL)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
            pShader->Set_Texture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION), CShader::E_TEXTURE_SLOT_01);
            pShader->Set_Texture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION), CShader::E_TEXTURE_SLOT_02);
            pShader->Set_Texture(CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_TextureHeightmap(), CShader::E_TEXTURE_SLOT_03);
        }
            break;
        case CShader::E_RENDER_MODE_REFLECTION:
        {
            
        }
            break;
        case CShader::E_RENDER_MODE_REFRACTION:
        {
            
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable(_eMode);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_IndexBufferRef()->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*)m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
}




