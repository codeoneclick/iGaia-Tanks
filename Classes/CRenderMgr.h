//
//  CRenderMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CRenderMgr_h
#define CRenderMgr_h

#include "CMainLoopUpdateCallback.h"
#include "IGLContext.h"
#include "CRenderOperationWorldSpace.h"
#include "CRenderOperationScreenSpace.h"
#include "CRenderOperationScreenOutput.h"

class CRenderMgr : public CMainLoopUpdateCallback_INTERFACE
{
private:

    const IGLContext_INTERFACE* m_glContext;
    CRenderOperationWorldSpace* m_worldSpaceOperations[E_RENDER_MODE_WORLD_SPACE_MAX];
    CRenderOperationScreenSpace* m_screenSpaceOperations[E_RENDER_MODE_SCREEN_SPACE_MAX];
    CRenderOperationScreenOutput* m_screenOutputOperation;
    
    CShaderComposite* m_shaderComposite;

    std::queue<CRenderOperationScreenSpace*> m_customScreenSpaceOperationsQueue;

protected:
    
    void OnUpdate(f32 _deltatime);

public:

    CRenderMgr(const IGLContext_INTERFACE* _glContext);
    ~CRenderMgr(void);
    
    inline CShaderComposite* Get_ShaderComposite(void)
    {
        return m_shaderComposite;
    };

    void AddEventListener(CRenderCallback_INTERFACE* _listener, E_RENDER_MODE_WORLD_SPACE _mode);
    void RemoveEventListener(CRenderCallback_INTERFACE* _listener, E_RENDER_MODE_WORLD_SPACE _mode);
    
    inline CTexture* Get_TextureWorldSpaceRenderMode(E_RENDER_MODE_WORLD_SPACE _mode)
    {
        return m_worldSpaceOperations[_mode]->Get_OperatingTexture();
    }
    
    inline CTexture* Get_TextureScreenSpaceRenderMode(E_RENDER_MODE_SCREEN_SPACE _mode)
    {
        return m_screenSpaceOperations[_mode]->Get_OperatingTexture();
    }

    CTexture* ProcessCustomScreenSpaceOperation(CMaterial* _material);
};

#endif
