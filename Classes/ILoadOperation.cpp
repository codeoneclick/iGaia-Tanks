//
//  ILoadOperation.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/26/13.
//
//

#include "ILoadOperation.h"

void ILoadOperation_INTERFACE::Register(IResource_INTERFACE* _resource)
{
    _resource->m_name = m_name;
}

void ILoadOperation_INTERFACE::Dispatch(IResource_INTERFACE* _resource)
{
    for(CResourceLoadCallback* _listener : m_listeners)
    {
        _listener->DispatchResourceDidLoad(_resource);
    }
    m_listeners.clear();
}