//
//  IResourceMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "IResourceMgr.h"

IResourceMgr_INTERFACE::IResourceMgr_INTERFACE(void)
{
    m_thread = std::thread(&IResourceMgr_INTERFACE::Thread, this);
}

IResourceMgr_INTERFACE::~IResourceMgr_INTERFACE(void)
{
    
}

void IResourceMgr_INTERFACE::Dispatch(CResourceLoadCallback_INTERFACE* _listener, IResource_INTERFACE* _resource)
{
	_listener->Get_Commands()->Execute_OnResourceDidLoadCallback(_resource);
}

void IResourceMgr_INTERFACE::AddListener(CResourceLoadCallback_INTERFACE* _listener, ILoadOperation_INTERFACE* _operation)
{
    
}

void IResourceMgr_INTERFACE::Thread(void)
{
    for(std::map<std::string, TSharedPtrLoadOperation>::iterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        TSharedPtrLoadOperation operation = iterator->second;
        if(operation->Get_Status() == E_PARSER_STATUS_UNKNOWN)
        {
            operation->Load(iterator->first);
        }
    }
}

void IResourceMgr_INTERFACE::CancelLoadOperation(CResourceLoadCallback_INTERFACE *_listener)
{
    for(std::map<std::string, TSharedPtrLoadOperation>::iterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        TSharedPtrLoadOperation operation = iterator->second;
		operation->Unregister_ResourceLoadCallback(_listener->Get_Commands());
    }
}

void IResourceMgr_INTERFACE::Update(void)
{
    for(std::map<std::string, TSharedPtrLoadOperation>::iterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        TSharedPtrLoadOperation operation = iterator->second;
        if(operation->Get_Status() == E_PARSER_STATUS_DONE)
        {
			TSharedPtrResource resource = TSharedPtrResource(operation->Link());
            assert(resource != nullptr);
			operation->Execute_ResourceLoadCallbacks(resource);
            m_resourceContainer.insert(std::make_pair(iterator->first, resource));
            std::lock_guard<std::mutex>lock(m_mutex);
            m_operationsQueue.erase(iterator);
        }
        else if(operation->Get_Status() == E_PARSER_STATUS_ERROR)
        {
            std::lock_guard<std::mutex>lock(m_mutex);
            m_operationsQueue.erase(iterator);
        }
    }
}

void IResourceMgr_INTERFACE::UnloadResource(TSharedPtrResource _resource)
{
    std::map<std::string, TSharedPtrResource>::iterator iterator = m_resourceContainer.find(_resource->Get_Name());
	assert(iterator != m_resourceContainer.end());
	m_resourceContainer.erase(iterator);
}
