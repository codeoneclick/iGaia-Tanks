//
//  CScreenSpacePostMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CScreenSpacePostMgr_h
#define iGaia_CScreenSpacePostMgr_h

#include "CShader.h"
class CMesh;

class CScreenSpacePostMgr
{
public:
    enum E_OFFSCREEN_MODE { E_OFFSCREEN_MODE_SIMPLE = 0, E_OFFSCREEN_MODE_REFLECTION, E_OFFSCREEN_MODE_REFRACTION, E_OFFSCREEN_MODE_EDGE_DETECT, E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP, E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_COLOR,E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_NORMAL, E_OFFSCREEN_MODE_MAX };
protected:
    static int k_REFLECTION_TEXTURE_SIZE;
    static int k_REFRACTION_TEXTURE_SIZE;
    
    static int k_LANDSCAPE_DETAIL_TEXTURE_SIZE;
    
    GLuint m_hOffScreenFBOs[E_OFFSCREEN_MODE_MAX];
    GLuint m_hOffScreenTextures[E_OFFSCREEN_MODE_MAX];
    GLuint m_hOffScreenDepthBuffers[E_OFFSCREEN_MODE_MAX];
    GLuint m_hOffScreenDepthTextures[E_OFFSCREEN_MODE_MAX];
    
    glm::vec2 m_pOffScreenSize[E_OFFSCREEN_MODE_MAX];
    glm::vec4 m_pOffScreenClearColor[E_OFFSCREEN_MODE_MAX];
    
    CShader* m_pPostShader[E_OFFSCREEN_MODE_MAX];
    CMesh* m_pMesh;
public:
    CScreenSpacePostMgr(void);
    ~CScreenSpacePostMgr(void);
    
    void EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    void DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    void EnableScreenMode(void);
    void DisableScreenMode(void);
    
    void Render_PostSimple(void);
    void Render_PostBloomExtract(void);
    void Render_PostBloomCombine(void);
    void Render_PostBlur(void);
    void Render_PostEdgeDetect(void);
    
    GLuint Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode) { return m_hOffScreenTextures[_eMode]; }
};

#endif