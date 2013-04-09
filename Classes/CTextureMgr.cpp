
#include "CTextureMgr.h"
#include "CTexture.h"
#include "CLoadOperation_PVR.h"

CTextureMgr::CTextureMgr(void)
{

}

CTextureMgr::~CTextureMgr(void)
{
    
}

TSharedPtrResource CTextureMgr::StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadingCommands* _observer)
{
    TSharedPtrTexture texture = nullptr;
    
    if(_thread == E_RESOURCE_LOAD_THREAD_SYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            texture = std::static_pointer_cast<CTexture>(m_resourceContainer[_filename]);
        }
        else
        {
            TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_PVR());
            operation->Load(_filename);
            if(operation->Get_Status() == E_PARSER_STATUS_DONE)
            {
				texture = TSharedPtrTexture(static_cast<CTexture*>(operation->Link()));
                m_resourceContainer.insert(std::make_pair(_filename, texture));
            }
        }
    }
    else if(_thread == E_RESOURCE_LOAD_THREAD_ASYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            texture = std::static_pointer_cast<CTexture>(m_resourceContainer[_filename]);
            Notify_ResourceLoadingObserver(_observer, texture);
        }
        else
        {
            if(m_operationsQueue.find(_filename) == m_operationsQueue.end())
            {
                TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_PVR());
                m_operationsQueue.insert(std::make_pair(_filename, operation));
            }
            TSharedPtrLoadOperation operation = m_operationsQueue.find(_filename)->second;
            operation->Register_ResourceLoadingObserver(_observer);
        }
    }
    return texture;
}



