//
//  CGame.cpp
//  iGaia
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGame.h"
#include "CInput.h"
#include "CResourceMgr.h"
#include "CGameSceneMgr.h"
#include "CGameUIMgr.h"
#include "CGameInGameScene.h"
#include "CGameMainMenuScene.h"
#include "GameNativeCommunicationMgr.h"

CGame* CGame::m_game = NULL;

CGame::CGame(void)
{

}

CGame::~CGame(void)
{
    
}

CGame* CGame::Instance(void)
{
    if(m_game == NULL)
    {
        m_game = new CGame();
    }
    return m_game;
}

void CGame::Load(void)
{
    
#ifdef OS_IPHONE
    CGameMainMenuScene* pScene = new CGameMainMenuScene();
#else
	CGameInGameScene* pScene = new CGameInGameScene();
#endif
    CGameSceneMgr::Instance()->Set_Scene(pScene);
    pScene->Load();
#ifdef OS_IPHONE
    CGameUIMgr::Instance()->Set_GameUI("main_menu_ui");
    GameNativeCommunicationMgr::Instance()->CreateGameServer();
    GameNativeCommunicationMgr::Instance()->ConnectToGameServer();
#endif
}

void CGame::Update(void)
{
    GameNativeCommunicationMgr::Instance()->Update();
    CGameSceneMgr::Instance()->Update();
    CResourceMgr::Instance()->Update();
    CSceneMgr::Instance()->Update();
}

void CGame::Render(void)
{
    CSceneMgr::Instance()->Render();
}










