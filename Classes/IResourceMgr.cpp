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
    _listener->Get_Commands()->DispatchResourceDidLoad(_resource);
    _resource->IncReferencesCount();
}

void IResourceMgr_INTERFACE::AddListener(CResourceLoadCallback_INTERFACE* _listener, ILoadOperation_INTERFACE* _operation)
{
    
}

void IResourceMgr_INTERFACE::Thread(void)
{
    for(std::map<std::string, ILoadOperation_INTERFACE*>::iterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        ILoadOperation_INTERFACE* operation = iterator->second;
        if(operation->Get_Status() == E_PARSER_STATUS_UNKNOWN)
        {
            operation->Load(iterator->first);
        }
    }
}

void IResourceMgr_INTERFACE::CancelLoadOperation(CResourceLoadCallback_INTERFACE *_listener)
{
    for(std::map<std::string, ILoadOperation_INTERFACE*>::iterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        ILoadOperation_INTERFACE* operation = iterator->second;
        operation->RemoveLoadingListener(_listener->Get_Commands());
    }
}

void IResourceMgr_INTERFACE::Update(void)
{
    for(std::map<std::string, ILoadOperation_INTERFACE*>::iterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        ILoadOperation_INTERFACE* operation = iterator->second;
        if(operation->Get_Status() == E_PARSER_STATUS_DONE)
        {
            IResource_INTERFACE* resource = operation->Build();
            assert(resource != nullptr);
            operation->Dispatch(resource);
            m_resourceContainer.insert(std::make_pair(iterator->first, resource));
            std::lock_guard<std::mutex>lock(m_mutex);
            m_operationsQueue.erase(iterator);
            delete operation;
        }
        else if(operation->Get_Status() == E_PARSER_STATUS_ERROR)
        {
            std::lock_guard<std::mutex>lock(m_mutex);
            m_operationsQueue.erase(iterator);
            delete operation;
        }
    }
}

void IResourceMgr_INTERFACE::UnloadResource(IResource_INTERFACE *_resource)
{
    std::map<std::string, IResource_INTERFACE*>::iterator iterator = m_resourceContainer.find(_resource->Get_Name());
    if(iterator != m_resourceContainer.end())
    {
        _resource->DecReferencesCount();
        if(_resource->Get_ReferencesCount() == 0)
        {
            m_resourceContainer.erase(iterator);
            delete _resource;
        }
    }
    else
    {
        delete _resource;
    }
}
