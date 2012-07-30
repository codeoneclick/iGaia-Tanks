//
//  IVertexBuffer.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IVertexBuffer.h"

glm::u8vec4 IVertexBuffer::CompressVEC3(const glm::vec3 &_vUncopressed)
{
    glm::vec3 vNormalized = glm::normalize(_vUncopressed);
    glm::u8vec4 vCompressed;
    vCompressed.x = static_cast<unsigned char>((vNormalized.x + 1.0f) * 0.5f * 255.0f);
    vCompressed.y = static_cast<unsigned char>((vNormalized.y + 1.0f) * 0.5f * 255.0f);
    vCompressed.z = static_cast<unsigned char>((vNormalized.z + 1.0f) * 0.5f * 255.0f);
    vCompressed.w = 0;
    return vCompressed;
}

glm::vec3 IVertexBuffer::UnCompressU8VEC4(const glm::u8vec4& _vCompressed)
{
    glm::vec3 vUnCompressed;
    vUnCompressed.x = static_cast<float>(_vCompressed.x / (255.0f * 0.5f) - 1.0f);
    vUnCompressed.y = static_cast<float>(_vCompressed.y / (255.0f * 0.5f) - 1.0f);
    vUnCompressed.z = static_cast<float>(_vCompressed.z / (255.0f * 0.5f) - 1.0f);
    return vUnCompressed;
}

IVertexBuffer::IVertexBuffer(void)
{
    m_pData = NULL;
    m_eMode = GL_STATIC_DRAW;
    m_iNumVertexes = 0;
    m_bIsCommited = false;
    glGenBuffers(1, &m_hHandle);
}

IVertexBuffer::~IVertexBuffer(void)
{
    SAFE_DELETE_ARRAY(m_pData);
    try
    {
        std::cout<<"[~IVertexBuffer] glDeleteBuffers id :"<<m_hHandle<<std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, NULL);
        glDeleteBuffers(1, &m_hHandle);
    }
    catch (int _error)
    {
        std::cout<<"[~IVertexBuffer] glDeleteBuffers exception id :"<<_error<<std::endl;
    }
    m_hHandle = 0;
}

void IVertexBuffer::Add_ShaderRef(CShader::E_RENDER_MODE _eRenderMode, CShader *_pShaderRef)
{
    m_lShaderRefContainer[_eRenderMode] = _pShaderRef;
}

void IVertexBuffer::Unlock(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_hHandle);
    if(!m_bIsCommited)
    {
        glBufferData(GL_ARRAY_BUFFER, k_STRIDE_SIZE * m_iNumVertexes, m_pData, m_eMode);
        m_bIsCommited = true;
    }
    else
    {
        glBufferData(GL_ARRAY_BUFFER, k_STRIDE_SIZE * m_iNumVertexes, m_pData, m_eMode);
    }
}

void IVertexBuffer::Commit(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_hHandle);
    if(!m_bIsCommited)
    {
        glBufferData(GL_ARRAY_BUFFER, k_STRIDE_SIZE * m_iNumVertexes, m_pData, m_eMode);
        m_bIsCommited = true;
    }
    else
    {
        glBufferData(GL_ARRAY_BUFFER, k_STRIDE_SIZE * m_iNumVertexes, m_pData, m_eMode);
    }
}







