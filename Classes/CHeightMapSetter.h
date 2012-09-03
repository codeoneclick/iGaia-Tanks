//
//  CHeightMapSetter.h
//  iGaia
//
//  Created by sergey.sergeev on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CHeightMapSetter_h
#define iGaia_CHeightMapSetter_h

#include "CMesh.h"
#include "CTexture.h"

class CHeightMapSetter
{
protected:
    float* m_pHeightMapData;
    
    int m_iWidth;
    int m_iHeight;
    
    glm::vec2 m_vScaleFactor;
    
    float m_fXThreshold;
    float m_fZThreshold;
    
    GLuint m_hTextureSplatting;
    GLuint m_hTextureEdgesMask;
    GLuint m_hTextureHeightmap;
    
    GLuint m_hTextureDetailColor;
    GLuint m_hTextureDetailNormal;
    
    CMesh* m_pPostRenderScreenPlaneMesh;
    CShader* m_pPostRenderScreenPlaneShader;
    
    void _Create_TextureSplatting(void);
    void _Create_TextureEgdesMask(void);
    void _Create_TextureHeightmap(void);
    void _Create_TextureDetail(void);
    void _CalculateNormals(IVertexBuffer* _pVertexBuffer, CIndexBuffer* _pIndexBuffer);
    void _CalculateTangentsAndBinormals(IVertexBuffer* _pVertexBuffer, CIndexBuffer* _pIndexBuffer);
    void _CalculateTriangleBasis(const glm::vec3& E, const glm::vec3& F, const glm::vec3& G, float sE,
                                 float tE, float sF, float tF, float sG, float tG, glm::vec3& tangentX,
                                 glm::vec3& tangentY);
    glm::vec3 _ClosestPointOnLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
    glm::vec3 _Ortogonalize(const glm::vec3& v1, const glm::vec3& v2);
    
public:
    CHeightMapSetter(void);
    ~CHeightMapSetter(void);
    
    void Load(const std::string _sName, unsigned int _iWidth, unsigned int _iHeight, const glm::vec2& _vScaleFactor);
    CMesh* Get_HeightMapMesh(void);
    inline float* Get_HeightMapData(void) { return m_pHeightMapData; }
    
    inline int Get_Width(void) { return m_iWidth; }
    inline int Get_Height(void) { return m_iHeight; }
    inline glm::vec2 Get_ScaleFactor(void) { return m_vScaleFactor; }
    
    float Get_HeightValue(float _x, float _z);
    float Get_HeightValue(glm::vec2 _vPosition);
    float Get_HeightValue(glm::vec3 _vPosition);
    
    GLuint Get_TextureSplatting(void) { return m_hTextureSplatting; }
    GLuint Get_TextureHeightmap(void) { return m_hTextureHeightmap; }
    GLuint Get_TextureEdgesMask(void) { return m_hTextureEdgesMask; }
    
    GLuint Get_TextureDetailColor(void)   { return m_hTextureDetailColor; }
    GLuint Get_TextureDetailNormal(void)  { return m_hTextureDetailNormal; }

    void Update(void);
};

#endif
