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

#include "../Shaders/ShaderLandscapeEdges.frag"
#include "../Shaders/ShaderLandscapeEdges.vert"

CShaderComposite* CShaderComposite::m_instance = nullptr;

CShaderComposite* CShaderComposite::Instance(void)
{
    if(m_instance == nullptr)
    {
        m_instance = new CShaderComposite();
    }
    return m_instance;
}

CShaderComposite::CShaderComposite(void)
{
    CParser_GLSL *parser = new CParser_GLSL();
    
    CShader* shader = parser->Load(ShaderModelV, ShaderModelF);
    m_shaders[CShader::E_SHADER_MODEL] = shader;
    
    shader = parser->Load(ShaderModelNDV, ShaderModelNDF);
    m_shaders[CShader::E_SHADER_MODEL_ND] = shader;
    
    shader = parser->Load(ShaderLandscapeV, ShaderLandscapeF);
    m_shaders[CShader::E_SHADER_LANDSCAPE] = shader;

    shader = parser->Load(ShaderLandscapeNDV, ShaderLandscapeNDF);
    m_shaders[CShader::E_SHADER_LANDSCAPE_ND] = shader;
    
    shader = parser->Load(ShaderOceanV, ShaderOceanF);
    m_shaders[CShader::E_SHADER_OCEAN] = shader;
    
    shader = parser->Load(ShaderSkyboxV, ShaderSkyboxF);
    m_shaders[CShader::E_SHADER_SKYBOX] = shader;
    
    shader = parser->Load(ShaderGrassV, ShaderGrassF);
    m_shaders[CShader::E_SHADER_GRASS] = shader;
    
    shader = parser->Load(ShaderGrassNDV, ShaderGrassNDF);
    m_shaders[CShader::E_SHADER_GRASS_ND] = shader;
    
    shader = parser->Load(ShaderDecalV, ShaderDecalF);
    m_shaders[CShader::E_SHADER_DECAL] = shader;
    
    shader = parser->Load(ShaderParticleV, ShaderParticleF);
    m_shaders[CShader::E_SHADER_PARTICLE] = shader;
    
    shader = parser->Load(ShaderParticleNDV, ShaderParticleNDF);
    m_shaders[CShader::E_SHADER_PARTICLE_ND] = shader;
    
    shader = parser->Load(ShaderPostPlaneV, ShaderPostPlaneF);
    m_shaders[CShader::E_SHADER_SCREEN_PLANE] = shader;
    
    shader = parser->Load(ShaderPostBloomExtractV, ShaderPostBloomExtractF);
    m_shaders[CShader::E_SHADER_SCREEN_PLANE_BLOOM_EXTRACT] = shader;
    
    shader = parser->Load(ShaderPostBloomCombineV, ShaderPostBloomCombineF);
    m_shaders[CShader::E_SHADER_SCREEN_PLANE_BLOOM_COMBINE] = shader;
    
    shader = parser->Load(ShaderPostBlurV, ShaderPostBlurF);
    m_shaders[CShader::E_SHADER_SCREEN_PLANE_BLUR] = shader;
    
    shader = parser->Load(ShaderPostEdgeDetectV, ShaderPostEdgeDetectF);
    m_shaders[CShader::E_SHADER_SCREEN_PLANE_EDGE_DETECT] = shader;
    
    shader = parser->Load(ShaderPostLandscapeDetailV, ShaderPostLandscapeDetailF);
    m_shaders[CShader::E_SHADER_SCREEN_PLANE_LANDSCAPE_DETAIL] = shader;
    
    shader = parser->Load(ShaderLandscapeEdgesV, ShaderLandscapeEdgesF);
    m_shaders[CShader::E_SHADER_LANDSCAPE_EDGES] = shader;
}

CShaderComposite::~CShaderComposite()
{
    
}

CShader* CShaderComposite::Get_Shader(CShader::E_SHADER _shader)
{
    if(m_shaders.find(_shader) != m_shaders.end())
    {
        return m_shaders[_shader];
    }
    else
    {
        return nullptr;
    }
}

