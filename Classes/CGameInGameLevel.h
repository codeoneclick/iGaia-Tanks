//
//  CGameInGameLevel.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameInGameLevel_h
#define iGaia_CGameInGameLevel_h

#include "IGameLevel.h"

class CGameInGameLevel : public IGameLevel
{
public:
    CGameInGameLevel(void);
    ~CGameInGameLevel(void);
    void Load(void);
    void Unload(void);
    void Update(void);
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif
