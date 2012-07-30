//
//  CIndexBuffer.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer(unsigned int _iNumIndexes, unsigned int _eMode)
{
    m_pSourceData = new unsigned short[_iNumIndexes];
    m_pWorkingSourceData = NULL;
    m_iNumIndexes = _iNumIndexes;
    m_iNumWorkingIndexes = m_iNumIndexes;
    m_bIsCommited = false;
    m_eMode = _eMode;
    glGenBuffers(1, &m_hHandle);
}

CIndexBuffer::~CIndexBuffer(void)
{  
    SAFE_DELETE_ARRAY(m_pWorkingSourceData);
    SAFE_DELETE_ARRAY(m_pSourceData);
    try
    {
        std::cout<<"[~CIndexBuffer] glDeleteBuffers id :"<<m_hHandle<<std::endl;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
        glDeleteBuffers(1, &m_hHandle);
    }
    catch (int _error)
    {
        std::cout<<"[~CIndexBuffer] glDeleteBuffers exception id :"<<_error<<std::endl;
    }
    m_hHandle = 0;
}

unsigned short* CIndexBuffer::Get_SourceData(void)
{
    return m_pSourceData;
}

unsigned short* CIndexBuffer::Get_SourceDataFromVRAM(void)
{
    if(m_bIsCommited == true)
    {
        return NULL;
    }
    else
    {
        if(m_pWorkingSourceData == NULL)
        {
            m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
            memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
        }
        return m_pWorkingSourceData;
    }
}

void CIndexBuffer::Enable(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hHandle);
}

void CIndexBuffer::Disable(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

unsigned short* CIndexBuffer::Get_WorkingSourceDataRef(void)
{
    if(m_pWorkingSourceData == NULL)
    {
        m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
        memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
    }
    return m_pWorkingSourceData;
}

void CIndexBuffer::Commit(void)
{
    if(!m_bIsCommited)
    {
        if(m_pWorkingSourceData == NULL)
        {
            m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
            memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_iNumWorkingIndexes, m_pWorkingSourceData, m_eMode);
        m_bIsCommited = true;
    }
    else
    {
        if(m_pWorkingSourceData == NULL)
        {
            m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
            memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_iNumWorkingIndexes, m_pWorkingSourceData, m_eMode);
    }
}



