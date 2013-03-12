//
//  CCommon_IOS.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CCommon_IOS.h"
#include <UIKit/UIKit.h>
#include <Foundation/Foundation.h>

std::string Get_BundlePath(void)
{
    std::string path([[[NSBundle mainBundle] resourcePath] UTF8String]);
    path.append("/");
    return path;
};

ui32 Get_ScreenWidth(void)
{
    return [UIScreen mainScreen].bounds.size.height;
}

ui32 Get_ScreenHeight(void)
{
    return [UIScreen mainScreen].bounds.size.width;
}