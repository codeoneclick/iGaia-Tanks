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
    m_moveDirection = E_MOVE_CONTROLLER_DIRECTION_NONE;
    m_rotateDirection = E_ROTATE_CONTROLLER_DIRECTION_NONE;
    m_navigator = new CNavigator(0.75f, 0.75f, 0.75f, 0.066f);

    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    m_navigator->Set_Position(m_position);
    m_navigator->Set_Rotation(m_rotation);
}

CCharacterController::~CCharacterController(void)
{

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
            m_navigator->MoveRight();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_EAST:
        {
            m_navigator->MoveLeft();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_NORTH_WEST:
        {
            m_navigator->MoveBackward();
            m_navigator->MoveRight();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_NORTH_EAST:
        {
            m_navigator->MoveBackward();
            m_navigator->MoveLeft();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_SOUTH_WEST:
        {
            m_navigator->MoveForward();
            m_navigator->MoveRight();
        }
            break;
        case E_MOVE_CONTROLLER_DIRECTION_SOUTH_EAST:
        {
            m_navigator->MoveForward();
            m_navigator->MoveLeft();
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
}


