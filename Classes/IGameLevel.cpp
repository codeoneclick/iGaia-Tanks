//
//  IGameLevel.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#include "IGameLevel.h"
#include "CSceneMgr.h"

IGameLevel::IGameLevel(void)
{
    m_pLandscape = NULL;
    m_pGrass = NULL;
    m_pSkyBox = NULL;
    m_pOcean = NULL;
}

IGameLevel::~IGameLevel(void)
{
    m_pLandscape = NULL;
    m_pGrass = NULL;
    m_pSkyBox = NULL;
    m_pOcean = NULL;
}

void IGameLevel::Load(void)
{

}

void IGameLevel::Unload(void)
{
    CSceneMgr::Instance()->Remove_LandscapeModel(m_pLandscape);
    CSceneMgr::Instance()->Remove_LandscapeGrassModel(m_pGrass);
    CSceneMgr::Instance()->Remove_OceanModel(m_pOcean);
    CSceneMgr::Instance()->Remove_SkyBoxModel(m_pSkyBox);
}

void IGameLevel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{

}

void IGameLevel::Update(void)
{

}