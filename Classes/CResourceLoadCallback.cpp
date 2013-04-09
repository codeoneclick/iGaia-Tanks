//
//  CResourceLoadCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/7/13.
//
//

#include "CResourceLoadCallback.h"

void CResourceLoadCallback::Register_OnResourceLoadCallback(const __ON_RESOURCE_DID_LOAD_CALLBACK& _callback)
{
	assert(_callback != nullptr);
	m_onResourceDidLoadCallback = _callback;
}

void CResourceLoadCallback::Execute_OnResourceDidLoadCallback(TSharedPtrResource _resource)
{
	assert(m_onResourceDidLoadCallback != nullptr);
    m_onResourceDidLoadCallback(_resource);
}


CResourceLoadCallback_INTERFACE::CResourceLoadCallback_INTERFACE(void)
{
	RegisterCommands();
}

void CResourceLoadCallback_INTERFACE::RegisterCommands(void)
{
	m_commands.Register_OnResourceLoadCallback(std::bind(&CResourceLoadCallback_INTERFACE::OnResourceDidLoad, this, std::placeholders::_1));
}