//
//  CShaderComposite.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShaderComposite.h"

#define STRINGIFY(A)  #A

#include "../Shaders/ShaderModel.frag"
#include "../Shaders/ShaderModel.vert"

#include "../Shaders/ShaderModelND.frag"
#include "../Shaders/ShaderModelND.vert"

#include "../Shaders/ShaderLandscape.frag"
#include "../Shaders/ShaderLandscape.vert"

#include "../Shaders/ShaderLandscapeND.frag"
#include "../Shaders/ShaderLandscapeND.vert"

#include "../Shaders/ShaderSkybox.frag"
#include "../Shaders/ShaderSkybox.vert"

#include "../Shaders/ShaderGrass.frag"
#include "../Shaders/ShaderGrass.vert"

#include "../Shaders/ShaderGrassND.frag"
#include "../Shaders/ShaderGrassND.vert"

#include "../Shaders/ShaderOcean.frag"
#include "../Shaders/ShaderOcean.vert"

#include "../Shaders/ShaderDecal.frag"
#include "../Shaders/ShaderDecal.vert"

#include "../Shaders/ShaderParticle.frag"
#include "../Shaders/ShaderParticle.vert"

#include "../Shaders/ShaderParticleND.frag"
#include "../Shaders/ShaderParticleND.vert"

#include "../Shaders/ShaderPostPlane.frag"
#include "../Shaders/ShaderPostPlane.vert"

#include "../Shaders/ShaderPostBloomExtract.frag"
#include "../Shaders/ShaderPostBloomExtract.vert"

#include "../Shaders/ShaderPostBloomCombine.frag"
#include "../Shaders/ShaderPostBloomCombine.vert"

#include "../Shaders/ShaderPostBlur.frag"
#include "../Shaders/ShaderPostBlur.vert"

#include "../Shaders/ShaderPostEdgeDetect.frag"
#include "../Shaders/ShaderPostEdgeDetect.vert"

#include "../Shaders/ShaderPostLandscapeDetail.frag"
#include "../Shaders/ShaderPostLandscapeDetail.vert"

CShaderComposite* CShaderComposite::m_pInstance = NULL;

CShaderComposite::CShaderComposite()
{
    CParser_GLSL *pParser = new CParser_GLSL(); 
    CParser_GLSL::SGLSLData pData;
    
    pData = pParser->Load(ShaderModelV, ShaderModelF);
    CShader* pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_MODEL] = pShader;
    
    pData = pParser->Load(ShaderModelNDV, ShaderModelNDF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_MODEL_ND] = pShader;
    
    pData = pParser->Load(ShaderLandscapeV, ShaderLandscapeF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_LANDSCAPE] = pShader;

    pData = pParser->Load(ShaderLandscapeNDV, ShaderLandscapeNDF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_LANDSCAPE_ND] = pShader;
    
    pData = pParser->Load(ShaderOceanV, ShaderOceanF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_OCEAN] = pShader;
    
    pData = pParser->Load(ShaderSkyboxV, ShaderSkyboxF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SKYBOX] = pShader;
    
    pData = pParser->Load(ShaderGrassV, ShaderGrassF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_GRASS] = pShader;
    
    pData = pParser->Load(ShaderGrassNDV, ShaderGrassNDF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_GRASS_ND] = pShader;
    
    pData = pParser->Load(ShaderDecalV, ShaderDecalF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_DECAL] = pShader;
    
    pData = pParser->Load(ShaderParticleV, ShaderParticleF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_PARTICLE] = pShader;
    
    pData = pParser->Load(ShaderParticleNDV, ShaderParticleNDF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_PARTICLE_ND] = pShader;
    
    pData = pParser->Load(ShaderPostPlaneV, ShaderPostPlaneF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SCREEN_PLANE] = pShader;
    
    pData = pParser->Load(ShaderPostBloomExtractV, ShaderPostBloomExtractF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SCREEN_PLANE_BLOOM_EXTRACT] = pShader;
    
    pData = pParser->Load(ShaderPostBloomCombineV, ShaderPostBloomCombineF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SCREEN_PLANE_BLOOM_COMBINE] = pShader;
    
    pData = pParser->Load(ShaderPostBlurV, ShaderPostBlurF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SCREEN_PLANE_BLUR] = pShader;
    
    pData = pParser->Load(ShaderPostEdgeDetectV, ShaderPostEdgeDetectF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SCREEN_PLANE_EDGE_DETECT] = pShader;
    
    pData = pParser->Load(ShaderPostLandscapeDetailV, ShaderPostLandscapeDetailF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SCREEN_PLANE_LANDSCAPE_DETAIL] = pShader;
}

CShaderComposite::~CShaderComposite()
{
    
}

CShaderComposite* CShaderComposite::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CShaderComposite();
    }
    return m_pInstance;
}

CShader* CShaderComposite::Get_Shader(IResource::E_SHADER _eShader)
{
    if( m_lContainer.find(_eShader) != m_lContainer.end())
    {
        return m_lContainer[_eShader];
    }
    else
    {
        return NULL;
    }
}