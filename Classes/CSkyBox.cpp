//
//  CSkyBox.cpp
//  iGaia
//
//  Created by sergey sergeev on 4/26/12.
//
//

#include "CSkyBox.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoord.h"

CSkyBox::CSkyBox(void)
{

}

CSkyBox::~CSkyBox(void)
{
    
}

void CSkyBox::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{     
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = 24;
    pSourceData->m_iNumIndexes  = 36;
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
    
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    
    //glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->GetOrCreate_PositionSourceData();
    //glm::vec2* pTexCoordData = pSourceData->m_pVertexBuffer->GetOrCreate_TexcoordSourceData();
    
    glm::vec3 m_vMin = glm::vec3( -1.0f, -1.0f, -1.0f);
    glm::vec3 m_vMax = glm::vec3(  1.0f,  1.0f,  1.0f);
    
    // Front
    pVertexBufferData[0].m_vPosition = glm::vec3( m_vMin.x,  m_vMin.y, m_vMax.z);
    pVertexBufferData[1].m_vPosition = glm::vec3( m_vMax.x,  m_vMin.y, m_vMax.z);
    pVertexBufferData[2].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y, m_vMax.z);
    pVertexBufferData[3].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y, m_vMax.z);
    // Back
    pVertexBufferData[4].m_vPosition = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pVertexBufferData[5].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[6].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[7].m_vPosition = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    // Left
    pVertexBufferData[8].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[9].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pVertexBufferData[10].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pVertexBufferData[11].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right
    pVertexBufferData[12].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[13].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[14].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pVertexBufferData[15].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    // Top
    pVertexBufferData[16].m_vPosition = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pVertexBufferData[17].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pVertexBufferData[18].m_vPosition = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pVertexBufferData[19].m_vPosition = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pVertexBufferData[20].m_vPosition = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pVertexBufferData[21].m_vPosition = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pVertexBufferData[22].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pVertexBufferData[23].m_vPosition = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    // Front
    pVertexBufferData[0].m_vTexcoord = glm::vec2(0.0f, 0.0f);
    pVertexBufferData[1].m_vTexcoord = glm::vec2(1.0f, 0.0f);
    pVertexBufferData[2].m_vTexcoord = glm::vec2(1.0f, 1.0f);
    pVertexBufferData[3].m_vTexcoord = glm::vec2(0.0f, 1.0f);
    // Back
    pVertexBufferData[4].m_vTexcoord = glm::vec2(1.0f, 0.0f);
    pVertexBufferData[5].m_vTexcoord = glm::vec2(1.0f, 1.0f);
    pVertexBufferData[6].m_vTexcoord = glm::vec2(0.0f, 1.0f);
    pVertexBufferData[7].m_vTexcoord = glm::vec2(0.0f, 0.0f);
    // Left
    pVertexBufferData[8].m_vTexcoord = glm::vec2(1.0f, 0.0f);
    pVertexBufferData[9].m_vTexcoord = glm::vec2(1.0f, 1.0f);
    pVertexBufferData[10].m_vTexcoord = glm::vec2(0.0f, 1.0f);
    pVertexBufferData[11].m_vTexcoord = glm::vec2(0.0f, 0.0f);
    // Right
    pVertexBufferData[12].m_vTexcoord = glm::vec2(0.0f, 0.0f);
    pVertexBufferData[13].m_vTexcoord = glm::vec2(1.0f, 0.0f);
    pVertexBufferData[14].m_vTexcoord = glm::vec2(1.0f, 1.0f);
    pVertexBufferData[15].m_vTexcoord = glm::vec2(0.0f, 1.0f);
    // Top
    pVertexBufferData[16].m_vTexcoord = glm::vec2(1.0f, 0.0f);
    pVertexBufferData[17].m_vTexcoord = glm::vec2(1.0f, 1.0f);
    pVertexBufferData[18].m_vTexcoord = glm::vec2(0.0f, 1.0f);
    pVertexBufferData[19].m_vTexcoord = glm::vec2(0.0f, 0.0f);
    // Bottom
    pVertexBufferData[20].m_vTexcoord = glm::vec2(0.0f, 0.0f);
    pVertexBufferData[21].m_vTexcoord = glm::vec2(1.0f, 0.0f);
    pVertexBufferData[22].m_vTexcoord = glm::vec2(1.0f, 1.0f);
    pVertexBufferData[23].m_vTexcoord = glm::vec2(0.0f, 1.0f);
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
    // Front
    pIndexBufferData[0] = 0;
    pIndexBufferData[1] = 1;
    pIndexBufferData[2] = 2;
    pIndexBufferData[3] = 0;
    pIndexBufferData[4] = 2;
    pIndexBufferData[5] = 3;
    // Back
    pIndexBufferData[6] = 4;
    pIndexBufferData[7] = 5;
    pIndexBufferData[8] = 6;
    pIndexBufferData[9] = 4;
    pIndexBufferData[10] = 6;
    pIndexBufferData[11] = 7;
    // Left
    pIndexBufferData[12] = 8;
    pIndexBufferData[13] = 9;
    pIndexBufferData[14] = 10;
    pIndexBufferData[15] = 8;
    pIndexBufferData[16] = 10;
    pIndexBufferData[17] = 11;
    // Right
    pIndexBufferData[18] = 12;
    pIndexBufferData[19] = 13;
    pIndexBufferData[20] = 14;
    pIndexBufferData[21] = 12;
    pIndexBufferData[22] = 14;
    pIndexBufferData[23] = 15;
    // Top
    pIndexBufferData[24] = 16;
    pIndexBufferData[25] = 17;
    pIndexBufferData[26] = 18;
    pIndexBufferData[27] = 16;
    pIndexBufferData[28] = 18;
    pIndexBufferData[29] = 19;
    // Bottom
    pIndexBufferData[30] = 20;
    pIndexBufferData[31] = 21;
    pIndexBufferData[32] = 22;
    pIndexBufferData[33] = 20;
    pIndexBufferData[34] = 22;
    pIndexBufferData[35] = 23;
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, false);
    m_pMaterial->Set_CullFace(GL_FRONT);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CSkyBox::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CSkyBox::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CSkyBox::Update()
{
    INode::Update();
}

void CSkyBox::Render(CShader::E_RENDER_MODE _eMode)
{
    if(!m_pMaterial->Check_RenderMode(_eMode))
    {
        std::cout<<"[CSkyBox::Render] Render mode incorrect"<<std::endl;
        return;
    }
    
    INode::Render(_eMode);
    
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
            if(pShader == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
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
        case CShader::E_RENDER_MODE_REFRACTION:
        {
            
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




