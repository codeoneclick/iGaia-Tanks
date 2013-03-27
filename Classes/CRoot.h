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
#include "IInputContext.h"

class CRoot : public IRoot
{
private:
    
    IGLContext_INTERFACE* m_glContext;
    IInputContext_INTERFACE* m_inputContext;
    
protected:
    
public:
    
    CRoot(void* _glWindow);
    ~CRoot(void);

    void AddTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener);
    void RemoveTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener);
};

#endif 
