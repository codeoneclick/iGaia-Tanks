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

INode* CDecalMgr::Add_LandscapeDecal(void)
{
    CLandscapeDecal* pDecal = new CLandscapeDecal();
    m_lContainer.push_back(pDecal);
    pDecal->Load("decal", IResource::E_THREAD_MAIN);
    return pDecal;
}

void CDecalMgr::Remove_Decal(INode* _pDecal)
{
    std::vector<INode*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndIterator = m_lContainer.end();
    
    while(pBeginIterator != pEndIterator)
    {
        INode* pDecal = (*pBeginIterator);
        if(pDecal == _pDecal)
        {
            m_lContainer.erase(pBeginIterator);
            SAFE_DELETE(pDecal);
            return;
        }
        ++pBeginIterator;
    }
}

void CDecalMgr::Update(void)
{
    std::vector<INode*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndIterator = m_lContainer.end();
    
    while(pBeginIterator != pEndIterator)
    {
        (*pBeginIterator)->Update();
        ++pBeginIterator;
    }
}

void CDecalMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    std::vector<INode*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndIterator = m_lContainer.end();
        
    while(pBeginIterator != pEndIterator)
    {
        (*pBeginIterator)->Render(_eMode);
        ++pBeginIterator;
    }
}
