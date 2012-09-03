//
//  CGameMainMenuLevel.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#include "CGameMainMenuLevel.h"
#include "CSceneMgr.h"
#include "CLandscapeEdges.h"

CGameMainMenuLevel::CGameMainMenuLevel(void)
{
    
}

CGameMainMenuLevel::~CGameMainMenuLevel(void)
{
    
}

void CGameMainMenuLevel::Load(void)
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

void CGameMainMenuLevel::Unload(void)
{
    IGameLevel::Unload();
    CSceneMgr::Instance()->UnloadEnvironment();
}

void CGameMainMenuLevel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    
}

void CGameMainMenuLevel::Update(void)
{
    
}


