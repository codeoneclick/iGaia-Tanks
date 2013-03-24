//
//  CParticleEmitter.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CParticleEmitter.h"
#include "CCommon.h"

CParticleEmitter::CParticleEmitter(void)
{
    m_settings = nullptr;
    m_particles = nullptr;
    m_lastEmittTimestamp = 0;
}

CParticleEmitter::~CParticleEmitter(void)
{

}

void CParticleEmitter::Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename)
{

    assert(_resourceMgrsFacade != nullptr);
    m_settings = _resourceMgrsFacade->LoadParticleEmitterSettings(_filename);
    assert(m_settings != nullptr);

    m_particles = new SParticle[m_settings->m_numParticles];

    CVertexBuffer* vertexBuffer = new CVertexBuffer(m_settings->m_numParticles * 4, GL_STREAM_DRAW);
    SVertex* vertexData = vertexBuffer->Lock();

    for(ui32 i = 0; i < m_settings->m_numParticles; ++i)
    {
        m_particles[i].m_size = glm::vec2(0.0f, 0.0f);
        m_particles[i].m_color = glm::u8vec4(0, 0, 0, 0);

        vertexData[i * 4 + 0].m_texcoord = glm::vec2( 0.0f,  0.0f);
        vertexData[i * 4 + 1].m_texcoord = glm::vec2( 1.0f,  0.0f);
        vertexData[i * 4 + 2].m_texcoord = glm::vec2( 1.0f,  1.0f);
        vertexData[i * 4 + 3].m_texcoord = glm::vec2( 0.0f,  1.0f);
    }
    vertexBuffer->Unlock();

    CIndexBuffer* indexBuffer = new CIndexBuffer(m_settings->m_numParticles * 6, GL_STREAM_DRAW);
    ui16* indexData = indexBuffer->Lock();

    for(ui32 i = 0; i < m_settings->m_numParticles; ++i)
    {
        indexData[i * 6 + 0] = static_cast<ui16>(i * 4 + 0);
        indexData[i * 6 + 1] = static_cast<ui16>(i * 4 + 1);
        indexData[i * 6 + 2] = static_cast<ui16>(i * 4 + 2);

        indexData[i * 6 + 3] = static_cast<ui16>(i * 4 + 0);
        indexData[i * 6 + 4] = static_cast<ui16>(i * 4 + 2);
        indexData[i * 6 + 5] = static_cast<ui16>(i * 4 + 3);
    }

    indexBuffer->Unlock();

    m_mesh = new CMesh(vertexBuffer, indexBuffer);

    std::vector<const SMaterialSettings*> m_materialsSettings = m_settings->m_materialsSettings;
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

void CParticleEmitter::CreateParticle(ui32 _index)
{
    m_particles[_index].m_position = m_position;
    m_particles[_index].m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    m_particles[_index].m_size = m_settings->m_startSize;
    m_particles[_index].m_color = m_settings->m_startColor;

    m_particles[_index].m_timestamp = Get_TickCount();

    f32 horizontalVelocity = glm::mix(m_settings->m_minHorizontalVelocity, m_settings->m_maxHorizontalVelocity, Get_Random(0.0f, 1.0f));

    f32 horizontalAngle = Get_Random(0.0f, 1.0f) * M_PI * 2.0f;

    m_particles[_index].m_velocity.x += horizontalVelocity * cosf(horizontalAngle);
    m_particles[_index].m_velocity.z += horizontalVelocity * sinf(horizontalAngle);

    m_particles[_index].m_velocity.y += glm::mix(m_settings->m_minVerticalVelocity, m_settings->m_maxVerticalVelocity, Get_Random(0.0f, 1.0f));
    m_particles[_index].m_velocity *= m_settings->m_velocitySensitivity;
}

void CParticleEmitter::OnUpdate(f32 _deltatime)
{
    CGameObject3d::OnUpdate(_deltatime);

    SVertex* vertexData = m_mesh->Get_VertexBuffer()->Lock();
    f32 currentTime = Get_TickCount();

    for(ui32 i = 0; i < m_settings->m_numParticles; ++i)
    {
        f32 particleAge = currentTime - m_particles[i].m_timestamp;

        if(particleAge > m_settings->m_duration)
        {
            if((currentTime - m_lastEmittTimestamp) > Get_Random(m_settings->m_minParticleEmittInterval, m_settings->m_maxParticleEmittInterval))
            {
                m_lastEmittTimestamp = currentTime;
                CreateParticle(i);
            }
            else
            {
                m_particles[i].m_size = glm::vec2(0.0f, 0.0f);
                m_particles[i].m_color = glm::u8vec4(0, 0, 0, 0);
            }
        }

        f32 particleClampAge = glm::clamp( particleAge / m_settings->m_duration, 0.0f, 1.0f);

        f32 startVelocity = glm::length(m_particles[i].m_velocity);
        f32 endVelocity = m_settings->m_endVelocity * startVelocity;
        f32 velocityIntegral = startVelocity * particleClampAge + (endVelocity - startVelocity) * particleClampAge * particleClampAge / 2.0f;
        m_particles[i].m_position += glm::normalize(m_particles[i].m_velocity) * velocityIntegral * m_settings->m_duration;
        m_particles[i].m_position += m_settings->m_gravity * particleAge * particleClampAge;

        f32 randomValue = Get_Random(0.0f, 1.0f);
        f32 startSize = glm::mix(m_settings->m_startSize.x, m_settings->m_startSize.y, randomValue);
        f32 endSize = glm::mix(m_settings->m_endSize.x, m_settings->m_endSize.y, randomValue);
        m_particles[i].m_size = glm::vec2(glm::mix(startSize, endSize, particleClampAge));

        m_particles[i].m_color = glm::mix(m_settings->m_startColor, m_settings->m_endColor, particleClampAge);
        m_particles[i].m_color.a = glm::mix(m_settings->m_startColor.a, m_settings->m_endColor.a, particleClampAge);

        glm::mat4x4 matrixSpherical = m_camera->Get_SphericalMatrixForPosition(m_particles[i].m_position);

        glm::vec4 position = glm::vec4(-m_particles[i].m_size.x, -m_particles[i].m_size.y, 0.0f, 1.0f);
        position = matrixSpherical * position;
        vertexData[i * 4 + 0].m_position = glm::vec3(position.x, position.y, position.z);

        position = glm::vec4(m_particles[i].m_size.x, -m_particles[i].m_size.y, 0.0f, 1.0f);
        position = matrixSpherical * position;
        vertexData[i * 4 + 1].m_position = glm::vec3(position.x, position.y, position.z);

        position = glm::vec4(m_particles[i].m_size.x, m_particles[i].m_size.y, 0.0f, 1.0f);
        position = matrixSpherical * position;
        vertexData[i * 4 + 2].m_position = glm::vec3(position.x, position.y, position.z);

        position = glm::vec4(-m_particles[i].m_size.x, m_particles[i].m_size.y, 0.0f, 1.0f);
        position = matrixSpherical * position;
        vertexData[i * 4 + 3].m_position = glm::vec3(position.x, position.y, position.z);

        vertexData[i * 4 + 0].m_color = m_particles[i].m_color;
        vertexData[i * 4 + 1].m_color = m_particles[i].m_color;
        vertexData[i * 4 + 2].m_color = m_particles[i].m_color;
        vertexData[i * 4 + 3].m_color = m_particles[i].m_color;
    }
    m_mesh->Get_VertexBuffer()->Unlock();
}

void CParticleEmitter::OnResourceDidLoad(IResource_INTERFACE* _resource)
{
    CGameObject3d::OnResourceDidLoad(_resource);
}

ui32 CParticleEmitter::OnDrawIndex(void)
{
    return 128;
}

void CParticleEmitter::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnBind(_mode);
}

void CParticleEmitter::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
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

void CParticleEmitter::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnUnbind(_mode);
}
