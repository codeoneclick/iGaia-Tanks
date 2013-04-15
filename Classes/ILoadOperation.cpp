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

void ILoadOperation_INTERFACE::Register_Resource(IResource_INTERFACE *_resource)
{
    assert(m_name.length() != 0);
    assert(_resource != nullptr);
    _resource->m_name = m_name;
}

void ILoadOperation_INTERFACE::Execute_CallbackCommands(TSharedPtrResource _resource)
{
    for(const CResourceLoadingCommands* commands : m_commands)
    {
		commands->Execute_OnResourceLoadedCallback(_resource);
    }
    m_commands.clear();
}