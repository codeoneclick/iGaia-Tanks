//
//  CTexture.cpp
//  iGaia
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CTexture.h"

CTexture::CTexture(ui32 _handle, ui32 _width, ui32 _height)
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

void CTexture::Set_WrapMode(ui32 _mode)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _mode);
}