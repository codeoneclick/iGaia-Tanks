//
//  CLandscapeEdges.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/11/12.
//
//

#include "CLandscapeEdges.h"
#include "CSceneMgr.h"
#include "CHeightMapSetter.h"
#include "CVertexBufferPositionTexcoord.h"

CLandscapeEdges* CLandscapeEdges::m_pInstance = nullptr;

CLandscapeEdges* CLandscapeEdges::Instance(void)
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new CLandscapeEdges();
        m_pInstance->_Load(nullptr);
    }
    return m_pInstance;
}

CLandscapeEdges::CLandscapeEdges(void)
{
    m_iWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    m_iHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    m_vHeight = glm::vec2(-8.0f, 8.0f);
}

CLandscapeEdges::~CLandscapeEdges(void)
{
    m_pInstance = nullptr;
}

void CLandscapeEdges::_Load(void *data)
{
    CVertexBufferPositionTexcoord* pVertexBuffer = new CVertexBufferPositionTexcoord(16, GL_STATIC_DRAW);
    
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pVertexBuffer->Lock());
    
    glm::vec3 m_vMin = glm::vec3(0.0f, m_vHeight.x, 0.0f);
    glm::vec3 m_vMax = glm::vec3((m_iWidth - 1), m_vHeight.y, (m_iHeight - 1));
    
    pVertexBufferData[0].m_vPosition = glm::vec3(m_vMin.x,  m_vMin.y, m_vMax.z);
    pVertexBufferData[1].m_vPosition = glm::vec3(m_vMax.x,  m_vMin.y, m_vMax.z);
    pVertexBufferData[2].m_vPosition = glm::vec3(m_vMax.x,  m_vMax.y, m_vMax.z);
    pVertexBufferData[3].m_vPosition = glm::vec3(m_vMin.x,  m_vMax.y, m_vMax.z);
    pVertexBufferData[4].m_vPosition = glm::vec3(m_vMin.x,  m_vMin.y,  m_vMin.z);
    pVertexBufferData[5].m_vPosition = glm::vec3(m_vMin.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[6].m_vPosition = glm::vec3(m_vMax.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[7].m_vPosition = glm::vec3(m_vMax.x,  m_vMin.y,  m_vMin.z);
    
    pVertexBufferData[8].m_vPosition = glm::vec3(m_vMax.x,  m_vMin.y,   m_vMax.z);
    pVertexBufferData[9].m_vPosition = glm::vec3(m_vMax.x,  m_vMin.y,   m_vMin.z);
    pVertexBufferData[10].m_vPosition = glm::vec3(m_vMax.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[11].m_vPosition = glm::vec3(m_vMax.x,  m_vMax.y,  m_vMax.z);
    
    pVertexBufferData[12].m_vPosition = glm::vec3(m_vMin.x,  m_vMin.y,  m_vMin.z);
    pVertexBufferData[13].m_vPosition = glm::vec3(m_vMin.x,  m_vMin.y,  m_vMax.z);
    pVertexBufferData[14].m_vPosition = glm::vec3(m_vMin.x,  m_vMax.y,  m_vMax.z);
    pVertexBufferData[15].m_vPosition = glm::vec3(m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    pVertexBufferData[0].m_vTexcoord = glm::vec2(0.0f, 1.0f / 4.0f);
    pVertexBufferData[1].m_vTexcoord = glm::vec2(1.0f - 0.001f, 1.0f / 4.0f);
    pVertexBufferData[2].m_vTexcoord = glm::vec2(1.0f - 0.001f, (1.0f / 4.0f) * 2.0f - 0.001f);
    pVertexBufferData[3].m_vTexcoord = glm::vec2(0.0f, (1.0f / 4.0f) * 2.0f - 0.001f);
    
    pVertexBufferData[4].m_vTexcoord = glm::vec2(1.0f - 0.001f, 0.0f);
    pVertexBufferData[5].m_vTexcoord = glm::vec2(1.0f - 0.001f, 1.0f / 4.0f - 0.001f);
    pVertexBufferData[6].m_vTexcoord = glm::vec2(0.0f, 1.0f / 4.0f - 0.001f);
    pVertexBufferData[7].m_vTexcoord = glm::vec2(0.0f, 0.0f);
    
    pVertexBufferData[8].m_vTexcoord =  glm::vec2(0.0f, (1.0f / 4.0f) * 3.0f);
    pVertexBufferData[9].m_vTexcoord =  glm::vec2(1.0f - 0.001f, (1.0f / 4.0f) * 3.0f);
    pVertexBufferData[10].m_vTexcoord = glm::vec2(1.0f - 0.001f, 1.0f - 0.001f);
    pVertexBufferData[11].m_vTexcoord = glm::vec2(0.0f, 1.0f - 0.001f);
    
    pVertexBufferData[12].m_vTexcoord = glm::vec2(0.0f, (1.0f / 4.0f) * 2.0f);
    pVertexBufferData[13].m_vTexcoord = glm::vec2(1.0f - 0.001f, (1.0f / 4.0f) * 2.0f);
    pVertexBufferData[14].m_vTexcoord = glm::vec2(1.0f - 0.001f, (1.0f / 4.0f) * 3.0f - 0.001f);
    pVertexBufferData[15].m_vTexcoord = glm::vec2(0.0f, (1.0f / 4.0f) * 3.0f - 0.001f);
    
    CIndexBuffer* pIndexBuffer = new CIndexBuffer(24, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pIndexBuffer->Get_SourceData();
    
    pIndexBufferData[0] = 0;
    pIndexBufferData[1] = 1;
    pIndexBufferData[2] = 2;
    pIndexBufferData[3] = 0;
    pIndexBufferData[4] = 2;
    pIndexBufferData[5] = 3;
    
    pIndexBufferData[6] = 4;
    pIndexBufferData[7] = 5;
    pIndexBufferData[8] = 6;
    pIndexBufferData[9] = 4;
    pIndexBufferData[10] = 6;
    pIndexBufferData[11] = 7;
    
    pIndexBufferData[12] = 8;
    pIndexBufferData[13] = 9;
    pIndexBufferData[14] = 10;
    pIndexBufferData[15] = 8;
    pIndexBufferData[16] = 10;
    pIndexBufferData[17] = 11;
    
    pIndexBufferData[18] = 12;
    pIndexBufferData[19] = 13;
    pIndexBufferData[20] = 14;
    pIndexBufferData[21] = 12;
    pIndexBufferData[22] = 14;
    pIndexBufferData[23] = 15;
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_VertexBufferRef(pVertexBuffer);
    m_pMesh->Set_IndexBufferRef(pIndexBuffer);
    m_pMesh->Get_VertexBufferRef()->Commit();
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, true);
    m_pMaterial->Set_CullFace(GL_BACK);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glm::vec2 vScaleFactor = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_ScaleFactor();
    Set_Scale(glm::vec3(vScaleFactor.x, 1.0f, vScaleFactor.y));
}

/*void CLandscapeEdges::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}*/

void CLandscapeEdges::Update(void)
{
    INode::Update();
    m_vTexCoordOffset.x += 0.05f;
    if(m_vTexCoordOffset.x >= 1.0f)
    {
        m_vTexCoordOffset.x = 0.0f;
    }
}

void CLandscapeEdges::Render(CShader::E_RENDER_MODE _eMode)
{
    if(!m_pMaterial->Check_RenderMode(_eMode))
    {
        std::cout<<"[CSkyBox::Render] Render mode incorrect"<<std::endl;
        return;
    }
    
    INode::Render(_eMode);
    
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
            
            pShader->Set_Matrix4x4(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            pShader->Set_Vector2(m_vTexCoordOffset, CShader::E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == NULL)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
            pShader->Set_Texture(CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_TextureEdgesMask(), CShader::E_TEXTURE_SLOT_03);
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
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_IndexBufferRef()->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
}




