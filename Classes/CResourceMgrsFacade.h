//
//  CResourceMgr.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CResourceMgr_h
#define CResourceMgr_h

#include "HCommon.h"
#include "CTextureMgr.h"
#include "CMeshMgr.h"
#include "CTexture.h"
#include "CMesh.h"
#include "CSettingsContainer.h"

class CResourceMgrsFacade
{

private:

protected:

    std::map<E_RESOURCE_MGR, IResourceMgr_INTERFACE*> m_resourceMgrsContainer;
    CSettingsContainer* m_settingsContainer;
    
public:
    
    CResourceMgrsFacade(void);
    ~CResourceMgrsFacade(void);

    void LoadTexture(const std::string& _filename, CResourceLoadCallback_INTERFACE* _listener);
    CTexture* LoadTexture(const std::string& _filename);

    void LoadMesh(const std::string& _filename, CResourceLoadCallback_INTERFACE* _listener);
    CMesh* LoadMesh(const std::string& _filename);

    SShape3dSettings* LoadShape3dSettings(const std::string& _filename);
    SLandscapeSettings* LoadLandscapeSettings(const std::string& _filename);
    SOceanSettings* LoadOceanSettings(const std::string& _filename);
    SGrassSettings* LoadGrassSettings(const std::string& _filename);
    SSkyDomeSettings* LoadSkyDomeSettings(const std::string& _filename);
    SParticleEmitterSettings* LoadParticleEmitterSettings(const std::string& _filename);

    void CancelLoadResource(CResourceLoadCallback_INTERFACE* _listener);

    void UnloadResource(IResource_INTERFACE* _resource);

    void Update(void);
};

#endif
