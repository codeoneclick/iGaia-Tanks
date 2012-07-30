//
//  CInput.h
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CInput_h
#define iGaia_CInput_h

#include <glm/glm.hpp>

class CInput
{
public:
    enum E_STATE 
    { 
        E_STATE_TOUCH = 0, 
        E_STATE_UNTOUCH, 
        E_STATE_MOVE 
    };
protected:
    static CInput* m_pInstance;
    E_STATE m_eState;
    glm::vec2 m_vStartTouchPoint;
    glm::vec2 m_vEndTouchPoint;
public:
    CInput();
    ~CInput();
    static CInput* Instance();
    void Set_State(E_STATE _eState, glm::vec2 _vTouchPoint);
    glm::vec2 Get_TouchPoint(void) { return m_vStartTouchPoint; }
};

#endif
