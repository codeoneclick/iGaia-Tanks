//
//  CParticleEmitterSettings.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CParticleEmitterSettings_PARSER.h"
#include "CCommon.h"

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

    settings->m_numParticles = settings_node.child("num_particles").attribute("value").as_int();
    settings->m_duration = settings_node.child("duration").attribute("value").as_uint();
    settings->m_durationRandomness = settings_node.child("duration_randomness").attribute("value").as_uint();
    settings->m_velocitySensitivity = settings_node.child("velocity_sensitivity").attribute("value").as_float();
    settings->m_minHorizontalVelocity = settings_node.child("min_horizontal_velocity").attribute("value").as_float();
    settings->m_maxHorizontalVelocity = settings_node.child("max_horizontal_velocity").attribute("value").as_float();
    settings->m_minVerticalVelocity = settings_node.child("min_vertical_velocity").attribute("value").as_float();
    settings->m_maxVerticalVelocity = settings_node.child("max_vertical_velocity").attribute("value").as_float();
    settings->m_endVelocity = settings_node.child("end_velocity").attribute("value").as_float();
    settings->m_gravity.x = settings_node.child("gravity").attribute("x").as_float();
    settings->m_gravity.y = settings_node.child("gravity").attribute("y").as_float();
    settings->m_gravity.z = settings_node.child("gravity").attribute("z").as_float();
    settings->m_startColor.x = settings_node.child("start_color").attribute("r").as_float();
    settings->m_startColor.y = settings_node.child("start_color").attribute("g").as_float();
    settings->m_startColor.z = settings_node.child("start_color").attribute("b").as_float();
    settings->m_startColor.w = settings_node.child("start_color").attribute("a").as_float();
    settings->m_endColor.x = settings_node.child("end_color").attribute("r").as_float();
    settings->m_endColor.y = settings_node.child("end_color").attribute("g").as_float();
    settings->m_endColor.z = settings_node.child("end_color").attribute("b").as_float();
    settings->m_endColor.w = settings_node.child("end_color").attribute("a").as_float();
    settings->m_startSize.x = settings_node.child("start_size").attribute("width").as_float();
    settings->m_startSize.y = settings_node.child("start_size").attribute("height").as_float();
    settings->m_endSize.x = settings_node.child("end_size").attribute("width").as_float();
    settings->m_endSize.y = settings_node.child("end_size").attribute("height").as_float();
    settings->m_minParticleEmittInterval = settings_node.child("min_particle_emitt_interval").attribute("value").as_uint();
    settings->m_maxParticleEmittInterval = settings_node.child("max_particle_emitt_interval").attribute("value").as_uint();

    return settings;
}