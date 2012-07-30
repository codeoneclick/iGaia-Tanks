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
    std::map<std::string, std::string> m_lParams;
public:
    IParser(void);
    virtual ~IParser(void);
    virtual void  Load(const std::string& _sName) = 0;
    virtual void* Get_SourceData(void) = 0;
    virtual void  Set_Params(const std::map<std::string, std::string>* _lParams) { m_lParams = (*_lParams); }
    virtual void  Commit(void) = 0;
    inline E_STATUS Get_Status(void) { return m_eStatus; }
};

#endif
