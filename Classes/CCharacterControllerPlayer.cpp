//
//  CCharacterControllerPlayer.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCharacterControllerPlayer.h"
#include "CGameSceneMgr.h"
#include "CSceneMgr.h"
#include "CTimer.h"

CCharacterControllerPlayer::CCharacterControllerPlayer(void)
{
    m_pChassis = NULL;
    m_pTrack = NULL;
    m_pTower = NULL;
    
    m_fMaxMoveSpeed = 0.2f;
    m_fMoveAcceleration = 0.01f;
    
    m_fMoveSpeed = 0.0f;
    m_fLeftTrackMoveSpeed = 0.0f;
    m_fRightTrackMoveSpeed = 0.0f;
    m_fSteerSpeed = 2.0f;
    m_fTowerSteerSpeed = 2.0f;
    m_fTowerRotationY = 0.0f;
    m_sColliderIdStr = "player_collider";
}

CCharacterControllerPlayer::~CCharacterControllerPlayer(void)
{
    CSceneMgr::Instance()->Get_CollisionMgr()->Remove_CollisionListener(this);
    CSceneMgr::Instance()->RemoveEventListener(m_pChassis->Get_BasisNode(), CEventMgr::E_EVENT_TOUCH);
    CSceneMgr::Instance()->Get_DecalMgr()->Remove_Decal(m_pTargetDecal);
}

void CCharacterControllerPlayer::Load(void)
{
    ICharacterController::Load();
    
    m_pTargetDecal = static_cast<CLandscapeDecal*>(CSceneMgr::Instance()->Get_DecalMgr()->Add_LandscapeDecal());
    m_pTargetDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pTargetDecal->Set_Texture("ring.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    m_pTargetDecal->Set_Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    
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

void CCharacterControllerPlayer::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    //CSceneMgr::Instance()->Get_CollisionMgr()->Get_Touch3DPoint();
}

void CCharacterControllerPlayer::Update(void)
{   
    m_fMoveSpeed = m_fMaxMoveSpeed;
    float fTrackTexCoordOffsetMoveFactor  = 0.2f;
    float fTrackTexCoordOffsetSteerFactor = 0.1f;
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    switch (m_eMoveState)
    {
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_NONE:
            if(pCamera->Get_FovY() > k_CAMERA_FOV_Y_STATE_NONE)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() - k_CAMERA_FOV_Y_DELTA_STATE_NONE);
            }
            m_pChassis->StartExhaust(false);
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_FORWARD:
            
            //MoveForward();
            m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
            
            if(pCamera->Get_FovY() < k_CAMERA_FOV_Y_STATE_FORWARD)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() + k_CAMERA_FOV_Y_DELTA_STATE_FORWARD);
            }
            m_pChassis->StartExhaust(true);
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_BACKWARD:
            
            //MoveBackward();
            m_pTrack->Move_LeftTrack(fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(fTrackTexCoordOffsetMoveFactor);
            
            if(pCamera->Get_FovY() > k_CAMERA_FOV_Y_STATE_BACKWARD)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() - k_CAMERA_FOV_Y_DELTA_STATE_BACKWARD);
            }
            m_pChassis->StartExhaust(true);
            break;
        default:
            break;
    }
    
    switch (m_eSteerState)
    {
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_NONE:
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_LEFT:
            
            SteerLeft();
            
            m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(fTrackTexCoordOffsetSteerFactor);
            m_pChassis->StartExhaust(true);
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_RIGHT:
            
            SteerRight();
            
            m_pTrack->Move_LeftTrack(fTrackTexCoordOffsetSteerFactor);
            m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
            m_pChassis->StartExhaust(true);
            
            break;
        default:
            break;
    }
    
    /*if(fabsf(CSettings::g_fAccellerometer_Y) > 0.1f && fabsf(m_fTowerRotationY + CSettings::g_fAccellerometer_Y * m_fTowerSteerSpeed) < 60.0f)
    {
        m_fTowerRotationY += CSettings::g_fAccellerometer_Y * m_fTowerSteerSpeed;
    }
    
    std::cout<<"[ BODY ANGLE ] :"<<_Get_WrapAngle(m_vRotation.y, 0.0f, 360.0f)<<std::endl;
    std::cout<<"[ TOWER ANGLE ] :"<<_Get_WrapAngle(m_fTowerRotationY + m_vRotation.y, 0.0f, 360.0f)<<std::endl;
   
    if(fabsf(_Get_WrapAngle(m_vRotation.y, 0.0f, 360.0f) - _Get_WrapAngle(m_fTowerRotationY + m_vRotation.y, 0.0f, 360.0f)) > 60.0f)
    {
        if(_Get_WrapAngle(m_vRotation.y, 0.0f, 360.0f) < _Get_WrapAngle((m_fTowerRotationY + m_vRotation.y), 0.0f, 360.0f))
        {
            m_fTowerRotationY -= m_fSteerSpeed;
            SteerLeft();
        }
        else
        {
            m_fTowerRotationY += m_fSteerSpeed;
            SteerRight();
        }
    }*/
    
    switch (m_eSteerTowerState)
    {
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_NONE:
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_RIGHT:
        {
            if((m_fTowerRotationY + m_fTowerSteerSpeed) > 60.0f)
            {
                SteerLeft();
            }
            else
            {
                m_fTowerRotationY += m_fTowerSteerSpeed;
            }
        }
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_LEFT:
        {
            if((m_fTowerRotationY - m_fTowerSteerSpeed) < -60.0f)
            {
                SteerRight();
            }
            else
            {
                m_fTowerRotationY -= m_fTowerSteerSpeed;
            }
        }
            break;
            
        default:
            break;
    }
    
    m_fMoveSpeed = 10.0f;

    if(m_pBox2dBody != NULL)
    {
        b2Vec2 vForce = b2Vec2(0.0f, 0.0f);
        switch (m_eMoveState)
        {
            case 1:
            {
                vForce.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
                vForce.y += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
            }
                break;
            case 2:
            {
                vForce.x -= sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
                vForce.y -= cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
            }
                break;
            default:
                break;
        }
        
        m_pBox2dBody->SetAwake(true);
        m_pBox2dBody->SetLinearVelocity(vForce);
    }
    
    if(m_pBox2dBody != NULL)
    {
        m_pBox2dBody->SetTransform(m_pBox2dBody->GetPosition(), glm::radians(m_vRotation.y));
    }
    
    /*if(m_pBox2dBody != NULL)
    {
        _UpdateFriction();
        _UpdateDrive(static_cast<int>(m_eMoveState));
        _UpdateTurn(static_cast<int>(m_eSteerState));
    }*/
    
    glm::vec3 vTargetDecalPosition = m_pTargetDecal->Get_Position();
    vTargetDecalPosition.x = m_vPosition.x + sin(glm::radians(m_fTowerRotationY + m_vRotation.y)) * 6.0f;
    vTargetDecalPosition.z = m_vPosition.z + cos(-glm::radians(m_fTowerRotationY + m_vRotation.y)) * 6.0f;
    m_pTargetDecal->Set_Position(vTargetDecalPosition);
    
    m_pTrack->Update();
    m_pTower->Update();
    m_pChassis->Update();

    Set_Position(m_vPosition);
    _SmoothRotation();
    Set_Rotation(m_vRotation);
}










