//
//  CLogger.h
//  iGaia
//
//  Created by Sergey Sergeev on 8/29/12.
//
//

#ifndef __iGaia__CLogger__
#define __iGaia__CLogger__

#include <iostream>

class CLogger
{
protected:
    static void _LogMsgImpl(const char *msg, va_list params);
public:
    CLogger(void) = default;
    ~CLogger(void) = default;
    static void LogMsg(const char *msg, ...);
};

#define LOG(msg, ...) \
std::cout<<__PRETTY_FUNCTION__<<" >>> "; \
CLogger::LogMsg(msg, ##__VA_ARGS__); 

#endif /* defined(__iGaia__CLogger__) */
