//
//  ITankBody.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CCarcass.h"

CCarcass::CCarcass(void)
{
    m_carcassShape = nullptr;
}

CCarcass::~CCarcass(void)
{

}

void CCarcass::Load(IRoot* _root, IPanzerSpareSettings* _settings)
{
    SCarcassSettings* settings = static_cast<SCarcassSettings*>(_settings);
    assert(settings != nullptr);
    m_carcassShape = _root->CreateShape3d(settings->m_carcassSettingsFilename);
    assert(m_carcassShape != nullptr);
    _root->InsertShape3d(m_carcassShape);
    m_carcassShape->Set_Position(m_position);
    m_carcassShape->Set_Rotation(m_rotation);
    m_carcassMaxBound = m_carcassShape->Get_MaxBound();
    m_carcassMinBound = m_carcassShape->Get_MinBound();
}

void CCarcass::Set_Position(const glm::vec3& _position)
{
    assert(m_carcassShape != nullptr);
    m_carcassShape->Set_Position(_position);
    m_position = _position;
}

void CCarcass::Set_Rotation(const glm::vec3& _rotation)
{
    assert(m_carcassShape != nullptr);
    m_carcassShape->Set_Rotation(_rotation);
    m_rotation = _rotation;
}