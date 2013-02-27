//
//  CResourceLoadCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/7/13.
//
//

#include "CResourceLoadCallback.h"

void CResourceLoadCallback::ConnectResourceDidLoadListener(const __RESOURCE_DID_LOAD_LISTENER &_listener)
{
    assert(_listener != nullptr);
    m_resourceDidLoadListener = _listener;
}

void CResourceLoadCallback::DispatchResourceDidLoad(IResource_INTERFACE *_resource)
{
    assert(m_resourceDidLoadListener != nullptr);
    m_resourceDidLoadListener(_resource);
}


CResourceLoadCallback_INTERFACE::CResourceLoadCallback_INTERFACE(void)
{
    ConnectResourceLoadCallback();
}

void CResourceLoadCallback_INTERFACE::ConnectResourceLoadCallback(void)
{
    m_resourceLoadCallback.ConnectResourceDidLoadListener(std::bind(&CResourceLoadCallback_INTERFACE::OnResourceDidLoad, this, std::placeholders::_1));
}