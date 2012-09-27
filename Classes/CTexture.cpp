//
//  CTexture.cpp
//  iGaia
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTexture.h"

CTexture::CTexture(unsigned int _handle, unsigned int _width, unsigned int _height)
{
    m_resourceType = E_RESOURCE_TYPE_TEXTURE;
    m_handle = _handle;
    m_width = _width;
    m_height = _height;
}

CTexture::~CTexture(void)
{
    glDeleteTextures(1, &m_handle);
}

void CTexture::Set_WrapMode(CTexture::E_WRAP_MODE _wrapMode)
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
    if(_wrapMode == CTexture::E_WRAP_MODE_REPEAT)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    }
    else if(_wrapMode == CTexture::E_WRAP_MODE_CLAMP)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}

void CTexture::PutInstance(IResource *_resource)
{
    CTexture* texture = static_cast<CTexture*>(_resource);
    m_handle = texture->m_handle;
    m_width = texture->m_width;
    m_height = texture->m_height;
}

