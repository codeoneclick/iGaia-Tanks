//
//  CLandscapeSettings.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CLandscapeSettings_PARSER.h"
#include "CCommon_IOS.h"

SLandscapeSettings* CLandscapeSettings_PARSER::Deserialize(const std::string& _name)
{
    std::string path(Get_BundlePath());
    path.append(_name);
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(path.c_str());
    assert(result.status == pugi::status_ok);
    pugi::xml_node settings_node = document.child("settings");
    SLandscapeSettings* settings = new SLandscapeSettings();
    settings->m_materialsSettings = m_gameObjectSettings.Deserialize(settings_node);
    settings->m_heightmapDataFileName = settings_node.child("heightmap_data_filename").attribute("value").as_string();
    settings->m_splattingDataFileName = settings_node.child("splatting_data_filename").attribute("value").as_string();
    settings->m_width = settings_node.child("width").attribute("value").as_uint();
    settings->m_height = settings_node.child("height").attribute("value").as_float();
    settings->m_edgesTextureFileName = settings_node.child("edges_texture_filename").attribute("value").as_string();
    return settings;
}