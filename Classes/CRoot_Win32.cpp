
#include "CRoot.h"
#include "CGLContext_Win32.h"
#include "CMainLoop.h"
#include "CGLWindow_Win32.h"

CRoot::CRoot(void* _glView)
{
    CGLWindow_Win32* glView = (CGLWindow_Win32*)_glView;

	m_glContext = new CGLContext_Win32(glView->Get_HWND(), glView->Get_HDC());
    
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