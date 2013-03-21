//
//  ITankTower.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CTankTower.h"

CTankTower::CTankTower(void)
{
    m_towerPrefab = nullptr;
}

CTankTower::~CTankTower(void)
{

}

void CTankTower::Load(IRoot* _root, ITankSettings* _settings)
{
    STankTowerSettings* settings  = static_cast<STankTowerSettings*>(_settings);
    assert(settings != nullptr);
    m_towerPrefab = _root->CreateShape3d(settings->m_tankTowerFilename);
    _root->InsertShape3d(m_towerPrefab);
    m_towerPrefab->Set_Position(m_position);
    m_towerPrefab->Set_Rotation(m_rotation);
}

void CTankTower::Set_Position(const glm::vec3& _position)
{
    assert(m_towerPrefab != nullptr);
    m_towerPrefab->Set_Position(_position);
    m_position = _position;
}

void CTankTower::Set_Rotation(const glm::vec3& _rotation)
{
    assert(m_towerPrefab != nullptr);
    m_towerPrefab->Set_Rotation(_rotation);
    m_rotation = _rotation;
}
