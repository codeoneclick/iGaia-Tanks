//
//  CResourceMgr.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CResourceMgr_h
#define CResourceMgr_h

#include "HCommon.h"
#include "CTextureMgr.h"
#include "CMeshMgr.h"
#include "IDelegate.h"
#include "CResourceLoadCallback.h"

class CResourceMgr
{

private:

    friend void* Thread(void* _pParameter);
    std::map<E_RESOURCE_MGR, IResourceMgr*> m_tResourceMgrsContainer;
    std::thread m_tThread;
    bool bIsThreadCanceled;

public:
    friend void* UpdateThread(void *_pParam);
    std::map<IResource::E_MGR,IResourceMgr*> m_lMgr;
private:
    static CResourceMgr* m_pInstance;
    pthread_t m_thread;
public:   
    CResourceMgr();
    ~CResourceMgr();
    static CResourceMgr* Instance();

    IResource* StartLoadOperation(const std::string& _sName, E_RESOURCE_MGR _eMgr, E_RESOURCE_LOAD_THREAD _eThread, CResourceLoadCallback_INTERFACE* _pListener);
    void CancelLoadOperation(CResourceLoadCallback_INTERFACE* _pListener);

    
    void Update();
    IResource* Load(const std::string& _sName, IResource::E_MGR _eMgr, IResource::E_THREAD _eThread, IDelegate* _pDeleagte,const std::map<std::string, std::string>* _lParams = NULL);

    
    void Unload(IResource* _pResource);
    void Cancel_Load(IDelegate* _pDeleagte);
};

#endif
