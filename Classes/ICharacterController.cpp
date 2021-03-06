//
//  IGameUnit.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ICharacterController.h"
#include "CGameSceneMgr.h"
#include "CSceneMgr.h"
#include "CMathHelper.h"
#include "GameNativeCommunicationMgr.h"

ICharacterController::ICharacterController(void)
{
    m_eMoveState = E_CHARACTER_CONTROLLER_MOVE_STATE_NONE;
    m_eSteerState = E_CHARACTER_CONTROLLER_STEER_STATE_NONE;
    m_pTarget = NULL;
    m_eFullSetType = GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT;
    
    m_pNavigationHelper = new CNavigationHelper();
    m_pNavigationHelper->Set_MoveForwardSpeed(GameSDBStorage::Instance()->Get_UserMoveSpeed(m_eFullSetType));
    m_pNavigationHelper->Set_MoveBackwardSpeed(GameSDBStorage::Instance()->Get_UserMoveSpeed(m_eFullSetType));
    m_pNavigationHelper->Set_SteerSpeed(GameSDBStorage::Instance()->Get_UserSteerSpeed(m_eFullSetType));
    m_pNavigationHelper->Set_UseHeightMap(true);
    m_pNavigationHelper->Set_Owner(this);
}

ICharacterController::~ICharacterController(void)
{
    SAFE_DELETE(m_pChassis);
    SAFE_DELETE(m_pTower);
    SAFE_DELETE(m_pTrack);
    
    SAFE_DELETE(m_pNavigationHelper);
    
    CSceneMgr::Instance()->Get_DecalMgr()->Remove_Decal(m_pShadowDecal);
    CSceneMgr::Instance()->Get_DecalMgr()->Remove_Decal(m_pHealthDecal);

    m_pTarget = NULL;
}

void ICharacterController::Load(void)
{
    m_pShadowDecal = static_cast<CLandscapeDecal*>(CSceneMgr::Instance()->Get_DecalMgr()->Add_LandscapeDecal());
    m_pShadowDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pShadowDecal->Set_Texture("shadow.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pHealthDecal = static_cast<CLandscapeDecal*>(CSceneMgr::Instance()->Get_DecalMgr()->Add_LandscapeDecal());
    m_pHealthDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pHealthDecal->Set_Texture("ring.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    m_pHealthDecal->Set_Color(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

void ICharacterController::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pChassis != NULL)
    {
        m_pChassis->Set_Position(_vPosition);
    }
    
    if(m_pTrack != NULL)
    {
        m_pTrack->Set_Position(_vPosition);
    }
    
    if(m_pTower != NULL)
    {
        m_pTower->Set_Position(_vPosition);
    }
    
    if(m_pShadowDecal != NULL)
    {
        m_pShadowDecal->Set_Position(glm::vec3(_vPosition.x, 0.0f, _vPosition.z));
    }
    
    if(m_pHealthDecal != NULL)
    {
        m_pHealthDecal->Set_Position(glm::vec3(_vPosition.x, 0.0f, _vPosition.z));
    }
    
    m_vPosition = _vPosition;
    
    Set_Box2dPosition(m_vPosition);
    
    m_pNavigationHelper->Set_CurrentPosition(m_vPosition);
    
    if(GameNativeCommunicationMgr::Instance()->Get_GameClient() != NULL)
    {
        GameNativeCommunicationMgr::Instance()->Get_GameClient()->Send_Position(m_vPosition);
    }
}

void ICharacterController::_SmoothRotation(void)
{
    glm::vec3 vCurrentRotation = glm::vec3(0.0f, m_vRotation.y, 0.0f);
    glm::vec2 vRotationOnHeightMap = CMathHelper::Get_RotationOnHeightmap(m_vPosition);
    vCurrentRotation.x = -glm::degrees(vRotationOnHeightMap.x);
    vCurrentRotation.z =  glm::degrees(vRotationOnHeightMap.y);
    m_vRotation = glm::mix(m_vRotation, vCurrentRotation, 0.25f);
}

void ICharacterController::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pTrack != NULL)
    {
        m_pTrack->Set_Rotation(_vRotation);
    }
    
    if(m_pTower != NULL)
    {
        m_pTower->Set_Rotation(glm::vec3(_vRotation.x, m_fTowerRotationY + _vRotation.y, _vRotation.z));
    }
    
    if(m_pChassis != NULL)
    {
        m_pChassis->Set_Rotation(_vRotation);
    }
    
    if(m_pShadowDecal != NULL)
    {
        m_pShadowDecal->Set_Rotation(_vRotation);
    }
    
    if(m_pHealthDecal != NULL)
    {
        m_pHealthDecal->Set_Rotation(_vRotation);
    }

    m_vRotation = _vRotation;
    
    m_pNavigationHelper->Set_CurrentRotation(m_vRotation);
}

void ICharacterController::Shoot(void)
{
    if(m_pTower != NULL)
    {
        glm::vec3 vTowerGunOffset = m_pTower->Get_TowerGunOffset();
        float fTowerFullRotationY = m_vRotation.y + m_fTowerRotationY;
        CGameSceneMgr::Instance()->Get_Scene()->Get_GameShooterMgr()->CreateBullet(glm::vec3(m_vPosition.x + sinf(glm::radians(fTowerFullRotationY)) * vTowerGunOffset.x, m_vPosition.y + vTowerGunOffset.y, m_vPosition.z + cosf(glm::radians(fTowerFullRotationY)) * vTowerGunOffset.z), glm::vec3(m_vRotation.x, fTowerFullRotationY, m_vRotation.z), this);
    }
}

void ICharacterController::Set_Chassis(GameTankSDB::E_CHARACTER_PART_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_PART_TYPE_LIGHT :
        {
            SAFE_DELETE(m_pChassis);
            m_pChassis = new CTankLightBody();
            m_pChassis->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_PART_TYPE_MEDIUM :
        {
            SAFE_DELETE(m_pChassis);
            m_pChassis = new CTankMediumBody();
            m_pChassis->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_PART_TYPE_HEAVY :
        {
            SAFE_DELETE(m_pChassis);
            m_pChassis = new CTankHeavyBody();
            m_pChassis->Load();
        }
            break;
        default:
            break;
    }
}

void ICharacterController::Set_Tower(GameTankSDB::E_CHARACTER_PART_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_PART_TYPE_LIGHT :
        {
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankLightTower();
            m_pTower->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_PART_TYPE_MEDIUM :
        {
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankMediumTower();
            m_pTower->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_PART_TYPE_HEAVY :
        {
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankHeavyTower();
            m_pTower->Load();
        }
            break;
        default:
            break;
    }
}

void ICharacterController::Set_Track(GameTankSDB::E_CHARACTER_PART_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_PART_TYPE_LIGHT :
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankLightTrack();
            m_pTrack->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_PART_TYPE_MEDIUM :
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankMediumTrack();
            m_pTrack->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_PART_TYPE_HEAVY :
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankHeavyTrack();
            m_pTrack->Load();
        }
            break;
        default:
            break;
    }
}

void ICharacterController::Set_FullSet(GameTankSDB::E_CHARACTER_FULLSET_TYPE _eType)
{
    switch (_eType)
    {
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT:
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankLightTrack();
            m_pTrack->Load();
            
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankLightTower();
            m_pTower->Load();
            
            SAFE_DELETE(m_pChassis);
            m_pChassis = new CTankLightBody();
            m_pChassis->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_MEDIUM:
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankMediumTrack();
            m_pTrack->Load();
            
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankMediumTower();
            m_pTower->Load();
            
            SAFE_DELETE(m_pChassis);
            m_pChassis = new CTankMediumBody();
            m_pChassis->Load();
        }
            break;
        case GameTankSDB::E_CHARACTER_FULLSET_TYPE_HEAVY:
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankHeavyTrack();
            m_pTrack->Load();
            
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankHeavyTower();
            m_pTower->Load();
            
            SAFE_DELETE(m_pChassis);
            m_pChassis = new CTankHeavyBody();
            m_pChassis->Load();
        }
            break;
            
        default:
            break;
    }
    
    m_eFullSetType = _eType;
}

void ICharacterController::OnCollision(ICollisionDelegate *_pCollider)
{
    
}

void ICharacterController::OnBox2dPositionChanged(const glm::vec3& _vPosition)
{
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(_vPosition.x, _vPosition.z);
    m_vPosition.y = fHeight;
    m_vPosition.x = _vPosition.x;
    m_vPosition.z = _vPosition.z;
}

void ICharacterController::OnBox2dRotationChanged(float _fAngleY)
{
    m_vRotation.y = _fAngleY;
}










