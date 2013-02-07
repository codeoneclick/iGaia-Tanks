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
#include "IParser.h"
#include "CResourceLoadCallback.h"

class IResourceMgr
{
private:
    

protected:

    std::map<std::string, IParser*> m_tOperationsPool;
    std::map<std::string, IResource*> m_tResourceContainer;
    
    std::map<std::string, IParser*> m_lTaskPool;
    std::map<std::string, IResource*> m_lContainer;
    
public:
    
    IResourceMgr(void);
    virtual ~IResourceMgr(void);
    
    virtual void Update(void);
    virtual void Thread(void);

    virtual IResource* StartLoadOperation(const std::string& _sName, E_RESOURCE_LOAD_THREAD _eThread, CResourceLoadCallback_INTERFACE* _pListener) = 0;
    void CancelLoadOperation(CResourceLoadCallback_INTERFACE* _pListener);
    
    
    virtual IResource* Load(const std::string& _sName, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams) = 0;
    void Cancel_Load(IDelegate* _pDelegate);
    virtual void Unload(const std::string& _sName) = 0;
};


#endif
