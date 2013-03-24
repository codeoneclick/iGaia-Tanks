//
//  CRotateControllerCallback.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/19/13.
//
//

#ifndef CRotateControllerCallback_h
#define CRotateControllerCallback_h

#include "HCommon.h"

typedef std::function<void(ui32)> __ROTATE_CONTROLLER_DID_UPDATE;

class CRotateControllerCallback final
{

private:

    friend class CRotateControllerCallback_INTERFACE;

    __ROTATE_CONTROLLER_DID_UPDATE m_rotateControllerDidUpdateCallback;

protected:

    CRotateControllerCallback(void) {};

    void ConnectRotateControllerDidUpdateCallback(const __ROTATE_CONTROLLER_DID_UPDATE& _listener);

public:

    ~CRotateControllerCallback(void) {};

    void DispatchRotateControllerDidUpdate(ui32 _direction);
};

class CRotateControllerCallback_INTERFACE
{
private:

    CRotateControllerCallback m_rotateControllerCallback;
    void ConnectCallbacks(void);

protected:

    CRotateControllerCallback_INTERFACE(void);

    virtual void OnRotateControllerUpdate(ui32 _direction) = 0;

public:

    virtual ~CRotateControllerCallback_INTERFACE(void) {};

    inline CRotateControllerCallback* Get_Commands(void)
    {
        return &m_rotateControllerCallback;
    };
};

#endif 
