//
//  CRenderPresentCallback.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/26/13.
//
//

#ifndef CRenderPresentCallback_h
#define CRenderPresentCallback_h

#include "HCommon.h"

typedef std::function<void(void)> __RENDER_DID_PRESENT;

class CRenderPresentCallback final
{

private:

    friend class CRenderPresentCallback_INTERFACE;
    __RENDER_DID_PRESENT m_renderDidPresentCallback;

protected:

    CRenderPresentCallback(void) {};

    void ConnectRenderDidPresentCallback(const __RENDER_DID_PRESENT& _listener);

public:

    ~CRenderPresentCallback(void) {};

    void DispatchRenderDidPresent(void);
};

class CRenderPresentCallback_INTERFACE
{
private:

    CRenderPresentCallback m_renderPresentCallback;
    void ConnectCallbacks(void);

protected:

    CRenderPresentCallback_INTERFACE(void);

    virtual void OnPresent(void) = 0;

public:

    virtual ~CRenderPresentCallback_INTERFACE(void) {};

    inline CRenderPresentCallback* Get_Commands(void)
    {
        return &m_renderPresentCallback;
    };
};

#endif 
