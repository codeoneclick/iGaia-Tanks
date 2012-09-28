//
//  CMeshMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CMeshMgr_h
#define iGaia_CMeshMgr_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CParser_MDL.h"

class CMeshMgr
{
protected:
    std::map<std::string, IParser*> m_taskPool;
    std::map<std::string, IResource*> m_resources;
    CMesh* m_stub;
public:
    CMeshMgr(void);
    ~CMeshMgr(void);
    
    IResource* LoadSync(const std::string& _name);
    IResource* LoadAsync(const std::string& _name);
    void Unload(const std::string& _name);
};

#endif
