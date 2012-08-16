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

#ifdef OS_IPHONE
static const std::string k_RES_MODELES_PATH = "";
static const std::string k_RES_TEXTURES_PATH = "";
#else
static const std::string k_RES_MODELES_PATH = "../Resources/Models/";
static const std::string k_RES_TEXTURES_PATH = "../Resources/Textures/";
#endif

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
    static float g_fAccellerometer_X;
    static float g_fAccellerometer_Y;
    static float g_fAccellerometer_Z;
};

#endif /* defined(__iGaia__CSettings__) */
