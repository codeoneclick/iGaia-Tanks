//
//  CCollisionCallback.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/25/13.
//
//

#ifndef CCollisionCallback_h
#define CCollisionCallback_h

#include "HCommon.h"

class CCollisionCallback_INTERFACE;

typedef std::function<void(CCollisionCallback_INTERFACE*)> __BOX2D_OBJECT_DID_COLLIDE;
typedef std::function<void(const glm::vec3&)> __BOX2D_OBJECT_DID_CHANGE_POSITION;
typedef std::function<void(f32)> __BOX2D_OBJECT_DID_CHANGE_ROTATION;

typedef std::function<glm::vec3(void)> __BOX2D_OBJECT_DID_RETRIVE_CENTER;
typedef std::function<glm::vec3(void)> __BOX2D_OBJECT_DID_RETRIVE_MAXBOUND;
typedef std::function<glm::vec3(void)> __BOX2D_OBJECT_DID_RETRIVE_MINBOUND;

class CCollisionCallback
{
private:

    friend class CCollisionCallback_INTERFACE;

    __BOX2D_OBJECT_DID_COLLIDE m_collisionCallback;
    __BOX2D_OBJECT_DID_CHANGE_POSITION m_positionChangedCallback;
    __BOX2D_OBJECT_DID_CHANGE_ROTATION m_rotationChangedCallback;

    __BOX2D_OBJECT_DID_RETRIVE_CENTER m_retriveCenterCallback;
    __BOX2D_OBJECT_DID_RETRIVE_MAXBOUND m_retriveMaxboundCallback;
    __BOX2D_OBJECT_DID_RETRIVE_MINBOUND m_retriveMinboundCallback;

protected:

    CCollisionCallback(void);

    void ConnectCollisionListener(const __BOX2D_OBJECT_DID_COLLIDE& _listener);
    void ConnectPositionChangedListener(const __BOX2D_OBJECT_DID_CHANGE_POSITION& _listener);
    void ConnectRotationChangedListener(const __BOX2D_OBJECT_DID_CHANGE_ROTATION& _listener);
    void ConnectRetriveCenterListener(const __BOX2D_OBJECT_DID_RETRIVE_CENTER& _listener);
    void ConnectRetriveMaxboundListener(const __BOX2D_OBJECT_DID_RETRIVE_MAXBOUND& _listener);
    void ConnectRetriveMinboundListener(const __BOX2D_OBJECT_DID_RETRIVE_MINBOUND& _listener);

public:
    
    ~CCollisionCallback(void) {};

    void DispatchDidCollide(CCollisionCallback_INTERFACE* _collider);
    void DispatchPositionDidChange(const glm::vec3& _position);
    void DispatchRotationDidChange(f32 _angle);
    glm::vec3 DispatchCenterDidRetrive(void);
    glm::vec3 DispatchMaxboundDidRetrive(void);
    glm::vec3 DispatchMinboundDidRetrive(void);
};

class CCollisionCallback_INTERFACE
{
private:

protected:

    b2Body* m_box2dBody;
    b2BodyDef m_box2dBodyDefinition;

    CCollisionCallback m_callbacks;
    void ConnectCallbacks(void);
    
    virtual void OnBox2dCollide(CCollisionCallback_INTERFACE* _collider) = 0;
    virtual void OnBox2dPositionChanged(const glm::vec3& _position) = 0;
    virtual void OnBox2dRotationChanged(f32 _angle) = 0;
    
    virtual glm::vec3 Get_Box2dCenter(void) = 0;
    virtual glm::vec3 Get_Box2dMaxBound(void) = 0;
    virtual glm::vec3 Get_Box2dMinBound(void) = 0;
    
public:

    CCollisionCallback_INTERFACE(void);
    virtual ~CCollisionCallback_INTERFACE(void) {};

    inline void Set_Box2dBody(b2Body* _box2dBody)
    {
        m_box2dBody = _box2dBody;
    };

    inline b2Body* Get_Box2dBody(void)
    {
        return m_box2dBody;
    };
    
    inline b2BodyDef* Get_Box2dBodyDefinition(void)
    {
        return &m_box2dBodyDefinition;
    };

    inline CCollisionCallback* Get_Commands(void)
    {
        return &m_callbacks;
    };
};

#endif 
