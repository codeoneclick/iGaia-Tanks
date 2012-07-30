//
//  CCommon_IOS.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCommon_IOS.h"


std::string Get_ResourceFileName(const std::string& _sName)
{
    NSString* nsName = [NSString stringWithUTF8String:_sName.c_str()];
    NSString* nsDirectory = [[NSBundle mainBundle] resourcePath];
    nsDirectory = [nsDirectory stringByAppendingPathComponent:nsName];
    std::string sDirectory = [nsDirectory UTF8String];
    return sDirectory;
};