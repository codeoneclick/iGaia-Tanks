//
//  GameTankSDB.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameTankSDB__
#define __iGaia__GameTankSDB__

#include <iostream>

class GameTankSDB
{
public:
    enum E_CHARACTER_FULLSET_TYPE { E_CHARACTER_FULLSET_TYPE_LIGHT = 0, E_CHARACTER_FULLSET_TYPE_MEDIUM, E_CHARACTER_FULLSET_TYPE_HEAVY };
    enum E_CHARACTER_PART_TYPE { E_CHARACTER_PART_TYPE_LIGHT = 0, E_CHARACTER_PART_TYPE_MEDIUM, E_CHARACTER_PART_TYPE_HEAVY };
protected:
    float m_fMoveSpeed;
    float m_fSteerSpeed;
    float m_fShootSpeed;
    float m_fDamage;
    float m_fHealth;
    virtual void InitWithDefaultStats(void) = 0;
public:
    GameTankSDB(void);
    ~GameTankSDB(void);
    virtual void SerializeData(void* _pData) = 0;
    virtual void DeserializeData(void* _pData) = 0;
    float Get_MoveSpeed(void) { return m_fMoveSpeed; }
    float Get_SteerSpeed(void) { return m_fSteerSpeed; }
    float Get_Damage(void) { return m_fDamage; }
    float Get_Health(void) { return m_fHealth; }
    float Get_ShootSpeed(void) { return m_fShootSpeed; }
};

#endif /* defined(__iGaia__GameTankSDB__) */
