//
//  CGameMainMenuScene.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#ifndef CGameMainMenuScene_h
#define CGameMainMenuScene_h

#include "HCommon.h"
#include "CRoot_iOS.h"

class CGameMainMenuScene
{
private:

protected:

    CCamera* m_camera;
    CLight* m_light;
    CShape3d* m_shape3d;
    CLandscape* m_landscape;

public:

    CGameMainMenuScene(void);
    ~CGameMainMenuScene(void);

    void Load(CRoot_iOS* _root);

};

#endif 
