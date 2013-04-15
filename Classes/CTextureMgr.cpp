
#include "CTextureMgr.h"
#include "CTexture.h"
#include "CLoadOperation_PVR.h"

CTextureMgr::CTextureMgr(void)
{

}

CTextureMgr::~CTextureMgr(void)
{
    
}

TSharedPtrResource CTextureMgr::Execute_LoadingOperationSynchronous(const std::string &_filename)
{
    TSharedPtrTexture texture = nullptr;
    if(m_resources.find(_filename) != m_resources.end())
    {
        texture = std::static_pointer_cast<CTexture>(m_resources[_filename]);
    }
    else
    {
        TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_PVR());
        operation->Load(_filename);
        if(operation->Get_Status() == E_PARSER_STATUS_DONE)
        {
            texture = TSharedPtrTexture(static_cast<CTexture*>(operation->Link()));
            m_resources.insert(std::make_pair(_filename, texture));
        }
    }
    return texture;
}

void CTextureMgr::Execute_LoadingOperationAsynchronous(const std::string &_filename, const CResourceLoadingCommands *_commands)
{
    TSharedPtrTexture texture = nullptr;
    if(m_resources.find(_filename) != m_resources.end())
    {
        texture = std::static_pointer_cast<CTexture>(m_resources[_filename]);
        Execute_CallbackCommands(_commands, texture);
    }
    else
    {
        if(m_operationsQueue.find(_filename) == m_operationsQueue.end())
        {
            TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_PVR());
            m_operationsQueue.insert(std::make_pair(_filename, operation));
        }
        TSharedPtrLoadOperation operation = m_operationsQueue.find(_filename)->second;
        operation->Register_ResourceLoadingCommands(_commands);
    }
}



