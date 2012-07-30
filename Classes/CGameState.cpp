//
//  CGameState.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameState.h"

CGameState* CGameState::m_pInstance = NULL;

CGameState::CGameState(void)
{
    m_eWorldState = E_GAME_WORLD_STATE_NONE;
}

CGameState::~CGameState(void)
{
    
}

CGameState* CGameState::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CGameState();
    }
    return m_pInstance;
}