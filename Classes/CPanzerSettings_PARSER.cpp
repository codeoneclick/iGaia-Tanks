//
//  CTankSettings_PARSER.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#include "CPanzerSettings_PARSER.h"
#include "CCommon.h"

SPanzerSettings* CPanzerSettings_PARSER::Deserialize(const std::string& _filename)
{
    std::string path(Get_BundlePath());
    path.append(_filename);
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(path.c_str());
    assert(result.status == pugi::status_ok);
    pugi::xml_node settings_node = document.child("settings");
    SPanzerSettings* settings = new SPanzerSettings();
    settings->m_carcassSettings.m_carcassSettingsFilename = settings_node.child("carcass").attribute("value").as_string();
    settings->m_chassisSettings.m_leftChassisSettingsFilename = settings_node.child("left_chassis").attribute("value").as_string();
    settings->m_chassisSettings.m_rightChassisSettingsFilename = settings_node.child("right_chassis").attribute("value").as_string();
    settings->m_turretSettings.m_turretSettingsFilename = settings_node.child("turret").attribute("value").as_string();
    return settings;
}