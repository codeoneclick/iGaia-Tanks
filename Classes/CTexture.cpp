//
//  CTexture.cpp
//  iGaia
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CTexture.h"

CTexture::CTexture(void) :
IResource_INTERFACE(E_RESOURCE_TYPE_TEXTURE),
m_handle(0),
m_width(0),
m_height(0),
m_wrap(GL_REPEAT)
{

}

CTexture::~CTexture(void)
{
    glDeleteTextures(1, &m_handle);
}

void CTexture::Link(ui32 _handle, ui32 _width, ui32 _height)
{
    m_handle = _handle;
    m_width = _width;
    m_height = _height;
    m_isLinked = true;
}

void CTexture::Set_Wrap(ui32 _wrap)
{
    m_wrap = _wrap;
}

void CTexture::Bind(void)
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap);
}

void CTexture::Unbind(void)
{
    glBindTexture(GL_TEXTURE_2D, NULL);
}