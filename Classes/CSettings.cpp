//
//  CSettings.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/29/12.
//
//

#include "CSettings.h"

unsigned int CSettings::g_iCurrentFramesPerSecond = 0;
unsigned int CSettings::g_iCurrentTrianglesPerFrame = 0;
unsigned int CSettings::g_iTotalFramesPerSecond = 0;
unsigned int CSettings::g_iTotalTriagnlesPerFrame = 0;
bool CSettings::g_bEdgeDetect = false;
bool CSettings::g_bOceanReflection = true;
bool CSettings::g_bOceanRefraction = true;