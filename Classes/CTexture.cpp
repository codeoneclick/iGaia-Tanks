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
    m_pSourceData = NULL;
    m_eResourceType = E_RESOURCE_TYPE_TEXTURE;
}

CTexture::~CTexture(void)
{
    glDeleteTextures(1, &m_pSourceData->m_hTextureHanlde);
    delete m_pSourceData;
}

void CTexture::Set_SourceData(void *_pSourceData)
{
    m_pSourceData = static_cast<SSourceData*>(_pSourceData);
}
