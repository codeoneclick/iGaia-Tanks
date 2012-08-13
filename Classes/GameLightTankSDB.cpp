//
//  GameLightTankSDB.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameLightTankSDB.h"

GameLightTankSDB::GameLightTankSDB(void)
{
    InitWithDefaultStats();
}

GameLightTankSDB::~GameLightTankSDB(void)
{
    
}

void GameLightTankSDB::InitWithDefaultStats(void)
{
    m_fShootSpeed = 1500;
    m_fMoveSpeed = 10;
    m_fSteerSpeed = 3.0f;
    m_fHealth = 100;
    m_fDamage = 15;
}

void GameLightTankSDB::SerializeData(void *_pData)
{
    
}

void GameLightTankSDB::DeserializeData(void *_pData)
{
    
}