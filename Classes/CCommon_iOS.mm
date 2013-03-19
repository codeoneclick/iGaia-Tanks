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

ui8* Get_ImageData(const std::string& _filename)
{
    UIImage* image = [UIImage imageNamed:[NSString stringWithCString:_filename.c_str() encoding:NSUTF8StringEncoding]];
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    size_t bytesPerRow = image.size.width * 4;
    ui8* result = (ui8*)malloc(image.size.height * bytesPerRow);
    CGContextRef context =  CGBitmapContextCreate(result,
                                                  image.size.width,
                                                  image.size.height,
                                                  8,
                                                  bytesPerRow,
                                                  colorSpace,
                                                  kCGImageAlphaNoneSkipFirst);
    UIGraphicsPushContext(context);
    CGContextTranslateCTM(context, 0.0, image.size.height);
    CGContextScaleCTM(context, 1.0, -1.0);
    [image drawInRect:CGRectMake(0.0, 0.0, image.size.width, image.size.height)];
    UIGraphicsPopContext();
    return result;
}