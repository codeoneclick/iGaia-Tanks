//
//  CGameSettingsMgr.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#include "CGameSettingsMgr.h"
#include "CPanzerSettings_PARSER.h"

CGameSettingsMgr::CGameSettingsMgr(void)
{

}

CGameSettingsMgr::~CGameSettingsMgr(void)
{
    
}

IGameSettings* CGameSettingsMgr::Get_CachedSettings(const std::string& _filename)
{
    if(m_settingsContainer.find(_filename) != m_settingsContainer.end())
    {
        return m_settingsContainer[_filename];
    }
    return nullptr;
}


SPanzerSettings* CGameSettingsMgr::Get_PanzerSettings(const std::string &_filename)
{
    SPanzerSettings* settings = static_cast<SPanzerSettings*>(Get_CachedSettings(_filename));
    if(settings == nullptr)
    {
        CPanzerSettings_PARSER parser;
        settings = parser.Deserialize(_filename);
        m_settingsContainer.insert(std::make_pair(_filename, settings));
    }
    return settings;
}
