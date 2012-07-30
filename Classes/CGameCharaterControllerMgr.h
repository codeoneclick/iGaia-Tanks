//
//  CGameCharaterControllerMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameCharaterControllerMgr_h
#define iGaia_CGameCharaterControllerMgr_h


#include <stdlib.h>
#include <map>
#include <vector>

#include "ICharacterController.h"

class CGameCharaterControllerMgr
{
private:
    ICharacterController* m_pCharacterControllerPlayer;
    std::vector<ICharacterController*> m_lContainer;
public:
    CGameCharaterControllerMgr(void);
    ~CGameCharaterControllerMgr(void);
    ICharacterController* Add_MainCharacterController(void);
    ICharacterController* Add_EnemyCharacterController(void);
    void Remove_MainCharacterController(void);
    void Remove_EnemyCharacterController(ICharacterController* _pCharacterController);
    void Reset_MainCharacterController(void);
    ICharacterController* Get_MainCharacterController(void) { return m_pCharacterControllerPlayer; }
    unsigned int Get_NumCharacterControllers(void) { return m_lContainer.size(); }
    ICharacterController* Get_CharacterController(unsigned int _index) { if(_index >= m_lContainer.size()) { return NULL; } else return m_lContainer[_index]; }
     void Update(void);
};

#endif
