//
//  CNavigationHelper.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/15/12.
//
//

#include "CNavigationHelper.h"
#include "CSceneMgr.h"

CNavigationHelper::CNavigationHelper(void)
{
    m_fMoveForwardSpeed = 0.0f;
    m_fMoveBackwardSpeed = 0.0f;
    m_fStrafeSpeed = 0.0f;
    m_fSteerSpeed = 0.0f;
    m_vMaxBound = glm::vec3(k_NAVIGATION_HELPER_BOUND_MAX_MIN);
    m_vMinBound = glm::vec3(-k_NAVIGATION_HELPER_BOUND_MAX_MIN);
    m_bIsUseHeightMap = false;
    
    m_vCurrentPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vCurrentRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    
    m_pOwner = NULL;
}

CNavigationHelper::~CNavigationHelper(void)
{
    
}

float CNavigationHelper::_Get_HeightForPosition(const glm::vec3 &_vPosition)
{
    if(CSceneMgr::Instance()->Get_HeightMapSetterRef() != NULL)
    {
        return CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(_vPosition.x, _vPosition.z);
    }
    else
    {
        std::cout<<"[CNavigationHelper::_Get_HeightForPosition] HeightMapSetter is NULL"<<std::endl;
        return 0.0f;
    }
}

bool CNavigationHelper::MoveForward(void)
{
    glm::vec3 vPreComputePosition = glm::vec3(m_vCurrentPosition.x + sinf(m_vCurrentRotation.y) * m_fMoveForwardSpeed, 0.0f, m_vCurrentPosition.z + cosf(m_vCurrentRotation.y) * m_fMoveForwardSpeed);
    if(vPreComputePosition.x < m_vMinBound.x || vPreComputePosition.z < m_vMinBound.z || vPreComputePosition.x > m_vMaxBound.x || vPreComputePosition.z > m_vMaxBound.z)
    {
        return false;
    }
    if(m_bIsUseHeightMap == true)
    {
        vPreComputePosition.y = _Get_HeightForPosition(vPreComputePosition);
    }
    m_vCurrentPosition = vPreComputePosition;
    if(m_pOwner != NULL)
    {
        m_pOwner->OnNavigationPositionChanged(m_vCurrentPosition);
    }
    return true;
}

bool CNavigationHelper::MoveBackward(void)
{
    glm::vec3 vPreComputePosition = glm::vec3(m_vCurrentPosition.x - sinf(m_vCurrentRotation.y) * m_fMoveBackwardSpeed, 0.0f, m_vCurrentPosition.z - cosf(m_vCurrentRotation.y) * m_fMoveBackwardSpeed);
    if(vPreComputePosition.x < m_vMinBound.x || vPreComputePosition.z < m_vMinBound.z || vPreComputePosition.x > m_vMaxBound.x || vPreComputePosition.z > m_vMaxBound.z)
    {
        return false;
    }
    if(m_bIsUseHeightMap == true)
    {
        vPreComputePosition.y = _Get_HeightForPosition(vPreComputePosition);
    }
    m_vCurrentPosition = vPreComputePosition;
    if(m_pOwner != NULL)
    {
        m_pOwner->OnNavigationPositionChanged(m_vCurrentPosition);
    }
    return true;
}

bool CNavigationHelper::MoveLeft(void)
{
    glm::vec3 vPreComputePosition = glm::vec3(m_vCurrentPosition.x - sinf(-m_vCurrentRotation.y) * m_fStrafeSpeed, 0.0f, m_vCurrentPosition.z - cosf(-m_vCurrentRotation.y) * m_fStrafeSpeed);
    if(vPreComputePosition.x < m_vMinBound.x || vPreComputePosition.z < m_vMinBound.z || vPreComputePosition.x > m_vMaxBound.x || vPreComputePosition.z > m_vMaxBound.z)
    {
        return false;
    }
    if(m_bIsUseHeightMap == true)
    {
        vPreComputePosition.y = _Get_HeightForPosition(vPreComputePosition);
    }
    m_vCurrentPosition = vPreComputePosition;
    if(m_pOwner != NULL)
    {
        m_pOwner->OnNavigationPositionChanged(m_vCurrentPosition);
    }
    return true;
}

bool CNavigationHelper::MoveRight(void)
{
    glm::vec3 vPreComputePosition = glm::vec3(m_vCurrentPosition.x + sinf(-m_vCurrentRotation.y) * m_fStrafeSpeed, 0.0f, m_vCurrentPosition.z + cosf(-m_vCurrentRotation.y) * m_fStrafeSpeed);
    if(vPreComputePosition.x < m_vMinBound.x || vPreComputePosition.z < m_vMinBound.z || vPreComputePosition.x > m_vMaxBound.x || vPreComputePosition.z > m_vMaxBound.z)
    {
        return false;
    }
    if(m_bIsUseHeightMap == true)
    {
        vPreComputePosition.y = _Get_HeightForPosition(vPreComputePosition);
    }
    m_vCurrentPosition = vPreComputePosition;
    if(m_pOwner != NULL)
    {
        m_pOwner->OnNavigationPositionChanged(m_vCurrentPosition);
    }
    return true;
}

void CNavigationHelper::SteerLeft(void)
{
    m_vCurrentRotation.y -= m_fSteerSpeed;
    if(m_pOwner != NULL)
    {
        m_pOwner->OnNavigationRotationChanged(m_vCurrentRotation);
    }
}

void CNavigationHelper::SteerRight(void)
{
    m_vCurrentRotation.y += m_fSteerSpeed;
    if(m_pOwner != NULL)
    {
        m_pOwner->OnNavigationRotationChanged(m_vCurrentRotation);
    }
}

glm::vec3 CNavigationHelper::Get_MoveForwardForceOffset(void)
{
    glm::vec3 vPreComputeForce = glm::vec3(sinf(m_vCurrentRotation.y) * m_fMoveForwardSpeed, 0.0f, cosf(m_vCurrentRotation.y) * m_fMoveForwardSpeed);
    if(m_bIsUseHeightMap == true)
    {
        vPreComputeForce.y = _Get_HeightForPosition(vPreComputeForce);
    }
    return vPreComputeForce;
}

glm::vec3 CNavigationHelper::Get_MoveBackwardForceOffset(void)
{
    glm::vec3 vPreComputeForce = glm::vec3(-sinf(m_vCurrentRotation.y) * m_fMoveBackwardSpeed, 0.0f, -cosf(m_vCurrentRotation.y) * m_fMoveBackwardSpeed);
    if(m_bIsUseHeightMap == true)
    {
        vPreComputeForce.y = _Get_HeightForPosition(vPreComputeForce);
    }
    return vPreComputeForce;
}

glm::vec3 CNavigationHelper::Get_MoveLeftForceOffset(void)
{
    glm::vec3 vPreComputeForce = glm::vec3(-sinf(-m_vCurrentRotation.y) * m_fStrafeSpeed, 0.0f, -cosf(-m_vCurrentRotation.y) * m_fStrafeSpeed);
    if(m_bIsUseHeightMap == true)
    {
        vPreComputeForce.y = _Get_HeightForPosition(vPreComputeForce);
    }
    return vPreComputeForce;
}

glm::vec3 CNavigationHelper::Get_MoveRightForceOffset(void)
{
    glm::vec3 vPreComputeForce = glm::vec3(sinf(-m_vCurrentRotation.y) * m_fStrafeSpeed, 0.0f, cosf(-m_vCurrentRotation.y) * m_fStrafeSpeed);
    if(m_bIsUseHeightMap == true)
    {
        vPreComputeForce.y = _Get_HeightForPosition(vPreComputeForce);
    }
    return vPreComputeForce;
}




