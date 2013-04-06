//
//  CCollisionNavigator.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/25/13.
//
//

#include "CCollisionNavigator.h"

CCollisionNavigator::CCollisionNavigator(f32 _moveForwardSpeed,
                                         f32 _moveBackwardSpeed,
                                         f32 _strafeSpeed,
                                         f32 _steerSpeed,
                                         f32* _heightmapData,
                                         ui32 _heightmapWidth,
                                         ui32 _heightmapHeight,
                                         const glm::vec3& _maxBound,
                                         const glm::vec3& _minBound)
{
    m_moveForwardSpeed = _moveForwardSpeed;
    m_moveBackwardSpeed = _moveBackwardSpeed;
    m_strafeSpeed = _strafeSpeed;
    m_steerSpeed = _steerSpeed;
    
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    
    assert(_heightmapData != nullptr);
    assert(_heightmapHeight != 0);
    assert(_heightmapWidth != 0);
    m_heightmapData = _heightmapData;
    m_heightmapWidth = _heightmapWidth;
    m_heightmapHeight = _heightmapHeight;
    
    m_maxBound = _maxBound;
    m_minBound = _minBound;
}

CCollisionNavigator::~CCollisionNavigator(void)
{
    
}

void CCollisionNavigator::OnBox2dCollide(CCollisionCallback_INTERFACE* _collider)
{
    
}

void CCollisionNavigator::OnBox2dPositionChanged(const glm::vec3& _position)
{
    Set_Position(_position);
}

void CCollisionNavigator::OnBox2dRotationChanged(f32 _angle)
{
    m_rotation.y = _angle;
    Set_Rotation(m_rotation);
}

glm::vec3 CCollisionNavigator::Get_Box2dCenter(void)
{
    return m_position;
}

glm::vec3 CCollisionNavigator::Get_Box2dMaxBound(void)
{
    return m_maxBound;
}

glm::vec3 CCollisionNavigator::Get_Box2dMinBound(void)
{
    return m_minBound;
}
