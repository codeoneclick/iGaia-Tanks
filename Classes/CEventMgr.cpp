//
//  CEventMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CEventMgr.h"

CEventMgr* CEventMgr::m_pInstance = NULL;

CEventMgr::CEventMgr(void)
{
    
}

CEventMgr::~CEventMgr(void)
{
    
}

CEventMgr* CEventMgr::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CEventMgr();
    }
    return m_pInstance;
}

void CEventMgr::AddEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    m_lContainer[_eEvent].push_back(_pNode);
}

void CEventMgr::RemoveEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        if(_pNode == m_lContainer[_eEvent][index])
        {
            m_lContainer[_eEvent].erase(m_lContainer[_eEvent].begin() + index);
        }
    }
}

void CEventMgr::OnEvent(CEventMgr::E_EVENT _eEvent)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        switch (_eEvent)
        {
            case E_EVENT_TOUCH:
                m_lContainer[_eEvent][index]->OnTouchEvent(NULL);
                break;
            case E_EVENT_UNTOUCH:
                
                break;
            default:
                break;
        }
    }
}




