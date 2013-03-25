//
//  CCollisionMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CCollisionMgr_h
#define CCollisionMgr_h

#include "HCommon.h"
#include "CCollisionCallback.h"
#include "CMainLoopUpdateCallback.h"

class CCollisionMgr : public b2ContactListener, public CMainLoopUpdateCallback_INTERFACE
{
private:

protected:

    std::set<CCollisionCallback_INTERFACE*> m_collidersContainer;
    b2World* m_box2dWorld;

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    void OnUpdate(f32 _deltatime);

public:
    
    CCollisionMgr(void);
    ~CCollisionMgr(void);

    void Set_CollisionBounds(const glm::vec2& _maxBound, const glm::vec2& _minBound);

    void AddCollisionEventListener(CCollisionCallback_INTERFACE* _listener, bool _isStatic);
    void RemoveCollisionEventListener(CCollisionCallback_INTERFACE* _listener);
};

#endif
