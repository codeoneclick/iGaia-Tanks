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
        std::map<IResource::E_MGR,IResourceMgr*>::iterator pBMgr = pInstance->m_lMgr.begin();
        std::map<IResource::E_MGR,IResourceMgr*>::iterator pEMgr = pInstance->m_lMgr.end();
        while( pBMgr != pEMgr)
        {
            pBMgr->second->Thread();
            ++pBMgr;
        }
    }
}

void* Thread(void* _pParameter)
{
    CResourceMgr* pInstance = static_cast<CResourceMgr*>(_pParameter);
    while(!pInstance->bIsThreadCanceled)
    {
        for(std::map<E_RESOURCE_MGR, IResourceMgr*>::iterator iterator = pInstance->m_tResourceMgrsContainer.begin(); iterator != pInstance->m_tResourceMgrsContainer.end(); ++iterator)
        {
            iterator->second->Thread();
        }
    }
    return nullptr;
}

CResourceMgr* CResourceMgr::m_pInstance = nullptr;

CResourceMgr* CResourceMgr::Instance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new CResourceMgr();
    }
    return m_pInstance;
}

CResourceMgr::CResourceMgr()
{
    m_tResourceMgrsContainer.insert(std::make_pair(E_RESOURCE_MGR_TEXTURE, new CTextureMgr()));
    m_tResourceMgrsContainer.insert(std::make_pair(E_RESOURCE_MGR_MESH, new CMeshMgr()));

    m_lMgr[IResource::E_MGR_TEXTURE] = new CTextureMgr();
    m_lMgr[IResource::E_MGR_MESH] = new CMeshMgr();
}

CResourceMgr::~CResourceMgr()
{
    
}

void CResourceMgr::Update()
{
    for(std::map<E_RESOURCE_MGR, IResourceMgr*>::iterator iterator = m_tResourceMgrsContainer.begin(); iterator != m_tResourceMgrsContainer.end(); ++iterator)
    {
        iterator->second->Thread();
        iterator->second->Update();
    }


    std::map<IResource::E_MGR,IResourceMgr*>::iterator pBeginIteratorMgr = m_lMgr.begin();
    std::map<IResource::E_MGR,IResourceMgr*>::iterator pEndIteratorMgr = m_lMgr.end();
    while(pBeginIteratorMgr != pEndIteratorMgr)
    {
        pBeginIteratorMgr->second->Thread();
        pBeginIteratorMgr->second->Update();
        ++pBeginIteratorMgr;
    }
}

void CResourceMgr::Cancel_Load(IDelegate *_pDeleagte)
{
    std::map<IResource::E_MGR,IResourceMgr*>::iterator pBeginIteratorMgr = m_lMgr.begin();
    std::map<IResource::E_MGR,IResourceMgr*>::iterator pEndIteratorMgr = m_lMgr.end();
    while(pBeginIteratorMgr != pEndIteratorMgr)
    {
        pBeginIteratorMgr->second->Cancel_Load(_pDeleagte);
        ++pBeginIteratorMgr;
    }
}

IResource* CResourceMgr::Load(const std::string& _sName, IResource::E_MGR _eMgr, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams)
{
    return m_lMgr[_eMgr]->Load(_sName, _eThread, _pDelegate, _lParams);
}

IResource* CResourceMgr::StartLoadOperation(const std::string &_sName, E_RESOURCE_MGR _eMgr, E_RESOURCE_LOAD_THREAD _eThread, CResourceLoadCallback_INTERFACE *_pListener)
{
    assert(m_tResourceMgrsContainer.at(_eMgr) != nullptr);
    IResource* resource = nullptr;
    // TODO : m_tResourceMgrsContainer.at(_eMgr)->
    return resource;
}

void CResourceMgr::CancelLoadOperation(CResourceLoadCallback_INTERFACE *_pListener)
{
    for(std::map<E_RESOURCE_MGR, IResourceMgr*>::iterator iterator = m_tResourceMgrsContainer.begin(); iterator != m_tResourceMgrsContainer.end(); ++iterator)
    {
        // TODO : implement cancel load
    }
}


void CResourceMgr::Unload(IResource *_pResource)
{
    //TODO: create Unload
}

