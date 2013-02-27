//
//  CTextureMgr.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CTextureMgr_h
#define CTextureMgr_h

#include "IResourceMgr.h"

class CTextureMgr : public IResourceMgr_INTERFACE
{
private:

protected:
    
public:
    
    CTextureMgr(void);
    ~CTextureMgr(void);
    
    IResource_INTERFACE* StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadCallback_INTERFACE* _listener);
};


#endif
