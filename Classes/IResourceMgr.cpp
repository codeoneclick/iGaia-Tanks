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
    for(auto& pTask : m_lTaskPool)
    {
        if(pTask.second->Get_Status() == IParser::E_NONE_STATUS)
        {
            pTask.second->Load(pTask.first.c_str());
        }
    }
}

void IResourceMgr::Cancel_Load(IDelegate *_pDelegate)
{
    for(auto& pResource : m_lContainer)
    {
        pResource.second->Remove_DelegateOnwer(_pDelegate);
    }
}

void IResourceMgr::Update(void)
{
    for(auto& pTask : m_lTaskPool)
    {
        if(pTask.second->Get_Status() == IParser::E_DONE_STATUS)
        {
            pTask.second->Commit();
            if(m_lContainer.find(pTask.first) != m_lContainer.end())
            {
                IResource* pResource = m_lContainer[pTask.first];
                pResource->Set_SourceData(pTask.second->Get_SourceData());
                SAFE_DELETE(pTask.second);
                m_lTaskPool.erase(pTask.first);
                pResource->Push_SignalToDelegateOwners();
                return;
            }
        }
        else
        {
            if(pTask.second->Get_Status() == IParser::E_ERROR_STATUS)
            {
                SAFE_DELETE(pTask.second);
                m_lTaskPool.erase(pTask.first);
                return;
            }
        }
    }
}

