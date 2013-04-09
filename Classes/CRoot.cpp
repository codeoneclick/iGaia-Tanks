
#include "CRoot.h"
#include "CMainLoop.h"
#include "CInputContext.h"

#ifdef __APPLE__

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include "CGLContext_iOS.h"

#else

#include "CGLWindow_Win32.h"
#include "CGLContext_Win32.h"

#endif


CRoot::CRoot(void* _glWindow)
{
#ifdef __APPLE__

	UIView* glWindow = (__bridge UIView*)_glWindow;
    assert([[glWindow layer] isKindOfClass:[CAEAGLLayer class]]);
    m_glContext = new CGLContext_iOS(static_cast<CAEAGLLayer*>(glWindow.layer));
    m_inputContext = new CInputContext((__bridge void*)glWindow);

#else

	CGLWindow_Win32* glView = (CGLWindow_Win32*)_glWindow;
	m_glContext = new CGLContext_Win32(glView->Get_HWND(), glView->Get_HDC());
	m_inputContext = CInputContext::SharedInstance();

#endif
    
    m_renderMgr = new CRenderMgr(m_glContext);
    m_updateMgr = new CSceneUpdateMgr();
    m_collisionMgr = new CCollisionMgr();
    
    m_shaderComposite = m_renderMgr->Get_ShaderComposite();

	m_uiMgr = new CUIMgr();
    m_uiMgr->Set_ShaderComposite(m_shaderComposite);
	m_uiMgr->Set_ResourceMgrFacade(m_resourceMgrsFacade);
    m_renderMgr->AddRenderPresentEventListener(m_uiMgr);
    m_inputContext->AddTapRecognizerListener(m_uiMgr);


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