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
    m_pFireEmmiter = NULL;
    m_pExplosionEmitter = NULL;
    m_pModel = NULL;
    m_pOwner = NULL;
    m_bIsDead = false;
    m_fMoveSpeed = 20.0f;
    m_iExplosionTimeStamp = 0;
    m_sColliderIdStr = "bullet_collider";
    m_eBulletState = E_BULLET_STATE_NONE;
}

CBullet::~CBullet(void)
{
    CSceneMgr::Instance()->Get_CollisionMgr()->Remove_CollisionListener(this);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pFireEmmiter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pExplosionEmitter);
    CSceneMgr::Instance()->Remove_Model(m_pModel);
}   

void CBullet::Load(void)
{
    m_pModel = (CModel*)CSceneMgr::Instance()->Add_CustomModel("tank_medium_tower.mdl", IResource::E_THREAD_BACKGROUND);
    m_pModel->Set_Texture("tank_medium.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pModel->Set_Visible(false);
    
    m_vMaxBound = m_pModel->Get_BoundingBox()->Get_MaxBound();
    m_vMinBound = m_pModel->Get_BoundingBox()->Get_MinBound();
    
    m_pFireEmmiter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFireTrail(36, glm::vec2(0.05f), glm::vec2(0.75f), 1000, false);
    m_pFireEmmiter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pFireEmmiter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pFireEmmiter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pExplosionEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFireTrail(36, glm::vec2(0.5f), glm::vec2(2.0f), 1000, false);
    m_pExplosionEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pExplosionEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pExplosionEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);

}

void CBullet::Set_Position(const glm::vec3& _vPosition)
{
    if(m_pExplosionEmitter != NULL)
    {
        m_pExplosionEmitter->Set_Position(_vPosition);
    }
    if(m_pFireEmmiter != NULL)
    {
        m_pFireEmmiter->Set_Position(_vPosition);
    }
    if(m_pModel != NULL)
    {
        m_pModel->Set_Position(_vPosition);
    }
    m_vPosition = _vPosition;
}

void CBullet::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pExplosionEmitter != NULL)
    {
        m_pExplosionEmitter->Set_Rotation(_vRotation);
    }
    if(m_pFireEmmiter != NULL)
    {
        m_pFireEmmiter->Set_Rotation(_vRotation);
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
    m_iExplosionTimeStamp = CTimer::Instance()->Get_TickCount() + 1000;
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
    m_iExplosionTimeStamp = 0;
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

    
    /*float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x + sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed, m_vPosition.z + cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed);
    int iWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    int iHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    if((m_vPosition.x < 0.0f || m_vPosition.x > iWidth || m_vPosition.z < 0.0f || m_vPosition.z > iHeight))
    {
        m_bIsDead = true;
    }
    m_vPosition.y = fHeight + k_BULLET_HEIGHT_OFFSET;
    m_vPosition.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_vPosition.z += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    Set_Position(m_vPosition);
    
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene != NULL)
    {
        unsigned int iNumCharacterControllers = pScene->Get_GameCharaterControllerMgr()->Get_NumCharacterControllers();
        for(unsigned int i = 0; i < iNumCharacterControllers; ++i)
        {
            ICharacterController* pCharacterController = pScene->Get_GameCharaterControllerMgr()->Get_CharacterController(i);
            glm::vec3 vMinBound = pCharacterController->Get_MinBound() + pCharacterController->Get_Position();
            glm::vec3 vMaxBound = pCharacterController->Get_MaxBound() + pCharacterController->Get_Position();
            if(m_vPosition.x >= vMinBound.x && 
               m_vPosition.z >= vMinBound.z &&
               m_vPosition.x <= vMaxBound.x &&
               m_vPosition.z <= vMaxBound.z)
            {
                float fDistanceToTower = glm::distance(pCharacterController->Get_TowerCenterBound(), m_vPosition);
                float fDistanceToLeftTrack = glm::distance(pCharacterController->Get_LeftTrackCenterBound(), m_vPosition);
                float fDistanceToRightTrack = glm::distance(pCharacterController->Get_RightTrackCenterBound(), m_vPosition);
                
                if(fDistanceToTower < fDistanceToLeftTrack && fDistanceToTower < fDistanceToRightTrack)
                {
                    float fTowerHealth = pCharacterController->Get_Tower()->Get_TowerHealth();
                    fTowerHealth -= 25.0f;
                    pCharacterController->Get_Tower()->Set_TowerHealth(fTowerHealth);
                }
                
                if(fDistanceToLeftTrack < fDistanceToTower && fDistanceToLeftTrack < fDistanceToRightTrack)
                {
                    float fLeftTrackHealth = pCharacterController->Get_Track()->Get_LeftTrackHealth();
                    fLeftTrackHealth -= 25.0f;
                    pCharacterController->Get_Track()->Set_LeftTrackHealth(fLeftTrackHealth);
                }
                
                if(fDistanceToRightTrack < fDistanceToTower && fDistanceToRightTrack < fDistanceToLeftTrack)
                {
                    float fRightTrackHealth = pCharacterController->Get_Track()->Get_RightTrackHealth();
                    fRightTrackHealth -= 25.0f;
                    pCharacterController->Get_Track()->Set_RightTrackHealth(fRightTrackHealth);
                }
                
                m_bIsDead = true;
            }
        }
    }*/
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
    
    if(m_eBulletState == E_BULLET_STATE_02 && CTimer::Instance()->Get_TickCount() > m_iExplosionTimeStamp)
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

void CBullet::OnOriginPositionChanged(const glm::vec3& _vPosition)
{
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(_vPosition.x, _vPosition.z) + k_BULLET_HEIGHT_OFFSET;
    m_vPosition.y = fHeight;
    m_vPosition.x = _vPosition.x;
    m_vPosition.z = _vPosition.z;
}

void CBullet::OnOriginRotationChanged(float _fAngleY)
{
    m_vRotation.y = _fAngleY;
}


