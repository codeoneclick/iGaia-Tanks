//
//  CMeshMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "CMeshMgr.h"
#include "CMesh.h"
#include "CLoadOperation_MDL.h"

CMeshMgr::CMeshMgr(void)
{

}

CMeshMgr::~CMeshMgr(void)
{
    
}

TSharedPtrResource CMeshMgr::StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadingCommands* _observer)
{
    TSharedPtrMesh mesh = nullptr;
    
    if(_thread == E_RESOURCE_LOAD_THREAD_SYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            mesh = std::static_pointer_cast<CMesh>(m_resourceContainer[_filename]);
        }
        else
        {
            TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_MDL());
            operation->Load(_filename);
            if(operation->Get_Status() == E_PARSER_STATUS_DONE)
            {
				mesh = TSharedPtrMesh(static_cast<CMesh*>(operation->Link()));
                m_resourceContainer.insert(std::make_pair(_filename, mesh));
            }
        }
    }
    else if(_thread == E_RESOURCE_LOAD_THREAD_ASYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            mesh = std::static_pointer_cast<CMesh>(m_resourceContainer[_filename]);
            Notify_ResourceLoadingObserver(_observer, mesh);
        }
        else
        {
            if(m_operationsQueue.find(_filename) == m_operationsQueue.end())
            {
                TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_MDL());
                m_operationsQueue.insert(std::make_pair(_filename, operation));
            }
            TSharedPtrLoadOperation operation = m_operationsQueue.find(_filename)->second;
            operation->Register_ResourceLoadingObserver(_observer);
        }
    }
    return mesh;
}


