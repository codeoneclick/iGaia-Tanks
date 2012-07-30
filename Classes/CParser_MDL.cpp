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
    
}

CParser_MDL::~CParser_MDL(void)
{
    
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
    
    int iNumVertexes = 0;
    int iNumIndexes = 0;
    
    fread(&iNumVertexes, sizeof(int), 1, pFile);
    fread(&iNumIndexes, sizeof(int), 1, pFile);
    
    m_pSourceData = new CMesh::SSourceData();
    m_pSourceData->m_iNumVertexes = iNumVertexes;
    m_pSourceData->m_iNumIndexes = iNumIndexes;
    m_pSourceData->m_pIndexBuffer  = new CIndexBuffer(m_pSourceData->m_iNumIndexes, GL_STATIC_DRAW);
	m_pSourceData->m_pData = new CMesh::SVertex[m_pSourceData->m_iNumVertexes];
    
    m_pSourceData->m_vMaxBound = glm::vec3( -4096.0f, -4096.0f, -4096.0f );
    m_pSourceData->m_vMinBound = glm::vec3(  4096.0f,  4096.0f,  4096.0f );
    
    for( unsigned int i = 0; i < m_pSourceData->m_iNumVertexes; ++i)
    {
        fread(&m_pSourceData->m_pData[i].m_vPosition,sizeof(glm::vec3), 1, pFile);
        fread(&m_pSourceData->m_pData[i].m_vNormal, sizeof(glm::vec3), 1, pFile);
        fread(&m_pSourceData->m_pData[i].m_vTangent, sizeof(glm::vec3), 1, pFile);
        fread(&m_pSourceData->m_pData[i].m_vTexCoord, sizeof(glm::vec2), 1, pFile);
        
        
        //std::cout<<"Position : "<<m_pSource->m_pData[i].m_vPosition.x<<","<<m_pSource->m_pData[i].m_vPosition.y<<","<<m_pSource->m_pData[i].m_vPosition.z<<"\n";
       
        if(m_pSourceData->m_pData[i].m_vPosition.x > m_pSourceData->m_vMaxBound.x)
        {
            m_pSourceData->m_vMaxBound.x = m_pSourceData->m_pData[i].m_vPosition.x;
        }
        
        if(m_pSourceData->m_pData[i].m_vPosition.y > m_pSourceData->m_vMaxBound.y)
        {
            m_pSourceData->m_vMaxBound.y = m_pSourceData->m_pData[i].m_vPosition.y;
        }
        
        if(m_pSourceData->m_pData[i].m_vPosition.z > m_pSourceData->m_vMaxBound.z)
        {
            m_pSourceData->m_vMaxBound.z = m_pSourceData->m_pData[i].m_vPosition.z;
        }
        
        if(m_pSourceData->m_pData[i].m_vPosition.x < m_pSourceData->m_vMinBound.x)
        {
            m_pSourceData->m_vMinBound.x = m_pSourceData->m_pData[i].m_vPosition.x;
        }
        
        if(m_pSourceData->m_pData[i].m_vPosition.y < m_pSourceData->m_vMinBound.y)
        {
            m_pSourceData->m_vMinBound.y = m_pSourceData->m_pData[i].m_vPosition.y;
        }
        
        if(m_pSourceData->m_pData[i].m_vPosition.z < m_pSourceData->m_vMinBound.z)
        {
            m_pSourceData->m_vMinBound.z = m_pSourceData->m_pData[i].m_vPosition.z;
        }
    }
    /*fseek (pFile , 0 , SEEK_CUR);
    long iFileBufferSizeRead = ftell (pFile);
    long iFileBufferSizeRest = iFileBufferSize - iFileBufferSizeRead;
    
    unsigned int iBlockSize = iFileBufferSizeRest / m_pSource->m_iNumIndexes;
    
    std::cout<<"[CParser_MDL] Index block size: "<<iBlockSize;*/
    
    //int iNum = 0;
    unsigned short* pIndexBufferData = m_pSourceData->m_pIndexBuffer->Get_SourceData();
    for(int i = 0; i < m_pSourceData->m_iNumIndexes; i++)
    {
        fread(&pIndexBufferData[i], sizeof(unsigned short),1, pFile);
        //std::cout<<"Index : "<<pIBData[i]<<"  Num : "<<iNum++<<"\n";
    }
    
    for(int i = 0; i < m_pSourceData->m_iNumIndexes; i += 3)
    {
        unsigned short iTempIndex = pIndexBufferData[i + 1];
        pIndexBufferData[i + 1] = pIndexBufferData[i + 2];
        pIndexBufferData[i + 2] = iTempIndex;
    }
    fclose(pFile);
    
    m_eStatus = E_DONE_STATUS;
}

void CParser_MDL::Commit(void)
{
    m_pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordNormalTangent(m_pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(m_pSourceData->m_pVertexBuffer->Lock());
    for(unsigned int index = 0; index < m_pSourceData->m_iNumVertexes; index++)
    {
        pVertexBufferData[index].m_vPosition = m_pSourceData->m_pData[index].m_vPosition;
        pVertexBufferData[index].m_vTexcoord = m_pSourceData->m_pData[index].m_vTexCoord;
        pVertexBufferData[index].m_vNormal = IVertexBuffer::CompressVEC3(m_pSourceData->m_pData[index].m_vNormal);
        pVertexBufferData[index].m_vTangent = IVertexBuffer::CompressVEC3(m_pSourceData->m_pData[index].m_vTangent);
    }
    
    m_pSourceData->m_pVertexBuffer->Commit();
    m_pSourceData->m_pIndexBuffer->Commit();
}


