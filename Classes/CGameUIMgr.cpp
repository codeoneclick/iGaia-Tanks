//
//  CGameUIMgr.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/5/12.
//
//

#include "CGameUIMgr.h"

CGameUIMgr* CGameUIMgr::m_pInstance = NULL;

CGameUIMgr* CGameUIMgr::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CGameUIMgr();
    }
    return m_pInstance;
}

CGameUIMgr::CGameUIMgr(void)
{
    m_sGameUIName = "none";
}

CGameUIMgr::~CGameUIMgr(void)
{
    
}

extern void Global_Set_GameUI(const std::string& _sName);

void CGameUIMgr::Set_GameUI(const std::string& _sName)
{
    m_sGameUIName = _sName;
    Global_Set_GameUI(m_sGameUIName);
}
