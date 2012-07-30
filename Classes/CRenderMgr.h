//
//  CRenderMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CRenderMgr_h
#define iGaia_CRenderMgr_h

#include "CScreenSpacePostMgr.h"
#include "CSettings.h"

class CRenderMgr
{
protected:
    CScreenSpacePostMgr* m_pScreenSpacePostMgr;
public:
    CRenderMgr();
    ~CRenderMgr();
    void DrawResult(void);
    void BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    void EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    GLuint Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode) { return m_pScreenSpacePostMgr->Get_OffScreenTexture(_eMode); }
};

#endif
