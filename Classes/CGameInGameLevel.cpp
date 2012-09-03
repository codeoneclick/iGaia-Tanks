//
//  CGameInGameLevel.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameInGameLevel.h"
#include "CSceneMgr.h"
#include "CLandscapeEdges.h"

CGameInGameLevel::CGameInGameLevel(void)
{

}

CGameInGameLevel::~CGameInGameLevel(void)
{
    
}

void CGameInGameLevel::Load(void)
{
    CSceneMgr::Instance()->LoadEnvironment("environment");
    
    CBuilding* pBuilding = new CBuilding();
    pBuilding->Load("building_06.mdl", "building.pvr");
    pBuilding->Set_Position(glm::vec3(12.0f, 0.0f, 12.0f));
    m_lBuildings.push_back(pBuilding);
    
    pBuilding = new CBuilding();
    pBuilding->Load("building_04.mdl", "building.pvr");
    pBuilding->Set_Position(glm::vec3(28.0f, 0.0f, 12.0f));
    m_lBuildings.push_back(pBuilding);
    
    pBuilding = new CBuilding();
    pBuilding->Load("building_05.mdl", "building.pvr");
    pBuilding->Set_Position(glm::vec3(12.0f, 0.0f, 28.0f));
    m_lBuildings.push_back(pBuilding);
}

void CGameInGameLevel::Unload(void)
{
    IGameLevel::Unload();
    CSceneMgr::Instance()->UnloadEnvironment();
}

void CGameInGameLevel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{

}

void CGameInGameLevel::Update(void)
{
    IGameLevel::Update();
}



