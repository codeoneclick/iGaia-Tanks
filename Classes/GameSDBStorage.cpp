//
//  GameSDBStorage.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameSDBStorage.h"

GameSDBStorage* GameSDBStorage::m_pInstance = NULL;

GameSDBStorage* GameSDBStorage::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new GameSDBStorage();
    }
    return m_pInstance;
}

GameSDBStorage::GameSDBStorage(void)
{
    m_pUserSDB = new GameUserSDB();
    m_pLightTankSDB = new GameLightTankSDB();
    m_pMediumTankSDB = new GameMediumTankSDB();
    m_pHeavyTankSDB = new GameHeavyTankSDB();
}

GameSDBStorage::~GameSDBStorage(void)
{
    
}

float GameSDBStorage::Get_UserMoveSpeed(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT:
        {
            return m_pLightTankSDB->Get_MoveSpeed();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_MEDIUM:
        {
            return m_pMediumTankSDB->Get_MoveSpeed();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_HEAVY:
        {
            return m_pHeavyTankSDB->Get_MoveSpeed();
        }
            break;
        default:
            break;
    }
    return 0;
}

float GameSDBStorage::Get_UserSteerSpeed(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT:
        {
            return m_pLightTankSDB->Get_SteerSpeed();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_MEDIUM:
        {
            return m_pMediumTankSDB->Get_SteerSpeed();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_HEAVY:
        {
            return m_pHeavyTankSDB->Get_SteerSpeed();
        }
            break;
        default:
            break;
    }
    return 0;
}

float GameSDBStorage::Get_UserShootSpeed(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT:
        {
            return m_pLightTankSDB->Get_ShootSpeed();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_MEDIUM:
        {
            return m_pMediumTankSDB->Get_ShootSpeed();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_HEAVY:
        {
            return m_pHeavyTankSDB->Get_ShootSpeed();
        }
            break;
        default:
            break;
    }
    return 0;
}

float GameSDBStorage::Get_UserHealth(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT:
        {
            m_pLightTankSDB->Get_Health();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_MEDIUM:
        {
            m_pMediumTankSDB->Get_Health();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_HEAVY:
        {
            m_pHeavyTankSDB->Get_Health();
        }
            break;
        default:
            break;
    }
    return 0;
}

float GameSDBStorage::Get_UserDamage(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT:
        {
            m_pLightTankSDB->Get_Damage();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_MEDIUM:
        {
            m_pMediumTankSDB->Get_Damage();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_HEAVY:
        {
            m_pHeavyTankSDB->Get_Damage();
        }
            break;
        default:
            break;
    }
    return 0;
}







