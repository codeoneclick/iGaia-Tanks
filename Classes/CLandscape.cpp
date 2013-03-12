//
//  CLandscape.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CLandscape.h"

CLandscape::CLandscape(void)
{
    m_heightmapProcessor = new CHeightmapProcessor();
}

CLandscape::~CLandscape(void)
{

}

void CLandscape::Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename)
{
    assert(_resourceMgrsFacade != nullptr);
    SLandscapeSettings* settings = _resourceMgrsFacade->LoadLandscapeSettings(_filename);
    assert(settings != nullptr);

    assert(m_heightmapProcessor != nullptr);
    m_heightmapProcessor->Process(settings->m_heightmapDataFileName, glm::vec2(settings->m_width, settings->m_height), settings->m_splattingDataFileName, glm::vec2(settings->m_width, settings->m_height));

    m_mesh = m_heightmapProcessor->Get_HeightmapMesh();
    assert(m_mesh != nullptr);

    m_quadTree = new CQuadTree();
    m_quadTree->BuildRoot(m_mesh->Get_VertexBuffer(), m_mesh->Get_IndexBuffer(), m_mesh->Get_MaxBound(), m_mesh->Get_MinBound(), 8, settings->m_width);

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
            CTexture* texture = _resourceMgrsFacade->LoadTexture(textureSettings->m_name);
            texture->Set_WrapMode(textureSettings->m_wrap);
            assert(texture != nullptr);
            assert(textureSettings->m_slot >= 0 && textureSettings->m_slot < E_TEXTURE_SLOT_MAX);
            m_materials[materialSettings->m_renderMode]->Set_Texture(texture, static_cast<E_TEXTURE_SLOT>(textureSettings->m_slot));
        }
    }
}

void CLandscape::OnResourceDidLoad(IResource_INTERFACE* _resource)
{
    CGameObject3d::OnResourceDidLoad(_resource);
}

void CLandscape::OnUpdate(f32 _deltatime)
{
    assert(m_quadTree != nullptr);
    assert(m_camera != nullptr);
    assert(m_camera->Get_Frustum() != nullptr);
    m_quadTree->OnUpdate(m_camera->Get_Frustum());
    CGameObject3d::OnUpdate(_deltatime);
}

ui32 CLandscape::OnDrawIndex(void)
{
    return 1;
}

void CLandscape::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnBind(_mode);
}

void CLandscape::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
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
        }
            break;
        case E_RENDER_MODE_WORLD_SPACE_REFLECTION:
        {
            assert(m_materials[_mode]->Get_Shader() != nullptr);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_matrixWorld, E_SHADER_ATTRIBUTE_MATRIX_WORLD);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ProjectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_PROJECTION);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ViewReflectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_VIEW);

            m_materials[_mode]->Get_Shader()->Set_Vector3(m_camera->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_light->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector4(m_materials[_mode]->Get_Clipping(), E_SHADER_ATTRIBUTE_VECTOR_CLIP_PLANE);
        }
            break;
        case E_RENDER_MODE_WORLD_SPACE_REFRACTION:
        {
            assert(m_materials[_mode]->Get_Shader() != nullptr);

            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_matrixWorld, E_SHADER_ATTRIBUTE_MATRIX_WORLD);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ProjectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_PROJECTION);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ViewMatrix(), E_SHADER_ATTRIBUTE_MATRIX_VIEW);

            m_materials[_mode]->Get_Shader()->Set_Vector3(m_camera->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_light->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector4(glm::vec4(m_materials[_mode]->Get_Clipping().x, m_materials[_mode]->Get_Clipping().y * -1.0f, m_materials[_mode]->Get_Clipping().z, m_materials[_mode]->Get_Clipping().w), E_SHADER_ATTRIBUTE_VECTOR_CLIP_PLANE);
        }
            break;
        default:
            break;
    }

    CGameObject3d::OnDraw(_mode);
}

void CLandscape::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnUnbind(_mode);
}



