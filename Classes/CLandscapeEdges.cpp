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

CLandscapeEdges::CLandscapeEdges(void)
{

}

CLandscapeEdges::~CLandscapeEdges(void)
{
    
}

void CLandscapeEdges::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    m_pMesh = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_LandscapeEdgesMesh();
    m_pMesh->Get_VertexBufferRef()->Commit();
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, true);
    m_pMaterial->Set_CullFace(GL_BACK);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CLandscapeEdges::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CLandscapeEdges::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CLandscapeEdges::Update(void)
{
    INode::Update();
}

void CLandscapeEdges::Render(CShader::E_RENDER_MODE _eMode)
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




