//
//  CVertexBuffer.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/26/13.
//
//

#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer(ui32 _numVertexes, GLenum _mode)
{
    assert(_numVertexes != 0);
    m_numVertexes = _numVertexes;
    m_mode = _mode;
    m_data = std::unique_ptr<SVertex>(new SVertex[m_numVertexes]);
    m_currentHandleIndex = -1;
    glGenBuffers(K_NUM_REPLACEMENT_VERTEX_BUFFERS, m_handles);
}

CVertexBuffer::~CVertexBuffer(void)
{
    glDeleteBuffers(K_NUM_REPLACEMENT_VERTEX_BUFFERS, m_handles);
}

glm::u8vec4 CVertexBuffer::CompressVec3(const glm::vec3& _uncompressed)
{
    glm::vec3 normalized = glm::normalize(_uncompressed);
    glm::u8vec4 compressed;
    compressed.x = static_cast<ui8>((normalized.x + 1.0f) * 0.5f * 255.0f);
    compressed.y = static_cast<ui8>((normalized.y + 1.0f) * 0.5f * 255.0f);
    compressed.z = static_cast<ui8>((normalized.z + 1.0f) * 0.5f * 255.0f);
    compressed.w = 0;
    return compressed;
}

glm::vec3 CVertexBuffer::UncompressU8Vec4(const glm::u8vec4& _compressed)
{
    glm::vec3 uncompressed;
    uncompressed.x = static_cast<f32>(_compressed.x / (255.0f * 0.5f) - 1.0f);
    uncompressed.y = static_cast<f32>(_compressed.y / (255.0f * 0.5f) - 1.0f);
    uncompressed.z = static_cast<f32>(_compressed.z / (255.0f * 0.5f) - 1.0f);
    return uncompressed;
}

void CVertexBuffer::Unlock(void)
{
    m_currentHandleIndex = (m_currentHandleIndex >= (K_NUM_REPLACEMENT_VERTEX_BUFFERS - 1)) ? 0 : m_currentHandleIndex + 1;
    glBindBuffer(GL_ARRAY_BUFFER, m_handles[m_currentHandleIndex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * m_numVertexes, m_data.get(), m_mode);
}

void CVertexBuffer::Bind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots)
{
    assert(m_currentHandleIndex >= 0 && m_currentHandleIndex <= (K_NUM_REPLACEMENT_VERTEX_BUFFERS - 1));
    glBindBuffer(GL_ARRAY_BUFFER, m_handles[m_currentHandleIndex]);
    ui32 offset = 0;
    i32 slot = _slots.find(E_SHADER_VERTEX_SLOT_POSITION)->second;
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (GLvoid*)offset);
    }
    offset += sizeof(glm::vec3);
    slot = _slots.find(E_SHADER_VERTEX_SLOT_TEXCOORD)->second;
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (GLvoid*)offset);
    }
    offset += sizeof(glm::vec2);
    slot = _slots.find(E_SHADER_VERTEX_SLOT_NORMAL)->second;
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(SVertex), (GLvoid*)offset);
    }
    offset += sizeof(glm::u8vec4);
    slot = _slots.find(E_SHADER_VERTEX_SLOT_TANGENT)->second;
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(SVertex), (GLvoid*)offset);
    }
    offset += sizeof(glm::u8vec4);
    slot = _slots.find(E_SHADER_VERTEX_SLOT_COLOR)->second;
    if(slot >= 0)
    {
        glEnableVertexAttribArray(slot);
        glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(SVertex), (GLvoid*)offset);
    }
}

void CVertexBuffer::Unbind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots)
{
    assert(m_currentHandleIndex >= 0 && m_currentHandleIndex <= (K_NUM_REPLACEMENT_VERTEX_BUFFERS - 1));
    glBindBuffer(GL_ARRAY_BUFFER, m_handles[m_currentHandleIndex]);
    i32 slot = _slots.find(E_SHADER_VERTEX_SLOT_POSITION)->second;
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = _slots.find(E_SHADER_VERTEX_SLOT_TEXCOORD)->second;
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = _slots.find(E_SHADER_VERTEX_SLOT_NORMAL)->second;
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = _slots.find(E_SHADER_VERTEX_SLOT_TANGENT)->second;
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    slot = _slots.find(E_SHADER_VERTEX_SLOT_COLOR)->second;
    if(slot >= 0)
    {
        glDisableVertexAttribArray(slot);
    }
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}
