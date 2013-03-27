//
//  CInputMgr.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/27/13.
//
//

#ifndef CInputContext_h
#define CInputContext_h

#include "HCommon.h"
#include "IInputContext.h"

class CInputContext : public IInputContext_INTERFACE
{
private:

protected:

    std::set<CInputTapRecognizerCallback_INTERFACE*> m_tapRecognizerListeners;

public:

    CInputContext(void* _glWindow);
    ~CInputContext(void);

    void TapRecognizerPressed(i32 _x, i32 _y);
    void TapRecognizerMoved(i32 _x, i32 _y);
    void TapRecognizerReleased(i32 _x, i32 _y);

    void AddTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener);
    void RemoveTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE* _listener);
};

#endif 
