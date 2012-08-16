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

}

IResourceMgr::~IResourceMgr(void)
{
    
}

void IResourceMgr::Thread(void)
{
    std::map<std::string, IParser*>::iterator pBeginIteratorTask = m_lTaskPool.begin();
    std::map<std::string, IParser*>::iterator pEndIteratorTask = m_lTaskPool.end();
    while(pBeginIteratorTask != pEndIteratorTask)
    {
        IParser* pParser = pBeginIteratorTask->second;
        if(pParser->Get_Status() == IParser::E_NONE_STATUS)
        {
            pParser->Load(pBeginIteratorTask->first.c_str());
        }
        ++pBeginIteratorTask;
    }
}

void IResourceMgr::Cancel_Load(IDelegate *_pDelegate)
{
    std::map<std::string, IResource*>::iterator pBeginIteratorResource = m_lContainer.begin();
    std::map<std::string, IResource*>::iterator pEndIteratorResource = m_lContainer.end();
    while(pBeginIteratorResource != pEndIteratorResource)
    {
        IResource* pResource = pBeginIteratorResource->second;
        pResource->Remove_DelegateOnwer(_pDelegate);
        ++pBeginIteratorResource;
    }
}

void IResourceMgr::Update(void)
{
    std::map<std::string, IParser*>::iterator pBeginIteratorTask = m_lTaskPool.begin();
    std::map<std::string, IParser*>::iterator pEndIteratorTask = m_lTaskPool.end();
    while(pBeginIteratorTask != pEndIteratorTask)
    {
        IParser* pParser = (IParser*)pBeginIteratorTask->second;
        if(pParser->Get_Status() == IParser::E_DONE_STATUS)
        {
            pParser->Commit();
            std::string sRequestName = pBeginIteratorTask->first;
            if(m_lContainer.find(pBeginIteratorTask->first) != m_lContainer.end())
            {
                IResource* pResource = m_lContainer[pBeginIteratorTask->first];
                pResource->Set_SourceData(pParser->Get_SourceData());
                m_lTaskPool.erase(pBeginIteratorTask);
                SAFE_DELETE(pParser);
                pResource->Push_SignalToDelegateOwners();
                return;
            }
        }
        else
        {
            if(pParser->Get_Status() == IParser::E_ERROR_STATUS)
            {
                m_lTaskPool.erase(pBeginIteratorTask);
                SAFE_DELETE(pParser);
                return;
            }
        }
        ++pBeginIteratorTask;
    }
}

