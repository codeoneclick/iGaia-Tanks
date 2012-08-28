//
//  CParser_MDL.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_MDL.h"
#include <fstream>
#include <strstream>
#include "CCommon_IOS.h"
#include "CVertexBufferPositionTexcoordNormalTangent.h"

CParser_MDL::CParser_MDL(void)
{
    m_pData = new SData();
}

CParser_MDL::~CParser_MDL(void)
{
    SAFE_DELETE(m_pData);
}

void CParser_MDL::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS;

    std::string sPath = Get_ResourceFileName(_sName); 
    
    FILE *pFile = fopen(sPath.c_str(), "r");
    if (!pFile)
    {
        return;
    }
    
    fread(&m_pData->m_iNumVertexes, sizeof(int), 1, pFile);
    fread(&m_pData->m_iNumIndexes, sizeof(int), 1, pFile);
    
    m_pData->m_vMaxBound = glm::vec3( -4096.0f, -4096.0f, -4096.0f );
    m_pData->m_vMinBound = glm::vec3(  4096.0f,  4096.0f,  4096.0f );
    
    m_pData->m_pVertexData = new SData::SVertex[m_pData->m_iNumVertexes];
    
    for(unsigned int i = 0; i < m_pData->m_iNumVertexes; ++i)
    {
        fread(&m_pData->m_pVertexData[i].m_vPosition,sizeof(glm::vec3), 1, pFile);
        fread(&m_pData->m_pVertexData[i].m_vNormal, sizeof(glm::vec3), 1, pFile);
        fread(&m_pData->m_pVertexData[i].m_vTangent, sizeof(glm::vec3), 1, pFile);
        fread(&m_pData->m_pVertexData[i].m_vTexCoord, sizeof(glm::vec2), 1, pFile);
       
        if(m_pData->m_pVertexData[i].m_vPosition.x > m_pData->m_vMaxBound.x)
        {
            m_pData->m_vMaxBound.x = m_pData->m_pVertexData[i].m_vPosition.x;
        }
        
        if(m_pData->m_pVertexData[i].m_vPosition.y > m_pData->m_vMaxBound.y)
        {
            m_pData->m_vMaxBound.y = m_pData->m_pVertexData[i].m_vPosition.y;
        }
        
        if(m_pData->m_pVertexData[i].m_vPosition.z > m_pData->m_vMaxBound.z)
        {
            m_pData->m_vMaxBound.z = m_pData->m_pVertexData[i].m_vPosition.z;
        }
        
        if(m_pData->m_pVertexData[i].m_vPosition.x < m_pData->m_vMinBound.x)
        {
            m_pData->m_vMinBound.x = m_pData->m_pVertexData[i].m_vPosition.x;
        }
        
        if(m_pData->m_pVertexData[i].m_vPosition.y < m_pData->m_vMinBound.y)
        {
            m_pData->m_vMinBound.y = m_pData->m_pVertexData[i].m_vPosition.y;
        }
        
        if(m_pData->m_pVertexData[i].m_vPosition.z < m_pData->m_vMinBound.z)
        {
            m_pData->m_vMinBound.z = m_pData->m_pVertexData[i].m_vPosition.z;
        }
    }

    m_pData->m_pIndexData = new unsigned short[m_pData->m_iNumIndexes];
    
    for(unsigned int i = 0; i < m_pData->m_iNumIndexes; ++i)
    {
        fread(&m_pData->m_pIndexData[i], sizeof(unsigned short),1, pFile);
    }
    
    for(unsigned int i = 0; i < m_pData->m_iNumIndexes; i += 3)
    {
        unsigned short iTempIndex = m_pData->m_pIndexData[i + 1];
        m_pData->m_pIndexData[i + 1] = m_pData->m_pIndexData[i + 2];
        m_pData->m_pIndexData[i + 2] = iTempIndex;
    }
    fclose(pFile);
    
    m_eStatus = E_DONE_STATUS;
}

IResource* CParser_MDL::Commit(void)
{
    CVertexBufferPositionTexcoordNormalTangent* pVertexBuffer = new CVertexBufferPositionTexcoordNormalTangent(m_pData->m_iNumVertexes, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(pVertexBuffer->Lock());
    for(unsigned int index = 0; index < m_pData->m_iNumVertexes; index++)
    {
        pVertexBufferData[index].m_vPosition = m_pData->m_pVertexData[index].m_vPosition;
        pVertexBufferData[index].m_vTexcoord = m_pData->m_pVertexData[index].m_vTexCoord;
        pVertexBufferData[index].m_vNormal = IVertexBuffer::CompressVEC3(m_pData->m_pVertexData[index].m_vNormal);
        pVertexBufferData[index].m_vTangent = IVertexBuffer::CompressVEC3(m_pData->m_pVertexData[index].m_vTangent);
    }
    
    CIndexBuffer* pIndexBuffer = new CIndexBuffer(m_pData->m_iNumIndexes, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pIndexBuffer->Get_SourceData();
    for(unsigned int index = 0; index < m_pData->m_iNumIndexes; ++index)
    {
        pIndexBufferData[index] = m_pData->m_pIndexData[index];
    }
    
    CMesh* pMesh = new CMesh(IResource::E_CREATION_MODE_NATIVE);
    pMesh->Set_VertexBufferRef(pVertexBuffer);
    pMesh->Set_IndexBufferRef(pIndexBuffer);
    
    pMesh->Get_VertexBufferRef()->Commit();
    pMesh->Get_IndexBufferRef()->Commit();
    
    pMesh->Set_MaxBound(m_pData->m_vMaxBound);
    pMesh->Set_MinBound(m_pData->m_vMinBound);
    
    return pMesh;
}


