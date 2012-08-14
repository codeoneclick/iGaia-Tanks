//
//  CGameInGameLevel.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameInGameLevel.h"
#include "CSceneMgr.h"
#include "CLandscapeEdges.h"

CGameInGameLevel::CGameInGameLevel(void)
{

}

CGameInGameLevel::~CGameInGameLevel(void)
{
    
}

void CGameInGameLevel::Load(void)
{
    m_pLandscape = (CLandscape*)CSceneMgr::Instance()->Add_LandscapeModel("landscape.mdl");
    m_pLandscape->Set_Texture("layer_01_diffuse.pvr", 0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  1, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    m_pLandscape->Set_Texture("layer_02_diffuse.pvr", 2, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    m_pLandscape->Set_Texture("layer_02_bump.pvr",    3, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    m_pLandscape->Set_Texture("layer_03_diffuse.pvr", 4, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  5, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_SIMPLE,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_REFLECTION,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_REFRACTION,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP,IResource::E_SHADER_LANDSCAPE_ND);
    CSceneMgr::Instance()->AddEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    m_pLandscape->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_pLandscape->Add_DelegateOwner(this);
    m_pLandscape->Set_RenderMode(CShader::E_RENDER_MODE_REFLECTION, true);
    m_pLandscape->Set_RenderMode(CShader::E_RENDER_MODE_REFRACTION, true);
    m_pLandscape->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    //m_pLandscape->Set_Scale(glm::vec3(2.0f, 2.0f, 2.0f));
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Create_Box2dWorld();
    
    INode* pLandscapeEdges = m_pLandscape->Get_LandscapeEdges();
    pLandscapeEdges->Set_Texture("layer_02_diffuse.pvr",  0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    pLandscapeEdges->Set_Texture("layer_03_normal.pvr",  1, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_MAIN);
    pLandscapeEdges->Set_Shader(CShader::E_RENDER_MODE_SIMPLE,IResource::E_SHADER_LANDSCAPE_EDGES);
    pLandscapeEdges->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    
    m_pOcean = static_cast<COcean*>(CSceneMgr::Instance()->Add_OceanModel("water"));
    m_pOcean->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_OCEAN);
    m_pOcean->Set_Texture("ocean_riple.pvr", 3, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    
    m_pGrass = (CGrass*)CSceneMgr::Instance()->Add_LandscapeGrassModel("grass");
    m_pGrass->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_GRASS);
    m_pGrass->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_GRASS_ND);
    m_pGrass->Set_Texture("mod_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    m_pGrass->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    CBuilding* pBuilding = new CBuilding();
    pBuilding->Load("building_06.mdl", "building.pvr");
    pBuilding->Set_Position(glm::vec3(12.0f, 0.0f, 12.0f));
    m_lBuildings.push_back(pBuilding);
    
    pBuilding = new CBuilding();
    pBuilding->Load("building_04.mdl", "building.pvr");
    pBuilding->Set_Position(glm::vec3(28.0f, 0.0f, 12.0f));
    m_lBuildings.push_back(pBuilding);
    
    pBuilding = new CBuilding();
    pBuilding->Load("building_05.mdl", "building.pvr");
    pBuilding->Set_Position(glm::vec3(12.0f, 0.0f, 28.0f));
    m_lBuildings.push_back(pBuilding);
    
    m_pSkyBox = (CSkyBox*)CSceneMgr::Instance()->Add_SkyBoxModel("skybox");
    m_pSkyBox->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_SKYBOX);
    m_pSkyBox->Set_Texture("clouds.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    
    
}

void CGameInGameLevel::Unload(void)
{
    CSceneMgr::Instance()->RemoveEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    IGameLevel::Unload();
}

void CGameInGameLevel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{

}

void CGameInGameLevel::Update(void)
{
    IGameLevel::Update();
}



