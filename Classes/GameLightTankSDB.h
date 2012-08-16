//
//  GameLightTankSDB.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameLightTankSDB__
#define __iGaia__GameLightTankSDB__

#include "GameTankSDB.h"

class GameLightTankSDB : public GameTankSDB
{
protected:
    void InitWithDefaultStats(void);
public:
    GameLightTankSDB(void);
    ~GameLightTankSDB(void);
    void SerializeData(void* _pData);
    void DeserializeData(void* _pData);
};

#endif /* defined(__iGaia__GameLightTankSDB__) */
