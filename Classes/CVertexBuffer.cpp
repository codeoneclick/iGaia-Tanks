//
//  IVertexBuffer.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBuffer.h"

glm::u8vec4 CVertexBuffer::CompressVEC3(const glm::vec3 &_uncopressed)
{
    glm::vec3 normalized = glm::normalize(_uncopressed);
    glm::u8vec4 compressed;
    compressed.x = static_cast<unsigned char>((normalized.x + 1.0f) * 0.5f * 255.0f);
    compressed.y = static_cast<unsigned char>((normalized.y + 1.0f) * 0.5f * 255.0f);
    compressed.z = static_cast<unsigned char>((normalized.z + 1.0f) * 0.5f * 255.0f);
    compressed.w = 0;
    return compressed;
}

glm::vec3 CVertexBuffer::UncompressU8VEC4(const glm::u8vec4& _compressed)
{
    glm::vec3 uncompressed;
    uncompressed.x = static_cast<float>(_compressed.x / (255.0f * 0.5f) - 1.0f);
    uncompressed.y = static_cast<float>(_compressed.y / (255.0f * 0.5f) - 1.0f);
    uncompressed.z = static_cast<float>(_compressed.z / (255.0f * 0.5f) - 1.0f);
    return uncompressed;
}

CVertexBuffer::CVertexBuffer(unsigned int _numVertexes, unsigned int _mode)
{
    m_mode = _mode;
    m_numVertexes = _numVertexes;
    m_dataSource = new SVertex[_numVertexes];
    glGenBuffers(1, &m_handle);
}

CVertexBuffer::~CVertexBuffer(void)
{
    SAFE_DELETE_ARRAY(m_dataSource);
    std::cout<<"[~IVertexBuffer] glDeleteBuffers id :"<<m_handle<<std::endl;
    glDeleteBuffers(1, &m_handle);
    m_handle = NULL;
}

void CVertexBuffer::PutShaderReference(unsigned int _renderMode, CShader *_shader)
{
    m_shaderReferences[_renderMode] = _shader;
}

void CVertexBuffer::Unlock(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * m_numVertexes, m_dataSource, m_mode);
}

void CVertexBuffer::Bind(unsigned int _renderMode)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    CShader* shader = m_shaderReferences[_renderMode];
    unsigned int bytesPerVertex = 0;
    int slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_POSITION);
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (GLvoid*)bytesPerVertex);
    }
    bytesPerVertex += sizeof(glm::vec3);
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_TEXCOORD);
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (GLvoid*)bytesPerVertex);
    }
    bytesPerVertex += sizeof(glm::vec2);
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_NORMAL);
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(SVertex), (GLvoid*)bytesPerVertex);
    }
    bytesPerVertex += sizeof(glm::u8vec4);
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_TANGENT);
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(SVertex), (GLvoid*)bytesPerVertex);
    }
    bytesPerVertex += sizeof(glm::u8vec4);
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_COLOR);
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(SVertex), (GLvoid*)bytesPerVertex);
    }
}

void CVertexBuffer::Unbind(unsigned int _renderMode)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    CShader* shader = m_shaderReferences[_renderMode];
    GLint slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_POSITION);
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_TEXCOORD);
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_NORMAL);
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_TANGENT);
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = shader->Get_VertexSlot(CShader::E_VERTEX_SLOT_COLOR);
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}






