//
//  CGameShooterMgr.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#include "CGameShooterMgr.h"

CGameShooterMgr::CGameShooterMgr(void)
{
    for(unsigned int i = 0; i < k_MAX_NUM_BULLETS; ++i)
    {
        CBullet* pBullet = new CBullet();
        pBullet->Load();
        m_lUnUsedBulletsContainer.push_back(pBullet);
    }
}

CGameShooterMgr::~CGameShooterMgr(void)
{
    for(size_t index = 0; index < m_lUnUsedBulletsContainer.size(); ++index)
    {
        SAFE_DELETE(m_lUnUsedBulletsContainer[index]);
    }
    
    for(size_t index = 0; index < m_lUsedBulletsContainer.size(); ++index)
    {
        SAFE_DELETE(m_lUsedBulletsContainer[index]);
    }

    m_lUnUsedBulletsContainer.clear();
    m_lUsedBulletsContainer.clear();
}

void CGameShooterMgr::CreateBullet(const glm::vec3& _vPosition, const glm::vec3& _vDirection, ICollisionDelegate* _pOwner)
{
    if(m_lUnUsedBulletsContainer.size() > 0)
    {
        CBullet* pBullet = m_lUnUsedBulletsContainer.back();
        m_lUnUsedBulletsContainer.pop_back();
        pBullet->Set_Position(_vPosition);
        pBullet->Set_Rotation(_vDirection);
        pBullet->Set_Owner(_pOwner);
        pBullet->Create();
        m_lUsedBulletsContainer.push_back(pBullet);
    }
    else
    {
        std::cout<<"[CGameShooterMgr::CreateBullet] bullet container is empty"<<std::endl;
    }
}

void CGameShooterMgr::Update(void)
{
    for(size_t index = 0; index < m_lUsedBulletsContainer.size(); ++index)
    {
        m_lUsedBulletsContainer[index]->Update();
        if(m_lUsedBulletsContainer[index]->Get_IsDead())
        {
            m_lUnUsedBulletsContainer.push_back(m_lUsedBulletsContainer[index]);
            m_lUsedBulletsContainer.erase(m_lUsedBulletsContainer.begin() + index);
        }
    }
}




