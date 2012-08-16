//
//  IResource.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResource.h"
#include "CResourceMgr.h"
#include "IResourceLoaderDelegate.h"

IResource::IResource(void)
{
    m_iRefCount = 0;
    m_eResourceType = E_RESOURCE_TYPE_NONE;
    m_eCreationMode = E_CREATION_MODE_NATIVE;
}

IResource::~IResource(void)
{
    std::cout<<"[IResource::~IResource]"<<std::endl;
    m_lDelegateOwners.clear();
}

void IResource::Release()
{
    CResourceMgr::Instance()->Unload(this);
}

void IResource::Add_DelegateOwner(IDelegate *_pDelegateOwner)
{
    for(size_t index = 0; index< m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index] == _pDelegateOwner)
        {
            return;
        }
    }
    m_lDelegateOwners.push_back(_pDelegateOwner);
}

void IResource::Remove_DelegateOnwer(IDelegate *_pDelegateOwner)
{
    for(size_t index = 0; index < m_lDelegateOwners.size(); ++index)
    {
        if(m_lDelegateOwners[index] == _pDelegateOwner)
        {
            m_lDelegateOwners.erase(m_lDelegateOwners.begin() + index);
        }
    }
}

void IResource::Push_SignalToDelegateOwners(void)
{
    for(size_t index = 0; index < m_lDelegateOwners.size(); ++index)
    {
        IDelegate* pDelegateOwner = m_lDelegateOwners[index];
        if(pDelegateOwner->Get_DelegateType() == IDelegate::E_DELEGATE_TYPE_RESOURCE_LOAD)
        {
            dynamic_cast<IResourceLoaderDelegate*>(pDelegateOwner)->OnResourceLoadDoneEvent(m_eResourceType, this);
        }
    }
    m_lDelegateOwners.clear();
}





