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

CParser_MDL::CParser_MDL(void)
{

}

CParser_MDL::~CParser_MDL(void)
{
  
}

void CParser_MDL::Load(const std::string& _name)
{
    m_status = E_STATUS_LOAD;

    std::string path = Get_ResourceFileName(_name);
    
    FILE *file = fopen(path.c_str(), "r");
    if (!file)
    {
        return;
    }
    
    fread(&m_numVertexes, sizeof(int), 1, file);
    fread(&m_numIndexes, sizeof(int), 1, file);

    m_vertexData = new CVertexBuffer::SVertex[m_numVertexes];

    for(unsigned int i = 0; i < m_numVertexes; ++i)
    {
        glm::vec3 position; 
        fread(&position,sizeof(glm::vec3), 1, file);
        glm::vec3 normal;
        fread(&normal, sizeof(glm::vec3), 1, file);
        glm::vec3 tangent;
        fread(&tangent, sizeof(glm::vec3), 1, file);
        glm::vec2 texcoord;
        fread(&texcoord, sizeof(glm::vec2), 1, file);

        m_vertexData[i].m_position = position;
        m_vertexData[i].m_texcoord = texcoord;
        m_vertexData[i].m_normal = CVertexBuffer::CompressVEC3(normal);
        m_vertexData[i].m_tangent = CVertexBuffer::CompressVEC3(tangent);
    }

    m_indexData = new unsigned short[m_numIndexes];
    
    for(unsigned int i = 0; i < m_numIndexes; ++i)
    {
        fread(&m_indexData[i], sizeof(unsigned short),1, file);
    }
    
    for(unsigned int i = 0; i < m_numIndexes; i += 3)
    {
        unsigned short index = m_indexData[i + 1];
        m_indexData[i + 1] = m_indexData[i + 2];
        m_indexData[i + 2] = index;
    }
    fclose(file);
    
    m_status = E_STATUS_DONE;
}

IResource* CParser_MDL::Commit(void)
{
    CVertexBuffer* vertexBuffer = new CVertexBuffer(m_numVertexes, GL_STATIC_DRAW);
    CVertexBuffer::SVertex* vertexData = vertexBuffer->Lock();
    memcpy(m_vertexData, vertexData, sizeof(CVertexBuffer::SVertex) * m_numVertexes);
    vertexBuffer->Unlock();

    CIndexBuffer* indexBuffer = new CIndexBuffer(m_numIndexes, GL_STATIC_DRAW);
    unsigned short* indexData = indexBuffer->Lock();
    memcpy(m_indexData, indexData, sizeof(unsigned short) * m_numIndexes);
    indexBuffer->Unlock();
    
    CMesh* mesh = new CMesh(IResource::E_CREATION_MODE_NATIVE, vertexBuffer, indexBuffer);
    return mesh;
}


