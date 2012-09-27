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
        E_NONE_STATUS,
        E_START_STATUS,
        E_ERROR_STATUS,
        E_DONE_STATUS,
    };
protected:
    E_STATUS m_eStatus;
public:
    IParser(void);
    virtual ~IParser(void);
    virtual void  Load(const std::string& _sName) = 0;
    virtual IResource* Commit(void) = 0;
    inline E_STATUS Get_Status(void) { return m_eStatus; }
};

#endif
