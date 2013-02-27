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

IResource_INTERFACE* CMeshMgr::StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadCallback_INTERFACE* _listener)
{
    CMesh* mesh = nullptr;
    
    if(_thread == E_RESOURCE_LOAD_THREAD_SYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            mesh = static_cast<CMesh*>(m_resourceContainer[_filename]);
            mesh->IncReferencesCount();
        }
        else
        {
            CLoadOperation_MDL* operation = new CLoadOperation_MDL();
            operation->Load(_filename);
            if(operation->Get_Status() == E_PARSER_STATUS_DONE)
            {
                mesh = static_cast<CMesh*>(operation->Build());
                operation->Dispatch(mesh);
                mesh->IncReferencesCount();
            }
            delete operation;
        }
    }
    else if(_thread == E_RESOURCE_LOAD_THREAD_ASYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            CMesh* mesh = static_cast<CMesh*>(m_resourceContainer[_filename]);
            Dispatch(_listener, mesh);
        }
        else
        {
            if(m_operationsQueue.find(_filename) == m_operationsQueue.end())
            {
                CLoadOperation_MDL* operation = new CLoadOperation_MDL();
                m_operationsQueue.insert(std::make_pair(_filename, operation));
            }

            CLoadOperation_MDL* operation = static_cast<CLoadOperation_MDL*>(m_operationsQueue.find(_filename)->second);
            AddListener(_listener, operation);
        }
    }
    return mesh;
}


