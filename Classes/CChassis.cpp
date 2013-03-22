//
//  ITankTrack.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "CChassis.h"

CChassis::CChassis(void)
{
    m_leftChassisShape = nullptr;
    m_rightChassisShape = nullptr;
}

CChassis::~CChassis(void)
{

}

void CChassis::Load(IRoot* _root, IPanzerSpareSettings* _settings)
{
    SChassisSettings* settings  = static_cast<SChassisSettings*>(_settings);
    assert(settings != nullptr);
    m_leftChassisShape = _root->CreateShape3d(settings->m_leftChassisSettingsFilename);
    _root->InsertShape3d(m_leftChassisShape);
    m_leftChassisShape->Set_Position(m_position);
    m_leftChassisShape->Set_Rotation(m_rotation);

    m_rightChassisShape = _root->CreateShape3d(settings->m_rightChassisSettingsFilename);
    _root->InsertShape3d(m_rightChassisShape);
    m_rightChassisShape->Set_Position(m_position);
    m_rightChassisShape->Set_Rotation(m_rotation);
}

void CChassis::Set_Position(const glm::vec3& _position)
{
    assert(m_leftChassisShape != nullptr);
    assert(m_rightChassisShape != nullptr);
    
    m_leftChassisShape->Set_Position(_position);
    m_rightChassisShape->Set_Position(_position);
    
    m_position = _position;
}

void CChassis::Set_Rotation(const glm::vec3& _rotation)
{
    assert(m_leftChassisShape != nullptr);
    assert(m_rightChassisShape != nullptr);
    
    m_leftChassisShape->Set_Rotation(_rotation);
    m_rightChassisShape->Set_Rotation(_rotation);
    
    m_rotation = _rotation;
}



