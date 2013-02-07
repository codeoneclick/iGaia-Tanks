//
//  CParser_PVR.h
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CParser_PVR_h
#define CParser_PVR_h

#include "HCommon.h"
#include "IParser.h"

class CParser_PVR : public IParser_INTERFACE
{
private:

    friend class CTexture;

protected:
    
public:
    
    CParser_PVR(void);
    ~CParser_PVR(void);
    
    virtual E_PARSER_STATUS Read(const std::string& _sName, IResource* _resource);
    
};

#endif
