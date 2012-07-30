//
//  CGameInGameScene.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameInGameScene_h
#define iGaia_CGameInGameScene_h

#include "IGameScene.h"
#include "IGameLevel.h"

#define k_CAMERA_DISTANCE_MODE_1 7.0f
#define k_CAMERA_DISTANCE_MODE_2 7.0f
#define k_CAMERA_HEIGHT_MODE_1 4.0f
#define k_CAMERA_HEIGHT_MODE_2 14.0f
#define k_CAMERA_DISPLACE_INC 0.33f
#define k_CAMERA_HEIGHT_LERP_VALUE 0.01f
#define k_CAMERA_HEIGHT_OUT_MAP 5.0f
#define k_CAMERA_ROTATION_LERP 0.1f

class CGameInGameScene : public IGameScene
{
public:
    enum E_CAMERA_MODE { E_CAMERA_MODE_1 = 0, E_CAMERA_MODE_2 };
private:
    E_CAMERA_MODE m_eCameraMode;
    float m_fCurrentCameraHeight;
    float m_fNeedCameraHeight;
public:
    CGameInGameScene(void);
    ~CGameInGameScene(void);
    void SwitchCameraModeToNext(void);
    void SwitchCameraMode(E_CAMERA_MODE _eCameraMode);
    void Load(void);
    void Unload(void);
    void Update(void);
};

#endif
