//
//  CBullet.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#include "CBullet.h"
#include "CGameSceneMgr.h"
#include "CTimer.h"

CBullet::CBullet(void)
{
    m_pExplosionEmitter = nullptr;
    m_pTrailEmitter = nullptr;
    m_pModel = nullptr;
    m_pOwner = nullptr;
    m_bIsDead = false;
    m_fMoveSpeed = 20.0f;
    m_cExplosionTimeStamp = CTimer::CTime();
    m_sColliderIdStr = "bullet_collider";
    m_eBulletState = E_BULLET_STATE_NONE;
}

CBullet::~CBullet(void)
{
    CSceneMgr::Instance()->Get_CollisionMgr()->Remove_CollisionListener(this);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pExplosionEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pTrailEmitter);
    CSceneMgr::Instance()->Remove_Model(m_pModel);
}   

void CBullet::Load(void)
{
    m_pModel = (CModel*)CSceneMgr::Instance()->Add_CustomModel("tank_heavy_body.mdl", IResource::E_THREAD_ASYNC);
    m_pModel->Set_Texture("tank_medium.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pModel->Set_Visible(false);
    m_pModel->Set_Scale(glm::vec3(0.25f, 0.25f, 0.25f));
    
    m_vMaxBound = m_pModel->Get_BoundingBox()->Get_MaxBound();
    m_vMinBound = m_pModel->Get_BoundingBox()->Get_MinBound();
    
    m_vMaxBound = glm::vec3(0.25f, 0.25f, 0.25f);
    m_vMinBound = glm::vec3(-0.25f, -0.25f, -0.25f);
    
    m_pExplosionEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterExplosion(36, glm::vec2(0.5f), glm::vec2(2.0f), 1000, false);
    m_pExplosionEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pExplosionEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pExplosionEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    
    m_pTrailEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterTrail(64, glm::vec2(0.1f), glm::vec2(0.5f), 500, true);
    m_pTrailEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pTrailEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pTrailEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
}

void CBullet::Set_Position(const glm::vec3& _vPosition)
{
    if(m_pExplosionEmitter != NULL)
    {
        m_pExplosionEmitter->Set_Position(_vPosition);
    }
    if(m_pTrailEmitter != NULL)
    {
        m_pTrailEmitter->Set_Position(_vPosition);
    }
    if(m_pModel != NULL)
    {
        m_pModel->Set_Position(glm::vec3(_vPosition.x, _vPosition.y - 0.25f, _vPosition.z));
    }
    m_vPosition = _vPosition;
}

void CBullet::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pExplosionEmitter != NULL)
    {
        m_pExplosionEmitter->Set_Rotation(_vRotation);
    }
    if(m_pTrailEmitter != NULL)
    {
        m_pTrailEmitter->Set_Rotation(_vRotation);
    }
    if(m_pModel != NULL)
    {
        m_pModel->Set_Rotation(_vRotation);
    }
    m_vRotation = _vRotation;
}

void CBullet::Create(void)
{
    m_eBulletState = E_BULLET_STATE_NONE;
    Set_IsDead(false);
    CSceneMgr::Instance()->Get_CollisionMgr()->Add_CollisionListener(this, false);
    if(m_pModel != NULL)
    {
        m_pModel->Set_Visible(true);
    }
}

void CBullet::WillDestroy(void)
{
    CSceneMgr::Instance()->Get_CollisionMgr()->Remove_CollisionListener(this);
    m_cExplosionTimeStamp = CTimer::CClock::now();
    m_pTrailEmitter->Stop();
    m_pExplosionEmitter->Reset();
    m_pExplosionEmitter->Start();
    if(m_pModel != NULL)
    {
        m_pModel->Set_Visible(false);
    }
    m_eBulletState = E_BULLET_STATE_02;
}

void CBullet::Destroy(void)
{
    Set_IsDead(true);
    m_eBulletState = E_BULLET_STATE_NONE;
    m_cExplosionTimeStamp = CTimer::CTime();
}

void CBullet::_MoveForward(void)
{
    if(m_pBox2dBody != NULL)
    {
        b2Vec2 vForce = b2Vec2(0.0f, 0.0f);
        vForce.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
        vForce.y += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
        m_pBox2dBody->SetAwake(true);
        m_pBox2dBody->SetLinearVelocity(vForce);
    }
    
    if(m_pBox2dBody != NULL)
    {
        m_pBox2dBody->SetTransform(m_pBox2dBody->GetPosition(), glm::radians(m_vRotation.y));
    }
    
    Set_Position(m_vPosition);
    Set_Rotation(m_vRotation);
}

void CBullet::Update(void)
{
    if(!m_bIsDead)
    {
        _MoveForward();
    }
    
    if(m_eBulletState == E_BULLET_STATE_01)
    {
        WillDestroy();
    }
    
    if(m_eBulletState == E_BULLET_STATE_02 && CTimer::Get_TimeInterval(CTimer::CClock::now(), m_cExplosionTimeStamp) > 1000)
    {
        Destroy();
    }
}

void CBullet::OnCollision(ICollisionDelegate *_pCollider)
{
    if(_pCollider != m_pOwner)
    {
        m_eBulletState = E_BULLET_STATE_01;
    }
}

void CBullet::OnBox2dPositionChanged(const glm::vec3& _vPosition)
{
    m_vPosition.x = _vPosition.x;
    m_vPosition.z = _vPosition.z;
}

void CBullet::OnBox2dRotationChanged(float _fAngleY)
{
    m_vRotation.y = _fAngleY;
}


