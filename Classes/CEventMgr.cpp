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
    std::vector<INode*>::iterator pBIterator = m_lContainer[_eEvent].begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer[_eEvent].end();
    while (pBIterator != pEIterator) 
    {
        if(_pNode == (*pBIterator))
        {
            m_lContainer[_eEvent].erase(pBIterator);
            return;
        }
        ++pBIterator;
    }
}

void CEventMgr::OnEvent(CEventMgr::E_EVENT _eEvent)
{
    std::vector<INode*>::iterator pBIterator = m_lContainer[_eEvent].begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer[_eEvent].end();
    while (pBIterator != pEIterator) 
    {
        INode* pNode = (*pBIterator);
        switch (_eEvent)
        {
            case E_EVENT_TOUCH:
                pNode->OnTouchEvent(NULL);
                break;
            case E_EVENT_UNTOUCH:
                
                break;
            default:
                break;
        }
        ++pBIterator;
    }
}




