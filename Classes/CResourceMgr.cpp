//
//  CResourceMgr.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CResourceMgr.h"

void* Thread(void *_pParam)
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
    //pthread_create(&m_thread, NULL, Thread, (void*)this);
}

CResourceMgr::~CResourceMgr()
{
    
}

void CResourceMgr::Update()
{
    std::map<IResource::E_MGR,IResourceMgr*>::iterator pBeginMgr = m_lMgr.begin();
    std::map<IResource::E_MGR,IResourceMgr*>::iterator pEndMgr = m_lMgr.end();
    while( pBeginMgr != pEndMgr)
    {
        pBeginMgr->second->Thread();
        pBeginMgr->second->Update();
        ++pBeginMgr;
    }
}

void CResourceMgr::Cancel_Load(IDelegate *_pDeleagte)
{
    std::map<IResource::E_MGR,IResourceMgr*>::iterator pBeginMgr = m_lMgr.begin();
    std::map<IResource::E_MGR,IResourceMgr*>::iterator pEndMgr = m_lMgr.end();
    while( pBeginMgr != pEndMgr)
    {
        pBeginMgr->second->Cancel_Load(_pDeleagte);
        ++pBeginMgr;
    }
}

IResource* CResourceMgr::Load(const std::string& _sName, IResource::E_MGR _eMgr, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams)
{
    return m_lMgr[_eMgr]->Load(_sName, _eThread, _pDelegate, _lParams);
}

void CResourceMgr::Unload(IResource *_pResource)
{
    //TODO: create Unload
}

