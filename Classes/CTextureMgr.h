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
#include "IResourceMgr.h"
#include "IDelegate.h"

class CTextureMgr : public IResourceMgr
{
private:
    CTexture::SSourceData* m_pDefaultTextureSourceData;
    CTexture* m_pDefault;
public:
    CTextureMgr(void);
    virtual ~CTextureMgr(void);
    
    IResource* LoadDefault(void);
    IResource* LoadSync(const std::string& _sName);
    void LoadAsync(const std::string& _sName, const IResource::EventSignature& _pListener);
    
    virtual IResource* Load(const std::string& _sName, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams);
    virtual void Unload(const std::string& _sName);
};


#endif
