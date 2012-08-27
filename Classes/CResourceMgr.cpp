//
//  CResourceMgr.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CResourceMgr.h"

void* UpdateThread(void *_pParam)
{
    CResourceMgr* pInstance = (CResourceMgr*)_pParam;
    while (true)
    {
        for(auto& pMgr : pInstance->m_lMgr)
        {
            pMgr.second->Thread();
        }
    }
}

CResourceMgr* CResourceMgr::m_pInstance = NULL;

CResourceMgr* CResourceMgr::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CResourceMgr();
    }
    return m_pInstance;
}

CResourceMgr::CResourceMgr()
{
    m_lMgr[IResource::E_MGR_TEXTURE] = new CTextureMgr();
    m_lMgr[IResource::E_MGR_MESH] = new CMeshMgr();
}

CResourceMgr::~CResourceMgr()
{
    
}

void CResourceMgr::Update()
{
    for(auto& pMgr : m_lMgr)
    {
        pMgr.second->Thread();
        pMgr.second->Update();
    }
}

void CResourceMgr::RemoveEventListener(IResource::EventHandle _iEventHandle)
{
    for(auto& pMgr : m_lMgr)
    {
        pMgr.second->RemoveEventListener(_iEventHandle);
    }
}

IResource::EventHandle CResourceMgr::AddEventListener(const std::string &_sName, IResource::E_MGR _eMgr, IResource::E_THREAD _eThread, const IResource::EventSignature &_pListener,const std::map<std::string, std::string>* _lParams)
{
    return m_lMgr[_eMgr]->AddEventListener(_sName, _eThread, _pListener, _lParams);
}

void CResourceMgr::Unload(IResource *_pResource)
{
    //TODO: create Unload
}

