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
#include "box2d.h"

class ICollisionDelegate : public virtual IDelegate
{
public:
    b2BodyDef      m_pBox2dBodyDef;
    b2Body*        m_pBox2dBody;
protected:
    std::string m_sColliderIdStr;
    
    b2Vec2 _Get_LateralVelocity(void);
    b2Vec2 _Get_ForwardVelocity(void);
    void _UpdateFriction(void);
    void _UpdateDrive(int _iControlState);    
    void _UpdateTurn(int _iControlState);
public:
    ICollisionDelegate(void);
    virtual ~ICollisionDelegate(void);
    virtual void OnCollision(ICollisionDelegate* _pCollider) = 0;
    virtual void OnOriginPositionChanged(const glm::vec3& _vPosition) = 0;
    virtual void OnOriginRotationChanged(float _fAngleY) = 0;
    virtual glm::vec3 Get_OriginPosition(void) { return glm::vec3(0.0f, 0.0f, 0.0f); }
    virtual glm::vec3 Get_OriginMaxBound(void) { return glm::vec3(0.0f, 0.0f, 0.0f); }
    virtual glm::vec3 Get_OriginMinBound(void) { return glm::vec3(0.0f, 0.0f, 0.0f); }
    void Set_OriginPosition(const glm::vec3& vPosition);
    std::string Get_ColliderIdStr(void) { return m_sColliderIdStr; }
    b2Body* Get_Box2dBody(void) { return m_pBox2dBody; }
    b2BodyDef Get_Box2dBodyDef(void) { return m_pBox2dBodyDef; }
};


#endif /* defined(__iGaia__ICollisionDelegate__) */
