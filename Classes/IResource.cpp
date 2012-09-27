//
//  IResource.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResource.h"

IResource::IResource(void)
{
    m_referenceCount = 0;
    m_resourceType = E_RESOURCE_TYPE_NONE;
    m_creationMode = E_CREATION_MODE_NATIVE;
}

IResource::~IResource(void)
{
    std::cout<<"[IResource::~IResource]"<<std::endl;
}





