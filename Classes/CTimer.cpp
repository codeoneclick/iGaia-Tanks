//
//  CTimer.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/6/12.
//
//

#include "CTimer.h"


CTimer* CTimer::m_pInstance = NULL;

CTimer::CTimer(void)
{
    
}

CTimer::~CTimer(void)
{
    
}

CTimer* CTimer::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CTimer();
    }
    return m_pInstance;
}

uint64_t CTimer::Get_TickCount(void)
{
    static mach_timebase_info_data_t sTimebaseInfo;
    uint64_t machTime = mach_absolute_time();
    
    if (sTimebaseInfo.denom == 0 )
    {
        (void)mach_timebase_info(&sTimebaseInfo);
    }
    
    uint64_t millis = ((machTime / 1000000) * sTimebaseInfo.numer) / sTimebaseInfo.denom;
    return millis;
}