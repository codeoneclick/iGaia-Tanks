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

    CMesh* m_mesh;

    f32* m_heightmapData;

    CTexture* m_heightmapTexture;
    CTexture* m_splattingDiffuseTexture;
    CTexture* m_splattingNormalTexture;

    ui32 m_width;
    ui32 m_height;

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

    inline CMesh* Get_HeightmapMesh(void)
    {
        assert(m_mesh != nullptr);
        return m_mesh;
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
