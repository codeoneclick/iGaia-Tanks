//
//  GameSDBStorage.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameSDBStorage__
#define __iGaia__GameSDBStorage__

#include "GameUserSDB.h"
#include "GameLightTankSDB.h"
#include "GameMediumTankSDB.h"
#include "GameHeavyTankSDB.h"

class GameSDBStorage
{
public:
    
protected:
    GameUserSDB* m_pUserSDB;
    GameLightTankSDB* m_pLightTankSDB;
    GameMediumTankSDB* m_pMediumTankSDB;
    GameHeavyTankSDB* m_pHeavyTankSDB;
    static GameSDBStorage* m_pInstance;
public:
    GameSDBStorage(void);
    ~GameSDBStorage(void);
    static GameSDBStorage* Instance(void);
    inline GameUserSDB* Get_UserSDB(void) { return m_pUserSDB; }
    inline GameLightTankSDB* Get_LightTankSDB(void) { return m_pLightTankSDB; }
    inline GameMediumTankSDB* Get_MediumTankSDB(void) { return m_pMediumTankSDB; }
    inline GameHeavyTankSDB* Get_HeavyTankSBD(void) { return m_pHeavyTankSDB; }
    
    float Get_UserMoveSpeed(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType);
    float Get_UserSteerSpeed(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType);
    float Get_UserHealth(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType);
    float Get_UserDamage(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType);
    float Get_UserShootSpeed(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType);
};

#endif /* defined(__iGaia__GameSDBStorage__) */
