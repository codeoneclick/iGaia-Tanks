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
#include "CShaderComposite.h"

class CGuiMgr : public CRenderPresentCallback_INTERFACE
{
private:

protected:

    Rocket::Core::Context* m_guiContext;
    Rocket::Core::ElementDocument* m_guiDocument;

    CGuiShellRenderMgr_INTERFACE m_renderInterface;
	CGuiShellCommonMgr_INTERFACE m_commonInterface;

    CShaderComposite* m_shaderComposite;

    void OnPresent(void);

public:

    CGuiMgr(void);
    ~CGuiMgr(void);

    inline void Set_ShaderComposite(CShaderComposite* _shaderComposite)
    {
        m_shaderComposite = _shaderComposite;
    };
    
};

#endif 
