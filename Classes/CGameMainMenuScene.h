//
//  CGameMainMenuScene.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__CGameMainMenuScene__
#define __iGaia__CGameMainMenuScene__

#include "IGameScene.h"
#include "IGameLevel.h"

#define k_CAMERA_DISTANCE 7.0f
#define k_CAMERA_HEIGHT 7.0f
#define k_CAMERA_DISPLACE_INC 0.33f
#define k_CAMERA_HEIGHT_LERP_VALUE 0.01f
#define k_CAMERA_HEIGHT_OUT_MAP 5.0f
#define k_CAMERA_ROTATION_LERP 0.1f

class CGameMainMenuScene : public IGameScene
{
protected:
    float m_fCurrentCameraHeight;
    float m_fNeedCameraHeight;
public:
    CGameMainMenuScene(void);
    ~CGameMainMenuScene(void);
    void Load(void);
    void Unload(void);
    void Update(void);
};


#endif /* defined(__iGaia__CGameMainMenuScene__) */
