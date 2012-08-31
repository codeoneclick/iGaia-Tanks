//
//  ITankBody.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "ITankBody.h"
#include "CSceneMgr.h"

ITankBody::ITankBody(void)
{
    m_pBody = nullptr;
    m_pLeftExhaustSmokeEmitter = nullptr;
    m_pRightExhaustSmokeEmitter = nullptr;
}

ITankBody::~ITankBody(void)
{
    std::cout<<"[~ITankBody] delete"<<std::endl;
    CSceneMgr::Instance()->Remove_Model(m_pBody);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pLeftExhaustSmokeEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pRightExhaustSmokeEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pLeftDirtEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pRightDirtEmitter);
}

void ITankBody::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pBody != NULL)
    {
        m_pBody->Set_Position(_vPosition);
    }
    
    if(!CMathHelper::IsFloatEqual(m_vRotation.x, m_vCachedRotation.x) || !CMathHelper::IsFloatEqual(m_vRotation.y, m_vCachedRotation.y) || !CMathHelper::IsFloatEqual(m_vRotation.z, m_vCachedRotation.z))
    {
        m_vCachedPosition = m_vRotation;
        m_mTransformHelper = glm::rotate(glm::mat4(1.0f),    m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mTransformHelper = glm::rotate(m_mTransformHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mTransformHelper = glm::rotate(m_mTransformHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    if(m_pLeftExhaustSmokeEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pBody->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vLeftExhaustEmitterOffset.x, m_vBoundPositionHelper.y + m_vLeftExhaustEmitterOffset.y, m_vBoundPositionHelper.z + m_vLeftExhaustEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pLeftExhaustSmokeEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    if(m_pRightExhaustSmokeEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pBody->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vRightExhaustEmitterOffset.x, m_vBoundPositionHelper.y + m_vRightExhaustEmitterOffset.y, m_vBoundPositionHelper.z + m_vRightExhaustEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pRightExhaustSmokeEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    if(m_pLeftDirtEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pBody->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vLeftDirtEmitterOffset.x, m_vBoundPositionHelper.y + m_vLeftDirtEmitterOffset.y, m_vBoundPositionHelper.z + m_vLeftDirtEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pLeftDirtEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    if(m_pRightDirtEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pBody->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vRightDirtEmitterOffset.x, m_vBoundPositionHelper.y + m_vRightDirtEmitterOffset.y, m_vBoundPositionHelper.z + m_vRightDirtEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pRightDirtEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    m_vPosition = _vPosition;
}

void ITankBody::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pBody != NULL)
    {
        m_pBody->Set_Rotation(_vRotation);
    }
    m_vRotation = _vRotation;
}

void ITankBody::StartExhaustEmitt(bool _bValue)
{
    if(_bValue)
    {
        if(m_pLeftExhaustSmokeEmitter != NULL)
        {
            m_pLeftExhaustSmokeEmitter->Start();
        }
        if(m_pRightExhaustSmokeEmitter != NULL)
        {
            m_pRightExhaustSmokeEmitter->Start();
        }
    }
    else
    {
        if(m_pLeftExhaustSmokeEmitter != NULL)
        {
            m_pLeftExhaustSmokeEmitter->Stop();
        }
        if(m_pRightExhaustSmokeEmitter != NULL)
        {
            m_pRightExhaustSmokeEmitter->Stop();
        }
    }
}

void ITankBody::StartDirtEmitt(bool _bValue)
{
    if(_bValue)
    {
        if(m_pRightDirtEmitter != NULL)
        {
            m_pRightDirtEmitter->Start();
        }
        if(m_pLeftDirtEmitter != NULL)
        {
            m_pLeftDirtEmitter->Start();
        }
    }
    else
    {
        if(m_pRightDirtEmitter != NULL)
        {
            m_pRightDirtEmitter->Stop();
        }
        if(m_pLeftDirtEmitter != NULL)
        {
            m_pLeftDirtEmitter->Stop();
        }
    }
}

void ITankBody::Load(void)
{
    
}

void ITankBody::Update(void)
{
    
}

