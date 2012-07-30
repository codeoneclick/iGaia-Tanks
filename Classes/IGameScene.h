//
//  IGameScene.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__IGameScene__
#define __iGaia__IGameScene__

#include "CGameCharaterControllerMgr.h"
#include "CGameAIMgr.h"
#include "IGameLevel.h"
#include "CSceneMgr.h"
#include "CCharacterControllerPlayer.h"
#include "CGameShooterMgr.h"

class IGameScene
{
protected:
    CGameCharaterControllerMgr* m_pCharaterControllerMgr;
    CGameShooterMgr* m_pGameShooterMgr;
    CGameAIMgr* m_pGameAIMgr;
    IGameLevel* m_pLevel;
    ICharacterController* m_pMainCharacterController;
    ICamera* m_pCamera;
    ILight* m_pLight;
public:
    IGameScene(void);
    virtual ~IGameScene(void);
    IGameLevel* Get_Level(void) { return m_pLevel; }
    CGameCharaterControllerMgr* Get_GameCharaterControllerMgr(void) { return m_pCharaterControllerMgr; }
    CGameAIMgr* Get_GameAIMgr(void) { return m_pGameAIMgr; }
    CGameShooterMgr* Get_GameShooterMgr(void) { return m_pGameShooterMgr; }
    ICharacterController* Get_MainCharacterController(void) { return m_pMainCharacterController; }
    virtual void Load(void);
    virtual void Unload(void);
    virtual void Update(void);
};

#endif /* defined(__iGaia__IGameScene__) */
