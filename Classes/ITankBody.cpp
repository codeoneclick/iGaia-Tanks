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
    m_pBody = NULL;
    m_pLeftExhaustSmokeEmitter = NULL;
    m_pRightExhaustSmokeEmitter = NULL;
}

ITankBody::~ITankBody(void)
{
    std::cout<<"[~ITankBody] delete"<<std::endl;
    CSceneMgr::Instance()->Remove_Model(m_pBody);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pLeftExhaustSmokeEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pRightExhaustSmokeEmitter);
}

void ITankBody::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pBody != NULL)
    {
        m_pBody->Set_Position(_vPosition);
    }
    
    if(!CMathHelper::Instance()->IsFloatEqual(m_vRotation.x, m_vCachedRotation.x) || !CMathHelper::Instance()->IsFloatEqual(m_vRotation.y, m_vCachedRotation.y) || !CMathHelper::Instance()->IsFloatEqual(m_vRotation.z, m_vCachedRotation.z))
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

void ITankBody::StartExhaust(bool _bValue)
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

void ITankBody::Load(void)
{
    
}

void ITankBody::Update(void)
{
    
}

