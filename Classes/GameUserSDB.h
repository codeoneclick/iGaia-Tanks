//
//  GameUserSDB.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameUserSDB__
#define __iGaia__GameUserSDB__

#include <iostream>

class GameUserSDB
{
protected:
    float m_fLightSkill;
    float m_fMediumSkill;
    float m_fHeavySkill;
    void InitWithDefaultStats(void);
public:
    GameUserSDB(void);
    ~GameUserSDB(void);
    void SerializeData(void* _pData);
    void DeserializeData(void* _pData);
    float Get_LightSkill(void) { return m_fLightSkill; }
    float Get_MediumSkill(void) { return m_fMediumSkill; }
    float Get_HeavySkill(void) { return m_fHeavySkill; }
};


#endif /* defined(__iGaia__GameUserStats__) */
