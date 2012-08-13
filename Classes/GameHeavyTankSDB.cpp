//
//  GameHeavyTankSDB.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameHeavyTankSDB.h"

GameHeavyTankSDB::GameHeavyTankSDB(void)
{
    InitWithDefaultStats();
}

GameHeavyTankSDB::~GameHeavyTankSDB(void)
{
    
}

void GameHeavyTankSDB::InitWithDefaultStats(void)
{
    m_fShootSpeed = 2500;
    m_fMoveSpeed = 5.0f;
    m_fSteerSpeed = 1.0f;
    m_fHealth = 300;
    m_fDamage = 45;
}

void GameHeavyTankSDB::SerializeData(void *_pData)
{
    
}

void GameHeavyTankSDB::DeserializeData(void *_pData)
{
    
}