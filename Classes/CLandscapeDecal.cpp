//
//  CLandscapeDecal.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#include "CLandscapeDecal.h"

glm::mat3x3 CLandscapeDecal::m_matrixTextureTranslation = glm::mat3x3(1.0f, 0.0f, 0.5f,
                                                                      0.0f, 1.0f, 0.5f,
                                                                      0.0f, 0.0f, 1.0f);

glm::mat3x3 CLandscapeDecal::m_matrixTextureScale = glm::mat3x3(0.5f, 0.0f, 0.0f,
                                                                0.0f, 0.5f, 0.0f,
                                                                0.0f, 0.0f, 1.0f);

CLandscapeDecal::CLandscapeDecal(void)
{
    m_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    m_heightmapData = nullptr;
}

CLandscapeDecal::~CLandscapeDecal(void)
{
    
}

void CLandscapeDecal::Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename)
{
    assert(_resourceMgrsFacade != nullptr);
    SLandscapeDecalSettings* settings = _resourceMgrsFacade->LoadLandscapeDecalSettings(_filename);
    assert(settings != nullptr);

    m_width = settings->m_width;
    m_height = settings->m_height;
    m_widthOffset = settings->m_widthOffset;
    m_heightOffset = settings->m_heightOffset;

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
            assert(textureSettings->m_slot < E_TEXTURE_SLOT_MAX);
            m_materials[materialSettings->m_renderMode]->Set_Texture(texture, static_cast<E_TEXTURE_SLOT>(textureSettings->m_slot));
        }
    }

    CVertexBuffer* vertexBuffer = new CVertexBuffer(m_width * m_height, GL_STREAM_DRAW);
    SVertex* vertexData = vertexBuffer->Lock();
    
    ui32 index = 0;
    for(ui32 i = 0; i < m_width; ++i)
    {
        for(ui32 j = 0; j < m_height; ++j)
        {
            vertexData[index].m_position = glm::vec3(static_cast<f32>(i), 0.0f, static_cast<f32>(j));
            vertexData[index].m_texcoord = glm::vec2(static_cast<f32>(i) / static_cast<f32>(m_width), static_cast<f32>(j) / static_cast<f32>(m_height));
            ++index;
        }
    }
    vertexBuffer->Unlock();

    CIndexBuffer* indexBuffer = new CIndexBuffer((m_width - 1) * (m_height - 1) * 6, GL_STATIC_DRAW);
    ui16* indexData = indexBuffer->Lock();
    
    index = 0;
    for(ui32 i = 0; i < (m_width - 1); ++i)
    {
        for(ui32 j = 0; j < (m_height - 1); ++j)
        {
            indexData[index] = i + j * m_width;
            index++;
            indexData[index] = i + (j + 1) * m_width;
            index++;
            indexData[index] = i + 1 + j * m_width;
            index++;
            
            indexData[index] = i + (j + 1) * m_width;
            index++;
            indexData[index] = i + 1 + (j + 1) * m_width;
            index++;
            indexData[index] = i + 1 + j * m_width;
            index++;
        }
    }
    indexBuffer->Unlock();
    
    m_mesh = new CMesh(vertexBuffer, indexBuffer);
}

void CLandscapeDecal::OnResourceDidLoad(IResource_INTERFACE* _resource)
{
    CGameObject3d::OnResourceDidLoad(_resource);
}

void CLandscapeDecal::OnUpdate(f32 _deltatime)
{
    assert(m_heightmapData != nullptr);

    i32 roundedPositionX = m_position.x;
    i32 roundedPositionZ = m_position.z;

    ui32 index = 0;

    SVertex* vertexData = m_mesh->Get_VertexBuffer()->Lock();

    for(i32 i = -m_widthOffset; i <= m_widthOffset; ++i)
    {
        for(i32 j = -m_heightOffset; j <= m_heightOffset; ++j)
        {
            if((roundedPositionX + i) < 0 || (roundedPositionZ + j) < 0 || (roundedPositionX + i) >= m_heightmapWidth || (roundedPositionZ +j) > m_heightmapHeight)
            {
                vertexData[index].m_position.x = roundedPositionX;
                vertexData[index].m_position.y = m_heightmapData[roundedPositionX + roundedPositionZ * m_heightmapWidth] + 0.2f;
                vertexData[index].m_position.z = roundedPositionZ;
            }
            else
            {
                vertexData[index].m_position.x = roundedPositionX + i;
                vertexData[index].m_position.y = m_heightmapData[(roundedPositionX + i)  + (roundedPositionZ + j) * m_heightmapWidth] + 0.2f;
                vertexData[index].m_position.z = roundedPositionZ + j;
            }
            index++;
        }
    }

    m_matrixTextureRotation = glm::mat3x3(cosf(glm::radians(m_rotation.y)), -sinf(glm::radians(m_rotation.y)), 0.0,
                                     sinf(glm::radians(m_rotation.y)),  cosf(glm::radians(m_rotation.y)), 0.0,
                                     0.0           ,  0.0           , 1.0);
    m_matrixTextureResult = m_matrixTextureScale * m_matrixTextureRotation * m_matrixTextureTranslation;
    m_mesh->Get_VertexBuffer()->Unlock();
}

ui32 CLandscapeDecal::OnDrawIndex(void)
{
    return 256;
}

void CLandscapeDecal::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnBind(_mode);
}

void CLandscapeDecal::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
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

            m_materials[_mode]->Get_Shader()->Set_Vector3Custom(m_position, "EXT_Center");
            m_materials[_mode]->Get_Shader()->Set_Matrix3x3Custom(m_matrixTextureResult, "EXT_MATRIX_TEXTURE");
            m_materials[_mode]->Get_Shader()->Set_Vector4Custom(m_color, "EXT_Color");
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

void CLandscapeDecal::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnUnbind(_mode);
}

