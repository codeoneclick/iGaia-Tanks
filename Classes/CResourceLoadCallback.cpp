//
//  CResourceLoadCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/7/13.
//
//

#include "CResourceLoadCallback.h"

void CResourceLoadCallback::ConnectResourceDidLoadListener(const __RESOURCE_DID_LOAD_LISTENER &_tListener)
{
    assert(_tListener != nullptr);
    m_tResourceDidLoadListener = _tListener;
}

void CResourceLoadCallback::NotifyResourceDidLoadListener(IResource *_pResource, E_RESOURCE_TYPE _eResourceType)
{
    assert(m_tResourceDidLoadListener != nullptr);
    m_tResourceDidLoadListener(_pResource, _eResourceType);
}


CResourceLoadCallback_INTERFACE::CResourceLoadCallback_INTERFACE(void)
{
    ConnectResourceLoadCallback();
}

void CResourceLoadCallback_INTERFACE::ConnectResourceLoadCallback(void)
{
    m_tResourceLoadCallback.ConnectResourceDidLoadListener(std::bind(&CResourceLoadCallback_INTERFACE::OnResourceDidLoad, this, std::placeholders::_1, std::placeholders::_2));
}