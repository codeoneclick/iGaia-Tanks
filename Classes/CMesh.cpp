//
//  CMesh.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMesh.h"

CMesh::CMesh(IResource::E_CREATION_MODE _eCreationMode)
{
    m_pVertexBuffer = nullptr;
    m_pIndexBuffer = nullptr;
    m_eResourceType = E_RESOURCE_TYPE_MESH;
    m_eCreationMode = _eCreationMode;
}

CMesh::~CMesh(void)
{
    std::cout<<"[CMesh::~CMesh] delete"<<std::endl;
}