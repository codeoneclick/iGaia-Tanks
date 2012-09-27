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
    m_vertexBuffer = _vertexBuffer;
    m_indexBuffer = _indexBuffer;
    m_resourceType = E_RESOURCE_TYPE_MESH;
    m_creationMode = _eCreationMode;
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
}