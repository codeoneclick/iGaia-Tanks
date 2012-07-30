//
//  CGameState.h
//  iGaia
//
//  Created by sergey.sergeev on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameState_h
#define iGaia_CGameState_h

class CGameState
{
public:
    enum E_GAME_WORLD_STATE { E_GAME_WORLD_STATE_NONE = 0, E_GAME_WORLD_STATE_UNIT_INFO, E_GAME_WORLD_STATE_BUILDING_INFO, E_GAME_WORLD_STATE_BUILDING_PLACE }; 
protected:
    E_GAME_WORLD_STATE m_eWorldState;
    static CGameState* m_pInstance;
public:
    CGameState(void);
    ~CGameState(void);
    static CGameState* Instance(void);
    E_GAME_WORLD_STATE Get_WorldState(void) { return m_eWorldState; }
    void Set_WorldState(E_GAME_WORLD_STATE _eWorldState) { m_eWorldState = _eWorldState; }
};

#endif
