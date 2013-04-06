//
//  CMoveGamepadView.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#include "CMoveGamepadView.h"

CMoveGamepadView::CMoveGamepadView(void)
{
    
}

CMoveGamepadView::~CMoveGamepadView(void)
{
    
}

void CMoveGamepadView::OnUIEventPerform(const std::string &_command, i32 _x, i32 _y)
{
    std::cout<<_command<<std::endl;
    std::cout<<"x: "<<_x<<" y: "<<_y<<std::endl;
    
    if(_command == "arrow_top_touch_down")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_SOUTH);
    }
    else if(_command == "arrow_top_touch_up")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_NONE);
    }
    else if(_command == "arrow_bottom_touch_down")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_NORTH);
    }
    else if(_command == "arrow_bottom_touch_up")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_NONE);
    }
    else if(_command == "arrow_left_touch_down")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_EAST);
    }
    else if(_command == "arrow_left_touch_up")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_NONE);
    }
    else if(_command == "arrow_right_touch_down")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_WEST);
    }
    else if(_command == "arrow_right_touch_up")
    {
        InvokeCallback(E_MOVE_CONTROLLER_DIRECTION_NONE);
    }
}

void CMoveGamepadView::AddEventListener(CMoveControllerCallback_INTERFACE* _listener)
{
    m_listeners.insert(_listener);
}

void CMoveGamepadView::RemoveEventListener(CMoveControllerCallback_INTERFACE* _listener)
{
    m_listeners.erase(_listener);
}

void CMoveGamepadView::InvokeCallback(E_MOVE_CONTROLLER_DIRECTION _direction)
{
    for (std::set<CMoveControllerCallback_INTERFACE*>::iterator iterator = m_listeners.begin(); iterator != m_listeners.end(); ++iterator)
    {
        CMoveControllerCallback_INTERFACE* listener = *iterator;
        listener->Get_Commands()->DispatchMoveControllerDidUpdate(_direction);
    }
}
