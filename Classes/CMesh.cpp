//
//  CMesh.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMesh.h"

CMesh::CMesh(IResource::E_CREATION_MODE _eCreationMode, CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer)
{
    m_resourceType = E_RESOURCE_TYPE_MESH;
    m_creationMode = _eCreationMode;
    
    m_vertexBuffer = _vertexBuffer;
    m_indexBuffer = _indexBuffer;
    _CreateBounds();
}

CMesh::~CMesh(void)
{
    std::cout<<"[CMesh::~CMesh] delete"<<std::endl;
    SAFE_DELETE(m_vertexBuffer);
    SAFE_DELETE(m_indexBuffer);
}

void CMesh::PutInstance(IResource *_resource)
{
    CMesh* mesh = static_cast<CMesh*>(_resource);
    m_vertexBuffer = mesh->m_vertexBuffer;
    m_indexBuffer = mesh->m_indexBuffer;
    _CreateBounds();
}

void CMesh::_CreateBounds(void)
{
    m_maxBound = glm::vec3( -4096.0f, -4096.0f, -4096.0f );
    m_minBound = glm::vec3(  4096.0f,  4096.0f,  4096.0f );

    CVertexBuffer::SVertex* vertexData = m_vertexBuffer->Lock();
    
    for(unsigned int i = 0; i < m_vertexBuffer->Get_NumVertexes(); ++i)
    {
        if(vertexData[i].m_position.x > m_maxBound.x)
        {
            m_maxBound.x = vertexData[i].m_position.x;
        }

        if(vertexData[i].m_position.y > m_maxBound.y)
        {
            m_maxBound.y = vertexData[i].m_position.y;
        }

        if(vertexData[i].m_position.z > m_maxBound.z)
        {
            m_maxBound.z = vertexData[i].m_position.z;
        }

        if(vertexData[i].m_position.x < m_minBound.x)
        {
            m_minBound.x = vertexData[i].m_position.x;
        }

        if(vertexData[i].m_position.y < m_minBound.y)
        {
            m_minBound.y = vertexData[i].m_position.y;
        }

        if(vertexData[i].m_position.z < m_minBound.z)
        {
            m_minBound.z = vertexData[i].m_position.z;
        }
    }
}


