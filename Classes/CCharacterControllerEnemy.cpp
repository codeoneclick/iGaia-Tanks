//
//  CCharacterControllerEnemy.cpp
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CCharacterControllerEnemy.h"
#include "CGameSceneMgr.h"
#include "CTimer.h"
#include "CTankLightTrack.h"
#include "CTankLightTower.h"
#include "CTankLightBody.h"

CCharacterControllerEnemy::CCharacterControllerEnemy(void)
{
    m_pTrack = NULL;
    m_pTower = NULL;
    m_pChassis  = NULL;
    
    m_eState = E_AI_STATE_NONE;
    m_iAIStateDuration = 0;
    m_vMoveDirection = glm::vec3(0.0f, 0.0, 0.0f);
    m_eStreerMode = E_AI_STEER_MODE_NONE;
}

CCharacterControllerEnemy::~CCharacterControllerEnemy(void)
{
    CSceneMgr::Instance()->Get_CollisionMgr()->Remove_CollisionListener(this);
    CSceneMgr::Instance()->RemoveEventListener(m_pChassis->Get_BasisNode(), CEventMgr::E_EVENT_TOUCH);
}

long CCharacterControllerEnemy::_Get_TimeStamp(void)
{
    return time(NULL);
}

bool CCharacterControllerEnemy::_IsStateTimeElapsed(void)
{
    int iCurrentTime = CTimer::Instance()->Get_TickCount();
    if(iCurrentTime - m_iAIStateTimeStamp >= m_iAIStateDuration)
    {
        return true;
    }
    return false;
}

void CCharacterControllerEnemy::Load(void)
{
    ICharacterController::Load();
    
    m_pTrack = new CTankLightTrack();
    m_pTrack->Load();
    
    m_pTower = new CTankLightTower();
    m_pTower->Load();
    
    m_pChassis = new CTankLightBody();
    m_pChassis->Load();
    
    m_vMaxBound = m_pChassis->Get_BodyMaxBound();
    m_vMinBound = m_pChassis->Get_BodyMinBound();
    
    m_vTowerCenterBound = m_pTower->Get_TowerCenterBound();
    m_vRightTrackCenterBound = m_pTrack->Get_RightTrackTowerCenterBound();
    m_vLeftTrackCenterBound = m_pTrack->Get_LeftTrackTowerCenterBound();
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Add_CollisionListener(this, false);
    /*CSceneMgr::Instance()->AddEventListener(m_pBody->Get_BasisNode(), CEventMgr::E_EVENT_TOUCH);
    m_pBody->Get_BasisNode()->Add_DelegateOwner(this);
    CGameSceneMgr::Instance()->Get_Scene()->Get_Level()->Get_Landscape()->Add_DelegateOwner(this);*/
}

void CCharacterControllerEnemy::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{

}

void CCharacterControllerEnemy::Set_AIState(E_AI_STATE _eState, long _iAIStateDuration)
{
    m_eState = _eState;
    m_iAIStateDuration = _iAIStateDuration;
    m_iAIStateTimeStamp = CTimer::Instance()->Get_TickCount();
    if(m_eState == E_AI_STATE_MOVE)
    {
        m_vMoveDirection = glm::normalize(m_vPosition - m_vMovePoint);
    }
    
    float fAngleFromSeekerToTarget = CMathHelper::Instance()->Get_RotationBetweenPoints(m_vMovePoint, m_vPosition) + 180.0f;
    fAngleFromSeekerToTarget = CMathHelper::Instance()->Get_WrapAngle(fAngleFromSeekerToTarget, 0.0f, 360.0f);
    if(fAngleFromSeekerToTarget > m_vRotation.y)
    {
        m_eStreerMode = E_AI_STEER_MODE_LEFT;
    }
    else 
    {
        m_eStreerMode = E_AI_STEER_MODE_RIGHT; 
    }
}

void CCharacterControllerEnemy::Shoot(void)
{
    if(m_pTarget == NULL)
    {
        return;
    }
    
    glm::vec2 vPoint_01 = glm::vec2(m_vPosition.x, m_vPosition.z);
    glm::vec2 vPoint_02 = glm::vec2(m_pTarget->Get_Position().x, m_pTarget->Get_Position().z);
    
    float fDistanceToTargetPoint = glm::distance(vPoint_01, vPoint_02);
    
    int iCurrentTime = CTimer::Instance()->Get_TickCount();
    
    if(((iCurrentTime - m_iAIShootTimeStamp) > k_AI_SHOOT_INTERVAL) && fDistanceToTargetPoint < k_AI_SHOOT_DISTANCE && m_pTower != NULL)
    {
        glm::vec3 vTowerGunOffset = m_pTower->Get_TowerGunOffset();
        CGameSceneMgr::Instance()->Get_Scene()->Get_GameShooterMgr()->CreateBullet(glm::vec3(m_vPosition.x + sinf(glm::radians(m_fTowerRotationY)) * vTowerGunOffset.x, m_vPosition.y + vTowerGunOffset.y, m_vPosition.z + cosf(glm::radians(m_fTowerRotationY)) * vTowerGunOffset.z), glm::vec3(m_vRotation.x, m_fTowerRotationY, m_vRotation.z), this);
        m_iAIShootTimeStamp = CTimer::Instance()->Get_TickCount();
    }
}

void CCharacterControllerEnemy::Update(void)
{
    float fTrackTexCoordOffsetMoveFactor  = 0.2f;
    
    m_vRotation.y = CMathHelper::Instance()->Get_WrapAngle(m_vRotation.y, 0.0f, 360.0f);
    
    switch (m_eState)
    {
        case E_AI_STATE_NONE:
            std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> AI_STATE_NONE"<<std::endl;
            m_pChassis->StartExhaustEmitt(false);
            m_pChassis->StartDirtEmitt(false);
            break;
        case E_AI_STATE_STAND:
        {
            m_pChassis->StartExhaustEmitt(false);
            m_pChassis->StartDirtEmitt(false);
            std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> E_AI_STATE_STAND"<<std::endl;
        }
            break;
        case E_AI_STATE_MOVE:
        {
            float fMoveSpeed = GameSDBStorage::Instance()->Get_UserMoveSpeed(m_eFullSetType);
            glm::vec2 vPoint_01 = glm::vec2(m_vPosition.x, m_vPosition.z);
            glm::vec2 vPoint_02 = glm::vec2(m_vMovePoint.x, m_vMovePoint.z);
            
            if(glm::distance(vPoint_01, vPoint_02) < 1.0f)
            {
                m_eState = E_AI_STATE_NONE;
                break;
            }
            
            float fAngleFromSeekerToTarget = CMathHelper::Instance()->Get_RotationBetweenPoints(m_vMovePoint, m_vPosition) + 180.0f;
            //glm::degrees(CMathHelper::Instance()->Get_RotationBetweenPointsDot(vPoint_01, vPoint_02));
            fAngleFromSeekerToTarget = CMathHelper::Instance()->Get_WrapAngle(fAngleFromSeekerToTarget, 0.0f, 360.0f);
            if(m_eStreerMode == E_AI_STEER_MODE_LEFT)
            {
                if(fabsf(fAngleFromSeekerToTarget - m_vRotation.y) > 45.0f)
                {
                    m_pNavigationHelper->MoveLeft();
                    m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
                    m_pTrack->Move_RightTrack(fTrackTexCoordOffsetMoveFactor);
                }
                else
                {
                    if(fabs(fAngleFromSeekerToTarget - m_vRotation.y) > 1.0f)
                    {
                        m_pNavigationHelper->MoveLeft();
                    }
                    //MoveForward();
                    if(m_pBox2dBody != NULL)
                    {
                        b2Vec2 vForce = b2Vec2(0.0f, 0.0f);
                        vForce.x += sinf(glm::radians(m_vRotation.y)) * fMoveSpeed;
                        vForce.y += cosf(glm::radians(m_vRotation.y)) * fMoveSpeed;
                        m_pBox2dBody->SetAwake(true);
                        m_pBox2dBody->SetLinearVelocity(vForce);
                    }
                    m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
                    m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
                }
            }
            else if(m_eStreerMode == E_AI_STEER_MODE_RIGHT)
            {
                if(fabsf(fAngleFromSeekerToTarget - m_vRotation.y) > 45.0f)
                {
                    m_pNavigationHelper->MoveRight();
                    m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
                    m_pTrack->Move_RightTrack(fTrackTexCoordOffsetMoveFactor);
                }
                else
                {
                    if(fabs(fAngleFromSeekerToTarget - m_vRotation.y) > 1.0f)
                    {
                        m_pNavigationHelper->MoveRight();
                    }
                    //MoveForward();
                    if(m_pBox2dBody != NULL)
                    {
                        b2Vec2 vForce = b2Vec2(0.0f, 0.0f);
                        vForce.x += sinf(glm::radians(m_vRotation.y)) * fMoveSpeed;
                        vForce.y += cosf(glm::radians(m_vRotation.y)) * fMoveSpeed;
                        m_pBox2dBody->SetAwake(true);
                        m_pBox2dBody->SetLinearVelocity(vForce);
                    }
                    m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
                    m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
                }
            }
            m_pChassis->StartExhaustEmitt(true);
            m_pChassis->StartDirtEmitt(true);
        }
            break;
        default:
            break;
    }
    
    if(m_pBox2dBody != NULL)
    {
        m_pBox2dBody->SetTransform(m_pBox2dBody->GetPosition(), glm::radians(m_vRotation.y));
    }
    
    m_pTrack->Update();
    m_pTower->Update();
    m_pChassis->Update();
    
    //Shoot();
    
    glm::vec3 vTargetPoint;
    if(m_pTarget != NULL)
    {
        vTargetPoint = m_pTarget->Get_Position();
    }
    else
    {
        vTargetPoint = m_vMovePoint;
    }
    
    //m_fTowerRotationY = CMathHelper::Instance()->Get_RotationBetweenPoints(m_vPosition, vTargetPoint);
    m_vRotation.y = CMathHelper::Instance()->Get_RotationBetweenPoints(m_vPosition, vTargetPoint);
    
    /*glm::vec3 vStepPosition = m_vPosition;
    vStepPosition.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    vStepPosition.z += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_fTowerRotationY = CMathHelper::Instance()->Get_RotationBetweenPointsDot(m_vPosition - vStepPosition, m_vPosition - vTargetPoint);
    */
    Set_Position(m_vPosition);
    _SmoothRotation();
    Set_Rotation(m_vRotation);
}




