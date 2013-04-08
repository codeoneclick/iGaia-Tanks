//
//  CMesh.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CMesh.h"

CMesh::CMesh(void) :
IResource_INTERFACE(E_RESOURCE_TYPE_MESH)
{

}

CMesh::~CMesh(void)
{

}

void CMesh::Link(std::unique_ptr<CVertexBuffer> _vertexBuffer, std::unique_ptr<CIndexBuffer> _indexBuffer)
{
    m_resourceType = E_RESOURCE_TYPE_MESH;
    
    m_vertexBuffer = std::move(_vertexBuffer);
    m_indexBuffer = std::move(_indexBuffer);
    
    m_maxBound = glm::vec3(0.0f, 0.0f, 0.0f);
    m_minBound = glm::vec3(0.0f, 0.0f, 0.0f);
}

void CMesh::Link(std::unique_ptr<CVertexBuffer> _vertexBuffer, std::unique_ptr<CIndexBuffer> _indexBuffer, const glm::vec3 &_maxBound, const glm::vec3 &_minBound)
{
    m_resourceType = E_RESOURCE_TYPE_MESH;
    
    m_vertexBuffer = std::move(_vertexBuffer);
    m_indexBuffer = std::move(_indexBuffer);
    
    m_maxBound = _maxBound;
    m_minBound = _minBound;
}

void CMesh::Bind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots)
{
    assert(m_vertexBuffer != nullptr);
    assert(m_indexBuffer != nullptr);
    m_vertexBuffer->Bind(_slots);
    m_indexBuffer->Bind();
}

void CMesh::Draw(void)
{
    assert(m_vertexBuffer != nullptr);
    assert(m_indexBuffer != nullptr);
    glDrawElements(GL_TRIANGLES, m_indexBuffer->Get_NumIndexes(), GL_UNSIGNED_SHORT, NULL);
}

void CMesh::Unbind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots)
{
    assert(m_vertexBuffer != nullptr);
    assert(m_indexBuffer != nullptr);
    m_vertexBuffer->Unbind(_slots);
    m_indexBuffer->Unbind();
}