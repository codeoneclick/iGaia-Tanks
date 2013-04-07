//
//  CBuildingSettings_PARSER.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 4/6/13.
//
//

#include "CBuildingSettings_PARSER.h"
#include "CCommon.h"

SBuildingSettings* CBuildingSettings_PARSER::Deserialize(const std::string& _filename)
{
    std::string path(Get_BundlePath());
    path.append(_filename);
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(path.c_str());
    assert(result.status == pugi::status_ok);
    pugi::xml_node settings_node = document.child("settings");
    SBuildingSettings* settings = new SBuildingSettings();
    settings->m_shapeSettingsFilename = settings_node.child("shape").attribute("value").as_string();
    return settings;
}