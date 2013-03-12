//
//  CGameObjectSettings.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#include "CGameObjectSettings_PARSER.h"

const std::string GL_FRONT_STR = "GL_FRONT";
const std::string GL_BACK_STR = "GL_BACK";

const std::string GL_SRC_ALPHA_STR = "GL_SRC_ALPHA";
const std::string GL_ONE_MINUS_SRC_ALPHA_STR = "GL_ONE_MINUS_SRC_ALPHA";

const std::string GL_REPEAT_STR = "GL_REPEAT";
const std::string GL_CLAMP_TO_EDGE_STR = "GL_CLAMP_TO_EDGE";
const std::string GL_MIRRORED_REPEAT_STR = "GL_MIRRORED_REPEAT";

std::map<std::string, GLenum> CGameObjectSettings_PARSER::m_glEnumContainer;

CGameObjectSettings_PARSER::CGameObjectSettings_PARSER(void)
{
    if(m_glEnumContainer.size() == 0)
    {
        m_glEnumContainer.insert(std::make_pair(GL_FRONT_STR, GL_FRONT));
        m_glEnumContainer.insert(std::make_pair(GL_BACK_STR, GL_BACK));

        m_glEnumContainer.insert(std::make_pair(GL_SRC_ALPHA_STR, GL_SRC_ALPHA));
        m_glEnumContainer.insert(std::make_pair(GL_ONE_MINUS_SRC_ALPHA_STR, GL_ONE_MINUS_SRC_ALPHA));

        m_glEnumContainer.insert(std::make_pair(GL_REPEAT_STR, GL_REPEAT));
        m_glEnumContainer.insert(std::make_pair(GL_CLAMP_TO_EDGE_STR, GL_CLAMP_TO_EDGE));
        m_glEnumContainer.insert(std::make_pair(GL_MIRRORED_REPEAT_STR, GL_MIRRORED_REPEAT));
    }
}

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
        
        std::string cullFaceModeStr = material.attribute("cull_face_mode").as_string();
        assert(m_glEnumContainer.find(cullFaceModeStr) != m_glEnumContainer.end());
        materialSettings->m_cullFaceMode = m_glEnumContainer.find(cullFaceModeStr)->second;

        std::string blendFunctionSourceStr = material.attribute("blend_function_source").as_string();
        assert(m_glEnumContainer.find(blendFunctionSourceStr) != m_glEnumContainer.end());
        materialSettings->m_blendFunctionSource = m_glEnumContainer.find(blendFunctionSourceStr)->second;

        std::string blendFunctionDestinationStr = material.attribute("blend_function_destination").as_string();
        assert(m_glEnumContainer.find(blendFunctionDestinationStr) != m_glEnumContainer.end());
        materialSettings->m_blendFunctionDestination = m_glEnumContainer.find(blendFunctionDestinationStr)->second;

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

            std::string wrapStr = texture.attribute("wrap").as_string();
            assert(m_glEnumContainer.find(wrapStr) != m_glEnumContainer.end());
            textureSettings->m_wrap = m_glEnumContainer.find(wrapStr)->second;
            materialSettings->m_texturesSettings.push_back(textureSettings);
        }
        materialsSettings.push_back(materialSettings);
    }
    return materialsSettings;
}