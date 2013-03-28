//
//  CUIEventCallback.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#ifndef CUIEventCallback_h
#define CUIEventCallback_h

#include "HCommon.h"

typedef std::function<void(const std::string& _command)> __EVENT_DID_PERFORM;

class CUIEventCallback final
{

private:

    friend class CUIEventCallback_INTERFACE;
    __EVENT_DID_PERFORM m_eventDidPerformCallback;

protected:

    CUIEventCallback(void) {};

    void ConnectEventDidPreformCallback(const __EVENT_DID_PERFORM& _listener);

public:

    ~CUIEventCallback(void) {};

    void DispatchEventDidPerform(const std::string& _command);
};

class CUIEventCallback_INTERFACE
{
private:

    CUIEventCallback m_eventPerformCallback;
    void ConnectCallbacks(void);

protected:

    CUIEventCallback_INTERFACE(void);

    virtual void OnPerform(const std::string& _command) = 0;

public:

    virtual ~CUIEventCallback_INTERFACE(void) {};

    inline CUIEventCallback* Get_Commands(void)
    {
        return &m_eventPerformCallback;
    };
};


#endif 
