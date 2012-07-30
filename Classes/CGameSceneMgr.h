//
//  CGameSceneMgr.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__CGameSceneMgr__
#define __iGaia__CGameSceneMgr__

#include <iostream>
#include "IGameScene.h"

class CGameSceneMgr
{
protected:
    IGameScene* m_pScene;
    static CGameSceneMgr* m_pInstance;
public:
    CGameSceneMgr(void);
    ~CGameSceneMgr(void);
    void Update(void);
    static CGameSceneMgr* Instance(void);
    void Set_Scene(IGameScene* _pScene);
    IGameScene* Get_Scene(void) { return m_pScene; }
};

#endif /* defined(__iGaia__CGameSceneMgr__) */
