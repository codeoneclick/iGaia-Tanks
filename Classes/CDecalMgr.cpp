//
//  CDecalMgr.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#include "CDecalMgr.h"

CDecalMgr::CDecalMgr(void)
{
    
}


CDecalMgr::~CDecalMgr(void)
{
    
}

CDecal* CDecalMgr::Add_Decal(void)
{
    CDecal* pDecal = new CDecal();
    m_lDecalContainer.push_back(pDecal);
    pDecal->Load("decal", IResource::E_THREAD_MAIN);
    return pDecal;
}

void CDecalMgr::Remove_Decal(CDecal* _pDecal)
{
    std::vector<CDecal*>::iterator pBeginIterator = m_lDecalContainer.begin();
    std::vector<CDecal*>::iterator pEndIterator = m_lDecalContainer.end();
    
    while(pBeginIterator != pEndIterator)
    {
        CDecal* pDecal = (*pBeginIterator);
        if(pDecal == _pDecal)
        {
            m_lDecalContainer.erase(pBeginIterator);
            SAFE_DELETE(pDecal);
            return;
        }
        ++pBeginIterator;
    }
}

void CDecalMgr::Update(void)
{
    std::vector<CDecal*>::iterator pBeginIterator = m_lDecalContainer.begin();
    std::vector<CDecal*>::iterator pEndIterator = m_lDecalContainer.end();
    
    while(pBeginIterator != pEndIterator)
    {
        (*pBeginIterator)->Update();
        ++pBeginIterator;
    }
}

void CDecalMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    std::vector<CDecal*>::iterator pBeginIterator = m_lDecalContainer.begin();
    std::vector<CDecal*>::iterator pEndIterator = m_lDecalContainer.end();
        
    while(pBeginIterator != pEndIterator)
    {
        (*pBeginIterator)->Render(_eMode);
        ++pBeginIterator;
    }
}
