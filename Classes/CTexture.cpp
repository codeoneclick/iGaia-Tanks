//
//  CTexture.cpp
//  iGaia
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTexture.h"

CTexture::CTexture(void)
{
    m_eResourceType = E_RESOURCE_TYPE_TEXTURE;
    m_eWrapMode = E_WRAP_MODE_REPEAT;
}

CTexture::~CTexture(void)
{
    glDeleteTextures(1, &m_iHandle);
}

void CTexture::Set_WrapMode(CTexture::E_WRAP_MODE _eWrapMode)
{
    m_eWrapMode = _eWrapMode;
    glBindTexture(GL_TEXTURE_2D, m_iHandle);
    if(m_eWrapMode == CTexture::E_WRAP_MODE_REPEAT)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    }
    else if(m_eWrapMode == CTexture::E_WRAP_MODE_CLAMP)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}

void CTexture::Set_Handle(GLuint _iHandle)
{
    m_iHandle = _iHandle;
    Set_WrapMode(m_eWrapMode);
}

