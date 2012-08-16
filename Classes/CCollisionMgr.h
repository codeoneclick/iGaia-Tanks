//
//  CCollisionMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CCollisionMgr_h
#define iGaia_CCollisionMgr_h

#include "stdlib.h"
#include <vector>
#include <iostream>
#include <map>
#include "box2d.h"
#include "IVertexBuffer.h"
#include "CIndexBuffer.h"
#include "ICollisionDelegate.h"

class CCollisionMgr : public b2ContactListener
{
public:
    class SRay3d
    {
    public:
        glm::vec3 m_vDirection;
        glm::vec3 m_vOrigin;
    };
protected:
    glm::vec2 m_vTouch2DPoint;
    glm::vec3 m_vTouch3DPoint;
    bool m_bIsTouch;
    SRay3d m_vTouchRay;

    std::vector<ICollisionDelegate*> m_lCollisionObject;

    b2World* m_pBox2dWorld;

    void _Update_Box2d(void);
public:
    CCollisionMgr(void);
    ~CCollisionMgr(void);

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    void OnScreenTouch(glm::vec2 _vTouchPoint);
    
    inline SRay3d Unproject(const glm::vec2& _vValue, const glm::mat4x4& _mView, const glm::mat4x4& _mProjection, glm::ivec4 _vViewport)
    {
        glm::vec3 vDirection, vOrigin;
        float fScreenX =  -((( 2.0f * _vValue.x ) / _vViewport[2]) - 1.0f ) / _mProjection[0][0];
        float fScreenY =  -((( 2.0f * _vValue.y ) / _vViewport[3]) - 1.0f ) / _mProjection[1][1];
        glm::mat4x4 mInverseView = glm::inverse(_mView);
        
        vDirection.x  = (fScreenX * mInverseView[0][0] + fScreenY * mInverseView[1][0] + mInverseView[2][0]);
        vDirection.y  = (fScreenX * mInverseView[0][1] + fScreenY * mInverseView[1][1] + mInverseView[2][1]);
        vDirection.z  = (fScreenX * mInverseView[0][2] + fScreenY * mInverseView[1][2] + mInverseView[2][2]);
        vOrigin.x = mInverseView[3][0];
        vOrigin.y = mInverseView[3][1];
        vOrigin.z = mInverseView[3][2];
        SRay3d tRay;
        tRay.m_vDirection = vDirection;
        tRay.m_vOrigin = vOrigin;
        std::cout<<"[CCollisionMgr::Unproject] Origin : ( "<<vOrigin.x<<", "<<vOrigin.y<<", "<<vOrigin.z<<" )\n"; 
        std::cout<<"[CCollisionMgr::Unproject] Direction : ( "<<vDirection.x<<", "<<vDirection.y<<", "<<vDirection.z<<" )\n"; 
        return tRay;
    }
    
    void Set_Touch3DPoint(glm::vec3 _vTouchPoint) { m_vTouch3DPoint = _vTouchPoint; }
    glm::vec3 Get_Touch3DPoint(void) { return m_vTouch3DPoint; }
    SRay3d Get_TouchRay(void) { return m_vTouchRay; }
    bool RayTriangleIntersection(glm::vec3& _vTrianglePoint_01, glm::vec3& _vTrianglePoint_02, glm::vec3& _vTrianglePoint_03, SRay3d& _tRay, glm::vec3* _vIntersectPoint);
    bool Get_CollisionPoint(IVertexBuffer *_pVB, CIndexBuffer *_pIB, SRay3d& _tRay3d, glm::vec3* _vCollisionPoint);
    void Update(void);

    void Add_CollisionListener(ICollisionDelegate* _pOwner, bool _bIsStatic);
    void Remove_CollisionListener(ICollisionDelegate* _pOwner);

    void Create_Box2dWorld(void);
    void Destroy_Box2dWorld(void);
};

#endif
