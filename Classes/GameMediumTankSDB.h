//
//  GameMediumTankStats.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameMediumTankSDB__
#define __iGaia__GameMediumTankSDB__

#include "GameTankSDB.h"

class GameMediumTankSDB : public GameTankSDB
{
protected:
    void InitWithDefaultStats(void);
public:
    GameMediumTankSDB(void);
    ~GameMediumTankSDB(void);
    void SerializeData(void* _pData);
    void DeserializeData(void* _pData);
};

#endif /* defined(__iGaia__GameMediumTankSDB__) */
