//
//  CResourceMgr.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "CResourceMgrsFacade.h"

CResourceMgrsFacade::CResourceMgrsFacade(void)
{
    m_resourceMgrsContainer.insert(std::make_pair(E_RESOURCE_MGR_TEXTURE, new CTextureMgr()));
    m_resourceMgrsContainer.insert(std::make_pair(E_RESOURCE_MGR_MESH, new CMeshMgr()));
}

CResourceMgrsFacade::~CResourceMgrsFacade(void)
{
    
}

void CResourceMgrsFacade::Update(void)
{
    for(std::map<E_RESOURCE_MGR, IResourceMgr_INTERFACE*>::iterator iterator = m_resourceMgrsContainer.begin(); iterator != m_resourceMgrsContainer.end(); ++iterator)
    {
        iterator->second->Update();
    }
}

void CResourceMgrsFacade::LoadTexture(const std::string& _filename, CResourceLoadCallback_INTERFACE* _listener)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
    assert(mgr != nullptr);
    mgr->StartLoadOperation(_filename, E_RESOURCE_LOAD_THREAD_ASYNC, _listener);
}

CTexture* CResourceMgrsFacade::LoadTexture(const std::string& _filename)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
    assert(mgr != nullptr);
    CTexture* texture = static_cast<CTexture*>(mgr->StartLoadOperation(_filename, E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    assert(texture != nullptr);
    return texture;
}

void CResourceMgrsFacade::LoadMesh(const std::string& _filename, CResourceLoadCallback_INTERFACE* _listener)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
    assert(mgr != nullptr);
    mgr->StartLoadOperation(_filename, E_RESOURCE_LOAD_THREAD_ASYNC, _listener);
}

CMesh* CResourceMgrsFacade::LoadMesh(const std::string& _filename)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
    assert(mgr != nullptr);
    CMesh* mesh = static_cast<CMesh*>(mgr->StartLoadOperation(_filename, E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    assert(mesh != nullptr);
    return mesh;
}

void CResourceMgrsFacade::CancelLoadResource(CResourceLoadCallback_INTERFACE* _listener)
{
    IResourceMgr_INTERFACE* textureMgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
    assert(textureMgr != nullptr);
    textureMgr->CancelLoadOperation(_listener);
    
    IResourceMgr_INTERFACE* meshMgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
    assert(meshMgr != nullptr);
    meshMgr->CancelLoadOperation(_listener);
}

void CResourceMgrsFacade::UnloadResource(IResource_INTERFACE* _resource)
{
    if(_resource->Get_ResourceType() == E_RESOURCE_TYPE_TEXTURE)
    {
        IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
        assert(mgr != nullptr);
        mgr->UnloadResource(_resource);
    }
    else if(_resource->Get_ResourceType() == E_RESOURCE_TYPE_MESH)
    {
        IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
        assert(mgr != nullptr);
        mgr->UnloadResource(_resource);
    }
}


