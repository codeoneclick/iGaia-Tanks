//
//  CIndexBuffer.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/26/13.
//
//

#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer(ui32 _numIndexes, GLenum _mode)
{
    m_numIndexes = _numIndexes;
    m_maxNumIndexes = m_numIndexes;
    m_data = new ui16[m_numIndexes];
    m_mode = _mode;
    m_currentHandleIndex = -1;
    glGenBuffers(K_NUM_REPLACEMENT_INDEX_BUFFERS, m_handles);
}

CIndexBuffer::~CIndexBuffer(void)
{
    delete [] m_data;
    glDeleteBuffers(K_NUM_REPLACEMENT_INDEX_BUFFERS, m_handles);
}

void CIndexBuffer::Unlock(void)
{
    m_currentHandleIndex = (m_currentHandleIndex >= (K_NUM_REPLACEMENT_INDEX_BUFFERS - 1)) ? 0 : m_currentHandleIndex + 1;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handles[m_currentHandleIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ui16) * m_numIndexes, m_data, m_mode);
}

void CIndexBuffer::Bind(void)
{
    assert(m_currentHandleIndex >= 0 && m_currentHandleIndex <= (K_NUM_REPLACEMENT_INDEX_BUFFERS - 1));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handles[m_currentHandleIndex]);
}

void CIndexBuffer::Unbind(void)
{
    assert(m_currentHandleIndex >= 0 && m_currentHandleIndex <= (K_NUM_REPLACEMENT_INDEX_BUFFERS - 1));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
