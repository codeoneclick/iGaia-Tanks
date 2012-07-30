//
//  CVertexBufferPositionTexcoordColor.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CVertexBufferPositionTexcoordColor.h"

CVertexBufferPositionTexcoordColor::CVertexBufferPositionTexcoordColor(unsigned int _iNumVertexes, unsigned int _eMode)
{
    m_iNumVertexes = _iNumVertexes;
    m_eMode = _eMode;
    m_pData = new char[m_iNumVertexes * k_STRIDE_SIZE];
}

CVertexBufferPositionTexcoordColor::~CVertexBufferPositionTexcoordColor(void)
{
    
}

void CVertexBufferPositionTexcoordColor::Enable(CShader::E_RENDER_MODE _eRenderMode)
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
    iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_COLOR);
    if(iSlot >= 0)
    {
        glEnableVertexAttribArray(iSlot);
        glVertexAttribPointer(iSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, k_STRIDE_SIZE, (GLvoid*)iBytesPerVertex);
    }
    iBytesPerVertex += sizeof(glm::u8vec4);
}

void CVertexBufferPositionTexcoordColor::Disable(CShader::E_RENDER_MODE _eRenderMode)
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
    iSlot = pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_COLOR);
    if(iSlot >= 0)
    {
        glDisableVertexAttribArray(iSlot);
    }
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}
