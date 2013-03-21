//
//  ITankBody.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CTankBody.h"

CTankBody::CTankBody(void)
{
    m_bodyPrefab = nullptr;
}

CTankBody::~CTankBody(void)
{

}

void CTankBody::Load(IRoot* _root, ITankSettings* _settings)
{
    STankBodySettings* settings = static_cast<STankBodySettings*>(_settings);
    assert(settings != nullptr);
    m_bodyPrefab = _root->CreateShape3d(settings->m_tankBodyFilename);
    _root->InsertShape3d(m_bodyPrefab);
    m_bodyPrefab->Set_Position(m_position);
    m_bodyPrefab->Set_Rotation(m_rotation);
}

void CTankBody::Set_Position(const glm::vec3& _position)
{
    assert(m_bodyPrefab != nullptr);
    m_bodyPrefab->Set_Position(_position);
    m_position = _position;
}

void CTankBody::Set_Rotation(const glm::vec3& _rotation)
{
    assert(m_bodyPrefab != nullptr);
    m_bodyPrefab->Set_Rotation(_rotation);
    m_rotation = _rotation;
}


