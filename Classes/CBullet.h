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

class CBullet
{
protected:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    CParticleEmitterFireTrail* m_pFireEmmiter;
    CParticleEmitter* m_pExplosionEmitter;
    INode* m_pModel;
    float m_fMoveSpeed;
    void _MoveForward(void);
    bool m_bIsDead;
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
};

#endif /* defined(__iGaia__CBullet__) */
