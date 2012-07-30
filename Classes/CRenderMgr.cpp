//
//  CRenderMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CRenderMgr.h"

CRenderMgr::CRenderMgr(void)
{
    m_pScreenSpacePostMgr = new CScreenSpacePostMgr();
}

CRenderMgr::~CRenderMgr(void)
{
    
}

void CRenderMgr::BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode)
{
    m_pScreenSpacePostMgr->EnableOffScreenMode(_eMode);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CRenderMgr::EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode)
{
    m_pScreenSpacePostMgr->DisableOffScreenMode(_eMode);
}

void CRenderMgr::DrawResult(void)
{
    if(CSettings::g_bEdgeDetect)
    {
        m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_EDGE_DETECT);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        m_pScreenSpacePostMgr->Render_PostEdgeDetect();
        m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_EDGE_DETECT);
    }
    
    /*m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_EXTRACT);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomExtract();
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_EXTRACT);
    
    m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLUR);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBlur();
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLUR);
    
    m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_COMBINE);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomCombine();
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_COMBINE);*/
    
    m_pScreenSpacePostMgr->EnableScreenMode();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostSimple();
}





