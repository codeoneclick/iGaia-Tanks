//
//  CInput.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CInput.h"
#include "CWindow.h"
#include "CSceneMgr.h"

CInput* CInput::m_pInstance = NULL;

CInput::CInput()
{
    m_eState = E_STATE_UNTOUCH;
    m_vStartTouchPoint = glm::vec2(0.0f, 0.0f);
    m_vEndTouchPoint = glm::vec2(0.0f, 0.0f);
}

CInput::~CInput()
{
    
}

CInput* CInput::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CInput();
    }
    
    return m_pInstance;
}

void CInput::Set_State(CInput::E_STATE _eState, glm::vec2 _vTouchPoint)
{
    switch (_eState)
    {
        case E_STATE_UNTOUCH:
            if(m_eState == E_STATE_MOVE)
            {

            }
            else
            {
                CSceneMgr::Instance()->Get_CollisionMgr()->OnScreenTouch(m_vStartTouchPoint);
            }
            break;
        case E_STATE_TOUCH:
        {
            m_vStartTouchPoint = _vTouchPoint;
            m_vEndTouchPoint = _vTouchPoint;
            m_vStartTouchPoint.y = CWindow::Get_ScreenWidth() - m_vStartTouchPoint.y;
        }
            break;
        case E_STATE_MOVE:
        {
            //glm::vec2 vDeltaMove = m_vEndTouchPoint - _vTouchPoint;
            m_vEndTouchPoint = _vTouchPoint;
            //CSceneMgr::Instance()->Get_Camera()->OnScreenMove(vDeltaMove);
        }
            break;
        default:
            break;
    }
    m_eState = _eState;
}







