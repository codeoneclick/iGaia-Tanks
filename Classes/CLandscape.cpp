//
//  CLandscape.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CLandscape.h"

CLandscape::CLandscape(void)
{
    m_heightmapProcessor = new CHeightmapProcessor();
}

CLandscape::~CLandscape(void)
{

}

void CLandscape::Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename)
{
    assert(_resourceMgrsFacade != nullptr);
    SLandscapeSettings* settings = _resourceMgrsFacade->LoadLandscapeSettings(_filename);
    assert(settings != nullptr);

    assert(m_heightmapProcessor != nullptr);
    m_heightmapProcessor->Process(settings->m_heightmapDataFileName, glm::vec2(settings->m_width, settings->m_height), settings->m_splattingDataFileName, glm::vec2(settings->m_width, settings->m_height));

    std::vector<const SMaterialSettings*> m_materialsSettings = settings->m_materialsSettings;
    for(const SMaterialSettings* materialSettings : m_materialsSettings)
    {
        assert(materialSettings->m_renderMode < E_RENDER_MODE_WORLD_SPACE_MAX && materialSettings->m_renderMode >= 0);
        assert(m_materials[materialSettings->m_renderMode] == nullptr);

        const SShaderSettings* shaderSettings = materialSettings->m_shaderSettings;

        assert(shaderSettings->m_guid >= 0 && shaderSettings->m_guid < E_SHADER_MAX);

        CShader* shader = _shaderComposite->Get_Shader(static_cast<E_SHADER>(shaderSettings->m_guid));
        m_materials[materialSettings->m_renderMode] = new CMaterial(shader);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_CULL_MODE, materialSettings->m_isCullFace);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_DEPTH_TEST, materialSettings->m_isDepthTest);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_DEPTH_MASK, materialSettings->m_isDepthMask);
        m_materials[materialSettings->m_renderMode]->Set_RenderState(E_RENDER_STATE_BLEND_MODE, materialSettings->m_isBlend);

        m_materials[materialSettings->m_renderMode]->Set_CullFaceMode(materialSettings->m_cullFaceMode);
        m_materials[materialSettings->m_renderMode]->Set_BlendFunctionSource(materialSettings->m_blendFunctionSource);
        m_materials[materialSettings->m_renderMode]->Set_BlendFunctionDest(materialSettings->m_blendFunctionDestination);

        for(const STextureSettings* textureSettings : materialSettings->m_texturesSettings)
        {
            CTexture* texture = _resourceMgrsFacade->LoadTexture(textureSettings->m_name);
            texture->Set_WrapMode(textureSettings->m_wrap);
            assert(texture != nullptr);
            assert(textureSettings->m_slot >= 0 && textureSettings->m_slot < E_TEXTURE_SLOT_MAX);
            m_materials[materialSettings->m_renderMode]->Set_Texture(texture, static_cast<E_TEXTURE_SLOT>(textureSettings->m_slot));
        }
    }
    
    m_numChunkRows = m_heightmapProcessor->Get_NumChunkRows();
    m_numChunkCells = m_heightmapProcessor->Get_NumChunkCells();
    
    ui32 chunkWidth = m_heightmapProcessor->Get_ChunkWidth();
    ui32 chunkHeight = m_heightmapProcessor->Get_ChunkHeight();
    
    m_landscapeContainer = new CLandscapeChunk*[m_numChunkRows * m_numChunkCells];
    
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            CMesh* mesh = m_heightmapProcessor->Get_Chunk(i, j);
            m_landscapeContainer[i + j * m_numChunkRows] = new CLandscapeChunk();
            m_landscapeContainer[i + j * m_numChunkRows]->Load(mesh, m_materials, chunkWidth, chunkHeight);
        }
    }

}

void CLandscape::Set_Camera(CCamera* _camera)
{
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            assert(m_landscapeContainer != nullptr);
            assert(m_landscapeContainer[i + j * m_numChunkRows] != nullptr);
            m_landscapeContainer[i + j * m_numChunkRows]->Set_Camera(_camera);
        }
    }
}

void CLandscape::Set_Light(CLight* _light)
{
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            assert(m_landscapeContainer != nullptr);
            assert(m_landscapeContainer[i + j * m_numChunkRows] != nullptr);
            m_landscapeContainer[i + j * m_numChunkRows]->Set_Light(_light);
        }
    }
}

void CLandscape::OnResourceDidLoad(IResource_INTERFACE* _resource)
{
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            assert(m_landscapeContainer != nullptr);
            assert(m_landscapeContainer[i + j * m_numChunkRows] != nullptr);
            m_landscapeContainer[i + j * m_numChunkRows]->OnResourceDidLoad(_resource);
        }
    }
}

void CLandscape::OnUpdate(f32 _deltatime)
{
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            assert(m_landscapeContainer != nullptr);
            assert(m_landscapeContainer[i + j * m_numChunkRows] != nullptr);
            m_landscapeContainer[i + j * m_numChunkRows]->OnUpdate(_deltatime);
        }
    }
}

ui32 CLandscape::OnDrawIndex(void)
{
    return 1;
}

void CLandscape::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            assert(m_landscapeContainer != nullptr);
            assert(m_landscapeContainer[i + j * m_numChunkRows] != nullptr);
            m_landscapeContainer[i + j * m_numChunkRows]->OnBind(_mode);
        }
    }
}

void CLandscape::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_materials[_mode] != nullptr);
    
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            assert(m_landscapeContainer != nullptr);
            assert(m_landscapeContainer[i + j * m_numChunkRows] != nullptr);
            m_landscapeContainer[i + j * m_numChunkRows]->OnDraw(_mode);
        }
    }
}

void CLandscape::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            assert(m_landscapeContainer != nullptr);
            assert(m_landscapeContainer[i + j * m_numChunkRows] != nullptr);
            m_landscapeContainer[i + j * m_numChunkRows]->OnUnbind(_mode);
        }
    }
}



