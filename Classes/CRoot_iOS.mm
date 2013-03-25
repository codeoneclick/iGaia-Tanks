//
//  CRoot_iOS.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>

#include "CRoot.h"
#include "CGLContext_iOS.h"
#include "CMainLoop.h"

CRoot::CRoot(void* _glView)
{
    UIView* glView = (__bridge UIView*)_glView;
    assert([[glView layer] isKindOfClass:[CAEAGLLayer class]]);
    m_glContext = new CGLContext_iOS(static_cast<CAEAGLLayer*>(glView.layer));
    
    m_renderMgr = new CRenderMgr(m_glContext);
    m_updateMgr = new CSceneUpdateMgr();
    m_collisionMgr = new CCollisionMgr();
    
    m_shaderComposite = m_renderMgr->Get_ShaderComposite();
    
    ConnectToMainLoop(m_renderMgr);
    ConnectToMainLoop(m_updateMgr);
    ConnectToMainLoop(m_collisionMgr);
}

CRoot::~CRoot(void)
{
    
}