//
//  CHeightmapProcessor.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CHeightmapProcessor_h
#define CHeightmapProcessor_h

#include "HCommon.h"
#include "CMesh.h"
#include "CTexture.h"

class CHeightmapProcessor
{
private:

protected:

    f32* m_heightmapData;

    CTexture* m_heightmapTexture;
    CTexture* m_splattingDiffuseTexture;
    CTexture* m_splattingNormalTexture;

    ui32 m_width;
    ui32 m_height;
    
    ui32 m_chunkWidth;
    ui32 m_chunkHeight;
    
    ui32 m_numChunkRows;
    ui32 m_numChunkCells;
    
    CMesh** m_chunksContainer;
    
    CIndexBuffer* CreateIndexBuffer(void);
    CVertexBuffer* CreateVertexBuffer(ui32 _widthOffset, ui32 _heightOffset, ui32 _numVertexes, GLenum _mode, glm::vec3* _maxBound, glm::vec3* _minBound);

public:

    CHeightmapProcessor(void);
    ~CHeightmapProcessor(void);

    void Process(const std::string& _heightmapFilename, const glm::vec2& _heightmapSize, const std::string& _splattingFilename, const glm::vec2& _splattingSize);

    inline ui32 Get_Width(void)
    {
        return m_width;
    };

    inline ui32 Get_Height(void)
    {
        return m_height;
    };

    inline CMesh* Get_Chunk(ui32 _i, ui32 _j)
    {
        assert(m_chunksContainer != nullptr);
        assert(m_chunksContainer[_i + _j * m_numChunkRows] != nullptr);
        return m_chunksContainer[_i + _j * m_numChunkRows];
    };
    
    inline ui32 Get_NumChunkRows(void)
    {
        return m_numChunkRows;
    };
    
    inline ui32 Get_NumChunkCells(void)
    {
        return m_numChunkCells;
    };
    
    inline ui32 Get_ChunkWidth(void)
    {
        return m_chunkWidth;
    };
    
    inline ui32 Get_ChunkHeight(void)
    {
        return m_chunkHeight;
    };
    
    inline f32* Get_HeightmapData(void)
    {
        assert(m_heightmapData != nullptr);
        return m_heightmapData;
    };

    CTexture* Get_HeightmapTexture(void)
    {
        assert(m_heightmapTexture);
        return m_heightmapTexture;
    };
    
    CTexture* Get_SplattingDiffuseTexture(void)
    {
        assert(m_splattingDiffuseTexture);
        return m_splattingDiffuseTexture;
    };
    
    CTexture* Get_SplattingNormalTexture(void)
    {
        assert(m_splattingNormalTexture);
        return m_splattingNormalTexture;
    };

};

#endif 
