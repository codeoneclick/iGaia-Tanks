//
//  CCollisionCallback.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/25/13.
//
//

#include "CCollisionCallback.h"

CCollisionCallback::CCollisionCallback(void)
{
    m_collisionCallback = nullptr;
    m_positionChangedCallback = nullptr;
    m_rotationChangedCallback = nullptr;
    m_retriveCenterCallback = nullptr;
    m_retriveMaxboundCallback = nullptr;
    m_retriveMinboundCallback = nullptr;
}

void CCollisionCallback::ConnectCollisionListener(const __BOX2D_OBJECT_DID_COLLIDE& _listener)
{
    assert(_listener != nullptr);
    m_collisionCallback = _listener;
}

void CCollisionCallback::ConnectPositionChangedListener(const __BOX2D_OBJECT_DID_CHANGE_POSITION& _listener)
{
    assert(_listener != nullptr);
    m_positionChangedCallback = _listener;
}

void CCollisionCallback::ConnectRotationChangedListener(const __BOX2D_OBJECT_DID_CHANGE_ROTATION& _listener)
{
    assert(_listener != nullptr);
    m_rotationChangedCallback = _listener;
}

void CCollisionCallback::ConnectRetriveCenterListener(const __BOX2D_OBJECT_DID_RETRIVE_CENTER& _listener)
{
    assert(_listener != nullptr);
    m_retriveCenterCallback = _listener;
}

void CCollisionCallback::ConnectRetriveMaxboundListener(const __BOX2D_OBJECT_DID_RETRIVE_MAXBOUND& _listener)
{
    assert(_listener != nullptr);
    m_retriveMaxboundCallback = _listener;
}

void CCollisionCallback::ConnectRetriveMinboundListener(const __BOX2D_OBJECT_DID_RETRIVE_MINBOUND& _listener)
{
    assert(_listener != nullptr);
    m_retriveMinboundCallback = _listener;
}

void CCollisionCallback::DispatchDidCollide(CCollisionCallback_INTERFACE* _collider)
{
    assert(m_collisionCallback != nullptr);
    m_collisionCallback(_collider);
}

void CCollisionCallback::DispatchPositionDidChange(const glm::vec3& _position)
{
    assert(m_positionChangedCallback != nullptr);
    m_positionChangedCallback(_position);
}

void CCollisionCallback::DispatchRotationDidChange(f32 _angle)
{
    assert(m_rotationChangedCallback != nullptr);
    m_rotationChangedCallback(_angle);
}

glm::vec3 CCollisionCallback::DispatchCenterDidRetrive(void)
{
    assert(m_retriveCenterCallback != nullptr);
    return m_retriveCenterCallback();
}

glm::vec3 CCollisionCallback::DispatchMaxboundDidRetrive(void)
{
    assert(m_retriveMaxboundCallback != nullptr);
    return m_retriveMaxboundCallback();
}

glm::vec3 CCollisionCallback::DispatchMinboundDidRetrive(void)
{
    assert(m_retriveMinboundCallback != nullptr);
    return m_retriveMinboundCallback();
}

CCollisionCallback_INTERFACE::CCollisionCallback_INTERFACE(void)
{
    ConnectCallbacks();
}

void CCollisionCallback_INTERFACE::ConnectCallbacks(void)
{
    m_callbacks.ConnectCollisionListener(std::bind(&CCollisionCallback_INTERFACE::OnBox2dCollide, this, std::placeholders::_1));
    m_callbacks.ConnectPositionChangedListener(std::bind(&CCollisionCallback_INTERFACE::OnBox2dPositionChanged, this, std::placeholders::_1));
    m_callbacks.ConnectRotationChangedListener(std::bind(&CCollisionCallback_INTERFACE::OnBox2dRotationChanged, this, std::placeholders::_1));
    m_callbacks.ConnectRetriveCenterListener(std::bind(&CCollisionCallback_INTERFACE::Get_Box2dCenter, this));
    m_callbacks.ConnectRetriveMaxboundListener(std::bind(&CCollisionCallback_INTERFACE::Get_Box2dMaxBound, this));
    m_callbacks.ConnectRetriveMinboundListener(std::bind(&CCollisionCallback_INTERFACE::Get_Box2dMinBound, this));
}




