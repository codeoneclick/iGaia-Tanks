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
#include <map>

class IResourceMgr
{
protected:
    pthread_mutex_t m_mutex;
    std::map<std::string, IParser*> m_lTaskPool;
    std::map<std::string, IResource*> m_lContainer;
public:
    IResourceMgr(void);
    virtual ~IResourceMgr(void);
    
    virtual void Update(void);
    virtual void Thread(void);
    virtual IResource* Load(const std::string& _sName, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams) = 0;
    void Cancel_Load(IDelegate* _pDelegate);
    virtual void Unload(const std::string& _sName) = 0;
};


#endif
