//
//  CCharacterControllerMain.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CCharacterControllerPlayer_h
#define iGaia_CCharacterControllerPlayer_h

#include "ICharacterController.h"
#include "CParticleEmitter.h"
#include "CSpriteCross.h"
#include "CDecal.h"

#define k_CAMERA_FOV_Y_STATE_NONE 45.0f
#define k_CAMERA_FOV_Y_STATE_FORWARD 50.0f
#define k_CAMERA_FOV_Y_STATE_BACKWARD 40.0f
#define k_CAMERA_FOV_Y_DELTA_STATE_NONE 0.66f
#define k_CAMERA_FOV_Y_DELTA_STATE_FORWARD 0.33f
#define k_CAMERA_FOV_Y_DELTA_STATE_BACKWARD 0.99f


class CCharacterControllerPlayer : public ICharacterController
{
protected:

public:
    CCharacterControllerPlayer(void);
    ~CCharacterControllerPlayer(void);
    
    void Load(void);
    void Update(void);
    
    INode* Get_TargetForCamera(void) { return m_pBody->Get_BasisNode(); }
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif
