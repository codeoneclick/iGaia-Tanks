//
//  CSpriteCross.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CSpriteCross.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoord.h"

const int CSpriteCross::k_ELEMENT_NUM_INDEXES = 12;
const int CSpriteCross::k_ELEMENT_NUM_VERTEXES = 8;

CSpriteCross::CSpriteCross(void)
{
    m_vSize = glm::vec2(1.0f, 1.0f);
    m_iNumFrames = 0;
    m_iCurrentFrame = 0;
    m_bIsEnable = false;
}

CSpriteCross::~CSpriteCross(void)
{
    
}

void CSpriteCross::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = k_ELEMENT_NUM_VERTEXES;
    pSourceData->m_iNumIndexes  = k_ELEMENT_NUM_INDEXES;
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();

    pIndexBufferData[0] = 0;
    pIndexBufferData[1] = 1;
    pIndexBufferData[2] = 2;
    pIndexBufferData[3] = 2;
    pIndexBufferData[4] = 3;
    pIndexBufferData[5] = 1;
    
    pIndexBufferData[6]  = 4;
    pIndexBufferData[7]  = 5;
    pIndexBufferData[8]  = 6;
    pIndexBufferData[9]  = 6;
    pIndexBufferData[10] = 7;
    pIndexBufferData[11] = 5;
    
    pVertexBufferData[0].m_vPosition = glm::vec3(-m_vSize.y / 2.0f, 0.0f, -m_vSize.x / 2.0f);
    pVertexBufferData[1].m_vPosition = glm::vec3( m_vSize.y / 2.0f, 0.0f, -m_vSize.x / 2.0f);
    pVertexBufferData[2].m_vPosition = glm::vec3(-m_vSize.y / 2.0f, 0.0f,  m_vSize.x / 2.0f);
    pVertexBufferData[3].m_vPosition = glm::vec3( m_vSize.y / 2.0f, 0.0f,  m_vSize.x / 2.0f);
    
    pVertexBufferData[4].m_vPosition = glm::vec3(0.0f,-m_vSize.y / 2.0f,-m_vSize.x / 2.0f);
    pVertexBufferData[5].m_vPosition = glm::vec3(0.0f, m_vSize.y / 2.0f,-m_vSize.x / 2.0f);
    pVertexBufferData[6].m_vPosition = glm::vec3(0.0f,-m_vSize.y / 2.0f, m_vSize.x / 2.0f);
    pVertexBufferData[7].m_vPosition = glm::vec3(0.0f, m_vSize.y / 2.0f, m_vSize.x / 2.0f);
    
    pVertexBufferData[0].m_vTexcoord = glm::vec2(0.0f,1.0f);
    pVertexBufferData[1].m_vTexcoord = glm::vec2(0.0f,0.0f);
    pVertexBufferData[2].m_vTexcoord = glm::vec2(1.0f,1.0f);
    pVertexBufferData[3].m_vTexcoord = glm::vec2(1.0f,0.0f);
    
    pVertexBufferData[4].m_vTexcoord = glm::vec2(0.0f,1.0f);
    pVertexBufferData[5].m_vTexcoord = glm::vec2(0.0f,0.0f);
    pVertexBufferData[6].m_vTexcoord = glm::vec2(1.0f,1.0f);
    pVertexBufferData[7].m_vTexcoord = glm::vec2(1.0f,0.0f);
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    
    m_pSequence = new SFrame[m_iNumFrames];
    
    unsigned int m_iNumX = m_vSizeAtlas.x / m_vSizeFrame.x;
    unsigned int m_iNumY = m_vSizeAtlas.y / m_vSizeFrame.y;
    
    unsigned int index = 0;
    for(unsigned int i = 0; i < m_iNumX; ++i)
    {
        for(unsigned int j = 0; j < m_iNumY; ++j)
        {
            if(index > m_iNumFrames)
            {
                continue;
            }
            
            m_pSequence[index].m_vTexcoord[0].x = (m_vSizeFrame.x * i) / m_vSizeAtlas.x;
            m_pSequence[index].m_vTexcoord[0].y = (m_vSizeFrame.y * (j + 1)) / m_vSizeAtlas.y;
            
            m_pSequence[index].m_vTexcoord[1].x = (m_vSizeFrame.x * i) / m_vSizeAtlas.x;
            m_pSequence[index].m_vTexcoord[1].y = (m_vSizeFrame.y * j) / m_vSizeAtlas.y;
            
            m_pSequence[index].m_vTexcoord[2].x = (m_vSizeFrame.x * (i + 1)) / m_vSizeAtlas.x;
            m_pSequence[index].m_vTexcoord[2].y = (m_vSizeFrame.y * (j + 1)) / m_vSizeAtlas.y;
            
            m_pSequence[index].m_vTexcoord[3].x = (m_vSizeFrame.x * (i + 1)) / m_vSizeAtlas.x;
            m_pSequence[index].m_vTexcoord[3].y = (m_vSizeFrame.y * j) / m_vSizeAtlas.y;
            
            index++;
        }
    }
}

void CSpriteCross::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CSpriteCross::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CSpriteCross::Enable(void)
{
    if(!m_bIsEnable)
    {
        m_iCurrentFrame = 0;
    }
    m_bIsEnable = true;
}

void CSpriteCross::Disable(void)
{
    m_bIsEnable = false;
}

void CSpriteCross::Update(void)
{
    if(!m_bIsEnable)
    {
        return;
    }
    
    INode::Update();
    
    m_iCurrentFrame++;
    if(m_iCurrentFrame >= m_iNumFrames)
    {
        m_iCurrentFrame = 0;
    }
    
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    
    pVertexBufferData[0].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[0];
    pVertexBufferData[1].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[1];
    pVertexBufferData[2].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[2];
    pVertexBufferData[3].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[3];
    
    pVertexBufferData[4].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[0];
    pVertexBufferData[5].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[1];
    pVertexBufferData[6].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[2];
    pVertexBufferData[7].m_vTexcoord = m_pSequence[m_iCurrentFrame].m_vTexcoord[3];
    
    m_pMesh->Get_VertexBufferRef()->Commit();
}

void CSpriteCross::Render(CShader::E_RENDER_MODE _eMode)
{
    if(CSceneMgr::Instance()->Get_Frustum()->IsPointInFrustum(m_vPosition) == CFrustum::E_FRUSTUM_RESULT_OUTSIDE)
    {
        return;
    }
    
    if(!m_bIsEnable)
    {
        return;
    }
    
    INode::Render(_eMode);
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    CShader* pShader = m_pMaterial->Get_Shader(_eMode);
    
    switch (_eMode)
    {
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CCrossBoxEffect::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }
            
            pShader->Enable();
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
        case CShader::E_RENDER_MODE_REFLECTION:
        {
            
        }
            break;
        case CShader::E_RENDER_MODE_REFRACTION:
        {
            
        }
            break;
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CCrossBoxEffect::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            
            pShader->Enable();
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
    unsigned int iNumIndexes = m_pMesh->Get_IndexBufferRef()->Get_NumWorkingIndexes();
    glDrawElements(GL_TRIANGLES, iNumIndexes, GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
    pShader->Disable();
}





