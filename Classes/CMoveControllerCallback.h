//
//  CMoveControllerCallback.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#ifndef CMoveControllerCallback_h
#define CMoveControllerCallback_h

#include "HCommon.h"

typedef std::function<void(ui32)> __MOVE_CONTROLLER_DID_UPDATE;

class CMoveControllerCallback final
{

private:

    friend class CMoveControllerCallback_INTERFACE;

    __MOVE_CONTROLLER_DID_UPDATE m_moveControllerDidUpdateCallback;

protected:

    CMoveControllerCallback(void) = default;

    void ConnectMoveControllerDidUpdateCallback(const __MOVE_CONTROLLER_DID_UPDATE& _listener);

public:

    ~CMoveControllerCallback(void) = default;

    void DispatchMoveControllerDidUpdate(ui32 _direction);
};

class CMoveControllerCallback_INTERFACE
{
private:

    CMoveControllerCallback m_moveControllerCallback;
    void ConnectCallbacks(void);

protected:

    CMoveControllerCallback_INTERFACE(void);

    virtual void OnMoveControllerUpdate(ui32 _direction) = 0;

public:

    virtual ~CMoveControllerCallback_INTERFACE(void) = default;

    inline CMoveControllerCallback* Get_Commands(void)
    {
        return &m_moveControllerCallback;
    };
};

#endif 
