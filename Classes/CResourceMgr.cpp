//
//  CResourceMgr.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "CResourceMgr.h"

CResourceMgr* CResourceMgr::m_instance = nullptr;

CResourceMgr* CResourceMgr::Instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new CResourceMgr();
    }
    return m_instance;
}

CResourceMgr::CResourceMgr()
{
    m_textureMgr = new CTextureMgr();
    m_meshMgr = new CMeshMgr();
}

CResourceMgr::~CResourceMgr()
{
    
}

IResource* CResourceMgr::LoadSync(IResource::E_MGR _mgr, const std::string &_name)
{
    IResource* resource = nullptr;
    switch (_mgr)
    {
        case IResource::E_MGR_TEXTURE:
        {
            resource = m_textureMgr->LoadSync(_name);
        }
            break;
        case IResource::E_MGR_MESH:
        {
            resource = m_meshMgr->LoadSync(_name);
        }
            break;

        default:
            break;
    }
    return resource;
}

IResource* CResourceMgr::LoadAsync(IResource::E_MGR _mgr, const std::string &_name)
{
    IResource* resource = nullptr;
    switch (_mgr)
    {
        case IResource::E_MGR_TEXTURE:
        {
            resource = m_textureMgr->LoadAsync(_name);
        }
            break;
        case IResource::E_MGR_MESH:
        {
            resource = m_meshMgr->LoadAsync(_name);
        }
            break;

        default:
            break;
    }
    return resource;
}

void CResourceMgr::Unload(IResource::E_MGR _mgr, IResource* _resource)
{
    switch (_mgr)
    {
        case IResource::E_MGR_TEXTURE:
        {
            m_textureMgr->Unload(_resource->Get_Name());
        }
            break;
        case IResource::E_MGR_MESH:
        {
            m_meshMgr->Unload(_resource->Get_Name());
        }
            break;

        default:
            break;
    }

}

