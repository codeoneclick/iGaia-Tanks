//
//  CBatchModel.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 8/19/12.
//
//

#include "CBatchModel.h"

CBatchModel::CBatchModel(void)
{

}

CBatchModel::~CBatchModel(void)
{
    
}

void CBatchModel::Create(IVertexBuffer::E_VERTEX_BUFFER_MODE _eVertexBufferMode)
{
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = 4096;
    pSourceData->m_iNumIndexes  = 8192;

    switch (_eVertexBufferMode)
    {
        case IVertexBuffer::E_VERTEX_BUFFER_MODE_PC:
        {
            pSourceData->m_pVertexBuffer = new CVertexBufferPositionColor(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
        }
            break;
        case IVertexBuffer::E_VERTEX_BUFFER_MODE_PT:
        {
             pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
        }
            break;
        case IVertexBuffer::E_VERTEX_BUFFER_MODE_PTC:
        {
             pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordColor(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
        }
            break;
        case IVertexBuffer::E_VERTEX_BUFFER_MODE_PTN:
        {
             pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordNormal(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
        }
            break;
        case IVertexBuffer::E_VERTEX_BUFFER_MODE_PTNT:
        {
             pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordNormalTangent(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
        }
            break;
            
        default:
            break;
    }
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STREAM_DRAW);
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
}

void CBatchModel::PushNodeRef(INode *_pNode)
{
    m_pMaterial = _pNode->Get_Material();
}

void CBatchModel::ResetNodeRef(void)
{
    
}

void CBatchModel::Update(void)
{
    
}

void CBatchModel::Render(CShader::E_RENDER_MODE _eMode)
{
    
}


