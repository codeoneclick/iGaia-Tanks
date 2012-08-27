//
//  IResourceMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IResourceMgr_h
#define iGaia_IResourceMgr_h
#include "IResource.h"
#include "IParser.h"
#include <pthread.h>
#include "stdlib.h"
#include <unordered_map>

class IResourceMgr
{
protected:
    std::unordered_map<std::string, IParser*> m_lTaskPool;
    std::unordered_map<std::string, IResource*> m_lContainer;
public:
    IResourceMgr(void);
    virtual ~IResourceMgr(void);
    
    virtual void Update(void);
    virtual void Thread(void);
    
    virtual IResource::EventHandle AddEventListener(const std::string& _sName, IResource::E_THREAD _eThread, const IResource::EventSignature& _pListener, const std::map<std::string, std::string>* _lParams) = 0;
    void RemoveEventListener(const IResource::EventHandle& _iEventHandle);
};


#endif
