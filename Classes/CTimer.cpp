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

#include "Common.h"

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
#elif __linux__
    return APP_API_GET_TIME();
#else
	return GetTickCount();
#endif
}

unsigned long long CTimer::Get_TimeInterval(const CTime &_cTime_01, const CTime &_cTime_02)
{
    return std::chrono::duration_cast<CMilliseconds>(_cTime_01 - _cTime_02).count();
}


