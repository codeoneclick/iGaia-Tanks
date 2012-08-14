//
//  CTankHeavyTower.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CTankHeavyTower.h"
#include "CSceneMgr.h"

CTankHeavyTower::CTankHeavyTower(void)
{
    m_vTowerEmitterOffset = glm::vec3(0.0f, 0.66f, 0.0f);
    m_vTowerGunOffset = glm::vec3(1.11f, 1.33f, 1.11f);
}

CTankHeavyTower::~CTankHeavyTower(void)
{
    
}

void CTankHeavyTower::Load(void)
{
    m_pTower = (CModel*)CSceneMgr::Instance()->Add_CustomModel("tank_heavy_tower.mdl", IResource::E_THREAD_BACKGROUND);
    m_pTower->Set_Texture("tank_heavy.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pTower->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pTower->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pTower->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_vMaxBound = m_pTower->Get_BoundingBox()->Get_MaxBound();
    m_vMinBound = m_pTower->Get_BoundingBox()->Get_MinBound();
    m_vCenterBound = m_pTower->Get_BoundingBox()->Get_Center();
    
    m_pTowerSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pTowerSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pTowerSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pTowerSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pTowerFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pTowerFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pTowerFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pTowerFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
}

void CTankHeavyTower::Update(void)
{
    ITankTower::Update();
}