//
//  IParser.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IParser_h
#define iGaia_IParser_h

#include "stdlib.h"
#include <string.h>
#include <map>
#include "IResource.h"

class IParser
{
public:
    enum E_STATUS
    {
        E_STATUS_INIT = 0,
        E_STATUS_LOAD,
        E_STATUS_ERROR,
        E_STATUS_DONE,
    };
protected:
    E_STATUS m_status;
public:
    IParser(void);
    virtual ~IParser(void);
    virtual void  Load(const std::string& _sName) = 0;
    virtual IResource* Commit(void) = 0;
    inline E_STATUS Get_Status(void) { return m_status; }
};

#endif
