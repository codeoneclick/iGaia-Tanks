//
//  CDecal.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#include "CDecal.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoord.h"

glm::mat3x3 CDecal::m_mTextureTranslation = glm::mat3x3(1.0f, 0.0f, 0.5f,
                                                        0.0f, 1.0f, 0.5f,
                                                        0.0f, 0.0f, 1.0f);

glm::mat3x3 CDecal::m_mTextureScale = glm::mat3x3(0.5f, 0.0f, 0.0f,
                                                  0.0f, 0.5f, 0.0f,
                                                  0.0f, 0.0f, 1.0f);

CDecal::CDecal(void)
{
    m_vColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

CDecal::~CDecal(void)
{
    
}

void CDecal::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    unsigned int iWidth = 7;
    unsigned int iHeight = 7;
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = iWidth * iHeight;
    pSourceData->m_iNumIndexes  = (iWidth - 1) * (iHeight - 1) * 6;
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
    
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    
    //glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->GetOrCreate_PositionSourceData();
    //glm::vec2* pTexCoordData = pSourceData->m_pVertexBuffer->GetOrCreate_TexcoordSourceData();
    
    //memset(pPositionData, 0x0, pSourceData->m_iNumVertexes * sizeof(glm::vec3));
    
    unsigned int index = 0;
    float fScale = 0.25f;
    for(unsigned int i = 0; i < iWidth; ++i)
    {
        for(unsigned int j = 0; j < iHeight; ++j)
        {
            pVertexBufferData[index].m_vPosition = glm::vec3(static_cast<float>(i) * fScale - 2.0f, 0.0f, static_cast<float>(j) * fScale - 2.0f);
            pVertexBufferData[index].m_vTexcoord = glm::vec2(static_cast<float>(i) / static_cast<float>(iWidth), static_cast<float>(j) / static_cast<float>(iHeight));
            ++index;
        }
    }
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    index = 0;
    for(unsigned int i = 0; i < (iWidth - 1); ++i)
    {
        for(unsigned int j = 0; j < (iHeight - 1); ++j)
        {
            pIndexBufferData[index] = i + j * iWidth;
            index++;
            pIndexBufferData[index] = i + (j + 1) * iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + j * iWidth;
            index++;
            
            pIndexBufferData[index] = i + (j + 1) * iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + (j + 1) * iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + j * iWidth;
            index++;
        }
    }
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, true);
    m_pMaterial->Set_CullFace(GL_FRONT);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CDecal::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CDecal::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CDecal::Update()
{
    //INode::Update();
    /*unsigned int iWidth = 8;
    unsigned int iHeight = 8;
    glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    unsigned int index = 0;
    for(unsigned int i = 0; i < iWidth; ++i)
    {
        for(unsigned int j = 0; j < iHeight; ++j)
        {
            pPositionData[index].y = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x + pPositionData[index].x, m_vPosition.z + pPositionData[index].z) + 0.05f;
            ++index;
        }
    }*/
    
    int iRoundPositionX = m_vPosition.x;
    int iRoundPositionZ = m_vPosition.z;
    CHeightMapSetter* pMapSetter = CSceneMgr::Instance()->Get_HeightMapSetterRef();
    float* pHeightmapData = NULL;
    if(pMapSetter != NULL)
    {
        pHeightmapData = pMapSetter->Get_SourceData();
    }
    else
    {
        return;
    }
    
    unsigned int index = 0;
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    //glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->GetOrCreate_PositionSourceData();
    int iHeightmapWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    int iHeightmapHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    for(int i = -3; i <= 3; ++i)
    {
        for(int j = -3; j <= 3; ++j)
        {
            if((iRoundPositionX + i) < 0 || (iRoundPositionZ + j) < 0 || (iRoundPositionX + i) >= iHeightmapWidth || (iRoundPositionZ +j) > iHeightmapHeight)
            {
                pVertexBufferData[index].m_vPosition.x = iRoundPositionX;
                pVertexBufferData[index].m_vPosition.y = pHeightmapData[iRoundPositionX + iRoundPositionZ * iHeightmapWidth] + 0.1f;
                pVertexBufferData[index].m_vPosition.z = iRoundPositionZ;
            }
            else
            {
                pVertexBufferData[index].m_vPosition.x = iRoundPositionX + i;
                pVertexBufferData[index].m_vPosition.y = pHeightmapData[iRoundPositionX + i + (iRoundPositionZ + j) * iHeightmapWidth] + 0.1f;
                pVertexBufferData[index].m_vPosition.z = iRoundPositionZ + j;
            }
            index++;
        }
    }
    
    m_mTextureRotation = glm::mat3x3(cosf(glm::radians(m_vRotation.y)), -sinf(glm::radians(m_vRotation.y)), 0.0,
                                     sinf(glm::radians(m_vRotation.y)),  cosf(glm::radians(m_vRotation.y)), 0.0,
                                      0.0           ,  0.0           , 1.0);
    
    m_mTexture = m_mTextureScale * m_mTextureRotation * m_mTextureTranslation;
    
    m_pMesh->Get_VertexBufferRef()->Commit();
}

void CDecal::Render(CShader::E_RENDER_MODE _eMode)
{
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
            pShader->Set_CustomVector3(m_vPosition, "EXT_Center");
            pShader->Set_CustomMatrix3x3(m_mTexture, "EXT_MATRIX_TEXTURE");
            pShader->Set_CustomVector4(m_vColor, "EXT_Color");
            
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
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable(_eMode);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
}


