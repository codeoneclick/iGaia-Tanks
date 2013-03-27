//
//  CGuiMgr.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/26/13.
//
//

#ifndef CGuiMgr_h
#define CGuiMgr_h

#include "HCommon.h"
#include "CGuiShellFileMgr.h"
#include "CGuiShellRenderMgr.h"
#include "CGuiShellCommonMgr.h"
#include "CRenderPresentCallback.h"
#include "CInputTapRecognizerCallback.h"
#include "CShaderComposite.h"
#include "CResourceMgrsFacade.h"

class CGuiMgr :
public CRenderPresentCallback_INTERFACE,
public CInputTapRecognizerCallback_INTERFACE
{
private:

protected:

    Rocket::Core::Context* m_guiContext;
    Rocket::Core::ElementDocument* m_guiDocument;

    CGuiShellRenderMgr_INTERFACE m_renderInterface;
	CGuiShellCommonMgr_INTERFACE m_commonInterface;

    CShaderComposite* m_shaderComposite;
	CResourceMgrsFacade* m_resourceMgrsFacade;

    void OnInputTapRecognizerPressed(i32 _x, i32 _y);
    void OnInputTapRecognizerMoved(i32 _x, i32 _y);
    void OnInputTapRecognizerReleased(i32 _x, i32 _y);

    void OnPresent(void);

public:

    CGuiMgr(void);
    ~CGuiMgr(void);

	void TEMP(void);

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

};

#endif 
