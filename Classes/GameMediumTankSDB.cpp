//
//  GameMediumTankSDB.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameMediumTankSDB.h"

GameMediumTankSDB::GameMediumTankSDB(void)
{
    InitWithDefaultStats();
}

GameMediumTankSDB::~GameMediumTankSDB(void)
{
    
}

void GameMediumTankSDB::InitWithDefaultStats(void)
{
    m_fShootSpeed = 2000;
    m_fMoveSpeed = 7.5;
    m_fSteerSpeed = 2.0f;
    m_fHealth = 180;
    m_fDamage = 30;
}

void GameMediumTankSDB::SerializeData(void *_pData)
{
    
}

void GameMediumTankSDB::DeserializeData(void *_pData)
{
    
}