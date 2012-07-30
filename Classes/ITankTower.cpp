//
//  ITankTower.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "ITankTower.h"
#include "CSceneMgr.h"

ITankTower::ITankTower(void)
{
    m_pTower = NULL;
    m_pTowerFireEmitter = NULL;
    m_pTowerSmokeEmitter = NULL;
    m_vTowerGunOffset = glm::vec3(0.0f, 0.0f, 0.0f);
}

ITankTower::~ITankTower(void)
{
    std::cout<<"[~ITankTower] delete"<<std::endl;
    CSceneMgr::Instance()->Remove_Model(m_pTower);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pTowerFireEmitter);
    CSceneMgr::Instance()->Get_ParticleMgr()->Remove_ParticleEmitter(m_pTowerSmokeEmitter);
}

void ITankTower::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pTower != NULL)
    {
        m_pTower->Set_Position(_vPosition);
    }
    
    if(!CMathHelper::Instance()->IsFloatEqual(m_vRotation.x, m_vCachedRotation.x) || !CMathHelper::Instance()->IsFloatEqual(m_vRotation.y, m_vCachedRotation.y) || !CMathHelper::Instance()->IsFloatEqual(m_vRotation.z, m_vCachedRotation.z))
    {
        m_vCachedPosition = m_vRotation;
        m_mTransformHelper = glm::rotate(glm::mat4(1.0f),    m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mTransformHelper = glm::rotate(m_mTransformHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mTransformHelper = glm::rotate(m_mTransformHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    if(m_pTowerSmokeEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pTower->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vTowerEmitterOffset.x, m_vBoundPositionHelper.y + m_vTowerEmitterOffset.y, m_vBoundPositionHelper.z - m_vTowerEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pTowerSmokeEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    
    if(m_pTowerFireEmitter != NULL)
    {
        m_vBoundPositionHelper = m_pTower->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vBoundPositionHelper.x + m_vTowerEmitterOffset.x, m_vBoundPositionHelper.y + m_vTowerEmitterOffset.y, m_vBoundPositionHelper.z - m_vTowerEmitterOffset.z, 1.0f);
        m_vTransformHelper = m_mTransformHelper * m_vTransformHelper;
        m_pTowerFireEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    m_vPosition = _vPosition;
}

void ITankTower::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pTower != NULL)
    {
        m_pTower->Set_Rotation(_vRotation);
    }
    m_vRotation = _vRotation;
}


void ITankTower::Load(void)
{
    
}

void ITankTower::Update(void)
{
    
}