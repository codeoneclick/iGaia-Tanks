//
//  CWater.cpp
//  iGaia
//
//  Created by sergey.sergeev on 3/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "COcean.h"


COcean::COcean(void)
{
    m_reflectionTexture = nullptr;
    m_refractionTexture = nullptr;
    m_heightmapTexture = nullptr;
}

COcean::~COcean(void)
{
    
}

void COcean::Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename)
{
    assert(_resourceMgrsFacade != nullptr);
    SOceanSettings* settings = _resourceMgrsFacade->LoadOceanSettings(_filename);
    assert(settings != nullptr);

    m_width = settings->m_width;
    m_height = settings->m_height;
    m_altitude = settings->m_altitude;

    m_waveGeneratorTimer = 0.0f;
    m_waveGeneratorInterval = settings->m_waveGeneratorInterval;

    std::unique_ptr<CVertexBuffer> vertexBuffer = std::unique_ptr<CVertexBuffer>(new CVertexBuffer(4, GL_STATIC_DRAW));
    SVertex* vertexData = vertexBuffer->Lock();

    vertexData[0].m_position = glm::vec3(0.0f,  settings->m_altitude,  0.0f);
    vertexData[1].m_position = glm::vec3(m_width, settings->m_altitude,  0.0f);
    vertexData[2].m_position = glm::vec3(m_width, settings->m_altitude,  m_height);
    vertexData[3].m_position = glm::vec3(0.0f,  settings->m_altitude,  m_height);

    vertexData[0].m_texcoord = glm::vec2(0.0f,  0.0f);
    vertexData[1].m_texcoord = glm::vec2(1.0f,  0.0f);
    vertexData[2].m_texcoord = glm::vec2(1.0f,  1.0f);
    vertexData[3].m_texcoord = glm::vec2(0.0f,  1.0f);

    vertexBuffer->Unlock();

    std::unique_ptr<CIndexBuffer> indexBuffer = std::unique_ptr<CIndexBuffer>(new CIndexBuffer(6, GL_STATIC_DRAW));
    ui16* indexData = indexBuffer->Lock();

    indexData[0] = 0;
    indexData[1] = 1;
    indexData[2] = 2;
    indexData[3] = 0;
    indexData[4] = 2;
    indexData[5] = 3;

    indexBuffer->Unlock();

    m_mesh = new CMesh();
    m_mesh->Link(std::move(vertexBuffer), std::move(indexBuffer));

    std::vector<const SMaterialSettings*> m_materialsSettings = settings->m_materialsSettings;
    for(const SMaterialSettings* materialSettings : m_materialsSettings)
    {
        assert(materialSettings->m_renderMode < E_RENDER_MODE_WORLD_SPACE_MAX && materialSettings->m_renderMode >= 0);
        assert(m_materials[materialSettings->m_renderMode] == nullptr);

        const SShaderSettings* shaderSettings = materialSettings->m_shaderSettings;

        assert(shaderSettings->m_guid >= 0 && shaderSettings->m_guid < E_SHADER_MAX);

        CShader* shader = _shaderComposite->Get_Shader(static_cast<E_SHADER>(shaderSettings->m_guid));
        m_materials[materialSettings->m_renderMode] = new CMaterial(shader);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_CULL_MODE, materialSettings->m_isCullFace);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_DEPTH_TEST, materialSettings->m_isDepthTest);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_DEPTH_MASK, materialSettings->m_isDepthMask);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_BLEND_MODE, materialSettings->m_isBlend);

        m_materials[materialSettings->m_renderMode]->Set_CullFaceMode(materialSettings->m_cullFaceMode);
        m_materials[materialSettings->m_renderMode]->Set_BlendFunctionSource(materialSettings->m_blendFunctionSource);
        m_materials[materialSettings->m_renderMode]->Set_BlendFunctionDest(materialSettings->m_blendFunctionDestination);

        for(const STextureSettings* textureSettings : materialSettings->m_texturesSettings)
        {
            CTexture* texture = _resourceMgrsFacade->LoadTexture(textureSettings->m_name).get();
            texture->Set_Wrap(textureSettings->m_wrap);
            assert(texture != nullptr);
            assert(textureSettings->m_slot >= 0 && textureSettings->m_slot < E_TEXTURE_SLOT_MAX);
            m_materials[materialSettings->m_renderMode]->Set_Texture(texture, static_cast<E_TEXTURE_SLOT>(textureSettings->m_slot));
        }
    }
}


void COcean::OnResourceDidLoad(TSharedPtrResource _resource)
{
    CGameObject3d::OnResourceDidLoad(_resource);
}

void COcean::OnUpdate(f32 _deltatime)
{
    m_waveGeneratorTimer += m_waveGeneratorInterval;
    CGameObject3d::OnUpdate(_deltatime);
}

ui32 COcean::OnDrawIndex(void)
{
    return 128;
}

void COcean::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnBind(_mode);
}

void COcean::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_materials[_mode] != nullptr);
    assert(m_camera != nullptr);
    assert(m_light != nullptr);

    switch (_mode)
    {
        case E_RENDER_MODE_WORLD_SPACE_COMMON:
        {
            assert(m_materials[_mode]->Get_Shader() != nullptr);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_matrixWorld, E_SHADER_ATTRIBUTE_MATRIX_WORLD);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ProjectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_PROJECTION);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ViewMatrix(), E_SHADER_ATTRIBUTE_MATRIX_VIEW);

            m_materials[_mode]->Get_Shader()->Set_Vector3(m_camera->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_light->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            m_materials[_mode]->Get_Shader()->Set_FloatCustom(m_waveGeneratorTimer, "EXT_Timer");
        }
            break;
        case E_RENDER_MODE_WORLD_SPACE_REFLECTION:
        {

        }
            break;
        case E_RENDER_MODE_WORLD_SPACE_REFRACTION:
        {
        }
            break;
        default:
            break;
    }

    CGameObject3d::OnDraw(_mode);
}

void COcean::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnUnbind(_mode);
}
