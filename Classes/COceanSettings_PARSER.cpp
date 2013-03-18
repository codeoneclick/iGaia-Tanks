//
//  COceanSettings.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "COceanSettings_PARSER.h"
#include "CCommon_IOS.h"

SOceanSettings* COceanSettings_PARSER::Deserialize(const std::string& _name)
{
    std::string path(Get_BundlePath());
    path.append(_name);
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(path.c_str());
    assert(result.status == pugi::status_ok);
    pugi::xml_node settings_node = document.child("settings");
    SOceanSettings* settings = new SOceanSettings();
    settings->m_materialsSettings = m_gameObjectSettings.Deserialize(settings_node);
    settings->m_width = settings_node.child("width").attribute("value").as_uint();
    settings->m_height = settings_node.child("height").attribute("value").as_float();
    settings->m_altitude = settings_node.child("altitude").attribute("value").as_float();
    settings->m_waveGeneratorInterval = settings_node.child("waveGeneratorInterval").attribute("value").as_float();
    return settings;
}