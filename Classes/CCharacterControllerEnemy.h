//
//  CCharacterControllerEnemy.h
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CCharacterControllerEnemy__
#define __iGaia__CCharacterControllerEnemy__

#include <iostream>
#include "ICharacterController.h"
#include "CTimer.h"

#define k_AI_SHOOT_INTERVAL 2000
#define k_AI_SHOOT_DISTANCE 10.0f

class CCharacterControllerEnemy : public ICharacterController
{
public:
    enum E_AI_STATE { E_AI_STATE_NONE = 0, E_AI_STATE_STAND, E_AI_STATE_MOVE, E_AI_STATE_CHASE, E_AI_STATE_CHASE_ATTACK, E_AI_STATE_BACK, E_AI_STATE_BACK_ATTACK };
    enum E_AI_STEER_MODE { E_AI_STEER_MODE_NONE = 0, E_AI_STEER_MODE_LEFT, E_AI_STEER_MODE_RIGHT };
protected:
    E_AI_STATE m_eState;
    E_AI_STEER_MODE m_eStreerMode;
    
    int m_iAIStateDuration;
    int m_iAIStateTimeStamp;
    int m_iAIShootTimeStamp;
    
    glm::vec3 m_vMovePoint;
    glm::vec3 m_vMoveDirection;
    
    long _Get_TimeStamp(void);
    bool _IsStateTimeElapsed(void);
    
public:
    CCharacterControllerEnemy(void);
    ~CCharacterControllerEnemy(void);
    
    void Load(void);
    void Update(void);
    
    void Shoot(void);
    
    INode* Get_TargetForCamera(void) { return m_pChassis->Get_BasisNode(); }
    
    void Set_AIState(E_AI_STATE _eState, long _iAIStateDuration);
    E_AI_STATE Get_AIState(void) { return m_eState; }
    
    void Set_AIMovePoint(glm::vec3 _vPoint) { m_vMovePoint = _vPoint; }
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__CCharaterControllerEnemy__) */
