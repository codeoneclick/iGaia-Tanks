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
#include "CInputContext.h"
#include "CMainLoop.h"

CRoot::CRoot(void* _glWindow)
{
    UIView* glWindow = (__bridge UIView*)_glWindow;
    assert([[glWindow layer] isKindOfClass:[CAEAGLLayer class]]);
    m_glContext = new CGLContext_iOS(static_cast<CAEAGLLayer*>(glWindow.layer));
    
    m_renderMgr = new CRenderMgr(m_glContext);
    m_shaderComposite = m_renderMgr->Get_ShaderComposite();

    m_inputContext = new CInputContext((__bridge void*)glWindow);

    m_updateMgr = new CSceneUpdateMgr();
    m_collisionMgr = new CCollisionMgr();
    
    m_guiMgr = new CGuiMgr();
    m_guiMgr->Set_ShaderComposite(m_shaderComposite);
    m_guiMgr->Set_ResourceMgrFacade(m_resourceMgrsFacade);
	m_guiMgr->TEMP();
    m_inputContext->AddTapRecognizerListener(m_guiMgr);
    
    m_renderMgr->AddRenderPresentEventListener(m_guiMgr);
    
    ConnectToMainLoop(m_renderMgr);
    ConnectToMainLoop(m_updateMgr);
    ConnectToMainLoop(m_collisionMgr);
}

CRoot::~CRoot(void)
{
    
}

void CRoot::AddTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE *_listener)
{
    assert(m_inputContext != nullptr);
    m_inputContext->AddTapRecognizerListener(_listener);
}

void CRoot::RemoveTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE *_listener)
{
    assert(m_inputContext != nullptr);
    m_inputContext->RemoveTapRecognizerListener(_listener);
}

