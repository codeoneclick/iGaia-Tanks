//
//  CParticleEmitterSettings.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CParticleEmitterSettings_PARSER.h"
#include "CCommon_IOS.h"

SParticleEmitterSettings* CParticleEmitterSettings_PARSER::Deserialize(const std::string& _name)
{
    std::string path(Get_BundlePath());
    path.append(_name);
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(path.c_str());
    assert(result.status == pugi::status_ok);
    pugi::xml_node settings_node = document.child("settings");
    SParticleEmitterSettings* settings = new SParticleEmitterSettings();
    settings->m_materialsSettings = m_gameObjectSettings.Deserialize(settings_node);
    return settings;
}