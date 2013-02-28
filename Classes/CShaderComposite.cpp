//
//  CShaderComposite.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "CShaderComposite.h"

#define STRING_SHADER(SHADER)  #SHADER

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

#include "CParser_GLSL.h"

CShaderComposite::CShaderComposite(void)
{
    CParser_GLSL *parser = new CParser_GLSL();
    SGLSLData data;
    
    data = parser->Load(ShaderModelV, ShaderModelF);
    CShader* shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_MODEL] = shader;
    
    data = parser->Load(ShaderModelNDV, ShaderModelNDF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_MODEL_ND] = shader;
    
    data = parser->Load(ShaderLandscapeV, ShaderLandscapeF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_LANDSCAPE] = shader;

    data = parser->Load(ShaderLandscapeNDV, ShaderLandscapeNDF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_LANDSCAPE_ND] = shader;
    
    data = parser->Load(ShaderOceanV, ShaderOceanF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_OCEAN] = shader;
    
    data = parser->Load(ShaderSkyboxV, ShaderSkyboxF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_SKYBOX] = shader;
    
    data = parser->Load(ShaderGrassV, ShaderGrassF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_GRASS] = shader;
    
    data = parser->Load(ShaderGrassNDV, ShaderGrassNDF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_GRASS_ND] = shader;
    
    data = parser->Load(ShaderDecalV, ShaderDecalF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_DECAL] = shader;
    
    data = parser->Load(ShaderParticleV, ShaderParticleF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_PARTICLE] = shader;
    
    data = parser->Load(ShaderParticleNDV, ShaderParticleNDF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_PARTICLE_ND] = shader;
    
    data = parser->Load(ShaderPostPlaneV, ShaderPostPlaneF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_SCREEN_PLANE] = shader;
    
    data = parser->Load(ShaderPostBloomExtractV, ShaderPostBloomExtractF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_SCREEN_PLANE_BLOOM_EXTRACT] = shader;
    
    data = parser->Load(ShaderPostBloomCombineV, ShaderPostBloomCombineF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_SCREEN_PLANE_BLOOM_COMBINE] = shader;
    
    data = parser->Load(ShaderPostBlurV, ShaderPostBlurF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_SCREEN_PLANE_BLUR] = shader;
    
    data = parser->Load(ShaderPostEdgeDetectV, ShaderPostEdgeDetectF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_SCREEN_PLANE_EDGE_DETECT] = shader;
    
    data = parser->Load(ShaderPostLandscapeDetailV, ShaderPostLandscapeDetailF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_SCREEN_PLANE_LANDSCAPE_DETAIL] = shader;
    
    data = parser->Load(ShaderLandscapeEdgesV, ShaderLandscapeEdgesF);
    shader = new CShader(data.m_linkedShaderHandle);
    m_shadersContainer[E_SHADER_LANDSCAPE_EDGES] = shader;
}

CShaderComposite::~CShaderComposite(void)
{
    
}

CShader* CShaderComposite::Get_Shader(E_SHADER _shader)
{
    if( m_shadersContainer.find(_shader) != m_shadersContainer.end())
    {
        return m_shadersContainer[_shader];
    }
    else
    {
        return nullptr;
    }
}

