//
//  CGame.h
//  iGaia
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGame_h
#define iGaia_CGame_h

#define MATH_RAD_TO_DEG 0.01745329f
#define MATH_DEG_TO_RAD 57.3248408f
#define MATH_PI 3.14159f
#define MATH_DEGREES 180.0f
#define MATH_EPS (1e-6f)

#include "CRenderMgr.h"
#include "CSceneMgr.h"
#include "ILight.h"

class CGame
{
private:
    static CGame* m_game;
public:
    CGame(void);
    ~CGame(void);
    static CGame* Instance(void);
    void Load(void);
    void Update(void);
    void Render(void);
};


#endif
