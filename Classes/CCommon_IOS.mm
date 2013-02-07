//
//  CCommon_IOS.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CCommon_IOS.h"

std::string Get_BundlePath(void)
{
    std::string path([[[NSBundle mainBundle] resourcePath] UTF8String]);
    path.append("/");
    return path;
};