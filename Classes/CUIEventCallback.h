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

typedef std::function<void(const std::string& _command, i32 _x, i32 _y)> __UI_EVENT_DID_PERFORM;

class CUIEventCallback final
{

private:

    friend class CUIEventCallback_INTERFACE;
    __UI_EVENT_DID_PERFORM m_uiEventDidPerformCallback;

protected:

    CUIEventCallback(void) {};

    void ConnectUIEventDidPreformCallback(const __UI_EVENT_DID_PERFORM& _listener);

public:

    ~CUIEventCallback(void) {};

    void DispatchUIEventDidPerform(const std::string& _command, i32 _x, i32 _y);
};

class CUIEventCallback_INTERFACE
{
private:

    CUIEventCallback m_uiEventPerformCallback;
    void ConnectUIEventCallbacks(void);

protected:

    CUIEventCallback_INTERFACE(void);

    virtual void OnUIEventPerform(const std::string& _command, i32 _x, i32 _y) = 0;

public:

    virtual ~CUIEventCallback_INTERFACE(void) {};

    inline CUIEventCallback* Get_Commands(void)
    {
        return &m_uiEventPerformCallback;
    };
};


#endif 
