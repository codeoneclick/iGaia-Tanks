//
//  CGameObjectSettings.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CGameObjectSettings_PARSER.h"

std::vector<const SMaterialSettings*> CGameObjectSettings_PARSER::Deserialize(pugi::xml_node const& _settingsNode)
{
    std::vector<const SMaterialSettings*> materialsSettings;

    pugi::xml_node materials_node = _settingsNode.child("materials");

    for (pugi::xml_node material = materials_node.child("material"); material; material = materials_node.next_sibling("material"))
    {
        SMaterialSettings* materialSettings = new SMaterialSettings();
        materialSettings->m_renderMode = material.attribute("render_mode").as_uint();
        materialSettings->m_isCullFace = material.attribute("is_cull_face").as_bool();
        materialSettings->m_isDepthTest = material.attribute("is_depth_test").as_bool();
        materialSettings->m_isDepthMask = material.attribute("is_depth_mask").as_bool();
        materialSettings->m_isBlend = material.attribute("is_blend").as_bool();
        materialSettings->m_cullFaceMode = material.attribute("cull_face_mode").as_uint();
        materialSettings->m_blendFunctionSource = material.attribute("blend_function_source").as_uint();
        materialSettings->m_blendFunctionDestination = material.attribute("blend_function_destination").as_uint();

        SShaderSettings* shaderSettings = new SShaderSettings();
        shaderSettings->m_vsName = material.child("shader").attribute("vs_name").as_string();
        shaderSettings->m_fsName = material.child("shader").attribute("fs_name").as_string();
        shaderSettings->m_guid = material.child("shader").attribute("guid").as_uint();
        materialSettings->m_shaderSettings = shaderSettings;

        pugi::xml_node textures_node = material.child("textures");
        for (pugi::xml_node texture = textures_node.child("texture"); texture; texture = textures_node.next_sibling("texture"))
        {
            STextureSettings* textureSettings = new STextureSettings();
            textureSettings->m_name = texture.attribute("name").as_string();
            textureSettings->m_slot = texture.attribute("slot").as_uint();
            textureSettings->m_wrap = texture.attribute("wrap").as_uint();
            materialSettings->m_texturesSettings.push_back(textureSettings);
        }
        materialsSettings.push_back(materialSettings);
    }
    return materialsSettings;
}