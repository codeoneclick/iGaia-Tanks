//
//  GameHeavyTankSDB.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameHeavyTankSDB__
#define __iGaia__GameHeavyTankSDB__

#include "GameTankSDB.h"

class GameHeavyTankSDB : public GameTankSDB
{
protected:
    void InitWithDefaultStats(void);
public:
    GameHeavyTankSDB(void);
    ~GameHeavyTankSDB(void);
    void SerializeData(void* _pData);
    void DeserializeData(void* _pData);
};

#endif /* defined(__iGaia__GameHeavyTankSDB__) */
