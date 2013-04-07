//
//  CGameMainMenuScene.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "CGameMainMenuScene.h"
#include "CMainLoop.h"
#include "CPanzer.h"
#include "CCommon.h"
#include "CCollisionNavigator.h"

CGameMainMenuScene::CGameMainMenuScene(void)
{
    m_camera = nullptr;
    m_light = nullptr;
    m_buildingQuest = nullptr;
    m_particleEmitter = nullptr;
    m_landscape = nullptr;
    m_ocean = nullptr;
    m_characterController = nullptr;

    m_gameSettingsMgr = new CGameSettingsMgr();
}

CGameMainMenuScene::~CGameMainMenuScene(void)
{

}

void CGameMainMenuScene::Load(IRoot* _root)
{
	m_camera = _root->CreateCamera(60.0f,
                                   0.1f,
                                   256.0f,
                                   glm::vec4(0.0f, 0.0f, Get_ScreenWidth(), Get_ScreenHeight()));
    _root->Set_Camera(m_camera);
    m_camera->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_camera->Set_LookAt(glm::vec3(16.0f, 0.0f, 16.0f));
    m_camera->Set_Distance(4.0f);
    m_camera->Set_Height(2.0f);

    m_light = _root->CreateLight();
    m_light->Set_Position(glm::vec3(32.0f, 128.0f, 32.0f));
    _root->Set_Light(m_light);

    m_particleEmitter = _root->CreateParticleEmitter("particle_emitter_01.xml");
    _root->InsertParticleEmitter(m_particleEmitter);
    m_particleEmitter->Set_Position(glm::vec3(16.0f, 4.0f, 16.0f));

    m_landscape = _root->CreateLandscape("landscape_01.xml");
    _root->Set_Landscape(m_landscape);

    m_ocean = _root->CreateOcean("ocean_01.xml");
    _root->Set_Ocean(m_ocean);

    assert(m_gameSettingsMgr != nullptr);
    SPanzerSettings* mainPanzerSettings = m_gameSettingsMgr->Get_PanzerSettings("panzer_light_settings.xml");
    assert(mainPanzerSettings != nullptr);
    
    CPanzer* mainPanzer = new CPanzer();
    mainPanzer->Load(_root, mainPanzerSettings);
    
    SBuildingSettings* buildingQuestSettings = m_gameSettingsMgr->Get_BuildingSettigns("building_quest.xml");
    assert(buildingQuestSettings != nullptr);
    m_buildingQuest = new CBuilding();
    m_buildingQuest->Load(_root, buildingQuestSettings);
    _root->InsertCollider(m_buildingQuest, false);
    m_buildingQuest->Set_Position(glm::vec3(16.0f, 2.0f, 16.0f));

    CLandscapeDecal* mainPanzerShadow = _root->CreateLandscapeDecal("landscape_decal_01.xml");
    _root->InsertLandscapeDecal(mainPanzerShadow);

    m_characterController = new CCharacterController();
    m_characterController->Set_Camera(m_camera);
    m_characterController->Set_Character(mainPanzer);
    m_characterController->Set_Shadow(mainPanzerShadow);
    m_characterController->Set_LookAtHeight(1.4f);

	CCollisionNavigator* navigator = new CCollisionNavigator(
                                                             0.3f,
                                                             0.15f,
                                                             0.0f,
                                                             0.025f,
                                                             m_landscape->Get_HeightmapData(),
                                                             m_landscape->Get_HeightmapWidth(),
                                                             m_landscape->Get_HeightmapHeight(),
                                                             glm::vec3(1.5f, 1.5f, 1.5f),
                                                             glm::vec3(-1.5f, -1.5f, -1.5f));

    _root->InsertCollider(navigator, false);
	navigator->Set_Position(glm::vec3(4.0f, 0.0f, 4.0f));
    navigator->Set_Rotation(glm::vec3(0.0f, 0.0f, 0.0f));

	m_characterController->Set_Navigator(navigator);
    ConnectToMainLoop(m_characterController);
}
