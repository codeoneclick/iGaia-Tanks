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
    pDecal->Load("decal", IResource::E_THREAD_ASYNC);
    return pDecal;
}

void CDecalMgr::Remove_Decal(INode* _pDecal)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        if(m_lContainer[index] == _pDecal)
        {
            SAFE_DELETE(m_lContainer[index]);
            m_lContainer.erase(m_lContainer.begin() + index);
        }
    }
}

void CDecalMgr::Update(void)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        m_lContainer[index]->Update();
    }
}

void CDecalMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        m_lContainer[index]->Render(_eMode);
    }
}
