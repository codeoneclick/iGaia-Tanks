//
//  IResourceMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResourceMgr.h"

IResourceMgr::IResourceMgr(void)
{
    pthread_mutex_init(&m_mutex, NULL);
}

IResourceMgr::~IResourceMgr(void)
{
    
}


void IResourceMgr::Thread(void)
{
    std::map<std::string, IParser*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, IParser*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        IParser* pParser = pBTask->second;
        if(pParser->Get_Status() == IParser::E_NONE_STATUS)
        {
            pParser->Load(pBTask->first.c_str());
        }
        ++pBTask;
    }
}

void IResourceMgr::Cancel_Load(IDelegate *_pDelegate)
{
    std::map<std::string, IResource*>::iterator pBeginResource = m_lContainer.begin();
    std::map<std::string, IResource*>::iterator pEndResource = m_lContainer.end();
    while( pBeginResource != pEndResource)
    {
        IResource* pResource = pBeginResource->second;
        pResource->Remove_DelegateOnwer(_pDelegate);
        ++pBeginResource;
    }
}

void IResourceMgr::Update(void)
{
    std::map<std::string, IParser*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, IParser*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        IParser* pParser = (IParser*)pBTask->second;
        if(pParser->Get_Status() == IParser::E_DONE_STATUS)
        {
            pParser->Commit();
            std::string sRequestName = pBTask->first;
            if(m_lContainer.find(pBTask->first) != m_lContainer.end())
            {
                IResource* pResource = m_lContainer[pBTask->first];
                pResource->Set_SourceData(pParser->Get_SourceData());
                m_lTaskPool.erase(pBTask);
                delete pParser;
                pResource->Push_SignalToDelegateOwners();
                return;
            }
        }
        else
        {
            if(pParser->Get_Status() == IParser::E_ERROR_STATUS)
            {
                m_lTaskPool.erase(pBTask);
                delete pParser;
                return;
            }
        }
        ++pBTask;
    }
}

