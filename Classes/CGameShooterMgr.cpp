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
    std::vector<CBullet*>::iterator pBeginBulletIterator = m_lUnUsedBulletsContainer.begin();
    std::vector<CBullet*>::iterator pEndBulletIterator = m_lUnUsedBulletsContainer.end();
    while (pBeginBulletIterator != pEndBulletIterator)
    {
        CBullet* pBullet = *pBeginBulletIterator;
        SAFE_DELETE(pBullet)
        ++pBeginBulletIterator;
    }
    
    pBeginBulletIterator = m_lUsedBulletsContainer.begin();
    pEndBulletIterator = m_lUsedBulletsContainer.end();
    while (pBeginBulletIterator != pEndBulletIterator)
    {
        CBullet* pBullet = *pBeginBulletIterator;
        SAFE_DELETE(pBullet)
        ++pBeginBulletIterator;
    }

    m_lUnUsedBulletsContainer.clear();
    m_lUsedBulletsContainer.clear();
}

void CGameShooterMgr::CreateBullet(const glm::vec3& _vPosition, const glm::vec3& _vDirection)
{
    if(m_lUnUsedBulletsContainer.size() > 0)
    {
        CBullet* pBullet = m_lUnUsedBulletsContainer.back();
        m_lUnUsedBulletsContainer.pop_back();
        pBullet->Set_Position(_vPosition);
        pBullet->Set_Rotation(_vDirection);
        pBullet->Set_IsDead(false);
        m_lUsedBulletsContainer.push_back(pBullet);
    }
    else
    {
        std::cout<<"[CGameShooterMgr::CreateBullet] bullet container is empty"<<std::endl;
    }
}

void CGameShooterMgr::Update(void)
{
    std::vector<CBullet*>::iterator pBeginBulletIterator = m_lUsedBulletsContainer.begin();
    std::vector<CBullet*>::iterator pEndBulletIterator = m_lUsedBulletsContainer.end();
    while (pBeginBulletIterator != pEndBulletIterator)
    {
        (*pBeginBulletIterator)->Update();
        ++pBeginBulletIterator;
    }
    
    pBeginBulletIterator = m_lUsedBulletsContainer.begin();
    pEndBulletIterator = m_lUsedBulletsContainer.end();
    while (pBeginBulletIterator != pEndBulletIterator)
    {
        if((*pBeginBulletIterator)->Get_IsDead())
        {
            CBullet* pBullet = (*pBeginBulletIterator);
            m_lUsedBulletsContainer.erase(pBeginBulletIterator);
            m_lUnUsedBulletsContainer.push_back(pBullet);
            break;
        }
        ++pBeginBulletIterator;
    }
}




