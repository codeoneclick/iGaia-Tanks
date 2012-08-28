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
}

CTexture::~CTexture(void)
{
    glDeleteTextures(1, &m_iHandle);
}