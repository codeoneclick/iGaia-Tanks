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
#include <mach/mach.h>
#include <mach/mach_time.h>

class CTimer
{
protected:
    static CTimer* m_pInstance;
public:
    CTimer(void);
    ~CTimer(void);
    static CTimer* Instance(void);
    uint64_t Get_TickCount(void);
};


#endif /* defined(__iGaia__CTimer__) */
