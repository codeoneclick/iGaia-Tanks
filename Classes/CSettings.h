//
//  CSettings.h
//  iGaia
//
//  Created by sergey sergeev on 6/29/12.
//
//

#ifndef __iGaia__CSettings__
#define __iGaia__CSettings__

#include <iostream>

class CSettings
{
public:
    static unsigned int g_iCurrentTrianglesPerFrame;
    static unsigned int g_iTotalTriagnlesPerFrame;
    static unsigned int g_iCurrentFramesPerSecond;
    static unsigned int g_iTotalFramesPerSecond;
    static bool g_bEdgeDetect;
    static bool g_bOceanReflection;
    static bool g_bOceanRefraction;
};

#endif /* defined(__iGaia__CSettings__) */
