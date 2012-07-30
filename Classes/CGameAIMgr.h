//
//  CGameAIMgr.h
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CGameAIMgr__
#define __iGaia__CGameAIMgr__

#include <iostream>
#include <stdlib.h>
#include <vector>

#include "CCharacterControllerEnemy.h"

class CGameAIMgr
{
protected:
    std::vector<CCharacterControllerEnemy*> m_lContainer;
    glm::vec2 _GenerateMovePoint(void);
    float _Get_RandomFromRange(float _fMin, float _fMax);
public:
    CGameAIMgr(void);
    ~CGameAIMgr(void);
    void Add_AICharacterController(ICharacterController* _pCharacterController);
    void Remove_AICharacterController(ICharacterController* _pCharacterController);
    void Update(void);
};

#endif /* defined(__iGaia__CGameAIMgr__) */
