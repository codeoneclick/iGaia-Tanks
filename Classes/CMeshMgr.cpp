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

TSharedPtrResource CMeshMgr::Execute_LoadingOperationSynchronous(const std::string& _filename)
{
    TSharedPtrMesh mesh = nullptr;
    if(m_resources.find(_filename) != m_resources.end())
    {
        mesh = std::static_pointer_cast<CMesh>(m_resources[_filename]);
    }
    else
    {
        TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_MDL());
        operation->Load(_filename);
        if(operation->Get_Status() == E_PARSER_STATUS_DONE)
        {
            mesh = TSharedPtrMesh(static_cast<CMesh*>(operation->Link()));
            m_resources.insert(std::make_pair(_filename, mesh));
        }
    }
    return mesh;
}

void CMeshMgr::Execute_LoadingOperationAsynchronous(const std::string& _filename, const CResourceLoadingCommands* _commands)
{
    TSharedPtrMesh mesh = nullptr;
    if(m_resources.find(_filename) != m_resources.end())
    {
        mesh = std::static_pointer_cast<CMesh>(m_resources[_filename]);
        Execute_CallbackCommands(_commands, mesh);
    }
    else
    {
        if(m_operationsQueue.find(_filename) == m_operationsQueue.end())
        {
            TSharedPtrLoadOperation operation = TSharedPtrLoadOperation(new CLoadOperation_MDL());
            m_operationsQueue.insert(std::make_pair(_filename, operation));
        }
        TSharedPtrLoadOperation operation = m_operationsQueue.find(_filename)->second;
        operation->Register_ResourceLoadingCommands(_commands);
    }
}
