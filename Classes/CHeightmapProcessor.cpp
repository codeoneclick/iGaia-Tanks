//
//  CHeightmapProcessor.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CHeightmapProcessor.h"
#include "CObject3dBasisProcessor.h"
#include "CHeightmapHelper.h"

CHeightmapProcessor::CHeightmapProcessor(void)
{
    m_chunksContainer = nullptr;

    m_heightmapData = nullptr;

    m_heightmapTexture = nullptr;
    m_splattingTexture = nullptr;
    m_diffuseTexture = nullptr;
    m_normalTexture = nullptr;

    m_renderMgr = nullptr;
}

CHeightmapProcessor::~CHeightmapProcessor(void)
{
    
}

void CHeightmapProcessor::Process(const std::string& _heightmapFilename, const glm::vec2& _heightmapSize, const std::string& _splattingFilename, const glm::vec2& _splattingSize)
{
    m_width = static_cast<ui32>(_heightmapSize.x);
    m_height = static_cast<ui32>(_heightmapSize.y);

    m_heightmapData = new f32[m_width * m_height];

    m_maxAltitude = 0.0f;
    
    for(ui32 i = 0; i < m_width; ++i)
    {
        for(ui32 j = 0; j < m_height; ++j)
        {
            m_heightmapData[i + j * m_height] = (sin(i * 0.33f) / 2.0f + cos(j * 0.33f) / 2.0f);
            if(fabsf(m_heightmapData[i +j * m_height]) > m_maxAltitude)
            {
                m_maxAltitude = fabsf(m_heightmapData[i +j * m_height]);
            }
        }
    }
    
    m_chunkWidth = 32;
    m_chunkHeight = 32;
    
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
            CObject3dBasisProcessor::ProcessNormals(vertexBuffer, indexBuffer);
            CObject3dBasisProcessor::ProcessTangentsAndBinormals(vertexBuffer, indexBuffer);
            m_chunksContainer[i + j * m_numChunkRows] = new CMesh(vertexBuffer, indexBuffer, maxBound, minBound);
        }
    }
}

CTexture* CHeightmapProcessor::PreprocessHeightmapTexture(void)
{
    assert(m_heightmapTexture == nullptr);
    
    ui32 textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    ui16* data = new ui16[m_width * m_height];
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            f32 height = CHeightmapHelper::Get_HeightValue(m_heightmapData, m_width, m_height, glm::vec3(i , 0.0f, j)); 
            if(height > 0.0f || height < -1.0f)
            {
                data[i + j * m_height] = TO_RGB(0, static_cast<ui8>(255), 0);
            }
            else
            {
                data[i + j * m_height] = TO_RGB(static_cast<ui8>(fabsf(height) * 255), 0, 0);
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);

    CTexture* texture = new CTexture(textureHandle, m_width, m_height);
    texture->Set_WrapMode(GL_CLAMP_TO_EDGE);
    return texture;
}

CTexture* CHeightmapProcessor::PreprocessSplattingTexture(void)
{
    assert(m_splattingTexture == nullptr);
    
    ui32 textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    ui16* data = new ui16[m_width * m_height];
    
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            data[i + j * m_height] = TO_RGB(255, 0, 0);

            f32 height = CHeightmapHelper::Get_HeightValue(m_heightmapData, m_width, m_height, glm::vec3(i , 0.0f, j));
            
            if(height > 1.0f)
            {
                data[i + j * m_width] = TO_RGB(0, 255, 0);
            }
            if(height < 0.1f)
            {
                data[i + j * m_width] = TO_RGB(0, 0, 255);
            }

            if( i == 0 || j == 0 || i == (m_width - 1) || j == (m_height - 1))
            {
                data[i + j * m_width] = TO_RGB(255, 0, 0);
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);

    CTexture* texture = new CTexture(textureHandle, m_width, m_height);
    texture->Set_WrapMode(GL_CLAMP_TO_EDGE);
    return texture;
}

void CHeightmapProcessor::PreprocessTextures(void)
{
    m_heightmapTexture = PreprocessHeightmapTexture();
    m_splattingTexture = PreprocessSplattingTexture();
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
            
            vertexData[index].m_texcoord.x = static_cast<ui32>(position.x) / static_cast<f32>(m_width);
            vertexData[index].m_texcoord.y = static_cast<ui32>(position.y) / static_cast<f32>(m_height);
            
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



