//
//  CBatch.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/21/12.
//
//

#include "CBatch.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoordNormalTangent.h"
#include "CVertexBufferPositionTexcoordColor.h"
#include "CVertexBufferPositionTexcoord.h"

CBatch::CBatch(E_BATCH_MODE _eMode)
{
    m_eMode = _eMode;
    
    m_pTextures = new CTexture*[k_TEXTURES_MAX_COUNT];
    for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
    {
        m_pTextures[i] = NULL;
    }
    
    m_pShaders = new CShader*[CShader::E_RENDER_MODE_MAX];
    for(unsigned int i = 0; i < CShader::E_RENDER_MODE_MAX; ++i)
    {
        m_pShaders[i] = NULL;
    }
    
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = k_MAX_VERTEXES;
    pSourceData->m_iNumIndexes  = k_MAX_INDEXES;
    
    switch (m_eMode)
    {
        case E_BATCH_MODE_MODEL:
            pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordNormalTangent(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
            break;
        case E_BATCH_MODE_PARTICLE_EMITTER:
            pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordColor(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
            break;
        case E_BATCH_MODE_SPRITE:
            pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
            break;
        case E_BATCH_MODE_SPRITE_CROSS:
            pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
            break;
            
        default:
            break;
    }
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STATIC_DRAW);
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    
    m_iNumVertexes = 0;
    m_iNumIndexes = 0;
}

CBatch::~CBatch(void)
{
    
}

void CBatch::Reset_MeshRef(void)
{
    m_iNumIndexes = 0;
    m_iNumVertexes = 0;
    m_lContainer.clear();
}

void CBatch::Push_MeshRef(INode *_pNode)
{
    m_lContainer.push_back(_pNode);
    m_iNumVertexes += _pNode->Get_Mesh()->Get_NumVertexes();
    m_iNumIndexes += _pNode->Get_Mesh()->Get_NumIndexes();
    
    for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
    {
        m_pTextures[i] = _pNode->Get_Texture(i);
    }
    
    for(unsigned int i = 0; i < CShader::E_RENDER_MODE_MAX; ++i)
    {
        m_pShaders[i] = _pNode->Get_Shader(static_cast<CShader::E_RENDER_MODE>(i));
        m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(static_cast<CShader::E_RENDER_MODE>(i), m_pShaders[i]);
    }
}

void CBatch::Update(void)
{
    switch (m_eMode)
    {
        case E_BATCH_MODE_MODEL:
        {
            
        }
            break;
        case E_BATCH_MODE_PARTICLE_EMITTER:
        {
            CVertexBufferPositionTexcoordColor::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordColor::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
            unsigned short* pIndexBufferData = m_pMesh->Get_IndexBufferRef()->Get_SourceData();
            unsigned int iNumVertexesOffset = 0;
            unsigned int iNumIndexesOffset = 0;
            for(unsigned int i = 0; i < m_lContainer.size(); ++i)
            {
                INode* pNode = m_lContainer[i];
                unsigned int iCurrentNumVertexes = pNode->Get_Mesh()->Get_NumVertexes();
                CVertexBufferPositionTexcoordColor::SVertex* pNodeVertexBufferData = static_cast<CVertexBufferPositionTexcoordColor::SVertex*>(pNode->Get_Mesh()->Get_VertexBufferRef()->Lock());
                glm::mat4x4 mCurrentWorldMatrix = pNode->Get_WorldMatrix();
                for(unsigned int j = 0; j < iCurrentNumVertexes; ++j)
                {
                    glm::vec4 vPosition = glm::vec4(pNodeVertexBufferData[j].m_vPosition.x, pNodeVertexBufferData[j].m_vPosition.y, pNodeVertexBufferData[j].m_vPosition.z, 1.0f);
                    vPosition = vPosition * mCurrentWorldMatrix;
                    pVertexBufferData[iNumVertexesOffset].m_vPosition = glm::vec3(vPosition.x, vPosition.y, vPosition.z);
                    pVertexBufferData[iNumVertexesOffset].m_vTexcoord = pNodeVertexBufferData[j].m_vTexcoord;
                    pVertexBufferData[iNumVertexesOffset].m_vColor = pNodeVertexBufferData[j].m_vColor;
                    iNumVertexesOffset++;
                }
                
                unsigned short* pNodeIndexBufferData = m_pMesh->Get_IndexBufferRef()->Get_SourceData();
                unsigned int iCurrentNumIndexes = pNode->Get_Mesh()->Get_NumIndexes();
                for(unsigned int j = 0; j < iCurrentNumIndexes; ++j)
                {
                    pIndexBufferData[iNumIndexesOffset] = pNodeIndexBufferData[j];
                    iNumIndexesOffset++;
                }
            }
            
            m_pMesh->Get_VertexBufferRef()->Commit();
            m_pMesh->Get_IndexBufferRef()->Commit();
        }
            break;
        case E_BATCH_MODE_SPRITE:
        {
            
        }
            break;
        case E_BATCH_MODE_SPRITE_CROSS:
        {
            
        }
            break;
        default:
            break;
    }
}

void CBatch::Render(CShader::E_RENDER_MODE _eMode)
{
    switch (m_eMode)
    {
        case E_BATCH_MODE_MODEL:
            _RenderBatchModeModel(_eMode);
            break;
        case E_BATCH_MODE_PARTICLE_EMITTER:
            _RenderBatchModeParticleEmitter(_eMode);
            break;
        case E_BATCH_MODE_SPRITE:
            _RenderBatchModeSprite(_eMode);
            break;
        case E_BATCH_MODE_SPRITE_CROSS:
            _RenderBatchModeSpriteCross(_eMode);
            break;
        default:
            break;
    }
}

void CBatch::_RenderBatchModeModel(CShader::E_RENDER_MODE _eMode)
{
    
}

void CBatch::_RenderBatchModeParticleEmitter(CShader::E_RENDER_MODE _eMode)
{
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    switch (_eMode)
    {
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }
            
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            m_pShaders[_eMode]->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                m_pShaders[_eMode]->Set_Texture(m_pTextures[i]->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                m_pShaders[_eMode]->Set_Texture(m_pTextures[i]->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        default:
            break;
    }
    
    m_iNumIndexes = 0;
    m_pMesh->Get_VertexBufferRef()->Enable(_eMode);
    m_pMesh->Get_IndexBufferRef()->Enable();
    //glDrawElements(GL_TRIANGLES, m_iNumIndexes, GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
    m_pShaders[_eMode]->Disable();
}

void CBatch::_RenderBatchModeSprite(CShader::E_RENDER_MODE _eMode)
{
    
}

void CBatch::_RenderBatchModeSpriteCross(CShader::E_RENDER_MODE _eMode)
{
    
}






