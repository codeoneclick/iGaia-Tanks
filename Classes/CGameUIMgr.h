//
//  CGameUIMgr.h
//  iGaia
//
//  Created by sergey sergeev on 7/5/12.
//
//

#ifndef __iGaia__CGameUIMgr__
#define __iGaia__CGameUIMgr__

#include <iostream>

class CGameUIMgr
{
protected:
    std::string m_sGameUIName;
    static CGameUIMgr* m_pInstance;
public:
    CGameUIMgr(void);
    ~CGameUIMgr(void);
    static CGameUIMgr* Instance(void);
    void Set_GameUI(const std::string& _sName);
    std::string Get_GameUIName(void) { return m_sGameUIName; }
};

#endif /* defined(__iGaia__CGameUIMgr__) */
