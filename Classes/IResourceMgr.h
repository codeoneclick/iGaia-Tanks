//
//  IResourceMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef IResourceMgr_h
#define IResourceMgr_h

#include "HCommon.h"
#include "IResource.h"
#include "ILoadOperation.h"
#include "CResourceLoadCallback.h"

class IResourceMgr_INTERFACE
{
private:
    

protected:

    std::map<std::string, ILoadOperation_INTERFACE*> m_operationsQueue;
    std::map<std::string, IResource_INTERFACE*> m_resourceContainer;

    std::mutex m_mutex;
    std::thread m_thread;

    void Dispatch(CResourceLoadCallback_INTERFACE* _listener, IResource_INTERFACE* _resource);
    void AddListener(CResourceLoadCallback_INTERFACE* _listener, ILoadOperation_INTERFACE* _operation);
    
public:
    
    IResourceMgr_INTERFACE(void);
    virtual ~IResourceMgr_INTERFACE(void);
    
    virtual void Update(void);
    virtual void Thread(void);

    virtual IResource_INTERFACE* StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadCallback_INTERFACE* _listener) = 0;
    void CancelLoadOperation(CResourceLoadCallback_INTERFACE* _listener);

    void UnloadResource(IResource_INTERFACE* resource);
};


#endif
