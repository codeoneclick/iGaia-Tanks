//
//  CBullet.h
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#ifndef __iGaia__CBullet__
#define __iGaia__CBullet__

#include <iostream>
#include "CSceneMgr.h"

#define k_BULLET_HEIGHT_OFFSET 1.45f

class CBullet : public ICollisionDelegate
{
protected:
    enum E_BULLET_STATE { E_BULLET_STATE_NONE = 0, E_BULLET_STATE_01, E_BULLET_STATE_02 };
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    CParticleEmitterFireTrail* m_pFireEmmiter;
    CParticleEmitterFireTrail* m_pExplosionEmitter;
    INode* m_pModel;
    float m_fMoveSpeed;
    void _MoveForward(void);
    bool m_bIsDead;
    ICollisionDelegate* m_pOwner;
    glm::vec3 m_vMaxBound;
    glm::vec3 m_vMinBound;
    E_BULLET_STATE m_eBulletState;
    unsigned int m_iExplosionTimeStamp;
public:
    CBullet(void);
    ~CBullet(void);
    void Load(void);
    void Update(void);
    
    void Set_Position(const glm::vec3& _vPosition);
    glm::vec3 Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(const glm::vec3& _vRotation);
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    bool Get_IsDead(void) { return m_bIsDead; }
    void Set_IsDead(bool _bValue) { m_bIsDead = _bValue; if(!m_bIsDead) { m_pFireEmmiter->Reset(); m_pFireEmmiter->Start(); } }
    
    void Create(void);
    void WillDestroy(void);
    void Destroy(void);
    
    void Set_Owner(ICollisionDelegate* _pOwner) { m_pOwner = _pOwner; }
    ICollisionDelegate* Get_Owner(void) { return m_pOwner; }
    
    void OnCollision(ICollisionDelegate* _pCollider);
    void OnBox2dPositionChanged(const glm::vec3& _vPosition);
    void OnBox2dRotationChanged(float _fAngleY);
    glm::vec3 Get_Box2dPosition(void) { return m_vPosition; }
    glm::vec3 Get_Box2dMaxBound(void) { return m_vMaxBound; }
    glm::vec3 Get_Box2dMinBound(void) { return m_vMinBound; }
};

#endif /* defined(__iGaia__CBullet__) */
