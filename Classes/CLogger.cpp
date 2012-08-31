//
//  CLogger.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 8/29/12.
//
//

#include "CLogger.h"

void CLogger::LogMsg(const char *msg, ...)
{
    va_list arg;
    va_start(arg, msg);
    _LogMsgImpl(msg, arg);
    va_end(arg);
}

void CLogger::_LogMsgImpl(const char *msg, va_list params)
{
    char msg_buf[1024];
    memset(msg_buf, 0x0, 1024);
    int msg_size;
    msg_size = vsnprintf(msg_buf, sizeof (msg_buf) - 1, msg, params);
    std::cout<<msg_buf<<std::endl;
}