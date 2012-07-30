//
//  CVertexBuffer.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
/*
#include "CVertexBuffer.h"

const std::string CVertexBuffer::k_SLOT_POSITION   = "IN_SLOT_Position";
const std::string CVertexBuffer::k_SLOT_TEXCOORD   = "IN_SLOT_TexCoord";
const std::string CVertexBuffer::k_SLOT_NORMAL     = "IN_SLOT_Normal";
const std::string CVertexBuffer::k_SLOT_TANGENT    = "IN_SLOT_Tangent";
const std::string CVertexBuffer::k_SLOT_COLOR      = "IN_SLOT_Color";

glm::u8vec4 CVertexBuffer::CompressVEC3(const glm::vec3 &_vUncopressed)
{
    glm::vec3 vNormalized = glm::normalize(_vUncopressed);
    glm::u8vec4 vCompressed;
    vCompressed.x = static_cast<unsigned char>((vNormalized.x + 1.0f) * 0.5f * 255.0f);
    vCompressed.y = static_cast<unsigned char>((vNormalized.y + 1.0f) * 0.5f * 255.0f);
    vCompressed.z = static_cast<unsigned char>((vNormalized.z + 1.0f) * 0.5f * 255.0f);
    vCompressed.w = 0;
    
    return vCompressed;
}

glm::vec3 CVertexBuffer::UnCompressU8VEC4(const glm::u8vec4 _vCompressed)
{
    glm::vec3 vUnCompressed;
    vUnCompressed.x = static_cast<float>(_vCompressed.x / (255.0f * 0.5f) - 1.0f);
    vUnCompressed.y = static_cast<float>(_vCompressed.y / (255.0f * 0.5f) - 1.0f);
    vUnCompressed.z = static_cast<float>(_vCompressed.z / (255.0f * 0.5f) - 1.0f);
    return vUnCompressed;
}

CVertexBuffer::CVertexBuffer(unsigned int _iNumVertexes)
{
    m_iNumVertexes = _iNumVertexes;
    m_iSize = 32;
    m_bIsInVRAM = false;
    m_eMode = GL_STATIC_DRAW;
    
    m_pSourceData = new char[m_iNumVertexes * m_iSize];

    m_WorkingSourceData.m_pPositionSourceData = NULL;
    m_WorkingSourceData.m_pTexcoordSourceData = NULL;
    m_WorkingSourceData.m_pNormalSourceData   = NULL;
    m_WorkingSourceData.m_pTangentSourceData  = NULL;
    m_WorkingSourceData.m_pColorSourceData    = NULL;
}

CVertexBuffer::~CVertexBuffer(void)
{
    SAFE_DELETE_ARRAY(m_pSourceData);
    
    SAFE_DELETE_ARRAY(m_WorkingSourceData.m_pPositionSourceData);
    SAFE_DELETE_ARRAY(m_WorkingSourceData.m_pTexcoordSourceData);
    SAFE_DELETE_ARRAY(m_WorkingSourceData.m_pNormalSourceData);
    SAFE_DELETE_ARRAY(m_WorkingSourceData.m_pTangentSourceData);
    SAFE_DELETE_ARRAY(m_WorkingSourceData.m_pColorSourceData);
    
    if(m_bIsInVRAM)
    {
        glDeleteBuffers(1, &m_iHandle);
    }
}

void CVertexBuffer::AppendWorkingSourceData(void)
{
    unsigned char iBytesPerVertex = 0;
    if(m_WorkingSourceData.m_pPositionSourceData != NULL)
    {
        iBytesPerVertex += sizeof(glm::vec3);
    }
    if(m_WorkingSourceData.m_pTexcoordSourceData != NULL)
    {
        iBytesPerVertex += sizeof(glm::vec2);
    }
    if(m_WorkingSourceData.m_pNormalSourceData != NULL)
    {
        iBytesPerVertex += sizeof(glm::u8vec4);
    }
    if(m_WorkingSourceData.m_pTangentSourceData != NULL)
    {
        iBytesPerVertex += sizeof(glm::u8vec4);
    }
    if(m_WorkingSourceData.m_pColorSourceData != NULL)
    {
        iBytesPerVertex += sizeof(glm::u8vec4);
    }
    
    unsigned int iPtrOffset = 0;
    unsigned int iPaddingSize = m_iSize - iBytesPerVertex;

    for(unsigned int i = 0; i < m_iNumVertexes; ++i)
    {
        if(m_WorkingSourceData.m_pPositionSourceData != NULL)
        {
            memcpy(m_pSourceData + iPtrOffset, &m_WorkingSourceData.m_pPositionSourceData[i][0], sizeof(glm::vec3));
            iPtrOffset += sizeof(glm::vec3);
        }
        if(m_WorkingSourceData.m_pTexcoordSourceData != NULL)
        {
            memcpy(m_pSourceData + iPtrOffset, &m_WorkingSourceData.m_pTexcoordSourceData[i][0], sizeof(glm::vec2));
            iPtrOffset += sizeof(glm::vec2);
        }
        if(m_WorkingSourceData.m_pNormalSourceData != NULL)
        {
            memcpy(m_pSourceData + iPtrOffset, &m_WorkingSourceData.m_pNormalSourceData[i][0], sizeof(glm::u8vec4));
            iPtrOffset += sizeof(glm::u8vec4);
        }
        if(m_WorkingSourceData.m_pTangentSourceData != NULL)
        {
            memcpy(m_pSourceData + iPtrOffset, &m_WorkingSourceData.m_pTangentSourceData[i][0], sizeof(glm::u8vec4));
            iPtrOffset += sizeof(glm::u8vec4);
        }
        if(m_WorkingSourceData.m_pColorSourceData != NULL)
        {
            memcpy(m_pSourceData + iPtrOffset, &m_WorkingSourceData.m_pColorSourceData[i][0], sizeof(glm::u8vec4));
            iPtrOffset += sizeof(glm::u8vec4);
        }
        
        iPtrOffset += iPaddingSize;
    }
}

void CVertexBuffer::Enable(void)
{
    if(m_bIsInVRAM)
    {
        unsigned char iBytesPerVertex = 0;
        glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
        if(m_iPositionSlot >= 0 && m_WorkingSourceData.m_pPositionSourceData != NULL)
        {
            glEnableVertexAttribArray(m_iPositionSlot);
            glVertexAttribPointer(m_iPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += sizeof(glm::vec3);
        }
        else if(m_WorkingSourceData.m_pPositionSourceData != NULL)
        {
            iBytesPerVertex += sizeof(glm::vec3);
        }
        
        if(m_iTexcoordSlot >= 0 && m_WorkingSourceData.m_pTexcoordSourceData != NULL)
        {
            glEnableVertexAttribArray(m_iTexcoordSlot);
            glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += sizeof(glm::vec2);
        }
        else if(m_WorkingSourceData.m_pTexcoordSourceData != NULL)
        {
            iBytesPerVertex += sizeof(glm::vec2);
        }
        
        if(m_iNormalSlot >= 0 && m_WorkingSourceData.m_pNormalSourceData != NULL)
        {
            glEnableVertexAttribArray(m_iNormalSlot);
            glVertexAttribPointer(m_iNormalSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += sizeof(glm::u8vec4);
        }
        else if(m_WorkingSourceData.m_pNormalSourceData != NULL)
        {
            iBytesPerVertex += sizeof(glm::u8vec4);
        }
        
        if(m_iTangentSlot >= 0 && m_WorkingSourceData.m_pTangentSourceData != NULL)
        {
            glEnableVertexAttribArray(m_iTangentSlot);
            glVertexAttribPointer(m_iTangentSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize,(GLvoid*)iBytesPerVertex);
            iBytesPerVertex += sizeof(glm::u8vec4);
        }
        else if(m_WorkingSourceData.m_pTangentSourceData != NULL)
        {
            iBytesPerVertex += sizeof(glm::u8vec4);
        }
        
        if(m_iColorSlot >= 0 && m_WorkingSourceData.m_pColorSourceData != NULL)
        {
            glEnableVertexAttribArray(m_iColorSlot);
            glVertexAttribPointer(m_iColorSlot,  4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize,(GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 4;
        }
        else if(m_WorkingSourceData.m_pColorSourceData != NULL)
        {
            iBytesPerVertex += 4;
        }
        return; 
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    const GLvoid* pPositionSource = NULL;
    const GLvoid* pTexcoordSource = NULL;
    const GLvoid* pNormalSource   = NULL;
    const GLvoid* pTangentSource  = NULL;
    const GLvoid* pColorSource    = NULL;
    
    unsigned int iBytesPerVertex = 0;
    if(m_WorkingSourceData.m_pPositionSourceData != NULL)
    {
        pPositionSource = m_pSourceData + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::vec3);
    }
    if(m_WorkingSourceData.m_pTexcoordSourceData != NULL)
    {
        pTexcoordSource = m_pSourceData + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::vec2);
    }
    if(m_WorkingSourceData.m_pNormalSourceData != NULL)
    {
        pNormalSource = m_pSourceData + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::u8vec4);
    }
    if(m_WorkingSourceData.m_pTangentSourceData != NULL)
    {
        pTangentSource = m_pSourceData + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::u8vec4);
    }
    if(m_WorkingSourceData.m_pColorSourceData != NULL)
    {
        pColorSource = m_pSourceData + iBytesPerVertex;
    }

    if(m_iPositionSlot >= 0 && m_WorkingSourceData.m_pPositionSourceData != NULL) 
    {
        glVertexAttribPointer(m_iPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iSize, pPositionSource);
        glEnableVertexAttribArray(m_iPositionSlot);
    }
    if(m_iTexcoordSlot >= 0 && m_WorkingSourceData.m_pTexcoordSourceData != NULL)
    {
        glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, pTexcoordSource);
        glEnableVertexAttribArray(m_iTexcoordSlot); 
    }
    if(m_iNormalSlot >= 0 && m_WorkingSourceData.m_pNormalSourceData != NULL)
    {
        glVertexAttribPointer(m_iNormalSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, pNormalSource);
        glEnableVertexAttribArray(m_iNormalSlot);
    }
    if(m_iTangentSlot >= 0 && m_WorkingSourceData.m_pTangentSourceData != NULL)
    {
        glVertexAttribPointer(m_iTangentSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, pTangentSource);
        glEnableVertexAttribArray(m_iTangentSlot);
    }
    if(m_iColorSlot >= 0 && m_WorkingSourceData.m_pColorSourceData != NULL)
    {
        glVertexAttribPointer(m_iColorSlot,  4, GL_UNSIGNED_BYTE, GL_TRUE, m_iSize, pColorSource);
        glEnableVertexAttribArray(m_iColorSlot);
    }
}

void CVertexBuffer::Disable()
{
    if(m_iPositionSlot >= 0)
    {
        glDisableVertexAttribArray(m_iPositionSlot);
    }
    if(m_iTexcoordSlot >= 0)
    {
        glDisableVertexAttribArray(m_iTexcoordSlot); 
    }
    if(m_iNormalSlot >= 0)
    {
        glDisableVertexAttribArray(m_iNormalSlot);
    }
    if(m_iTangentSlot >= 0)
    {
        glDisableVertexAttribArray(m_iTangentSlot);
    }
    if(m_iColorSlot >= 0)
    {
        glDisableVertexAttribArray(m_iColorSlot);
    }
}

void CVertexBuffer::CommitFromRAMToVRAM(void)
{
    if(m_bIsInVRAM)
    {*/
        /*glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
        char* pSourceDataVRAM = static_cast<char*>(glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES));
        if(pSourceDataVRAM != NULL)
        {
            memcpy(pSourceDataVRAM, m_pSource,  m_iSize * m_iNumVertexes);
        }
        glUnmapBufferOES(GL_ARRAY_BUFFER);*/
        /*
        glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
        glBufferData(GL_ARRAY_BUFFER, m_iSize * m_iNumVertexes, m_pSourceData, m_eMode);
    }
    else
    {
        glGenBuffers(1, &m_iHandle);
        glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
        glBufferData(GL_ARRAY_BUFFER, m_iSize * m_iNumVertexes, NULL, m_eMode);
        glBufferSubData(GL_ARRAY_BUFFER, NULL, m_iSize * m_iNumVertexes, m_pSourceData);
        m_bIsInVRAM = true;
    }
}

void CVertexBuffer::Lock(void)
{
    if(!m_bIsInVRAM)
    {
        return;
    }
}

void CVertexBuffer::Unlock(void)
{
    if(!m_bIsInVRAM)
    {
        return;
    }
}
*/















