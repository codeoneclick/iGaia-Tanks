//
//  CGameMainMenuScene.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#include "CGameMainMenuScene.h"
#include "CGameMainMenuLevel.h"
#include "CLightPoint.h"
#include "CMathHelper.h"

CGameMainMenuScene::CGameMainMenuScene(void)
{
    m_pCharaterControllerMgr = NULL;
    m_pMainCharacterController = NULL;
    m_pGameAIMgr = NULL;
    m_pGameShooterMgr = NULL;
}

CGameMainMenuScene::~CGameMainMenuScene(void)
{
    
}

void CGameMainMenuScene::Load(void)
{
    IGameScene::Load();
    
    m_pLevel = new CGameMainMenuLevel();
    m_pLevel->Load();
    
    CCharacterControllerEnemy* pEnemy = static_cast<CCharacterControllerEnemy*>(m_pCharaterControllerMgr->Add_EnemyCharacterController());
    pEnemy->Set_Position(glm::vec3(8.0f, 0.0f, 8.0f));
    m_pGameAIMgr->Add_AICharacterController(pEnemy);
    
    pEnemy = static_cast<CCharacterControllerEnemy*>(m_pCharaterControllerMgr->Add_EnemyCharacterController());
    pEnemy->Set_Position(glm::vec3(CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width() - 8.0f, 0.0f, 8.0f));
    m_pGameAIMgr->Add_AICharacterController(pEnemy);

    pEnemy = static_cast<CCharacterControllerEnemy*>(m_pCharaterControllerMgr->Add_EnemyCharacterController());
    pEnemy->Set_Position(glm::vec3(8.0f, 0.0f, CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height() - 8.0f));
    m_pGameAIMgr->Add_AICharacterController(pEnemy);
    
    m_pLight = CSceneMgr::Instance()->Get_Light(ILight::E_LIGHT_MODE_POINT, 0);
    m_pLight->Set_Position(glm::vec3(32.0f, 16.0f, 32.0f));
    m_pLight->Set_LightAt(glm::vec3(32.0f, 0.0f, 32.0f));
    static_cast<CLightPoint*>(m_pLight)->Set_Visible(true);
    CSceneMgr::Instance()->Set_GlobalLight(m_pLight);
    
    m_pMainCharacterController = pEnemy;
    
    m_pCamera = CSceneMgr::Instance()->CreateTargetCamera(45.0f, 0.25f, 128.0f, m_pMainCharacterController);
    CSceneMgr::Instance()->Set_Camera(m_pCamera);
    m_pCamera->Set_DistanceToLookAt(k_CAMERA_DISTANCE);
    m_pCamera->Set_HeightFromLookAt(k_CAMERA_HEIGHT);
}

void CGameMainMenuScene::Unload(void)
{
    IGameScene::Unload();
}

void CGameMainMenuScene::Update(void)
{
    IGameScene::Update();
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    
    float fCameraHeight = vCameraPosition.y;
    CHeightMapSetter* pMapSetter = CSceneMgr::Instance()->Get_HeightMapSetterRef();
    if(pMapSetter != NULL)
    {
        fCameraHeight = pMapSetter->Get_HeightValue(vCameraPosition.x, vCameraPosition.z);
    }
    
    if(pMapSetter != NULL && (vCameraPosition.x <= 0.0f || vCameraPosition.z <= 0.0f || vCameraPosition.x >= (pMapSetter->Get_Width() - 1.0f) || (vCameraPosition.z >= pMapSetter->Get_Height() - 1.0f)))
    {
        fCameraHeight = k_CAMERA_HEIGHT_OUT_MAP;
    }
    
    if(fCameraHeight < 0.0f)
    {
        fCameraHeight = 0.0f;
    }
    
    m_fNeedCameraHeight = k_CAMERA_HEIGHT + fCameraHeight;
    
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
}




