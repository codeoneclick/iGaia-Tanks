//
//  CRenderPresentCallback.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/26/13.
//
//

#include "CRenderPresentCallback.h"

void CRenderPresentCallback::ConnectRenderDidPresentCallback(const __RENDER_DID_PRESENT& _listener)
{
    assert(_listener != nullptr);
    m_renderDidPresentCallback = _listener;
}


void CRenderPresentCallback::DispatchRenderDidPresent(void)
{
    assert(m_renderDidPresentCallback != nullptr);
    m_renderDidPresentCallback();
}

CRenderPresentCallback_INTERFACE::CRenderPresentCallback_INTERFACE(void)
{
    ConnectCallbacks();
}

void CRenderPresentCallback_INTERFACE::ConnectCallbacks(void)
{
    m_renderPresentCallback.ConnectRenderDidPresentCallback(std::bind(&CRenderPresentCallback_INTERFACE::OnPresent, this));
}
