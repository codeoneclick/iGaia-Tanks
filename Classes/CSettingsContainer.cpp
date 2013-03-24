//
//  CSettingsContainer.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CSettingsContainer.h"
#include "CShape3dSettings_PARSER.h"
#include "CLandscapeSettings_PARSER.h"
#include "COceanSettings_PARSER.h"
#include "CGrassSettings_PARSER.h"
#include "CSkyDomeSettings_PARSER.h"
#include "CParticleEmitterSettings_PARSER.h"
#include "CLandscapeDecalSettings_PARSER.h"

CSettingsContainer::CSettingsContainer(void)
{

}

CSettingsContainer::~CSettingsContainer(void)
{
    
}

SObject3dSettings* CSettingsContainer::Get_CachedSettings(const std::string& _filename)
{
    if(m_settingsContainer.find(_filename) != m_settingsContainer.end())
    {
        return m_settingsContainer[_filename];
    }
    return nullptr;
}

SShape3dSettings* CSettingsContainer::LoadShape3dSettings(const std::string& _filename)
{
    SShape3dSettings* settings = static_cast<SShape3dSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        CShape3dSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}

SLandscapeSettings* CSettingsContainer::LoadLandscapeSettings(const std::string& _filename)
{
    SLandscapeSettings* settings = static_cast<SLandscapeSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        CLandscapeSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}

SLandscapeDecalSettings* CSettingsContainer::LoadLandscapeDecalSettings(const std::string &_filename)
{
    SLandscapeDecalSettings* settings = static_cast<SLandscapeDecalSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        CLandscapeDecalSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}

SOceanSettings* CSettingsContainer::LoadOceanSettings(const std::string& _filename)
{
    SOceanSettings* settings = static_cast<SOceanSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        COceanSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}

SGrassSettings* CSettingsContainer::LoadGrassSettings(const std::string& _filename)
{
    SGrassSettings* settings = static_cast<SGrassSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        CGrassSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}

SSkyDomeSettings* CSettingsContainer::LoadSkyDomeSettings(const std::string& _filename)
{
    SSkyDomeSettings* settings = static_cast<SSkyDomeSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        CSkyDomeSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}

SParticleEmitterSettings* CSettingsContainer::LoadParticleEmitterSettings(const std::string& _filename)
{
    SParticleEmitterSettings* settings = static_cast<SParticleEmitterSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        CParticleEmitterSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}
