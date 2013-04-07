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

void CCollisionNavigator::Set_Position(const glm::vec3 &_position)
{
    assert(m_heightmapHeight != 0);
    assert(m_heightmapWidth != 0);
    
    if(!IsPrecomputedPositionValid(_position))
    {
        assert(false);
    }
    assert(m_box2dBody != nullptr);
    m_box2dBody->SetTransform(b2Vec2(_position.x, _position.z), m_box2dBody->GetAngle());
}

void CCollisionNavigator::OnBox2dCollide(CCollisionCallback_INTERFACE* _collider)
{
    
}

void CCollisionNavigator::OnBox2dPositionChanged(const glm::vec3& _position)
{
    CNavigator::Set_Position(_position);
}

void CCollisionNavigator::OnBox2dRotationChanged(f32 _angle)
{
    
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

bool CCollisionNavigator::MoveForward(void)
{
    b2Vec2 velocity = b2Vec2(0.0f, 0.0f);
    velocity.x += sinf(m_rotation.y) * m_moveForwardSpeed * 50.0f;
    velocity.y += cosf(m_rotation.y) * m_moveForwardSpeed * 50.0f;
    assert(m_box2dBody != nullptr);
    m_box2dBody->SetAwake(true);
    m_box2dBody->SetLinearVelocity(velocity);
    return true;
}

bool CCollisionNavigator::MoveBackward(void)
{
    b2Vec2 velocity = b2Vec2(0.0f, 0.0f);
    velocity.x -= sinf(m_rotation.y) * m_moveBackwardSpeed * 50.0f;
    velocity.y -= cosf(m_rotation.y) * m_moveBackwardSpeed * 50.0f;
    assert(m_box2dBody != nullptr);
    m_box2dBody->SetAwake(true);
    m_box2dBody->SetLinearVelocity(velocity);
    return true;
}

bool CCollisionNavigator::MoveLeft(void)
{
    glm::vec3 precomputePosition = glm::vec3(m_position.x - sinf(m_rotation.y) * m_strafeSpeed, 0.0f, m_position.z - cosf(m_rotation.y) * m_strafeSpeed);
    if(!IsPrecomputedPositionValid(precomputePosition))
    {
        return false;
    }
    Set_Position(precomputePosition);
    return true;
}

bool CCollisionNavigator::MoveRight(void)
{
    glm::vec3 precomputePosition = glm::vec3(m_position.x + sinf(m_rotation.y) * m_strafeSpeed, 0.0f, m_position.z + cosf(m_rotation.y) * m_strafeSpeed);
    if(!IsPrecomputedPositionValid(precomputePosition))
    {
        return false;
    }
    Set_Position(precomputePosition);
    return true;
}

