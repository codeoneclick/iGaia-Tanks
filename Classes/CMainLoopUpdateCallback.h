//
//  CUpdateCallback.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CMainLoopUpdateCallback_h
#define CMainLoopUpdateCallback_h

#include "HCommon.h"

typedef std::function<void(f32)> __MAIN_LOOP_DID_UPDATE;

class CMainLoopUpdateCallback final
{
    
private:
    
    friend class CMainLoopUpdateCallback_INTERFACE;
    
    __MAIN_LOOP_DID_UPDATE m_mainLoopDidUpdateCallback;
    
protected:
    
    CMainLoopUpdateCallback(void) = default;
    
    void ConnectMainLoopDidUpdateCallback(const __MAIN_LOOP_DID_UPDATE& _listener);
    
public:
    
    ~CMainLoopUpdateCallback(void) = default;
    
    void DispatchMainLoopDidUpdate(f32 _deltatime);
};

class CMainLoopUpdateCallback_INTERFACE
{
private:
    
    CMainLoopUpdateCallback m_mainLoopUpdateCallback;
    void ConnectMainLoopUpdateCallback(void);
    
protected:
    
    CMainLoopUpdateCallback_INTERFACE(void);
    
    virtual void OnUpdate(f32 _deltatime) = 0;
    
public:
    
    virtual ~CMainLoopUpdateCallback_INTERFACE(void) = default;
    
    inline CMainLoopUpdateCallback* Get_Commands(void)
    {
        return &m_mainLoopUpdateCallback;
    };
};



#endif /* defined(__iGaia__CUpdateCallback__) */
