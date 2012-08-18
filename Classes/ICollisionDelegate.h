//
//  ICollisionDelegate.h
//  iGaia
//
//  Created by sergey sergeev on 8/7/12.
//
//

#ifndef __iGaia__ICollisionDelegate__
#define __iGaia__ICollisionDelegate__

#include <iostream>
#include "IDelegate.h"
#include <Box2D/Box2D.h>

class ICollisionDelegate : public virtual IDelegate
{
public:
    b2BodyDef      m_pBox2dBodyDef;
    b2Body*        m_pBox2dBody;
protected:
    std::string m_sColliderIdStr;
public:
    ICollisionDelegate(void);
    virtual ~ICollisionDelegate(void);
    virtual void OnCollision(ICollisionDelegate* _pCollider) = 0;
    virtual void OnBox2dPositionChanged(const glm::vec3& _vPosition) = 0;
    virtual void OnBox2dRotationChanged(float _fAngleY) = 0;
    virtual glm::vec3 Get_Box2dPosition(void) { return glm::vec3(0.0f, 0.0f, 0.0f); }
    virtual glm::vec3 Get_Box2dMaxBound(void) { return glm::vec3(0.0f, 0.0f, 0.0f); }
    virtual glm::vec3 Get_Box2dMinBound(void) { return glm::vec3(0.0f, 0.0f, 0.0f); }
    void Set_Box2dPosition(const glm::vec3& vPosition);
    std::string Get_ColliderIdStr(void) { return m_sColliderIdStr; }
    b2Body* Get_Box2dBody(void) { return m_pBox2dBody; }
    b2BodyDef Get_Box2dBodyDef(void) { return m_pBox2dBodyDef; }
};


#endif /* defined(__iGaia__ICollisionDelegate__) */
