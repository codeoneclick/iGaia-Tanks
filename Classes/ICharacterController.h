//
//  ICharacterController.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_ICharacterController_h
#define iGaia_ICharacterController_h

#include "CModel.h"
#include "CSceneMgr.h"
#include "ITouchDelegate.h"
#include "CLandscape.h"
#include "CMathHelper.h"

#include "ITankTrack.h"
#include "ITankTower.h"
#include "ITankBody.h"

#include "CTankLightTrack.h"
#include "CTankLightTower.h"
#include "CTankLightBody.h"

#include "CTankMediumTrack.h"
#include "CTankMediumTower.h"
#include "CTankMediumBody.h"

#include "CTankHeavyTrack.h"
#include "CTankHeavyTower.h"
#include "CTankHeavyBody.h"

#define k_MIN_HEIGHTMAP_VALUE -8.0f

class ICharacterController : public ITouchDelegate, public ICollisionDelegate
{
public:
    enum E_CHARACTER_PART_TYPE { E_CHARACTER_PART_TYPE_LIGHT = 0, E_CHARACTER_PART_TYPE_MEDIUM, E_CHARACTER_PART_TYPE_HEAVY };
    enum E_CHARACTER_CONTROLLER_STATE { E_CHARACTER_CONTROLLER_STATE_NONE = 0, E_CHARACTER_CONTROLLER_STATE_INC_MOVE, E_CHARACTER_CONTROLLER_STATE_DEC_MOVE };
    enum E_CHARACTER_CONTROLLER_MOVE_STATE { E_CHARACTER_CONTROLLER_MOVE_STATE_NONE = 0, E_CHARACTER_CONTROLLER_MOVE_STATE_FORWARD, E_CHARACTER_CONTROLLER_MOVE_STATE_BACKWARD };
    enum E_CHARACTER_CONTROLLER_STEER_STATE { E_CHARACTER_CONTROLLER_STEER_STATE_NONE = 0, E_CHARACTER_CONTROLLER_STEER_STATE_LEFT, E_CHARACTER_CONTROLLER_STEER_STATE_RIGHT };
    enum E_CHARACTER_CONTROLLER_STEER_TOWER_STATE { E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_NONE = 0, E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_LEFT, E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_RIGHT };
protected:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    
    float m_fMaxMoveSpeed;
    float m_fMoveAcceleration;
    float m_fLeftTrackMoveSpeed;
    float m_fRightTrackMoveSpeed;
    float m_fMoveSpeed;
    float m_fSteerSpeed;
    float m_fTowerSteerSpeed;
    float m_fTowerRotationY;
    
    E_CHARACTER_CONTROLLER_MOVE_STATE m_eMoveState;
    E_CHARACTER_CONTROLLER_STEER_STATE m_eSteerState;
    E_CHARACTER_CONTROLLER_STEER_TOWER_STATE m_eSteerTowerState;
    
    ITankBody* m_pChassis;
    ITankTower* m_pTower;
    ITankTrack* m_pTrack;

    CLandscapeDecal* m_pShadowDecal;
    CLandscapeDecal* m_pHealthDecal;
    
    glm::vec3 m_vMaxBound;
    glm::vec3 m_vMinBound;
    
    glm::vec3 m_vTowerCenterBound;
    glm::vec3 m_vLeftTrackCenterBound;
    glm::vec3 m_vRightTrackCenterBound;
    
    ICharacterController* m_pTarget;
    
    inline float _Get_WrapAngle(float _fValue, float _fMin, float _fMax)
    {
        float fDistance = _fMax - _fMin;
        float fTimes = static_cast<float>(floorf((_fValue - _fMin) / fDistance));
        return _fValue - (fTimes * fDistance);
    }
    void _SmoothRotation(void);
public:
    ICharacterController(void);
    virtual ~ICharacterController(void);
    
    virtual void Load(void);
    virtual void Update(void) = 0;
    
    void Set_Position(const glm::vec3& _vPosition);
    void Set_Rotation(const glm::vec3& _vRotation);
    
    glm::vec3 Get_Position(void) { return m_vPosition; }
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    inline glm::vec3 Get_MaxBound(void) { return m_vMaxBound; }
    inline glm::vec3 Get_MinBound(void) { return m_vMinBound; }
    
    inline glm::vec3 Get_TowerCenterBound(void)     { return m_vTowerCenterBound; }
    inline glm::vec3 Get_LeftTrackCenterBound(void) { return m_vLeftTrackCenterBound; }
    inline glm::vec3 Get_RightTrackCenterBound(void){ return m_vRightTrackCenterBound; }
    inline float Get_TowerAngleY(void) { return m_fTowerRotationY; }
    
    virtual bool MoveForward(void);
    virtual bool MoveBackward(void);
    virtual void SteerRight(void);
    virtual void SteerLeft(void);
    
    virtual void Shoot(void);
    
    void Set_MoveState(E_CHARACTER_CONTROLLER_MOVE_STATE _eMoveState) { m_eMoveState = _eMoveState; }
    void Set_SteerState(E_CHARACTER_CONTROLLER_STEER_STATE _eSteerState) { m_eSteerState = _eSteerState; }
    void Set_SteerTowerState(E_CHARACTER_CONTROLLER_STEER_TOWER_STATE _eSteerTowerState) { m_eSteerTowerState = _eSteerTowerState; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner) = 0;
    void Set_Target(ICharacterController* _pTarget) { m_pTarget = _pTarget; }
    ICharacterController* Get_Target(void) { return m_pTarget; }
    
    void Set_Chassis(E_CHARACTER_PART_TYPE _eType);
    void Set_Tower(E_CHARACTER_PART_TYPE _eType);
    void Set_Track(E_CHARACTER_PART_TYPE _eType);
    
    ITankBody* Get_Chassis(void)   { return m_pChassis; }
    ITankTower* Get_Tower(void) { return m_pTower; }
    ITankTrack* Get_Track(void) { return m_pTrack; }
    
    void OnCollision(ICollisionDelegate* _pCollider);
    void OnOriginPositionChanged(const glm::vec3& _vPosition);
    void OnOriginRotationChanged(float _fAngleY);
    glm::vec3 Get_OriginPosition(void) { return m_vPosition; }
    glm::vec3 Get_OriginMaxBound(void) { return m_vMaxBound; }
    glm::vec3 Get_OriginMinBound(void) { return m_vMinBound; }
    
};


#endif
