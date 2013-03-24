//
//  CShape3dSettings.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CShape3dSettings_PARSER.h"
#include "CCommon.h"

SShape3dSettings* CShape3dSettings_PARSER::Deserialize(const std::string& _name)
{
    std::string path(Get_BundlePath());
    path.append(_name);
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(path.c_str());
    assert(result.status == pugi::status_ok);
    pugi::xml_node settings_node = document.child("settings");
    SShape3dSettings* settings = new SShape3dSettings();
    settings->m_materialsSettings = m_gameObjectSettings.Deserialize(settings_node);
    settings->m_meshName = settings_node.child("mesh").attribute("value").as_string();
    return settings;
}