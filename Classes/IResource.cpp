//
//  IResource.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResource.h"
#include "CResourceMgr.h"
#include "IResourceLoaderDelegate.h"

IResource::IResource(void) : m_iEventHandle(0), m_iRefCount(0), m_eCreationMode(E_CREATION_MODE_NATIVE)
{

}

IResource::~IResource(void)
{
    std::cout<<"[IResource::~IResource]"<<std::endl;
    m_lListeners.clear();
}

IResource::EventHandle IResource::AddEventListener(const EventSignature &_pListener)
{
    m_lListeners.insert(std::make_pair(++m_iEventHandle, _pListener));
    return m_iEventHandle;
}

void IResource::RemoveEventListener(EventHandle _eventHandler)
{
    m_lListeners.erase(_eventHandler);
}

void IResource::DispatchEvent(void)
{
    for(auto& pListener : m_lListeners)
    {
        pListener.second(this, pListener.first);
    }
    m_lListeners.clear();
}





