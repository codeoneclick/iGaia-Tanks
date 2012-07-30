//
//  CGameMainMenuLevel.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#include "CGameMainMenuLevel.h"
#include "CSceneMgr.h"

CGameMainMenuLevel::CGameMainMenuLevel(void)
{
    
}

CGameMainMenuLevel::~CGameMainMenuLevel(void)
{
    
}

void CGameMainMenuLevel::Load(void)
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
    
    m_pOcean = (CWater*)CSceneMgr::Instance()->Add_OceanModel("water");
    m_pOcean->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_OCEAN);
    m_pOcean->Set_Texture("ocean_riple.pvr", 3, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    
    m_pGrass = (CGrass*)CSceneMgr::Instance()->Add_LandscapeGrassModel("grass");
    m_pGrass->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_GRASS);
    m_pGrass->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_GRASS_ND);
    m_pGrass->Set_Texture("mod_02.pvr", 0, CTexture::E_WRAP_MODE_CLAMP, IResource::E_THREAD_BACKGROUND);
    m_pGrass->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_pSkyBox = (CSkyBox*)CSceneMgr::Instance()->Add_SkyBoxModel("skybox");
    m_pSkyBox->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_SKYBOX);
    m_pSkyBox->Set_Texture("clouds.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
}

void CGameMainMenuLevel::Unload(void)
{
    CSceneMgr::Instance()->RemoveEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    IGameLevel::Unload();
}

void CGameMainMenuLevel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    
}

void CGameMainMenuLevel::Update(void)
{
    
}


