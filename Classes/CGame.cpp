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
    //CGameInGameScene* pScene = new CGameInGameScene();
    CGameMainMenuScene* pScene = new CGameMainMenuScene();
    CGameSceneMgr::Instance()->Set_Scene(pScene);
    pScene->Load();
    CGameUIMgr::Instance()->Set_GameUI("main_menu_ui");
}

void CGame::Update(void)
{
    CGameSceneMgr::Instance()->Update();
    CResourceMgr::Instance()->Update();
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    //if(pScene != NULL)
    //{
        CSceneMgr::Instance()->Update();
    //}
}

void CGame::Render(void)
{
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    //if(pScene != NULL)
    //{
       CSceneMgr::Instance()->Render();
    //}
}










