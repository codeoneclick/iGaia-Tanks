//
//  CSceneUpdateMgr.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CSceneUpdateMgr_h
#define CSceneUpdateMgr_h

#include "HCommon.h"
#include "CMainLoopUpdateCallback.h"
#include "CSceneUpdateCallback.h"

class CSceneUpdateMgr : public CMainLoopUpdateCallback_INTERFACE
{
private:

    std::set<CSceneUpdateCallback_INTERFACE*> m_listeners;

protected:

    void OnUpdate(f32 _deltatime);

public:

    CSceneUpdateMgr(void);
    ~CSceneUpdateMgr(void);

    void AddEventListener(CSceneUpdateCallback_INTERFACE* _listener);
    void RemoveEventListener(CSceneUpdateCallback_INTERFACE* _listener);
};

#endif 

