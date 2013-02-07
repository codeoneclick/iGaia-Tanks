//
//  IParser.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef IParser_h
#define IParser_h

#include "HCommon.h"
#include "IResource.h"

class IParser_INTERFACE
{
private:
    
protected:
    
public:
    
    IParser_INTERFACE(void) = default;
    virtual ~IParser_INTERFACE(void) = default;

    virtual E_PARSER_STATUS Read(const std::string& _sName, IResource* _resource) = 0;
    
};

#endif
