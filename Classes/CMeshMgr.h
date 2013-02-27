//
//  CMeshMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CMeshMgr_h
#define CMeshMgr_h

#include "IResourceMgr.h"

class CMeshMgr : public IResourceMgr_INTERFACE
{
private:
    
protected:
    
public:
    
    CMeshMgr(void);
    ~CMeshMgr(void);
    
    IResource_INTERFACE* StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadCallback_INTERFACE* _listener);
};

#endif
