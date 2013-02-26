//
//  IResource.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "IResource.h"

IResource::IResource(void)
{
    m_referencesCount = 0;
}

IResource::~IResource(void)
{
    
}

void IResource::NotifyLoadingListeners(void)
{
    for(CResourceLoadCallback* _listener : m_listeners)
    {
        _listener->NotifyResourceDidLoadListener(this);
    }
    m_listeners.clear();
}





