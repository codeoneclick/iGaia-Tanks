//
//  ITankTower.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CTurret.h"

CTurret::CTurret(void)
{
    m_turretShape = nullptr;
}

CTurret::~CTurret(void)
{

}

void CTurret::Load(IRoot* _root, IPanzerSpareSettings* _settings)
{
    STurretSettings* settings  = static_cast<STurretSettings*>(_settings);
    assert(settings != nullptr);
    m_turretShape = _root->CreateShape3d(settings->m_turretSettingsFilename);
    _root->InsertShape3d(m_turretShape);
    m_turretShape->Set_Position(m_position);
    m_turretShape->Set_Rotation(m_rotation);
}

void CTurret::Set_Position(const glm::vec3& _position)
{
    assert(m_turretShape != nullptr);
    m_turretShape->Set_Position(_position);
    m_position = _position;
}

void CTurret::Set_Rotation(const glm::vec3& _rotation)
{
    assert(m_turretShape != nullptr);
    m_turretShape->Set_Rotation(_rotation);
    m_rotation = _rotation;
}
