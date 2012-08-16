//
//  CTimer.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/6/12.
//
//

#include "CTimer.h"
#ifdef WIN32
#include <Windows.h>
#endif


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

unsigned long long CTimer::Get_TickCount(void)
{
#ifdef OS_IPHONE
    static mach_timebase_info_data_t sTimebaseInfo;
    uint64_t machTime = mach_absolute_time();
    
    if (sTimebaseInfo.denom == 0 )
    {
        (void)mach_timebase_info(&sTimebaseInfo);
    }
    
    uint64_t millis = ((machTime / 1000000) * sTimebaseInfo.numer) / sTimebaseInfo.denom;
    return millis;
#else
	return GetTickCount();
#endif
}