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

class CTimer
{
protected:
    static CTimer* m_pInstance;
public:
    CTimer(void);
    ~CTimer(void);
    static CTimer* Instance(void);
    unsigned long long Get_TickCount(void);
};


#endif /* defined(__iGaia__CTimer__) */
