//
//  CCommon_IOS.h
//  iGaia
//
//  Created by sergey.sergeev on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CCommon_IOS_h
#define CCommon_IOS_h

#include "HCommon.h"

std::string Get_BundlePath(void);

ui32 Get_ScreenWidth(void);
ui32 Get_ScreenHeight(void);

ui8* Get_ImageData(const std::string& _filename);

f32 Get_Random(f32 _minValue, f32 _maxValue);

ui64 Get_TickCount(void);

#endif
