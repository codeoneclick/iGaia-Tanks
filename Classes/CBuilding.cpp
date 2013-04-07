//
//  CBuilding.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 4/6/13.
//
//

#include "CBuilding.h"

CBuilding::CBuilding(void)
{
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

CBuilding::~CBuilding(void)
{
    
}

void CBuilding::Load(IRoot *_root, SBuildingSettings *_settings)
{
    assert(_settings != nullptr);
    m_shape3d = _root->CreateShape3d(_settings->m_shapeSettingsFilename);
    assert(m_shape3d != nullptr);
    _root->InsertShape3d(m_shape3d);
    m_shape3d->Set_Position(m_position);
    m_shape3d->Set_Rotation(m_rotation);
}

void CBuilding::Set_Position(const glm::vec3 &_position)
{
    assert(m_box2dBody != nullptr);
    m_box2dBody->SetTransform(b2Vec2(_position.x, _position.z), m_box2dBody->GetAngle());
}

void CBuilding::Set_Rotation(const glm::vec3 &_rotation)
{
    assert(m_shape3d != nullptr);
    m_rotation = _rotation;
    m_shape3d->Set_Rotation(m_rotation);
}

void CBuilding::OnBox2dCollide(CCollisionCallback_INTERFACE* _collider)
{
    
}

void CBuilding::OnBox2dPositionChanged(const glm::vec3& _position)
{
    assert(m_shape3d != nullptr);
    m_position = _position;
    m_shape3d->Set_Position(m_position);
}

void CBuilding::OnBox2dRotationChanged(f32 _angle)
{
    
}

glm::vec3 CBuilding::Get_Box2dCenter(void)
{
    return m_position;
}

glm::vec3 CBuilding::Get_Box2dMaxBound(void)
{
    assert(m_shape3d != nullptr);
    return m_shape3d->Get_MaxBound();
}

glm::vec3 CBuilding::Get_Box2dMinBound(void)
{
    assert(m_shape3d != nullptr);
    return m_shape3d->Get_MinBound();
}

