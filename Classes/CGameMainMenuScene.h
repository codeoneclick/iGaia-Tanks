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
#include "CCharacterController.h"

class CGameMainMenuScene
{
private:

protected:

    CCamera* m_camera;
    CLight* m_light;
    CShape3d* m_shape3d;
    CParticleEmitter* m_particleEmitter;
    CLandscape* m_landscape;
    COcean* m_ocean;
    CCharacterController* m_characterController;

public:

    CGameMainMenuScene(void);
    ~CGameMainMenuScene(void);

    void Load(CRoot_iOS* _root);

    inline CCharacterController* Get_CharacterController(void)
    {
        assert(m_characterController != nullptr);
        return m_characterController;
    };
};

#endif 
