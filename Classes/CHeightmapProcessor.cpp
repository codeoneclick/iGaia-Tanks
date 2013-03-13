//
//  CHeightmapProcessor.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CHeightmapProcessor.h"

CHeightmapProcessor::CHeightmapProcessor(void)
{
    m_chunksContainer = nullptr;

    m_heightmapData = nullptr;

    m_heightmapTexture = nullptr;
    m_splattingDiffuseTexture = nullptr;
    m_splattingNormalTexture = nullptr;
}

CHeightmapProcessor::~CHeightmapProcessor(void)
{
    
}

void CHeightmapProcessor::Process(const std::string& _heightmapFilename, const glm::vec2& _heightmapSize, const std::string& _splattingFilename, const glm::vec2& _splattingSize)
{
    m_width = static_cast<ui32>(_heightmapSize.x);
    m_height = static_cast<ui32>(_heightmapSize.y);

    m_heightmapData = new f32[m_width * m_height];
    f32 maxAltitude = 0.0f;
    
    for(ui32 i = 0; i < m_width; ++i)
    {
        for(ui32 j = 0; j < m_height; ++j)
        {
            m_heightmapData[i + j * m_height] = (sin(i * 0.33f) / 2.0f + cos(j * 0.33f) / 2.0f);
            if(fabsf(m_heightmapData[i +j * m_height]) > maxAltitude)
            {
                maxAltitude = fabsf(m_heightmapData[i +j * m_height]);
            }
        }
    }
    
    m_chunkWidth = 64;
    m_chunkHeight = 64;
    
    m_numChunkRows = m_width / m_chunkWidth;
    m_numChunkCells = m_height / m_chunkHeight;
    
    m_chunksContainer = new CMesh*[m_numChunkRows * m_numChunkCells];
    
    for(ui32 i = 0; i < m_numChunkRows; ++i)
    {
        for(ui32 j = 0; j < m_numChunkCells; ++j)
        {
            glm::vec3 maxBound = glm::vec3( -4096.0f, -4096.0f, -4096.0f );
            glm::vec3 minBound = glm::vec3(  4096.0f,  4096.0f,  4096.0f );
            
            CVertexBuffer* vertexBuffer = CreateVertexBuffer(i, j, m_chunkWidth * m_chunkHeight, GL_STATIC_DRAW, &maxBound, &minBound);
            CIndexBuffer* indexBuffer = CreateIndexBuffer();
            m_chunksContainer[i + j * m_numChunkRows] = new CMesh(vertexBuffer, indexBuffer, maxBound, minBound);
        }
    }
}

CIndexBuffer* CHeightmapProcessor::CreateIndexBuffer(void)
{
    assert(m_chunkWidth != 0);
    assert(m_chunkHeight != 0);
    
    CIndexBuffer* indexBuffer = new CIndexBuffer((m_chunkWidth - 1) * (m_chunkHeight - 1) * 6, GL_DYNAMIC_DRAW);
    ui16* indexData = indexBuffer->Lock();
    
    ui32 index = 0;
    for(ui32 i = 0; i < (m_chunkWidth - 1); ++i)
    {
        for(ui32 j = 0; j < (m_chunkHeight - 1); ++j)
        {
            indexData[index] = i + j * m_chunkWidth;
            index++;
            indexData[index] = i + (j + 1) * m_chunkWidth;
            index++;
            indexData[index] = i + 1 + j * m_chunkWidth;
            index++;
            
            indexData[index] = i + (j + 1) * m_chunkWidth;
            index++;
            indexData[index] = i + 1 + (j + 1) * m_chunkWidth;
            index++;
            indexData[index] = i + 1 + j * m_chunkWidth;
            index++;
        }
    }
    indexBuffer->Unlock();
    return indexBuffer;
}

CVertexBuffer* CHeightmapProcessor::CreateVertexBuffer(ui32 _widthOffset, ui32 _heightOffset, ui32 _numVertexes, GLenum _mode, glm::vec3 *_maxBound, glm::vec3 *_minBound)
{
    assert(m_heightmapData != nullptr);
    assert(m_chunkWidth != 0);
    assert(m_chunkHeight != 0);
    
    CVertexBuffer* vertexBuffer = new CVertexBuffer(_numVertexes, _mode);
    SVertex* vertexData = vertexBuffer->Lock();
    
    ui32 index = 0;
    for(ui32 i = 0; i < m_chunkWidth;++i)
    {
        for(ui32 j = 0; j < m_chunkHeight;++j)
        {
            glm::vec2 position = glm::vec2(i + _widthOffset * m_chunkWidth - _widthOffset, j + _heightOffset * m_chunkHeight - _heightOffset);
            
            vertexData[index].m_position.x = position.x;
            vertexData[index].m_position.y = m_heightmapData[static_cast<ui32>(position.x) + static_cast<ui32>(position.y) * m_height];
            vertexData[index].m_position.z = position.y;
            
            vertexData[index].m_texcoord.x = i / static_cast<f32>(m_width);
            vertexData[index].m_texcoord.y = j / static_cast<f32>(m_height);
            
            if(vertexData[index].m_position.x > _maxBound->x)
            {
                _maxBound->x = vertexData[index].m_position.x;
            }
            if(vertexData[index].m_position.y > _maxBound->y)
            {
                _maxBound->y = vertexData[index].m_position.y;
            }
            if(vertexData[index].m_position.z > _maxBound->z)
            {
                _maxBound->z = vertexData[index].m_position.z;
            }
            if(vertexData[index].m_position.x < _minBound->x)
            {
                _minBound->x = vertexData[index].m_position.x;
            }
            if(vertexData[index].m_position.y < _minBound->y)
            {
                _minBound->y = vertexData[index].m_position.y;
            }
            if(vertexData[index].m_position.z < _minBound->z)
            {
                _minBound->z = vertexData[index].m_position.z;
            }
            ++index;
        }
    }
    vertexBuffer->Unlock();
    return vertexBuffer;
}



