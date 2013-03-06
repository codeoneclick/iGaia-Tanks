//
//  HSettings_DTO.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef HSettings_DTO_h
#define HSettings_DTO_h

struct STextureSettings
{
    std::string m_name;
    ui32 m_slot;
    ui32 m_wrap;
};

struct SShaderSettings
{
    std::string m_vsName;
    std::string m_fsName;
    ui32 m_shaderGuid;
};

struct SMaterialSettings
{
    bool m_isCullFace;
    bool m_isBlend;
    bool m_isDepthTest;
    bool m_isDepthMask;
    ui32 m_cullFaceMode;
    ui32 m_blendFunctionSource;
    ui32 m_blendFunctionDestination;

    std::vector<const STextureSettings*> m_texturesSettings;
    const SShaderSettings* m_shaderSettings;

    ui32 m_renderMode;
};

struct SObject3dSettings
{
    std::vector<const SMaterialSettings*> m_materialsSettings;
};

struct SShape3dSettings : public SObject3dSettings
{
    std::string m_meshName;
};

struct SOceanSettings : public SObject3dSettings
{
    f32 m_width;
    f32 m_height;
    f32 m_altitude;
};

struct SSkyDomeSettings : public SObject3dSettings
{
};

struct LandscapeSettings : public SObject3dSettings
{
    f32 m_width;
    f32 m_height;
    std::string m_heightmapDataFileName;
    std::string m_splattingDataFileName;
};

struct SParticleEmitterSettings : public SObject3dSettings
{
    ui32 m_numParticles;

    f32 m_duration;
    f32 m_durationRandomness;

    f32 m_velocitySensitivity;

    f32 m_minHorizontalVelocity;
    f32 m_maxHorizontalVelocity;

    f32 m_minVerticalVelocity;
    f32 m_maxVerticalVelocity;

    f32 m_endVelocity;

    glm::vec3 m_gravity;

    glm::u8vec4 m_startColor;
    glm::u8vec4 m_endColor;

    glm::vec2 m_startSize;
    glm::vec2 m_endSize;

    f32 m_minParticleEmittInterval;
    f32 m_maxParticleEmittInterval;
};

#endif
