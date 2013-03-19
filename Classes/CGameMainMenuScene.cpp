//
//  CGameMainMenuScene.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "CGameMainMenuScene.h"
#include "CMainLoop_iOS.h"

CGameMainMenuScene::CGameMainMenuScene(void)
{
    m_camera = nullptr;
    m_light = nullptr;
    m_shape3d = nullptr;
    m_landscape = nullptr;
    m_ocean = nullptr;
    m_characterController = nullptr;
}

CGameMainMenuScene::~CGameMainMenuScene(void)
{

}

void CGameMainMenuScene::Load(CRoot_iOS* _root)
{
    m_camera = _root->CreateCamera(45.0f, 0.1f, 1000.0f, glm::vec4(0.0f, 0.0f, 480.0f, 320.0f));
    _root->Set_Camera(m_camera);
    m_camera->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_camera->Set_LookAt(glm::vec3(16.0f, 0.0f, 16.0f));
    m_camera->Set_Distance(128.0f);
    m_camera->Set_Height(128.0f);

    m_light = _root->CreateLight();
    m_light->Set_Position(glm::vec3(32.0f, 128.0f, 32.0f));
    _root->Set_Light(m_light);

    m_shape3d = _root->CreateShape3d("building_01.xml");
    _root->InsertShape3d(m_shape3d);
    m_shape3d->Set_Position(glm::vec3(16.0f, 0.0f, 16.0f));

    m_landscape = _root->CreateLandscape("landscape_01.xml");
    _root->Set_Landscape(m_landscape);

    m_ocean = _root->CreateOcean("ocean_01.xml");
    _root->Set_Ocean(m_ocean);

    m_characterController = new CCharacterController();
    m_characterController->Set_Camera(m_camera);
    m_characterController->Set_Character(m_shape3d);
    m_characterController->Get_Navigator()->Set_Heightmap(m_landscape->Get_HeightmapData(), m_landscape->Get_HeightmapWidth(), m_landscape->Get_HeightmapHeight());
    ConnectToMainLoop(m_characterController);
}



