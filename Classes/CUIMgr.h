//
//  CGuiMgr.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/26/13.
//
//

#ifndef CUIMgr_h
#define CUIMgr_h

#include "HCommon.h"
#include "CUIShellFileMgr.h"
#include "CUIShellRenderMgr.h"
#include "CUIShellCommonMgr.h"
#include "CUIShellEventListenerInstancer.h"
#include "CRenderPresentCallback.h"
#include "CInputTapRecognizerCallback.h"
#include "CShaderComposite.h"
#include "CResourceMgrsFacade.h"
#include "IUIView.h"
#include "CUIEventCallback.h"

class CUIMgr :
public CRenderPresentCallback_INTERFACE,
public CInputTapRecognizerCallback_INTERFACE
{
private:

protected:

    friend class CUIShellEventHandler;

    Rocket::Core::Context* m_uiContext;

    std::set<CUIEventCallback_INTERFACE*> m_uiEventListenersContainer;

    CUIShellRenderMgr_INTERFACE m_renderInterface;
	CUIShellCommonMgr_INTERFACE m_commonInterface;
    CUIShellEventListenerInstancer_INTERFACE* m_eventListenerInterface;

    CShaderComposite* m_shaderComposite;
	CResourceMgrsFacade* m_resourceMgrsFacade;

    void OnInputTapRecognizerPressed(i32 _x, i32 _y);
    void OnInputTapRecognizerMoved(i32 _x, i32 _y);
    void OnInputTapRecognizerReleased(i32 _x, i32 _y);

    void OnPresent(void);
    void PerformEvent(const std::string& _command);

public:

    CUIMgr(void);
    ~CUIMgr(void);

    inline void Set_ShaderComposite(CShaderComposite* _shaderComposite)
    {
        m_shaderComposite = _shaderComposite;
		m_renderInterface.Set_ShaderComposite(m_shaderComposite);
    };

	inline void Set_ResourceMgrFacade(CResourceMgrsFacade* _resourceMgrsFacade)
	{
		m_resourceMgrsFacade = _resourceMgrsFacade;
		m_renderInterface.Set_ResourceMgrFacade(m_resourceMgrsFacade);
	};

    void FillUIView(IUIView_INTERFACE* _view,const std::string& _filename);

    
    void AddUIEventListener(CUIEventCallback_INTERFACE* _listener);
    void RemoveUIEventListener(CUIEventCallback_INTERFACE* _listener);
};

#endif 
