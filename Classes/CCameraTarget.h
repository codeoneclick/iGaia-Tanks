//
//  CCameraTarget.h
//  iGaia
//
//  Created by sergey.sergeev on 12/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CCameraTarget_h
#define iGaia_CCameraTarget_h

#include "ICamera.h"
#include "INode.h"
#include "ICharacterController.h"

class CCameraTarget : public ICamera
{ 
protected:
    ICharacterController* m_pTarget;
public:
    CCameraTarget(void);
    ~CCameraTarget();
    virtual void Update(void);
    virtual void OnScreenMove(glm::vec2 _vMoveDirection);
    void Set_Target(ICharacterController* _pTarget) { m_pTarget = _pTarget; }
    ICharacterController* Get_Target(void) { return m_pTarget; }
};

#endif
