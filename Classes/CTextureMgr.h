//
//  CTextureMgr.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CTextureMgr_h
#define iGaia_CTextureMgr_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CParser_PVR.h"

class CTextureMgr
{
protected:
    std::map<std::string, IParser*> m_taskPool;
    std::map<std::string, IResource*> m_resources;
    CTexture* m_stub;
public:
    CTextureMgr(void);
    ~CTextureMgr(void);
    
    IResource* LoadSync(const std::string& _name);
    IResource* LoadAsync(const std::string& _name);
    void Unload(const std::string& _name);
};


#endif
