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
#include "CRoot.h"
#include "CCharacterController.h"
#include "CGameSettingsMgr.h"
#include "CBuilding.h"

class CGameMainMenuScene
{
private:

    CGameSettingsMgr* m_gameSettingsMgr;

protected:

    CCamera* m_camera;
    CLight* m_light;
    CBuilding* m_buildingQuest;
    CParticleEmitter* m_particleEmitter;
    CLandscape* m_landscape;
    COcean* m_ocean;
    CCharacterController* m_characterController;

public:

    CGameMainMenuScene(void);
    ~CGameMainMenuScene(void);

	void Load(IRoot* _root);

    inline CCharacterController* Get_CharacterController(void)
    {
        assert(m_characterController != nullptr);
        return m_characterController;
    };
};

#endif 
