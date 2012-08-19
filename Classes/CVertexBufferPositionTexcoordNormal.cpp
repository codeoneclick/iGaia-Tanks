//
//  CVertexBufferPositionTexcoordNormal.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBufferPositionTexcoordNormal.h"

CVertexBufferPositionTexcoordNormal::CVertexBufferPositionTexcoordNormal(unsigned int _iNumVertexes, unsigned int _eMode)
{
    m_iNumVertexes = _iNumVertexes;
    m_eRenderMode = _eMode;
    m_eVertexBufferMode = IVertexBuffer::E_VERTEX_BUFFER_MODE_PTN;
    m_pData = new char[m_iNumVertexes * k_STRIDE_SIZE];
}

CVertexBufferPositionTexcoordNormal::~CVertexBufferPositionTexcoordNormal(void)
{
    
}

void CVertexBufferPositionTexcoordNormal::Enable(CShader::E_RENDER_MODE _eRenderMode)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_hHandle);
    CShader* pShader = m_lShaderRefContainer[_eRenderMode];
    unsigned char iBytesPerVertex = 0;
    GLint iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_POSITION);
    if(iSlot >= 0)
    {
        glEnableVertexAttribArray(iSlot);
        glVertexAttribPointer(iSlot, 3, GL_FLOAT, GL_FALSE, k_STRIDE_SIZE, (GLvoid*)iBytesPerVertex);
    }
    iBytesPerVertex += sizeof(glm::vec3);
    iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_TEXCOORD);
    if(iSlot >= 0)
    {
        glEnableVertexAttribArray(iSlot);
        glVertexAttribPointer(iSlot, 2, GL_FLOAT, GL_FALSE, k_STRIDE_SIZE, (GLvoid*)iBytesPerVertex);
    }
    iBytesPerVertex += sizeof(glm::vec2);
    iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_NORMAL);
    if(iSlot >= 0)
    {
        glEnableVertexAttribArray(iSlot);
        glVertexAttribPointer(iSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, k_STRIDE_SIZE, (GLvoid*)iBytesPerVertex);
    }
    iBytesPerVertex += sizeof(glm::u8vec4);
}

void CVertexBufferPositionTexcoordNormal::Disable(CShader::E_RENDER_MODE _eRenderMode)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_hHandle);
    CShader* pShader = m_lShaderRefContainer[_eRenderMode];
    GLint iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_POSITION);
    if(iSlot >= 0)
    {
        glDisableVertexAttribArray(iSlot);
    }
    iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_TEXCOORD);
    if(iSlot >= 0)
    {
        glDisableVertexAttribArray(iSlot);
    }
    iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_NORMAL);
    if(iSlot >= 0)
    {
        glDisableVertexAttribArray(iSlot);
    }
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}




