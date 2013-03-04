//
//  CUpdateCallback.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/4/13.
//
//

#ifndef CSceneUpdateCallback_h
#define CSceneUpdateCallback_h

#include "HCommon.h"

typedef std::function<void(f32)> __SCENE_DID_UPDATE;

class CSceneUpdateCallback final
{

private:

    friend class CSceneUpdateCallback_INTERFACE;

    __SCENE_DID_UPDATE m_sceneDidUpdateCallback;

protected:

    CSceneUpdateCallback(void) = default;

    void ConnectSceneDidUpdateCallback(const __SCENE_DID_UPDATE& _listener);

public:

    ~CSceneUpdateCallback(void) = default;

    void DispatchSceneDidUpdate(f32 _deltatime);
};

class CSceneUpdateCallback_INTERFACE
{
private:

    CSceneUpdateCallback m_sceneUpdateCallback;
    void ConnectSceneUpdateCallback(void);

protected:

    CSceneUpdateCallback_INTERFACE(void);

    virtual void OnUpdate(f32 _deltatime) = 0;

public:

    virtual ~CSceneUpdateCallback_INTERFACE(void) = default;

    inline CSceneUpdateCallback* Get_Commands(void)
    {
        return &m_sceneUpdateCallback;
    };
};


#endif 
