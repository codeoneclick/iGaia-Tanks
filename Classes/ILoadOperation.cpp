//
//  ILoadOperation.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/26/13.
//
//

#include "ILoadOperation.h"

ILoadOperation_INTERFACE::ILoadOperation_INTERFACE(void) :
	m_status(E_PARSER_STATUS_UNKNOWN)
{

}

void ILoadOperation_INTERFACE::_Register(IResource_INTERFACE* _resource)
{
    _resource->m_name = m_name;
}

void ILoadOperation_INTERFACE::Execute_ResourceLoadCallbacks(TSharedPtrResource _resource)
{
    for(CResourceLoadCallback* _listener : m_listeners)
    {
		_listener->Execute_OnResourceDidLoadCallback(_resource);
    }
    m_listeners.clear();
}