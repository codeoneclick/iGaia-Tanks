//
//  GameUserSDB.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameUserSDB.h"

GameUserSDB::GameUserSDB(void)
{
    InitWithDefaultStats();
}

GameUserSDB::~GameUserSDB(void)
{
    
}

void GameUserSDB::InitWithDefaultStats(void)
{
    m_fHeavySkill = 1;
    m_fLightSkill = 1;
    m_fMediumSkill = 1;
}

void GameUserSDB::SerializeData(void *_pData)
{
    
}

void GameUserSDB::DeserializeData(void *_pData)
{
    
}