//
//  CIndexBuffer.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer(unsigned int _numIndexes, unsigned int _mode)
{
    m_dataSource = new unsigned short[_numIndexes];
    m_numIndexes = _numIndexes;
    m_mode = _mode;
    glGenBuffers(1, &m_hanlde);
}

CIndexBuffer::~CIndexBuffer(void)
{  
    SAFE_DELETE_ARRAY(m_dataSource);
    std::cout<<"[~CIndexBuffer] glDeleteBuffers id :"<<m_hanlde<<std::endl;
    glDeleteBuffers(1, &m_hanlde);
    m_hanlde = 0;
}

unsigned short* CIndexBuffer::Lock(void)
{
    return m_dataSource;
}

void CIndexBuffer::Unlock(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hanlde);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_numIndexes, m_dataSource, m_mode);
}

void CIndexBuffer::Bind(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hanlde);
}

void CIndexBuffer::Unbind(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}







