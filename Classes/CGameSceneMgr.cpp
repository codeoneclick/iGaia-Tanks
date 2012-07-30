//
//  CGameSceneMgr.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#include "CGameSceneMgr.h"

CGameSceneMgr* CGameSceneMgr::m_pInstance = NULL;

CGameSceneMgr* CGameSceneMgr::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CGameSceneMgr();
    }
    return m_pInstance;
}

CGameSceneMgr::CGameSceneMgr(void)
{
    m_pScene = NULL;
}

CGameSceneMgr::~CGameSceneMgr(void)
{
    
}

void CGameSceneMgr::Set_Scene(IGameScene *_pScene)
{
    m_pScene = _pScene;
}

void CGameSceneMgr::Update(void)
{
    if(m_pScene != NULL)
    {
        m_pScene->Update();
    }
}