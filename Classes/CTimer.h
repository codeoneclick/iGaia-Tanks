//
//  CTimer.h
//  iGaia
//
//  Created by sergey sergeev on 6/6/12.
//
//

#ifndef __iGaia__CTimer__
#define __iGaia__CTimer__

#include <iostream>
#ifdef OS_IPHONE
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif
#include <chrono>


class CTimer
{
public:
    typedef std::chrono::high_resolution_clock CClock;
    typedef std::chrono::milliseconds CMilliseconds;
    typedef CClock::time_point CTime;
    
    static unsigned long long Get_TickCount(void);
    static unsigned long long Get_TimeInterval(const CTime& _cTime_01, const CTime& _cTime_02);
};


#endif /* defined(__iGaia__CTimer__) */
