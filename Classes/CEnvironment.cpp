//
//  СEnvironment.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 8/31/12.
//
//

#include "CEnvironment.h"
#include "CSceneMgr.h"

CEnvironment::CEnvironment(void)
{
    m_pHeightMapSetter = nullptr;
    m_pLandscape = nullptr;
    m_pLandscapeEdges = nullptr;
    m_pGrass = nullptr;
    m_pOcean = nullptr;
    m_pSkyBox = nullptr;
}

CEnvironment::~CEnvironment(void)
{
    SAFE_DELETE(m_pHeightMapSetter);
    SAFE_DELETE(m_pLandscape);
    SAFE_DELETE(m_pLandscapeEdges);
    SAFE_DELETE(m_pGrass);
    SAFE_DELETE(m_pOcean);
    SAFE_DELETE(m_pSkyBox);
    CSceneMgr::Instance()->Set_HeightMapSetterRef(nullptr);
}

void CEnvironment::Load(const std::string &_sName)
{
    m_pHeightMapSetter = new CHeightMapSetter();
    m_pHeightMapSetter->Load("", 64, 64, glm::vec2(2.0f, 2.0f));
    CSceneMgr::Instance()->Set_HeightMapSetterRef(m_pHeightMapSetter);
    
    m_pLandscape = CLandscape::Instance();

    m_pLandscape->Set_Texture("layer_01_diffuse.pvr", 0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  1, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
    m_pLandscape->Set_Texture("layer_02_diffuse.pvr", 2, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
    m_pLandscape->Set_Texture("layer_02_bump.pvr",    3, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
    m_pLandscape->Set_Texture("layer_03_diffuse.pvr", 4, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  5, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
   
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_SIMPLE,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_REFLECTION,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_REFRACTION,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP,IResource::E_SHADER_LANDSCAPE_ND);

    m_pLandscape->Set_RenderMode(CShader::E_RENDER_MODE_REFLECTION, true);
    m_pLandscape->Set_RenderMode(CShader::E_RENDER_MODE_REFRACTION, true);
    m_pLandscape->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_pLandscapeEdges = CLandscapeEdges::Instance();
    m_pLandscapeEdges->Set_Texture("layer_02_diffuse.pvr",  0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
    m_pLandscapeEdges->Set_Texture("layer_03_normal.pvr",  1, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_SYNC);
    m_pLandscapeEdges->Set_Shader(CShader::E_RENDER_MODE_SIMPLE,IResource::E_SHADER_LANDSCAPE_EDGES);
    
    m_pOcean = COcean::Instance();
    m_pOcean->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_OCEAN);
    m_pOcean->Set_Texture("ocean_riple.pvr", 3, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_ASYNC);
    
    m_pGrass = CGrass::Instance();
    m_pGrass->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_GRASS);
    m_pGrass->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_GRASS_ND);
    m_pGrass->Set_Texture("mod_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_ASYNC);
    m_pGrass->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_pSkyBox = CSkyBox::Instance();
    m_pSkyBox->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_SKYBOX);
    m_pSkyBox->Set_Texture("clouds.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
}

void CEnvironment::Update(void)
{
    m_pLandscape->Update();
    m_pLandscapeEdges->Update();
    m_pGrass->Update();
    m_pOcean->Update();
    m_pSkyBox->Update();
}
