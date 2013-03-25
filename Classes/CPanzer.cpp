//
//  CTank.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#include "CPanzer.h"

CPanzer::CPanzer(void)
{
    m_carcass = nullptr;
    m_chassis = nullptr;
    m_turret = nullptr;
}

CPanzer::~CPanzer(void)
{

}

void CPanzer::Load(IRoot *_root, SPanzerSettings *_settings)
{
    m_carcass = new CCarcass();
    m_carcass->Load(_root, &_settings->m_carcassSettings);

    m_chassis = new CChassis();
    m_chassis->Load(_root, &_settings->m_chassisSettings);

    m_turret = new CTurret();
    m_turret->Load(_root, &_settings->m_turretSettings);
}

void CPanzer::Set_Position(const glm::vec3 &_position)
{
    assert(m_carcass != nullptr);
    assert(m_chassis != nullptr);
    assert(m_turret != nullptr);

    m_carcass->Set_Position(_position);
    m_chassis->Set_Position(_position);
    m_turret->Set_Position(_position);

    m_position = _position;
}

void CPanzer::Set_Rotation(const glm::vec3 &_rotation)
{
    assert(m_carcass != nullptr);
    assert(m_chassis != nullptr);
    assert(m_turret != nullptr);

    m_carcass->Set_Rotation(_rotation);
    m_chassis->Set_Rotation(_rotation);
    m_turret->Set_Rotation(_rotation);

    m_rotation = _rotation;
}

void CPanzer::OnBox2dCollide(CCollisionCallback_INTERFACE* _collider)
{

}

void CPanzer::OnBox2dPositionChanged(const glm::vec3& _position)
{
    Set_Position(_position);
}

void CPanzer::OnBox2dRotationChanged(f32 _angle)
{
    m_rotation.y = _angle;
    Set_Rotation(m_rotation);
}

glm::vec3 CPanzer::Get_Box2dCenter(void)
{
    return m_position;
}

glm::vec3 CPanzer::Get_Box2dMaxBound(void)
{
    return m_carcass->Get_CarcassMaxBound();
}

glm::vec3 CPanzer::Get_Box2dMinBound(void)
{
    return m_carcass->Get_CarcassMinBound();
}

