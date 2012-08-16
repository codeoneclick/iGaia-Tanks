//
//  CEventMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 1/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CEventMgr_h
#define iGaia_CEventMgr_h

#include "stdlib.h"
#include <vector>
#include <map>
#include "INode.h"

class CEventMgr
{
public:
    enum E_EVENT { E_EVENT_TOUCH = 0, E_EVENT_UNTOUCH };
protected:
    std::map<E_EVENT, std::vector<INode*> > m_lContainer;
    static CEventMgr* m_pInstance;
public:
    CEventMgr(void);
    ~CEventMgr(void);
    static CEventMgr* Instance(void);
    void AddEventListener(INode* _pNode, E_EVENT _eEvent);
    void RemoveEventListener(INode* _pNode, E_EVENT _eEvent);
    void OnEvent(E_EVENT _eEvent);
};

#endif
