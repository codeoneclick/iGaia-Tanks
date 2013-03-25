//
//  CGLContext_iOS.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#ifndef CGLContext_iOS_h
#define CGLContext_iOS_h

#include "IGLContext.h"

#ifdef __APPLE__

class CGLContext_iOS : public IGLContext_INTERFACE
{
private:

protected:
    
    EAGLContext* m_iOSGLContext;
    
public:
    
    CGLContext_iOS(const CAEAGLLayer* _iOSGLLayer);
    ~CGLContext_iOS(void);

    void Present(void) const;
};

#endif

#endif 
