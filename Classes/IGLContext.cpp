//
//  CGLContext.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#include "IGLContext.h"

IGLContext_INTERFACE::IGLContext_INTERFACE(void)
{

}

IGLContext_INTERFACE::~IGLContext_INTERFACE(void)
{

}

const ui32 IGLContext_INTERFACE::Get_FrameBufferHandle(void) const
{
    return m_frameBufferHandle;
}

const ui32 IGLContext_INTERFACE::Get_RenderBufferHandle(void) const
{
    return m_renderBufferHandle;
}