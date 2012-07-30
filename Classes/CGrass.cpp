//
//  CGrass.cpp
//  iGaia
//
//  Created by sergey.sergeev on 3/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGrass.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoord.h"

const float CGrass::k_ELEMENT_SIZE = 1.0f;
const float CGrass::k_ELEMENT_HEIGHT = 1.75f;
const int CGrass::k_ELEMENT_NUM_INDEXES = 6;
const int CGrass::k_ELEMENT_NUM_VERTEXES = 4;

CGrass::CGrass(void)
{
    m_iWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    m_iHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    
    m_pSingleElementIndexBuffer = new unsigned short[k_ELEMENT_NUM_INDEXES];
    m_pSingleElementIndexBuffer[0] = 0;
    m_pSingleElementIndexBuffer[1] = 1;
    m_pSingleElementIndexBuffer[2] = 2;
    m_pSingleElementIndexBuffer[3] = 2;
    m_pSingleElementIndexBuffer[4] = 3;
    m_pSingleElementIndexBuffer[5] = 1;
    
    /*m_pSingleElementIndexBuffer[6]  = 4;
    m_pSingleElementIndexBuffer[7]  = 5;
    m_pSingleElementIndexBuffer[8]  = 6;
    m_pSingleElementIndexBuffer[9]  = 6;
    m_pSingleElementIndexBuffer[10] = 7;
    m_pSingleElementIndexBuffer[11] = 5;*/
    
    m_pSingleElementVertexBuffer = new CVertexBufferPositionTexcoord(k_ELEMENT_NUM_VERTEXES, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pSingleElementVertexBuffer->Lock());
    //glm::vec3* pPositionData = m_pSingleElementVertexBuffer->GetOrCreate_PositionSourceData();

    pVertexBufferData[0].m_vPosition = glm::vec3(-k_ELEMENT_SIZE / 2, 0.0f, 0.0f);
    pVertexBufferData[1].m_vPosition = glm::vec3(-k_ELEMENT_SIZE / 2, k_ELEMENT_HEIGHT, 0.0f);
    pVertexBufferData[2].m_vPosition = glm::vec3( k_ELEMENT_SIZE / 2, 0.0f, 0.0f);
    pVertexBufferData[3].m_vPosition = glm::vec3( k_ELEMENT_SIZE / 2, k_ELEMENT_HEIGHT, 0.0f);
    
    /*pPositionData[4] = glm::vec3(0.0f, 0.0f, -k_ELEMENT_SIZE / 2);
    pPositionData[5] = glm::vec3(0.0f, k_ELEMENT_HEIGHT, -k_ELEMENT_SIZE / 2);
    pPositionData[6] = glm::vec3(0.0f, 0.0f,  k_ELEMENT_SIZE / 2);
    pPositionData[7] = glm::vec3(0.0f, k_ELEMENT_HEIGHT,  k_ELEMENT_SIZE / 2);*/
    
    //glm::vec2* pTexCoordData = m_pSingleElementVertexBuffer->GetOrCreate_TexcoordSourceData();
    
    pVertexBufferData[0].m_vTexcoord = glm::vec2(0.0f,1.0f);
    pVertexBufferData[1].m_vTexcoord = glm::vec2(0.0f,0.0f);
    pVertexBufferData[2].m_vTexcoord = glm::vec2(1.0f,1.0f);
    pVertexBufferData[3].m_vTexcoord = glm::vec2(1.0f,0.0f);
    
    /*pTexCoordData[4] = glm::vec2(0.0f,1.0f);
    pTexCoordData[5] = glm::vec2(0.0f,0.0f);
    pTexCoordData[6] = glm::vec2(1.0f,1.0f);
    pTexCoordData[7] = glm::vec2(1.0f,0.0f);*/
    
    m_pHeightMapSetter = NULL;
}

CGrass::~CGrass(void)
{
    SAFE_DELETE(m_pQuadTree);
    SAFE_DELETE_ARRAY(m_pSingleElementIndexBuffer);
    SAFE_DELETE(m_pSingleElementVertexBuffer);
    m_pHeightMapSetter = NULL;
}

void CGrass::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{   
    m_pHeightMapSetter = CSceneMgr::Instance()->Get_HeightMapSetterRef();
    
    srand(time(NULL));
    
    for(unsigned int i = 1; i < (m_iWidth - 1); i += 2)
    {
        for(unsigned int j = 1; j < (m_iHeight - 1); j += 2)
        {
           
            float fRange = 0.9f - 0.1f;
            float fOffetX = 0.1f + float(fRange * rand() / (RAND_MAX + 1.0f));
            float fOffetY = 0.1f + float(fRange * rand() / (RAND_MAX + 1.0f));
            
            float fHeight = m_pHeightMapSetter->Get_HeightValue(i + fOffetX, j + fOffetY);
            if(fHeight < 1.25f && fHeight > 0.05f)
            {
                m_lGrassElementsPosition.push_back(glm::vec3(i + fOffetX, fHeight + 0.025f, j + fOffetY));
            }
        }
    }
    
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = m_lGrassElementsPosition.size() * k_ELEMENT_NUM_VERTEXES;
    pSourceData->m_iNumIndexes  = m_lGrassElementsPosition.size() * k_ELEMENT_NUM_INDEXES;
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STREAM_DRAW);
    
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    CVertexBufferPositionTexcoord::SVertex* pSingleElementVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pSingleElementVertexBuffer->Lock());
    //glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->GetOrCreate_PositionSourceData();
    //glm::vec2* pTextCoordData = pSourceData->m_pVertexBuffer->GetOrCreate_TexcoordSourceData();
    
    unsigned short* pIndexesBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
    //glm::vec3* pSingleElementPositionData = m_pSingleElementVertexBuffer->GetOrCreate_PositionSourceData();
    //glm::vec2* pSingleElementTextCoordData = m_pSingleElementVertexBuffer->GetOrCreate_TexcoordSourceData();
    
    std::vector<glm::vec3>::iterator pElementsSourceDataBegin = m_lGrassElementsPosition.begin();
    std::vector<glm::vec3>::iterator pElementsSourceDataEnd   = m_lGrassElementsPosition.end();
    unsigned int iVertexesDataOffset = 0;
    unsigned int iIndexesDataOffset = 0;
    while (pElementsSourceDataBegin != pElementsSourceDataEnd)
    {
        for(unsigned int i = 0; i < k_ELEMENT_NUM_VERTEXES; ++i)
        {
            pVertexBufferData[i + iVertexesDataOffset].m_vPosition = pSingleElementVertexBufferData[i].m_vPosition + (*pElementsSourceDataBegin);
            pVertexBufferData[i +iVertexesDataOffset].m_vTexcoord = pSingleElementVertexBufferData[i].m_vTexcoord;
        }
        
        for(unsigned int i = 0; i < k_ELEMENT_NUM_INDEXES; ++i)
        {
            pIndexesBufferData[i + iIndexesDataOffset] = m_pSingleElementIndexBuffer[i] + iVertexesDataOffset;
        }
        
        iIndexesDataOffset += k_ELEMENT_NUM_INDEXES;
        iVertexesDataOffset += k_ELEMENT_NUM_VERTEXES;
        ++pElementsSourceDataBegin;
    }
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    m_pMesh->Get_VertexBufferRef()->Commit();
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    unsigned int iNumIndexes = m_pMesh->Get_NumIndexes();
    unsigned short* pIndexBufferData = m_pMesh->Get_IndexBufferRef()->Get_SourceData();
    
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
    
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_CULL_MODE,  false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_MASK, false);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_DEPTH_TEST, true);
    m_pMaterial->Set_RenderState(CMaterial::E_RENDER_STATE_BLEND_MODE, true);
    m_pMaterial->Set_CullFace(GL_FRONT);
    m_pMaterial->Set_BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CGrass::_CreateQuadTreeNode(int _iSize, CGrass::SQuadTreeNode *_pParentNode)
{
    static int iRecurseCount = 0;
    iRecurseCount++;
    std::cout<<"[CGrass::_CreateQuadTreeNode] Recurse Count : "<<iRecurseCount<<std::endl;
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

void CGrass::_CreateIndexBufferRefForQuadTreeNode(CGrass::SQuadTreeNode *_pNode)
{
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    //glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->GetOrCreate_PositionSourceData();
    unsigned int iParentNumIndexes = _pNode->m_pParent->m_iNumIndexes;
    _pNode->m_pIndexes = static_cast<unsigned short*>(malloc(sizeof(unsigned short)));
    float fMaxY = -4096.0f;
    float fMinY =  4096.0f;
    
    unsigned int iQuadTreeNodeId = 0;
    CGrass::SQuadTreeNode* pParentNode = _pNode->m_pParent;
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

bool CGrass::_IsPointInBoundBox(glm::vec3 _vPoint, glm::vec3 _vMinBound, glm::vec3 _vMaxBound)
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

void CGrass::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CGrass::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CGrass::_CheckVisibleQuadTreeNode(CGrass::SQuadTreeNode *_pNode)
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

void CGrass::Update(void)
{
    INode::Update();
    
    m_iWorkingNumIndexes = 0;
    _CheckVisibleQuadTreeNode(m_pQuadTree);
    m_pMesh->Get_IndexBufferRef()->Set_NumWorkingIndexes(m_iWorkingNumIndexes);
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    unsigned int iNumGrassElements = m_lGrassElementsPosition.size();
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>( m_pMesh->Get_VertexBufferRef()->Lock());
    CVertexBufferPositionTexcoord::SVertex* pSingleElementVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pSingleElementVertexBuffer->Lock());

    for(unsigned int index = 0; index < iNumGrassElements; index++)
    {
        glm::mat4 mWorld = pCamera->Get_BillboardCylindricalMatrix(m_lGrassElementsPosition[index]);
        
        glm::vec3 vVertexPosition = pSingleElementVertexBufferData[0].m_vPosition;
        glm::vec4 vTransform = glm::vec4(vVertexPosition.x, vVertexPosition.y, vVertexPosition.z, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 0].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vVertexPosition = pSingleElementVertexBufferData[1].m_vPosition;
        vTransform = glm::vec4(vVertexPosition.x, vVertexPosition.y, vVertexPosition.z, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 1].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vVertexPosition = pSingleElementVertexBufferData[2].m_vPosition;
        vTransform = glm::vec4(vVertexPosition.x, vVertexPosition.y, vVertexPosition.z, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 2].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);

        vVertexPosition = pSingleElementVertexBufferData[3].m_vPosition;
        vTransform = glm::vec4(vVertexPosition.x, vVertexPosition.y, vVertexPosition.z, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 3].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        static float fTimer = 0.0f;
        fTimer += 0.00025f;
        
        float fAngleX = m_lGrassElementsPosition[index].z * m_lGrassElementsPosition[index].y - static_cast<int>(m_lGrassElementsPosition[index].z) * m_lGrassElementsPosition[index].y;
        float fAngleZ = m_lGrassElementsPosition[index].x - static_cast<int>(m_lGrassElementsPosition[index].x);
        
        pVertexBufferData[index * 4 + 1].m_vPosition.x += sinf(fTimer * fAngleX) * 0.33f;
        pVertexBufferData[index * 4 + 1].m_vPosition.z += cosf(fTimer * fAngleZ) * 0.33f;
        
        pVertexBufferData[index * 4 + 3].m_vPosition.x += sinf(fTimer * fAngleX) * 0.33f;
        pVertexBufferData[index * 4 + 3].m_vPosition.z += cosf(fTimer * fAngleZ) * 0.33f;
    }
    m_pMesh->Get_VertexBufferRef()->Commit();
}

void CGrass::Render(CShader::E_RENDER_MODE _eMode)
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
            
            //pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            //pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            //pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Matrix(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            
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
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            
            //pShader->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            //pShader->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            //pShader->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            pShader->Set_Matrix(m_mWVP, CShader::E_ATTRIBUTE_MATRIX_WVP);
            
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
}
