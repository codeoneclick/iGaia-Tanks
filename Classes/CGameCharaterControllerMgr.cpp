//
//  CGameCharaterControllerMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameCharaterControllerMgr.h"
#include "CCharacterControllerPlayer.h"
#include "CCharacterControllerEnemy.h"

CGameCharaterControllerMgr::CGameCharaterControllerMgr(void)
{
    m_pCharacterControllerPlayer = NULL;
}

CGameCharaterControllerMgr::~CGameCharaterControllerMgr(void)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        SAFE_DELETE(m_lContainer[index]);
    }
    m_lContainer.clear();
    m_pCharacterControllerPlayer = NULL;
}

ICharacterController* CGameCharaterControllerMgr::Add_MainCharacterController(void)
{
    m_pCharacterControllerPlayer = new CCharacterControllerPlayer();
    m_pCharacterControllerPlayer->Load();
    m_lContainer.push_back(m_pCharacterControllerPlayer);
    return m_pCharacterControllerPlayer;
}

ICharacterController* CGameCharaterControllerMgr::Add_EnemyCharacterController(void)
{
    CCharacterControllerEnemy* pCharacterController = new CCharacterControllerEnemy();
    pCharacterController->Load();
    m_lContainer.push_back(pCharacterController);
    return pCharacterController;
}

void CGameCharaterControllerMgr::Remove_MainCharacterController(void)
{
    
}

void CGameCharaterControllerMgr::Remove_EnemyCharacterController(ICharacterController* _pCharacterController)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        if(m_lContainer[index] == _pCharacterController)
        {
            SAFE_DELETE(m_lContainer[index]);
            m_lContainer.erase(m_lContainer.begin() + index);
        }
    }
}

void CGameCharaterControllerMgr::Reset_MainCharacterController(void)
{
    
}

void CGameCharaterControllerMgr::Update(void)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        m_lContainer[index]->Update();
    }
}










