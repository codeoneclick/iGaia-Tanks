//
//  СEnvironment.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 8/31/12.
//
//

#include "СEnvironment.h"

CEnviroment::CEnviroment(void)
{
    m_pHeightMapSetter = nullptr;
    m_pLandscape = nullptr;
    m_pLandscapeEdges = nullptr;
    m_pGrass = nullptr;
    m_pOcean = nullptr;
    m_pSkyBox = nullptr;
}

CEnviroment::~CEnviroment(void)
{
    SAFE_DELETE(m_pHeightMapSetter);
    SAFE_DELETE(m_pLandscape);
    SAFE_DELETE(m_pLandscapeEdges);
    SAFE_DELETE(m_pGrass);
    SAFE_DELETE(m_pOcean);
    SAFE_DELETE(m_pSkyBox);
}

void CEnviroment::Load(const std::string &_sName)
{
    
}

void CEnviroment::Update(void)
{
    
}

void CEnviroment::Render(CShader::E_RENDER_MODE _eMode)
{
    
}