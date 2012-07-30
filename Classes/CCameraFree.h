//
//  CCameraFree.h
//  iGaia
//
//  Created by sergey.sergeev on 12/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CCameraFree_h
#define iGaia_CCameraFree_h

#include "ICamera.h"

class CCameraFree : public ICamera
{
protected:
    float m_fMoveSpeed;
    void MoveForward(void);
    void MoveBackward(void);
    void MoveRight(void);
    void MoveLeft(void);
    
public:
    CCameraFree(void);
    ~CCameraFree(void);
    virtual void Update(void);
    virtual void OnScreenMove(glm::vec2 _vMoveDirection);
    void Set_MoveSpeed(float _fMoveSpeed) { m_fMoveSpeed = _fMoveSpeed; } 
    virtual glm::vec3 Get_Position() { return m_vPosition; }
    virtual void Set_Position(const glm::vec3& _vPosition) { }
    
};


#endif
