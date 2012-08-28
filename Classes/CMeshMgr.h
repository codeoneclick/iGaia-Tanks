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
#include "IResourceMgr.h"

class CMeshMgr : public IResourceMgr
{
protected:
    CMesh* m_pDefault;
public:
    CMeshMgr(void);
    virtual ~CMeshMgr(void);
    
    IResource* LoadDefault(void);
    IResource* LoadSync(const std::string& _sName);
    void LoadAsync(const std::string& _sName, const IResource::EventSignature& _pListener);
    
    virtual IResource* Load(const std::string& _sName, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams);
    virtual void Unload(const std::string& _sName);
};

#endif
