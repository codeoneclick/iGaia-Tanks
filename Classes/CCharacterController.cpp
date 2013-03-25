//
//  CCharacterController.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#include "CCharacterController.h"

CCharacterController::CCharacterController(void)
{
    m_camera = nullptr;
    m_character = nullptr;
    m_moveDirection = E_MOVE_CONTROLLER_DIRECTION_NONE;
    m_rotateDirection = E_ROTATE_CONTROLLER_DIRECTION_NONE;
	m_navigator = nullptr;

    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

CCharacterController::~CCharacterController(void)
{

}

glm::vec3 CCharacterController::SmoothRotation(const glm::vec3& _oldRotation, const glm::vec3& _newRotation)
{
    return glm::mix(_oldRotation, _newRotation, 0.5f);
}

void CCharacterController::OnMoveControllerUpdate(ui32 _direction)
{
    m_moveDirection = static_cast<E_MOVE_CONTROLLER_DIRECTION>(_direction);
}

void CCharacterController::OnRotateControllerUpdate(ui32 _direction)
{
    m_rotateDirection = static_cast<E_ROTATE_CONTROLLER_DIRECTION>(_direction);
}

void CCharacterController::OnUpdate(f32 _deltatime)
{
	assert(m_navigator != nullptr);

    switch(m_moveDirection)
    {
        case E_MOVE_CONTROLLER_DIRECTION_NONE:
        {

        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_NORTH:
        {
            m_navigator->MoveBackward();

        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_SOUTH:
        {
            m_navigator->MoveForward();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_WEST:
        {
            m_navigator->SteerRight();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_EAST:
        {
            m_navigator->SteerLeft();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_NORTH_WEST:
        {
            m_navigator->MoveBackward();
            m_navigator->SteerRight();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_NORTH_EAST:
        {
            m_navigator->MoveBackward();
            m_navigator->SteerLeft();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_SOUTH_WEST:
        {
            m_navigator->MoveForward();
            m_navigator->SteerRight();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_SOUTH_EAST:
        {
            m_navigator->MoveForward();
            m_navigator->SteerLeft();
        }
            break;
    }

    switch (m_rotateDirection)
    {
        case E_ROTATE_CONTROLLER_DIRECTION_NONE:
        {
            
        }
            break;
        case E_ROTATE_CONTROLLER_DIRECTION_LEFT:
        {
            m_navigator->SteerLeft();
        }
            break;
        case E_ROTATE_CONTROLLER_DIRECTION_RIGHT:
        {
            m_navigator->SteerRight();
        }
            break;
    }

    m_position = m_navigator->Get_Position();
    m_rotation = m_navigator->Get_Rotation();

    assert(m_camera != nullptr);
    m_camera->Set_LookAt(m_position);
    m_camera->Set_Rotation(m_rotation.y);

    assert(m_shadow != nullptr);
    m_shadow->Set_Position(m_position);
    glm::vec3 shadowRotation = glm::degrees(m_rotation);
    shadowRotation.y += 90.0f;
    m_shadow->Set_Rotation(shadowRotation);

    assert(m_character != nullptr);
    m_character->Set_Position(m_position);
    glm::vec3 oldCharacterRotation = m_character->Get_Rotation();
    glm::vec3 newCharacterRotation = glm::degrees(m_rotation);
    newCharacterRotation.y += 90.0f;
    m_character->Set_Rotation(SmoothRotation(oldCharacterRotation, newCharacterRotation));
}


