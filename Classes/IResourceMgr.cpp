
#include "IResourceMgr.h"

IResourceMgr_INTERFACE::IResourceMgr_INTERFACE(void) :
m_isThreadRunning(TRUE)
{
    m_thread = std::thread(&IResourceMgr_INTERFACE::Thread, this);
}

IResourceMgr_INTERFACE::~IResourceMgr_INTERFACE(void)
{
    m_isThreadRunning = FALSE;
    usleep(1);
}

void IResourceMgr_INTERFACE::Execute_CallbackCommands(const CResourceLoadingCommands *_commands, TSharedPtrResource _resource)
{
	_commands->Execute_OnResourceLoadedCallback(_resource);
}

void IResourceMgr_INTERFACE::Thread(void)
{
    while (m_isThreadRunning)
    {
        for(TOperationIterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
        {
            TSharedPtrLoadOperation operation = iterator->second;
            if(operation->Get_Status() == E_PARSER_STATUS_UNKNOWN)
            {
                operation->Load(iterator->first);
            }
        }
    }
}

void IResourceMgr_INTERFACE::Cancel_LoadingOperation(const CResourceLoadingCommands *_commands)
{
    for(TOperationIterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        TSharedPtrLoadOperation operation = iterator->second;
		operation->Unregister_ResourceLoadingCommands(_commands);
        m_operationsQueue.erase(iterator);
    }
}

void IResourceMgr_INTERFACE::Update(void)
{
    for(TOperationIterator iterator = m_operationsQueue.begin(); iterator != m_operationsQueue.end(); ++iterator)
    {
        TSharedPtrLoadOperation operation = iterator->second;
        if(operation->Get_Status() == E_PARSER_STATUS_DONE)
        {
			TSharedPtrResource resource = TSharedPtrResource(operation->Link());
            assert(resource != nullptr);
			operation->Execute_CallbackCommands(resource);
            m_resources.insert(std::make_pair(iterator->first, resource));
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

void IResourceMgr_INTERFACE::Unload_Resource(TSharedPtrResource _resource)
{
    TResourceIterator iterator = m_resources.find(_resource->Get_Name());
	assert(iterator != m_resources.end());
	m_resources.erase(iterator);
}
