//
//  CGLContext.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#ifndef CGLContext_h
#define CGLContext_h

#include "HCommon.h"

class IGLContext_INTERFACE
{
private:

protected:

    ui32 m_frameBufferHandle;
    ui32 m_renderBufferHandle;

public:
    
    IGLContext_INTERFACE(void);
    virtual ~IGLContext_INTERFACE(void);

    const ui32 Get_FrameBufferHandle(void) const;
    const ui32 Get_RenderBufferHandle(void) const;

    virtual void Present(void) const = 0;

};

#endif 
