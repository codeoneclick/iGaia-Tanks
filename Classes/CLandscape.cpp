//
//  CLandscape.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLandscape.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CVertexBufferPositionTexcoordNormalTangent.h"

CLandscape::CLandscape(void)
{
    m_iWidth = 64;
    m_iHeight = 64;
    m_pHeightMapSetter = NULL;
}

CLandscape::~CLandscape(void)
{
    SAFE_DELETE(m_pQuadTree);
    SAFE_DELETE(m_pHeightMapSetter);
    CSceneMgr::Instance()->Set_HeightMapSetterRef(NULL);
}

void CLandscape::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    m_pHeightMapSetter = new CHeightMapSetter();
    m_pMesh = m_pHeightMapSetter->Load_DataSource(_sName, m_iWidth, m_iHeight);
    
    CSceneMgr::Instance()->Set_HeightMapSetterRef(m_pHeightMapSetter);
    
    m_pMesh->Get_VertexBufferRef()->Commit();
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    unsigned short* pIndexBufferData = m_pMesh->Get_IndexBufferRef()->Get_SourceData();
    unsigned int iNumIndexes = m_pMesh->Get_IndexBufferRef()->Get_NumIndexes();
    
    m_pWorkingIndexesSourceDataRef = m_pMesh->Get_IndexBufferRef()->Get_WorkingSourceDataRef();
    m_iWorkingNumIndexes = 0;
    
    m_pQuadTree = new SQuadTreeNode();
    m_pQuadTree->m_pParent = NULL;
    m_pQuadTree->m_vMaxBound = glm::vec3(m_iWidth, 64.0f, m_iHeight);
    m_pQuadTree->m_vMinBound = glm::vec3(0.0f, -64.0f, 0.0f);
    m_pQuadTree->m_iNumIndexes = iNumIndexes;
    m_pQuadTree->m_pIndexes = static_cast<unsigned short*>(malloc(m_pQuadTree->m_iNumIndexes * sizeof(unsigned short)));
    m_pQuadTree->m_pIndexesId = static_cast<unsigned short*>(malloc(m_pQuadTree->m_iNumIndexes * sizeof(unsigned short)));
    memcpy(m_pQuadTree->m_pIndexes , pIndexBufferData, m_pQuadTree->m_iNumIndexes * sizeof(unsigned short));
    memset(m_pQuadTree->m_pIndexesId, 0x0, m_pQuadTree->m_iNumIndexes * sizeof(unsigned short));
    _CreateQuadTreeNode(m_iWidth, m_pQuadTree);
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, false);
    m_pMaterial->Set_CullFace(GL_FRONT);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CLandscape::_CreateQuadTreeNode(int _iSize, CLandscape::SQuadTreeNode *_pParentNode)
{
    static int iRecurseCount = 0;
    iRecurseCount++;
    std::cout<<"[CLandscape::_CreateQuadTreeNode] Recurse Count : "<<iRecurseCount<<std::endl;
    if(_iSize <= 2)
    {
        return;
    }
    
    _pParentNode->m_pChilds = new SQuadTreeNode*[k_MAX_QUADTREE_CHILDREN];
    
    _pParentNode->m_pChilds[0] = new SQuadTreeNode();
    _pParentNode->m_pChilds[0]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[0]->m_vMinBound = glm::vec3(_pParentNode->m_vMinBound.x, _pParentNode->m_vMinBound.y, _pParentNode->m_vMinBound.z );
    _pParentNode->m_pChilds[0]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[0]);
    
    _pParentNode->m_pChilds[1] = new SQuadTreeNode();
    _pParentNode->m_pChilds[1]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[1]->m_vMinBound = glm::vec3(_pParentNode->m_vMinBound.x, _pParentNode->m_vMinBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _pParentNode->m_pChilds[1]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[1]);
    
    _pParentNode->m_pChilds[2] = new SQuadTreeNode();
    _pParentNode->m_pChilds[2]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[2]->m_vMinBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMinBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _pParentNode->m_pChilds[2]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[2]);
    
    _pParentNode->m_pChilds[3] = new SQuadTreeNode();
    _pParentNode->m_pChilds[3]->m_pParent = _pParentNode;
    _pParentNode->m_pChilds[3]->m_vMinBound = glm::vec3(_pParentNode->m_vMaxBound.x / 2.0f, _pParentNode->m_vMinBound.y, _pParentNode->m_vMinBound.z);
    _pParentNode->m_pChilds[3]->m_vMaxBound = glm::vec3(_pParentNode->m_vMaxBound.x, _pParentNode->m_vMaxBound.y, _pParentNode->m_vMaxBound.z / 2.0f);
    _CreateIndexBufferRefForQuadTreeNode(_pParentNode->m_pChilds[3]);
    
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[0]);
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[1]);
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[2]);
    _CreateQuadTreeNode(_iSize / 2, _pParentNode->m_pChilds[3]);
}

void CLandscape::_CreateIndexBufferRefForQuadTreeNode(CLandscape::SQuadTreeNode *_pNode)
{
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    unsigned int iParentNumIndexes = _pNode->m_pParent->m_iNumIndexes;
    _pNode->m_pIndexes = static_cast<unsigned short*>(malloc(sizeof(unsigned short)));
    float fMaxY = -4096.0f;
    float fMinY =  4096.0f;
    
    unsigned int iQuadTreeNodeId = 0;
    CLandscape::SQuadTreeNode* pParentNode = _pNode->m_pParent;
    while (pParentNode != NULL)
    {
        iQuadTreeNodeId++;
        pParentNode = pParentNode->m_pParent;
    }
    
    for(unsigned int i = 0; i < iParentNumIndexes; i += 3)
    {
        if(_IsPointInBoundBox(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 0]].m_vPosition, _pNode->m_vMinBound, _pNode->m_vMaxBound) ||
           _IsPointInBoundBox(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 1]].m_vPosition, _pNode->m_vMinBound, _pNode->m_vMaxBound) ||
           _IsPointInBoundBox(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 2]].m_vPosition, _pNode->m_vMinBound, _pNode->m_vMaxBound))
        {
            
            if(_pNode->m_pParent->m_pIndexesId[i + 0] == iQuadTreeNodeId ||
               _pNode->m_pParent->m_pIndexesId[i + 1] == iQuadTreeNodeId ||
               _pNode->m_pParent->m_pIndexesId[i + 2] == iQuadTreeNodeId)
            {
                continue;
            }
            
            _pNode->m_iNumIndexes += 3;
            _pNode->m_pIndexes = static_cast<unsigned short*>(realloc(_pNode->m_pIndexes, sizeof(unsigned short) * _pNode->m_iNumIndexes));
            
            _pNode->m_pIndexes[_pNode->m_iNumIndexes - 3] = _pNode->m_pParent->m_pIndexes[i + 0];
            _pNode->m_pIndexes[_pNode->m_iNumIndexes - 2] = _pNode->m_pParent->m_pIndexes[i + 1];
            _pNode->m_pIndexes[_pNode->m_iNumIndexes - 1] = _pNode->m_pParent->m_pIndexes[i + 2];
            
            _pNode->m_pParent->m_pIndexesId[i + 0] = iQuadTreeNodeId;
            _pNode->m_pParent->m_pIndexesId[i + 1] = iQuadTreeNodeId;
            _pNode->m_pParent->m_pIndexesId[i + 2] = iQuadTreeNodeId;
            
            if(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 0]].m_vPosition.y > fMaxY)
            {
                fMaxY = pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 0]].m_vPosition.y;
            }
            
            if(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 1]].m_vPosition.y > fMaxY)
            {
                fMaxY = pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 1]].m_vPosition.y;
            }
            
            if(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 2]].m_vPosition.y > fMaxY)
            {
                fMaxY = pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 2]].m_vPosition.y;
            }
            
            if(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 0]].m_vPosition.y < fMinY)
            {
                fMinY = pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 0]].m_vPosition.y;
            }
            
            if(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 1]].m_vPosition.y < fMinY)
            {
                fMinY = pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 1]].m_vPosition.y;
            }
            
            if(pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 2]].m_vPosition.y < fMinY)
            {
                fMinY = pVertexBufferData[_pNode->m_pParent->m_pIndexes[i + 2]].m_vPosition.y;
            }
        }
    }
    _pNode->m_pIndexesId = static_cast<unsigned short*>(malloc(_pNode->m_iNumIndexes * sizeof(unsigned short)));
    memset(_pNode->m_pIndexesId, 0x0, _pNode->m_iNumIndexes * sizeof(unsigned short));
    _pNode->m_vMaxBound.y = fMaxY;
    _pNode->m_vMinBound.y = fMinY;
}

bool CLandscape::_IsPointInBoundBox(glm::vec3 _vPoint, glm::vec3 _vMinBound, glm::vec3 _vMaxBound)
{
    if(_vPoint.x >= _vMinBound.x &&
       _vPoint.x <= _vMaxBound.x &&
       _vPoint.y >= _vMinBound.y &&
       _vPoint.y <= _vMaxBound.y &&
       _vPoint.z >= _vMinBound.z &&
       _vPoint.z <= _vMaxBound.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CLandscape::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CLandscape::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
    
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pMesh->Get_VertexBufferRef(), m_pMesh->Get_IndexBufferRef(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CLandscape::OnTouchEvent] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Set_Touch3DPoint(vCollisionPoint);
    
    for(size_t index = 0; index< m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index]->Get_DelegateType() == IDelegate::E_DELEGATE_TYPE_TOUCH)
        {
            dynamic_cast<ITouchDelegate*>(m_lDelegateOwners[index])->OnTouchEvent(this);
        }
    }
}

void CLandscape::_CheckVisibleQuadTreeNode(CLandscape::SQuadTreeNode *_pNode)
{
    CFrustum* pFrustum = CSceneMgr::Instance()->Get_Frustum();
    if(_pNode->m_pChilds == NULL)
    {
        return;
    }
    
    for(unsigned int i = 0; i < k_MAX_QUADTREE_CHILDREN; i++)
    {
        int iResult = pFrustum->IsBoxInFrustum(_pNode->m_pChilds[i]->m_vMaxBound, _pNode->m_pChilds[i]->m_vMinBound);
        if(iResult == CFrustum::E_FRUSTUM_RESULT_INSIDE)
        {
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] QuadTreeNode Index : "<<i<<" E_FRUSTUM_RESULT_INSIDE"<<std::endl;
            memcpy(&m_pWorkingIndexesSourceDataRef[m_iWorkingNumIndexes], _pNode->m_pChilds[i]->m_pIndexes, sizeof(unsigned short) * _pNode->m_pChilds[i]->m_iNumIndexes);
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] Indexes Nun += "<<_pNode->m_pChilds[i]->m_iNumIndexes<<std::endl;
            m_iWorkingNumIndexes += _pNode->m_pChilds[i]->m_iNumIndexes;
        }
        else if(iResult == CFrustum::E_FRUSTUM_RESULT_INTERSECT)
        {
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] QuadTreeNode Index : "<<i<<" E_FRUSTUM_RESULT_INTERSECT"<<std::endl;
            if(_pNode->m_pChilds[i]->m_pChilds == NULL)
            {
                memcpy(&m_pWorkingIndexesSourceDataRef[m_iWorkingNumIndexes], _pNode->m_pChilds[i]->m_pIndexes, sizeof(unsigned short) * _pNode->m_pChilds[i]->m_iNumIndexes);
                //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] Indexes Nun += "<<_pNode->m_pChilds[i]->m_iNumIndexes<<std::endl;
                m_iWorkingNumIndexes += _pNode->m_pChilds[i]->m_iNumIndexes;
            }
            else
            {
                _CheckVisibleQuadTreeNode(_pNode->m_pChilds[i]);
            }
        }
        else if(iResult == CFrustum::E_FRUSTUM_RESULT_OUTSIDE)
        {
            //std::cout<<"[CLandscape::_CheckVisibleQuadTreeNode] QuadTreeNode Index : "<<i<<" E_FRUSTUM_RESULT_OUTSIDE"<<std::endl;
        }
    }
}

void CLandscape::Update(void)
{
    INode::Update();
    m_iWorkingNumIndexes = 0;
    _CheckVisibleQuadTreeNode(m_pQuadTree);
    m_pMesh->Get_IndexBufferRef()->Set_NumWorkingIndexes(m_iWorkingNumIndexes);
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    m_pHeightMapSetter->Set_TextureDetailLayers(m_pMaterial->Get_Textures());
}

void CLandscape::Render(CShader::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);

    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    ILight* pLight = CSceneMgr::Instance()->Get_GlobalLight();
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
            
            //pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            //pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            //pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Matrix(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            pShader->Set_Vector3(pLight->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == NULL)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }

            pShader->Set_Texture(m_pHeightMapSetter->Get_TextureDetailColor(), CShader::E_TEXTURE_SLOT_01);
            pShader->Set_Texture(m_pHeightMapSetter->Get_TextureDetailNormal(), CShader::E_TEXTURE_SLOT_02);
            pShader->Set_Vector4(glm::vec4(0.0f, 1.0, 0.0, 16.0), CShader::E_ATTRIBUTE_VECTOR_CLIP_PLANE);
        }
            break;
        case CShader::E_RENDER_MODE_REFLECTION:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_REFLECTION is NULL"<<std::endl;
                return;
            }

            //pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            //pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            //pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Matrix(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            pShader->Set_Vector3(pLight->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == NULL)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
            
            pShader->Set_Texture(m_pHeightMapSetter->Get_TextureDetailColor(), CShader::E_TEXTURE_SLOT_01);
            pShader->Set_Texture(m_pHeightMapSetter->Get_TextureDetailNormal(), CShader::E_TEXTURE_SLOT_02);
            pShader->Set_Vector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::E_ATTRIBUTE_VECTOR_CLIP_PLANE);
        }
            break;
        case CShader::E_RENDER_MODE_REFRACTION:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_REFRACTION is NULL"<<std::endl;
                return;
            }
            
            //pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            //pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            //pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Matrix(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            pShader->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            pShader->Set_Vector3(pLight->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            
            for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
            {
                CTexture* pTexture = m_pMaterial->Get_Texture(i);
                if(pTexture == NULL)
                {
                    continue;
                }
                pShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
            pShader->Set_Texture(m_pHeightMapSetter->Get_TextureDetailColor(), CShader::E_TEXTURE_SLOT_01);
            pShader->Set_Texture(m_pHeightMapSetter->Get_TextureDetailNormal(), CShader::E_TEXTURE_SLOT_02);
            pShader->Set_Vector4(glm::vec4(0.0f, -1.0, 0.0, 0.1), CShader::E_ATTRIBUTE_VECTOR_CLIP_PLANE);
        }
            break;
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(pShader == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            
            //pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            //pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            //pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Matrix(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            pShader->Set_Vector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::E_ATTRIBUTE_VECTOR_CLIP_PLANE);
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
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Render();
    }
}




