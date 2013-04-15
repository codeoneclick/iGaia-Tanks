
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
    
    TSharedPtrTexture Get_TextureSynchronous(const std::string& _filename);
    void Get_TextureAsynchronous(const std::string& _filename, const CResourceLoadingCommands* _commands);
    
    TSharedPtrMesh Get_MeshSynchronous(const std::string& _filename);
    void Get_MeshAsynchronous(const std::string& _filename, const CResourceLoadingCommands* _commands);

    SShape3dSettings* LoadShape3dSettings(const std::string& _filename);
    SLandscapeSettings* LoadLandscapeSettings(const std::string& _filename);
    SLandscapeDecalSettings* LoadLandscapeDecalSettings(const std::string& _filename);
    SOceanSettings* LoadOceanSettings(const std::string& _filename);
    SGrassSettings* LoadGrassSettings(const std::string& _filename);
    SSkyDomeSettings* LoadSkyDomeSettings(const std::string& _filename);
    SParticleEmitterSettings* LoadParticleEmitterSettings(const std::string& _filename);

    void Cancel_LoadingOperation(const CResourceLoadingCommands* _commands);

    void Unload_Resource(TSharedPtrResource _resource);

    void Update(void);
};

#endif
