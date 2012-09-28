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

#include "stdlib.h"

class CResourceMgr
{
public:
    CTextureMgr* m_textureMgr;
    CMeshMgr* m_meshMgr;
private:
    static CResourceMgr* m_instance;
public:   
    CResourceMgr(void);
    ~CResourceMgr(void);
    static CResourceMgr* Instance(void);
    
    IResource* LoadSync(IResource::E_MGR _mgr, const std::string& _name);
    IResource* LoadAsync(IResource::E_MGR _mgr, const std::string& _name);
    void Unload(IResource::E_MGR _mgr, IResource* _resource);
};

#endif
