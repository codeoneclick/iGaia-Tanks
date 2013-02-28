//
//  CRenderCallback.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#include "CRenderCallback.h"

void CRenderCallback::ConnectRendeDidBindListener(const __RENDER_DID_BIND& _listener)
{
    assert(_listener != nullptr);
    m_renderDidBindCallback = _listener;
}

void CRenderCallback::ConnectRendeDidDrawListener(const __RENDER_DID_DRAW& _listener)
{
    assert(_listener != nullptr);
    m_renderDidDrawCallback = _listener;
}

void CRenderCallback::ConnectRendeDidUnbindListener(const __RENDER_DID_UNBIND &_listener)
{
    assert(_listener != nullptr);
    m_renderDidUnbindCallback = _listener;
}

void CRenderCallback::ConnectRenderDidDrawIndexCallback(const __RENDER_DID_DRAW_INDEX &_listener)
{
    assert(_listener != nullptr);
    m_renderDidDrawIndexCallback = _listener;
}

void CRenderCallback::DispatchRenderDidBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_renderDidBindCallback != nullptr);
    m_renderDidBindCallback(_mode);
}

void CRenderCallback::DispatchRenderDidDraw(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_renderDidDrawCallback != nullptr);
    m_renderDidDrawCallback(_mode);
}

void CRenderCallback::DispatchRenderDidUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_renderDidUnbindCallback != nullptr);
    m_renderDidUnbindCallback(_mode);
}

ui32 CRenderCallback::DispatchRenderDidDrawIndex(void)
{
    assert(m_renderDidDrawIndexCallback != nullptr);
    return m_renderDidDrawIndexCallback();
}

CRenderCallback_INTERFACE::CRenderCallback_INTERFACE(void)
{
    ConnectRenderCallback();
}

void CRenderCallback_INTERFACE::ConnectRenderCallback(void)
{
    m_renderCallback.ConnectRenderDidDrawIndexCallback(std::bind(&CRenderCallback_INTERFACE::OnDrawIndex, this));
    m_renderCallback.ConnectRendeDidBindListener(std::bind(&CRenderCallback_INTERFACE::OnBind, this, std::placeholders::_1));
    m_renderCallback.ConnectRendeDidDrawListener(std::bind(&CRenderCallback_INTERFACE::OnDraw, this, std::placeholders::_1));
    m_renderCallback.ConnectRendeDidUnbindListener(std::bind(&CRenderCallback_INTERFACE::OnUnbind, this, std::placeholders::_1));
}

