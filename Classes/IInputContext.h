//
//  IInputMgr.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/27/13.
//
//

#ifndef IInputContext_h
#define IInputContext_h

#include "HCommon.h"
#include "CInputTapRecognizerCallback.h"

class IInputContext_INTERFACE
{
private:

protected:

public:

    IInputContext_INTERFACE(void) {};
    ~IInputContext_INTERFACE(void) {};

    virtual void AddTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener) = 0;
    virtual void RemoveTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener) = 0;
};

#endif
