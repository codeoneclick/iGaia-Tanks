//
//  CRoot_iOS.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#ifndef CRoot_h
#define CRoot_h

#include "IRoot.h"
#include "IGLContext.h"

class CRoot : public IRoot
{
private:
    
    IGLContext_INTERFACE* m_glContext;
    
protected:
    
public:
    
    CRoot(void* _glView);
    ~CRoot(void);
};

#endif 
