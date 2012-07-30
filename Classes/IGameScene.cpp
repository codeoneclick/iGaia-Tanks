//
//  IGameScene.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#include "IGameScene.h"
#include "CMathHelper.h"


IGameScene::IGameScene(void)
{
    m_pCharaterControllerMgr = NULL;
    m_pMainCharacterController = NULL;
    m_pGameAIMgr = NULL;
    m_pGameShooterMgr = NULL;
}

IGameScene::~IGameScene(void)
{
    
}

void IGameScene::Load(void)
{
    m_pCharaterControllerMgr = new CGameCharaterControllerMgr();
    m_pGameAIMgr = new CGameAIMgr();
    m_pGameShooterMgr = new CGameShooterMgr();
}

void IGameScene::Unload(void)
{
    SAFE_DELETE(m_pGameAIMgr);
    SAFE_DELETE(m_pCharaterControllerMgr);
    m_pMainCharacterController = NULL;
    SAFE_DELETE(m_pGameShooterMgr);
    m_pLevel->Unload();
    SAFE_DELETE(m_pLevel);
    CSceneMgr::Instance()->Remove_Camera(m_pCamera);
}

void IGameScene::Update(void)
{
    if(m_pCharaterControllerMgr != NULL)
    {
        m_pCharaterControllerMgr->Update();
    }
    if(m_pGameShooterMgr != NULL)
    {
        m_pGameShooterMgr->Update();
    }
    if(m_pGameAIMgr != NULL)
    {
        m_pGameAIMgr->Update();
    }
    if(m_pLevel != NULL)
    {
        m_pLevel->Update();
    }
}



