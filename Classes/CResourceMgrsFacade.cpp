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
    m_settingsContainer = new CSettingsContainer();
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

void CResourceMgrsFacade::Get_TextureAsynchronous(const std::string &_filename, const CResourceLoadingCommands *_commands)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
    assert(mgr != nullptr);
    mgr->Execute_LoadingOperationAsynchronous(_filename, _commands);
}

TSharedPtrTexture CResourceMgrsFacade::Get_TextureSynchronous(const std::string &_filename)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
    assert(mgr != nullptr);
    TSharedPtrTexture texture = std::static_pointer_cast<CTexture>(mgr->Execute_LoadingOperationSynchronous(_filename));
    assert(texture != nullptr);
    return texture;
}

void CResourceMgrsFacade::Get_MeshAsynchronous(const std::string &_filename, const CResourceLoadingCommands *_commands)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
    assert(mgr != nullptr);
    mgr->Execute_LoadingOperationAsynchronous(_filename, _commands);
}

TSharedPtrMesh CResourceMgrsFacade::Get_MeshSynchronous(const std::string &_filename)
{
    IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
    assert(mgr != nullptr);
    TSharedPtrMesh mesh = std::static_pointer_cast<CMesh>(mgr->Execute_LoadingOperationSynchronous(_filename));
    assert(mesh != nullptr);
    return mesh;
}

SShape3dSettings* CResourceMgrsFacade::LoadShape3dSettings(const std::string& _filename)
{
    assert(m_settingsContainer != nullptr);
    SShape3dSettings* settings = m_settingsContainer->LoadShape3dSettings(_filename);
    assert(settings != nullptr);
    return settings;
}

SLandscapeSettings* CResourceMgrsFacade::LoadLandscapeSettings(const std::string& _filename)
{
    assert(m_settingsContainer != nullptr);
    SLandscapeSettings* settings = m_settingsContainer->LoadLandscapeSettings(_filename);
    assert(settings != nullptr);
    return settings;
}

SLandscapeDecalSettings* CResourceMgrsFacade::LoadLandscapeDecalSettings(const std::string &_filename)
{
    assert(m_settingsContainer != nullptr);
    SLandscapeDecalSettings* settings = m_settingsContainer->LoadLandscapeDecalSettings(_filename);
    assert(settings != nullptr);
    return settings;
}

SOceanSettings* CResourceMgrsFacade::LoadOceanSettings(const std::string& _filename)
{
    assert(m_settingsContainer != nullptr);
    SOceanSettings* settings = m_settingsContainer->LoadOceanSettings(_filename);
    assert(settings != nullptr);
    return settings;
}

SGrassSettings* CResourceMgrsFacade::LoadGrassSettings(const std::string& _filename)
{
    assert(m_settingsContainer != nullptr);
    SGrassSettings* settings = m_settingsContainer->LoadGrassSettings(_filename);
    assert(settings != nullptr);
    return settings;
}

SSkyDomeSettings* CResourceMgrsFacade::LoadSkyDomeSettings(const std::string& _filename)
{
    assert(m_settingsContainer != nullptr);
    SSkyDomeSettings* settings = m_settingsContainer->LoadSkyDomeSettings(_filename);
    assert(settings != nullptr);
    return settings;
}

SParticleEmitterSettings* CResourceMgrsFacade::LoadParticleEmitterSettings(const std::string& _filename)
{
    assert(m_settingsContainer != nullptr);
    SParticleEmitterSettings* settings = m_settingsContainer->LoadParticleEmitterSettings(_filename);
    assert(settings != nullptr);
    return settings;
}

void CResourceMgrsFacade::Cancel_LoadingOperation(const CResourceLoadingCommands *_commands)
{
    IResourceMgr_INTERFACE* textureMgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
    assert(textureMgr != nullptr);
    textureMgr->Cancel_LoadingOperation(_commands);
    
    IResourceMgr_INTERFACE* meshMgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
    assert(meshMgr != nullptr);
    meshMgr->Cancel_LoadingOperation(_commands);
}

void CResourceMgrsFacade::Unload_Resource(TSharedPtrResource _resource)
{
    if(_resource->Get_ResourceType() == E_RESOURCE_TYPE_TEXTURE)
    {
        IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_TEXTURE)->second;
        assert(mgr != nullptr);
        mgr->Unload_Resource(_resource);
    }
    else if(_resource->Get_ResourceType() == E_RESOURCE_TYPE_MESH)
    {
        IResourceMgr_INTERFACE* mgr = m_resourceMgrsContainer.find(E_RESOURCE_MGR_MESH)->second;
        assert(mgr != nullptr);
        mgr->Unload_Resource(_resource);
    }
}


