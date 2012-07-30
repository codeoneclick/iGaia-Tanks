//
//  CMeshComposite.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMeshComposite.h"

CMeshComposite* CMeshComposite::m_pInstance = NULL;

CMeshComposite::CMeshComposite()
{
    /*CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 4;
    pSource->m_iNumIndexes  = 6;
    
    pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIndexBuffer->Get_Data();
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 2;
    pIBData[4] = 3;
    pIBData[5] = 0;
    
    pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSource->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    glm::u8vec4* pNormalData = pSource->m_pVertexBuffer->CreateOrReUse_NormalData();
    
    
    pPositionData[0] = glm::vec3(-0.5f, -0.5f, 0.0f);
    pPositionData[1] = glm::vec3(-0.5f,  0.5f, 0.0f);
    pPositionData[2] = glm::vec3( 0.5f,  0.5f, 0.0f);
    pPositionData[3] = glm::vec3( 0.5f, -0.5f, 0.0f);
    
    pTexCoordData[0] = glm::vec2(0.0f, 0.0f);
    pTexCoordData[1] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[2] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[3] = glm::vec2(1.0f, 0.0f);
    
    pSource->m_pVertexBuffer->CommitToRAM();
    pSource->m_pVertexBuffer->CommitFromRAMToVRAM();

    CMesh* pMesh = new CMesh();
    pMesh->Set_Source(pSource);
    pMesh->Set_Name("plane");
    
    m_lContainer[IResource::E_STANDART_MODEL_PLANE] = pMesh;
    
    pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 24;
    pSource->m_iNumIndexes  = 36;
    
    pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
    
    pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
    pTexCoordData = pSource->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    pNormalData = pSource->m_pVertexBuffer->CreateOrReUse_NormalData();
    
    glm::vec3 m_vMin = glm::vec3( -0.5f, -0.5f, -0.5f);
    glm::vec3 m_vMax = glm::vec3(  0.5f,  0.5f,  0.5f);
    
    // Front
    pPositionData[0] = glm::vec3( m_vMin.x,  m_vMin.y, m_vMax.z);
    pPositionData[1] = glm::vec3( m_vMax.x,  m_vMin.y, m_vMax.z);
    pPositionData[2] = glm::vec3( m_vMax.x,  m_vMax.y, m_vMax.z);
    pPositionData[3] = glm::vec3( m_vMin.x,  m_vMax.y, m_vMax.z);
    // Back
    pPositionData[4] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[5] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[6] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[7] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    // Left
    pPositionData[8] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[9] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[10] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[11] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right
    pPositionData[12] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[13] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[14] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    pPositionData[15] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    // Top
    pPositionData[16] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[17] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[18] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[19] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pPositionData[20] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[21] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pPositionData[22] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[23] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    // Front
    pTexCoordData[0] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[1] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[2] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[3] = glm::vec2(0.0f, 0.0f);
    // Back
    pTexCoordData[4] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[5] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[6] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[7] = glm::vec2(0.0f, 0.0f);
    // Left
    pTexCoordData[8] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[9] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[10] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[11] = glm::vec2(0.0f, 0.0f);
    // Right
    pTexCoordData[12] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[13] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[14] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[15] = glm::vec2(0.0f, 0.0f);
    // Top
    pTexCoordData[16] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[17] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[18] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[19] = glm::vec2(0.0f, 0.0f);
    // Bottom
    pTexCoordData[20] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[21] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[22] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[23] = glm::vec2(0.0f, 0.0f);
    
    pSource->m_pVertexBuffer->CommitToRAM();
    pSource->m_pVertexBuffer->CommitFromRAMToVRAM();
    
    pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
    pIBData = pSource->m_pIndexBuffer->Get_Data();
    
    // Front
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 0;
    pIBData[4] = 2;
    pIBData[5] = 3;
    // Back
    pIBData[6] = 4;
    pIBData[7] = 5;
    pIBData[8] = 6;
    pIBData[9] = 4;
    pIBData[10] = 6;
    pIBData[11] = 7;
    // Left
    pIBData[12] = 8;
    pIBData[13] = 9;
    pIBData[14] = 10;
    pIBData[15] = 8;
    pIBData[16] = 10;
    pIBData[17] = 11;
    // Right
    pIBData[18] = 12;
    pIBData[19] = 13;
    pIBData[20] = 14;
    pIBData[21] = 12;
    pIBData[22] = 14;
    pIBData[23] = 15;
    // Top
    pIBData[24] = 16;
    pIBData[25] = 17;
    pIBData[26] = 18;
    pIBData[27] = 16;
    pIBData[28] = 18;
    pIBData[29] = 19;
    // Bottom
    pIBData[30] = 20;
    pIBData[31] = 21;
    pIBData[32] = 22;
    pIBData[33] = 20;
    pIBData[34] = 22;
    pIBData[35] = 23;
    
    pMesh = new CMesh();
    pMesh->Set_Source(pSource);
    pMesh->Set_Name("cube");
    
    m_lContainer[IResource::E_STANDART_MODEL_CUBE] = pMesh;*/
}

CMeshComposite::~CMeshComposite()
{
    
}

CMeshComposite* CMeshComposite::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CMeshComposite();
    }
    return m_pInstance;
}

CMesh* CMeshComposite::Get_Mesh(IResource::E_STANDART_MODEL _eMesh)
{
    CMesh* pMesh = NULL;
    if( m_lContainer.find(_eMesh) != m_lContainer.end())
    {
        pMesh = m_lContainer[_eMesh];
        return pMesh;
    }
    else
    {
        return pMesh;
    }
}