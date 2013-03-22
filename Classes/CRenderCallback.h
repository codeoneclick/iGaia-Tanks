//
//  CRenderCallback.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#ifndef CRenderCallback_h
#define CRenderCallback_h

#include "HCommon.h"

typedef std::function<ui32(void)> __RENDER_DID_DRAW_INDEX;
typedef std::function<void(E_RENDER_MODE_WORLD_SPACE)> __RENDER_DID_BIND;
typedef std::function<void(E_RENDER_MODE_WORLD_SPACE)> __RENDER_DID_DRAW;
typedef std::function<void(E_RENDER_MODE_WORLD_SPACE)> __RENDER_DID_UNBIND;

class CRenderCallback final
{

private:

    friend class CRenderCallback_INTERFACE;

    __RENDER_DID_DRAW_INDEX m_renderDidDrawIndexCallback;
    __RENDER_DID_BIND m_renderDidBindCallback;
    __RENDER_DID_DRAW m_renderDidDrawCallback;
    __RENDER_DID_UNBIND m_renderDidUnbindCallback;

protected:

    CRenderCallback(void) {};

    void ConnectRenderDidDrawIndexCallback(const __RENDER_DID_DRAW_INDEX& _listener);
    void ConnectRendeDidBindListener(const __RENDER_DID_BIND& _listener);
    void ConnectRendeDidDrawListener(const __RENDER_DID_DRAW& _listener);
    void ConnectRendeDidUnbindListener(const __RENDER_DID_UNBIND& _listener);

public:

    ~CRenderCallback(void) {};

    ui32 DispatchRenderDidDrawIndex(void);
    void DispatchRenderDidBind(E_RENDER_MODE_WORLD_SPACE _mode);
    void DispatchRenderDidDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    void DispatchRenderDidUnbind(E_RENDER_MODE_WORLD_SPACE _mode);
};

class CRenderCallback_INTERFACE
{
private:

    CRenderCallback m_renderCallback;
    void ConnectRenderCallback(void);

protected:

    CRenderCallback_INTERFACE(void);

    virtual ui32 OnDrawIndex(void) = 0;
    virtual void OnBind(E_RENDER_MODE_WORLD_SPACE _mode) = 0;
    virtual void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode) = 0;
    virtual void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode) = 0;

public:

    virtual ~CRenderCallback_INTERFACE(void) {};

    inline CRenderCallback* Get_Commands(void)
    {
        return &m_renderCallback;
    };
};

#endif 
