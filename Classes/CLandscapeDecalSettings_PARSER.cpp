//
//  CLandscapeDecalSettings_PARSER.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#include "CLandscapeDecalSettings_PARSER.h"
#include "CCommon_iOS.h"

SLandscapeDecalSettings* CLandscapeDecalSettings_PARSER::Deserialize(const std::string& _name)
{
    std::string path(Get_BundlePath());
    path.append(_name);
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(path.c_str());
    assert(result.status == pugi::status_ok);
    pugi::xml_node settings_node = document.child("settings");
    SLandscapeDecalSettings* settings = new SLandscapeDecalSettings();
    settings->m_materialsSettings = m_gameObjectSettings.Deserialize(settings_node);
    settings->m_width = settings_node.child("width").attribute("value").as_uint();
    settings->m_height = settings_node.child("height").attribute("value").as_uint();
    settings->m_widthOffset = settings_node.child("width_offset").attribute("value").as_uint();
    settings->m_heightOffset = settings_node.child("height_offset").attribute("value").as_uint();
    return settings;
}