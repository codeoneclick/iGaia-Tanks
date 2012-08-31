//
//  ITankTrack.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "ITankTrack.h"
#include "CSceneMgr.h"

ITankTrack::ITankTrack(void)
{
    m_pLeftTrack = NULL;
    m_pRightTrack = NULL;
    
    m_pLeftTrackFireEmitter = NULL;
    m_pLeftTrackSmokeEmitter = NULL;
    m_pRightTrackFireEmitter = NULL;
    m_pRightTrackSmokeEmitter = NULL;
    
    m_fLeftTrackMoveOffset = 0.0f;
    m_fRightTrackMoveOffset = 0.0f;
}

ITankTrack::~ITankTrack(void)
{
    std::cout<<"[~ITankTrack] delete"<<std::endl;
    CSceneMgr::Instance()->Remove_Model(m_pLeftTrack);
    CSceneMgr::Instance()->Remove_Model(m_pRightTrack);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pLeftTrackFireEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pLeftTrackSmokeEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pRightTrackFireEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pRightTrackSmokeEmitter);
}

void ITankTrack::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pLeftTrack != NULL)
    {
        m_pLeftTrack->Set_Position(_vPosition);
    }
    
    if(m_pRightTrack != NULL)
    {
        m_pRightTrack->Set_Position(_vPosition);
    }
    
    if(!CMathHelper::IsFloatEqual(m_vRotation.x, m_vCachedRotation.x) || !CMathHelper::IsFloatEqual(m_vRotation.y, m_vCachedRotation.y) || !CMathHelper::IsFloatEqual(m_vRotation.z, m_vCachedRotation.z))
    {
        m_vCachedPosition = m_vRotation;
        m_mTransformHelper = glm::rotate(glm::mat4(1.0f),    m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mTransformHelper = glm::rotate(m_mTransformHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mTransformHelper = glm::rotate(m_mTransformHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    if(m_pLeftTrackSmokeEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pLeftTrack->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vLeftTrackEmitterOffset.x, m_vBoundPositionHelper.y + m_vLeftTrackEmitterOffset.y, m_vBoundPositionHelper.z - m_vLeftTrackEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pLeftTrackSmokeEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    if(m_pRightTrackSmokeEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pRightTrack->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vRightTrackEmitterOffset.x, m_vBoundPositionHelper.y + m_vRightTrackEmitterOffset.y, m_vBoundPositionHelper.z + m_vRightTrackEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pRightTrackSmokeEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    if(m_pLeftTrackFireEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pLeftTrack->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vLeftTrackEmitterOffset.x, m_vBoundPositionHelper.y + m_vLeftTrackEmitterOffset.y, m_vBoundPositionHelper.z - m_vLeftTrackEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pLeftTrackFireEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    if(m_pRightTrackFireEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pRightTrack->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vRightTrackEmitterOffset.x, m_vBoundPositionHelper.y + m_vRightTrackEmitterOffset.y, m_vBoundPositionHelper.z + m_vRightTrackEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pRightTrackFireEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    m_vPosition = _vPosition;
    //std::cout<<"[ITankTrack::Set_Position] Position : "<<m_vPosition.x<<","<<m_vPosition.z<<std::endl;
}

void ITankTrack::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pLeftTrack != NULL)
    {
        m_pLeftTrack->Set_Rotation(_vRotation);
    }
    
    if(m_pRightTrack != NULL)
    {
        m_pRightTrack->Set_Rotation(_vRotation);
    }
    m_vRotation = _vRotation;
}

void ITankTrack::Move_LeftTrack(float _fDelta)
{
    m_fLeftTrackMoveOffset -= _fDelta;
}

void ITankTrack::Move_RightTrack(float _fDelta)
{
    m_fRightTrackMoveOffset -= _fDelta;
}

void ITankTrack::Load(void)
{
    
}

void ITankTrack::Update(void)
{
    if(m_pLeftTrack != NULL)
    {
        m_pLeftTrack->Set_TexCoordOffset(glm::vec2(0.0f, m_fLeftTrackMoveOffset));
    }
    
    if(m_pRightTrack)
    {
        m_pRightTrack->Set_TexCoordOffset(glm::vec2(0.0f, m_fRightTrackMoveOffset));
    }
    
    float fLeftTrackPercentHealth = m_fLeftTrackCurrentHealth / m_fLeftTrackTotalHealth;
    
    if(fLeftTrackPercentHealth > 0.75f)
    {
        m_pLeftTrackFireEmitter->Stop();
        m_pLeftTrackSmokeEmitter->Stop();
    }
    else if(fLeftTrackPercentHealth < 0.75f && fLeftTrackPercentHealth > 0.25f)
    {
        m_pLeftTrackSmokeEmitter->Start();
        m_pLeftTrackFireEmitter->Stop();
    }
    else if(fLeftTrackPercentHealth < 0.25f)
    {
        m_pLeftTrackSmokeEmitter->Stop();
        m_pLeftTrackFireEmitter->Start();
    }
        
    
    float fRightTrackPercentHealth = m_fRightTrackCurrentHealth / m_fRightTrackTotalHealth;
    
    if(fRightTrackPercentHealth > 0.75f)
    {
        m_pRightTrackFireEmitter->Stop();
        m_pRightTrackSmokeEmitter->Stop();
    }
    else if(fRightTrackPercentHealth < 0.75f && fRightTrackPercentHealth > 0.25f)
    {
        m_pRightTrackSmokeEmitter->Start();
        m_pRightTrackFireEmitter->Stop();
    }
    else if(fRightTrackPercentHealth < 0.25f)
    {
        m_pRightTrackSmokeEmitter->Stop();
        m_pRightTrackFireEmitter->Start();
    }
}




