//
//  CSettingsContainer.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CSettingsContainer_h
#define CSettingsContainer_h

#include "HCommon.h"
#include "HSettings_DTO.h"

class CSettingsContainer
{
private:

protected:

    std::map<std::string, SObject3dSettings*> m_settingsContainer;

    SObject3dSettings* Get_CachedSettings(const std::string& _name);

public:

    CSettingsContainer(void);
    ~CSettingsContainer(void);

    SShape3dSettings* LoadShape3dSettings(const std::string& _filename);
    SLandscapeSettings* LoadLandscapeSettings(const std::string& _filename);
    SOceanSettings* LoadOceanSettings(const std::string& _filename);
    SGrassSettings* LoadGrassSettings(const std::string& _filename);
    SSkyDomeSettings* LoadSkyDomeSettings(const std::string& _filename);
    SParticleEmitterSettings* LoadParticleEmitterSettings(const std::string& _filename);

};

#endif
