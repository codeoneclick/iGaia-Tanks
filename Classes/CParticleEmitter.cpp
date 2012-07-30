//
//  CParticleEmitter.cpp
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CParticleEmitter.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoordColor.h"
#include "CTimer.h"

CParticleEmitter::CParticleEmitter(void)
{
    m_iNumParticles = k_DEFAULT_NUM_PARTICLES;
    m_pParticles = NULL;
    
    m_bIsRepeat = false;
    m_bIsDead = false;
    m_bIsStop = true;
}

CParticleEmitter::~CParticleEmitter(void)
{
    std::cout<<"[CParticleEmitter::~CParticleEmitter] delete"<<std::endl;
    SAFE_DELETE_ARRAY(m_pParticles);
}

void CParticleEmitter::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = m_iNumParticles * 4;
    pSourceData->m_iNumIndexes  = m_iNumParticles * 6;
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordColor(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
    CVertexBufferPositionTexcoordColor::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordColor::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    
    m_pParticles = new SParticle[m_iNumParticles];
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        m_pParticles[index].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vColor = glm::u8vec4(255, 255, 255, 255);
        m_pParticles[index].m_iLifeTime = 0;
        m_pParticles[index].m_vSize = m_vMinSize;
        m_pParticles[index].m_bIsDead = false;
        m_pParticles[index].m_iLifeTime = _Get_RandomFromRange(m_iMinLifeTime, m_iMaxLifeTime);
        m_pParticles[index].m_iTimeStamp = 0;
        
        pVertexBufferData[index * 4 + 0].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        pVertexBufferData[index * 4 + 1].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        pVertexBufferData[index * 4 + 2].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);
        pVertexBufferData[index * 4 + 3].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);
        
        pVertexBufferData[index * 4 + 0].m_vTexcoord = glm::vec2( 0.0f,  0.0f);
        pVertexBufferData[index * 4 + 1].m_vTexcoord = glm::vec2( 1.0f,  0.0f);
        pVertexBufferData[index * 4 + 2].m_vTexcoord = glm::vec2( 1.0f,  1.0f);
        pVertexBufferData[index * 4 + 3].m_vTexcoord = glm::vec2( 0.0f,  1.0f);
        
        pVertexBufferData[index * 4 + 0].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 1].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 2].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 3].m_vColor = m_pParticles[index].m_vColor;
    }
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        pIndexBufferData[index * 6 + 0] = static_cast<unsigned short>(index * 4 + 0);
        pIndexBufferData[index * 6 + 1] = static_cast<unsigned short>(index * 4 + 1);
        pIndexBufferData[index * 6 + 2] = static_cast<unsigned short>(index * 4 + 2);
        
        pIndexBufferData[index * 6 + 3] = static_cast<unsigned short>(index * 4 + 0);
        pIndexBufferData[index * 6 + 4] = static_cast<unsigned short>(index * 4 + 2);
        pIndexBufferData[index * 6 + 5] = static_cast<unsigned short>(index * 4 + 3);
    }
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    m_pMesh->Set_Name("emitter");
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, true);
    m_pMaterial->Set_CullFace(GL_FRONT);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE);
}

float CParticleEmitter::_Get_RandomFromRange(float _fMin, float _fMax)
{
    float fRange = _fMax - _fMin;
    return _fMin + float(fRange * rand() / (RAND_MAX + 1.0f)); 
}

void CParticleEmitter::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
{
    switch (_eType)
    {
        case IResource::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        case IResource::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CParticleEmitter::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CParticleEmitter::Reset(void)
{
    m_bIsDead = false;
    int iCurrentTimeStamp = CTimer::Instance()->Get_TickCount();
    for(unsigned int i = 0; i < m_iNumParticles; ++i)
    {
        m_pParticles[i].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[i].m_vSize = m_vMinSize;
        m_pParticles[i].m_vColor.a = 255;
        m_pParticles[i].m_bIsDead = false;
        m_pParticles[i].m_iTimeStamp = iCurrentTimeStamp;
    }
}

void CParticleEmitter::Update(void)
{
    if(m_bIsDead)
    {
        return;
    }
    
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 vPositionCached = m_vPosition;
    m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    INode::Update();
    m_vPosition = vPositionCached;
    
    CVertexBufferPositionTexcoordColor::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordColor::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
   
    m_iNumDeadParticles = 0;
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        if(m_pParticles[index].m_bIsDead)
        {
            m_iNumDeadParticles++;
            continue;
        }
        
        glm::mat4x4 mWorld = pCamera->Get_BillboardSphericalMatrix(m_pParticles[index].m_vPosition + vPositionCached);
                
        glm::vec4 vTransform = glm::vec4(-m_pParticles[index].m_vSize.x, -m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 0].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
       
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, -m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 1].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 2].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(-m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 3].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        pVertexBufferData[index * 4 + 0].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 1].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 2].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 3].m_vColor = m_pParticles[index].m_vColor;
    }
    m_pMesh->Get_VertexBufferRef()->Commit();
    
    if(m_iNumDeadParticles == m_iNumParticles && !m_bIsRepeat && !m_bIsStop)
    {
        m_bIsDead = true;
    }
}

void CParticleEmitter::Render(CShader::E_RENDER_MODE _eMode)
{
    if(m_bIsDead)
    {
        return;
    }
    
    if(CSceneMgr::Instance()->Get_Frustum()->IsPointInFrustum(m_vPosition) == CFrustum::E_FRUSTUM_RESULT_OUTSIDE)
    {
        return;
    }
    
    INode::Render(_eMode);
    
    /*if(m_bIsBatching)
    {
        CSceneMgr::Instance()->Get_BatchMgr()->Push(this, CBatch::E_BATCH_MODE_PARTICLE_EMITTER);
        return;
    }*/
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    CShader* pShader = m_pMaterial->Get_Shader(_eMode);
    
    m_pMaterial->Commit(_eMode);
    
    switch (_eMode)
    {
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }

            pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == NULL)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            
            pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == NULL)
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
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
}



