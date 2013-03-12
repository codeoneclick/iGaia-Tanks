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
    m_mesh = nullptr;

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

    glm::vec3 maxBound = glm::vec3( -4096.0f, -4096.0f, -4096.0f );
    glm::vec3 minBound = glm::vec3(  4096.0f,  4096.0f,  4096.0f );

    CVertexBuffer* vertexBuffer = new CVertexBuffer(m_width * m_height, GL_DYNAMIC_DRAW);
    SVertex* vertexData = vertexBuffer->Lock();

    ui32 index = 0;
    for(ui32 i = 0; i < m_width; ++i)
    {
        for(ui32 j = 0; j < m_height; ++j)
        {
            vertexData[index].m_position.x = i;
            vertexData[index].m_position.y = m_heightmapData[i + j * m_height];
            vertexData[index].m_position.z = j;

            vertexData[index].m_texcoord.x = i / static_cast<f32>(m_width);
            vertexData[index].m_texcoord.y = j / static_cast<f32>(m_height);

            if(vertexData[index].m_position.x > maxBound.x)
            {
                maxBound.x = vertexData[index].m_position.x;
            }
            if(vertexData[index].m_position.y > maxBound.y)
            {
                maxBound.y = vertexData[index].m_position.y;
            }
            if(vertexData[index].m_position.z > maxBound.z)
            {
                maxBound.z = vertexData[index].m_position.z;
            }
            if(vertexData[index].m_position.x < minBound.x)
            {
                minBound.x = vertexData[index].m_position.x;
            }
            if(vertexData[index].m_position.y < minBound.y)
            {
                minBound.y = vertexData[index].m_position.y;
            }
            if(vertexData[index].m_position.z < minBound.z)
            {
                minBound.z = vertexData[index].m_position.z;
            }
            ++index;
        }
    }
    vertexBuffer->Unlock();

    CIndexBuffer* indexBuffer = new CIndexBuffer((m_width - 1) * (m_height - 1) * 6, GL_DYNAMIC_DRAW);
    ui16* indexData = indexBuffer->Lock();

    index = 0;
    for(ui32 i = 0; i < (m_width - 1); ++i)
    {
        for(ui32 j = 0; j < (m_height - 1); ++j)
        {
            indexData[index] = i + j * m_width;
            index++;
            indexData[index] = i + (j + 1) * m_width;
            index++;
            indexData[index] = i + 1 + j * m_width;
            index++;

            indexData[index] = i + (j + 1) * m_width;
            index++;
            indexData[index] = i + 1 + (j + 1) * m_width;
            index++;
            indexData[index] = i + 1 + j * m_width;
            index++;
        }
    }
    indexBuffer->Unlock();

    m_mesh = new CMesh(vertexBuffer, indexBuffer, maxBound, minBound);
}


