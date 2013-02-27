//
//  CRenderMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CRenderMgr_h
#define CRenderMgr_h

#include "IGLContext.h"

class CRenderMgr
{
private:

    const IGLContext_INTERFACE* m_glContext;

    iGaiaRenderOperationWorldSpace* m_worldSpaceOperations[iGaiaMaterial::iGaia_E_RenderModeWorldSpaceMaxValue];
    iGaiaRenderOperationScreenSpace* m_screenSpaceOperations[iGaiaMaterial::iGaia_E_RenderModeScreenSpaceMaxValue];
    iGaiaRenderOperationOutlet* m_outletOperation;

    queue<iGaiaRenderOperationOffscreenProcessingHelper*> m_offscreenProcessingOperation;

    iGaiaLoopCallback m_loopCallback;

protected:

public:

    iGaiaRenderMgr(const iGaiaGLContext* _glContext);
    ~iGaiaRenderMgr(void);

    void AddEventListener(iGaiaRenderCallback* _listener, iGaiaMaterial::iGaia_E_RenderModeWorldSpace _mode);
    void RemoveEventListener(iGaiaRenderCallback* _listener, iGaiaMaterial::iGaia_E_RenderModeWorldSpace _mode);
    iGaiaTexture* Get_TextureFromWorldSpaceRenderMode(iGaiaMaterial::iGaia_E_RenderModeWorldSpace _mode);
    iGaiaTexture* Get_TextureFromScreenSpaceRenderMode(iGaiaMaterial::iGaia_E_RenderModeScreenSpace _mode);

    void AddOffscreenProcessOperation(iGaiaRenderOperationOffscreenProcessingHelper* _operation);

    void OnUpdate(void);
    
};

#endif
