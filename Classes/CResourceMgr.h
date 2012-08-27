//
//  CResourceMgr.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CResourceMgr_h
#define iGaia_CResourceMgr_h

#include "CTextureMgr.h"
#include "CMeshMgr.h"
#include "IDelegate.h"
#include "stdlib.h"

class CResourceMgr
{
public:
    friend void* UpdateThread(void *_pParam);
    std::map<IResource::E_MGR,IResourceMgr*> m_lMgr;
private:
    static CResourceMgr* m_pInstance;
    pthread_t m_thread;
public:   
    CResourceMgr(void);
    ~CResourceMgr(void);
    static CResourceMgr* Instance(void);
    void Update();
    IResource::EventHandle AddEventListener(const std::string& _sName, IResource::E_MGR _eMgr, IResource::E_THREAD _eThread, const IResource::EventSignature& _pListener, const std::map<std::string, std::string>* _lParams = NULL);
    void RemoveEventListener(IResource::EventHandle _iEventHandle);
    void Unload(IResource* _pResource);
    
};

#endif
