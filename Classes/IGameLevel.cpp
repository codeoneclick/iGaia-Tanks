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
    
}

IGameLevel::~IGameLevel(void)
{
    
}

void IGameLevel::Load(void)
{

}

void IGameLevel::Unload(void)
{
    for(unsigned int index = 0; index < m_lBuildings.size(); ++index)
    {
        delete m_lBuildings[index];
    }
    m_lBuildings.clear();
}

void IGameLevel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{

}

void IGameLevel::Update(void)
{

}