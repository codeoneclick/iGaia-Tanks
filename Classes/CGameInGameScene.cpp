//
//  CGameInGameScene.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameInGameScene.h"
#include "CGameInGameLevel.h"
#include "CLightPoint.h"
#include "CMathHelper.h"

CGameInGameScene::CGameInGameScene(void)
{
    m_pCharaterControllerMgr = NULL;
    m_pGameAIMgr = NULL;
    m_eCameraMode = E_CAMERA_MODE_1;
    m_pGameShooterMgr = NULL;
}

CGameInGameScene::~CGameInGameScene(void)
{
    
}

void CGameInGameScene::Load(void)
{
    IGameScene::Load();
      
    m_pLevel = new CGameInGameLevel();
    m_pLevel->Load();
    
    m_pCharaterControllerMgr->Add_MainCharacterController();
    m_pMainCharacterController = static_cast<CCharacterControllerPlayer*>(m_pCharaterControllerMgr->Get_MainCharacterController());
    m_pMainCharacterController->Set_Position(glm::vec3(5.0f, 0.0f, 5.0f));
    
    CCharacterControllerEnemy* pEnemy = static_cast<CCharacterControllerEnemy*>(m_pCharaterControllerMgr->Add_EnemyCharacterController());
    pEnemy->Set_Position(glm::vec3(8.0f, 0.0f, 8.0f));
    m_pGameAIMgr->Add_AICharacterController(pEnemy);
    pEnemy->Set_Target(m_pMainCharacterController);
    
    /*pEnemy = static_cast<CCharacterControllerEnemy*>(m_pCharaterControllerMgr->Add_EnemyCharacterController());
    pEnemy->Set_Position(glm::vec3(CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width() - 8.0f, 0.0f, 8.0f));
    m_pGameAIMgr->Add_AICharacterController(pEnemy);
    pEnemy->Set_Target(m_pMainCharacterController);
    
    pEnemy = static_cast<CCharacterControllerEnemy*>(m_pCharaterControllerMgr->Add_EnemyCharacterController());
    pEnemy->Set_Position(glm::vec3(8.0f, 0.0f, CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height() - 8.0f));
    m_pGameAIMgr->Add_AICharacterController(pEnemy);
    pEnemy->Set_Target(m_pMainCharacterController);*/
    
    m_pLight = new CLightPoint();
    m_pLight->Set_Position(glm::vec3(32.0f, 16.0f, 32.0f));
    m_pLight->Set_LightAt(glm::vec3(32.0f, 0.0f, 32.0f));
    static_cast<CLightPoint*>(m_pLight)->Set_Visible(true);
    CSceneMgr::Instance()->Set_Light(m_pLight);
    
    m_pCamera = CSceneMgr::Instance()->CreateTargetCamera(45.0f, 0.25f, 128.0f, m_pMainCharacterController);
    CSceneMgr::Instance()->Set_Camera(m_pCamera);
    m_pCamera->Set_DistanceToLookAt(k_CAMERA_DISTANCE_MODE_1);
    m_pCamera->Set_HeightFromLookAt(k_CAMERA_HEIGHT_MODE_1);
    m_fNeedCameraHeight = k_CAMERA_HEIGHT_MODE_1;
    m_fCurrentCameraHeight = k_CAMERA_HEIGHT_MODE_1;
}

void CGameInGameScene::Unload(void)
{
    IGameScene::Unload();
}

void CGameInGameScene::SwitchCameraMode(CGameInGameScene::E_CAMERA_MODE _eCameraMode)
{
    m_eCameraMode = _eCameraMode;
}

void CGameInGameScene::SwitchCameraModeToNext(void)
{
    if(m_eCameraMode == E_CAMERA_MODE_1)
    {
        m_eCameraMode = E_CAMERA_MODE_2;
    }
    else
    {
        m_eCameraMode = E_CAMERA_MODE_1;
    }
}

void CGameInGameScene::Update(void)
{
    IGameScene::Update();
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    float fCameraHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(vCameraPosition.x, vCameraPosition.z);
    if(vCameraPosition.x <= 0.0f || vCameraPosition.z <= 0.0f || vCameraPosition.x >= (CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width() - 1.0f) || (vCameraPosition.z >= CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height() - 1.0f))
    {
         fCameraHeight = k_CAMERA_HEIGHT_OUT_MAP;
    }
    
    if(fCameraHeight < 0.0f)
    {
        fCameraHeight = 0.0f;
    }
    
    if(m_eCameraMode == E_CAMERA_MODE_1)
    {
        m_fNeedCameraHeight = k_CAMERA_HEIGHT_MODE_1 + fCameraHeight;
    }
    else if(m_eCameraMode == E_CAMERA_MODE_2)
    {
        m_fNeedCameraHeight = k_CAMERA_HEIGHT_MODE_2 + fCameraHeight;
    }
    
    m_fCurrentCameraHeight = vCameraPosition.y;
    
    if(!CMathHelper::Instance()->IsFloatEqualWithDelta(m_fCurrentCameraHeight, m_fNeedCameraHeight, k_CAMERA_DISPLACE_INC * 1.33f) && m_fCurrentCameraHeight > m_fNeedCameraHeight)
    {
        m_fCurrentCameraHeight -= std::fabs(m_fCurrentCameraHeight - m_fNeedCameraHeight) * 0.1f;
    }
    else if(!CMathHelper::Instance()->IsFloatEqualWithDelta(m_fCurrentCameraHeight, m_fNeedCameraHeight, k_CAMERA_DISPLACE_INC * 1.33f) && m_fCurrentCameraHeight < m_fNeedCameraHeight)
    {
         m_fCurrentCameraHeight += std::fabs(m_fCurrentCameraHeight - m_fNeedCameraHeight) * 0.1f;
    }
    
    m_pCamera->Set_HeightFromLookAt(m_fCurrentCameraHeight);
    
    glm::vec3 vCurrentCameraRotation = m_pCamera->Get_Rotation();
    vCurrentCameraRotation.y = glm::radians(m_pMainCharacterController->Get_Rotation().y) - CMathHelper::k_HALF_PI;
    glm::vec3 vOldCameraRotation = m_pCamera->Get_Rotation();
    glm::vec3 vCameraRotation = glm::mix(vOldCameraRotation, vCurrentCameraRotation, k_CAMERA_ROTATION_LERP);
    m_pCamera->Set_Rotation(vCameraRotation);
}





