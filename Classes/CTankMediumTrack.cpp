//
//  CTankMediumTrack.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CTankMediumTrack.h"
#include "CSceneMgr.h"

CTankMediumTrack::CTankMediumTrack(void)
{
    m_vLeftTrackEmitterOffset = glm::vec3(0.0f, 0.66f, 0.0f);
    m_vRightTrackEmitterOffset = glm::vec3(0.0f, 0.66f, 0.0f);
}

CTankMediumTrack::~CTankMediumTrack(void)
{
    
}

void CTankMediumTrack::Load(void)
{
    m_pLeftTrack = (CModel*)CSceneMgr::Instance()->Add_CustomModel("tank_medium_left_track.mdl", IResource::E_THREAD_BACKGROUND);
    m_pLeftTrack->Set_Texture("tank_track.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pLeftTrack->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pLeftTrack->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pLeftTrack->Create_BoundingBox();
    m_pLeftTrack->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_pRightTrack = (CModel*)CSceneMgr::Instance()->Add_CustomModel("tank_medium_right_track.mdl", IResource::E_THREAD_BACKGROUND);
    m_pRightTrack->Set_Texture("tank_track.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pRightTrack->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pRightTrack->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pRightTrack->Create_BoundingBox();
    m_pRightTrack->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_vLeftTrackMaxBound = m_pLeftTrack->Get_BoundingBox()->Get_MaxBound();
    m_vLeftTrackMinBound = m_pLeftTrack->Get_BoundingBox()->Get_MinBound();
    m_vLeftTrackCenterBound = m_pLeftTrack->Get_BoundingBox()->Get_Center();
    
    m_vRightTrackCenterBound = m_pRightTrack->Get_BoundingBox()->Get_MaxBound();
    m_vRightTrackCenterBound = m_pRightTrack->Get_BoundingBox()->Get_MinBound();
    m_vRightTrackCenterBound = m_pRightTrack->Get_BoundingBox()->Get_Center();
    
    m_pLeftTrackSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.025f), glm::vec2(0.45f), 1000, true);
    m_pLeftTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pLeftTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pLeftTrackSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pLeftTrackFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pLeftTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pLeftTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pLeftTrackFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pRightTrackSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.025f), glm::vec2(0.45f), 1000, true);
    m_pRightTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pRightTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pRightTrackSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pRightTrackFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pRightTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pRightTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pRightTrackFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
}

void CTankMediumTrack::Update(void)
{
    ITankTrack::Update();
}